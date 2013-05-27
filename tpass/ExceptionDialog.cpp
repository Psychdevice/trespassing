#include "String.hpp"
#include "Exception.hpp"

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

const char* Exception::message()
{
	char intStr[32];
	String str;

	str  = "An exception has been captured by the application runtime\r\n";
	str += "Error Code: ";
	sprintf( intStr, "0x%X", this->id() );
	str += intStr;
	str += "\r\n";
	str += "File: ";

	m_message = strdup( (char*)str );
	return m_message;
}

#if defined( PLATFORM_LINUX )

#include <X11/Xlib.h>

/*
 * Just remember kids, if the Exception Dialog throws an Exception, then you are in really deep shit.
 * So I've made it dump information to stderr if it fails.
 */
int32_t ExceptionDialog( Exception& e )
{
	Display*	dpy;
	Window		wnd, edt_text, btn_abort, btn_ignore;
	Atom		destroy;
	bool		run = true;
	int32_t		result = 0;

	dpy = XOpenDisplay( NULL );

	// -- Create a window
	wnd = XCreateSimpleWindow( dpy, DefaultRootWindow(dpy), 0,0, 500, 300, 4, 0xFF0000, 0xCCCCCC );
	// -- Get the atom for the deletion of a window (X button)
	destroy = XInternAtom( dpy, "WM_DELETE_WINDOW", false );
	// -- Apply that we wish to capture this as a ClientMessage
	XSetWMProtocols( dpy, wnd, &destroy, 1 );
	// -- Store the name
	XStoreName( dpy, wnd, "An Exception Has Occured!" );
	// -- Transient of the root window (desktop)
	XSetTransientForHint( dpy, DefaultRootWindow(dpy), wnd );

	XSelectInput(	dpy, wnd,
					ExposureMask | ButtonPressMask | ButtonReleaseMask |
					PointerMotionMask | StructureNotifyMask );

	// -- Map the window to the display
	XMapWindow( dpy, wnd );

	edt_text	= XCreateSimpleWindow( dpy, wnd, 8, 8, 500-16, 300-28-16, 1, 0x000000, 0xFFFFFFFF );
	btn_abort	= XCreateSimpleWindow( dpy, wnd, 500-128-8,300-28, 64, 24, 1, 0x000000, 0xDDDDDD );
	btn_ignore	= XCreateSimpleWindow( dpy, wnd, 500-64-4,300-28, 64, 24, 1, 0x000000, 0xDDDDDD );

	XSelectInput(	dpy, edt_text, ExposureMask | ButtonPressMask | ButtonReleaseMask | PointerMotionMask | StructureNotifyMask );
	XMapWindow( dpy, edt_text );
	XSelectInput(	dpy, btn_abort, ExposureMask | ButtonPressMask | ButtonReleaseMask | PointerMotionMask | StructureNotifyMask );
	XMapWindow( dpy, btn_abort );
	XSelectInput(	dpy, btn_ignore, ExposureMask | ButtonPressMask | ButtonReleaseMask | PointerMotionMask | StructureNotifyMask );
	XMapWindow( dpy, btn_ignore );

	XFlush( dpy );

	XGCValues values;
    values.background = 0xCCCCCC;
	GC gc = XCreateGC( dpy, wnd, GCBackground, &values );

	String str = "An Exception occured!";

	while ( run )
	{
		XEvent ev;

		if ( XPending( dpy ) > 0 )
		{
			XNextEvent( dpy, &ev );
			//XAnyEvent aev = ev.xany;

			switch ( ev.type )
			{
				case ClientMessage:
					{
						if ( (Atom)ev.xclient.data.l[0] == destroy )
						{
							run = false;
						}
					}
				break;

				case ButtonPress:
					{
						XButtonEvent bev = ev.xbutton;
						if ( bev.window == btn_abort )
						{
							result = 1;
							run = false;
						}
						if ( bev.window == btn_ignore )
						{
							result = 2;
							run = false;
						}
					}
				break;

				case Expose:
					{
						//XExposeEvent eev = ev.xexpose;

						if (ev.xexpose.count != 0)
							break;

						if ( ev.xexpose.window == wnd )
						{
							//XDrawString( dpy, wnd, gc, 2, 2 + 16, str, str.length() );
							//XDrawString( dpy, wnd, gc, 2, 2 + 48, e.what(), strlen(e.what()) );
						}
						if ( ev.xexpose.window == edt_text)
						{
							Window root;
							int x, y;
							unsigned int width, height;
							unsigned int border_width;
							unsigned int depth;

							if ( XGetGeometry( dpy, edt_text, &root,
								&x, &y, &width, &height, &border_width, &depth) == true )
							{
								XDrawString( dpy, edt_text, gc, 4, 4+16, e.what(), strlen(e.what()) );
							}
						}
						if ( ev.xexpose.window == btn_abort )
						{
							Window root;
							int x, y;
							unsigned int width, height;
							unsigned int border_width;
							unsigned int depth;

							if ( XGetGeometry( dpy, btn_abort, &root,
								&x, &y, &width, &height, &border_width, &depth) == true )
							{
								XDrawString( dpy, btn_abort, gc, 1 + (width / 2) - 15 , 16, "Abort", 5 );
							}
						}
						if ( ev.xexpose.window == btn_ignore )
						{
							Window root;
							int x, y;
							unsigned int width, height;
							unsigned int border_width;
							unsigned int depth;

							if ( XGetGeometry( dpy, btn_ignore, &root,
								&x, &y, &width, &height, &border_width, &depth) == true )
							{
								XDrawString( dpy, btn_ignore, gc, 1 + (width / 2) - 17 , 16, "Ignore", 6 );
							}
						}
					}
				break;

				default: break;
			}
		}
	}

	XFreeGC( dpy, gc );

	XUnmapWindow( dpy, wnd );
	XDestroyWindow( dpy, edt_text );
	XDestroyWindow( dpy, btn_abort );
	XDestroyWindow( dpy, btn_ignore );
	XDestroyWindow( dpy, wnd );

	XCloseDisplay( dpy );

	return result;
}

#elif defined( PLATFORM_WINDOWS )

#include <Windows.h>
#include <CommCtrl.h>

// -- Helper function aligns to next double-word
uint16_t* Align4( uint16_t* p_ptr )
{
    intptr_t ul;

    ul = (intptr_t)p_ptr;
    ul ++;
    ul >>=1;
    ul <<=1;
    return (uint16_t*)ul;
}

INT_PTR CALLBACK ExceptionDlgProc( HWND dlg, UINT msg, WPARAM wParam, LPARAM lParam )
{
	switch ( msg )
	{
	case WM_INITDIALOG:
		{
			Exception *e = (Exception*)lParam;

			SetWindowPos( dlg, 0, 0,0, 500,300, SWP_NOMOVE | SWP_NOZORDER );

			RECT crc;
			GetClientRect( dlg, &crc );

			char except_str[512];
			sprintf( except_str, "%s", e->what() );

			HWND item = CreateWindow( 	WC_EDIT, except_str,
										WS_CHILD | WS_VISIBLE | WS_BORDER | ES_READONLY | ES_MULTILINE,
										0,0,0,0, dlg, (HMENU)999, GetModuleHandle(0), 0 );
			SetWindowPos( item, 0, 8, 8, crc.right - 16, crc.bottom - 32 - 16, SWP_NOZORDER );
			SendMessage( item, WM_SETFONT, (WPARAM)GetStockObject(DEFAULT_GUI_FONT), TRUE );

			item = CreateWindow( 	WC_BUTTON, "Abort",
									WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
									0,0,0,0, dlg, (HMENU)1000, GetModuleHandle(0), 0 );
			SetWindowPos( item, 0, crc.right-128-16,crc.bottom-8-24, 64,24, SWP_NOZORDER );
			SendMessage( item, WM_SETFONT, (WPARAM)GetStockObject(DEFAULT_GUI_FONT), TRUE );

			item = CreateWindow( 	WC_BUTTON, "Ignore",
									WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
									0,0,0,0, dlg, (HMENU)1001, GetModuleHandle(0), 0 );
			SetWindowPos( item, 0, crc.right-64-8,crc.bottom-8-24, 64,24, SWP_NOZORDER );
			SendMessage( item, WM_SETFONT, (WPARAM)GetStockObject(DEFAULT_GUI_FONT), TRUE );
		}
		break;

	case WM_CLOSE:
		return EndDialog( dlg, 0 );

	case WM_COMMAND:
		switch (wParam)
		{
		case 1000:	// Abort
			return EndDialog( dlg, 1 );
		case 1001:	// Ignore
			return EndDialog( dlg, 2 );
		}
		break;

	//default: return DefDlgProc( dlg, msg, wParam, lParam );
	}
	return 0;
}

int32_t ExceptionDialog( Exception& e )
{
	void* lpdlg = 0;
	uint16_t* lpw = 0;
	wchar_t* lpwsz = 0;
	intptr_t nchar = 0;
	HWND wnd;
	MSG msg;

	// -- STD Allocate memory for the template
	lpdlg = (uint8_t*)malloc( 512 );
	memset( lpdlg, 0, 512 );

	// -- BEGINNING OF DIALOG TEMPLATE
	LPDLGTEMPLATE lpdlgtmp = (LPDLGTEMPLATE)lpdlg;
	lpdlgtmp->style	= WS_POPUP | WS_BORDER | WS_DLGFRAME | WS_SYSMENU | DS_CENTER | DS_SYSMODAL;// | DS_SETFONT;
	lpdlgtmp->cdit	= 0; // 3 child controls

	lpw = (uint16_t*)(lpdlgtmp + 1);
	*lpw++ = 0; // No Menu
	*lpw++ = 0; // Predefined dialog box class

	lpwsz = (wchar_t*)lpw;
    nchar = 1 + MultiByteToWideChar(CP_ACP, 0, "An Exception Has Occured!", -1, lpwsz, 50);
    lpw += nchar;
    // -- END OF DIALOG TEMPLATE

	int ret = DialogBoxIndirectParam( GetModuleHandle(0), lpdlgtmp, HWND_DESKTOP, ExceptionDlgProc, (LPARAM)&e );

	// -- Free the memory, set the pointer to NULL (no danglers here thanks)
	free( lpdlg );
	lpdlg = 0;

	// -- Return < 1 failure, 1 == Abort, 2 == Ignore
	return ret;
}

#endif // defined PLATFORM

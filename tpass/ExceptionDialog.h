#ifndef EXCEPTIONDIALOG_H
#define EXCEPTIONDIALOG_H

//(*Headers(ExceptionDialog)
#include <wx/stattext.h>
#include <wx/hyperlink.h>
#include <wx/richtext/richtextctrl.h>
#include <wx/button.h>
#include <wx/dialog.h>
//*)

class ExceptionDialog: public wxDialog
{
	public:

		ExceptionDialog(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~ExceptionDialog();

		//(*Declarations(ExceptionDialog)
		wxRichTextCtrl* edExceptionContent;
		wxButton* btnExceptionAgain;
		wxButton* btnExceptionAbort;
		wxHyperlinkCtrl* linkExceptionContact;
		wxStaticText* stExceptTxt1;
		//*)

	protected:

		//(*Identifiers(ExceptionDialog)
		static const long ID_BUTTON2;
		static const long ID_BUTTON1;
		static const long ID_STATICTEXT1;
		static const long ID_HYPERLINKCTRL1;
		static const long ID_RICHTEXTCTRL1;
		//*)

	private:

		//(*Handlers(ExceptionDialog)
		void OnButton1Click(wxCommandEvent& event);
		//*)

		DECLARE_EVENT_TABLE()
};

#endif

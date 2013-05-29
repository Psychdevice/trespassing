
#ifndef __thread_hpp__
#define __thread_hpp__

#if defined( PLATFORM_WINDOWS )
typedef void* wthread_t;
#elif defined( PLATFORM_LINUX )
typedef unsigned long int pthread_t;
#endif


class Thread
{
public:
#if defined( PLATFORM_WINDOWS )
	typedef wthread_t	native_thread_t;
#elif defined( PLATFORM_LINUX )
	typedef pthread_t	native_thread_t;
#endif

	Thread();							// Unused Thread
	Thread( const Thread& p_thread );	// Override copy, moves thread handling from p_thread
	template< class func_type, class arg_type >
	Thread( func_type p_function, arg_type p_argument );

	void join();

	// -- Return the native handle to the system (pthread_t for Posix systems and a HANDLE for Windows)
	native_thread_t	native_handle();

protected:

}

#endif //__thread_hpp__

#pragma once

namespace Engine
{
	#define			USING(NAMESPACE)	using namespace NAMESPACE;

	#define			MSG_BOX(_message)			MessageBox(NULL, TEXT(_message), L"System Message", MB_OK)
	#define			TAGMSG_BOX(_tag,_message)	MessageBoxW(NULL, _message, _tag, MB_OK)

	#define			BEGIN(NAMESPACE)		namespace NAMESPACE {
	#define			END						}

	#ifdef ENGINE_EXPORTS
	#define ENGINE_DLL _declspec(dllexport)
	#else
	#define ENGINE_DLL _declspec(dllimport)
	#endif // ENGINE_EXPORTS


	#define NULL_CHECK( _ptr)	\
	{if( _ptr == nullptr){DebugBreak();return;}}

	#define NULL_CHECK_RETURN( _ptr, _return)	\
	{if( _ptr == nullptr){DebugBreak();return _return;}}

	#define NULL_CHECK_MSG( _ptr, _message )		\
	{if( _ptr == nullptr){MessageBox(NULL, _message, L"System Message",MB_OK);DebugBreak();}}

	#define NULL_CHECK_RETURN_MSG( _ptr, _return, _message )	\
	{if( _ptr == nullptr){MessageBox(NULL, _message, L"System Message",MB_OK);DebugBreak();return _return;}}


	#define FAILED_CHECK(_hr)	if( ((HRESULT)(_hr)) < 0 )	\
	{ MessageBoxW(NULL, L"Failed", L"System Error",MB_OK); DebugBreak(); return E_FAIL;}

	#define FAILED_CHECK_RETURN(_hr, _return)	if( ((HRESULT)(_hr)) < 0 )		\
	{ MessageBoxW(NULL, L"Failed", L"System Error",MB_OK); DebugBreak(); return _return;}

	#define FAILED_CHECK_MSG( _hr, _message)	if( ((HRESULT)(_hr)) < 0 )	\
	{ MessageBoxW(NULL, _message, L"System Message",MB_OK); DebugBreak();return E_FAIL;}

	#define FAILED_CHECK_RETURN_MSG( _hr, _return, _message)	if( ((HRESULT)(_hr)) < 0 )	\
	{ MessageBoxW(NULL, _message, L"System Message",MB_OK); DebugBreak();return _return;}



	#define NO_COPY(CLASSNAME)							\
		private:										\
		CLASSNAME(const CLASSNAME&);					\
		CLASSNAME& operator = (const CLASSNAME&);		

	#define DECLARE_SINGLETON(CLASSNAME)				\
		NO_COPY(CLASSNAME)								\
		private:										\
		static CLASSNAME*	m_pInstance;				\
		public:											\
		static CLASSNAME*	GetInstance( void );		\
		static void DestroyInstance( void );			

	#define IMPLEMENT_SINGLETON(CLASSNAME)				\
		CLASSNAME*	CLASSNAME::m_pInstance = NULL;		\
		CLASSNAME*	CLASSNAME::GetInstance( void )	{	\
			if(NULL == m_pInstance) {					\
				m_pInstance = new CLASSNAME;			\
			}											\
			return m_pInstance;							\
		}												\
		void CLASSNAME::DestroyInstance( void ) {		\
			if(NULL != m_pInstance)	{					\
				delete m_pInstance;						\
				m_pInstance = NULL;						\
			}											\
		}

#define WORLD_X_AXIS _vec3(1.f, 0.f, 0.f)
#define WORLD_Y_AXIS _vec3(0.f, 1.f, 0.f)
#define WORLD_Z_AXIS _vec3(0.f, 0.f, 1.f)
#define VEC3_ZERO   _vec3(0.f, 0.f, 0.f)
#define VEC3_ONE3   _vec3(1.f, 1.f, 1.f)

// Event
#define EVENT_NONE			-1
#define EVENT_NEXT_STAGE	10
#define EVENT_COLOR_RED		11
#define EVENT_COLOR_BLUE	12
#define EVENT_COLOR_GREEN	13
#define EVENT_SPAWNER		20
#define EVENT_SPAWNER_GOAL	21

#define EVENT_NEAR_OPEN		30
}

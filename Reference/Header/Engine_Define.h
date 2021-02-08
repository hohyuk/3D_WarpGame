#pragma once

#include <d3d9.h>
#include <d3dx9.h>

#include <chrono>
#include <vector>
#include <list>
#include <map>
#include <string>
#include <algorithm>
#include <functional>
#include <ctime>
#include <chrono>
#include <process.h>

#pragma warning(disable : 4251)

#define	DIRECTINPUT_VERSION		0x0800
#include <dinput.h>

#include "Engine_Typedef.h"
#include "Engine_Macro.h"

#include "Engine_Struct.h"
#include "Engine_Function.h"
#include "Engine_Enum.h"

#ifdef _DEBUG

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#ifndef DBG_NEW 

#ifndef _AFX		// MFC모드가 아닐때.
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ ) 
#define new DBG_NEW 

#endif // !_AFX

#endif

#endif // _DEBUG

using namespace std;

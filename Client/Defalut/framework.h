// header.h: 표준 시스템 포함 파일
// 또는 프로젝트 특정 포함 파일이 들어 있는 포함 파일입니다.
//

#pragma once

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.
// Windows 헤더 파일
#include <windows.h>

#pragma warning(push)                   // 신뢰받는 헤더의 경고 비활성화
#pragma warning(once:26495)

// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

// 사용자가 추가한 헤더 파일
#include <d3d9.h>
#include <d3dx9.h>
#include <vector>
#include <list>
#include <deque>
#include <map>
#include <string>
#include <algorithm>
#include <functional>
#include <ctime>
#pragma warning(pop)                    // 신뢰받는 헤더의 경고 비활성화 끝

using namespace std;

#include "Macro.h"
#include "Enum.h"
#include "Typedef.h"
#include "Define.h"
#include "Struct.h"
#include "Base.h"
#include "Function.h"

#include <io.h>
#include "fmod.h"
#pragma comment(lib, "fmod_vc.lib")
#include "SoundMgr.h"

#ifdef _DEBUG

#define _CRTDBG_MAP_ALLOC
//#include <stdlib.h>
#include <crtdbg.h>

#ifndef DBG_NEW 

#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ ) 
#define new DBG_NEW 

#endif

#endif // _DEBUG
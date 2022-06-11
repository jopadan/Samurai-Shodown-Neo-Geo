#ifndef __MEMLEAKS_H__
#define __MEMLEAKS_H__

	#define _CRTDBG_MAP_ALLOC
	#include <stdlib.h>
#ifdef WIN32
	#include <crtdbg.h>
#endif
	#ifdef _DEBUG
		#ifndef DBG_NEW
			#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
			#define new DBG_NEW
		#endif
	#endif  // _DEBUG

#ifdef WIN32
	#define ReportMemoryLeaks() _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF)
#endif
#endif // __MEMLEAKS_H__

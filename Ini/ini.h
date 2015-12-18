#include "stdafx.h"
#include <tchar.h>

#define INIDLL extern "C" _declspec(dllexport)

#ifndef FILENAME
#define FILENAME "server.ini"
#endif

INIDLL BOOL Write(const TCHAR *appName,const TCHAR *keyName,const TCHAR *value);
INIDLL char *GetStringValue(const TCHAR *appName,const TCHAR *keyName,char *value);
INIDLL int GetIntValue(const TCHAR *appName,const TCHAR *keyName);
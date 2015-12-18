#include "stdafx.h"
#include "ini.h"

TCHAR path[MAX_PATH];
TCHAR* GetFileName()
{
	if(lstrlen(path)==0)
	{
		TCHAR exePath[MAX_PATH];
		GetModuleFileName(NULL,exePath,MAX_PATH);  
		TCHAR *pEnd = _tcsrchr(exePath, '\\'); 
		if (pEnd != NULL)  
		{  
			*pEnd = '\0';  

			int lenA=lstrlen(exePath);
			int lenB=lstrlen(_T(FILENAME));

			memcpy(path,exePath,lenA*sizeof(TCHAR));  
			memcpy(path+lenA,_T("\\"),lstrlen(_T("\\"))*sizeof(TCHAR)); 
			memcpy(path+lenA+1,_T(FILENAME),lstrlen(_T(FILENAME))*sizeof(TCHAR));
			path[lenA+lenB+1]='\0';
		}
	}
}

BOOL Write(const TCHAR *appName,const TCHAR *keyName,const TCHAR *value)
{
	GetFileName();
	BOOL b=WritePrivateProfileString(appName, keyName, value, path);  
	return b;
}

char *GetStringValue(const TCHAR *appName,const TCHAR *keyName,char *value)
{
	GetFileName();
	TCHAR temp[MAX_PATH];
	GetPrivateProfileString(appName, keyName, NULL, temp, MAX_PATH, path); 
	DWORD len = WideCharToMultiByte(CP_OEMCP,NULL,temp,-1,NULL,0,NULL,FALSE);
    WideCharToMultiByte (CP_OEMCP,NULL,temp,-1,value,len,NULL,FALSE);
	return value;
}

int GetIntValue(const TCHAR *appName,const TCHAR *keyName)
{
	GetFileName();
	int value=GetPrivateProfileInt(appName, keyName, 0, path);  
	return value;
}

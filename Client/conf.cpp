#include "stdafx.h"
#include "conf.h"

conf::conf(void)
{
}

void conf::Init(char *ip)
{
	HINSTANCE hDll;
	hDll=LoadLibraryA("Ini.dll");
	if(hDll==NULL)
	{
		cout<<"open dll failed"<<endl;
		system("PAUSE");
		return;
	}
	GetStringValue getstring;
	getstring=(GetStringValue)GetProcAddress(hDll,"GetStringValue");
	GetIntValue getint;
	getint=(GetIntValue)GetProcAddress(hDll,"GetIntValue");
	if(getstring==NULL || getint==NULL)
	{
		cout<<"get ini failed"<<endl;
		system("PAUSE");
		return;
	}
	this->ip=getstring(_T("SERVER"),_T("IP"),ip);
	this->ip=ip;
	this->port=getint(_T("SERVER"),_T("PORT"));
	FreeLibrary(hDll);
}

conf::~conf(void)
{
}

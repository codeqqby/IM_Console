#pragma once
#include <Windows.h>
#include <iostream>
using namespace std;

typedef BOOL (*Write)(const TCHAR *appName,const TCHAR *keyName,const TCHAR *value);
typedef char* (*GetStringValue)(const TCHAR *appName,const TCHAR *keyName,char *value);
typedef int (*GetIntValue)(const TCHAR *appName,const TCHAR *keyName);

class conf
{
public:
	conf(void);
	void Init(char *ip);
	~conf(void);
public:
	char *ip;
	int port;
};


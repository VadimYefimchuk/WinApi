#include <iostream>
#include <cstdlib>
#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <tchar.h>

using namespace std;

int main() 
{
  	string mapping_name;
	string message;
	
	printf("Enter mapping name: ");
	cin >> 	mapping_name;
	LPCSTR lpName;
	lpName = (LPCSTR)mapping_name.c_str();
	
	HANDLE hMapFile;
	DWORD  dwDesiredAccess;
  	BOOL   bInheritHandle;
  	LPCTSTR pBuf;
  	
	if(OpenFileMapping(dwDesiredAccess, bInheritHandle, lpName) == NULL)
	{
		printf("Connecting to '%s' ... failed. \n", lpName);
		printf("Creating new mapping '%s'.\n", lpName);
		hMapFile = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, 256, lpName);
	}
	else
	{
		printf("Connecting to '%s' ... done. \n", lpName);
	}
	pBuf = (LPTSTR) MapViewOfFile(hMapFile, FILE_MAP_ALL_ACCESS, 0, 0, 256);

	int A;
	while(true)
	{
		printf("Enter 1 for writing, 2 for reading, 3 for exit: ");
		cin >> A;
		if (A == 3)
		{
			UnmapViewOfFile(pBuf);
			CloseHandle(hMapFile);
			break;
		}
		switch(A)
		{
			case 1:
				{
					printf("Enter the message: ");
					cin >> message;
					TCHAR *szMsg = new TCHAR[message.size()+1];
					szMsg[message.size()]=0;
					copy(message.begin(),message.end(),szMsg);
					CopyMemory((PVOID)pBuf, szMsg, (_tcslen(szMsg) * sizeof(TCHAR)));
					break;
				}
			case 2:
				{
					printf("The message is '%s'.\n", pBuf);
					break;
				}
		}
	}

	return 0;
}

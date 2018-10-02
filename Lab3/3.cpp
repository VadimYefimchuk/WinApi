#include <iostream>
#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <vector>
#define DIV 1024
#define WIDTH 7
#define MEMSIZE 104857600
using namespace std;

int GMSE()
{
  MEMORYSTATUSEX statex;

  statex.dwLength = sizeof (statex);

  GlobalMemoryStatusEx (&statex);

  _tprintf (TEXT("There is  %*ld percent of memory in use.\n"),
            WIDTH, statex.dwMemoryLoad);
  _tprintf (TEXT("There are %*I64d total KB of physical memory.\n"),
            WIDTH, statex.ullTotalPhys/DIV);
  _tprintf (TEXT("There are %*I64d free  KB of physical memory.\n"),
            WIDTH, statex.ullAvailPhys/DIV);
  _tprintf (TEXT("There are %*I64d total KB of paging file.\n"),
            WIDTH, statex.ullTotalPageFile/DIV);
  _tprintf (TEXT("There are %*I64d free  KB of paging file.\n"),
            WIDTH, statex.ullAvailPageFile/DIV);
  _tprintf (TEXT("There are %*I64d total KB of virtual memory.\n"),
            WIDTH, statex.ullTotalVirtual/DIV);
  _tprintf (TEXT("There are %*I64d free  KB of virtual memory.\n"),
            WIDTH, statex.ullAvailVirtual/DIV);
  _tprintf (TEXT("There are %*I64d free  KB of extended memory.\n"),
            WIDTH, statex.ullAvailExtendedVirtual/DIV);
          
}

int main()
{
	GMSE();
	cout<<endl;
	
	std::vector<LPVOID *> spus;
	while(VirtualAlloc(NULL,MEMSIZE,MEM_RESERVE,PAGE_READWRITE)!=NULL)
	{
		VirtualAlloc(NULL,MEMSIZE,MEM_RESERVE,PAGE_READWRITE);
		spus.push_back(new LPVOID(VirtualAlloc(NULL,MEMSIZE,MEM_RESERVE,PAGE_READWRITE)));
	}
	
	GMSE();
	cout<<endl;
	
	int i=0;
	while (i < spus.size()) 
	{
  			VirtualFree(*spus[i],0,MEM_RELEASE);
  			i=i+2;
  	}
	
	MEMORYSTATUSEX statex;
	statex.dwLength = sizeof (statex);
  GlobalMemoryStatusEx (&statex);
  _tprintf (TEXT("There are %*I64d total KB of virtual memory.\n"),
            WIDTH, statex.ullTotalVirtual/DIV);
  _tprintf (TEXT("There are %*I64d free  KB of virtual memory.\n"),
            WIDTH, statex.ullAvailVirtual/DIV);
  _tprintf (TEXT("There are %*I64d free  KB of extended memory.\n"),
            WIDTH, statex.ullAvailExtendedVirtual/DIV);
	cout<<endl;
	
	spus.push_back(new LPVOID(VirtualAlloc(NULL,statex.ullAvailVirtual/4,MEM_RESERVE,PAGE_READWRITE)));
	
	while (i < spus.size()) 
	{
  			VirtualFree(*spus[i],0,MEM_RELEASE);
  			i=i+1;
  	}
  	
	GMSE();
	cout<<endl;
	spus.push_back(new LPVOID(VirtualAlloc(NULL,statex.ullAvailVirtual/4,MEM_RESERVE,PAGE_READWRITE)));
	GMSE();
	cout<<endl;
	spus.push_back(new LPVOID(VirtualAlloc(spus[spus.size()],statex.ullAvailVirtual/4,MEM_COMMIT,PAGE_READWRITE)));	
	GMSE();
	cout<<endl;
	
	system ("Pause");
	return 0;
}

#include <windows.h>
#include <iostream>
#include <stdio.h>
#pragma comment(lib, "user32.lib")

#define READABLE (PAGE_EXECUTE_READ | PAGE_EXECUTE_READWRITE | PAGE_EXECUTE_WRITECOPY | PAGE_READONLY | PAGE_READWRITE | PAGE_WRITECOPY)

void scan()
{
	MEMORY_BASIC_INFORMATION mbi;

	for (BYTE* addr = 0; VirtualQuery(addr, &mbi, sizeof(mbi)); addr = reinterpret_cast<BYTE*>(mbi.BaseAddress) + mbi.RegionSize)
	{
		if (mbi.State & MEM_COMMIT)
		{
			if (mbi.AllocationProtect & READABLE)
			{
				for (BYTE* i = addr; i < addr+mbi.RegionSize; ++i)
				{
					std::cout << "0x" << reinterpret_cast<void*>(i);
					std::cout << "\t" << static_cast<unsigned>(*i);
					std::cout << std::endl;
				}
			}
		}		
	}
}
int main()
{
   SYSTEM_INFO siSysInfo;
   GetSystemInfo(&siSysInfo); 
   printf("Hardware information: \n");  
   printf("  OEM ID: %u\n", siSysInfo.dwOemId);
   printf("  Number of processors: %u\n", 
      siSysInfo.dwNumberOfProcessors); 
   printf("  Page size: %u\n", siSysInfo.dwPageSize); 
   printf("  Processor type: %u\n", siSysInfo.dwProcessorType); 
   printf("  Minimum application address: %lx\n", 
      siSysInfo.lpMinimumApplicationAddress); 
   printf("  Maximum application address: %lx\n", 
      siSysInfo.lpMaximumApplicationAddress); 
   printf("  Active processor mask: %u\n", 
      siSysInfo.dwActiveProcessorMask); 
      
   //scan();
      
	system ("Pause");
	return 0;      
}

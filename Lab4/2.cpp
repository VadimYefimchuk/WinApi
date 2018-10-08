#include <windows.h>
#include <iostream>
#include <tchar.h>

int main(void)
{
	HANDLE hHeap;	
	hHeap=HeapCreate(0,0x01000,0);	
	if (hHeap!=NULL)	
	{
		std::cout << "Create Heap\n";			
	}

		
	char *strName=NULL;		
		strName=(char*)HeapAlloc(hHeap,0,100);	
		if (strName!=NULL)
		{
			std::cout << "Create HeapAlloc\n";
		}	
	

	PROCESS_HEAP_ENTRY Entry;
	Entry.lpData = NULL;
	HeapWalk(hHeap, &Entry);
	_tprintf(TEXT("Total amount of stored data %#p\n"), Entry.cbData);
	_tprintf(TEXT("Total overheads %#p\n"), Entry.cbOverhead);
	_tprintf(TEXT("Total amount of stored data %#p\n"),Entry.cbOverhead-Entry.cbData-Entry.cbOverhead);
	 	
	HeapFree(hHeap,0,strName);
	std::cout << "HeapFree\n";
	
	HeapWalk(hHeap, &Entry);
	_tprintf(TEXT("Total amount of stored data %#p\n"), Entry.cbData);
	_tprintf(TEXT("Total overheads %#p\n"), Entry.cbOverhead);
	_tprintf(TEXT("Total amount of stored data %#p\n"),Entry.cbData-Entry.cbOverhead);
	
	HeapDestroy(hHeap);
	 	
	system ("Pause");
	return 0;	
}

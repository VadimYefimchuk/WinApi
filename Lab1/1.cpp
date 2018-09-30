#include <iostream>
#include <cstdlib> 
#define WINVER 0x0502
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>
#define MAX_KEY_LENGTH 255
#define MAX_VALUE_NAME 16383

using namespace std;

void QueryKey(HKEY hKey) 
{ 
    TCHAR    achKey[MAX_KEY_LENGTH];   
    DWORD    cbName;           
    TCHAR    achClass[MAX_PATH] = TEXT("");
    DWORD    cchClassName = MAX_PATH; 
    DWORD    cSubKeys=0;       
    DWORD    cbMaxSubKey;    
    DWORD    cchMaxClass;        
    DWORD    cValues;         
    DWORD    cchMaxValue;       
    DWORD    cbMaxValueData;    
    DWORD    cbSecurityDescriptor; 
    FILETIME ftLastWriteTime;      
 
    DWORD i, retCode; 
 
    TCHAR  achValue[MAX_VALUE_NAME]; 
    DWORD cchValue = MAX_VALUE_NAME; 
 

    retCode = RegQueryInfoKey(
        hKey,                   
        achClass,               
        &cchClassName,          
        NULL,                  
        &cSubKeys,              
        &cbMaxSubKey,             
        &cchMaxClass,          
        &cValues,               
        &cchMaxValue,           
        &cbMaxValueData,       
        &cbSecurityDescriptor,  
        &ftLastWriteTime);      
 

    
    if (cSubKeys)
    {

        for (i=0; i<cSubKeys; i++) 
        { 
            cbName = MAX_KEY_LENGTH;
            retCode = RegEnumKeyEx(hKey, i,
                     achKey, 
                     &cbName, 
                     NULL, 
                     NULL, 
                     NULL, 
                     &ftLastWriteTime); 
            if (retCode == ERROR_SUCCESS) 
            {
                _tprintf(TEXT("(%d) %s\n"), i+1, achKey);
            }
        }
    } 
 


    if (cValues) 
    {

        for (i=0, retCode=ERROR_SUCCESS; i<cValues; i++) 
        { 
            cchValue = MAX_VALUE_NAME; 
            achValue[0] = '\0'; 
            retCode = RegEnumValue(hKey, i, 
                achValue, 
                &cchValue, 
                NULL, 
                NULL,
                NULL,
                NULL);
 
            if (retCode == ERROR_SUCCESS ) 
            { 
                _tprintf(TEXT("(%d) %s\n"), i+1, achValue); 
            } 
        }
    }
}

double PCFreq = 0.0;
__int64 CounterStart = 0;

void StartCounter()
{
    LARGE_INTEGER li;
    if(!QueryPerformanceFrequency(&li))
    cout << "QueryPerformanceFrequency failed!\n";

    PCFreq = double(li.QuadPart)/1000000.0;

    QueryPerformanceCounter(&li);
    CounterStart = li.QuadPart;
}
double GetCounter()
{
    LARGE_INTEGER li;
    QueryPerformanceCounter(&li);
    return double(li.QuadPart-CounterStart)/PCFreq;
}


int main() 
{ 
const DWORD encodedVersion = ::GetVersion();								//Версія Віндовс
const unsigned majorVersion = unsigned(LOBYTE(LOWORD(encodedVersion)));
const unsigned minorVersion = unsigned(HIBYTE(LOWORD(encodedVersion)));
cout<<"Windows version:"<<majorVersion<<"."<< minorVersion<<endl;
 
TCHAR windir[256];//Директорія
GetWindowsDirectory(windir, 256);
cout<<"Windows Directory:"<<windir<<endl;
 
char buffer[256]; //Імя компютера і користувача
char buffer1[256];
unsigned long size = 256;
GetComputerName( buffer, &size );
GetUserName(buffer1, &size );
cout<<"Computer Name: "<< buffer<<endl;
cout<<"User Name: "<< buffer1<<endl;
cout<<endl;

TCHAR fvol[256];
HANDLE FirstVol=FindFirstVolume(fvol, 256);
cout<<"FindFirstVolume:"<<fvol<<endl;

TCHAR nvol[256];
FindNextVolume(FirstVol,nvol, 256);
cout<<"FindNextVolume:"<<nvol<<endl;
BOOLEAN bSuccess;

DWORD dwSectorsPerCluster;
DWORD dwBytesPerSector;
DWORD dwFreeClusters;
DWORD dwTotalClusters;

bSuccess = GetDiskFreeSpace(NULL, &dwSectorsPerCluster, &dwBytesPerSector, &dwFreeClusters, &dwTotalClusters );

if(!bSuccess)
{
	printf("Could not get drive information.\n");
	exit(EXIT_FAILURE);
}

cout<<"Bytes per sector: "<< dwBytesPerSector<<endl;
cout<<"Sectors per cluster: "<< dwSectorsPerCluster<<endl;
cout<<"Free clusters: "<< dwFreeClusters<<endl;
cout<<"Total clusters: "<< dwTotalClusters<<endl;

unsigned int uiKBPerCluster = dwBytesPerSector * dwSectorsPerCluster / 1024;

cout<<"You have "  << (double) uiKBPerCluster * dwFreeClusters / 1024/1024<<" GB of free storage"<<endl;
cout<<"You have "  << (double) uiKBPerCluster * dwTotalClusters / 1024/1024<<" GB of total storage"<<endl;

FindVolumeClose(FirstVol);

cout<<endl;

printf("\nProgramm autostart OS: \n");
	HKEY hTestKey;
	if( RegOpenKeyEx( HKEY_CURRENT_USER, TEXT("Software\\Microsoft\\Windows\\CurrentVersion\\Run"), 0, KEY_READ, &hTestKey) == ERROR_SUCCESS)
  		{
      			QueryKey(hTestKey);
   		}
   
   	RegCloseKey(hTestKey);

cout<<endl;

LARGE_INTEGER lpFrequency;
QueryPerformanceFrequency(&lpFrequency);
printf("Frequency of processor: %d", lpFrequency);

cout<<endl;

StartCounter();
Sleep(1000);
cout <<"Number of processor counts: "<< GetCounter() <<"\n";

    system("pause");
    return 0; 
}

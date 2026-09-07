#include<Windows.h>
#include<TlHelp32.h>
#include<wchar.h>
#include<iostream>
#include<iomanip>
using namespace std;


DWORD ListProcess(const wchar_t* processName)
{
    HANDLE hProc = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);
    if(hProc == INVALID_HANDLE_VALUE)
    {
        return GetLastError();
    }

    PROCESSENTRY32W pStruct;
    pStruct.dwSize = sizeof(PROCESSENTRY32W);
    DWORD PID = 0;
    // Process32FirstW
    // Process32NextW
    if(Process32FirstW(hProc,&pStruct))
    {
        do
        {
           if(_wcsicmp(pStruct.szExeFile,processName) == 0)
           {
            PID = pStruct.th32ProcessID;
            break;
           }
            
        } while (Process32NextW(hProc,&pStruct));
        
    }
    return PID;

    CloseHandle(hProc);

    return NO_ERROR;

}




int main()
{   
   wcout << "PID: " << ListProcess(L"msedge.exe");
    return 0;
}
#include<Windows.h>
#include<TlHelp32.h>
#include<wchar.h>
#include<iostream>
#include<iomanip>
using namespace std;


DWORD ListProcess()
{
    HANDLE hProc = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);
    if(hProc == INVALID_HANDLE_VALUE)
    {
        return GetLastError();
    }

    PROCESSENTRY32W pStruct;
    pStruct.dwSize = sizeof(PROCESSENTRY32W);

    wcout << left
        << setw(10) << L"PID"
        << setw(30) << L"PROCESS NAME" 
        << L"PARENT ID" << endl;
    
    wcout << wstring(50,'-') << endl;

    // Process32FirstW
    // Process32NextW
    if(Process32FirstW(hProc,&pStruct))
    {
        do
        {
            wcout << left 
                << setw(10) << pStruct.th32ProcessID 
                << setw(30) << pStruct.szExeFile 
                << pStruct.th32ParentProcessID << endl;
            
        } while (Process32NextW(hProc,&pStruct));
        
    }

    CloseHandle(hProc);

    return NO_ERROR;

}




int main()
{   
    ListProcess();
    return 0;
}
#include <Windows.h>
#include <iostream>
#include <TlHelp32.h>
#include "ntapi.h"
#include "Encryption.h"

using namespace std;

void ascii_output()
{
    cout << R"(
  /$$$$$$            /$$    /$$        /$$$$$$                           /$$      /$$      /$$                /$$    /$$ /$$$$$$ 
 /$$__  $$          | $$   |__/       /$$__  $$                         | $$     | $$$    /$$$               | $$   | $$/$$__  $$
| $$  \ $$/$$$$$$$ /$$$$$$  /$$      | $$  \__/ /$$$$$$ /$$$$$$  /$$$$$$| $$   /$| $$$$  /$$$$ /$$$$$$       | $$   | $|__/  \ $$
| $$$$$$$| $$__  $|_  $$_/ | $$      | $$      /$$__  $|____  $$/$$_____| $$  /$$| $$ $$/$$ $$/$$__  $$      |  $$ / $$/ /$$$$$$/
| $$__  $| $$  \ $$ | $$   | $$      | $$     | $$  \__//$$$$$$| $$     | $$$$$$/| $$  $$$| $| $$$$$$$$       \  $$ $$/ /$$____/ 
| $$  | $| $$  | $$ | $$ /$| $$      | $$    $| $$     /$$__  $| $$     | $$_  $$| $$\  $ | $| $$_____/        \  $$$/ | $$      
| $$  | $| $$  | $$ |  $$$$| $$      |  $$$$$$| $$    |  $$$$$$|  $$$$$$| $$ \  $| $$ \/  | $|  $$$$$$$         \  $/  | $$$$$$$$
|__/  |__|__/  |__/  \___/ |__/       \______/|__/     \_______/\_______|__/  \__|__/     |__/\_______/          \_/   |________/
)" << '\n';
}

HANDLE handleA, handleB;

DWORD WINAPI Thread1(__in LPVOID lpParameter)
{
#ifdef _WIN64
    PEB* pPeb = (PEB*)__readgsqword(0x60);
#else
    PEB* pPeb = (PEB*)__readfsdword(0x30);
#endif

    DWORD IsRemoteDbgPresent;
    HANDLE IsDebugObjectPresent;
    NTSTATUS status;

    while (true)
    {
        if (pPeb)
        {
            if (pPeb->NtGlobalFlag == STATUS_GLOBAL_FLAG_DEBUGGED)
                exit(0);
            if (pPeb->BeingDebugged == 1)
                exit(0);
            status = NtQueryInformationProcess(GetCurrentProcess(), ProcessDebugPort, &IsRemoteDbgPresent, sizeof(DWORD), 0);
            if (status == STATUS_SUCCESS && IsRemoteDbgPresent != 0)
                exit(0);
            status = NtQueryInformationProcess(GetCurrentProcess(), ProcessDebugObjectHandle, &IsDebugObjectPresent, sizeof(HANDLE), 0);
            if (status == STATUS_SUCCESS && IsDebugObjectPresent != 0)
                exit(0);
        }
    }
}

DWORD WINAPI Thread2(__in LPVOID lpParameter)
{
    HANDLE hProcSnap;
    PROCESSENTRY32 pe32 = { sizeof(PROCESSENTRY32) };

    while (true)
    {
        const char DebuggersNames[10][60] = { "x64dbg", "x32dbg.exe", "ida.exe", "ida64.exe", "windbg.exe", "cheatengine-i386e.exe", "cheatengine-x86_64.exe", "Dbgview.exe", "dbgview64.exe",
            "Dbgview64a.exe" };
        hProcSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
        if (Process32First(hProcSnap, &pe32))
        {
            do
            {
                for (int i = 0; i < 10; i++)
                    if (!strcmp(pe32.szExeFile, DebuggersNames[i]))
                        exit(0);
            } while (Process32Next(hProcSnap, &pe32));
        }
    }
}

void Start()
{
    string username, BinUsername, password;

start:
    ascii_output();
    cout << "Warning: You Can Only Use From A To Z You Cant Use Special Chars Like: ; / . ]" << "\n" << "Tips: 1.You Can Use Numbers. | 2.The Length Of Username Should Be 8 Chars." << "\n";
    cout << "Enter Your Username: ";
    cin >> username;

    if (username.length() < 8)
    {
        cout << "The Length Of Username Should Be 8 Chars!" << "\n";
        system("pause");
        system("CLS");
        goto start;
    }

    BinUsername = Encrypt(username);

    cout << "Enter A Password : ";
    cin >> password;

    if (password == BinUsername)
    {
        cout << "You Passed The Encryption! Now Make KeyGen!!!!!!" << "\n";
        system("pause");
    }

    else
    {
        cout << "Password Not Correct!\n";
        system("pause");
        system("CLS");
        goto start;
    }
}

int main()
{
    RECT WindowRect;
    GetWindowRect(GetConsoleWindow(), &WindowRect);
    MoveWindow(GetConsoleWindow(), 0, 0, 1200, 600, true);
    system("Color 02");
    CreateThread(0, 0, Thread1, 0, 0, 0);
    CreateThread(0, 0, Thread2, 0, 0, 0);
    Start();
}
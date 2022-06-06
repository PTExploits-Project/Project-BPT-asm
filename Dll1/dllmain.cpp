// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include "Api.h"
#include <Windows.h>

void lol(void* pFunction, bool bLoop)
{
    void* pPosition;

    BYTE OPCodesLoop[17] = { 0x8B, 0xFF, 0x55, 0x8B, 0xEC, 0x31, 0xC0, 0xE8, 00, 00, 00, 00, 0xEB, 0xF9, 0x31, 0xC0, 0xC3 };
    BYTE OPCodesNoLoop[15] = { 0x8B, 0xFF, 0x55, 0x8B, 0xEC, 0x31, 0xC0, 0xE8, 00, 00, 00, 00, 0x31, 0xC0, 0xC3 };

    pPosition = VirtualAlloc(NULL, 50, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);

    if (bLoop)
        MoveMemory(pPosition, OPCodesLoop, 17);
    else
        MoveMemory(pPosition, OPCodesNoLoop, 15);

    *(DWORD*)((DWORD(pPosition) + 8)) = DWORD(pFunction) - DWORD(pPosition) - 0xC;

    CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)pPosition, 0, 0, 0);
}

void StartHook() {
    MessageBoxA(0, "", "", MB_OK);
    while (true) {
        //MessageBoxA(0, "", "", MB_OK);
    }
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        lol(StartHook, false);
        break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}


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

__declspec (naked) void integrity_check() {
    __asm {

    }
}

void StartHook() {
    bool bPatch = false;

    while (true) {
        if (!bPatch) {
            int hooksgame = read(0x004E1C0C, 1);
            int baseZF = 0;

            if (hooksgame == 0xE9) {
                baseZF = aobScan((BYTE*)"\x8D\x2C\x38\x88", 0x135000) - 0x6;

                if (baseZF > 0) {
                    HANDLE hThread = OpenThread(THREAD_SUSPEND_RESUME, FALSE, getThreadID(GetCurrentProcessId()));

                    //Suspende a thread para fazer as alterações afim de prevenir detecções antecipadas.
                    SuspendThread(hThread);

                    //copia todos os bytes da sessão ZForce
                    int pByteZF = copy_paste(baseZF, 0, 0x001348D4);

                    //copia todos os bytes da sessão Game.exe
                    int pByteGame = copy_paste(0x00401000, 0, 0x247FFF);

                    //espaço alocado dinâmico para pôr os bytes da sessão ZForce
                    void* pbIntegrity = VirtualAlloc(0, 0xBC, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);

                    hookFunc(0xE9, (DWORD)pbIntegrity, baseZF, (BYTE*)"\x90", 1); //Hook para o endereço alocado

                    write((DWORD)pbIntegrity, (BYTE*)"\x81\xFE\xD4\x48\x13\x00" //cmp esi, 001348D4
                        "\x74\x43"	//je ..
                        "\x81\xFE\xFF\x7F\x24\x00" //cmp esi,00247FFF
                        "\x74\x49" //je ..
                        "\x81\xF9\x6D\x1C\x4E\x00" //cmp ecx,004E1C6D
                        "\x74\x4f"
                        "\x81\xF9\x15\x1C\x4E\x00" //cmp ecx,004E1C15
                        "\x74\x55"
                        "\x81\xF9\x8F\xF4\x44\x00" //cmp ecx,0044F48F
                        "\x74\x5b"
                        "\x81\xF9\xF0\xE9\x44\x00" //cmp ecx,0044E9F0
                        "\x74\x61"
                        "\x81\xF9\x4F\xED\x41\x00" //cmp ecx, 0041ED4F
                        "\x74\x67"
                        "\x81\xF9\x39\xFE\x41\x00" //cmp ecx, 0041FE39
                        "\x74\x6d"
                        "\x8D\x1C\x08" //lea ebx,[eax+ecx]
                        "\x0F\xB6\x1B" //movzx ebx,byte ptr [ebx]
                        , 0x46);

                    hookFunc(0xE9, baseZF + 0x6, (DWORD)pbIntegrity + 0x46); //return to func

                    //cmp esi, 1315D0
                    write((DWORD)pbIntegrity + 0x4B, (BYTE*)"\x8D\x98", 2); //lea ebx, [eax + 00000000]
                    write((DWORD)pbIntegrity + 0x4D, &pByteZF, 4); //Addr pByteZF
                    write((DWORD)pbIntegrity + 0x51, (BYTE*)"\x0F\xB6\x1B", 3); //movzx ebx,byte ptr [ebx]
                    hookFunc(0xE9, baseZF + 0x6, (DWORD)pbIntegrity + 0x54); //return to func

                    //cmp esi, 247FFF
                    write((DWORD)pbIntegrity + 0x59, (BYTE*)"\x8D\x98", 2); //lea ebx, [eax + 00000000]
                    write((DWORD)pbIntegrity + 0x5B, &pByteGame, 4); //Addr pByteGame
                    write((DWORD)pbIntegrity + 0x5F, (BYTE*)"\x0F\xB6\x1B", 3); //movzx ebx,byte ptr [ebx]
                    hookFunc(0xE9, baseZF + 0x6, (DWORD)pbIntegrity + 0x62); //return to func

                    //cmp ecx,004E1C6D
                    int value = pByteGame + 0xE0C6D;
                    write((DWORD)pbIntegrity + 0x67, (BYTE*)"\x8D\x98", 2);
                    write((DWORD)pbIntegrity + 0x69, &value, 4);
                    write((DWORD)pbIntegrity + 0x6D, (BYTE*)"\x0F\xB6\x1B", 3);
                    hookFunc(0xE9, baseZF + 0x6, (DWORD)pbIntegrity + 0x70); //return to func

                    //cmp ecx,004E1C15
                    value = pByteGame + 0xE0C15;
                    write((DWORD)pbIntegrity + 0x75, (BYTE*)"\x8D\x98", 2);
                    write((DWORD)pbIntegrity + 0x77, &value, 4);
                    write((DWORD)pbIntegrity + 0x7B, (BYTE*)"\x0F\xB6\x1B", 3);
                    hookFunc(0xE9, baseZF + 0x6, (DWORD)pbIntegrity + 0x7E); //return to func

                    //cmp ecx,0044F48F
                    value = pByteGame + 0x4E48F;
                    write((DWORD)pbIntegrity + 0x83, (BYTE*)"\x8D\x98", 2);
                    write((DWORD)pbIntegrity + 0x85, &value, 4);
                    write((DWORD)pbIntegrity + 0x89, (BYTE*)"\x0F\xB6\x1B", 3);
                    hookFunc(0xE9, baseZF + 0x6, (DWORD)pbIntegrity + 0x8C); //return to func

                    //cmp ecx,0044E9F0
                    value = pByteGame + 0x4D9F0;
                    write((DWORD)pbIntegrity + 0x91, (BYTE*)"\x8D\x98", 2);
                    write((DWORD)pbIntegrity + 0x93, &value, 4);
                    write((DWORD)pbIntegrity + 0x97, (BYTE*)"\x0F\xB6\x1B", 3);
                    hookFunc(0xE9, baseZF + 0x6, (DWORD)pbIntegrity + 0x9A); //return to func

                    //cmp ecx, 0041ED4F
                    value = pByteGame + 0x1DD4F;
                    write((DWORD)pbIntegrity + 0x9F, (BYTE*)"\x8D\x98", 2);
                    write((DWORD)pbIntegrity + 0xA1, &value, 4);
                    write((DWORD)pbIntegrity + 0xA5, (BYTE*)"\x0F\xB6\x1B", 3);
                    hookFunc(0xE9, baseZF + 0x6, (DWORD)pbIntegrity + 0xA8); //return to func

                    //cmp ecx, 0041FE39
                    value = pByteGame + 0x1EE39;
                    write((DWORD)pbIntegrity + 0xAD, (BYTE*)"\x8D\x98", 2);
                    write((DWORD)pbIntegrity + 0xAF, &value, 4);
                    write((DWORD)pbIntegrity + 0xB3, (BYTE*)"\x0F\xB6\x1B", 3);
                    hookFunc(0xE9, baseZF + 0x6, (DWORD)pbIntegrity + 0xB6); //return to func

                    ResumeThread(hThread);

                    //MessageBoxA(0, "", "", MB_OK);
                    bPatch = true;
                }
            }
        }
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


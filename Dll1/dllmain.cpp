// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include "Api.h"

extern void inGame();
extern void findMob();
extern void findPlayer();
extern void sellitem();
extern void putItem();
extern void noHp();
extern int reformCharForm();

int zfStart = 0, integrityCheck_07 = 0, integrityCheck_07_2 = 0, pAllocZf = 0, integrityCheck_04 = 0, pAllocGame = 0, size_region = 0x139000;
int jmpo = 0, jmpo2 = 0, jmpo3 = 0, jmpo4 = 0, jmpo5 = 0, jmpo6 = 0, jmpo7 = 0, jmpo8 = 0;

__declspec(naked) void integrity() {
    __asm {
        mov edx, [pAllocZf]
        lea ecx, [eax + edx]
        movzx ecx, byte ptr [ecx]
        jmp jmpo
    }
}

__declspec(naked) void integrity_02() {
    __asm {
        mov edx, [pAllocZf]
        lea ecx, [eax + edx]
        movzx ecx, byte ptr[ecx]
        jmp jmpo2
    }
}

__declspec(naked) void integrity_03() {
    __asm {
        mov eax, [pAllocGame]
        add eax, [ebp - 0x28]
        movzx eax, byte ptr[eax]
        jmp jmpo3
    }
}

__declspec(naked) void integrity_04() {
    __asm {
        mov edx, [pAllocGame]
        lea ebx, [eax + edx]
        movzx ebx, byte ptr[ebx]
        jmp jmpo4
    }
}

__declspec(naked) void integrity_05() {
    __asm {
        mov edx, [pAllocGame]
        lea ecx, [eax + edx]
        movzx ecx, byte ptr[ecx]
        jmp jmpo5
    }
}

__declspec(naked) void integrity_06() {
    __asm {
        mov edx, [pAllocGame]
        lea ebx, [eax + edx]
        movzx ebx, byte ptr[ebx]
        jmp jmpo6
    }
}

__declspec(naked) void integrity_07() {
    __asm {
        mov edx, [pAllocGame]
        lea ecx, [eax + edx]
        movzx ecx, byte ptr[ecx]
        jmp jmpo7
    }
}

__declspec(naked) void integrity_08() {
    __asm {
        cmp edx, 0x4e1c15
        je teste
        cmp edx, 0x44e9f0
        je teste2
        lea ecx, [eax + edx]
        movzx ecx, byte ptr[ecx]
        jmp jmpo8

        teste:
        mov edx, [pAllocGame]
        add edx, 0xe0c15
        lea ecx, [eax + edx]
        movzx ecx, byte ptr[ecx]
        jmp jmpo8

        teste2:
        mov edx, [pAllocGame]
        add edx, 0x4d9f0
        lea ecx, [eax + edx]
        movzx ecx, byte ptr[ecx]
        jmp jmpo8
    }
}

int sendbuy = 0x004CBB9C;
__declspec(naked) void meu() {
    __asm {
        mov eax, eax
        call sendbuy
        retn
    }
}

struct smTRANS_COMMAND_EX
{
    int	size;
    int code;

    int LParam;
    int WParam;
    int SParam;
    int EParam;

    int LxParam;
    int WxParam;
    int SxParam;
    int ExParam;

};

void StartHook() {
    bool bPatch = false, b1 = false;
    int codeGame = 0;
    HANDLE hThread = 0;

    while (true) {
         if (bPatch) {
            int baseZF = 0;
            hThread = OpenThread(THREAD_SUSPEND_RESUME, FALSE, getThreadID(GetCurrentProcessId()));

            if (!b1) {
                if (read(0x401000, 1) == 0xE9) {
                    SuspendThread(hThread);
                    codeGame = copy_paste(0x00401000, 0, 0x247FFF);
                    ResumeThread(hThread);
                    b1 = true;
                }
            }
            else {
                if (read(0x004E1C0C, 1) == 0xE9) {
                    SuspendThread(hThread);

                    //busca o endereço a partir da referência
                    integrityCheck_07 = aobScan((char*)"\x89\x45\xFC\x33\xC0\x89\x45\xF0\x89\x45\xF4\xB2\x01", size_region) + 0x78;
                    integrityCheck_07_2 = aobScan((char*)"\x8B\x55\xBC\x33\xC9\xB0\x01", size_region) - 0xCF;

                    int integrityCheck_04 = aobScan((char*)"\x8B\x55\xD4\x8B\x45\xD0", size_region) + 0x41;
                    int integrityCheck_04_2 = aobScan((char*)"\x50\x8B\x4D\xEC\x8B\x55\xE8\x8B\x45\xE4", size_region) - 0x14;
                    int integrityCheck_04_3 = aobScan((char*)"\x83\xC0\x4C\xBA\x82\xA1\x00\x00", size_region) + 0x7b;
                    int checkJobFace = aobScan((char*)"\x83\x78\x70\x00\x0f\x85", size_region) + 0x4;

                    zfStart = aobScan(0, size_region); //busca o endereço inicial 07x  partir do tamanho da região de memória
                    int zfEnd = read(read(read(integrityCheck_07 - 0x7f, 4), 4) + 0x70, 4); //busca o fim do endereço 07x

                    if (read(zfStart, 4) > 0x07000000 && 
                        read(integrityCheck_07, 1) == 0x8D && read(integrityCheck_07_2, 1) == 0x8D &&/*
                        read(integrityCheck_04, 1) == 0x8D && read(integrityCheck_04_2, 1) == 0x8D &&
                        read(integrityCheck_04_3, 1) == 0x8D && */read(checkJobFace, 1) == 0x0F) {

                        //detecção de programas abertos
                        write(aobScan((char*)"\xc7\x40\x08\x6c", size_region) + 0x7, (BYTE*)"\x90\x90\x90\x90\x90", 5);

                        //não fecha o game no serve local
                        write(aobScan((char*)"\x55\xFC\x83\xC2\x04", size_region) + 0x1E, (BYTE*)"\xEB", 1); 

                        //desabilita NtDuplicateObject
                        write(aobScan((char*)"\xd0\x81\xfa\x0a", size_region) - 0x15, (BYTE*)"\x00", 1);


                        /*pAllocZf = copy_paste(zfStart, 0, zfEnd); //copia os bytes da região 07x e aloca em um espaço na memória

                        hookFunc(0xE9, (DWORD)integrity, integrityCheck_07, (BYTE*)"\x90", 1); //desvia para integrity
                        jmpo = integrityCheck_07 + 0x5; //jmp para voltar a aplicação

                        hookFunc(0xE9, (DWORD)integrity_02, integrityCheck_07_2, (BYTE*)"\x90", 1); //desvia para integrity
                        jmpo2 = integrityCheck_07_2 + 0x5; //jmp para voltar  a aplicação*/

                        //

                       /* pAllocGame = copy_paste(0x00401000, 0, 0x247FFF); //copia os bytes da região .text e aloca em um espaço na memória

                        hookFunc(0xE9, (DWORD)integrity_03, integrityCheck_04, (BYTE*)"\x90", 1); //desvia para integrity
                        jmpo3 = integrityCheck_04 + 0x6; //jmp para voltar  a aplicação

                        hookFunc(0xE9, (DWORD)integrity_04, integrityCheck_04_2, (BYTE*)"\x90", 1); //desvia para integrity
                        jmpo4 = integrityCheck_04_2 + 0x5; //jmp para voltar  a aplicação

                        hookFunc(0xE9, (DWORD)integrity_05, integrityCheck_04_3, (BYTE*)"\x90", 1); //desvia para integrity
                        jmpo5 = integrityCheck_04_3 + 0x5; //jmp para voltar  a aplicação

                        lol(inGame, false);
                        lol(findMob, false);
                        lol(findPlayer, false);
                        lol(putItem, false);

                        //dm_SendTransDamage
                        copy_paste(codeGame + 0x63B9, (void*)0x004073B9, 0x6);
                        copy_paste(codeGame + 0x64ED, (void*)0x004074ED, 0x6);
                        copy_paste(codeGame + 0x64FC, (void*)0x004074FC, 0x10);
                        copy_paste(codeGame + 0x650D, (void*)0x0040750D, 0x6);
                        copy_paste(codeGame + 0x672C, (void*)0x0040772C, 0x6);
                        //dm_SelectRange
                        copy_paste(codeGame + 0x57B5, (void*)0x004067B5, 0x5);
                        //dm_SendRangeDamage
                        copy_paste(codeGame + 0x683A, (void*)0x0040783A, 0x12);
                        copy_paste(codeGame + 0x6A99, (void*)0x00407A99, 0x6);
                        //send2
                        copy_paste(codeGame + 0x5E5AA, (void*)0x0045F5AA, 6);

                        write(0x004073E6, (BYTE*)"\x90\x90\x90\x90\x90\x90", 6); //dwLastCharMove
                        write(0x00407400, (BYTE*)"\x90\x90\x90\x90\x90\x90", 6); //dwLastMouseMove

                        //dc4 put item / sell item
                        write(0x00496BED, (BYTE*)"\xEB", 1); //checkinvenitemform
                        write(0x004A0FB3, (BYTE*)"\xEB", 1); //checksellitem
                        write(0x004C915C, (BYTE*)"\xEB", 1); //checksellitem

                        //rankup
                        write((DWORD)checkJobFace, (BYTE*)"\xe9\xf5\x00\x00\x00\x90", 6);
                        write(0x00407362, (BYTE*)"\xEB", 1); //warning skill

                        //CoreMagico
                        copy_paste(codeGame + 0x89434, (void*)0x0048A434, 0x6);
                        copy_paste(codeGame + 0x88C1D, (void*)0x00489C1D, 0x6);
                        write(0x004801C4, (BYTE*)"\xEB\x45", 2); //Drop core

                        hookFunc(0xE9, (int)noHp, 0x0041ED5F); //trava hp*/
                    }
                    else {
                        MessageBoxA(0, "Error 500", "", MB_OK | MB_ICONERROR);
                    }

                    ResumeThread(hThread);
                    bPatch = true;
                }
            }
        }
        else {
            
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


#include "pch.h"
#include "thread.h"

int volta = 0x410b12, callSendDamage = 0x4073b9, pMob = 0;
bool bFoundMob = 0;

__declspec(naked) void dm_SendTransDamage() {
    __asm {
        cmp [bFoundMob], 0
        je testao
        push 0
        push 1
        push 0
        push 0
        push 0
        push 0
        push 0
        push [pMob]
        call [callSendDamage]
        add esp, 0x20
        mov dword ptr ds: [bFoundMob], 0

        testao:
        push ebp
        mov ebp, esp
        sub esp, 0x1c
        jmp [volta]
    }
}

void findMob() {

    while (true) {
        int chrOtherPlayer = 0x0B0A218, somaOtherPlayer = 0x4CF0, pMotionInfo = 0, lpCurPlayer, x, y, z;

        for (int i = 0; i < 1024; i++) {
            //Flag - smCHAR_STATE_ENEMY - Mob Life
            if (read(chrOtherPlayer, 4) > 0 && read(chrOtherPlayer + 0x39C4, 4) == 1 && read(chrOtherPlayer + 0x3A40, 2) > 0) {

                lpCurPlayer = read(0xAFE60C, 4);
                x = read(chrOtherPlayer + 0x1D8, 4) - read(lpCurPlayer + 0x1E8, 4);
                y = read(chrOtherPlayer + 0x1DC, 4) - read(lpCurPlayer + 0x1EC, 4);
                z = read(chrOtherPlayer + 0x1E0, 4) - read(lpCurPlayer + 0x1F0, 4);

                if (bAutoDamage && bFlagGet == false && bFlagSell == false)
                    if (abs(x) < 74000 && abs(z) < 50000) {
                        pMob = chrOtherPlayer - 0x10;
                        bFoundMob = true;
                        //SendTransDamage(chrOtherPlayer - 0x10, 0, 0, 0, 0, 0, 1, 0);
                        Sleep(700);
                    }
            }
            if (chrOtherPlayer < 0x1E46218)
                chrOtherPlayer += somaOtherPlayer;
        }
    }
}

int getServerSock = 0x005D5C2B;
int send2 = 0x0045F591;
int szItem = 0;

__declspec(naked)void sendputItem() {
    __asm {
        push ebp
        mov ebp, esp
        mov eax, [szItem]
        push[eax + 0x000000B0]
        call dword ptr ds : [getServerSock]
        cmp eax, ebx
        pop ecx
        je abc
        push 01
        push[TransActionItem.size]
        lea ecx, [TransActionItem.size]
        push ecx
        mov ecx, eax
        call dword ptr ds : [send2]
        pop ecx
        abc :
        pop ebp
        push putItem
        retn
    }
}

int sellitemtoshop = 0x004C9147;
int szIvenItem = 0;

__declspec(naked) void sellItemShop() {
    __asm {
        push 1
        push[szIvenItem]
        mov ecx, 0x034057B0 //cSHOP
        call sellitemtoshop
        add esp, 0xc
        push putItem
        retn
    }
}

void putItem() {
    TransActionItem.code = smTRANSCODE_PUTITEM;
    TransActionItem.size = sizeof(smTRANS_ACITON_ITEM);

    while (true) {
        if (bSellItem) {
            Sleep(2000);

            szIvenItem = 0x033B2AD4;
            int somaIvenItem = 0x314;

            for (int i = 0; i < 100; i++) {
                if (read(szIvenItem, 4) > 0x01000000 && read(szIvenItem + 0xE4, 1) == 0 && read(szIvenItem + 0xCC, 1) == 1) { //codeItem - useItem - mouseItem
                    for (int j = 0; j < sizeof(arrayDontSell); j++) {
                        bFlagSell = true;

                        if (read(szIvenItem, 4) == arrayDontSell[j]) { //codeItem
                            bFlagSell = false;
                            break;
                        }
                    }
                    if (bFlagSell)
                        break;
                }
                szIvenItem += somaIvenItem;
            }

            if (bFlagSell) {
                bSellItem = false, bFlagSell = false;
                sellItemShop();
            }
        }

        if (bDropItem) {
            Sleep(2000);

            szItem = 0xAFE6D0;
            int szSomaItem = 0xDC;

            for (int i = 0; i < 128; i++) {
                if (read(szItem + 0xA8, 4) > 0x01000000 && read(szItem + 0x8, 1) == 1) { //codeItem - stateItem
                    for (int j = 0; j < sizeof(arrayDontGet); j++) {
                        bFlagGet = true;

                        if (read(szItem + 0xA8, 4) == arrayDontGet[j]) { //codeItem
                            bFlagGet = false;
                            break;
                        }
                    }
                    if (bFlagGet)
                        break;
                }

                szItem += szSomaItem;
            }

            if (bFlagGet) {
                bSellItem = true, bFlagGet = false;

                TransActionItem.x = read(szItem + 0xc, 4);
                TransActionItem.y = read(szItem + 0x10, 4);
                TransActionItem.z = read(szItem + 0x14, 4);
                TransActionItem.lpStgArea = (void*)read(szItem + 0x98, 4);

                sendputItem();
            }
        }
    }
}

int jmpInstruction = 0x0041FE39, jmpBack = 0x0041ED64;
int callinst = 0x004197A9;

__declspec(naked) void noHp() {
    __asm {
        call [callinst]

        cmp [bNoHp], 0
        je bdesativado
        jmp [jmpInstruction]

        bdesativado:
        jmp [jmpBack]
    }
}
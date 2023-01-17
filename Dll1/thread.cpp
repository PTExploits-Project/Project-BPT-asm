#include "pch.h"
#include "thread.h"

extern DWORD dwSkillCode;

void autoAttack(int lpChar, int powParam1, int powParam2, int attackState, int resistance, int dwSkillCode, int useaccuracy) {
    dm_SendTransDamage(lpChar, powParam1, powParam2, attackState, resistance, dwSkillCode, useaccuracy, 0);
}

void autoSkill(int x, int y, int z, int lpCharTarget, int atqMin, int atqMax, int attackState, int registance, int dwSkillCode) {
    dm_SelectRange(x, y, z, 160, 0);
    dm_SendRangeDamage(x, y, z, lpCharTarget, atqMin, atqMax, attackState, registance, dwSkillCode);
}

int getRefromCharState = 0x0044CE70;

__declspec(naked) int lpReformCharForm() {
    __asm {
        push esi
        mov esi, dword ptr ds:[esp+0x8]
        push 0x0a
        pop eax
        mov ecx, esi
        call [getRefromCharState]
        inc dword ptr ds:[0x1E636D4]
        mov dword ptr ds:[esi+0x170], eax
        xor eax, eax
        inc eax
        pop esi
        retn
    }
}

__declspec(naked) int reformCharForm() {
    __asm {
        mov eax, dword ptr ds:[0xAFE60C]
        add eax,0x392c
        push eax
        call lpReformCharForm
        pop ecx
        retn
    }
}

int changeModelFace = 0x0044A42E;

void rankUp() {
    __asm {
        mov eax, dword ptr ds : [0x33ded30]
        inc dword ptr ds : [eax + 0x174]
        mov eax, dword ptr ds : [0x00AFE60C] //lpCurPlayer
        push 0
        push 0
        push[eax + 0x3AA0] //ChangeJob
        push 0
        push eax
        call [changeModelFace]
        call reformCharForm
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

                if (abs(x) < 74000 && abs(z) < 50000) {
                    if (bAutoDamage) {
                        autoAttack(chrOtherPlayer - 0x10, 0, 0, 0, 0, 0, 1);
                        Sleep(700);
                    }

                    if (bAutoSkill) {
                        int pPosX = read(chrOtherPlayer + 0x1D8, 4);
                        int pPosY = read(chrOtherPlayer + 0x1DC, 4);
                        int pPosZ = read(chrOtherPlayer + 0x1E0, 4);

                        autoSkill(pPosX, pPosY, pPosZ, 0, 500, 500, 0, 0, dwSkillCode);
                        Sleep(1000);
                    }
                }
            }
            if (chrOtherPlayer < 0x1E46218)
                chrOtherPlayer += somaOtherPlayer;
        }
    }
}

void findPlayer() {

    while (true) {
        int chrOtherPlayer = 0x0B0A218, somaOtherPlayer = 0x4CF0, pMotionInfo = 0, lpCurPlayer, x, y, z;

        for (int i = 0; i < 1024; i++) {
            pMotionInfo = read(chrOtherPlayer + 0x4794, 4);

            //Flag - PartyFlag - smCHAR_STATE_USER - CHROMOTION_STATE_DEAD
            if (read(chrOtherPlayer + 0x35C, 4) > 0 && read(chrOtherPlayer + 0x4898, 4) == 0 && read(chrOtherPlayer + 0x39C4, 4) == 0x80 && read(pMotionInfo, 4) != 0x120) {

                lpCurPlayer = read(0xAFE60C, 4);
                x = read(chrOtherPlayer + 0x1D8, 4) - read(lpCurPlayer + 0x1E8, 4);
                y = read(chrOtherPlayer + 0x1DC, 4) - read(lpCurPlayer + 0x1EC, 4);
                z = read(chrOtherPlayer + 0x1E0, 4) - read(lpCurPlayer + 0x1F0, 4);

                if (abs(x) < 136000 && abs(z) < 137000)
                    if (bSecure)
                        ExitProcess(0);
            }
            if (chrOtherPlayer < 0x1E46218)
                chrOtherPlayer += somaOtherPlayer;
        }
    }
}

int getServerSock = 0x005D5C2B;
int send2 = 0x0045F591;
int szItem = 0;

void sendputItem() {
    __asm {
        mov eax, [szItem]
        push[eax + 0x000000B0]
        call dword ptr ds : [getServerSock]
        cmp eax, ebx
        je abc
        push 01
        push[TransActionItem.size]
        lea ecx, [TransActionItem.size]
        push ecx
        mov ecx, eax
        call dword ptr ds : [send2]
        abc :
    }
}

int sellitemtoshop = 0x004C9147;
int szIvenItem = 0;

void sellItemShop() {
    __asm {
        push 1
        push[szIvenItem]
        mov ecx, 0x034057B0 //cSHOP
        call [sellitemtoshop]
        call reformCharForm
    }
}

void sellitem() {
    szIvenItem = 0x033B2AD4;
    int somaIvenItem = 0x314;

    for (int i = 0; i < 80; i++) {
        if (read(szIvenItem, 4) > 0x01000000 && read(szIvenItem + 0xE4, 1) == 0 && read(szIvenItem + 0xCC, 1) == 1) { //codeItem - useItem - mouseItem
            bFlagSell = true;

            for (int j = 0; j < sizeof(arrayDontSell); j++) {
                if (read(szIvenItem, 4) == arrayDontSell[j]) { //codeItem
                    bFlagSell = false;
                    break;
                }
            }
            if (bFlagSell) {
                Sleep(500);
                sellItemShop();

                bFlagSell = false;
                break;
            }
        }
        szIvenItem += somaIvenItem;
    }
}

void putItem() {
    TransActionItem.code = smTRANSCODE_PUTITEM;
    TransActionItem.size = sizeof(smTRANS_ACITON_ITEM);

    while (true) {
         if (bDropItem) {
            szItem = 0xAFE6D0;
            int szSomaItem = 0xDC;

            for (int i = 0; i < 80; i++) {
                if (read(szItem + 0xA8, 4) > 0x01000000 && read(szItem + 0x8, 1) == 1) { //codeItem - stateItem
                    bFlagGet = true;

                    for (int j = 0; j < sizeof(arrayDontGet); j++) {
                        if (read(szItem + 0xA8, 4) == arrayDontGet[j]) { //codeItem
                            bFlagGet = false;
                            break;
                        }
                    }

                    if (bFlagGet) {
                        Sleep(500);

                        TransActionItem.x = read(szItem + 0xc, 4);
                        TransActionItem.y = read(szItem + 0x10, 4);
                        TransActionItem.z = read(szItem + 0x14, 4);
                        TransActionItem.lpStgArea = (void*)read(szItem + 0x98, 4);

                        sendputItem();
                        sellitem();

                        bFlagGet = false;
                        break;
                    }
                }

                szItem += szSomaItem;
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
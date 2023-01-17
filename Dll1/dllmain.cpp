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

struct	sITEM_CREATE {
    DWORD	Head;			//Header
    DWORD	dwVersion;		//Generated version
    DWORD	dwTime;			//Creation Time
    DWORD	dwChkSum;		//Items checksum
};

struct sITEM_SPECIAL {

    float	Add_fAbsorb;			//Add Absorb 
    int     Add_Defence;			//Add Defence 
    float   Add_fSpeed;				//Add Speed 
    float   Add_fBlock_Rating;		//Add BlockRating
    int     Add_Attack_Speed;		//Add AttackSpeed
    int     Add_Critical_Hit;		//Add CriticalHit
    int     Add_Shooting_Range;		//Shooting Range 
    float   Add_fMagic_Mastery;     //Magic Mastery
    short	Add_Resistance[8];		//Resistance

    ////////////////////////////////////////////////

    short	Lev_Attack_Resistance[8];	//¿ø¼Ò¿¡´ëÇÑ °ø°Ý·Â
    int		Lev_Mana;				//¸¶³ªÈ¸º¹(ÃÖ¼Ò)(ÃÖ´ë)
    int		Lev_Life;				//¶óÀÌÇÁÈ¸º¹(ÃÖ¼Ò)(ÃÖ´ë) 
    int     Lev_Attack_Rating;		//¸íÁß·Â 
    short	Lev_Damage[2];			//°ø°Ý·Â

    float	Per_Mana_Regen;			//¸¶³ª Àç»ý 6
    float	Per_Life_Regen;			//¶óÀÌÇÁ Àç»ý 
    float	Per_Stamina_Regen;		//½ºÅ×¹Ì³ª Àç»ý

    //////////////////////////////////////////////////

    DWORD	dwTemp[32];
};

struct sITEMINFO {

    DWORD	dwSize;						//¾ÆÀÌÅÛ ±¸Á¶ Å©±â

    sITEM_CREATE	ItemHeader;			//¾ÆÀÌÅÛ »ý¼º Á¤º¸

    short	Durability[2];				//³»±¸·Â

    //////// ½ÇÁ¦ ¾ÆÀÌÅÛ µ¥ÀÌÅ¸Á¤º¸°¡ µé¾î°©´Ï´Ù /////////

    /*-------------------------*
    *		 ¾ÆÀÌÅÛ Á¤º¸
    *--------------------------*/
    DWORD	CODE;				//¾ÆÀÌÅÛ ÄÚµå 	
    char	ItemName[32];		//¾ÆÀÌÅÛ ÀÌ¸§ 	

    /*-------------------------*
    *		°øÅë »çÇ×
    *--------------------------*/
    int     Weight;				//¹«°Ô 		
    int     Price;				//°¡°Ý

    /////////////////////////////////////////
    int		Index;				//ÀÎµ¦½º
    int		PotionCount;		//Æ÷¼ÇÄ«¿îÅÍ
    ////////////////////////////////////////

    /**¿ø¼Ò**/
    short	Resistance[8];		//¿ø¼Ò¿¡´ëÇÑ ÀúÇ×·Â 
    /********/

    int		Sight;				//½Ã¾ß

    DWORD	Temp0;

    /*-------------------------*
    *		 °ø°Ý¼º´É
    *--------------------------*/
    short	Damage[2];			//°ø°Ý·Â 
    int     Shooting_Range;		//»çÁ¤°Å¸® 
    int     Attack_Speed;		//°ø°Ý¼Óµµ 
    int     Attack_Rating;		//¸íÁß·Â 
    int     Critical_Hit;		//1.5¹è µ¥¹ÌÁöÈ®À²  

    /*-------------------------*
    *		 ¹æ¾î¼º´É
    *--------------------------*/

    float	fAbsorb;			//Èí¼ö·Â 
    int     Defence;			//¹æ¾î·Â 
    float   fBlock_Rating;		//(¹æÆÐ)ºí·°À² 

    /*-------------------------*
    *		 ÀÌµ¿¼º´É
    *--------------------------*/
    float     fSpeed;				//ÀÌµ¿ ¼Óµµ 

    /*-------------------------*
    *		 ÆÈÂî ¼º´É
    *--------------------------*/

    int		Potion_Space;		//¼ÒÄÏ °ø°£ ÇÒ´ç 

    /**Æ¯¼ö´É·Â**/
    float   fMagic_Mastery;     //¸¶¹ý¼÷·Ãµµ 
    float   fMana_Regen;		//¸¶³ª Àç»ý 
    float   fLife_Regen;		//¶óÀÌÇÁ Àç»ý 
    float   fStamina_Regen;	    //½ºÅ×¹Ì³ª Àç»ý 
    float   fIncrease_Life;     //¶óÀÌÇÁ ÃÖ´ëÄ¡»ó½Â 
    float   fIncrease_Mana;     //¸¶³ª ÃÖ´ëÄ¡»ó½Â
    float   fIncrease_Stamina;  //½ºÅ×¹Ì³ª ÃÖ´ëÄ¡»ó½Â

    /************/

    /*-------------------------*
    *		¿ä±¸Æ¯¼º
    *--------------------------*/
    int     Level;				//·¹º§ 
    int     Strength;			//Èû 	
    int     Spirit;				//Á¤½Å·Â 
    int     Talent;				//Àç´É 
    int     Dexterity;			//¹ÎÃ¸¼º 
    int     Health;				//°Ç°­ 

    /*-------------------------*
    *		 È¸º¹¾à
    *--------------------------*/
    short   Mana[2];            //¸¶³ªÈ¸º¹(ÃÖ¼Ò)(ÃÖ´ë)
    short   Life[2];            //¶óÀÌÇÁÈ¸º¹(ÃÖ¼Ò)(ÃÖ´ë) 
    short   Stamina[2];         //½ºÅ×¹Ì³ÊÈ¸º¹(ÃÖ¼Ò)(ÃÖ´ë)

    /*-------------------------*
    *		 .....
    *--------------------------*/
    int		Money;				//º¸À¯ÇÑ µ·
    int     NotUseFlag;         //»ç¿ëºÒ°¡´É ÇÃ·¢

    DWORD	BackUpKey;			//¹é¾÷Çì´õ
    DWORD	BackUpChkSum;		//¹é¾÷ ¾ÆÀÌÅÛ Ã¼Å©¼¶

    short   ScaleBlink[2];		//½ºÄÉÀÏ º¯°æ 
    DWORD	UniqueItem;			//À¯´ÏÅ©
    short	EffectBlink[2];		//»ö»óÇ¥½Ã ÁÖ±â (0) ÀÌÆåÆ® Ã½Å©¼¶(1)
    short	EffectColor[4];		//»ö»óÇ¥½Ã¸ðµå

    DWORD	DispEffect;			//¾ÆÀÌÅÛ Ç¥½Ã ÀÌÆåÆ® (¿¹Á¤)


    /*-------------------------*
    *		Ä³¸¯ÅÍ Æ¯È­¾ÆÀÌÅÛ    (ÇöÀç ¹Ì¼³Á¤)
    *--------------------------*/

    DWORD			JobCodeMask;		//Æ¯È­ Á÷¾÷	(Á÷¾÷º° ºñÆ® ¸¶½ºÅ©)
    sITEM_SPECIAL	JobItem;			//Æ¯È­ ¾ÆÀÌÅÛ ¼º´É

    DWORD   ItemKindCode;		//¾ÆÀÌÅÛ Á¾·ù 0ÀÌ¸é ³ë¸Ö ¾ÆÀÌÅÛ 
    DWORD   ItemKindMask;

    short   ItemAgingNum[2];	//0Àº ¿¡ÀÌÂ¡+¸î 1Àº ¿¡ÀÌÂ¡ÀÌ µÇ°íÀÖ³ª ¾Æ´Ñ°¡?
    short   ItemAgingCount[2];	//0¾ÆÀÌÅÛ ¼÷·Ã Ä«¿îÆ® 1¼÷·ÃÄ¡ ÃÖ´ë 
    short   ItemAgingProtect[2];//¿¡ÀÌÂ¡ º¸È£ 

    short   SpecialItemFlag[2];   //0Àº ÀúÁÖ¾ÆÀÌÅÛ ÇÃ·º 1 Àº Äù½ºÆ®°°Àº °÷¿¡ »ç¿ëµÇ´Â Æ¯¼ö¾ÆÀÌÅÛ

    DWORD	dwCreateTime;		//»ý¼º ½Ã°£
    DWORD	dwTemp[9];			//¿¹ºñ

};

struct TRANS_ITEMINFO
{
    int	size, code;

    sITEMINFO	Item;

    int x, y, z;

    DWORD	dwSeCode[4];
};

static DWORD iFormCode;
static DWORD iFromCnt;

static DWORD ReformStateCode(char* lpState, int size)
{
    int cnt;

    for (cnt = 0; cnt < size; cnt++)
    {
        iFormCode += ((DWORD)lpState[cnt]) * ((iFromCnt & 0x1FFF) + 1);
        iFromCnt++;
    }

    return iFormCode;
}

static DWORD GetRefromItemCode(sITEMINFO* lpItemInfo, int Key)
{

    iFormCode = 0;
    iFromCnt = Key;

    ReformStateCode((char*)&lpItemInfo->CODE, sizeof(DWORD));
    ReformStateCode((char*)lpItemInfo->ItemName, 32);

    ReformStateCode((char*)&lpItemInfo->Weight, sizeof(int));
    ReformStateCode((char*)&lpItemInfo->Price, sizeof(int));

    ReformStateCode((char*)lpItemInfo->Resistance, sizeof(short) * 8);
    ReformStateCode((char*)lpItemInfo->Damage, sizeof(short) * 2);

    ReformStateCode((char*)&lpItemInfo->fAbsorb, sizeof(float));
    ReformStateCode((char*)&lpItemInfo->Defence, sizeof(int));
    ReformStateCode((char*)&lpItemInfo->fBlock_Rating, sizeof(float));

    ReformStateCode((char*)&lpItemInfo->Shooting_Range, sizeof(int));
    ReformStateCode((char*)&lpItemInfo->Attack_Speed, sizeof(int));

    ReformStateCode((char*)&lpItemInfo->Attack_Rating, sizeof(int));
    ReformStateCode((char*)&lpItemInfo->Critical_Hit, sizeof(int));

    ReformStateCode((char*)&lpItemInfo->fSpeed, sizeof(float));
    ReformStateCode((char*)&lpItemInfo->Potion_Space, sizeof(int));

    ReformStateCode((char*)&lpItemInfo->fMagic_Mastery, sizeof(float));
    ReformStateCode((char*)&lpItemInfo->fMana_Regen, sizeof(float));
    ReformStateCode((char*)&lpItemInfo->fLife_Regen, sizeof(float));
    ReformStateCode((char*)&lpItemInfo->fStamina_Regen, sizeof(float));
    ReformStateCode((char*)&lpItemInfo->fIncrease_Life, sizeof(float));
    ReformStateCode((char*)&lpItemInfo->fIncrease_Mana, sizeof(float));
    ReformStateCode((char*)&lpItemInfo->fIncrease_Stamina, sizeof(float));

    ReformStateCode((char*)&lpItemInfo->Level, sizeof(int));
    ReformStateCode((char*)&lpItemInfo->Strength, sizeof(int));
    ReformStateCode((char*)&lpItemInfo->Spirit, sizeof(int));
    ReformStateCode((char*)&lpItemInfo->Talent, sizeof(int));
    ReformStateCode((char*)&lpItemInfo->Dexterity, sizeof(int));
    ReformStateCode((char*)&lpItemInfo->Health, sizeof(int));

    ReformStateCode((char*)lpItemInfo->Mana, sizeof(short) * 2);
    ReformStateCode((char*)lpItemInfo->Life, sizeof(short) * 2);
    ReformStateCode((char*)lpItemInfo->Stamina, sizeof(short) * 2);

    ReformStateCode((char*)&lpItemInfo->Money, sizeof(int));
    ReformStateCode((char*)&lpItemInfo->JobCodeMask, sizeof(DWORD));
    ReformStateCode((char*)&lpItemInfo->JobItem, sizeof(sITEM_SPECIAL));

    ReformStateCode((char*)&lpItemInfo->UniqueItem, sizeof(DWORD));
    ReformStateCode((char*)lpItemInfo->EffectBlink, sizeof(short) * 2);
    ReformStateCode((char*)lpItemInfo->EffectColor, sizeof(short) * 4);
    ReformStateCode((char*)lpItemInfo->ScaleBlink, sizeof(short) * 2);
    ReformStateCode((char*)&lpItemInfo->DispEffect, sizeof(DWORD));

    return iFormCode;
}

void validateItem(sITEMINFO* sItem, DWORD dwPlayTime) {
    sItem->ItemHeader.Head = 10000 + GetCurrentTime();

    DWORD dwCode = GetRefromItemCode(sItem, sItem->ItemHeader.Head);

    sItem->ItemHeader.dwChkSum = dwCode;
    sItem->ItemHeader.dwVersion = 0xC;
    sItem->dwCreateTime = GetCurrentTime();

    if (sItem->BackUpKey || sItem->BackUpChkSum)
    {
        sItem->BackUpKey = sItem->ItemHeader.Head;
        sItem->BackUpChkSum = sItem->ItemHeader.dwChkSum;
    }

    sItem->Temp0 = sItem->ItemHeader.dwChkSum + sItem->CODE;
}

#define XOR_ITEM_SeCode_0	0x536c56ba
#define XOR_ITEM_SeCode_1	0x9ab536cd
#define XOR_ITEM_SeCode_2	0xc6abce56

DWORD rsITEM_SecCode_Xor[] = {
    0x6794bca6 ,
    0x78645fe3 ,
    0xcea82934 ,
    0x56fdca87 ,
    0x357d3653 ,
    0xf3487eba ,
    0x3478978f ,
    0x6793fbc2 ,
    0x5842eec6 ,
    0x257ecdb5 ,
    0x579cbec5 ,
    0x985612ab ,
    0x5487cc56 ,
    0xba7d4553 ,
    0xeca53b96 ,
    0xb5c549ce
};

DWORD rsRegist_EnterKey(DWORD _dwCode, DWORD _dwAdd)
{
    return rsITEM_SecCode_Xor[(_dwCode + _dwAdd) & 0xF];
}

DWORD GetSpeedSum(const char* szName)
{
    DWORD cnt;
    DWORD Sum1, Sum2;
    BYTE ch;
    DWORD  dwSum;

    Sum2 = 0;
    dwSum = 0;

    cnt = 0;

    while (1)
    {
        ch = (BYTE)szName[cnt];
        if (ch == 0) break;
        if (ch >= 'a' && ch <= 'z')
        {
            Sum2 += (ch - 0x20) * (cnt + 1);
            dwSum += (ch - 0x20) * (cnt * cnt);
        }
        else
        {
            Sum2 += (ch * (cnt + 1));
            dwSum += ch * (cnt * cnt);
        }
        cnt++;
    }

    Sum1 = cnt;

    return (dwSum << 24) | (Sum1 << 16) | Sum2;
}

int	RegisterItem(TRANS_ITEMINFO* lpTransItemInfo, sITEMINFO* sItem, int NewItem)
{
    DWORD	cnt;
    DWORD	Key;

    DWORD lpCurPlayer = read(0x017A3058, 4);
    DWORD	dwOs = read(lpCurPlayer + 0x39C8, 4); //dwobjectserial
    DWORD	dwCode_Name = GetSpeedSum("crooks2"); //namechar
    DWORD	dwSvCode = 0;
    DWORD	dwSndCount = 1;
    DWORD	dwItemChkSum = sItem->ItemHeader.dwChkSum ^ sItem->ItemHeader.Head;
    DWORD dwPlayTime = GetCurrentTime(); //read(0x00FD9D1C, 4);


    Key = (dwPlayTime & 0xFFFF) ^ dwItemChkSum;
    Key = Key ^ (Key << 10);

    lpTransItemInfo->dwSeCode[0] = (dwSvCode << 16) | (dwSndCount & 0xFFFF);

    if (NewItem) lpTransItemInfo->dwSeCode[0] |= 0x8000000;
    else lpTransItemInfo->dwSeCode[0] &= 0x7FFFFFFF;

    lpTransItemInfo->dwSeCode[1] = dwItemChkSum ^ ((dwCode_Name & 0xFFFF) | (dwOs << 16));
    lpTransItemInfo->dwSeCode[2] = 0 ^ lpTransItemInfo->dwSeCode[0] ^ lpTransItemInfo->dwSeCode[1];
    lpTransItemInfo->dwSeCode[3] = Key;

    lpTransItemInfo->dwSeCode[0] ^= (XOR_ITEM_SeCode_0 ^ rsRegist_EnterKey(Key ^ dwOs, 0));
    lpTransItemInfo->dwSeCode[1] ^= (XOR_ITEM_SeCode_1 ^ rsRegist_EnterKey(Key ^ dwOs, 1));
    lpTransItemInfo->dwSeCode[2] ^= (XOR_ITEM_SeCode_2 ^ rsRegist_EnterKey(Key ^ dwOs, 2));

    /*(DWORD*)0xfa81fc = sItem->ItemHeader.dwChkSum;
    *(DWORD*)0xfa8200 = sItem->ItemHeader.Head;
    *(DWORD*)0xfa8204 = lpTransItemInfo->dwSeCode[1];
    *(DWORD*)0xfa8208 = lpTransItemInfo->dwSeCode[3];*/

    //lpPlayInfo->smCharInfo.SndItemSecCodeCount++;

    return TRUE;
}

smTRANS_COMMAND_EX			TransCommandEx;

void checkRegister(smTRANS_COMMAND_EX* smTrans) {
    DWORD lpCurPlayer = read(0x00A6DC8C, 4);
    DWORD	dwOs = read(lpCurPlayer + 0x39C4, 4); //dwobjectserial

    DWORD	dwSeCode[4];

    DWORD Key = smTrans->ExParam;

    dwSeCode[1] = smTrans->LxParam ^ (XOR_ITEM_SeCode_1 ^ rsRegist_EnterKey(Key ^ dwOs, 1));

    DWORD dwCmpCode = (smTrans->LParam ^ smTrans->SParam) ^ ((GetSpeedSum("stest") & 0xFFFF) | (dwOs << 16));

    /*if (dwSeCode[1] != dwCmpCode)
        MessageBoxA(NULL, "Error", "Error", MB_ICONERROR | MB_OK);
    else
        MessageBoxA(NULL, "Ok", "", MB_OK);*/
}

void testezin(TRANS_ITEMINFO* lpTransItemInfo, sITEMINFO* sItem) {
    validateItem(sItem, read(0x00AB24D8, 4));

    int PKTHR_GETITEM = 0x4847005A;

    TransCommandEx.code = PKTHR_GETITEM;
    TransCommandEx.size = sizeof(smTRANS_COMMAND_EX);
    TransCommandEx.WParam = sItem->CODE;
    TransCommandEx.LParam = sItem->ItemHeader.Head;
    TransCommandEx.SParam = sItem->ItemHeader.dwChkSum;
    TransCommandEx.EParam = 0 ^ PKTHR_GETITEM ^ sItem->ItemHeader.dwChkSum;

    RegisterItem(lpTransItemInfo, sItem, 1);

    TransCommandEx.WxParam = lpTransItemInfo->dwSeCode[0];
    TransCommandEx.LxParam = lpTransItemInfo->dwSeCode[1];
    TransCommandEx.SxParam = lpTransItemInfo->dwSeCode[2];
    TransCommandEx.ExParam = lpTransItemInfo->dwSeCode[3];

    checkRegister(&TransCommandEx);
}

void StartHook() {
    bool bPatch = false, b1 = false;
    int codeGame = 0;
    HANDLE hThread = 0;

    TRANS_ITEMINFO* lpTransItemInfo = new TRANS_ITEMINFO;
    sITEMINFO* sItem = (sITEMINFO*)0x00FF6FD0;

    while (true) {
        if (GetAsyncKeyState(VK_F1) < 0) {
            Sleep(200);
            for (int i = 0; i < 528; i++) {
                int iItem = read(0x070C7668 + i, 1);
                write(0x00FF6FD0 + i, &iItem, 1);
            }
        }

        if (GetAsyncKeyState(VK_F2) < 0) {
            Sleep(200);
            testezin(lpTransItemInfo, sItem);
        }

        if (GetAsyncKeyState(VK_F3) < 0) {
            Sleep(200);
            write(0x00FF6FC0, (BYTE*)"\x1", 1);
        }

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


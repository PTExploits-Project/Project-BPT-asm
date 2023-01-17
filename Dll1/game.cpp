#include "pch.h"
#include "game.h"

extern int reformCharForm();

BYTE dwItem[] = { 00, 0x01, 0x07, 0x01, 0x44, 0x61, 0x67, 0x67, 0x65, 0x72, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x57, 0x53, 0x32, 0x30, 0x31, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x16, 0x00, 0x00, 0x00, 0x2C, 0x00, 0x00, 0x00, 0x57, 0x65, 0x61, 0x70, 0x6F, 0x6E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x57, 0x53, 0x32, 0x30, 0x31, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x99, 0x00, 0x00, 0x00, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x8B, 0x41, 0x29, 0x20, 0x0C, 0x00, 0x00, 0x00, 0x59, 0xFA, 0x40, 0x93, 0x2B, 0xD2, 0x03, 0x00, 0x0F, 0x00, 0x0F, 0x00, 0x00, 0x01, 0x07, 0x01, 0x41, 0x64, 0x61, 0x67, 0x61, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x3C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x2B, 0xD3, 0x0A, 0x01, 0x01, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x32, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

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

	short	Lev_Attack_Resistance[8];	//원소에대한 공격력
	int		Lev_Mana;				//마나회복(최소)(최대)
	int		Lev_Life;				//라이프회복(최소)(최대) 
	int     Lev_Attack_Rating;		//명중력 
	short	Lev_Damage[2];			//공격력

	float	Per_Mana_Regen;			//마나 재생 6
	float	Per_Life_Regen;			//라이프 재생 
	float	Per_Stamina_Regen;		//스테미나 재생

	//////////////////////////////////////////////////

	DWORD	dwTemp[32];
};

struct sITEMINFO {

	DWORD	dwSize;						//아이템 구조 크기

	sITEM_CREATE	ItemHeader;			//아이템 생성 정보

	short	Durability[2];				//내구력

	//////// 실제 아이템 데이타정보가 들어갑니다 /////////

	/*-------------------------*
	*		 아이템 정보
	*--------------------------*/
	DWORD	CODE;				//아이템 코드 	
	char	ItemName[32];		//아이템 이름 	

	/*-------------------------*
	*		공통 사항
	*--------------------------*/
	int     Weight;				//무게 		
	int     Price;				//가격

	/////////////////////////////////////////
	int		Index;				//인덱스
	int		PotionCount;		//포션카운터
	////////////////////////////////////////

	/**원소**/
	short	Resistance[8];		//원소에대한 저항력 
	/********/

	int		Sight;				//시야

	DWORD	Temp0;

	/*-------------------------*
	*		 공격성능
	*--------------------------*/
	short	Damage[2];			//공격력 
	int     Shooting_Range;		//사정거리 
	int     Attack_Speed;		//공격속도 
	int     Attack_Rating;		//명중력 
	int     Critical_Hit;		//1.5배 데미지확율  

	/*-------------------------*
	*		 방어성능
	*--------------------------*/

	float	fAbsorb;			//흡수력 
	int     Defence;			//방어력 
	float   fBlock_Rating;		//(방패)블럭율 

	/*-------------------------*
	*		 이동성능
	*--------------------------*/
	float     fSpeed;				//이동 속도 

	/*-------------------------*
	*		 팔찌 성능
	*--------------------------*/

	int		Potion_Space;		//소켓 공간 할당 

	/**특수능력**/
	float   fMagic_Mastery;     //마법숙련도 
	float   fMana_Regen;		//마나 재생 
	float   fLife_Regen;		//라이프 재생 
	float   fStamina_Regen;	    //스테미나 재생 
	float   fIncrease_Life;     //라이프 최대치상승 
	float   fIncrease_Mana;     //마나 최대치상승
	float   fIncrease_Stamina;  //스테미나 최대치상승

	/************/

	/*-------------------------*
	*		요구특성
	*--------------------------*/
	int     Level;				//레벨 
	int     Strength;			//힘 	
	int     Spirit;				//정신력 
	int     Talent;				//재능 
	int     Dexterity;			//민첩성 
	int     Health;				//건강 

	/*-------------------------*
	*		 회복약
	*--------------------------*/
	short   Mana[2];            //마나회복(최소)(최대)
	short   Life[2];            //라이프회복(최소)(최대) 
	short   Stamina[2];         //스테미너회복(최소)(최대)

	/*-------------------------*
	*		 .....
	*--------------------------*/
	int		Money;				//보유한 돈
	int     NotUseFlag;         //사용불가능 플랙

	DWORD	BackUpKey;			//백업헤더
	DWORD	BackUpChkSum;		//백업 아이템 체크섬

	short   ScaleBlink[2];		//스케일 변경 
	DWORD	UniqueItem;			//유니크
	short	EffectBlink[2];		//색상표시 주기 (0) 이펙트 첵크섬(1)
	short	EffectColor[4];		//색상표시모드

	DWORD	DispEffect;			//아이템 표시 이펙트 (예정)


	/*-------------------------*
	*		캐릭터 특화아이템    (현재 미설정)
	*--------------------------*/

	DWORD			JobCodeMask;		//특화 직업	(직업별 비트 마스크)
	sITEM_SPECIAL	JobItem;			//특화 아이템 성능

	DWORD   ItemKindCode;		//아이템 종류 0이면 노멀 아이템 
	DWORD   ItemKindMask;

	short   ItemAgingNum[2];	//0은 에이징+몇 1은 에이징이 되고있나 아닌가?
	short   ItemAgingCount[2];	//0아이템 숙련 카운트 1숙련치 최대 
	short   ItemAgingProtect[2];//에이징 보호 

	short   SpecialItemFlag[2];   //0은 저주아이템 플렉 1 은 퀘스트같은 곳에 사용되는 특수아이템

	DWORD	dwCreateTime;		//생성 시간
	DWORD	dwTemp[9];			//예비

};

struct sITEM
{
	DWORD	CODE;
	char	ItemNameIndex[32];	//Item Name	

	/*-------------------------*
	*	The set during initialization
	*--------------------------*/
	char	LastCategory[16];   //The final category	
	int		w;
	int     h;			        //Item size
	char	ItemFilePath[64];   //Items loaded when a file path
	DWORD	Class;		        //The type of item
	char    DorpItem[64];       //When the item drops
	DWORD   SetModelPosi;		//Position the item to be set
	int		SoundIndex;			//Sound item
	int     WeaponClass;		//Recognize that the close-launched type


	//--------------------------

	int Flag;			        //Flags items
	int x, y;			        //The item is drawn coordinates
	int SetX, SetY;				//Gives the item is set to be put in place

	DWORD	lpItem; //Pointer required to load the picture
	int		ItemPosition;       //This item gives a position on the presence of inventory (right hand, left hand, both hands, gapot ...)

	int     PotionCount;		//Only when the potion counts
	int     NotUseFlag;			//It gives the flag when the required value is not satisfied
	int     SellPrice;			//Items sold price

	int     OldX, OldY;          //Doetdeon coordinates the item is set in the past
	DWORD	lpTempItem; //Pointer required to load the picture
	//int		LimitTimeFlag;		    //Shelf Life

	sITEMINFO sItemInfo;

};

static DWORD iFormCode;
static DWORD iFromCnt;

static DWORD ReformStateCode(char* lpState, int size)
{
	int cnt;

	for (cnt = 0; cnt < size; cnt++) {
		iFormCode += ((DWORD)lpState[cnt]) * ((iFromCnt & 0x1FFF) + 1);
		iFromCnt++;
	}

	return iFormCode;
}

static DWORD GetRefromItemCode(sITEMINFO* lpItemInfo, int Key) {

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

DWORD sendAging = 0x005D962E;

__declspec(naked) void sendAgingItemToServer() {
	__asm {
		mov eax, 0x033DC0D8
		push eax
		call[sendAging]
		retn
	}
}

DWORD gamesave = 0x005DF283;

__declspec(naked) void gameSave() {
	__asm {
		call[gamesave]
		retn
	}
}

DWORD reforminven = 0x004945E4;

__declspec(naked) void reformInvenItem() {
	__asm {
		mov ecx, 0x33620D0
		call[reforminven]
		retn
	}
}

DWORD resetcode = 0x0044FE2E;

__declspec(naked) void resetInvenItemCode() {
	__asm {
		call[resetcode]
		retn
	}
}

void reformItem(sITEMINFO* lpItemInfo) {
	int ItemFormKey = read(0x1E636D4, 4);
	lpItemInfo->ItemHeader.Head = ItemFormKey + GetCurrentTime();

	DWORD dwCode = GetRefromItemCode(lpItemInfo, lpItemInfo->ItemHeader.Head);
	lpItemInfo->ItemHeader.dwChkSum = dwCode;

	//reformInvenItem();
	resetInvenItemCode();
	//gameSave();
	//sendAgingItemToServer();
}

struct sMIXTURE_RESET_ITEM_SERVER
{
	int		size, code;
	int		DocIndex;
	int		Result;
	int		Index;

	sITEM	DesMixtureResetItem;	// ¸®¼Â ÇÒ ¾ÆÀÌÅÛ

	DWORD	dwMixtureResetStoneItemCode;	// ¹Í½ºÃÄ ¸®¼Â ½ºÅæ¿ë
	DWORD	dwMixtureResetStoneHead;		// ¹Í½ºÃÄ ¸®¼Â ½ºÅæ¿ë
	DWORD	dwMixtureResetStoneCheckSum;	// ¹Í½ºÃÄ ¸®¼Â ½ºÅæ¿ë
};
sMIXTURE_RESET_ITEM_SERVER* a = new sMIXTURE_RESET_ITEM_SERVER;
sITEM item;

void inGame() {
	while (true) {
		if (rsCompString((char*)"/secureon"))
			bSecure = true;

		if (rsCompString((char*)"/secureoff"))
			bSecure = false;

		if (rsCompString((char*)"/hiton"))
			bAutoDamage = true;

		if (rsCompString((char*)"/hitoff"))
			bAutoDamage = false;

		if (rsCompString((char*)"/ondaon")) {
			dwSkillCode = SKILL_ONDA_NEGRA;
			bAutoSkill = true;
		}

		if (rsCompString((char*)"/ondaoff"))
			bAutoSkill = false;

		if (rsCompString((char*)"/manhaon")) {
			dwSkillCode = SKILL_MANHA_ORACAO;
			bAutoSkill = true;
		}

		if (rsCompString((char*)"/manhaoff"))
			bAutoSkill = false;

		if (rsCompString((char*)"/bolaon")) {
			dwSkillCode = SKILL_BOLA_FOGO;
			bAutoSkill = true;
		}

		if (rsCompString((char*)"/bolaoff")) {
			bAutoSkill = false;
		}

		if (rsCompString((char*)"/meteoron")) {
			dwSkillCode = SKILL_METEORO;
			bAutoSkill = true;
		}

		if (rsCompString((char*)"/meteoroff")) {
			bAutoSkill = false;
		}

		if (rsCompString((char*)"/itemon"))
			bDropItem = true;

		if (rsCompString((char*)"/itemoff"))
			bDropItem = false;

		if (rsCompString((char*)"/travaon"))
			bNoHp = true;

		if (rsCompString((char*)"/travaoff"))
			bNoHp = false;

		if (rsCompString((char*)"/passrankup"))
			rankUp();

		if (rsCompString((char*)"/core"))
			write(0x03396E0C, (BYTE*)"\x08", 1);

		/*if (GetAsyncKeyState(VK_F1) < 0) {
			Sleep(200);
			item = *(sITEM*)0x0338B5C0;
			
		}

		if (GetAsyncKeyState(VK_F2) < 0) {
			Sleep(200);
			write(0x0338B5C0, &item, sizeof(sITEM));
			reformInvenItem();
			resetInvenItemCode();
		}*/

		/*if (GetAsyncKeyState(VK_F1) < 0) {
			Sleep(200);
			a->size = 0;
			a->code = 0;
			a->DocIndex = 0;
			a->Result = 0;
			a->Index = 2;
			a->DesMixtureResetItem = *(sITEM*)0x0338B5C0;
			//reformItem((sITEMINFO*)0x033DC0D8);
		}

		if (GetAsyncKeyState(VK_F2) < 0) {
			Sleep(200);
			a->dwMixtureResetStoneItemCode = read(0x0338B5C0, 4);
			a->dwMixtureResetStoneHead = read(0x0338B6C4, 4);
			a->dwMixtureResetStoneCheckSum = read(0x0338B6D0, 4);
		}
		if (GetAsyncKeyState(VK_F3) < 0) {
			Sleep(200);
			int az = 0x005C8951;
			__asm {
				mov ebx, [a]
				push ebx
				call az
				pop ebx
				retn
			}
		}*/
	}
}
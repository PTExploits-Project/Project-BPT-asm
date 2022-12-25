#include "Api.h"

void dm_SendTransDamage();
void findMob();
void putItem();
void noHp();

extern bool bAutoDamage, bAutoSkill, bDropItem, bNoHp;

bool bSellItem = false;
bool bFlagGet = false, bFlagSell = false;

typedef int(__stdcall* selectRange)(int x, int y, int z, int range, int useAttackRating);
selectRange dm_SelectRange = (selectRange)0x40680d;

typedef int(__stdcall* sendRangeDamage)(int x, int y, int z, int lpCharTarget, int powParam1, int powParam2, int attackState, int registance, int dwSkillCode);
sendRangeDamage dm_SendRangeDamage = (sendRangeDamage)0x40783a;

struct smTRANS_ACITON_ITEM
{
    int size, code, state, x, y, z;
    void* lpStgArea;
};

smTRANS_ACITON_ITEM TransActionItem;

#define smTRANSCODE_PUTITEM			0x48470052

#define sinGold						0x05010100

//pot
#define sinPM1			0x04010000  //Mana
#define sinPL1			0x04020000  //Life
#define sinPS1			0x04030000  //Stamina

//cristal
#define sinGP1			0x08020000

//type
#define sin01			0x00000100	
#define sin02			0x00000200
#define sin03			0x00000300
#define sin04			0x00000400

DWORD arrayDontGet[] = {
    sinPM1 | sin01, sinPM1 | sin02, sinPM1 | sin03, //pot mana
    sinPL1 | sin01, sinPL1 | sin02, sinPL1 | sin03, //pot life
    sinPS1 | sin01, sinPS1 | sin02, sinPS1 | sin03, //pot stm
    sinGP1 | sin01 //hopy
};

DWORD arrayDontSell[] = { 
    sinPM1 | sin01, sinPM1 | sin02, sinPM1 | sin03, sinPM1 | sin04, //pot mana
    sinPL1 | sin01, sinPL1 | sin02, sinPL1 | sin03, sinPL1 | sin04, //pot life
    sinPS1 | sin01, sinPS1 | sin02, sinPS1 | sin03, sinPS1 | sin04, //pot stm
    sinGP1 | sin01 //hopy
};
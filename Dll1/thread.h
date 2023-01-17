#include "Api.h"

void findMob();
void putItem();
void noHp();

extern bool bSecure, bAutoDamage, bAutoSkill, bDropItem, bNoHp;

bool bSellItem = false;
bool bFlagGet = false, bFlagSell = false;

typedef int(__stdcall* sendTransDamage)(int, int, int, int, int, int, int, int);
sendTransDamage dm_SendTransDamage = (sendTransDamage)0x4073b9;

typedef int(__stdcall* selectRange)(int, int, int, int, int);
selectRange dm_SelectRange = (selectRange)0x40680d;

typedef int(__stdcall* sendRangeDamage)(int, int, int, int, int, int, int, int, int);
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

//Event
#define sinSP1			0x08010000 //shop
#define sinGP1			0x08020000 //crystal

//Acessory
#define sinOS1			0x02350000	//Sheltom

//type
#define sin01			0x00000100	
#define sin02			0x00000200
#define sin03			0x00000300
#define sin04			0x00000400
#define sin05			0x00000500
#define sin06			0x00000600
#define sin07			0x00000700
#define sin08			0x00000800
#define sin09			0x00000900
#define sin12			0x00000C00
#define sin24			0x00001800

DWORD arrayDontGet[] = {
    sinPM1 | sin01, sinPM1 | sin02, sinPM1 | sin03, sinPM1 | sin04, sinPM1 | sin05, //pot mana
    sinPL1 | sin01, sinPL1 | sin02, sinPL1 | sin03, sinPL1 | sin04, sinPL1 | sin05, //pot life
    sinPS1 | sin01, sinPS1 | sin02, sinPS1 | sin03, sinPS1 | sin04, sinPS1 | sin05, //pot stm
    sinGP1 | sin01, //hopy
    sinGP1 | sin02, //goblin
    sinGP1 | sin03, //decoy
    sinGP1 | sin04, //bargon
    sinGP1 | sin05, //decap
    sinGP1 | sin06, //figon
    sinGP1 | sin07, //king hopy
    sinGP1 | sin08, //hulk
    sinGP1 | sin09, //mistic
    sinGP1 | sin24 //mirotic
};

DWORD arrayDontSell[] = {
    sinPM1 | sin01, sinPM1 | sin02, sinPM1 | sin03, sinPM1 | sin04, sinPM1 | sin05, //pot mana
    sinPL1 | sin01, sinPL1 | sin02, sinPL1 | sin03, sinPL1 | sin04, sinPL1 | sin05, //pot life
    sinPS1 | sin01, sinPS1 | sin02, sinPS1 | sin03, sinPS1 | sin04, sinPS1 | sin05, //pot stm
    sinGP1 | sin01, //hopy
    sinGP1 | sin02, //goblin
    sinGP1 | sin03, //decoy
    sinGP1 | sin04, //bargon
    sinGP1 | sin05, //decap
    sinGP1 | sin06, //figon
    sinGP1 | sin07, //king hopy
    sinGP1 | sin08, //hulk
    sinGP1 | sin09, //mistic
    sinGP1 | sin24, //mirotic
    sinOS1 | sin12 //sheltom enigma
};
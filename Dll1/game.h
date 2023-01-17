#include "Api.h"

bool bSecure, bAutoDamage, bAutoSkill, bDropItem, bNoHp;
DWORD dwSkillCode = 0;

#define SKILL_ONDA_NEGRA 0xA1B
#define SKILL_MANHA_ORACAO 0x14D
#define SKILL_BOLA_FOGO 0xA1D
#define SKILL_METEORO 0xA4D

extern void rankUp();

void inGame();
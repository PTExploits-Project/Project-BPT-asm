#include "pch.h"
#include "game.h"

void inGame() {
	while (true) {
		if (rsCompString((char*)"/damageon"))
			bAutoDamage = true;

		if (rsCompString((char*)"/damageoff"))
			bAutoDamage = false;

		if (rsCompString((char*)"/skillon"))
			bAutoSkill = true;

		if (rsCompString((char*)"/skilloff"))
			bAutoSkill = false;

		if (rsCompString((char*)"/dropitemon"))
			bDropItem = true;

		if (rsCompString((char*)"/dropitemoff"))
			bDropItem = false;

		if (rsCompString((char*)"/nodamageon"))
			bNoHp = true;

		if (rsCompString((char*)"/nodamageoff"))
			bNoHp = false;
	}
}
#include "pch.h"
#include "Api.h"

void write(BYTE* dst, BYTE* value, int len) {
	DWORD old;

	VirtualProtect(dst, len, PAGE_EXECUTE_READWRITE, &old);
	MoveMemory(dst, value, len);
	VirtualProtect(dst, len, old, &old);
}

int copy_paste(DWORD addrCopy, void* addrPaste, int MAX_REGION) {
	//Aloca um endereço no processo do game
	if (addrPaste == 0)
		addrPaste = VirtualAlloc(NULL, MAX_REGION, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);

	//laço para ler e escrever
	for (int cnt = 0; cnt < MAX_REGION; cnt++) {
		int value = *(BYTE*)(addrCopy + cnt); //Lê 1 byte do endereço

		//write((void*)((DWORD)addrPaste + cnt), &value, 1); //Escreve o 1 byte lido no endereço alocado
	}

	return (DWORD)addrPaste;
}
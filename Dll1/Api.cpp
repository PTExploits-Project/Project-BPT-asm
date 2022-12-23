#include "pch.h"
#include "Api.h"

void lol(void* pFunction, bool bLoop)
{
	void* pPosition;

	BYTE OPCodesLoop[17] = { 0x8B, 0xFF, 0x55, 0x8B, 0xEC, 0x31, 0xC0, 0xE8, 00, 00, 00, 00, 0xEB, 0xF9, 0x31, 0xC0, 0xC3 };
	BYTE OPCodesNoLoop[15] = { 0x8B, 0xFF, 0x55, 0x8B, 0xEC, 0x31, 0xC0, 0xE8, 00, 00, 00, 00, 0x31, 0xC0, 0xC3 };

	pPosition = VirtualAlloc(NULL, 50, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);

	if (bLoop)
		MoveMemory(pPosition, OPCodesLoop, 17);
	else
		MoveMemory(pPosition, OPCodesNoLoop, 15);

	*(DWORD*)((DWORD(pPosition) + 8)) = DWORD(pFunction) - DWORD(pPosition) - 0xC;

	CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)pPosition, 0, 0, 0);
}

bool rsCompString(char* string) {
	BYTE dwChar[0xF];

	for (int i = 0; i < strlen(string); i++)
		dwChar[i] = read(0x03709fb0 + i, 1);

	if (strcmp(string, (char*)dwChar) == 0) {
		write(0x03709fb0, (BYTE*)"\x00", 4);
		return 1;
	}

	return 0;
}

DWORD getThreadID(DWORD dwPid) {
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, dwPid);
	DWORD Tid = 0;

	if (hSnap != INVALID_HANDLE_VALUE && dwPid > 0) {
		THREADENTRY32 te32;
		te32.dwSize = sizeof(THREADENTRY32);

		if (Thread32First(hSnap, &te32)) {
			do {
				if (te32.th32OwnerProcessID == dwPid)
				{
					Tid = te32.th32ThreadID;
					break;
				}
			} while (Thread32Next(hSnap, &te32));
		}
	}
	CloseHandle(hSnap);
	return Tid;
}

int aobScan(char* value, int size) {
	DWORD old;
	MEMORY_BASIC_INFORMATION mbi = { 0 };
	int base = 0x07000000;
	void* pData = malloc(0x7FFFFF);

	do {
		base += mbi.RegionSize;
		VirtualQuery((void*)base, &mbi, sizeof(MEMORY_BASIC_INFORMATION));
	} while (mbi.RegionSize != size && base < 0x0C000000);

	if (mbi.RegionSize > size || base > 0x0BF00000)
		return 0;

	VirtualProtect((void*)base, mbi.RegionSize, PAGE_EXECUTE_READWRITE, &old);
	MoveMemory(pData, (void*)base, mbi.RegionSize);
	VirtualProtect((void*)base, mbi.RegionSize, old, &old);

	if (value > 0)
		for (int i = 0; i < mbi.RegionSize; i++) {

			bool found = true;
			for (int j = 0; j < strlen(value); j++)
			{
				found &= value[j] == *(char*)(DWORD(pData) + i + j);
			}
			if (found)
				return base + i;
		}

	return base;
}

int copy_paste(DWORD addrCopy, void* addrPaste, int MAX_REGION) {
	//Aloca um endereço no processo do game
	if (addrPaste == NULL)
		addrPaste = VirtualAlloc(NULL, MAX_REGION, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);

	if (addrPaste == NULL)
		return 0;

	//laço para ler e escrever
	for (int cnt = 0; cnt < MAX_REGION; cnt++) {
		int value = *(BYTE*)(addrCopy + cnt); //Lê 1 byte do endereço

		write((DWORD)addrPaste + cnt, &value, 1); //Escreve o 1 byte lido no endereço alocado
	}

	return (DWORD)addrPaste;
}

void hookFunc(DWORD opcode, DWORD dst, DWORD src, BYTE* Value, unsigned int size)
{
	int Hook = DWORD(dst) - DWORD(src) - 5;

	write(src, &opcode, 1);
	write(((DWORD)src + 1), &Hook, sizeof(Hook));

	if (Value != NULL)
		write(((DWORD)src + 5), Value, size);
}

void write(DWORD dst, void* value, int len) {
	DWORD old;

	VirtualProtect((void*)dst, len, PAGE_EXECUTE_READWRITE, &old);
	MoveMemory((void*)dst, value, len);
	VirtualProtect((void*)dst, len, old, &old);
}

int read(DWORD src, int len) {
	DWORD old;
	int dst = NULL;

	VirtualProtect((void*)src, len, PAGE_EXECUTE_READWRITE, &old);
	MoveMemory(&dst, (void*)src, len);
	VirtualProtect((void*)src, len, old, &old);

	return (DWORD)dst;
}

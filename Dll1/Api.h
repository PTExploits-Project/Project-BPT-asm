#include <Windows.h>
#include <stdlib.h>
#include <TlHelp32.h>

void lol(void* pFunction, bool bLoop);
bool rsCompString(char* string);
DWORD getThreadID(DWORD dwPid);
int aobScan(char* value, int size);
int copy_paste(DWORD addrCopy, void* addrPaste, int MAX_REGION);
void hookFunc(DWORD opcode, DWORD dst, DWORD src, BYTE* Value = 0, unsigned int size = 0);
void write(DWORD dst, void* value, int len);
int read(DWORD src, int len);
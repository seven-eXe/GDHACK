#include "Entry.hpp"

cInfo* INFO = new cInfo();

DWORD GetProcId(const char* procname)
{
	PROCESSENTRY32 pe;
	HANDLE hSnap;

	pe.dwSize = sizeof(PROCESSENTRY32);
	hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
	if (Process32First(hSnap, &pe)) {
		do {
			if (strcmp(pe.szExeFile, procname) == 0)
				break;
		} while (Process32Next(hSnap, &pe));
	}
	return pe.th32ProcessID;
}


uintptr_t GetModuleBaseAddress(DWORD procId, const char* modName)
{
	uintptr_t modBaseAddr = 0;
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, procId);
	if (hSnap != INVALID_HANDLE_VALUE)
	{
		MODULEENTRY32 modEntry;
		modEntry.dwSize = sizeof(modEntry);
		if (Module32First(hSnap, &modEntry))
		{
			do
			{
				if (!strcmp(modEntry.szModule, modName))
				{
					modBaseAddr = (uintptr_t)modEntry.modBaseAddr;
					break;
				}
			} while (Module32Next(hSnap, &modEntry));
		}
	}
	CloseHandle(hSnap);
	return modBaseAddr;
}


bool isProcessRun(const char* processName)
{
	HANDLE hSnap = NULL;
	PROCESSENTRY32 pe32;
	pe32.dwSize = sizeof(PROCESSENTRY32);
	hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hSnap != NULL)
	{
		if (Process32First(hSnap, &pe32))
		{
			if (lstrcmp(pe32.szExeFile, processName) == 0)
				return TRUE;
			while (Process32Next(hSnap, &pe32))
				if (lstrcmp(pe32.szExeFile, processName) == 0)
					return TRUE;
		}
	}
	CloseHandle(hSnap);
	return FALSE;
}


int main()
{
	if (isProcessRun("GeometryDash.exe"))
	{
		SetConsoleTitle("GDHack External | seven.eXe & Receiver (1.0)");
		system("color 06");

		const char* processName = "GeometryDash.exe";

		DWORD procId = GetProcId(processName);
		INFO->hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, procId);
		INFO->baseAddress = GetModuleBaseAddress(procId, processName);

		ReadProcessMemory(INFO->hProcess, (void*)(GEOMETRY_PLAYER_PTR_OFFSET), &INFO->PlayerPTR, sizeof(&INFO->PlayerPTR), NULL);

		std::string inputCode;
		std::cout << "[+] GDHack External by seven.eXe & Receiver (1.0)\n[+] Hi, " << cheatGetPlayerName() << std::endl;
		std::cout << 
			"[+] Input codes: \n\
			[+] 1 - Toggle NoClip\n\
			[+] 2 - Change music index\n\
			[+] 3 - Disable music limit\n\
			[+] 4 - JumpHack\n[+] 5 - Practice music hack\n[+] 6 - Unlock all icons\n[+] 7 - Patch fucking anticheat\n[+] 8 - Unlock all levels\n[+] 9 - ShopHack\n[+] 10 - Unlock secret lvl" << std::endl;
		do {
			std::cout << "[+] Enter code: ";
			std::cin >> inputCode;
			switch (atoi(inputCode.c_str()))
			{
				case 1: cheatFuncNoclip();
					break;
				case 2: cheatFuncMusicHack();
					break;
				case 3: cheatFuncMusicLimit();
					break;
				case 4: cheatFuncJumpHack();
					break;
				case 5: cheatFuncPracticeMusicHack();
					break;
				case 6: cheatFuncUnlockAllIcons();
					break;
				case 7: cheatFuncPatchFuckingAnticheat();
					break;
				case 8: cheatFuncUnlockAllLevels();
					break;
				case 9: cheatFuncShopHack();
					break;
				case 10: cheatFuncUnlockSecretLvl();
					break;
				default:
					break;
			}
		} while (true);
	}
}
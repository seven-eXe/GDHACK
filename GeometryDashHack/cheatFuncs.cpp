#include "cheatFuncs.hpp"

struct stFuncStates {
	bool noclip;
	bool noMusicLimit;
	bool JumpHack;
	bool cheatPracticeMusicHack;
	bool cheatUnlockAllIcons;
	bool cheatPatchFuckingAc;
	bool cheatUnlockAllLevels;
	bool cheatShopHack;
	bool cheatUnlockSecretLvl;
} fs;

void cheatFuncNoclip() // seven.eXe
{
	fs.noclip = !fs.noclip;

	if (fs.noclip)
	{
		unsigned char hackValue[5] = { 0xE9, 0x79, 0x06, 0x00, 0x00 };
		WriteProcessMemory(INFO->hProcess, (void*)(INFO->baseAddress + GEOMETRY_TOUCH_OFFSET), (char*)hackValue, 5, NULL);
	}
	else
	{
		unsigned char oldValue[5] = { 0x6A, 0x14, 0x8B, 0xCB, 0xFF };
		WriteProcessMemory(INFO->hProcess, (void*)(INFO->baseAddress + GEOMETRY_TOUCH_OFFSET), (char*)oldValue, 5, NULL);
	}

	std::cout << "[+] Noclip state: " << fs.noclip << std::endl;
}

DWORD getLastPointer(DWORD sAddress, short oCount, DWORD* offsets)
{
	DWORD address;
	ReadProcessMemory(INFO->hProcess, (DWORD*)(INFO->baseAddress + sAddress), &address, sizeof(DWORD), 0);
	address += offsets[0];
	for (short i = 1; i < oCount; i++) {
		ReadProcessMemory(INFO->hProcess, (void*)&address, (void*)&address, sizeof(DWORD), 0);
		address += offsets[i];
	}
	return address;
}

void cheatFuncMusicHack() // Receiver
{
	DWORD offsets[5] = { 0x110, 0x20, 0x8, 0x0, 0x1C0 };
	DWORD address = getLastPointer(GEOMETRY_MUSIC_HACK_OFFSET, 5, offsets);

	int iMusic;
	ReadProcessMemory(INFO->hProcess, reinterpret_cast<void*>(&address), &iMusic, sizeof(int), NULL);

	std::cout << "[+] Current music index: " << std::dec << iMusic << std::endl;

	std::cout << "[/] Enter music index: ";
	std::cin >> iMusic;

	std::cout << "[+] New music index: " << iMusic << std::endl;

	iMusic = iMusic - 1;

	WriteProcessMemory(INFO->hProcess, (void*)address, &iMusic, sizeof(int), NULL);
}

char* cheatGetPlayerName() // Receiver
{
	int nameLenght;
	ReadProcessMemory(INFO->hProcess, (void*)(INFO->PlayerPTR + GEOMETRY_PLAYER_NAME_LENGHT_OFFSET), &nameLenght, sizeof(nameLenght), NULL);

	char* playerName = new char[nameLenght];
	ReadProcessMemory(INFO->hProcess, (void*)(INFO->PlayerPTR + GEOMETRY_PLAYER_NAME_OFFSET), playerName, nameLenght, NULL);

	return playerName;
}

void cheatFuncMusicLimit() // Receiver
{
	// GeometryDash.exe + 174404 - 83 F8 14              { 20 } // Current check
	// GeometryDash.exe+17440A - BE 16000000           { 22 } // Next
	// GeometryDash.exe + 174459 - BE 14000000           { 34 } // Back

	if (!fs.noMusicLimit) {
		unsigned char fValue[3] = { 0x83, 0xF8, 0x22 };
		unsigned char sValue[2] = { 0xBE, 0x22 };

		WriteProcessMemory(INFO->hProcess, (void*)(INFO->baseAddress + 0x174404), (char*)fValue, 3, NULL); // Current check
		WriteProcessMemory(INFO->hProcess, (void*)(INFO->baseAddress + 0x17440A), (char*)sValue, 2, NULL); // Next
		WriteProcessMemory(INFO->hProcess, (void*)(INFO->baseAddress + 0x174459), (char*)sValue, 2, NULL); // Back
	}
	else {
		unsigned char fValue[3] = { 0x83, 0xF8, 0x14 };
		unsigned char sValue[2] = { 0xBE, 0x14 };

		WriteProcessMemory(INFO->hProcess, (void*)(INFO->baseAddress + 0x174404), (char*)fValue, 3, NULL); // Current check
		WriteProcessMemory(INFO->hProcess, (void*)(INFO->baseAddress + 0x17440A), (char*)sValue, 2, NULL); // Next
		WriteProcessMemory(INFO->hProcess, (void*)(INFO->baseAddress + 0x174459), (char*)sValue, 2, NULL); // Back
	}
	fs.noMusicLimit = !fs.noMusicLimit;

	std::cout << "[+] DisableLimitMusic state: " << fs.noMusicLimit << std::endl;
}

void cheatFuncJumpHack() // seven.eXe
{
	fs.JumpHack = !fs.JumpHack;
	if (fs.JumpHack)
	{
		int jmHack = 1;
		WriteProcessMemory(INFO->hProcess, (void*)(INFO->baseAddress + GEOMETRY_JUMP_OFFSET), &jmHack, 1, NULL);
	}
	else
	{
		int jmOrig = 0;
		WriteProcessMemory(INFO->hProcess, (void*)(INFO->baseAddress + GEOMETRY_JUMP_OFFSET), &jmOrig, 1, NULL);
	}
	std::cout << "[+] JumpHack state: " << fs.JumpHack << std::endl;
}

void cheatFuncPracticeMusicHack() // seven.eXe
{
	fs.cheatPracticeMusicHack = !fs.cheatPracticeMusicHack;
	if (fs.cheatPracticeMusicHack)
	{
		unsigned char hackValue[6] = { 0x90, 0x90, 0x90, 0x90, 0x90, 0x90 };
		unsigned char hackValue2[2] = { 0x90, 0x90 };
		WriteProcessMemory(INFO->hProcess, (LPVOID)(INFO->baseAddress + GEOMETRY_PRACTICE_MUSIC_OFFSET_1), (char*)hackValue, 6, NULL);
		WriteProcessMemory(INFO->hProcess, (LPVOID)(INFO->baseAddress + GEOMETRY_PRACTICE_MUSIC_OFFSET_2), (char*)hackValue2, 2, NULL);
		WriteProcessMemory(INFO->hProcess, (LPVOID)(INFO->baseAddress + GEOMETRY_PRACTICE_MUSIC_OFFSET_3), (char*)hackValue2, 2, NULL);
		WriteProcessMemory(INFO->hProcess, (LPVOID)(INFO->baseAddress + GEOMETRY_PRACTICE_MUSIC_OFFSET_4), (char*)hackValue2, 2, NULL);
	}
	else
	{
		unsigned char oldValue[6] = { 0x0F, 0x85, 0xF7, 0x00, 0x00, 0x00 };
		unsigned char oldValue2[2] = { 0x75, 0x41 };
		unsigned char oldValue3[2] = { 0x75, 0x3E };
		unsigned char oldValue4[2] = { 0x75, 0x0C };
		WriteProcessMemory(INFO->hProcess, (LPVOID)(INFO->baseAddress + GEOMETRY_PRACTICE_MUSIC_OFFSET_1), (char*)oldValue, 6, NULL);
		WriteProcessMemory(INFO->hProcess, (LPVOID)(INFO->baseAddress + GEOMETRY_PRACTICE_MUSIC_OFFSET_2), (char*)oldValue2, 2, NULL);
		WriteProcessMemory(INFO->hProcess, (LPVOID)(INFO->baseAddress + GEOMETRY_PRACTICE_MUSIC_OFFSET_3), (char*)oldValue3, 2, NULL);
		WriteProcessMemory(INFO->hProcess, (LPVOID)(INFO->baseAddress + GEOMETRY_PRACTICE_MUSIC_OFFSET_4), (char*)oldValue4, 2, NULL);
	}

	std::cout << "[+] Practice music hack state: " << fs.cheatPracticeMusicHack << std::endl;
}

void cheatFuncUnlockAllIcons() // seven.eXe
{
	fs.cheatUnlockAllIcons = !fs.cheatUnlockAllIcons;

	if (fs.cheatUnlockAllIcons)
	{
		unsigned char hackValue[5] = { 0xB0, 0x01, 0x90, 0x90, 0x90 };
		WriteProcessMemory(INFO->hProcess, (LPVOID)(INFO->baseAddress + GEOMETRY_ICONS_OFFSET), (char*)hackValue, 5, NULL);
	}
	else
	{
		unsigned char oldValue[5] = { 0xE8, 0x7A, 0xCD, 0x19, 0x00 };
		WriteProcessMemory(INFO->hProcess, (LPVOID)(INFO->baseAddress + GEOMETRY_ICONS_OFFSET), (char*)oldValue, 5, NULL);
	}

	std::cout << "[+] Unlock all icons state: " << fs.cheatUnlockAllIcons << std::endl;
}

void cheatFuncPatchFuckingAnticheat() // seven.eXe
{
	fs.cheatPatchFuckingAc = !fs.cheatPatchFuckingAc;

	if (fs.cheatPatchFuckingAc)
	{
		unsigned char speedHackValue[2] = { 0xEB, 0x2E };
		unsigned char resetHackValue[6] = { 0xE9, 0xD7, 0x00, 0x00, 0x00, 0x90 };
		unsigned char loadHackValue[2] = { 0xB0, 0x01 };

		unsigned char kickHackValue[5] = { 0x90, 0x90, 0x90, 0x90, 0x90 };
		unsigned char kickHackValue2[2] = { 0x90, 0x90 };

		BYTE lvlCompHackValue[2] = { 0xEB, 0x0C };
		unsigned char lvlCompHackValue2[26] = { 0xC7, 0x87, 0xE0, 0x02, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0xC7, 0x87, 0xE4, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90 };
		unsigned char lvlCompHackValue3[6] = { 0x90, 0x90, 0x90, 0x90, 0x90, 0x90 };

		WriteProcessMemory(INFO->hProcess, (LPVOID)(INFO->baseAddress + GEOMETRY_PATCH_SPEEDHACK_AC), (BYTE*)speedHackValue, 2, NULL);
		WriteProcessMemory(INFO->hProcess, (LPVOID)(INFO->baseAddress + GEOMETRY_PATCH_RESET_AC), (char*)resetHackValue, 6, NULL);
		WriteProcessMemory(INFO->hProcess, (LPVOID)(INFO->baseAddress + GEOMETRY_PATCH_LOAD_LEVEL_AC), (char*)loadHackValue, 2, NULL);

		WriteProcessMemory(INFO->hProcess, (LPVOID)(INFO->baseAddress + GEOMETRY_PATCH_LEVEL_KICK_AC), (char*)kickHackValue, 5, NULL);
		WriteProcessMemory(INFO->hProcess, (LPVOID)(INFO->baseAddress + GEOMETRY_PATCH_LEVEL_KICK_AC_1), (char*)kickHackValue2, 2, NULL);

		WriteProcessMemory(INFO->hProcess, (LPVOID)(INFO->baseAddress + GEOMETRY_PATCH_LEVEL_COMP_AC), (char*)lvlCompHackValue, 2, NULL);
		WriteProcessMemory(INFO->hProcess, (LPVOID)(INFO->baseAddress + GEOMETRY_PATCH_LEVEL_COMP_AC_2), (char*)lvlCompHackValue2, 26, NULL);
		WriteProcessMemory(INFO->hProcess, (LPVOID)(INFO->baseAddress + GEOMETRY_PATCH_LEVEL_COMP_AC_3), (char*)lvlCompHackValue3, 6, NULL);
		WriteProcessMemory(INFO->hProcess, (LPVOID)(INFO->baseAddress + GEOMETRY_PATCH_LEVEL_COMP_AC_4), (char*)lvlCompHackValue3, 6, NULL);
		WriteProcessMemory(INFO->hProcess, (LPVOID)(INFO->baseAddress + GEOMETRY_PATCH_LEVEL_COMP_AC_5), (char*)lvlCompHackValue3, 6, NULL);
	}
	else
	{
		unsigned char speedOldValue[2] = { 0x74, 0x2E };
		unsigned char resetOldValue[6] = { 0x0F, 0x85, 0xD6, 0x00, 0x00, 0x00 };
		unsigned char loadOldValue[2] = { 0x88, 0xD8 };

		unsigned char kickOldValue[5] = { 0xE8, 0x58, 0x04, 0x00, 0x00 };
		unsigned char kickOldValue2[2] = { 0x74, 0x6E };

		unsigned char lvlCompOldValue[2] = { 0x74, 0x0C };
		unsigned char lvlCompOldValue2[26] = { 0x80, 0xBF, 0xDD, 0x02, 0x00, 0x00, 0x00, 0x0F, 0x85, 0x0A, 0xFE, 0xFF, 0xFF, 0x80, 0xBF, 0x34, 0x05, 0x00, 0x00, 0x00, 0x0F, 0x84, 0xFD, 0xFD, 0xFF, 0xFF };
		unsigned char lvlCompOldValue3[6] = { 0x0F, 0x84, 0xFD, 0xFD, 0xFF, 0xFF };
		unsigned char lvlCompOldValue4[6] = { 0x0F, 0x84, 0xB9, 0xFD, 0xFF, 0xFF };
		unsigned char lvlCompOldValue5[6] = { 0x0F, 0x84, 0xA4, 0xFD, 0xFF, 0xFF };

		WriteProcessMemory(INFO->hProcess, (LPVOID)(INFO->baseAddress + GEOMETRY_PATCH_SPEEDHACK_AC), (char*)speedOldValue, 2, NULL);
		WriteProcessMemory(INFO->hProcess, (LPVOID)(INFO->baseAddress + GEOMETRY_PATCH_RESET_AC), (char*)resetOldValue, 6, NULL);
		WriteProcessMemory(INFO->hProcess, (LPVOID)(INFO->baseAddress + GEOMETRY_PATCH_LOAD_LEVEL_AC), (char*)loadOldValue, 2, NULL);

		WriteProcessMemory(INFO->hProcess, (LPVOID)(INFO->baseAddress + GEOMETRY_PATCH_LEVEL_KICK_AC), (char*)kickOldValue, 5, NULL);
		WriteProcessMemory(INFO->hProcess, (LPVOID)(INFO->baseAddress + GEOMETRY_PATCH_LEVEL_KICK_AC_1), (char*)kickOldValue2, 2, NULL);

		WriteProcessMemory(INFO->hProcess, (LPVOID)(INFO->baseAddress + GEOMETRY_PATCH_LEVEL_COMP_AC), (char*)lvlCompOldValue, 2, NULL);
		WriteProcessMemory(INFO->hProcess, (LPVOID)(INFO->baseAddress + GEOMETRY_PATCH_LEVEL_COMP_AC_2), (char*)lvlCompOldValue2, 26, NULL);
		WriteProcessMemory(INFO->hProcess, (LPVOID)(INFO->baseAddress + GEOMETRY_PATCH_LEVEL_COMP_AC_3), (char*)lvlCompOldValue3, 6, NULL);
		WriteProcessMemory(INFO->hProcess, (LPVOID)(INFO->baseAddress + GEOMETRY_PATCH_LEVEL_COMP_AC_4), (char*)lvlCompOldValue4, 6, NULL);
		WriteProcessMemory(INFO->hProcess, (LPVOID)(INFO->baseAddress + GEOMETRY_PATCH_LEVEL_COMP_AC_5), (char*)lvlCompOldValue5, 6, NULL);
	}

	std::cout << "[+] Anticheat patch: " << fs.cheatPatchFuckingAc << std::endl;
}

void cheatFuncUnlockAllLevels() // seven.eXe
{
	fs.cheatUnlockAllLevels = !fs.cheatUnlockAllLevels;

	if (fs.cheatUnlockAllLevels)
	{
		unsigned char hackValue[6] = { 0xE9, 0x8A, 0x00, 0x00, 0x00, 0x90 };
		WriteProcessMemory(INFO->hProcess, (LPVOID)(INFO->baseAddress + GEOMETRY_UNLOCK_LEVELS_OFFSET), (char*)hackValue, 6, NULL);
	}
	else
	{
		unsigned char oldValue[6] = { 0x0F, 0x8E, 0x89, 0x00, 0x00, 0x00 };
		WriteProcessMemory(INFO->hProcess, (LPVOID)(INFO->baseAddress + GEOMETRY_UNLOCK_LEVELS_OFFSET), (char*)oldValue, 6, NULL);
	}

	std::cout << "[+] Unlock all levels state: " << fs.cheatUnlockAllLevels << std::endl;
}

void cheatFuncShopHack()
{
	fs.cheatShopHack = !fs.cheatShopHack;

	if (fs.cheatShopHack)
	{
		unsigned char hackValue[6] = { 0x8B, 0x93, 0x10, 0x01, 0x00, 0x00 };
		unsigned char hackValue2[6] = { 0x2B, 0xB3, 0x10, 0x01, 0x00, 0x00 };

		WriteProcessMemory(INFO->hProcess, (LPVOID)(INFO->baseAddress + GEOMETRY_SHOPHACK_1_OFFSET), (char*)hackValue, 6, NULL);
		WriteProcessMemory(INFO->hProcess, (LPVOID)(INFO->baseAddress + GEOMETRY_SHOPHACK_2_OFFSET), (char*)hackValue2, 6, NULL);
	}
	else
	{
		unsigned char oldValue[6] = { 0x8B, 0x93, 0x14, 0x01, 0x00, 0x00 };
		unsigned char oldValue2[6] = { 0x2B, 0xB3, 0x14, 0x01, 0x00, 0x00 };

		WriteProcessMemory(INFO->hProcess, (LPVOID)(INFO->baseAddress + GEOMETRY_SHOPHACK_1_OFFSET), (char*)oldValue, 6, NULL);
		WriteProcessMemory(INFO->hProcess, (LPVOID)(INFO->baseAddress + GEOMETRY_SHOPHACK_2_OFFSET), (char*)oldValue2, 6, NULL);
	}

	std::cout << "[+] ShopHack state: " << fs.cheatShopHack << std::endl;
}

void cheatFuncUnlockSecretLvl()
{
	fs.cheatUnlockSecretLvl = !fs.cheatUnlockSecretLvl;

	if (fs.cheatUnlockSecretLvl)
	{
		unsigned char hackValue[6] = { 0x90, 0x90, 0x90, 0x90, 0x90, 0x90 };
		WriteProcessMemory(INFO->hProcess, (LPVOID)(INFO->baseAddress + GEOMETRY_SECRET_LVL_OFFSET), (char*)hackValue, 6, NULL);
	}
	else
	{
		unsigned char oldValue[6] = { 0x0F, 0x84, 0x87, 0x00, 0x00, 0x00 };
		WriteProcessMemory(INFO->hProcess, (LPVOID)(INFO->baseAddress + GEOMETRY_SECRET_LVL_OFFSET), (char*)oldValue, 6, NULL);
	}

	std::cout << "[+] Unlock secret lvl state: " << fs.cheatUnlockSecretLvl << std::endl;
}
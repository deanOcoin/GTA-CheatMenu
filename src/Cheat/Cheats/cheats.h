#pragma once
#include "structs.h"
#include "cheatconfig.h"

const auto BASE = (uintptr_t)GetModuleHandleW(L"GTA5.exe");
static CPedFactory* PedFactory = *(CPedFactory**)(BASE + 0x266C868);

// static vars (non writable)
static bool* isInVehicle = (bool*)(BASE + 0x1DF3220);

class Cheats
{
public:
	void NeverWanted(bool tog);
	void InfAmmo(bool tog);
	void CheckUpdate();
};



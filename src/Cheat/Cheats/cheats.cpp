#include "cheats.h"

DWORD c_OldProtect = 0;
void Cheats::NeverWanted(bool tog)
{
	// reset wanted to 0 before patching
	PedFactory->Ped->PlayerInfo->WantedLevel = 0;

	uint32_t WantedAddresses[5] = { 0x65B74B, 0x65B71F, 0x65B6E5, 0x65B6B9, 0x65B689 };
	switch (tog)
	{
	case 1: // on
		for (uint8_t i = 0; i < 5; i++)
		{
			Mem::NOP((void*)(BASE + WantedAddresses[i]), 10, c_OldProtect);
		}
		break;
	case 0: // off
		for (uint8_t i = 0; i < 5; i++)
		{
			Mem::Patch((void*)(BASE + WantedAddresses[i]), { 0xC7, 0x83, 0xB8, 0x00, 0x00, 0x00, (uint8_t)(i + 1), 0x00, 0x00, 0x00 }, c_OldProtect);
		}
		break;
	}
}

void Cheats::InfAmmo(bool tog) // fix wont turn off
{
	switch (tog)
	{
	case 1:
		Mem::NOP((void*)(BASE + 0x10404C5), 3, c_OldProtect);
		break;
	case 0:
		Mem::Patch((void*)(BASE + 0x10404C5), { 0x89, 0x5F, 0x20 }, c_OldProtect);
		break;
	}
}

void Cheats::CheckUpdate() // cheat loop
{
	static bool INWtog = 0;
	static bool IIAtog = 0;
	static bool OSKtog = 0;
	static bool NRPtog = 0;

	// 
	static float originaldamage;
	static float ogac;
	static float ogex;

	// Never Wanted
	if (Config::isNeverWanted && !INWtog)
	{
		Cheats::NeverWanted(1);
		INWtog = 1;
	}
	else if (!Config::isNeverWanted && INWtog)
	{
		Cheats::NeverWanted(0);
		INWtog = 0;
	}

	// Infinite Ammo
	if (Config::isInfAmmo && !IIAtog)
	{
		Cheats::InfAmmo(1);
		IIAtog = 1;
	}
	else if (!Config::isInfAmmo && IIAtog)
	{
		Cheats::InfAmmo(0);
		IIAtog = 0;
	}

	// One Shot Kill
	if (Config::isOSK)
	{
		if (PedFactory->Ped->WeaponManager->WeaponInfo->weapon_damage != 500.0)
			originaldamage = PedFactory->Ped->WeaponManager->WeaponInfo->weapon_damage;
	}

	if (Config::isOSK)
	{
		PedFactory->Ped->WeaponManager->WeaponInfo->weapon_damage = 500.0;
		OSKtog = 1;
	}
	else if (!Config::isOSK && OSKtog)
	{
		PedFactory->Ped->WeaponManager->WeaponInfo->weapon_damage = originaldamage;
		OSKtog = 0;
	}

	// NoRecoil Pro
	if (Config::isNRP)
	{
		if (PedFactory->Ped->WeaponManager->WeaponInfo->accuracy_spread != 0.0 &&
			PedFactory->Ped->WeaponManager->WeaponInfo->explosion_shake_amplitude != 0.0)
		{
			ogac = PedFactory->Ped->WeaponManager->WeaponInfo->accuracy_spread;
			ogex = PedFactory->Ped->WeaponManager->WeaponInfo->explosion_shake_amplitude;
		}
	}

	if (Config::isNRP)
	{
		PedFactory->Ped->WeaponManager->WeaponInfo->accuracy_spread = 0.0;
		PedFactory->Ped->WeaponManager->WeaponInfo->explosion_shake_amplitude = 0.0;
		NRPtog = 1;
	}
	else if (!Config::isNRP && NRPtog)
	{
		PedFactory->Ped->WeaponManager->WeaponInfo->accuracy_spread = ogac;
		PedFactory->Ped->WeaponManager->WeaponInfo->explosion_shake_amplitude = ogex;
		NRPtog = 0;
	}

	// Vehicle Speed
	if (Config::tGrav != 1.0 && PedFactory->Ped->Vehicle != nullptr && *(bool*)isInVehicle)
	{
		PedFactory->Ped->Vehicle->gravity = (Config::tGrav * 10.0);
	}

	// 0 Gravity
	if (Config::isZeroGrav && *(bool*)isInVehicle)
	{
		Config::tGrav = 1.0; // reset gravity multiplier first
		PedFactory->Ped->Vehicle->gravity = 0;
	}


}
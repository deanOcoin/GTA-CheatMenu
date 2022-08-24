#pragma once
#include "Windows.h"
#include "memory.h"

enum class eDamageType : int32_t
{
	_0xA869C908 = 7,
	_0xC5403EC0 = 4,
	_0xCAE075C0 = 9,
	BarbedWire = 11,
	Bullet = 3,
	Electric = 10,
	Explosive = 5,
	Fall = 8,
	Fire = 6,
	FireExtinguisher = 12,
	Melee = 2,
	None = 1,
	Smoke = 13,
	Unknown = 0,
	WaterCannon = 14
};

class CPedFactory
{
public:
	char pad_0000[8]; //0x0000
	class CPed* Ped; //0x0008
};

class CPed
{
public:
	char pad_0000[393]; //0x0000
	bool Godmode; //0x0189
	char pad_018A[246]; //0x018A
	float Health; //0x0280
	char pad_0284[2732]; //0x0284
	class CAutoMobile* Vehicle; //0x0D30
	char pad_0D38[912]; //0x0D38
	class mPlayerInfo* PlayerInfo; //0x10C8
	char pad_10D0[8]; //0x10D0
	class CPedWeaponManager* WeaponManager; //0x10D8
};

class mPlayerInfo
{
public:
	char pad_0000[164]; //0x0000
	char PlayerName[23]; //0x00A4
	char pad_00BB[181]; //0x00BB
	float swim_speed; //0x0170
	char pad_0174[1812]; //0x0174
	int32_t WantedLevel; //0x0888
	char pad_088C[1124]; //0x088C
	float MovSpeedX; //0x0CF0
	char pad_0CF4[228]; //0x0CF4
};

class CAutoMobile
{
public:
	char pad_0000[792]; //0x0000
	uint8_t boost_state; //0x0318
	char pad_0319[1319]; //0x0319
	float vhealth; //0x0840
	char pad_0844[244]; //0x0844
	class CHandlingData* Handling; //0x0938
	char pad_0940[2]; //0x0940
	uint8_t isDrivable; //0x0942
	uint8_t canTiresBurst; //0x0943
	char pad_0944[792]; //0x0944
	float gravity; //0x0C5C
	char pad_0C60[8]; //0x0C60
	class CPed* Driver; //0x0C68
	class CPed(*Passengers)[1]; //0x0C70
	char pad_0C78[908]; //0x0C78
};

class CHandlingData
{
	
};

class CPedWeaponManager
{
public:
	char pad_0000[24]; //0x0000
	int64_t selected_weapon_hash; //0x0018
	class CWeaponInfo* WeaponInfo; //0x0020
};

class CWeaponInfo
{
public:
	char pad_0000[32]; //0x0000
	int32_t ignore_int; //0x0020
	char pad_0024[76]; //0x0024
	int32_t clip_size; //0x0070
	float accuracy_spread; //0x0074
	char pad_0078[20]; //0x0078
	float recoil_recovery_rate; //0x008C
	char pad_0090[32]; //0x0090
	float weapon_damage; //0x00B0
	char pad_00B4[20]; //0x00B4
	float limb_damage_modifier; //0x00C8
	char pad_00CC[80]; //0x00CC
	float speed; //0x11C
	char pad_01E8[468]; //0x1E8
	float explosion_shake_amplitude; //0x02F4
};
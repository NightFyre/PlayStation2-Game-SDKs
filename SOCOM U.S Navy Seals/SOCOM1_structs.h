#pragma once

/**
 * Name: PlayStation2 - PCSX2 :: SOCOM U.S NAVY SEALs
 * Version: 0.0.1
 * Author: NightFyre
*/

#pragma pack(push, 0x01)
namespace PlayStation2
{
	namespace SOCOM
	{
		enum EWeaponSlot : uint32_t
		{
			Primary,		// = 0x60C,
			Secondary,		// = 0x610,
			EqSlot1,		// = 0x614,
			EqSlot2,		// = 0x618,
			EqSlot3,		// = 0x61C,
		};
		/*
			static const char* AvailSlots[5] = 
			{ 
				"Primary", 
				"Secondary", 
				"Equipment 1", 
				"Equipment 2", 
				"Equipment 3" 
			};
		*/


		/*
		* KEY:
			- P = Primary
			- S = Secondary
			- EQ = Equipment
		*/
		enum class EWeapon : __int32
		{
			// Assault Rifles
			EWeapon_P_AR_M4A1_M203			= 0xCC4270,
			EWeapon_P_AR_M4A1_SD			= 0xCC3F80,
			EWeapon_P_AR_M16A2				= 0xCC36E0,
			EWeapon_P_AR_M16_M203			= 0xCC39C0,
			EWeapon_P_AR_552				= 0xCC4550,
			EWeapon_P_AR_AK74				= 0xCC4850,
			EWeapon_P_AR_AKS74				= 0xCC4B20,
			
			//	
			EWeapon_P_SMG_9MM				= 0xCC61F0,
			EWeapon_P_SMG_HK5				= 0xCC5970,
			EWeapon_P_SMG_HK5_SD			= 0xCC5C40, 
			
			//	
			EWeapon_P_SNIPER_M40A1			= 0xCC67A0,

			//	
			EWeapon_S_PISTOL_9MM			= 0xCC22D0,
			EWeapon_S_PISTOL_9MM_SD			= 0xCC2B60,
			EWeapon_S_PISTOL_MK23			= 0xCC1A10,
			EWeapon_S_PISTOL_MK23_SD		= 0xCC2880,
			EWeapon_S_PISTOL_226			= 0xCC25B0,
			EWeapon_S_PISTOL_F57			= 0xCC1CF0,
			EWeapon_S_PISTOL_DE50			= 0xCC1FD0,

			//	
			EWeapon_EQ_Flashbang			= 0xCC8A60,
			EWeapon_EQ_C4					= 0xCC9300,
			EWeapon_EQ_Claymore				= 0xCC9030,
			EWeapon_EQ_Satchel				= 0xCC8D50,
			EWeapon_EQ_M67					= 0xCC81A0,
			EWeapon_EQ_HE					= 0xCC8490,
			EWeapon_EQ_Smoke				= 0xCC8760,
			EWeapon_EQ_AMMOx2				= 0xCCB800,
			EWeapon_EQ_M203_HE				= 0xCC9B50,
			EWeapon_EQ_M203_FRAG			= 0xCC9E30,
			EWeapon_EQ_M203_SMOKE			= 0xCCA120,
		};
		const char* GetWeaponName(EWeapon weapon);
		/*
			static const char* PrimaryWeapons[4] =
			{
				"M4A1 SD",						//	0
				"552", 							//	1
				"9mm Sub",						//	2
				"abs" 							//	3
			};
			static const char* SecondaryWeapons[5] =
			{
				"9MM Pistol",					//	0
				"abs", 							//	1
				"abs2", 						//	2
				"abs3", 						//	3
				"abs4" 							//	4
			};
			static const char* EquipmentWeapons[1] =
			{
				"Flashbang"						//	0
			};
		*/

		enum class EAmmoType : unsigned __int32
		{
			EAmmoType_556x45_SD				= 0xCC0ED0,			//	M4A1_SD , 
			EAmmoType_556x45				= 0xCC0F40,			//	M4A1, M16A2, 552 , 
			EAmmoType_762x39				= 0xCC1050,			//	AK47 , 
			EAmmoType_545x39				= 0xCC0E60,			//	AKS74
			EAmmoType_9x19p					= 0xCC0C90,			//	SMG_HK5, SMG_9MM, PISTOL_MODEL_18, PISTOL_9MM
			EAmmoType_9x19p_SD				= 0xCC0CD0,			//	SMG_HK5_SD, PISTOL_9MM_SD
			EAmmoType_45ACP					= 0xCC0DC0,			//	PISTOL_MK23
			EAmmoType_762x51				= 0xCC0F90,			//	M40A1 , 
			EAmmoType_50AE					= 0xCC0E10,			//	DE50 , 
			EAmmoType_57x28					= 0xCC0D20,			//	F57
			EAmmoType_2xAmmo				= 0x0,
			EAmmoType_Satchel				= 0xCC12C0,
			EAmmoType_Smoke					= 0xCC1210,
			EAmmoType_Claymore				= 0xCC1320,
			EAmmoType_C4					= 0xCC1380,
			EAmmoType_M203_HE				= 0xCC1420,
			EAmmoType_M203_FRAG				= 0xCC1490,
			EAmmoType_M203_SMOKE			= 0xCC1500,
		};
		const char* GetAmmoTypeName(EAmmoType weapon);
		/* 
			static const char* AmmoTypes[1] =
			{
				"NULL"							//	0
			};
		*/

		enum class EFireType : unsigned __int32
		{
			//	Single, Burst, Auto, SecondaryWeapon, EqSlot1, EqSlot2, EqSlot3
			EFireType_Single = 1,				//	
			EFireType_Burst = 2,				//	
			EFireType_Auto = 3,					//	
			EFireType_SecondaryWeapon = 4,		//	
			EFireType_EqSlot1 = 5, 				//	
			EFireType_EqSlot2 = 6,				//	
			EFireType_EqSlot3 = 7				//	
		};
		const char* GetFireTypeName(EAmmoType weapon);
		/*
			enum EPrimaryWeapon : uint32_t
			{
				AR_M4A1_SD	= 0xCC3F80,			
				AR_552		= 0xCC4550,			
				AR_AK74		= 0xCC4850,
				SMG_9MM		= 0x00CC61F0,
				SMG_HK5		= 0xCC5970,
				SMG_HK5_SD	= 0xCC5C40,
				abs1		= 0xCC6D90,			
			};

			enum ESecondaryWeapon : uint32_t
			{
				PISTOL_9MM	= 0xCC2B60,		
				PISTOL	= 0xCC2880,
				_abs		= 13402528,		
				_abs2		= 13401072,		
				_abs3		= 13395872,		
				_abs4		= 13377488,		
			};

			enum EEquipment : uint32_t
			{
				Flashbang = 0x0,
				EEquipment_Satchel	= 0xCC8D50,	//	satchel, flash, grenade
				EEquipment_M67		= 0xCC81A0,	//	
				EEquipment_FlashBang = 0xCC8A60	//	
			};
		*/

		enum class ETeam : unsigned __int32
		{
			SEALS		= 0x40000001,		//	Seal
			TERRORIST	= 0x80000100,		//	Terrorist
			TURRET		= 0x48000000,		//	Turret
			SPECTATOR	= 0x00010000,		//	Spectator

			// CAMPAIGN
			SP_ABLE		= 0x84000006,		//	Alpha Team
			SP_BRAVO	= 0x8400000A,		//	Bravo Team
			SP_ENEMY_A	= 0x40000050,		//	Iron Brother / Iron Leader
			SP_ENEMY_B	= 0x40000100,		//	
			SP_ENEMY_C	= 0x40000210,		//	
			SP_ENEMY_D	= 0x40000410,		//	
			SP_ENEMY_E	= 0x40000810,		//	
			SP_ENEMY_F	= 0x40001010,		//	
			SP_ENEMY_G	= 0x40002010,		//	
			SP_ENEMY_H	= 0x40004010,		//	
			SP_ENEMY_I	= 0x40021010,		//	
			NONE		= 0
		};
		const char* GetTeamName(ETeam team);
		/*
		
			static const char* TeamNames[5] =
			{
				"SEALS",			//	0
				"TERRORISTS",		//	1
				"SPECTATOR",		//	2
				"ABLE",				//	3
				"BRAVO",			//	4
			};
		*/
		
		enum class EMap : unsigned __int32
		{

		};
		const char* GetMapName(EMap map);
		/*
			static const char* MapNames[1] =
			{
				"NULL"
			};
		*/

		enum class EPlayerViewState : __int8
		{

		};

		enum class ECameraViewState : __int8
		{

		};


		//	
		template<typename Z>
		struct ZArrayIterator
		{
		private:
			__int32 _next;		//	might be start	??
			__int32 _prev;		//	first object in the array will point to the start.
			__int32 _data;		//	Z
		
		public:
			
			ZArrayIterator()
			{
				_next = 0;
				_prev = 0;
				_data = 0;
			}
			
			ZArrayIterator(__int32 next, __int32 prev, __int32 data)
			{
				_next = next;
				_prev = prev;
				_data = data;
			}

			Z Data() const { return reinterpret_cast<Z>(PS2Memory::GetModuleBase() + _data); }
			ZArrayIterator<Z> Next() const { return PS2Memory::ReadShort<ZArrayIterator<Z>>(_next); }
			ZArrayIterator<Z> Prev() const { return PS2Memory::ReadShort<ZArrayIterator<Z>>(_prev); }
		};

		template<typename Z>
		struct ZArray
		{
		private:
			__int32 _count;
			__int32 _begin;
			__int32 _end;
		
		public:
			ZArray()
			{
				_count = 0;
				_begin = 0;
				_end = 0;
			}

			ZArray(__int32 count, __int32 begin, __int32 end)
			{
				_count = count;
				_begin = begin;
				_end = end;
			}

			int Count() const { return _count; }
			bool IsValid() const { return false; }	//	check if count > 0 && if _begin & _end are <= 0
			ZArrayIterator<Z> GetIterator() const
			{
				return PS2Memory::ReadShort<ZArrayIterator<Z>>(_begin);
			}

			std::vector<Z> Data() const
			{
				std::vector<Z> result;

				if (_count > 0)
				{
					ZArrayIterator<Z> it = GetIterator();
					ZArrayIterator<Z> end = it.Prev();
					
					do
					{
						Z data = it.Data();

						if (data > 0)
							result.push_back(data);

						it = it.Next();

					} while (it.Data() != end.Data());
				}

				return result;
			}
		};
	}

}
#pragma pack(pop)
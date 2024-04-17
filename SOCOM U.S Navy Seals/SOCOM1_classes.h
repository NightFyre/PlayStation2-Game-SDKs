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
		namespace Offsets
		{
			//	MatchData
			static const unsigned int	o_GameEndAddr{ 0x5D708C };
			static const unsigned int	o_GameForceMatch{ 0x1F66F4 };

			//	Seal
			static const unsigned int	o_LocalCamera{ 0x48D548 };
			static const unsigned int	o_LocalSeal{ 0x48D548 };
			static const unsigned int	o_SealArray{ 0x4D46A0 };

			//	Visuals
			static const unsigned int	o_fog{ 0x1E5AC0 };
			static const unsigned int	o_fps1{ 0x48CF60 };
			static const unsigned int	o_fps2{ 0x48CF64 };
		}

		class CZCamera
		{
		private:
			char							pad_0000[80];			//0x0000
			Vector3							m_relativePosition;		//0x0050	
			unsigned int					m_viewType;				//0x005C	//	0 = normal view : 2+ = zoom of sorts

		public:
			static CZCamera*				GetDefaultInstance();
			Vector3							GetPosition();
		};

		class CZSealObject
		{
		private:
			char							pad_0000[48];	//0x0000
			Vector3							m_absPosition;	//0x0030
			char							pad_003C[96];	//0x003C
			float							m_selfVisible;	//0x009C	//	255 = visible : 0 = invisible

		public:
			static CZSealObject*			GetDefaultInstance();
			Vector3							GetPosition();
			void							SetPosition(Vector3 in);

		};	//Size: 0x0100
		
		class CSealCtrl
		{
		private:
			char pad_0000[384];	//0x0000
		};	//Size: 0x0180

		class CZSeal
		{
		private:
			char							pad_0000[20];				//0x0000
			__int32							m_pName;					//0x0014
			char							pad_0018[4];				//0x0018
			Vector3							m_relativeLocation;			//0x001C
			__int32							m_pSealObj;					//0x0028	//	CZSealObject
			char							pad_002C[148];				//0x002C
			__int32							m_pSealCtrl;				//0x00C0	//	CSealCtrl
			ETeam							m_teamID;					//0x00C4
			char							pad_00C8[152];				//0x00C8
			__int8							m_zoomPos;					//0x0160
			char							pad_0161[3];				//0x0161
			float							m_fZoom;					//0x0164
			char							pad_0168[704];				//0x0168
			Vector3							m_relativeRotation;			//0x0428
			char							pad_0434[168];				//0x0434
			__int32							m_totalShotsFired;			//0x04DC
			char							pad_04E0[48];				//0x04E0
			__int32							m_totalShotsFired2;			//0x0510
			char							pad_0514[56];				//0x0514
			float							m_xhairBounce;				//0x054C
			char							pad_0550[188];				//0x0550
			__int32							m_PrimaryWeapon;			//0x060C
			__int32							m_SecondaryWeapon;			//0x0610
			__int32							m_EqSlot1;					//0x0614
			__int32							m_EqSlot2;					//0x0618
			__int32							m_EqSlot3;					//0x061C
			char							pad_0620[100];				//0x0620
			__int32							m_PrimaryAmmoType;			//0x0684
			__int32							m_SecondaryAmmoType;		//0x0688
			__int32							m_EqSlot1AmmoType;			//0x068C
			__int32							m_EqSlot2AmmoType;			//0x0690
			__int32							m_EqSlot3AmmoType;			//0x0694
			char							pad_0698[100];				//0x0698
			__int32							m_PrimaryMags[10];			//0x06FC
			__int32							m_SecondaryMags[10];		//0x0724
			__int32							m_EqSlot1Ammo;				//0x074C
			char							pad_0750[36];				//0x0750
			__int32							m_EqSlot2Ammo;				//0x0774
			char							pad_0778[36];				//0x0778
			__int32							m_EqSlot3Ammo;				//0x079C
			char							pad_07A0[1156];				//0x07A0
			EFireType						m_primaryFireType;			//0x0C24
			EFireType						m_secondaryFireType;		//0x0C28
			char							pad_0C2C[272];				//0x0C2C
			__int32							m_curShotsFired;			//0x0D3C
			float							m_fireCooldown;				//0x0D40
			char							pad_0D44[84];				//0x0D44
			__int32							m_totalShotsFired3;			//0x0D98
			char							pad_0D9C[108];				//0x0D9C
			__int32							m_gunHot;					//0x0E08
			char							pad_0E0C[120];				//0x0E0C
			__int32							m_gunHot2;					//0x0E84
			char							pad_0E88[72];				//0x0E88
			float							m_Health;					//0x0ED0
			char							pad_0ED4[1180];				//0x0ED4

		public:
			static CZSeal*					GetDefaultInstance();
			bool							IsValid();
			CZSealObject*					GetSealObject();
			Vector3							GetPosition();
			bool							SetPosition(Vector3 in);
			std::string						GetName();
			ETeam							GetTeam();
			float							GetHealth();
			bool							IsAlive();
		};	//Size: 0x1370
		
		class CZMatchData
		{
			
			
			//	- ForceHost
			//	- ForceStartMatch
			//	- ForceEndMatch
			//	- MatchNeverEnds
			//	- PlayerArray
			//	- GetLobbyInfo	| RoomName, MapName, Mode, #Players(Organized by team), Rounds Won/Current Round/Timer
		
		
			// NOTES
			// Host
			// - Force Start
			// - 
			// Match Info
			// - Map
			// - Round
			// - Time
			// - Players
			// - Score

			// SUB CLASSES
		public:

			//	OFFSETS
		public:
			//	const char*						roomName;
			//	const char*						currentMap;
			//	float							matchTime;
			//	int32_t							num_players;
			//	int32_t							num_alivePlayers;
			//	int32_t							num_spectators;
			//	int32_t							num_ai;
			//	int32_t							num_teams;
			//	int32_t							num_currentRound;
			//	class CZSealBody*				Host;
			//	class CZSealBody*				localPlayer;

			//	FUNCTIONS
		public:
			static bool						isMatchEnded();
			static void						ForceStartMatch();
			static bool						GetPlayers(std::vector<CZSeal*>* players);
		};

		///	@TODO:	
		/*

			class CZWeapon
			{

				//	- Core
				//	-- GiveAmmo
				//	-- GiveWeapon
				//	-- GetLoadoutData | Primary, Secondary, Equipment & Ammo
				//	
				//	- Systems
				//	-- Weapon Manager | Slot -> Type -> Weapon : Send



			public:
				EWeaponSlot						e_selectedSlot;
				EPrimaryWeapon					e_selected_Primary;
				ESecondaryWeapon				e_selected_Secondary;
				EEquipment						e_selected_Equipment;

			public:
				Vector3							GetBulletPos();
				void							SetBulletPos(Vector3 Pos);
				void							GiveWeapon();
				void							GiveAmmo();
				void							GetLoadoutData();
				std::string						LogData();
			};

			class CZSealBody
			{
			public:	// NATIVE OFFSETS (DO NOT DISRUPT)
				char							pad_0000[20];		//0x0000
				int								NamePTR;			//0x0014
				char							pad_0018[4];		//0x0018
				Vector3							Position;			//0x001C
				class CZSealObject* CPlayerMovement;	//0x0028
				char							pad_0030[148];		//0x0030
				int								TeamID;				//0x00C4
				char							pad_00C8[1348];		//0x00C8
				EPrimaryWeapon					PrimaryWeapon;		//0x060C
				ESecondaryWeapon				SecondaryWeapon;	//0x0610
				EEquipment						EqSlot1;			//0x0614
				EEquipment						EqSlot2;			//0x0618
				EEquipment						EqSlot3;			//0x061C
				char							pad_0620[220];		//0x0620
				int								PrimaryMag[10];		//0x06FC
				int								SecondaryMag[10];	//0x0724
				int								EquipmentSlot1;		//0x074C
				char							pad_0750[36];		//0x0750
				int								EquipmentSlot2;		//0x0774
				char							pad_0778[36];		//0x0778
				int								EquipmentSlot3;		//0x079C
				char							pad_07A0[1840];		//0x07A0
				float							Health;				//0x0ED0

				//	FUNCTIONS
			public:
				bool							IsValid();
				bool							IsAlive();
				class CZSealObject* PlayerPhysicsPtr();
				std::string						GetPlayerName();
				std::string						GetTeamName();
				std::string						GetWeaponName(unsigned int Weapon);
				void							GiveAmmo(int amount, int mags = {});
				void							GiveWeapon(unsigned int Slot, unsigned int Weapon);
				void							RemoveWeaponsandAmmo();
				void							Teleport(Vector3 Pos);
				void							ChangeTeams(ETeam newTeam);
				void							SetHealth(float newHealth);
				std::string						LogData();

			};	//Size: 0x0ED4

			

		*/
	}
}
#pragma pack(pop)
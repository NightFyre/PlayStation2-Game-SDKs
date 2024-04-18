#pragma once
#include "CDK.h"
#include "SOCOM1_package.h"

/**
 * Name: PlayStation2 - PCSX2 :: SOCOM U.S NAVY SEALs
 * Version: 1.0.0
 * Author: NightFyre
*/

#pragma pack(push, 0x01)
namespace PlayStation2
{
	namespace SOCOM
	{
		//----------------------------------------------------------------------------------------------------
		//										CCAMERA
		// - CCamera
		//-----------------------------------------------------------------------------------

		CZCamera* CZCamera::GetDefaultInstance()
		{
			if (Offsets::o_LocalCamera)
				return nullptr;

			return PS2Memory::GetPtrShort<CZCamera*>(Offsets::o_LocalCamera);
		}

		Vector3 CZCamera::GetPosition() { return this->m_relativePosition; }



		//----------------------------------------------------------------------------------------------------
		//										CZSealObject
		// - CPlayerPhysics
		//-----------------------------------------------------------------------------------

		CZSealObject* CZSealObject::GetDefaultInstance()
		{
			CZSeal* pLocalSeal =  CZSeal::GetDefaultInstance();

			if (!pLocalSeal)
				return nullptr;

			return pLocalSeal->GetSealObject();
		}

		Vector3 CZSealObject::GetPosition() { return this->m_absPosition; }

		void CZSealObject::SetPosition(Vector3 p) { this->m_absPosition = p; }


		//----------------------------------------------------------------------------------------------------
		//										CSealCtrl
		// - CPlayer
		//-----------------------------------------------------------------------------------


		//----------------------------------------------------------------------------------------------------
		//										CZSeal
		// - CPlayer
		//-----------------------------------------------------------------------------------

		CZSeal* CZSeal::GetDefaultInstance()
		{
			if (!Offsets::o_LocalSeal)
				return nullptr;

			return PS2Memory::GetPtrShort<CZSeal*>(Offsets::o_LocalSeal);
		}

		bool CZSeal::IsValid()
		{
			return (this->m_pName > 0 && this->m_pSealObj > 0 && this->m_teamID > ETeam::NONE);
		}

		CZSealObject* CZSeal::GetSealObject() { return PS2Memory::GetPtrShort<CZSealObject*>(this->m_pSealObj); }

		Vector3 CZSeal::GetPosition() { return this->m_relativeLocation; }

		bool CZSeal::SetPosition(Vector3 p)
		{
			CZSealObject* pObj = this->GetSealObject();
			if (!pObj)
				return false;

			pObj->SetPosition(p);

			return (pObj->GetPosition() == p);
		}

		std::string CZSeal::GetName()
		{
			if (!this->IsValid())
				return "";
			
			return (char*)PS2Memory::GetAddr(this->m_pName);
		}

		ETeam CZSeal::GetTeam() { return (ETeam)this->m_teamID; }

		float CZSeal::GetHealth() { return this->m_Health * 100.f; }

		bool CZSeal::IsAlive() { return this->m_Health > 0.0f; }

		//----------------------------------------------------------------------------------------------------
		//										MATCHDATA
		// - MatchData
		//-----------------------------------------------------------------------------------

		bool CZMatchData::isMatchEnded()
		{
			return (PS2Memory::ReadShort<int>(Offsets::o_GameEndAddr) == 0) ? true : false;
		}

		void CZMatchData::ForceStartMatch()
		{
			//
		}

		bool CZMatchData::GetPlayers(std::vector<CZSeal*>* p)
		{
			std::vector<CZSeal*> result{};

			const auto arr = PS2Memory::ReadShort<ZArray<CZSeal*>>(Offsets::o_SealArray).Data();
			
			for (auto ent : arr)
			{
				if (!ent->IsValid())
					continue;

				result.push_back(ent);
			}

			*p = result;

			return result.size() > 0;
		}
	}
}
#pragma pack(pop)




/*

//----------------------------------------------------------------------------------------------------
//										CWEAPON
// - CWeapon
//-----------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------
//										CZSealBody
// - CPlayer
//-----------------------------------------------------------------------------------

///---------------------------------------------------------------------------------------------------
//	[CPLAYER]
// Returns Class Pointer Status
bool CZSealBody::IsValid()
{
	return ((unsigned int)this->pad_0000 == 0x000000 || this->NamePTR == NULL || this->CPlayerMovement == nullptr || this->TeamID == NULL) ? FALSE : TRUE;
}

///---------------------------------------------------------------------------------------------------
//	[CPLAYER]
// Returns Players Alive State
bool CZSealBody::IsAlive()
{
	return (this->Health > 0.0f) ? TRUE : FALSE;
}

///---------------------------------------------------------------------------------------------------
//	[CPLAYER]
// Returns a Pointer to CPlayerPhysics Class
CZSealObject* CZSealBody::PlayerPhysicsPtr()
{
	return (CZSealObject*)((unsigned int)this->CPlayerMovement + g_PS2Mem->BasePS2MemorySpace);
}

///---------------------------------------------------------------------------------------------------
//	[CPLAYER]
// Returns Player Name
std::string CZSealBody::GetPlayerName()
{
	return (char*)(NamePTR + g_PS2Mem->BasePS2MemorySpace);
}

///---------------------------------------------------------------------------------------------------
//	[CPLAYER]
// Returns Player Team Name
std::string CZSealBody::GetTeamName()
{
	switch (this->TeamID)
	{
	case (SEALS):		return "SEAL";
	case (TERRORIST):	return "TERRORIST";
	case (SPECTATOR):	return "SPECTATOR";
	case (SP_ABLE):		return	"SEALS - ABLE Team";
	case (SP_BRAVO):	return	"SEALS - BRAVO Team";
	case (SP_ENEMY_A):	return	"Hostile";
	case (SP_ENEMY_B):	return	"Hostile";
	case (SP_ENEMY_C):	return	"Hostile";
	case (SP_ENEMY_D):	return	"Hostile";
	case (SP_ENEMY_E):	return	"Hostile";
	case (SP_ENEMY_F):	return	"Hostile";
	case (SP_ENEMY_G):	return	"Hostile";
	case (SP_ENEMY_H):	return	"Hostile";
	case (SP_ENEMY_I):	return	"Hostile";
	}
	return std::to_string(this->TeamID);
}

///---------------------------------------------------------------------------------------------------
//	[CPLAYER]
// Returns Weapon Name
std::string CZSealBody::GetWeaponName(unsigned int Weapon)
{
	switch (Weapon)
	{
		case(EPrimaryWeapon::AR_552):		return "552";
		case(EPrimaryWeapon::SMG_9MM):		return "9MM SUB";
		case(ESecondaryWeapon::PISTOL_9MM): return "9MM PISTOL";
	}

	char data[0x56];
	const char* data2 = "%08X";
	sprintf_s(data, data2, Weapon);
	return std::to_string(Weapon);
}

///---------------------------------------------------------------------------------------------------
//	[CPLAYER]
void CZSealBody::GiveAmmo(int amount, int mags)
{
	if (mags <= NULL || mags > 10)
		mags = 3;

	for (int i = NULL; i < mags; i++)
	{
		this->PrimaryMag[i] = amount;
		this->SecondaryMag[i] = amount;
	}
	this->EquipmentSlot1 = NULL;
	this->EquipmentSlot2 = NULL;
	this->EquipmentSlot3 = NULL;
}

///---------------------------------------------------------------------------------------------------
//	[CPLAYER]
// Replaces current weapon in slot with input Weapon
void CZSealBody::GiveWeapon(unsigned int Slot, unsigned int Weapon)
{
	// Intended usage
	switch (Slot)
	{
		case (EWeaponSlot::Primary):		this->PrimaryWeapon		= (EPrimaryWeapon)Weapon;	break;
		case (EWeaponSlot::Secondary):		this->SecondaryWeapon	= (ESecondaryWeapon)Weapon;	break;
		case (EWeaponSlot::EqSlot1):		this->EqSlot1			= (EEquipment)Weapon;	break;
		case (EWeaponSlot::EqSlot2):		this->EqSlot2			= (EEquipment)Weapon;	break;
		case (EWeaponSlot::EqSlot3):		this->EqSlot3			= (EEquipment)Weapon;	break;
	}
}

///---------------------------------------------------------------------------------------------------
//	[CPLAYER]
void CZSealBody::RemoveWeaponsandAmmo()
{
	this->PrimaryWeapon		= (EPrimaryWeapon)NULL;
	this->SecondaryWeapon	= (ESecondaryWeapon)NULL;
	this->EqSlot1			= (EEquipment)NULL;
	this->EqSlot2			= (EEquipment)NULL;
	this->EqSlot3			= (EEquipment)NULL;

	for (int i = NULL; i < 10; i++)
	{
		this->PrimaryMag[i] = NULL;
		this->SecondaryMag[i] = NULL;
	}
	this->EquipmentSlot1 = NULL;
	this->EquipmentSlot2 = NULL;
	this->EquipmentSlot3 = NULL;
}

///---------------------------------------------------------------------------------------------------
//	[CPLAYER]
// Teleports this entity to desired position
void CZSealBody::Teleport(Vector3 Pos)
{
	unsigned int test = (unsigned int)this->CPlayerMovement;
	auto offset = (test + g_PS2Mem->BasePS2MemorySpace);
	auto Movement = (CZSealObject*)offset;
	Movement->absPosition = Pos;
}


///---------------------------------------------------------------------------------------------------
//	[CPLAYER]
// Changes this entity to team to desired team
void CZSealBody::ChangeTeams(ETeam newTeam)
{
	this->TeamID = newTeam;
}

///---------------------------------------------------------------------------------------------------
//	[CPLAYER]
// Sets this entity health (value from 0 - 100)
void CZSealBody::SetHealth(float newHealth)
{
	if (newHealth > 100.f )
		newHealth = 100.0f;
	else if (newHealth < 1.0f)
		newHealth = 0.0f;
	this->Health = newHealth / 100.f;
}

///---------------------------------------------------------------------------------------------------
//	[CPLAYER]
// generates a log containing important player data
// NOTE: Ends with 2New Line
std::string CZSealBody::LogData()
{
	Offsets offsets;
	auto SEAL = (CZSealBody*)offsets.SEALPointer;
	float distance;
	if (SEAL != this)
		distance = g_PS2Mem->Tools->GetDistanceTo3DObject(SEAL->Position, this->Position);	//	@todo: Tools might be a nullptr here
	else
		distance = 0.0f;

	char data[0x256];
	const char* data2 = "PlayerObjectBase: %llX\nPlayerName: %s\nTeamName: %s\nPrimary Weapon: %s	|	PrimaryAmmo: %i\nSecondary Weapon: %s	|	SecondaryAmmo: %i\nHealth: %0.f\nPosition: { %f, %f, %f }\nDistance: { %f }\n\n";
	sprintf_s(data, data2, this, this->GetPlayerName().c_str(), this->GetTeamName().c_str(),
		GetWeaponName(this->PrimaryWeapon).c_str(), this->PrimaryMag[0],
		GetWeaponName(this->SecondaryWeapon).c_str(), this->SecondaryMag[0],
		(this->Health * 100.f),
		this->Position.x, this->Position.y, this->Position.z, distance);
	return data;
}

*/

///	EXAMPLE ImGui Project

	/*
	//	Debug Weapon Manager
	//	Will not work in this scope!
	//	Does not work in current state, enum values need to be passed but instead is passing enum positions
	CWeapon WeaponData;
	void WeaponManager(CPlayer* player)
	{
		ImGui::Spacing();
		ImGui::Separator();
		ImGui::TextCentered("[WEAPON MANAGER]", TRUE, ImColor(0, 255, 255, 200));
		ImGui::Separator();
		ImGui::SetNextItemWidth(100);
		ImGui::Combo("##jfhgjdflkhklsdh", (int*)&WeaponData.e_selectedSlot, WeaponData.AvailSlots, IM_ARRAYSIZE(WeaponData.AvailSlots));
		ImGui::SameLine();
		ImGui::SetNextItemWidth(100);
		switch (WeaponData.e_selectedSlot)
		{
			case(0): ImGui::Combo("##jfhgjdflkhklsdh1", (int*)&WeaponData.e_selected_Primary, WeaponData.PrimaryWeapons, IM_ARRAYSIZE(WeaponData.PrimaryWeapons)); break;
			case(1): ImGui::Combo("##kdgdsazhljfna", (int*)&WeaponData.e_selected_Secondary, WeaponData.SecondaryWeapons, IM_ARRAYSIZE(WeaponData.SecondaryWeapons)); break;
			case(2): ImGui::Combo("##zjdfhbadeh", (int*)&WeaponData.e_selected_Equipment, WeaponData.EquipmentWeapon, IM_ARRAYSIZE(WeaponData.EquipmentWeapon)); break;
			case(3): ImGui::Combo("##hsdfgjsytkiet", (int*)&WeaponData.e_selected_Equipment, WeaponData.EquipmentWeapon, IM_ARRAYSIZE(WeaponData.EquipmentWeapon)); break;
			case(4): ImGui::Combo("##gjnkdtoythmyuk", (int*)&WeaponData.e_selected_Equipment, WeaponData.EquipmentWeapon, IM_ARRAYSIZE(WeaponData.EquipmentWeapon)); break;
		}
		if (ImGui::Button("GIVE WEAPON", ImVec2(ImGui::GetContentRegionAvail().x, 0)))
		{
			switch (WeaponData.e_selectedSlot)
			{
				case 0:        player->GiveWeapon(WeaponData.e_selectedSlot, WeaponData.e_selected_Primary); break;
				case 1:        player->GiveWeapon(WeaponData.e_selectedSlot, WeaponData.e_selected_Secondary); break;
				case 2:        player->GiveWeapon(WeaponData.e_selectedSlot, WeaponData.e_selected_Equipment); break;
				case 3:        player->GiveWeapon(WeaponData.e_selectedSlot, WeaponData.e_selected_Equipment); break;
				case 4:        player->GiveWeapon(WeaponData.e_selectedSlot, WeaponData.e_selected_Equipment); break;
			}
		}
	}

	void test_debug_menu()
	{
		SOCOM1::Offsets offsets;
		SOCOM1::CPlayer* PLAYER = (CPlayer*)offsets.SEALPointer;
		SOCOM1::MatchData MATCH;

		if (ImGui::Button("Test Read Memory", ImVec2(ImGui::GetWindowContentRegionWidth(), 20)))
		{
			auto address = offsets.FrameRate1;

			auto value = g_Engine->PS2Read<int>(offsets.FrameRate1);

			g_Console->printdbg("Test Read Memory:\nFrameRate1: [%08X]\nVALUE: [%i]\n\n", Console::Colors::blue, address, value);
		}

		if (ImGui::Button("Test Write Memory", ImVec2(ImGui::GetWindowContentRegionWidth(), 20)))
		{
			g_Engine->PS2Write<int>(offsets.FrameRate1, 30);

			g_Engine->PS2Write<int>(offsets.FrameRate2, 30);

			g_Console->printdbg("Test Write Memory:\nFrameRate1: [%i]\nFrameRate2: [%i]\n\n", Console::Colors::blue, g_Engine->PS2Read<int>(offsets.FrameRate1), g_Engine->PS2Read<int>(offsets.FrameRate2));

		}

		if (ImGui::Button("Test ResolvePointer", ImVec2(ImGui::GetWindowContentRegionWidth(), 20)))
		{
			if (PLAYER->IsValid()) {

				CPlayer::CPlayerPhysics* move = PLAYER->PlayerPhysicsPtr();

				g_Console->printdbg("%s", Console::Colors::DEFAULT, PLAYER->LogData().c_str());
			}
			else
				g_Console->printdbg("[!] INVALID PLAYER OBJECT\n", Console::Colors::red);
		}

		if (ImGui::Button("Display Offsets Data", ImVec2(ImGui::GetWindowContentRegionWidth(), 20)))
			g_Console->printdbg("Dumping Offset Data:\n%s", Console::Colors::DEFAULT, offsets.LogData().c_str());

		if (ImGui::Button("Check isValid", ImVec2(ImGui::GetWindowContentRegionWidth(), 20)))
		{
			bool result = PLAYER->IsValid();

			switch (result) {

			case (TRUE):	g_Console->printdbg("isValid: [%i]\n", Console::Colors::yellow, result); break;

			case (FALSE):	g_Console->printdbg("isValid: [%i]\n", Console::Colors::red, result); break;
			}
		}

		if (ImGui::Button("Dump Player Data", ImVec2(ImGui::GetWindowContentRegionWidth(), 20)))
		{
			if (PLAYER->IsValid())
				g_Console->printdbg("%s", Console::Colors::DEFAULT, PLAYER->LogData().c_str());
			else
				g_Console->printdbg("[!] INVALID PLAYER OBJECT\n", Console::Colors::red);
		}

		if (ImGui::Button("Give 552", ImVec2(ImGui::GetWindowContentRegionWidth(), 20)))
		{
			if (PLAYER->IsValid()) {
				//player->PrimaryWeapon = CPlayer::CWeapon::AR_552;
				PLAYER->PrimaryWeapon = CWeapon::AR_552;
				for (int i = 0; i < 10; i++)
					PLAYER->PrimaryMag[i] = 1337;
			}
			else
				g_Console->printdbg("[!] INVALID PLAYER OBJECT\n", Console::Colors::red);
		}

		if (ImGui::Button("Dump Entity Array", ImVec2(ImGui::GetWindowContentRegionWidth(), 20)))
		{
			std::vector<SOCOM1::CPlayer*> ent = MATCH.GetPlayers();

			if (!ent.empty()) {

				for (int i = 0; i < ent.size(); i++)
					g_Console->printdbg("%s", Console::Colors::DEFAULT, ent[i]->LogData().c_str());

			}

		}

		if (ImGui::Button("Telpeort All Entities", ImVec2(ImGui::GetWindowContentRegionWidth(), 20)))
		{
			if (PLAYER->IsValid())
			{
				std::vector<SOCOM1::CPlayer*> ent = MATCH.GetPlayers();

				if (!ent.empty()) {

					for (int i = 0; i < ent.size(); i++) {

						float distance = PLAYER->GetDistanceTo3DObject(PLAYER->Position, ent[i]->Position);
						g_Console->printdbg("Teleporting Entity:\n- Name: %s\n - Position: { %0.2f, %0.2f, %0.2f }\n - Distance: %0.0fm\n\n", Console::Colors::DEFAULT, ent[i]->GetPlayerName().c_str(), ent[i]->Position.x, ent[i]->Position.y, ent[i]->Position.z, distance);
						ent[i]->Teleport(PLAYER->Position);
					}
				}
			}
		}

		if (ImGui::Button("Dump Match Data", ImVec2(ImGui::GetWindowContentRegionWidth(), 20)))
			g_Console->printdbg("IsMatchEnded: [%i]\n\n", Console::Colors::yellow, MATCH.isMatchEnded());

		if (PLAYER->IsValid())
			WeaponManager(PLAYER);
	}
	*/
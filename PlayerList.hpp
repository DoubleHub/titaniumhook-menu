#pragma once
 
#include "MenuElements.hpp"
#include "CBaseEntity.h"
 
class PlayerList : public Element
{
protected:
 
    std::vector<SourceSDK::CBaseEntity*> _ents;
	bool once;
 
public:
 
    PlayerList()
    {
        _ents.clear();
		for (int i=0; i<MAX_CLIENTS; i++)
			_ents.push_back(nullptr);
		once = true;
    }
 
    void Think()
    {
        visible = parent->GetVisible();
        if (!visible) return;
		if (!V::PlayerList::Active) return;
		if (IsControlOpen()) return;
 
		for (int i=1; i<=64; i++)
		{
			SourceSDK::CBaseEntity* pEnt = (SourceSDK::CBaseEntity*)I::ClientEntityList->GetClientEntity(i);
			if (!pEnt) continue;
			if (pEnt->IsDormant()) continue;
			if (pEnt == (SourceSDK::CBaseEntity*)I::ClientEntityList->GetClientEntity(I::EngineClient->GetLocalPlayer())) continue;
			if (!pEnt->IsAlive()) continue;
 
			_ents[i] = pEnt;
		}
    }
 
    void Paint()
    {
        if (!visible) return;
		if (!V::PlayerList::Active) return;
		static int indexes = 0;
 
		D::DrawString(F::Tahoma12_Outline, rx, ry, SourceSDK::Color::White(), false, XorStr("Name\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\tTeam\t\t\t\t\t\tHealth\t\t\t\t\t\tArmor\t\t\t\t\t\tRank\t\t\t\t\t\tWins\t\t\t\t\t\tLocation"));
		for (unsigned int i=0; i<_ents.size(); i++)
		{
			if (_ents[i] == nullptr) continue;

			D::DrawString(F::Tahoma12_Outline, rx, ry + 20 * (indexes + 1), _ents[i]->IsEnemy() ? SourceSDK::Color::Red() : SourceSDK::Color::White(), false, _ents[i]->IsDormant() ? XorStr("[%s]") : XorStr("%s"), _ents[i]->GetName().c_str());

			D::DrawString(F::Tahoma12_Outline, rx + 175, ry + 20 * (indexes + 1), _ents[i]->IsEnemy() ? SourceSDK::Color::Red() : SourceSDK::Color::White(), false, _ents[i]->IsDormant() ? XorStr("--") : XorStr("%s"), _ents[i]->TeamToString().c_str());
			D::DrawString(F::Tahoma12_Outline, rx + 235, ry + 20 * (indexes + 1), _ents[i]->IsEnemy() ? SourceSDK::Color::Red() : SourceSDK::Color::White(), false, _ents[i]->IsDormant() ? XorStr("--") : XorStr("%d"), _ents[i]->GetHealth());
			D::DrawString(F::Tahoma12_Outline, rx + 305, ry + 20 * (indexes + 1), _ents[i]->IsEnemy() ? SourceSDK::Color::Red() : SourceSDK::Color::White(), false, _ents[i]->IsDormant() ? XorStr("--") : XorStr("%d"), _ents[i]->GetArmor());
			D::DrawString(F::Tahoma12_Outline, rx + 375, ry + 20 * (indexes + 1), _ents[i]->IsEnemy() ? SourceSDK::Color::Red() : SourceSDK::Color::White(), false, _ents[i]->IsDormant() ? XorStr("--") : XorStr("%s"), _ents[i]->GetRankShort().c_str());
			D::DrawString(F::Tahoma12_Outline, rx + 440, ry + 20 * (indexes + 1), _ents[i]->IsEnemy() ? SourceSDK::Color::Red() : SourceSDK::Color::White(), false, _ents[i]->IsDormant() ? XorStr("--") : XorStr("%d"), _ents[i]->GetWins());
			D::DrawString(F::Tahoma12_Outline, rx + 495, ry + 20 * (indexes + 1), _ents[i]->IsEnemy() ? SourceSDK::Color::Red() : SourceSDK::Color::White(), false, _ents[i]->IsDormant() ? XorStr("--") : XorStr("%s"), _ents[i]->GetLastPlaceName());

			indexes++;
		}

		indexes = 0;
    }
 
    std::vector<SourceSDK::CBaseEntity*> GetEntities() { return _ents; }
    void AddEntity(SourceSDK::CBaseEntity* pEntity) { _ents.push_back(pEntity); }
};
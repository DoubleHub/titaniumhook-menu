#pragma once

#include "MenuElements.hpp"

class Combobox : public Element
{
protected:

	std::string title;
	std::vector<std::string> items;
	bool opened;
	std::string current_item;
	int* value;
	
	// Fill it only if it's the Weapon Combobox of Skinchanger!
	Combobox* par_SkinList;
	// Fill it only if it's the SkinList!!!
	int item_def;
	std::string raw_weap_name;

public:

	bool bIsPaintKitList;
	std::string FancyWeaponNameToRaw(const std::string& strFancyWeapon)
	{
		if (strFancyWeapon == XorStr("Deagle"))
			return XorStr("deagle");
		if (strFancyWeapon == XorStr("Elites"))
			return XorStr("elite");
		if (strFancyWeapon == XorStr("Five-Seven"))
			return XorStr("fiveseven");
		if (strFancyWeapon == XorStr("Glock"))
			return XorStr("glock");
		if (strFancyWeapon == XorStr("AK-47"))
			return XorStr("ak47");
		if (strFancyWeapon == XorStr("AUG"))
			return XorStr("aug");
		if (strFancyWeapon == XorStr("AWP"))
			return XorStr("awp");
		if (strFancyWeapon == XorStr("Famas"))
			return XorStr("famas");
		if (strFancyWeapon == XorStr("G3SG1"))
			return XorStr("g3sg1");
		if (strFancyWeapon == XorStr("Galil-AR"))
			return XorStr("galilar");
		if (strFancyWeapon == XorStr("M249"))
			return XorStr("m249");
		if (strFancyWeapon == XorStr("M4A1-S"))
			return XorStr("m4a1_silencer");
		if (strFancyWeapon == XorStr("M4A4"))
			return XorStr("m4a1");
		if (strFancyWeapon == XorStr("MAC-10"))
			return XorStr("mac10");
		if (strFancyWeapon == XorStr("P90"))
			return XorStr("p90");
		if (strFancyWeapon == XorStr("UMP-45"))
			return XorStr("ump45");
		if (strFancyWeapon == XorStr("XM-1014"))
			return XorStr("xm1014");
		if (strFancyWeapon == XorStr("PP-Bizon"))
			return XorStr("bizon");
		if (strFancyWeapon == XorStr("MAG-7"))
			return XorStr("mag7");
		if (strFancyWeapon == XorStr("Negev"))
			return XorStr("negev");
		if (strFancyWeapon == XorStr("Sawed-Off"))
			return XorStr("sawedoff");
		if (strFancyWeapon == XorStr("Tec-9"))
			return XorStr("tec9");
		if (strFancyWeapon == XorStr("P2000"))
			return XorStr("hkp2000");
		if (strFancyWeapon == XorStr("MP7"))
			return XorStr("mp7");
		if (strFancyWeapon == XorStr("MP9"))
			return XorStr("mp9");
		if (strFancyWeapon == XorStr("Nova"))
			return XorStr("nova");
		if (strFancyWeapon == XorStr("P250"))
			return XorStr("p250");
		if (strFancyWeapon == XorStr("SCAR-20"))
			return XorStr("scar20");
		if (strFancyWeapon == XorStr("SG-553"))
			return XorStr("sg556");
		if (strFancyWeapon == XorStr("SSG-08"))
			return XorStr("ssg08");
		if (strFancyWeapon == XorStr("USP-S"))
			return XorStr("usp_silencer");
		if (strFancyWeapon == XorStr("CZ75-A"))
			return XorStr("cz75a");
		if (strFancyWeapon == XorStr("Revolver"))
			return XorStr("revolver");
		if (strFancyWeapon == XorStr("M9 Bayonet"))
			return XorStr("knife_m9_bayonet");
		if (strFancyWeapon == XorStr("Bayonet"))
			return XorStr("bayonet");
		if (strFancyWeapon == XorStr("Flip Knife"))
			return XorStr("knife_flip");
		if (strFancyWeapon == XorStr("Gut Knife"))
			return XorStr("knife_gut");
		if (strFancyWeapon == XorStr("Karambit"))
			return XorStr("knife_karambit");
		if (strFancyWeapon == XorStr("Huntsman Knife"))
			return XorStr("knife_tactical");
		if (strFancyWeapon == XorStr("Falchion Knife"))
			return XorStr("knife_falchion");
		if (strFancyWeapon == XorStr("Bowie Knife"))
			return XorStr("knife_survival_bowie");
		if (strFancyWeapon == XorStr("Butterfly Knife"))
			return XorStr("knife_butterfly");
		if (strFancyWeapon == XorStr("Shadow Daggers"))
			return XorStr("knife_push");
	}

	Combobox()
	{
		opened = false;
		items.clear();
		current_item = "";
		value = nullptr;
		par_SkinList = nullptr;
		item_def = 0;
		bIsPaintKitList = false;
		raw_weap_name = "";
	}

	void Think()
	{
		visible = parent->GetVisible();
		if (!visible) return;

		if (Input->Clicked(rx, ry, width, height) && GetCurrentlyOpenedControl() == nullptr)
		{
			opened = !opened;
			SetControlOpen(opened);
			SetCurrentlyOpenedControl((opened) ? this : nullptr);
		}

		if (bIsPaintKitList)
		{
			int PaintKit = 0;
			auto vecSkinConfigs = GetSkinConfigList();
			for (auto& e : vecSkinConfigs)
			{
				if (e.WeaponName == raw_weap_name && e.PaintKit != 0)
					PaintKit = e.PaintKit;
			}
			if (PaintKit != 0)
				current_item = SkinParser->GetSkinNameFromPaintKit(raw_weap_name, PaintKit);
		}

		if (opened)
		{
			if (Input->GetClick())
			{
				POINT mouse = Input->GetMousePos();
				if (
					(mouse.x < rx || mouse.x > rx + width
					|| mouse.y < ry || mouse.y > ry + height)
					&& GetCurrentlyOpenedControl() == this)
				{
					for (unsigned int i=0; i<items.size(); i++)
					{
						bool bHovering = Input->Hovering(rx, ry + 20 * (i + 1), width, height);
						if (bHovering && Input->GetClick())
						{
							//std::swap(items[0], items[i]);
							if (!par_SkinList && value)
								*value = i;
							if (!items.empty())
								current_item = items[i];
							BUTTON_SOUND;
							if (par_SkinList)
							{
								// THIS PART OF CODE IS RELATED TO SKIN CHANGER ONLY!!!
								par_SkinList->items = 
									SkinParser->GetVectorSkinsFromWeapon
									(FancyWeaponNameToRaw(current_item));
								auto vecWeapons = GetWeaponMap();
								for (auto& e : vecWeapons)
								{
									if (e.first == FancyWeaponNameToRaw(current_item))
										par_SkinList->item_def = e.second;
								}
								par_SkinList->raw_weap_name = FancyWeaponNameToRaw(current_item);
							}

							if (bIsPaintKitList)
							{
								auto vecSkinConfigs = GetSkinConfigList();
								auto vecWeapons = GetWeaponMap();
								for (auto& e : vecWeapons)
								{
									if (e.second == item_def)
									{
										for (auto& i : vecSkinConfigs)
										{
											if (i.ItemDefinitionIndex == item_def)
												i.PaintKit = SkinParser->GetPaintKitFromSkinName(e.first, current_item);
										}
									}
								}
								SetSkinConfigList(vecSkinConfigs);
							}

						}
					}
					opened = false;
					SetCurrentlyOpenedControl(nullptr);
					SetControlOpen(false);
				}
			}
		}

		if (!items.empty() && value && !par_SkinList)
			current_item = items[*value];
		if (par_SkinList != nullptr)
		{
			*value = par_SkinList->item_def;
		}
	}

	void Paint()
	{
		if (!visible) return;

		D::DrawFilledRect(rx, ry, width, height, SourceSDK::Color::DarkestGray3());
		if (Input->Hovering(rx, ry, width, height) && !opened)
			D::DrawOutlinedRect(rx, ry, width, height, SourceSDK::Color::White());

		if (opened)
		{
			D::DrawString(F::Tahoma12_Outline, rx + 3, ry + height / 2, SourceSDK::Color::White(), false, XorStr("%s"), current_item.c_str());
			for (unsigned int i=0; i<items.size(); i++)
			{
				bool bHovering = Input->Hovering(rx, ry + 20 * (i + 1), width, height);
				D::DrawFilledRect(rx, ry + 20 * (i + 1), width, height, bHovering ? V::Colors::MenuColor_First : SourceSDK::Color::DarkestGray3());
				D::DrawString(F::Tahoma12_Outline, rx + 5, (ry + 20 * (i + 1)) + 10, SourceSDK::Color::White(), false, XorStr("%s"), items[i].c_str());
			}
		}
		D::DrawString(F::Tahoma12_Outline, rx + 3, ry - 7, SourceSDK::Color::White(), false, XorStr("%s"), title.c_str());
		if (!opened)
			D::DrawString(F::Tahoma12_Outline, rx + 3, ry + height / 2, SourceSDK::Color::White(), false, XorStr("%s"), current_item.c_str());
	}

	std::string GetTitle() { return title; }
	void SetTitle(std::string _title) { title = _title; }
	void SetValue(int* _value) { value = _value; *value = 0; 
											if (!items.empty())
												current_item = items[0]; }
	void AddItem(std::string item_name) { items.push_back(item_name); }
	// There is no failsafe check for items not present in vector, be careful! 
	// TODO: Add a failsafe check for item_name validity
	void SetCurrentItem(std::string item_name) 
	{ 
		current_item = item_name; 
		(value == nullptr && !items.empty()) ? 0 : std::find(items.begin(), items.end(), item_name) - items.begin();
	}
	void SetParentSkinList(Combobox* pParent)
	{
		if (pParent)
		this->par_SkinList = pParent;
	}
	Combobox* GetParentSkinList()
	{
		return this->par_SkinList;
	}
	int GetItemDef()
	{
		return this->item_def;
	}
	std::string GetCurrentItem()
	{
		return this->current_item;
	}

};
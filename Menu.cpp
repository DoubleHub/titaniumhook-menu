#include "Menu.hpp"

void CMenu::Setup()
{
	int iScrW, iScrH, iMenuW = 803, iMenuH = 600;
	I::EngineClient->GetScreenSize(iScrW, iScrH);

	/// FRAME =====================================================================

	frame = new Frame;
	frame->SetPosition(iScrW / 2 - iMenuW / 2, iScrH / 2 - iMenuH / 2);
	frame->SetSize(iMenuW, iMenuH);
	frame->is_separate_frame = true;

	static int checkbox = 0;
	static int tab = 0;
	static int groupbox = 0;

	// ============================================================================

	auto legitbot_tab = new Tab;
	legitbot_tab->SetTab(tab);
	legitbot_tab->SetTitle(XorStr("Legit"));

	/// LEGITBOT ==================================================================

	auto legitbot_active = new Checkbox;
	legitbot_active->SetPosition(20, 68);
	legitbot_active->SetTitle(XorStr("Active"));
	legitbot_active->SetValue(&V::Legitbot::Active);
	legitbot_tab->Add(legitbot_active);

	auto legitbot_faceit = new Checkbox;
	legitbot_faceit->SetPosition(120, 68);
	legitbot_faceit->SetTitle(XorStr("FaceIT Mode"));
	legitbot_faceit->SetValue(&V::Legitbot::FaceIT);
	legitbot_tab->Add(legitbot_faceit);

#pragma region LEGITBOT

	auto legitbot_settings = new Groupbox;
	legitbot_settings->SetPosition(20, 108);
	legitbot_settings->SetSize(147, 450);
	legitbot_settings->SetTitle(XorStr("Default Settings"));
	legitbot_tab->Add(legitbot_settings);

	// Settings ======================================================

	auto aimbot_enable = new Checkbox;
	aimbot_enable->SetPosition(25, 115);
	aimbot_enable->SetTitle(XorStr("Enabled"));
	aimbot_enable->SetValue(&V::Legitbot::Enabled);
	legitbot_tab->Add(aimbot_enable);

	auto aimbot_key = new KeyReader;
	aimbot_key->SetPosition(25, 185);
	aimbot_key->SetTitle(XorStr("Key"));
	aimbot_key->SetSize(137, 20);
	aimbot_key->SetValue(&V::Legitbot::AimKey);
	legitbot_tab->Add(aimbot_key);

	auto aimbot_ignoreteam = new Checkbox;
	aimbot_ignoreteam->SetPosition(25, 245);
	aimbot_ignoreteam->SetTitle(XorStr("Ignore Team"));
	aimbot_ignoreteam->SetValue(&V::Legitbot::IgnoreTeam);
	legitbot_tab->Add(aimbot_ignoreteam);

	auto aimbot_smartbone = new Checkbox;
	aimbot_smartbone->SetPosition(25, 265);
	aimbot_smartbone->SetTitle(XorStr("Smart Bone"));
	aimbot_smartbone->SetValue(&V::Legitbot::SmartHitbox);
	legitbot_tab->Add(aimbot_smartbone);

	auto aimbot_fov = new Slider;
	aimbot_fov->SetPosition(25, 300);
	aimbot_fov->SetTitle(XorStr("FOV Amount"));
	aimbot_fov->SetValue(&V::Legitbot::FOV);
	aimbot_fov->SetSize(137, 7);
	aimbot_fov->SetMin(0.f);
	aimbot_fov->SetMax(90.f);
	legitbot_tab->Add(aimbot_fov);

	auto aimbot_smooth = new Checkbox;
	aimbot_smooth->SetPosition(25, 325);
	aimbot_smooth->SetTitle(XorStr("Smooth"));
	aimbot_smooth->SetValue(&V::Legitbot::EnableSmooth);
	legitbot_tab->Add(aimbot_smooth);

	auto aimbot_smooth_amount = new Slider;
	aimbot_smooth_amount->SetPosition(25, 360);
	aimbot_smooth_amount->SetTitle(XorStr("Smooth Amount"));
	aimbot_smooth_amount->SetValue(&V::Legitbot::Smooth);
	aimbot_smooth_amount->SetSize(137, 7);
	aimbot_smooth_amount->SetMin(0.f);
	aimbot_smooth_amount->SetMax(25.f);
	legitbot_tab->Add(aimbot_smooth_amount);

	auto aimbot_smoke = new Checkbox;
	aimbot_smoke->SetPosition(25, 420);
	aimbot_smoke->SetTitle(XorStr("Smoke Check"));
	aimbot_smoke->SetValue(&V::Legitbot::SmokeCheck);
	legitbot_tab->Add(aimbot_smoke);

	auto aimbot_weapons = new Checkbox;
	aimbot_weapons->SetPosition(25, 445);
	aimbot_weapons->SetTitle(XorStr("Use WeaponGroups"));
	aimbot_weapons->SetValue(&V::Legitbot::WeaponGroups);
	legitbot_tab->Add(aimbot_weapons);

	auto aimbot_silent = new Checkbox;
	aimbot_silent->SetPosition(25, 470);
	aimbot_silent->SetTitle(XorStr("Silent Aim"));
	aimbot_silent->SetValue(&V::Legitbot::Silent);
	legitbot_tab->Add(aimbot_silent);

	auto aimbot_visible = new Checkbox;
	aimbot_visible->SetPosition(25, 495);
	aimbot_visible->SetTitle(XorStr("Visible Only"));
	aimbot_visible->SetValue(&V::Legitbot::VisibleCheck);
	legitbot_tab->Add(aimbot_visible);

	auto aimbot_mode = new Combobox;
	aimbot_mode->SetPosition(25, 390);
	aimbot_mode->SetTitle(XorStr("Mode"));
	aimbot_mode->SetSize(137, 20);
	aimbot_mode->AddItem(XorStr("On Fire"));
	aimbot_mode->AddItem(XorStr("On Key"));
	aimbot_mode->AddItem(XorStr("On Sight"));
	aimbot_mode->SetCurrentItem(XorStr("On Fire"));
	aimbot_mode->SetValue(&V::Legitbot::Mode);
	legitbot_tab->Add(aimbot_mode);

	auto aimbot_target = new Combobox;
	aimbot_target->SetPosition(25, 220);
	aimbot_target->SetTitle(XorStr("Target Selection"));
	aimbot_target->SetSize(137, 20);
	aimbot_target->AddItem(XorStr("Crosshair Distance"));
	aimbot_target->AddItem(XorStr("Player Distance"));
	aimbot_target->AddItem(XorStr("Lowest HP"));
	aimbot_target->AddItem(XorStr("Highest Threat"));
	aimbot_target->SetCurrentItem(XorStr("Crosshair Distance"));
	aimbot_target->SetValue(&V::Legitbot::AimTarget);
	legitbot_tab->Add(aimbot_target);

	auto aimbot_hitbox = new Combobox;
	aimbot_hitbox->SetPosition(25, 150);
	aimbot_hitbox->SetTitle(XorStr("Hitbox"));
	aimbot_hitbox->SetSize(137, 20);
	FillComboBox_Hitbox(aimbot_hitbox);
	aimbot_hitbox->SetValue(&V::Legitbot::Hitbox);
	aimbot_hitbox->SetCurrentItem(XorStr("Head"));
	legitbot_tab->Add(aimbot_hitbox);

	// ===============================================================

	auto legitbot_pistol = new Groupbox;
	legitbot_pistol->SetPosition(20 + (++groupbox * 145) + 8, 108);
	legitbot_pistol->SetSize(147, 450);
	legitbot_pistol->SetTitle(XorStr("Pistol"));
	legitbot_tab->Add(legitbot_pistol);

	// Pistol ========================================================

	auto pistol_enable = new Checkbox;
	pistol_enable->SetPosition(25 + (groupbox * 145) + 8, 115);
	pistol_enable->SetTitle(XorStr("Enabled"));
	pistol_enable->SetValue(&V::Legitbot_Pistol::Enabled);
	legitbot_tab->Add(pistol_enable);

	auto pistol_key = new KeyReader;
	pistol_key->SetPosition(25 + (groupbox * 145) + 8, 185);
	pistol_key->SetTitle(XorStr("Key"));
	pistol_key->SetSize(137, 20);
	pistol_key->SetValue(&V::Legitbot_Pistol::AimKey);
	legitbot_tab->Add(pistol_key);

	auto pistol_ignoreteam = new Checkbox;
	pistol_ignoreteam->SetPosition(25 + (groupbox * 145) + 8, 245);
	pistol_ignoreteam->SetTitle(XorStr("Ignore Team"));
	pistol_ignoreteam->SetValue(&V::Legitbot_Pistol::IgnoreTeam);
	legitbot_tab->Add(pistol_ignoreteam);

	auto pistol_smartbone = new Checkbox;
	pistol_smartbone->SetPosition(25 + (groupbox * 145) + 8, 265);
	pistol_smartbone->SetTitle(XorStr("Smart Bone"));
	pistol_smartbone->SetValue(&V::Legitbot_Pistol::SmartHitbox);
	legitbot_tab->Add(pistol_smartbone);

	auto pistol_fov = new Slider;
	pistol_fov->SetPosition(25 + (groupbox * 145) + 8, 300);
	pistol_fov->SetTitle(XorStr("FOV Amount"));
	pistol_fov->SetValue(&V::Legitbot_Pistol::FOV);
	pistol_fov->SetSize(137, 7);
	pistol_fov->SetMin(0.f);
	pistol_fov->SetMax(90.f);
	legitbot_tab->Add(pistol_fov);

	auto pistol_smooth = new Checkbox;
	pistol_smooth->SetPosition(25 + (groupbox * 145) + 8, 325);
	pistol_smooth->SetTitle(XorStr("Smooth"));
	pistol_smooth->SetValue(&V::Legitbot_Pistol::EnableSmooth);
	legitbot_tab->Add(pistol_smooth);

	auto pistol_smooth_amount = new Slider;
	pistol_smooth_amount->SetPosition(25 + (groupbox * 145) + 8, 360);
	pistol_smooth_amount->SetTitle(XorStr("Smooth Amount"));
	pistol_smooth_amount->SetValue(&V::Legitbot_Pistol::Smooth);
	pistol_smooth_amount->SetSize(137, 7);
	pistol_smooth_amount->SetMin(0.f);
	pistol_smooth_amount->SetMax(25.f);
	legitbot_tab->Add(pistol_smooth_amount);

	auto pistol_smoke = new Checkbox;
	pistol_smoke->SetPosition(25 + (groupbox * 145) + 8, 420);
	pistol_smoke->SetTitle(XorStr("Smoke Check"));
	pistol_smoke->SetValue(&V::Legitbot_Pistol::SmokeCheck);
	legitbot_tab->Add(pistol_smoke);

	auto pistol_auto = new Checkbox;
	pistol_auto->SetPosition(25 + (groupbox * 145) + 8, 445);
	pistol_auto->SetTitle(XorStr("Auto-Pistols"));
	pistol_auto->SetValue(&V::Legitbot_Pistol::AutoPistols);
	legitbot_tab->Add(pistol_auto);

	auto pistol_mode = new Combobox;
	pistol_mode->SetPosition(25 + (groupbox * 145) + 8, 390);
	pistol_mode->SetTitle(XorStr("Mode"));
	pistol_mode->SetSize(137, 20);
	pistol_mode->AddItem(XorStr("On Fire"));
	pistol_mode->AddItem(XorStr("On Key"));
	pistol_mode->AddItem(XorStr("On Sight"));
	pistol_mode->SetCurrentItem(XorStr("On Fire"));
	pistol_mode->SetValue(&V::Legitbot_Pistol::Mode);
	legitbot_tab->Add(pistol_mode);

	auto pistol_target = new Combobox;
	pistol_target->SetPosition(25 + (groupbox * 145) + 8, 220);
	pistol_target->SetTitle(XorStr("Target Selection"));
	pistol_target->SetSize(137, 20);
	pistol_target->AddItem(XorStr("Crosshair Distance"));
	pistol_target->AddItem(XorStr("Player Distance"));
	pistol_target->AddItem(XorStr("Lowest HP"));
	pistol_target->AddItem(XorStr("Highest Threat"));
	pistol_target->SetCurrentItem(XorStr("Crosshair Distance"));
	pistol_target->SetValue(&V::Legitbot_Pistol::AimTarget);
	legitbot_tab->Add(pistol_target);

	auto pistol_hitbox = new Combobox;
	pistol_hitbox->SetPosition(25 + (groupbox * 145) + 8, 150);
	pistol_hitbox->SetTitle(XorStr("Hitbox"));
	pistol_hitbox->SetSize(137, 20);
	FillComboBox_Hitbox(pistol_hitbox);
	pistol_hitbox->SetValue(&V::Legitbot_Pistol::Hitbox);
	pistol_hitbox->SetCurrentItem(XorStr("Head"));
	legitbot_tab->Add(pistol_hitbox);

	// ===============================================================

	auto legitbot_rifle = new Groupbox;
	legitbot_rifle->SetPosition(20 + (++groupbox * 145) + 16, 108);
	legitbot_rifle->SetSize(147, 450);
	legitbot_rifle->SetTitle(XorStr("Rifle"));
	legitbot_tab->Add(legitbot_rifle);

	// Rifle =========================================================

	auto rifle_enable = new Checkbox;
	rifle_enable->SetPosition(25 + (groupbox * 145) + 16, 115);
	rifle_enable->SetTitle(XorStr("Enabled"));
	rifle_enable->SetValue(&V::Legitbot_Rifle::Enabled);
	legitbot_tab->Add(rifle_enable);

	auto rifle_key = new KeyReader;
	rifle_key->SetPosition(25 + (groupbox * 145) + 16, 185);
	rifle_key->SetTitle(XorStr("Key"));
	rifle_key->SetSize(137, 20);
	rifle_key->SetValue(&V::Legitbot_Rifle::AimKey);
	legitbot_tab->Add(rifle_key);

	auto rifle_ignoreteam = new Checkbox;
	rifle_ignoreteam->SetPosition(25 + (groupbox * 145) + 16, 245);
	rifle_ignoreteam->SetTitle(XorStr("Ignore Team"));
	rifle_ignoreteam->SetValue(&V::Legitbot_Rifle::IgnoreTeam);
	legitbot_tab->Add(rifle_ignoreteam);

	auto rifle_smartbone = new Checkbox;
	rifle_smartbone->SetPosition(25 + (groupbox * 145) + 16, 265);
	rifle_smartbone->SetTitle(XorStr("Smart Bone"));
	rifle_smartbone->SetValue(&V::Legitbot_Rifle::SmartHitbox);
	legitbot_tab->Add(rifle_smartbone);

	auto rifle_fov = new Slider;
	rifle_fov->SetPosition(25 + (groupbox * 145) + 16, 300);
	rifle_fov->SetTitle(XorStr("FOV Amount"));
	rifle_fov->SetValue(&V::Legitbot_Rifle::FOV);
	rifle_fov->SetSize(137, 7);
	rifle_fov->SetMin(0.f);
	rifle_fov->SetMax(90.f);
	legitbot_tab->Add(rifle_fov);

	auto rifle_smooth = new Checkbox;
	rifle_smooth->SetPosition(25 + (groupbox * 145) + 16, 325);
	rifle_smooth->SetTitle(XorStr(XorStr("Smooth")));
	rifle_smooth->SetValue(&V::Legitbot_Rifle::EnableSmooth);
	legitbot_tab->Add(rifle_smooth);

	auto rifle_smooth_amount = new Slider;
	rifle_smooth_amount->SetPosition(25 + (groupbox * 145) + 16, 360);
	rifle_smooth_amount->SetTitle(XorStr("Smooth Amount"));
	rifle_smooth_amount->SetValue(&V::Legitbot_Rifle::Smooth);
	rifle_smooth_amount->SetSize(137, 7);
	rifle_smooth_amount->SetMin(0.f);
	rifle_smooth_amount->SetMax(25.f);
	legitbot_tab->Add(rifle_smooth_amount);

	auto rifle_smoke = new Checkbox;
	rifle_smoke->SetPosition(25 + (groupbox * 145) + 16, 420);
	rifle_smoke->SetTitle(XorStr("Smoke Check"));
	rifle_smoke->SetValue(&V::Legitbot_Rifle::SmokeCheck);
	legitbot_tab->Add(rifle_smoke);

	auto rifle_rcs = new Checkbox;
	rifle_rcs->SetPosition(25 + (groupbox * 145) + 16, 445);
	rifle_rcs->SetTitle(XorStr("Recoil Control"));
	rifle_rcs->SetValue(&V::Legitbot_Rifle::EnableRCS);
	legitbot_tab->Add(rifle_rcs);

	auto rifle_rcs_amount_x = new Slider;
	rifle_rcs_amount_x->SetPosition(25 + (groupbox * 145) + 16, 480);
	rifle_rcs_amount_x->SetTitle(XorStr("Control Strength X-Axis"));
	rifle_rcs_amount_x->SetValue(&V::Legitbot_Rifle::RCSAmount_X);
	rifle_rcs_amount_x->SetSize(137, 7);
	rifle_rcs_amount_x->SetMin(0.f);
	rifle_rcs_amount_x->SetMax(2.f);
	legitbot_tab->Add(rifle_rcs_amount_x);

	auto rifle_rcs_amount_y = new Slider;
	rifle_rcs_amount_y->SetPosition(25 + (groupbox * 145) + 16, 525);
	rifle_rcs_amount_y->SetTitle(XorStr("Control Strength Y-Axis"));
	rifle_rcs_amount_y->SetValue(&V::Legitbot_Rifle::RCSAmount_Y);
	rifle_rcs_amount_y->SetSize(137, 7);
	rifle_rcs_amount_y->SetMin(0.f);
	rifle_rcs_amount_y->SetMax(2.f);
	legitbot_tab->Add(rifle_rcs_amount_y);

	auto rifle_mode = new Combobox;
	rifle_mode->SetPosition(25 + (groupbox * 145) + 16, 390);
	rifle_mode->SetTitle(XorStr("Mode"));
	rifle_mode->SetSize(137, 20);
	rifle_mode->AddItem(XorStr("On Fire"));
	rifle_mode->AddItem(XorStr("On Key"));
	rifle_mode->AddItem(XorStr("On Sight"));
	rifle_mode->SetCurrentItem(XorStr("On Fire"));
	rifle_mode->SetValue(&V::Legitbot_Rifle::Mode);
	legitbot_tab->Add(rifle_mode);

	auto rifle_target = new Combobox;
	rifle_target->SetPosition(25 + (groupbox * 145) + 16, 220);
	rifle_target->SetTitle(XorStr("Target Selection"));
	rifle_target->SetSize(137, 20);
	rifle_target->AddItem(XorStr("Crosshair Distance"));
	rifle_target->AddItem(XorStr("Player Distance"));
	rifle_target->AddItem(XorStr("Lowest HP"));
	rifle_target->AddItem(XorStr("Highest Threat"));
	rifle_target->SetCurrentItem(XorStr("Crosshair Distance"));
	rifle_target->SetValue(&V::Legitbot_Rifle::AimTarget);
	legitbot_tab->Add(rifle_target);

	auto rifle_hitbox = new Combobox;
	rifle_hitbox->SetPosition(25 + (groupbox * 145) + 16, 150);
	rifle_hitbox->SetTitle(XorStr("Hitbox"));
	rifle_hitbox->SetSize(137, 20);
	FillComboBox_Hitbox(rifle_hitbox);
	rifle_hitbox->SetValue(&V::Legitbot_Rifle::Hitbox);
	rifle_hitbox->SetCurrentItem(XorStr("Head"));
	legitbot_tab->Add(rifle_hitbox);

	// ===============================================================

	auto legitbot_sniper = new Groupbox;
	legitbot_sniper->SetPosition(20 + (++groupbox * 145) + 24, 108);
	legitbot_sniper->SetSize(147, 450);
	legitbot_sniper->SetTitle("Sniper");
	legitbot_tab->Add(legitbot_sniper);

	// Sniper ========================================================

	auto sniper_enable = new Checkbox;
	sniper_enable->SetPosition(25 + (groupbox * 145) + 24, 115);
	sniper_enable->SetTitle(XorStr("Enabled"));
	sniper_enable->SetValue(&V::Legitbot_Sniper::Enabled);
	legitbot_tab->Add(sniper_enable);

	auto sniper_key = new KeyReader;
	sniper_key->SetPosition(25 + (groupbox * 145) + 24, 185);
	sniper_key->SetTitle(XorStr("Key"));
	sniper_key->SetSize(137, 20);
	sniper_key->SetValue(&V::Legitbot_Sniper::AimKey);
	legitbot_tab->Add(sniper_key);

	auto sniper_ignoreteam = new Checkbox;
	sniper_ignoreteam->SetPosition(25 + (groupbox * 145) + 24, 245);
	sniper_ignoreteam->SetTitle(XorStr("Ignore Team"));
	sniper_ignoreteam->SetValue(&V::Legitbot_Sniper::IgnoreTeam);
	legitbot_tab->Add(sniper_ignoreteam);

	auto sniper_smartbone = new Checkbox;
	sniper_smartbone->SetPosition(25 + (groupbox * 145) + 24, 265);
	sniper_smartbone->SetTitle(XorStr("Smart Bone"));
	sniper_smartbone->SetValue(&V::Legitbot_Sniper::SmartHitbox);
	legitbot_tab->Add(sniper_smartbone);

	auto sniper_fov = new Slider;
	sniper_fov->SetPosition(25 + (groupbox * 145) + 24, 300);
	sniper_fov->SetTitle(XorStr("FOV Amount"));
	sniper_fov->SetValue(&V::Legitbot_Sniper::FOV);
	sniper_fov->SetSize(137, 7);
	sniper_fov->SetMin(0.f);
	sniper_fov->SetMax(90.f);
	legitbot_tab->Add(sniper_fov);

	auto sniper_smooth = new Checkbox;
	sniper_smooth->SetPosition(25 + (groupbox * 145) + 24, 325);
	sniper_smooth->SetTitle(XorStr("Smooth"));
	sniper_smooth->SetValue(&V::Legitbot_Sniper::EnableSmooth);
	legitbot_tab->Add(sniper_smooth);

	auto sniper_smooth_amount = new Slider;
	sniper_smooth_amount->SetPosition(25 + (groupbox * 145) + 24, 360);
	sniper_smooth_amount->SetTitle(XorStr("Smooth Amount"));
	sniper_smooth_amount->SetValue(&V::Legitbot_Sniper::Smooth);
	sniper_smooth_amount->SetSize(137, 7);
	sniper_smooth_amount->SetMin(0.f);
	sniper_smooth_amount->SetMax(25.f);
	legitbot_tab->Add(sniper_smooth_amount);

	auto sniper_smoke = new Checkbox;
	sniper_smoke->SetPosition(25 + (groupbox * 145) + 24, 420);
	sniper_smoke->SetTitle(XorStr("Smoke Check"));
	sniper_smoke->SetValue(&V::Legitbot_Sniper::SmokeCheck);
	legitbot_tab->Add(sniper_smoke);

	auto sniper_body = new Checkbox;
	sniper_body->SetPosition(25 + (groupbox * 145) + 24, 445);
	sniper_body->SetTitle(XorStr("Body AWP"));
	sniper_body->SetValue(&V::Legitbot_Sniper::BodyAim);
	legitbot_tab->Add(sniper_body);

	auto sniper_mode = new Combobox;
	sniper_mode->SetPosition(25 + (groupbox * 145) + 24, 390);
	sniper_mode->SetTitle(XorStr("Mode"));
	sniper_mode->SetSize(137, 20);
	sniper_mode->AddItem(XorStr("On Fire"));
	sniper_mode->AddItem(XorStr("On Key"));
	sniper_mode->AddItem(XorStr("On Sight"));
	sniper_mode->SetCurrentItem(XorStr("On Fire"));
	sniper_mode->SetValue(&V::Legitbot_Sniper::Mode);
	legitbot_tab->Add(sniper_mode);

	auto sniper_target = new Combobox;
	sniper_target->SetPosition(25 + (groupbox * 145) + 24, 220);
	sniper_target->SetTitle(XorStr("Target Selection"));
	sniper_target->SetSize(137, 20);
	sniper_target->AddItem(XorStr("Crosshair Distance"));
	sniper_target->AddItem(XorStr("Player Distance"));
	sniper_target->AddItem(XorStr("Lowest HP"));
	sniper_target->AddItem(XorStr("Highest Threat"));
	sniper_target->SetCurrentItem(XorStr("Crosshair Distance"));
	sniper_target->SetValue(&V::Legitbot_Sniper::AimTarget);
	legitbot_tab->Add(sniper_target);

	auto sniper_hitbox = new Combobox;
	sniper_hitbox->SetPosition(25 + (groupbox * 145) + 24, 150);
	sniper_hitbox->SetTitle(XorStr("Hitbox"));
	sniper_hitbox->SetSize(137, 20);
	FillComboBox_Hitbox(sniper_hitbox);
	sniper_hitbox->SetValue(&V::Legitbot_Sniper::Hitbox);
	sniper_hitbox->SetCurrentItem(XorStr("Head"));
	legitbot_tab->Add(sniper_hitbox);

	// ===============================================================

	auto legitbot_other = new Groupbox;
	legitbot_other->SetPosition(20 + (++groupbox * 145) + 32, 108);
	legitbot_other->SetSize(147, 450);
	legitbot_other->SetTitle(XorStr("Other"));
	legitbot_tab->Add(legitbot_other);

	// Other =========================================================

	auto other_enable = new Checkbox;
	other_enable->SetPosition(25 + (groupbox * 145) + 32, 115);
	other_enable->SetTitle(XorStr("Enabled"));
	other_enable->SetValue(&V::Legitbot_Other::Enabled);
	legitbot_tab->Add(other_enable);

	auto other_key = new KeyReader;
	other_key->SetPosition(25 + (groupbox * 145) + 32, 185);
	other_key->SetTitle(XorStr("Key"));
	other_key->SetSize(137, 20);
	other_key->SetValue(&V::Legitbot_Other::AimKey);
	legitbot_tab->Add(other_key);

	auto other_ignoreteam = new Checkbox;
	other_ignoreteam->SetPosition(25 + (groupbox * 145) + 32, 245);
	other_ignoreteam->SetTitle(XorStr("Ignore Team"));
	other_ignoreteam->SetValue(&V::Legitbot_Other::IgnoreTeam);
	legitbot_tab->Add(other_ignoreteam);

	auto other_smartbone = new Checkbox;
	other_smartbone->SetPosition(25 + (groupbox * 145) + 32, 265);
	other_smartbone->SetTitle(XorStr("Smart Bone"));
	other_smartbone->SetValue(&V::Legitbot_Other::SmartHitbox);
	legitbot_tab->Add(other_smartbone);

	auto other_fov = new Slider;
	other_fov->SetPosition(25 + (groupbox * 145) + 32, 300);
	other_fov->SetTitle(XorStr("FOV Amount"));
	other_fov->SetValue(&V::Legitbot_Other::FOV);
	other_fov->SetSize(137, 7);
	other_fov->SetMin(0.f);
	other_fov->SetMax(90.f);
	legitbot_tab->Add(other_fov);

	auto other_smooth = new Checkbox;
	other_smooth->SetPosition(25 + (groupbox * 145) + 32, 325);
	other_smooth->SetTitle(XorStr("Smooth"));
	other_smooth->SetValue(&V::Legitbot_Other::EnableSmooth);
	legitbot_tab->Add(other_smooth);

	auto other_smooth_amount = new Slider;
	other_smooth_amount->SetPosition(25 + (groupbox * 145) + 32, 360);
	other_smooth_amount->SetTitle(XorStr("Smooth Amount"));
	other_smooth_amount->SetValue(&V::Legitbot_Other::Smooth);
	other_smooth_amount->SetSize(137, 7);
	other_smooth_amount->SetMin(0.f);
	other_smooth_amount->SetMax(25.f);
	legitbot_tab->Add(other_smooth_amount);

	auto other_smoke = new Checkbox;
	other_smoke->SetPosition(25 + (groupbox * 145) + 32, 420);
	other_smoke->SetTitle(XorStr("Smoke Check"));
	other_smoke->SetValue(&V::Legitbot_Other::SmokeCheck);
	legitbot_tab->Add(other_smoke);

	auto other_mode = new Combobox;
	other_mode->SetPosition(25 + (groupbox * 145) + 32, 390);
	other_mode->SetTitle(XorStr("Mode"));
	other_mode->SetSize(137, 20);
	other_mode->AddItem(XorStr("On Fire"));
	other_mode->AddItem(XorStr("On Key"));
	other_mode->AddItem(XorStr("On Sight"));
	other_mode->SetCurrentItem(XorStr("On Fire"));
	other_mode->SetValue(&V::Legitbot_Other::Mode);
	legitbot_tab->Add(other_mode);

	auto other_target = new Combobox;
	other_target->SetPosition(25 + (groupbox * 145) + 32, 220);
	other_target->SetTitle(XorStr("Target Selection"));
	other_target->SetSize(137, 20);
	other_target->AddItem(XorStr("Crosshair Distance"));
	other_target->AddItem(XorStr("Player Distance"));
	other_target->AddItem(XorStr("Lowest HP"));
	other_target->AddItem(XorStr("Highest Threat"));
	other_target->SetCurrentItem(XorStr("Crosshair Distance"));
	other_target->SetValue(&V::Legitbot_Other::AimTarget);
	legitbot_tab->Add(other_target);

	auto other_hitbox = new Combobox;
	other_hitbox->SetPosition(25 + (groupbox * 145) + 32, 150);
	other_hitbox->SetTitle(XorStr("Hitbox"));
	other_hitbox->SetSize(137, 20);
	FillComboBox_Hitbox(other_hitbox);
	other_hitbox->SetValue(&V::Legitbot_Other::Hitbox);
	other_hitbox->SetCurrentItem(XorStr("Head"));
	legitbot_tab->Add(other_hitbox);

#pragma endregion

	// ===============================================================

	frame->Add(legitbot_tab);

	// ============================================================================

	auto ragebot_tab = new Tab;
	ragebot_tab->SetTab(++tab);
	ragebot_tab->SetTitle(XorStr("Rage"));

	// RAGEBOT ===================================================================

	auto ragebot_active = new Checkbox;
	ragebot_active->SetPosition(20, 68);
	ragebot_active->SetTitle(XorStr("Active"));
	ragebot_active->SetValue(&V::Ragebot::Active);
	ragebot_tab->Add(ragebot_active);

	groupbox = 0;

	// TODO: Continue XORing the menu!!! >://///

#pragma region RAGEBOT

	auto ragebot_settings = new Groupbox;
	ragebot_settings->SetPosition(20, 108);
	ragebot_settings->SetSize(145, 450);
	ragebot_settings->SetTitle(XorStr("Ragebot"));
	ragebot_tab->Add(ragebot_settings);

	// Ragebot ======================================================

	auto ragebot_enable = new Checkbox;
	ragebot_enable->SetPosition(25, 115);
	ragebot_enable->SetTitle(XorStr("Enabled"));
	ragebot_enable->SetValue(&V::Ragebot::Enabled);
	ragebot_tab->Add(ragebot_enable);

	auto ragebot_check_fov = new Checkbox;
	ragebot_check_fov->SetPosition(25, 135);
	ragebot_check_fov->SetTitle(XorStr("FOV Check"));
	ragebot_check_fov->SetValue(&V::Ragebot::CheckFOV);
	ragebot_tab->Add(ragebot_check_fov);

	auto ragebot_fov = new Slider;
	ragebot_fov->SetPosition(25, 170);
	ragebot_fov->SetTitle(XorStr("FOV Amount"));
	ragebot_fov->SetValue(&V::Ragebot::FOV);
	ragebot_fov->SetSize(137, 7);
	ragebot_fov->SetMin(0.f);
	ragebot_fov->SetMax(360.f);
	ragebot_tab->Add(ragebot_fov);

	auto ragebot_silent = new Checkbox;
	ragebot_silent->SetPosition(25, 200);
	ragebot_silent->SetTitle("Perfect Silent Aim");
	ragebot_silent->SetValue(&V::Ragebot::Silent);
	ragebot_tab->Add(ragebot_silent);

	auto ragebot_autopistols = new Checkbox;
	ragebot_autopistols->SetPosition(25, 220);
	ragebot_autopistols->SetTitle("Auto-Pistols");
	ragebot_autopistols->SetValue(&V::Ragebot::AutoPistols);
	ragebot_tab->Add(ragebot_autopistols);

	auto ragebot_autoaim = new Checkbox;
	ragebot_autoaim->SetPosition(25, 240);
	ragebot_autoaim->SetTitle("Auto-Aim");
	ragebot_autoaim->SetValue(&V::Ragebot::AutoAim);
	ragebot_tab->Add(ragebot_autoaim);

	auto ragebot_autoshoot = new Checkbox;
	ragebot_autoshoot->SetPosition(25, 260);
	ragebot_autoshoot->SetTitle("Auto-Shoot");
	ragebot_autoshoot->SetValue(&V::Ragebot::AutoShoot);
	ragebot_tab->Add(ragebot_autoshoot);

	auto ragebot_autostop = new Checkbox;
	ragebot_autostop->SetPosition(25, 280);
	ragebot_autostop->SetTitle("Auto-Stop");
	ragebot_autostop->SetValue(&V::Ragebot::AutoStop);
	ragebot_tab->Add(ragebot_autostop);

	auto ragebot_autoduck = new Checkbox;
	ragebot_autoduck->SetPosition(25, 300);
	ragebot_autoduck->SetTitle("Auto-Duck");
	ragebot_autoduck->SetValue(&V::Ragebot::AutoDuck);
	ragebot_tab->Add(ragebot_autoduck);

	auto ragebot_autoscope = new Checkbox;
	ragebot_autoscope->SetPosition(25, 320);
	ragebot_autoscope->SetTitle("Auto-Scope");
	ragebot_autoscope->SetValue(&V::Ragebot::AutoScope);
	ragebot_tab->Add(ragebot_autoscope);

	auto ragebot_hitscan = new Checkbox;
	ragebot_hitscan->SetPosition(25, 340);
	ragebot_hitscan->SetTitle("Hit-Scan");
	ragebot_hitscan->SetValue(&V::Ragebot::HitScan);
	ragebot_tab->Add(ragebot_hitscan);

	auto ragebot_drawspot = new Checkbox;
	ragebot_drawspot->SetPosition(25, 360);
	ragebot_drawspot->SetTitle("Draw HitSpot");
	ragebot_drawspot->SetValue(&V::Ragebot::DrawSpot);
	ragebot_tab->Add(ragebot_drawspot);

	// ===============================================================

	auto ragebot_target = new Groupbox;
	ragebot_target->SetPosition(20 + (++groupbox * 145) + 8, 108);
	ragebot_target->SetSize(145, 450);
	ragebot_target->SetTitle("Target");
	ragebot_tab->Add(ragebot_target);

	// Target ======================================================

	auto ragebot_ignoreteam = new Checkbox;
	ragebot_ignoreteam->SetPosition(25 + (groupbox * 145) + 8, 115);
	ragebot_ignoreteam->SetTitle("Ignore Team");
	ragebot_ignoreteam->SetValue(&V::Ragebot::IgnoreTeam);
	ragebot_tab->Add(ragebot_ignoreteam);

	auto ragebot_bodyawp = new Checkbox;
	ragebot_bodyawp->SetPosition(25 + (groupbox * 145) + 8, 210);
	ragebot_bodyawp->SetTitle("Body AWP");
	ragebot_bodyawp->SetValue(&V::Ragebot::BodyAWP);
	ragebot_tab->Add(ragebot_bodyawp);

	auto ragebot_legitchecks = new Checkbox;
	ragebot_legitchecks->SetPosition(25 + (groupbox * 145) + 8, 230);
	ragebot_legitchecks->SetTitle("Legit Checks");
	ragebot_legitchecks->SetValue(&V::Ragebot::LegitChecks);
	ragebot_tab->Add(ragebot_legitchecks);

	auto ragebot_autowall = new Checkbox;
	ragebot_autowall->SetPosition(25 + (groupbox * 145) + 8, 250);
	ragebot_autowall->SetTitle("Auto-Wall");
	ragebot_autowall->SetValue(&V::Ragebot::AutoWall);
	ragebot_tab->Add(ragebot_autowall);

	auto ragebot_autowalldamage = new Slider;
	ragebot_autowalldamage->SetPosition(25 + (groupbox * 145) + 8, 285);
	ragebot_autowalldamage->SetSize(137, 7);
	ragebot_autowalldamage->SetMin(0);
	ragebot_autowalldamage->SetMax(120);
	ragebot_autowalldamage->SetTitle("Auto-Wall Damage");
	ragebot_autowalldamage->SetValue(&V::Ragebot::AutoWall_Damage);
	ragebot_tab->Add(ragebot_autowalldamage);

	auto ragebot_multipoint = new Checkbox;
	ragebot_multipoint->SetPosition(25 + (groupbox * 145) + 8, 320);
	ragebot_multipoint->SetTitle("Multi-Point");
	ragebot_multipoint->SetValue(&V::Ragebot::MultiPoint);
	ragebot_tab->Add(ragebot_multipoint);

	auto ragebot_hitchance = new Checkbox;
	ragebot_hitchance->SetPosition(25 + (groupbox * 145) + 8, 340);
	ragebot_hitchance->SetTitle("Hit-Chance");
	ragebot_hitchance->SetValue(&V::Ragebot::HitChance);
	ragebot_tab->Add(ragebot_hitchance);

	auto ragebot_hitchance_amt = new Slider;
	ragebot_hitchance_amt->SetPosition(25 + (groupbox * 145) + 8, 370);
	ragebot_hitchance_amt->SetSize(137, 7);
	ragebot_hitchance_amt->SetMin(0);
	ragebot_hitchance_amt->SetMax(100);
	ragebot_hitchance_amt->SetTitle("HitChance Amount");
	ragebot_hitchance_amt->SetValue(&V::Ragebot::HitChance_Amount);
	ragebot_tab->Add(ragebot_hitchance_amt);

	auto ragebot_hitbox = new Combobox;
	ragebot_hitbox->SetPosition(25 + (groupbox * 145) + 8, 185);
	ragebot_hitbox->SetTitle("Hitbox");
	ragebot_hitbox->SetSize(137, 20);
	FillComboBox_Hitbox(ragebot_hitbox);
	ragebot_hitbox->SetValue(&V::Ragebot::Hitbox);
	ragebot_hitbox->SetCurrentItem("Head");
	ragebot_tab->Add(ragebot_hitbox);

	auto ragebot_target_mode = new Combobox;
	ragebot_target_mode->SetPosition(25 + (groupbox * 145) + 8, 150);
	ragebot_target_mode->SetTitle("Target Selection");
	ragebot_target_mode->SetSize(137, 20);
	ragebot_target_mode->AddItem("Crosshair Distance");
	ragebot_target_mode->AddItem("Player Distance");
	ragebot_target_mode->AddItem("Lowest HP");
	ragebot_target_mode->AddItem("Highest Threat");
	ragebot_target_mode->SetCurrentItem("Crosshair Distance");
	ragebot_target_mode->SetValue(&V::Ragebot::AimTarget);
	ragebot_tab->Add(ragebot_target_mode);

	// ===============================================================

	auto ragebot_chatbot = new Groupbox;
	ragebot_chatbot->SetPosition(20 + (++groupbox * 145) + 16, 108);
	ragebot_chatbot->SetSize(450, 450);
	ragebot_chatbot->SetTitle("Chatbot");
	ragebot_tab->Add(ragebot_chatbot);

	// Chatbot ======================================================

	auto chatbot_enabled = new Checkbox;
	chatbot_enabled->SetPosition(25 + (groupbox * 145) + 16, 115);
	chatbot_enabled->SetTitle(XorStr("Enabled"));
	chatbot_enabled->SetValue(&V::Chatbot::Enabled);
	ragebot_tab->Add(chatbot_enabled);

	auto chatbot_onkill = new Textbox;
	chatbot_onkill->SetPosition(25 + (groupbox * 145) + 16, 150);
	chatbot_onkill->SetSize(440, 20);
	chatbot_onkill->SetTitle("On Kill");
	chatbot_onkill->SetValue(const_cast<char*>(V::Chatbot::OnKill.c_str()));
	ragebot_tab->Add(chatbot_onkill);

	auto chatbot_ondeath = new Textbox;
	chatbot_ondeath->SetPosition(25 + (groupbox * 145) + 16, 185);
	chatbot_ondeath->SetSize(440, 20);
	chatbot_ondeath->SetTitle("On Death");
	chatbot_ondeath->SetValue(const_cast<char*>(V::Chatbot::OnDeath.c_str()));
	ragebot_tab->Add(chatbot_ondeath);

	auto chatbot_onplant = new Textbox;
	chatbot_onplant->SetPosition(25 + (groupbox * 145) + 16, 220);
	chatbot_onplant->SetSize(440, 20);
	chatbot_onplant->SetTitle("On Plant");
	chatbot_onplant->SetValue(const_cast<char*>(V::Chatbot::OnPlant.c_str()));
	ragebot_tab->Add(chatbot_onplant);

	auto chatbot_ondefuse = new Textbox;
	chatbot_ondefuse->SetPosition(25 + (groupbox * 145) + 16, 255);
	chatbot_ondefuse->SetSize(440, 20);
	chatbot_ondefuse->SetTitle("On Defuse");
	chatbot_ondefuse->SetValue(const_cast<char*>(V::Chatbot::OnDefuse.c_str()));
	ragebot_tab->Add(chatbot_ondefuse);

	auto chatbot_onroundstart = new Textbox;
	chatbot_onroundstart->SetPosition(25 + (groupbox * 145) + 16, 290);
	chatbot_onroundstart->SetSize(440, 20);
	chatbot_onroundstart->SetTitle("On Round Start");
	chatbot_onroundstart->SetValue(const_cast<char*>(V::Chatbot::OnRoundStart.c_str()));
	ragebot_tab->Add(chatbot_onroundstart);

	auto chatbot_onexplode = new Textbox;
	chatbot_onexplode->SetPosition(25 + (groupbox * 145) + 16, 325);
	chatbot_onexplode->SetSize(440, 20);
	chatbot_onexplode->SetTitle("On Explode");
	chatbot_onexplode->SetValue(const_cast<char*>(V::Chatbot::OnExplode.c_str()));
	ragebot_tab->Add(chatbot_onexplode);

	auto chatbot_spam = new Textbox;
	chatbot_spam->SetPosition(25 + (groupbox * 145) + 16, 360);
	chatbot_spam->SetSize(440, 20);
	chatbot_spam->SetTitle("Chat Spam Line");
	chatbot_spam->SetValue(const_cast<char*>(V::Chatbot::OnChatSpam.c_str()));
	ragebot_tab->Add(chatbot_spam);

#pragma endregion

	// ===============================================================

	frame->Add(ragebot_tab);

	// ============================================================================

	auto visuals_tab = new Tab;
	visuals_tab->SetTab(++tab);
	visuals_tab->SetTitle("Visuals");

	groupbox = 0;

	// VISUALS ===================================================================

	auto visuals_active = new Checkbox;
	visuals_active->SetPosition(20, 68);
	visuals_active->SetTitle("Active");
	visuals_active->SetValue(&V::Visuals::Active);
	visuals_tab->Add(visuals_active);

#pragma region VISUALS

	auto visuals_settings = new Groupbox;
	visuals_settings->SetPosition(20, 108);
	visuals_settings->SetSize(145, 450);
	visuals_settings->SetTitle("Wallhack");
	visuals_tab->Add(visuals_settings);

	// Settings ======================================================

	auto visuals_enabled = new Checkbox;
	visuals_enabled->SetPosition(25, 115);
	visuals_enabled->SetTitle(XorStr("Enabled"));
	visuals_enabled->SetValue(&V::Visuals::Enabled);
	visuals_tab->Add(visuals_enabled);

	auto visuals_fill = new Checkbox;
	visuals_fill->SetPosition(25, 260);
	visuals_fill->SetTitle("Filled Box");
	visuals_fill->SetValue(&V::Visuals::FillBox);
	visuals_tab->Add(visuals_fill);

	auto visuals_fill_alpha = new Slider;
	visuals_fill_alpha->SetPosition(25, 300);
	visuals_fill_alpha->SetTitle("Fill Alpha");
	visuals_fill_alpha->SetValue(&V::Visuals::FillBox_Alpha);
	visuals_fill_alpha->SetSize(137, 7);
	visuals_fill_alpha->SetMin(0.f);
	visuals_fill_alpha->SetMax(255.f);
	visuals_tab->Add(visuals_fill_alpha);

	auto visuals_glow = new Checkbox;
	visuals_glow->SetPosition(25, 335);
	visuals_glow->SetTitle("Glow");
	visuals_glow->SetValue(&V::Visuals::Glow);
	visuals_tab->Add(visuals_glow);

	auto visuals_glow_alpha = new Slider;
	visuals_glow_alpha->SetPosition(25, 375);
	visuals_glow_alpha->SetTitle("Glow Alpha");
	visuals_glow_alpha->SetValue(&V::Visuals::Glow_Alpha);
	visuals_glow_alpha->SetSize(137, 7);
	visuals_glow_alpha->SetMin(0.f);
	visuals_glow_alpha->SetMax(255.f);
	visuals_tab->Add(visuals_glow_alpha);

	auto visuals_enemyonly = new Checkbox;
	visuals_enemyonly->SetPosition(25, 410);
	visuals_enemyonly->SetTitle("Enemy Only");
	visuals_enemyonly->SetValue(&V::Visuals::EnemyOnly);
	visuals_tab->Add(visuals_enemyonly);

	auto visuals_visibleonly = new Checkbox;
	visuals_visibleonly->SetPosition(25, 430);
	visuals_visibleonly->SetTitle("Visible Only");
	visuals_visibleonly->SetValue(&V::Visuals::VisibleOnly);
	visuals_tab->Add(visuals_visibleonly);

	auto visuals_watermark = new Checkbox;
	visuals_watermark->SetPosition(25, 450);
	visuals_watermark->SetTitle("Show Watermark");
	visuals_watermark->SetValue(&V::Visuals::Watermark);
	visuals_tab->Add(visuals_watermark);

	auto visuals_dynamic = new Checkbox;
	visuals_dynamic->SetPosition(25, 470);
	visuals_dynamic->SetTitle("Dynamic Boxes");
	visuals_dynamic->SetValue(&V::Visuals::DynamicBox);
	visuals_tab->Add(visuals_dynamic);

	auto visuals_armorstyle = new Combobox;
	visuals_armorstyle->SetPosition(25, 230);
	visuals_armorstyle->SetTitle("Armorbar Style");
	visuals_armorstyle->SetSize(137, 20);
	visuals_armorstyle->AddItem("Bar Bottom");
	visuals_armorstyle->AddItem("Bar Left");
	visuals_armorstyle->AddItem("Bar Right");
	visuals_armorstyle->AddItem("Bar Upper");
	visuals_armorstyle->AddItem("Interwebz");
	visuals_armorstyle->SetCurrentItem("Bar Bottom");
	visuals_armorstyle->SetValue(&V::Visuals::ArmorType);
	visuals_tab->Add(visuals_armorstyle);

	auto visuals_healthstyle = new Combobox;
	visuals_healthstyle->SetPosition(25, 190);
	visuals_healthstyle->SetTitle("Healthbar Style");
	visuals_healthstyle->SetSize(137, 20);
	visuals_healthstyle->AddItem("Bar Bottom");
	visuals_healthstyle->AddItem("Bar Left");
	visuals_healthstyle->AddItem("Bar Right");
	visuals_healthstyle->AddItem("Bar Upper");
	visuals_healthstyle->AddItem("Interwebz");
	visuals_healthstyle->SetCurrentItem("Bar Left");
	visuals_healthstyle->SetValue(&V::Visuals::HealthType);
	visuals_tab->Add(visuals_healthstyle);

	auto visuals_mode = new Combobox;
	visuals_mode->SetPosition(25, 150);
	visuals_mode->SetTitle("Box Style");
	visuals_mode->SetSize(137, 20);
	visuals_mode->AddItem("Normal");
	visuals_mode->AddItem("Corner");
	visuals_mode->AddItem("3D");
	visuals_mode->SetCurrentItem("Normal");
	visuals_mode->SetValue(&V::Visuals::BoxType);
	visuals_tab->Add(visuals_mode);

	// ===============================================================

	auto visuals_esp = new Groupbox;
	visuals_esp->SetPosition(20 + (++groupbox * 145) + 8, 108);
	visuals_esp->SetSize(145, 450);
	visuals_esp->SetTitle("ESP Settings");
	visuals_tab->Add(visuals_esp);

	// ESP Settings ======================================================

	auto visuals_radar = new Checkbox;
	visuals_radar->SetPosition(25 + (groupbox * 145) + 8, 115);
	visuals_radar->SetTitle("External Radar");
	visuals_radar->SetValue(&V::Visuals::ExternalRadar);
	visuals_tab->Add(visuals_radar);

	auto visuals_radar_rotate = new Checkbox;
	visuals_radar_rotate->SetPosition(25 + (groupbox * 145) + 8, 135);
	visuals_radar_rotate->SetTitle("Radar Rotation");
	visuals_radar_rotate->SetValue(&V::Visuals::RadarRotation);
	visuals_tab->Add(visuals_radar_rotate);

	auto visuals_head = new Checkbox;
	visuals_head->SetPosition(25 + (groupbox * 145) + 8, 155);
	visuals_head->SetTitle("Head Dot");
	visuals_head->SetValue(&V::Visuals::HeadDot);
	visuals_tab->Add(visuals_head);

	auto visuals_name = new Checkbox;
	visuals_name->SetPosition(25 + (groupbox * 145) + 8, 175);
	visuals_name->SetTitle("Show Name");
	visuals_name->SetValue(&V::Visuals::Name);
	visuals_tab->Add(visuals_name);

	auto visuals_health = new Checkbox;
	visuals_health->SetPosition(25 + (groupbox * 145) + 8, 195);
	visuals_health->SetTitle("Show Health");
	visuals_health->SetValue(&V::Visuals::Health);
	visuals_tab->Add(visuals_health);

	auto visuals_armor = new Checkbox;
	visuals_armor->SetPosition(25 + (groupbox * 145) + 8, 215);
	visuals_armor->SetTitle("Show Armor");
	visuals_armor->SetValue(&V::Visuals::Armor);
	visuals_tab->Add(visuals_armor);

	auto visuals_wins = new Checkbox;
	visuals_wins->SetPosition(25 + (groupbox * 145) + 8, 235);
	visuals_wins->SetTitle("Show MM Wins");
	visuals_wins->SetValue(&V::Visuals::Wins);
	visuals_tab->Add(visuals_wins);

	auto visuals_rank = new Checkbox;
	visuals_rank->SetPosition(25 + (groupbox * 145) + 8, 255);
	visuals_rank->SetTitle("Show MM Rank");
	visuals_rank->SetValue(&V::Visuals::Rank);
	visuals_tab->Add(visuals_rank);

	auto visuals_weapon = new Checkbox;
	visuals_weapon->SetPosition(25 + (groupbox * 145) + 8, 275);
	visuals_weapon->SetTitle("Show Weapon");
	visuals_weapon->SetValue(&V::Visuals::Weapon);
	visuals_tab->Add(visuals_weapon);

	auto visuals_defusing = new Checkbox;
	visuals_defusing->SetPosition(25 + (groupbox * 145) + 8, 295);
	visuals_defusing->SetTitle("Show Defusing");
	visuals_defusing->SetValue(&V::Visuals::Defusing);
	visuals_tab->Add(visuals_defusing);

	auto visuals_flashed = new Checkbox;
	visuals_flashed->SetPosition(25 + (groupbox * 145) + 8, 315);
	visuals_flashed->SetTitle("Show Flashed");
	visuals_flashed->SetValue(&V::Visuals::Flashed);
	visuals_tab->Add(visuals_flashed);

	auto visuals_chicken = new Checkbox;
	visuals_chicken->SetPosition(25 + (groupbox * 145) + 8, 335);
	visuals_chicken->SetTitle("Chicken ESP");
	visuals_chicken->SetValue(&V::Visuals::Chicken);
	visuals_tab->Add(visuals_chicken);

	auto visuals_bomb = new Checkbox;
	visuals_bomb->SetPosition(25 + (groupbox * 145) + 8, 355);
	visuals_bomb->SetTitle("Bomb ESP");
	visuals_bomb->SetValue(&V::Visuals::Bomb);
	visuals_tab->Add(visuals_bomb);

	auto visuals_scoreboard_rank = new Checkbox;
	visuals_scoreboard_rank->SetPosition(25 + (groupbox * 145) + 8, 375);
	visuals_scoreboard_rank->SetTitle("Reveal Ranks");
	visuals_scoreboard_rank->SetValue(&V::Visuals::ScoreboardRank);
	visuals_tab->Add(visuals_scoreboard_rank);

	auto visuals_recoil = new Checkbox;
	visuals_recoil->SetPosition(25 + (groupbox * 145) + 8, 395);
	visuals_recoil->SetTitle("Recoil Crosshair");
	visuals_recoil->SetValue(&V::Visuals::RecoilCrosshair);
	visuals_tab->Add(visuals_recoil);

	auto visuals_spread = new Checkbox;
	visuals_spread->SetPosition(25 + (groupbox * 145) + 8, 415);
	visuals_spread->SetTitle("Spread Crosshair");
	visuals_spread->SetValue(&V::Visuals::SpreadCrosshair);
	visuals_tab->Add(visuals_spread);

	auto visuals_outline = new Checkbox;
	visuals_outline->SetPosition(25 + (groupbox * 145) + 8, 435);
	visuals_outline->SetTitle("Outline");
	visuals_outline->SetValue(&V::Visuals::Outline);
	visuals_tab->Add(visuals_outline);

	auto visuals_weaponesp = new Checkbox;
	visuals_weaponesp->SetPosition(25 + (groupbox * 145) + 8, 455);
	visuals_weaponesp->SetTitle("Weapon ESP");
	visuals_weaponesp->SetValue(&V::Visuals::WeaponESP);
	visuals_tab->Add(visuals_weaponesp);

	auto visuals_bones = new Checkbox;
	visuals_bones->SetPosition(25 + (groupbox * 145) + 8, 475);
	visuals_bones->SetTitle("Bone ESP");
	visuals_bones->SetValue(&V::Visuals::BoneESP);
	visuals_tab->Add(visuals_bones);

	auto visuals_hitboxes = new Checkbox;
	visuals_hitboxes->SetPosition(25 + (groupbox * 145) + 8, 495);
	visuals_hitboxes->SetTitle("Hitbox ESP");
	visuals_hitboxes->SetValue(&V::Visuals::HitboxESP);
	visuals_tab->Add(visuals_hitboxes);

	auto visuals_bullettracer = new Checkbox;
	visuals_bullettracer->SetPosition(25 + (groupbox * 145) + 8, 515);
	visuals_bullettracer->SetTitle("Bullet Tracer");
	visuals_bullettracer->SetValue(&V::Visuals::BulletTracer);
	visuals_tab->Add(visuals_bullettracer);

	auto visuals_nadetracer = new Checkbox;
	visuals_nadetracer->SetPosition(25 + (groupbox * 145) + 8, 535);
	visuals_nadetracer->SetTitle("Grenade Tracer");
	visuals_nadetracer->SetValue(&V::Visuals::GrenadeTracer);
	visuals_tab->Add(visuals_nadetracer);

	// ===============================================================

	auto visuals_chams = new Groupbox;
	visuals_chams->SetPosition(20 + (++groupbox * 145) + 16, 108);
	visuals_chams->SetSize(145, 450);
	visuals_chams->SetTitle("Chams");
	visuals_tab->Add(visuals_chams);

	// Chams ======================================================

	auto visuals_chams_enabled = new Checkbox;
	visuals_chams_enabled->SetPosition(25 + (groupbox * 145) + 16, 115);
	visuals_chams_enabled->SetTitle(XorStr("Enabled"));
	visuals_chams_enabled->SetValue(&V::Chams::Enabled);
	visuals_tab->Add(visuals_chams_enabled);

	auto visuals_chams_visible = new Checkbox;
	visuals_chams_visible->SetPosition(25 + (groupbox * 145) + 16, 135);
	visuals_chams_visible->SetTitle("Visible Only");
	visuals_chams_visible->SetValue(&V::Chams::VisibleOnly);
	visuals_tab->Add(visuals_chams_visible);

	auto visuals_chams_enemy = new Checkbox;
	visuals_chams_enemy->SetPosition(25 + (groupbox * 145) + 16, 155);
	visuals_chams_enemy->SetTitle("Enemy Only");
	visuals_chams_enemy->SetValue(&V::Chams::EnemyOnly);
	visuals_tab->Add(visuals_chams_enemy);

	auto visuals_chams_xqz = new Checkbox;
	visuals_chams_xqz->SetPosition(25 + (groupbox * 145) + 16, 175);
	visuals_chams_xqz->SetTitle("XQZ Chams");
	visuals_chams_xqz->SetValue(&V::Chams::XQZ);
	visuals_tab->Add(visuals_chams_xqz);

	auto visuals_chams_hands = new Checkbox;
	visuals_chams_hands->SetPosition(25 + (groupbox * 145) + 16, 195);
	visuals_chams_hands->SetTitle("Hand Chams");
	visuals_chams_hands->SetValue(&V::Chams::Hands);
	visuals_tab->Add(visuals_chams_hands);

	auto visuals_chams_weapons = new Checkbox;
	visuals_chams_weapons->SetPosition(25 + (groupbox * 145) + 16, 215);
	visuals_chams_weapons->SetTitle("Weapon Chams");
	visuals_chams_weapons->SetValue(&V::Chams::Weapons);
	visuals_tab->Add(visuals_chams_weapons);

	auto visuals_chams_mode_weapons = new Combobox;
	visuals_chams_mode_weapons->SetPosition(25 + (groupbox * 145) + 16, 320);
	visuals_chams_mode_weapons->SetTitle("Weapon Chams Style");
	visuals_chams_mode_weapons->SetSize(137, 20);
	visuals_chams_mode_weapons->AddItem("Textured");
	visuals_chams_mode_weapons->AddItem("Wireframe");
	visuals_chams_mode_weapons->AddItem("Flat");
	visuals_chams_mode_weapons->SetCurrentItem("Textured");
	visuals_chams_mode_weapons->SetValue(&V::Chams::Type_Weapons);
	visuals_tab->Add(visuals_chams_mode_weapons);

	auto visuals_chams_mode_hands = new Combobox;
	visuals_chams_mode_hands->SetPosition(25 + (groupbox * 145) + 16, 285);
	visuals_chams_mode_hands->SetTitle("Hand Chams Style");
	visuals_chams_mode_hands->SetSize(137, 20);
	visuals_chams_mode_hands->AddItem("Textured");
	visuals_chams_mode_hands->AddItem("Wireframe");
	visuals_chams_mode_hands->AddItem("Flat");
	visuals_chams_mode_hands->SetCurrentItem("Textured");
	visuals_chams_mode_hands->SetValue(&V::Chams::Type_Hands);
	visuals_tab->Add(visuals_chams_mode_hands);

	auto visuals_chams_mode = new Combobox;
	visuals_chams_mode->SetPosition(25 + (groupbox * 145) + 16, 250);
	visuals_chams_mode->SetTitle("Chams Style");
	visuals_chams_mode->SetSize(137, 20);
	visuals_chams_mode->AddItem("Textured");
	visuals_chams_mode->AddItem("Wireframe");
	visuals_chams_mode->AddItem("Flat");
	visuals_chams_mode->SetCurrentItem("Textured");
	visuals_chams_mode->SetValue(&V::Chams::Type);
	visuals_tab->Add(visuals_chams_mode);

	// ===============================================================

	auto visuals_removals = new Groupbox;
	visuals_removals->SetPosition(20 + (++groupbox * 145) + 24, 108);
	visuals_removals->SetSize(145, 450);
	visuals_removals->SetTitle("Removals");
	visuals_tab->Add(visuals_removals);

	// Removals ======================================================

	auto visuals_removals_noflash = new Checkbox;
	visuals_removals_noflash->SetPosition(25 + (groupbox * 145) + 24, 115);
	visuals_removals_noflash->SetTitle("No Flash");
	visuals_removals_noflash->SetValue(&V::Removals::NoFlash);
	visuals_tab->Add(visuals_removals_noflash);

	auto visuals_removals_nosmoke = new Checkbox;
	visuals_removals_nosmoke->SetPosition(25 + (groupbox * 145) + 24, 135);
	visuals_removals_nosmoke->SetTitle("No Smoke");
	visuals_removals_nosmoke->SetValue(&V::Removals::NoSmoke);
	visuals_tab->Add(visuals_removals_nosmoke);

	auto visuals_removals_nohands = new Checkbox;
	visuals_removals_nohands->SetPosition(25 + (groupbox * 145) + 24, 155);
	visuals_removals_nohands->SetTitle("No Hands");
	visuals_removals_nohands->SetValue(&V::Removals::NoHands);
	visuals_tab->Add(visuals_removals_nohands);

	auto visuals_removals_noweapons = new Checkbox;
	visuals_removals_noweapons->SetPosition(25 + (groupbox * 145) + 24, 175);
	visuals_removals_noweapons->SetTitle("No Weapons");
	visuals_removals_noweapons->SetValue(&V::Removals::NoWeapons);
	visuals_tab->Add(visuals_removals_noweapons);

	auto visuals_removals_novisrecoil = new Checkbox;
	visuals_removals_novisrecoil->SetPosition(25 + (groupbox * 145) + 24, 195);
	visuals_removals_novisrecoil->SetTitle("No Visual Recoil");
	visuals_removals_novisrecoil->SetValue(&V::Removals::NoVisualRecoil);
	visuals_tab->Add(visuals_removals_novisrecoil);

	auto visuals_removals_sky = new Checkbox;
	visuals_removals_sky->SetPosition(25 + (groupbox * 145) + 24, 215);
	visuals_removals_sky->SetTitle("No Sky");
	visuals_removals_sky->SetValue(&V::Removals::NoSky);
	visuals_tab->Add(visuals_removals_sky);

	auto visuals_removals_asus = new Checkbox;
	visuals_removals_asus->SetPosition(25 + (groupbox * 145) + 24, 235);
	visuals_removals_asus->SetTitle("ASUS Walls");
	visuals_removals_asus->SetValue(&V::Removals::AsusWalls);
	visuals_tab->Add(visuals_removals_asus);

	auto visuals_removals_asus_amount = new Slider;
	visuals_removals_asus_amount->SetPosition(25 + (groupbox * 145) + 24, 275);
	visuals_removals_asus_amount->SetTitle("ASUS Alpha");
	visuals_removals_asus_amount->SetSize(137, 7);
	visuals_removals_asus_amount->SetValue(&V::Removals::AsusAlpha);
	visuals_tab->Add(visuals_removals_asus_amount);

#pragma endregion

	// ===============================================================

	frame->Add(visuals_tab);

	// ============================================================================

	auto trigger_tab = new Tab;
	trigger_tab->SetTab(++tab);
	trigger_tab->SetTitle("Triggerbot");
	groupbox = 0;

	// TRIGGER ====================================================================

	auto trigger_active = new Checkbox;
	trigger_active->SetPosition(20, 68);
	trigger_active->SetTitle("Active");
	trigger_active->SetValue(&V::Triggerbot::Active);
	trigger_tab->Add(trigger_active);

#pragma region TRIGGER

	auto trigger_settings = new Groupbox;
	trigger_settings->SetPosition(20, 108);
	trigger_settings->SetSize(145, 450);
	trigger_settings->SetTitle("Settings");
	trigger_tab->Add(trigger_settings);

	// Settings ======================================================

	auto trigger_enabled = new Checkbox;
	trigger_enabled->SetPosition(25, 115);
	trigger_enabled->SetTitle(XorStr("Enabled"));
	trigger_enabled->SetValue(&V::Triggerbot::Enabled);
	trigger_tab->Add(trigger_enabled);

	auto trigger_usekey = new Checkbox;
	trigger_usekey->SetPosition(25, 135);
	trigger_usekey->SetTitle("Use Key");
	trigger_usekey->SetValue(&V::Triggerbot::UseKey);
	trigger_tab->Add(trigger_usekey);

	auto trigger_key = new KeyReader;
	trigger_key->SetPosition(25, 170);
	trigger_key->SetSize(137, 20);
	trigger_key->SetTitle("Trigger Key");
	trigger_key->SetValue(&V::Triggerbot::TriggerKey);
	trigger_tab->Add(trigger_key);

	auto trigger_filter = new Checkbox;
	trigger_filter->SetPosition(25, 195);
	trigger_filter->SetTitle("Hitgroup Filter");
	trigger_filter->SetValue(&V::Triggerbot::Filter);
	trigger_tab->Add(trigger_filter);

	auto trigger_hitchance_enable = new Checkbox;
	trigger_hitchance_enable->SetPosition(25, 255);
	trigger_hitchance_enable->SetTitle("Hitchance");
	trigger_hitchance_enable->SetValue(&V::Triggerbot::EnableHitchance);
	trigger_tab->Add(trigger_hitchance_enable);

	auto trigger_hitchance = new Slider;
	trigger_hitchance->SetPosition(25, 290);
	trigger_hitchance->SetTitle("Hitchance Amount");
	trigger_hitchance->SetValue(&V::Triggerbot::Hitchance);
	trigger_hitchance->SetSize(137, 7);
	trigger_hitchance->SetMin(0.f);
	trigger_hitchance->SetMax(100.f);
	trigger_tab->Add(trigger_hitchance);

	auto trigger_ignoreteam = new Checkbox;
	trigger_ignoreteam->SetPosition(25, 315);
	trigger_ignoreteam->SetTitle("Ignore Team");
	trigger_ignoreteam->SetValue(&V::Triggerbot::IgnoreTeam);
	trigger_tab->Add(trigger_ignoreteam);

	auto trigger_smoke = new Checkbox;
	trigger_smoke->SetPosition(25, 335);
	trigger_smoke->SetTitle("Smoke Check");
	trigger_smoke->SetValue(&V::Triggerbot::SmokeCheck);
	trigger_tab->Add(trigger_smoke);

	auto trigger_delay = new Checkbox;
	trigger_delay->SetPosition(25, 355);
	trigger_delay->SetTitle("Use Delay");
	trigger_delay->SetValue(&V::Triggerbot::UseDelay);
	trigger_tab->Add(trigger_delay);

	auto trigger_delay_amount = new Slider;
	trigger_delay_amount->SetPosition(25, 390);
	trigger_delay_amount->SetTitle("Delay Amount");
	trigger_delay_amount->SetValue(&V::Triggerbot::Delay);
	trigger_delay_amount->SetSize(137, 7);
	trigger_delay_amount->SetMin(0.f);
	trigger_delay_amount->SetMax(100.f);
	trigger_tab->Add(trigger_delay_amount);

	auto trigger_weapongroups = new Checkbox;
	trigger_weapongroups->SetPosition(25, 420);
	trigger_weapongroups->SetTitle("Use WeaponGroups");
	trigger_weapongroups->SetValue(&V::Triggerbot::WeaponGroups);
	trigger_tab->Add(trigger_weapongroups);

	auto trigger_hitgroup = new Combobox;
	trigger_hitgroup->SetPosition(25, 230);
	trigger_hitgroup->SetTitle("Hitgroup");
	trigger_hitgroup->SetSize(137, 20);
	trigger_hitgroup->AddItem("Head");
	trigger_hitgroup->AddItem("Chest");
	trigger_hitgroup->AddItem("Stomach");
	trigger_hitgroup->AddItem("Arms");
	trigger_hitgroup->AddItem("Legs");
	trigger_hitgroup->SetCurrentItem("Head");
	trigger_hitgroup->SetValue(&V::Triggerbot::Hitgroup);
	trigger_tab->Add(trigger_hitgroup);

	// ===============================================================

	auto trigger_pistol = new Groupbox;
	trigger_pistol->SetPosition(20 + (++groupbox * 145) + 8, 108);
	trigger_pistol->SetSize(145, 450);
	trigger_pistol->SetTitle("Pistol");
	trigger_tab->Add(trigger_pistol);

	// Pistol ======================================================

	auto trigger_pistol_enabled = new Checkbox;
	trigger_pistol_enabled->SetPosition(25 + (groupbox * 145) + 8, 115);
	trigger_pistol_enabled->SetTitle(XorStr("Enabled"));
	trigger_pistol_enabled->SetValue(&V::Triggerbot_Pistol::Enabled);
	trigger_tab->Add(trigger_pistol_enabled);

	auto trigger_pistol_usekey = new Checkbox;
	trigger_pistol_usekey->SetPosition(25 + (groupbox * 145) + 8, 135);
	trigger_pistol_usekey->SetTitle("Use Key");
	trigger_pistol_usekey->SetValue(&V::Triggerbot_Pistol::UseKey);
	trigger_tab->Add(trigger_pistol_usekey);

	auto trigger_pistol_key = new KeyReader;
	trigger_pistol_key->SetPosition(25 + (groupbox * 145) + 8, 170);
	trigger_pistol_key->SetSize(137, 20);
	trigger_pistol_key->SetTitle("Trigger Key");
	trigger_pistol_key->SetValue(&V::Triggerbot_Pistol::TriggerKey);
	trigger_tab->Add(trigger_pistol_key);

	auto trigger_pistol_filter = new Checkbox;
	trigger_pistol_filter->SetPosition(25 + (groupbox * 145) + 8, 195);
	trigger_pistol_filter->SetTitle("Hitgroup Filter");
	trigger_pistol_filter->SetValue(&V::Triggerbot_Pistol::Filter);
	trigger_tab->Add(trigger_pistol_filter);

	auto trigger_pistol_hitchance_enable = new Checkbox;
	trigger_pistol_hitchance_enable->SetPosition(25 + (groupbox * 145) + 8, 25 + (groupbox * 145) + 85);
	trigger_pistol_hitchance_enable->SetTitle("Hitchance");
	trigger_pistol_hitchance_enable->SetValue(&V::Triggerbot_Pistol::EnableHitchance);
	trigger_tab->Add(trigger_pistol_hitchance_enable);

	auto trigger_pistol_hitchance = new Slider;
	trigger_pistol_hitchance->SetPosition(25 + (groupbox * 145) + 8, 290);
	trigger_pistol_hitchance->SetTitle("Hitchance Amount");
	trigger_pistol_hitchance->SetValue(&V::Triggerbot_Pistol::Hitchance);
	trigger_pistol_hitchance->SetSize(137, 7);
	trigger_pistol_hitchance->SetMin(0.f);
	trigger_pistol_hitchance->SetMax(100.f);
	trigger_tab->Add(trigger_pistol_hitchance);

	auto trigger_pistol_ignoreteam = new Checkbox;
	trigger_pistol_ignoreteam->SetPosition(25 + (groupbox * 145) + 8, 315);
	trigger_pistol_ignoreteam->SetTitle("Ignore Team");
	trigger_pistol_ignoreteam->SetValue(&V::Triggerbot_Pistol::IgnoreTeam);
	trigger_tab->Add(trigger_pistol_ignoreteam);

	auto trigger_pistol_smoke = new Checkbox;
	trigger_pistol_smoke->SetPosition(25 + (groupbox * 145) + 8, 335);
	trigger_pistol_smoke->SetTitle("Smoke Check");
	trigger_pistol_smoke->SetValue(&V::Triggerbot_Pistol::SmokeCheck);
	trigger_tab->Add(trigger_pistol_smoke);

	auto trigger_pistol_delay = new Checkbox;
	trigger_pistol_delay->SetPosition(25 + (groupbox * 145) + 8, 355);
	trigger_pistol_delay->SetTitle("Use Delay");
	trigger_pistol_delay->SetValue(&V::Triggerbot_Pistol::UseDelay);
	trigger_tab->Add(trigger_pistol_delay);

	auto trigger_pistol_delay_amount = new Slider;
	trigger_pistol_delay_amount->SetPosition(25 + (groupbox * 145) + 8, 390);
	trigger_pistol_delay_amount->SetTitle("Delay Amount");
	trigger_pistol_delay_amount->SetValue(&V::Triggerbot_Pistol::Delay);
	trigger_pistol_delay_amount->SetSize(137, 7);
	trigger_pistol_delay_amount->SetMin(0.f);
	trigger_pistol_delay_amount->SetMax(100.f);
	trigger_tab->Add(trigger_pistol_delay_amount);

	auto trigger_pistol_hitgroup = new Combobox;
	trigger_pistol_hitgroup->SetPosition(25 + (groupbox * 145) + 8, 230);
	trigger_pistol_hitgroup->SetTitle("Hitgroup");
	trigger_pistol_hitgroup->SetSize(137, 20);
	trigger_pistol_hitgroup->AddItem("Head");
	trigger_pistol_hitgroup->AddItem("Chest");
	trigger_pistol_hitgroup->AddItem("Stomach");
	trigger_pistol_hitgroup->AddItem("Arms");
	trigger_pistol_hitgroup->AddItem("Legs");
	trigger_pistol_hitgroup->SetCurrentItem("Head");
	trigger_pistol_hitgroup->SetValue(&V::Triggerbot_Pistol::Hitgroup);
	trigger_tab->Add(trigger_pistol_hitgroup);

	// ===============================================================

	auto trigger_rifle = new Groupbox;
	trigger_rifle->SetPosition(20 + (++groupbox * 145) + 16, 108);
	trigger_rifle->SetSize(145, 450);
	trigger_rifle->SetTitle("Rifle");
	trigger_tab->Add(trigger_rifle);

	// Rifle ======================================================

	auto trigger_rifle_enabled = new Checkbox;
	trigger_rifle_enabled->SetPosition(25 + (groupbox * 145) + 16, 115);
	trigger_rifle_enabled->SetTitle(XorStr("Enabled"));
	trigger_rifle_enabled->SetValue(&V::Triggerbot_Rifle::Enabled);
	trigger_tab->Add(trigger_rifle_enabled);

	auto trigger_rifle_usekey = new Checkbox;
	trigger_rifle_usekey->SetPosition(25 + (groupbox * 145) + 16, 135);
	trigger_rifle_usekey->SetTitle("Use Key");
	trigger_rifle_usekey->SetValue(&V::Triggerbot_Rifle::UseKey);
	trigger_tab->Add(trigger_rifle_usekey);

	auto trigger_rifle_key = new KeyReader;
	trigger_rifle_key->SetPosition(25 + (groupbox * 145) + 16, 170);
	trigger_rifle_key->SetSize(137, 20);
	trigger_rifle_key->SetTitle("Trigger Key");
	trigger_rifle_key->SetValue(&V::Triggerbot_Rifle::TriggerKey);
	trigger_tab->Add(trigger_rifle_key);

	auto trigger_rifle_filter = new Checkbox;
	trigger_rifle_filter->SetPosition(25 + (groupbox * 145) + 16, 195);
	trigger_rifle_filter->SetTitle("Hitgroup Filter");
	trigger_rifle_filter->SetValue(&V::Triggerbot_Rifle::Filter);
	trigger_tab->Add(trigger_rifle_filter);

	auto trigger_rifle_hitchance_enable = new Checkbox;
	trigger_rifle_hitchance_enable->SetPosition(25 + (groupbox * 145) + 16, 25 + (1 * 145) + 85);
	trigger_rifle_hitchance_enable->SetTitle("Hitchance");
	trigger_rifle_hitchance_enable->SetValue(&V::Triggerbot_Rifle::EnableHitchance);
	trigger_tab->Add(trigger_rifle_hitchance_enable);

	auto trigger_rifle_hitchance = new Slider;
	trigger_rifle_hitchance->SetPosition(25 + (groupbox * 145) + 16, 290);
	trigger_rifle_hitchance->SetTitle("Hitchance Amount");
	trigger_rifle_hitchance->SetValue(&V::Triggerbot_Rifle::Hitchance);
	trigger_rifle_hitchance->SetSize(137, 7);
	trigger_rifle_hitchance->SetMin(0.f);
	trigger_rifle_hitchance->SetMax(100.f);
	trigger_tab->Add(trigger_rifle_hitchance);

	auto trigger_rifle_ignoreteam = new Checkbox;
	trigger_rifle_ignoreteam->SetPosition(25 + (groupbox * 145) + 16, 315);
	trigger_rifle_ignoreteam->SetTitle("Ignore Team");
	trigger_rifle_ignoreteam->SetValue(&V::Triggerbot_Rifle::IgnoreTeam);
	trigger_tab->Add(trigger_rifle_ignoreteam);

	auto trigger_rifle_smoke = new Checkbox;
	trigger_rifle_smoke->SetPosition(25 + (groupbox * 145) + 16, 335);
	trigger_rifle_smoke->SetTitle("Smoke Check");
	trigger_rifle_smoke->SetValue(&V::Triggerbot_Rifle::SmokeCheck);
	trigger_tab->Add(trigger_rifle_smoke);

	auto trigger_rifle_delay = new Checkbox;
	trigger_rifle_delay->SetPosition(25 + (groupbox * 145) + 16, 355);
	trigger_rifle_delay->SetTitle("Use Delay");
	trigger_rifle_delay->SetValue(&V::Triggerbot_Rifle::UseDelay);
	trigger_tab->Add(trigger_rifle_delay);

	auto trigger_rifle_delay_amount = new Slider;
	trigger_rifle_delay_amount->SetPosition(25 + (groupbox * 145) + 16, 390);
	trigger_rifle_delay_amount->SetTitle("Delay Amount");
	trigger_rifle_delay_amount->SetValue(&V::Triggerbot_Rifle::Delay);
	trigger_rifle_delay_amount->SetSize(137, 7);
	trigger_rifle_delay_amount->SetMin(0.f);
	trigger_rifle_delay_amount->SetMax(100.f);
	trigger_tab->Add(trigger_rifle_delay_amount);

	auto trigger_rifle_hitgroup = new Combobox;
	trigger_rifle_hitgroup->SetPosition(25 + (groupbox * 145) + 16, 230);
	trigger_rifle_hitgroup->SetTitle("Hitgroup");
	trigger_rifle_hitgroup->SetSize(137, 20);
	trigger_rifle_hitgroup->AddItem("Head");
	trigger_rifle_hitgroup->AddItem("Chest");
	trigger_rifle_hitgroup->AddItem("Stomach");
	trigger_rifle_hitgroup->AddItem("Arms");
	trigger_rifle_hitgroup->AddItem("Legs");
	trigger_rifle_hitgroup->SetCurrentItem("Head");
	trigger_rifle_hitgroup->SetValue(&V::Triggerbot_Rifle::Hitgroup);
	trigger_tab->Add(trigger_rifle_hitgroup);

	// ===============================================================

	auto trigger_sniper = new Groupbox;
	trigger_sniper->SetPosition(20 + (++groupbox * 145) + 24, 108);
	trigger_sniper->SetSize(145, 450);
	trigger_sniper->SetTitle("Sniper");
	trigger_tab->Add(trigger_sniper);

	// Sniper ======================================================

	auto trigger_sniper_enabled = new Checkbox;
	trigger_sniper_enabled->SetPosition(25 + (groupbox * 145) + 24, 115);
	trigger_sniper_enabled->SetTitle(XorStr("Enabled"));
	trigger_sniper_enabled->SetValue(&V::Triggerbot_Sniper::Enabled);
	trigger_tab->Add(trigger_sniper_enabled);

	auto trigger_sniper_usekey = new Checkbox;
	trigger_sniper_usekey->SetPosition(25 + (groupbox * 145) + 24, 135);
	trigger_sniper_usekey->SetTitle("Use Key");
	trigger_sniper_usekey->SetValue(&V::Triggerbot_Sniper::UseKey);
	trigger_tab->Add(trigger_sniper_usekey);

	auto trigger_sniper_key = new KeyReader;
	trigger_sniper_key->SetPosition(25 + (groupbox * 145) + 24, 170);
	trigger_sniper_key->SetSize(137, 20);
	trigger_sniper_key->SetTitle("Trigger Key");
	trigger_sniper_key->SetValue(&V::Triggerbot_Sniper::TriggerKey);
	trigger_tab->Add(trigger_sniper_key);

	auto trigger_sniper_filter = new Checkbox;
	trigger_sniper_filter->SetPosition(25 + (groupbox * 145) + 24, 195);
	trigger_sniper_filter->SetTitle("Hitgroup Filter");
	trigger_sniper_filter->SetValue(&V::Triggerbot_Sniper::Filter);
	trigger_tab->Add(trigger_sniper_filter);

	auto trigger_sniper_hitchance_enable = new Checkbox;
	trigger_sniper_hitchance_enable->SetPosition(25 + (groupbox * 145) + 24, 25 + (1 * 145) + 85);
	trigger_sniper_hitchance_enable->SetTitle("Hitchance");
	trigger_sniper_hitchance_enable->SetValue(&V::Triggerbot_Sniper::EnableHitchance);
	trigger_tab->Add(trigger_sniper_hitchance_enable);

	auto trigger_sniper_hitchance = new Slider;
	trigger_sniper_hitchance->SetPosition(25 + (groupbox * 145) + 24, 290);
	trigger_sniper_hitchance->SetTitle("Hitchance Amount");
	trigger_sniper_hitchance->SetValue(&V::Triggerbot_Sniper::Hitchance);
	trigger_sniper_hitchance->SetSize(137, 7);
	trigger_sniper_hitchance->SetMin(0.f);
	trigger_sniper_hitchance->SetMax(100.f);
	trigger_tab->Add(trigger_sniper_hitchance);

	auto trigger_sniper_ignoreteam = new Checkbox;
	trigger_sniper_ignoreteam->SetPosition(25 + (groupbox * 145) + 24, 315);
	trigger_sniper_ignoreteam->SetTitle("Ignore Team");
	trigger_sniper_ignoreteam->SetValue(&V::Triggerbot_Sniper::IgnoreTeam);
	trigger_tab->Add(trigger_sniper_ignoreteam);

	auto trigger_sniper_smoke = new Checkbox;
	trigger_sniper_smoke->SetPosition(25 + (groupbox * 145) + 24, 335);
	trigger_sniper_smoke->SetTitle("Smoke Check");
	trigger_sniper_smoke->SetValue(&V::Triggerbot_Sniper::SmokeCheck);
	trigger_tab->Add(trigger_sniper_smoke);

	auto trigger_sniper_delay = new Checkbox;
	trigger_sniper_delay->SetPosition(25 + (groupbox * 145) + 24, 355);
	trigger_sniper_delay->SetTitle("Delay Amount");
	trigger_sniper_delay->SetValue(&V::Triggerbot_Sniper::UseDelay);
	trigger_tab->Add(trigger_sniper_delay);

	auto trigger_sniper_delay_amount = new Slider;
	trigger_sniper_delay_amount->SetPosition(25 + (groupbox * 145) + 24, 390);
	trigger_sniper_delay_amount->SetTitle("Delay Amount");
	trigger_sniper_delay_amount->SetValue(&V::Triggerbot_Sniper::Delay);
	trigger_sniper_delay_amount->SetSize(137, 7);
	trigger_sniper_delay_amount->SetMin(0.f);
	trigger_sniper_delay_amount->SetMax(100.f);
	trigger_tab->Add(trigger_sniper_delay_amount);

	auto trigger_sniper_hitgroup = new Combobox;
	trigger_sniper_hitgroup->SetPosition(25 + (groupbox * 145) + 24, 230);
	trigger_sniper_hitgroup->SetTitle("Hitgroup");
	trigger_sniper_hitgroup->SetSize(137, 20);
	trigger_sniper_hitgroup->AddItem("Head");
	trigger_sniper_hitgroup->AddItem("Chest");
	trigger_sniper_hitgroup->AddItem("Stomach");
	trigger_sniper_hitgroup->AddItem("Arms");
	trigger_sniper_hitgroup->AddItem("Legs");
	trigger_sniper_hitgroup->SetCurrentItem("Head");
	trigger_sniper_hitgroup->SetValue(&V::Triggerbot_Sniper::Hitgroup);
	trigger_tab->Add(trigger_sniper_hitgroup);

	// ===============================================================

	auto trigger_other = new Groupbox;
	trigger_other->SetPosition(20 + (++groupbox * 145) + 32, 108);
	trigger_other->SetSize(145, 450);
	trigger_other->SetTitle("Other");
	trigger_tab->Add(trigger_other);

	// Other ======================================================

	auto trigger_other_enabled = new Checkbox;
	trigger_other_enabled->SetPosition(25 + (groupbox * 145) + 32, 115);
	trigger_other_enabled->SetTitle(XorStr("Enabled"));
	trigger_other_enabled->SetValue(&V::Triggerbot_Other::Enabled);
	trigger_tab->Add(trigger_other_enabled);

	auto trigger_other_usekey = new Checkbox;
	trigger_other_usekey->SetPosition(25 + (groupbox * 145) + 32, 135);
	trigger_other_usekey->SetTitle("Use Key");
	trigger_other_usekey->SetValue(&V::Triggerbot_Other::UseKey);
	trigger_tab->Add(trigger_other_usekey);

	auto trigger_other_key = new KeyReader;
	trigger_other_key->SetPosition(25 + (groupbox * 145) + 32, 170);
	trigger_other_key->SetSize(137, 20);
	trigger_other_key->SetTitle("Trigger Key");
	trigger_other_key->SetValue(&V::Triggerbot_Other::TriggerKey);
	trigger_tab->Add(trigger_other_key);

	auto trigger_other_filter = new Checkbox;
	trigger_other_filter->SetPosition(25 + (groupbox * 145) + 32, 195);
	trigger_other_filter->SetTitle("Hitgroup Filter");
	trigger_other_filter->SetValue(&V::Triggerbot_Other::Filter);
	trigger_tab->Add(trigger_other_filter);

	auto trigger_other_hitchance_enable = new Checkbox;
	trigger_other_hitchance_enable->SetPosition(25 + (groupbox * 145) + 32, 25 + (1 * 145) + 85);
	trigger_other_hitchance_enable->SetTitle("Hitchance");
	trigger_other_hitchance_enable->SetValue(&V::Triggerbot_Other::EnableHitchance);
	trigger_tab->Add(trigger_other_hitchance_enable);

	auto trigger_other_hitchance = new Slider;
	trigger_other_hitchance->SetPosition(25 + (groupbox * 145) + 32, 290);
	trigger_other_hitchance->SetTitle("Hitchance Amount");
	trigger_other_hitchance->SetValue(&V::Triggerbot_Other::Hitchance);
	trigger_other_hitchance->SetSize(137, 7);
	trigger_other_hitchance->SetMin(0.f);
	trigger_other_hitchance->SetMax(100.f);
	trigger_tab->Add(trigger_other_hitchance);

	auto trigger_other_ignoreteam = new Checkbox;
	trigger_other_ignoreteam->SetPosition(25 + (groupbox * 145) + 32, 315);
	trigger_other_ignoreteam->SetTitle("Ignore Team");
	trigger_other_ignoreteam->SetValue(&V::Triggerbot_Other::IgnoreTeam);
	trigger_tab->Add(trigger_other_ignoreteam);

	auto trigger_other_smoke = new Checkbox;
	trigger_other_smoke->SetPosition(25 + (groupbox * 145) + 32, 335);
	trigger_other_smoke->SetTitle("Smoke Check");
	trigger_other_smoke->SetValue(&V::Triggerbot_Other::SmokeCheck);
	trigger_tab->Add(trigger_other_smoke);

	auto trigger_other_delay = new Checkbox;
	trigger_other_delay->SetPosition(25 + (groupbox * 145) + 32, 355);
	trigger_other_delay->SetTitle("Use Delay");
	trigger_other_delay->SetValue(&V::Triggerbot_Other::UseDelay);
	trigger_tab->Add(trigger_other_delay);

	auto trigger_other_delay_amount = new Slider;
	trigger_other_delay_amount->SetPosition(25 + (groupbox * 145) + 32, 390);
	trigger_other_delay_amount->SetTitle("Delay Amount");
	trigger_other_delay_amount->SetValue(&V::Triggerbot_Other::Delay);
	trigger_other_delay_amount->SetSize(137, 7);
	trigger_other_delay_amount->SetMin(0.f);
	trigger_other_delay_amount->SetMax(100.f);
	trigger_tab->Add(trigger_other_delay_amount);

	auto trigger_other_hitgroup = new Combobox;
	trigger_other_hitgroup->SetPosition(25 + (groupbox * 145) + 32, 230);
	trigger_other_hitgroup->SetTitle("Hitgroup");
	trigger_other_hitgroup->SetSize(137, 20);
	trigger_other_hitgroup->AddItem("Head");
	trigger_other_hitgroup->AddItem("Chest");
	trigger_other_hitgroup->AddItem("Stomach");
	trigger_other_hitgroup->AddItem("Arms");
	trigger_other_hitgroup->AddItem("Legs");
	trigger_other_hitgroup->SetCurrentItem("Head");
	trigger_other_hitgroup->SetValue(&V::Triggerbot_Other::Hitgroup);
	trigger_tab->Add(trigger_other_hitgroup);

	// ===============================================================

#pragma endregion

	// ===============================================================

	frame->Add(trigger_tab);

	// ============================================================================

	auto colors_tab = new Tab;
	colors_tab->SetTab(++tab);
	colors_tab->SetTitle("Colors");
	groupbox = 0;

#pragma region COLORS

	// COLORS ====================================================================

	auto colors_boxteam_group = new Groupbox;
	colors_boxteam_group->SetPosition(20, 68);
	colors_boxteam_group->SetSize(150, 80);
	colors_boxteam_group->SetTitle("Box Team");
	colors_tab->Add(colors_boxteam_group);

	auto colors_boxteam = new ColorPicker(colors_tab);
	colors_boxteam->SetValue(&V::Colors::BoxTeam);
	colors_boxteam->SetPosition(25, 75);
	colors_boxteam->SetSize(141, 20);
	colors_boxteam->CreateSliders();
	colors_tab->Add(colors_boxteam);

	auto colors_boxenemy_group = new Groupbox;
	colors_boxenemy_group->SetPosition(20 + (++groupbox * 150) + 32, 68);
	colors_boxenemy_group->SetSize(150, 80);
	colors_boxenemy_group->SetTitle("Box Enemy");
	colors_tab->Add(colors_boxenemy_group);

	auto colors_boxenemy = new ColorPicker(colors_tab);
	colors_boxenemy->SetValue(&V::Colors::BoxEnemy);
	colors_boxenemy->SetPosition(25 + (groupbox * 150) + 32, 75);
	colors_boxenemy->SetSize(141, 20);
	colors_boxenemy->CreateSliders();
	colors_tab->Add(colors_boxenemy);

	auto colors_glowteam_group = new Groupbox;
	colors_glowteam_group->SetPosition(20 + (++groupbox * 150) + 64, 68);
	colors_glowteam_group->SetSize(150, 80);
	colors_glowteam_group->SetTitle("Glow Team");
	colors_tab->Add(colors_glowteam_group);

	auto colors_glowteam = new ColorPicker(colors_tab);
	colors_glowteam->SetValue(&V::Colors::GlowTeam);
	colors_glowteam->SetPosition(25 + (groupbox * 150) + 64, 75);
	colors_glowteam->SetSize(141, 20);
	colors_glowteam->CreateSliders();
	colors_tab->Add(colors_glowteam);

	auto colors_glowenemy_group = new Groupbox;
	colors_glowenemy_group->SetPosition(20 + (++groupbox * 150) + 96, 68);
	colors_glowenemy_group->SetSize(150, 80);
	colors_glowenemy_group->SetTitle("Glow Enemy");
	colors_tab->Add(colors_glowenemy_group);

	auto colors_glowenemy = new ColorPicker(colors_tab);
	colors_glowenemy->SetValue(&V::Colors::GlowEnemy);
	colors_glowenemy->SetPosition(25 + (groupbox * 150) + 96, 75);
	colors_glowenemy->SetSize(141, 20);
	colors_glowenemy->CreateSliders();
	colors_tab->Add(colors_glowenemy);

	groupbox = 0;
	static int offy = 90;

	auto colors_chamsteam_group = new Groupbox;
	colors_chamsteam_group->SetPosition(20 + (groupbox * 150), 68 + offy);
	colors_chamsteam_group->SetSize(150, 80);
	colors_chamsteam_group->SetTitle("Chams Team Visible");
	colors_tab->Add(colors_chamsteam_group);

	auto colors_chamsteam_visible = new ColorPicker(colors_tab);
	colors_chamsteam_visible->SetValue(&V::Colors::ChamsVisible_Team);
	colors_chamsteam_visible->SetPosition(25 + (groupbox * 150), 75 + offy);
	colors_chamsteam_visible->SetSize(141, 20);
	colors_chamsteam_visible->CreateSliders();
	colors_tab->Add(colors_chamsteam_visible);

	auto colors_chamsenemy_group = new Groupbox;
	colors_chamsenemy_group->SetPosition(20 + (++groupbox * 150) + 32, 68 + offy);
	colors_chamsenemy_group->SetSize(150, 80);
	colors_chamsenemy_group->SetTitle("Chams Enemy Visible");
	colors_tab->Add(colors_chamsenemy_group);

	auto colors_chamsenemy_visible = new ColorPicker(colors_tab);
	colors_chamsenemy_visible->SetValue(&V::Colors::ChamsVisible_Enemy);
	colors_chamsenemy_visible->SetPosition(25 + (groupbox * 150) + 32, 75 + offy);
	colors_chamsenemy_visible->SetSize(141, 20);
	colors_chamsenemy_visible->CreateSliders();
	colors_tab->Add(colors_chamsenemy_visible);

	auto colors_chamsteam_group_normal = new Groupbox;
	colors_chamsteam_group_normal->SetPosition(20 + (++groupbox * 150) + 64, 68 + offy);
	colors_chamsteam_group_normal->SetSize(150, 80);
	colors_chamsteam_group_normal->SetTitle("Chams Team");
	colors_tab->Add(colors_chamsteam_group_normal);

	auto colors_chamsteam_normal = new ColorPicker(colors_tab);
	colors_chamsteam_normal->SetValue(&V::Colors::ChamsTeam);
	colors_chamsteam_normal->SetPosition(25 + (groupbox * 150) + 64, 75 + offy);
	colors_chamsteam_normal->SetSize(141, 20);
	colors_chamsteam_normal->CreateSliders();
	colors_tab->Add(colors_chamsteam_normal);

	auto colors_chamsenemy_group_normal = new Groupbox;
	colors_chamsenemy_group_normal->SetPosition(20 + (++groupbox * 150) + 96, 68 + offy);
	colors_chamsenemy_group_normal->SetSize(150, 80);
	colors_chamsenemy_group_normal->SetTitle("Chams Enemy");
	colors_tab->Add(colors_chamsenemy_group_normal);

	auto colors_chamsenemy_normal = new ColorPicker(colors_tab);
	colors_chamsenemy_normal->SetValue(&V::Colors::ChamsEnemy);
	colors_chamsenemy_normal->SetPosition(25 + (groupbox * 150) + 96, 75 + offy);
	colors_chamsenemy_normal->SetSize(141, 20);
	colors_chamsenemy_normal->CreateSliders();
	colors_tab->Add(colors_chamsenemy_normal);

	groupbox = -1;

	auto colors_chamshands_group = new Groupbox;
	colors_chamshands_group->SetPosition(20 + (++groupbox * 150), 68 + offy * 2);
	colors_chamshands_group->SetSize(150, 80);
	colors_chamshands_group->SetTitle("Chams Hands");
	colors_tab->Add(colors_chamshands_group);

	auto colors_chamshands = new ColorPicker(colors_tab);
	colors_chamshands->SetValue(&V::Colors::Chams_Hands);
	colors_chamshands->SetPosition(25 + (groupbox * 150), 75 + offy * 2);
	colors_chamshands->SetSize(141, 20);
	colors_chamshands->CreateSliders();
	colors_tab->Add(colors_chamshands);

	auto colors_chamsweapons_group = new Groupbox;
	colors_chamsweapons_group->SetPosition(20 + (++groupbox * 150) + 32, 68 + offy * 2);
	colors_chamsweapons_group->SetSize(150, 80);
	colors_chamsweapons_group->SetTitle("Chams Weapons");
	colors_tab->Add(colors_chamsweapons_group);

	auto colors_chamsweapons = new ColorPicker(colors_tab);
	colors_chamsweapons->SetValue(&V::Colors::Chams_Weapon);
	colors_chamsweapons->SetPosition(25 + (groupbox * 150) + 32, 75 + offy * 2);
	colors_chamsweapons->SetSize(141, 20);
	colors_chamsweapons->CreateSliders();
	colors_tab->Add(colors_chamsweapons);

	auto colors_menufirst_group = new Groupbox;
	colors_menufirst_group->SetPosition(20 + (++groupbox * 150) + 64, 68 + offy * 2);
	colors_menufirst_group->SetSize(150, 80);
	colors_menufirst_group->SetTitle("Menu Color - First");
	colors_tab->Add(colors_menufirst_group);

	auto colors_menufirst = new ColorPicker(colors_tab);
	colors_menufirst->SetValue(&V::Colors::MenuColor_First);
	colors_menufirst->SetPosition(25 + (groupbox * 150) + 64, 75 + offy * 2);
	colors_menufirst->SetSize(141, 20);
	colors_menufirst->CreateSliders();
	colors_tab->Add(colors_menufirst);

	auto colors_menusecond_group = new Groupbox;
	colors_menusecond_group->SetPosition(20 + (++groupbox * 150) + 96, 68 + offy * 2);
	colors_menusecond_group->SetSize(150, 80);
	colors_menusecond_group->SetTitle("Menu Color - Second");
	colors_tab->Add(colors_menusecond_group);

	auto colors_menusecond = new ColorPicker(colors_tab);
	colors_menusecond->SetValue(&V::Colors::MenuColor_Second);
	colors_menusecond->SetPosition(25 + (groupbox * 150) + 96, 75 + offy * 2);
	colors_menusecond->SetSize(141, 20);
	colors_menusecond->CreateSliders();
	colors_tab->Add(colors_menusecond);

	frame->Add(colors_tab);

#pragma endregion

	// ============================================================================

	auto misc_tab = new Tab;
	misc_tab->SetTab(++tab);
	misc_tab->SetTitle("Misc");
	groupbox = 0;

	// MISC ======================================================================

#pragma region MISC

	auto misc_misc = new Groupbox;
	misc_misc->SetPosition(20, 68);
	misc_misc->SetSize(145, 415);
	misc_misc->SetTitle("Misc");
	misc_tab->Add(misc_misc);

	auto misc_bhop = new Checkbox;
	misc_bhop->SetPosition(25, 75);
	misc_bhop->SetTitle("Bunny Hop");
	misc_bhop->SetValue(&V::Misc::BunnyHop);
	misc_tab->Add(misc_bhop);

	auto misc_autostrafe = new Checkbox;
	misc_autostrafe->SetPosition(25, 95);
	misc_autostrafe->SetTitle("Auto Strafe");
	misc_autostrafe->SetValue(&V::Misc::AutoStrafe);
	misc_tab->Add(misc_autostrafe);

	auto misc_autoaccept = new Checkbox;
	misc_autoaccept->SetPosition(25, 115);
	misc_autoaccept->SetTitle("Auto Accept");
	misc_autoaccept->SetValue(&V::Misc::AutoAccept);
	misc_tab->Add(misc_autoaccept);

	auto misc_chatspam = new Checkbox;
	misc_chatspam->SetPosition(25, 135);
	misc_chatspam->SetTitle("Chat Spam");
	misc_chatspam->SetValue(&V::Misc::ChatSpam);
	misc_tab->Add(misc_chatspam);

	auto misc_infospam = new Checkbox;
	misc_infospam->SetPosition(25, 155);
	misc_infospam->SetTitle("Info Spam");
	misc_infospam->SetValue(&V::Misc::InfoSpam);
	misc_tab->Add(misc_infospam);

	auto misc_nazicrosshair = new Checkbox;
	misc_nazicrosshair->SetPosition(25, 175);
	misc_nazicrosshair->SetTitle("Nazi Crosshair");
	misc_nazicrosshair->SetValue(&V::Misc::NaziCrosshair);
	misc_tab->Add(misc_nazicrosshair);

	auto misc_slide = new Checkbox;
	misc_slide->SetPosition(25, 195);
	misc_slide->SetTitle("Slide Walk");
	misc_slide->SetValue(&V::Misc::SlideWalk);
	misc_tab->Add(misc_slide);

	auto misc_antiut = new Checkbox;
	misc_antiut->SetPosition(25, 215);
	misc_antiut->SetTitle("Anti Untrusted [!!!]");
	misc_antiut->SetValue(&V::HvH::AntiUntrusted);
	misc_tab->Add(misc_antiut);

	auto misc_nospread = new Checkbox;
	misc_nospread->SetPosition(25, 235);
	misc_nospread->SetTitle("No Spread [!]");
	misc_nospread->SetValue(&V::HvH::NoSpread);
	misc_tab->Add(misc_nospread);

	auto misc_fov = new Checkbox;
	misc_fov->SetPosition(25, 255);
	misc_fov->SetTitle("Custom FOV");
	misc_fov->SetValue(&V::Visuals::EnableFOV);
	misc_tab->Add(misc_fov);

	auto misc_fov_amount = new Slider;
	misc_fov_amount->SetPosition(25, 255 + 35);
	misc_fov_amount->SetTitle("Custom FOV");
	misc_fov_amount->SetSize(137, 7);
	misc_fov_amount->SetMin(0);
	misc_fov_amount->SetMax(200);
	misc_fov_amount->SetValue(&V::Visuals::CustomFOV);
	misc_tab->Add(misc_fov_amount);

	auto misc_circlestrafe = new Checkbox;
	misc_circlestrafe->SetPosition(25, 255 + 35 + 30);
	misc_circlestrafe->SetTitle("Circle Strafer");
	misc_circlestrafe->SetValue(&V::Misc::CircleStrafe);
	misc_tab->Add(misc_circlestrafe);

	auto misc_circlestrafe_key = new KeyReader;
	misc_circlestrafe_key->SetSize(137, 20);
	misc_circlestrafe_key->SetPosition(25, 255 + 35 + 45 + 20);
	misc_circlestrafe_key->SetTitle("Circle Strafer Key");
	misc_circlestrafe_key->SetValue(&V::Misc::CircleStrafe_Key);
	misc_tab->Add(misc_circlestrafe_key);

	auto misc_menukey = new KeyReader;
	misc_menukey->SetSize(137, 20);
	misc_menukey->SetPosition(25, 255 + 35 + 45 + 55);
	misc_menukey->SetTitle("Menu Key");
	misc_menukey->SetValue(&V::Menu::Key);
	misc_tab->Add(misc_menukey);

	auto misc_panickey = new KeyReader;
	misc_panickey->SetSize(137, 20);
	misc_panickey->SetPosition(25, 255 + 35 + 45 + 90);
	misc_panickey->SetTitle("Panic Key");
	misc_panickey->SetValue(&V::Menu::PanicKey);
	misc_tab->Add(misc_panickey);

	auto misc_clantag = new Checkbox;
	misc_clantag->SetPosition(25, 255 + 35 + 45 + 115);
	misc_clantag->SetTitle("Animated ClanTag");
	misc_clantag->SetValue(&V::Misc::AnimatedClanTag);
	misc_tab->Add(misc_clantag);

	frame->Add(misc_tab);

	// ============================================================================

	auto misc_hvh = new Groupbox;
	misc_hvh->SetPosition(20 + (++groupbox * 145) + 8, 68 + 215);
	misc_hvh->SetSize(290, 200);
	misc_hvh->SetTitle("HvH");
	misc_tab->Add(misc_hvh);

	// HvH Memes ======================================================

	// hvh 25 + (groupbox * 145) + 8, 75
	// 25 + (groupbox * 145) + 8 + 137, 75

	static int hvh_offset = 68 + 220;
	static int skins_offset = 70;

	auto misc_enable_antiaim = new Checkbox;
	misc_enable_antiaim->SetPosition(25 + (groupbox * 145) + 8, hvh_offset);
	misc_enable_antiaim->SetTitle("Enable Anti-Aim");
	misc_enable_antiaim->SetValue(&V::HvH::AntiAim);
	misc_tab->Add(misc_enable_antiaim);

	auto misc_enable_airstuck = new Checkbox;
	misc_enable_airstuck->SetPosition(25 + (groupbox * 145) + 8 + 137 + 5, hvh_offset);
	misc_enable_airstuck->SetTitle("Enable AirStuck");
	misc_enable_airstuck->SetValue(&V::HvH::AirStuck);
	misc_tab->Add(misc_enable_airstuck);

	auto misc_airstuck_key = new KeyReader;
	misc_airstuck_key->SetPosition(25 + (groupbox * 145) + 8 + 137 + 5, hvh_offset + 35);
	misc_airstuck_key->SetSize(137, 20);
	misc_airstuck_key->SetTitle("AirStuck Key");
	misc_airstuck_key->SetValue(&V::HvH::AirStuck_Key);
	misc_tab->Add(misc_airstuck_key);

	auto misc_enable_fakelag = new Checkbox;
	misc_enable_fakelag->SetPosition(25 + (groupbox * 145) + 8 + 137 + 5, hvh_offset + 65);
	misc_enable_fakelag->SetTitle("Enable FakeLag");
	misc_enable_fakelag->SetValue(&V::HvH::FakeLag);
	misc_tab->Add(misc_enable_fakelag);

	auto misc_fakelag_amount = new Slider;
	misc_fakelag_amount->SetPosition(25 + (groupbox * 145) + 8 + 137 + 5, hvh_offset + 105);
	misc_fakelag_amount->SetTitle("FakeLag Amount");
	misc_fakelag_amount->SetValue(&V::HvH::FakeLag_Amount);
	misc_fakelag_amount->SetSize(137, 7);
	misc_fakelag_amount->SetMin(1.f);
	misc_fakelag_amount->SetMax(14.f);
	misc_tab->Add(misc_fakelag_amount);

	auto misc_enable_resolver = new Checkbox;
	misc_enable_resolver->SetPosition(25 + (groupbox * 145) + 8, hvh_offset + 95);
	misc_enable_resolver->SetTitle("Enable Resolver");
	misc_enable_resolver->SetValue(&V::HvH::Resolver);
	misc_tab->Add(misc_enable_resolver);

	auto misc_enable_thirdperson = new Checkbox;
	misc_enable_thirdperson->SetPosition(25 + (groupbox * 145) + 8, hvh_offset + 115);
	misc_enable_thirdperson->SetTitle("Third Person");
	misc_enable_thirdperson->SetValue(&V::HvH::ThirdPerson);
	misc_tab->Add(misc_enable_thirdperson);

	auto misc_enable_fakelagfix = new Checkbox;
	misc_enable_fakelagfix->SetPosition(25 + (groupbox * 145) + 8, hvh_offset + 115 + 20);
	misc_enable_fakelagfix->SetTitle("Lag Compensation");
	misc_enable_fakelagfix->SetValue(&V::HvH::LagCompensation);
	misc_tab->Add(misc_enable_fakelagfix);

	auto misc_enable_attargets = new Checkbox;
	misc_enable_attargets->SetPosition(25 + (groupbox * 145) + 8, hvh_offset + 115 + 40);
	misc_enable_attargets->SetTitle("At Targets");
	misc_enable_attargets->SetValue(&V::HvH::AtTargets);
	misc_tab->Add(misc_enable_attargets);

	auto misc_enable_dynamicfakelag = new Checkbox;
	misc_enable_dynamicfakelag->SetPosition(25 + (groupbox * 145) + 8, hvh_offset + 115 + 60);
	misc_enable_dynamicfakelag->SetTitle("Dynamic FakeLag");
	misc_enable_dynamicfakelag->SetValue(&V::HvH::DynamicFakeLag);
	misc_tab->Add(misc_enable_dynamicfakelag);

	auto misc_saveconfig_legit = new Button;
	misc_saveconfig_legit->SetPosition(15, 560);
	misc_saveconfig_legit->SetSize(137, 20);
	misc_saveconfig_legit->SetTitle("Save Legit");
	misc_saveconfig_legit->SetCallback(SaveConfigLegit);
	misc_tab->Add(misc_saveconfig_legit);

	auto misc_loadconfig_legit = new Button;
	misc_loadconfig_legit->SetPosition(15 + 137 + 5, 560);
	misc_loadconfig_legit->SetSize(137, 20);
	misc_loadconfig_legit->SetTitle("Load Legit");
	misc_loadconfig_legit->SetCallback(LoadConfigLegit);
	misc_tab->Add(misc_loadconfig_legit);

	auto misc_saveconfig_rage = new Button;
	misc_saveconfig_rage->SetPosition(15 + 137 + 350, 560);
	misc_saveconfig_rage->SetSize(137, 20);
	misc_saveconfig_rage->SetTitle("Save Rage");
	misc_saveconfig_rage->SetCallback(SaveConfigRage);
	misc_tab->Add(misc_saveconfig_rage);

	auto misc_loadconfig_rage = new Button;
	misc_loadconfig_rage->SetPosition(15 + 137 + 350 + 137 + 5, 560);
	misc_loadconfig_rage->SetSize(137, 20);
	misc_loadconfig_rage->SetTitle("Load Rage");
	misc_loadconfig_rage->SetCallback(LoadConfigRage);
	misc_tab->Add(misc_loadconfig_rage);

	// ============================================================================

	auto misc_skins = new Groupbox;
	misc_skins->SetPosition(20 + (groupbox * 145) + 8, 70);
	misc_skins->SetSize(290 + 150, 200);
	misc_skins->SetTitle("Skins");
	misc_tab->Add(misc_skins);

	auto misc_enable_skinchanger = new Checkbox;
	misc_enable_skinchanger->SetPosition(20 + (groupbox * 145) + 8 + 5, skins_offset + 5);
	misc_enable_skinchanger->SetTitle("Enable SkinChanger");
	misc_enable_skinchanger->SetValue(&V::Skins::Enabled);
	misc_tab->Add(misc_enable_skinchanger);

	auto misc_skindata = new Groupbox;
	misc_skindata->SetPosition(147 + 20 + (groupbox * 145) + 8 + 5, skins_offset + 15);
	misc_skindata->SetSize(255, 170);
	misc_skindata->SetTitle("Skin Data");
	misc_tab->Add(misc_skindata);

	auto misc_skins_save = new Button;
	misc_skins_save->SetPosition(20 + (groupbox * 145) + 8 + 5, 70 + skins_offset + 55);
	misc_skins_save->SetSize(137, 20);
	misc_skins_save->SetTitle("Save Skins");
	misc_skins_save->SetCallback(SaveSkins);
	misc_tab->Add(misc_skins_save);

	auto misc_skins_load = new Button;
	misc_skins_load->SetPosition(20 + (groupbox * 145) + 8 + 5, skins_offset + 70 + 80);
	misc_skins_load->SetSize(137, 20);
	misc_skins_load->SetTitle("Load Skins");
	misc_skins_load->SetCallback(LoadSkins);
	misc_tab->Add(misc_skins_load);

	auto misc_skins_apply = new Button;
	misc_skins_apply->SetPosition(20 + (groupbox * 145) + 8 + 5, skins_offset + 70 + 105);
	misc_skins_apply->SetSize(137, 20);
	misc_skins_apply->SetTitle("Apply Skins");
	misc_skins_apply->SetCallback(ForceFullUpdate);
	misc_tab->Add(misc_skins_apply);

	auto misc_skinchanger_paintkit = new Combobox;
	misc_skinchanger_paintkit->SetPosition(147 + 20 + (groupbox * 145) + 8 + 5 + 5, skins_offset + 40);
	misc_skinchanger_paintkit->SetSize(137, 20);
	misc_skinchanger_paintkit->SetTitle("PaintKit");
	misc_skinchanger_paintkit->bIsPaintKitList = true;
	misc_tab->Add(misc_skinchanger_paintkit);

	auto misc_antiaim_yaw = new Combobox;
	misc_antiaim_yaw->SetPosition(25 + (groupbox * 145) + 8, hvh_offset + 70);
	misc_antiaim_yaw->SetSize(137, 20);
	misc_antiaim_yaw->SetTitle("Anti-Aim Yaw");
	misc_antiaim_yaw->AddItem("Jitter");
	misc_antiaim_yaw->AddItem("Slowspin");
	misc_antiaim_yaw->AddItem("Fastspin");
	misc_antiaim_yaw->AddItem("Sideways");
	misc_antiaim_yaw->AddItem("Fake Sideways");
	misc_antiaim_yaw->AddItem("Static");
	misc_antiaim_yaw->AddItem("Fake Static");
	misc_antiaim_yaw->AddItem("Backward");
	misc_antiaim_yaw->AddItem("Fake Backward");
	misc_antiaim_yaw->AddItem("Angel Backward [!]");
	misc_antiaim_yaw->AddItem("Angel Inverse [!]");
	misc_antiaim_yaw->AddItem("Angel Spin [!]");
	misc_antiaim_yaw->AddItem("Angel Fake Spin [!]");
	misc_antiaim_yaw->AddItem("Angel Fake [!]");
	misc_antiaim_yaw->AddItem("LISP [!]");
	misc_antiaim_yaw->AddItem("LISP Jitter [!]");
	misc_antiaim_yaw->AddItem("LISP Backward [!]");
	misc_antiaim_yaw->AddItem("LISP Sideways [!]");
	misc_antiaim_yaw->AddItem("LISP Crazy [!]");
	misc_antiaim_yaw->AddItem("SwitchStep");
	misc_antiaim_yaw->AddItem("LowerFake");
	misc_antiaim_yaw->AddItem("RestFake");
	misc_antiaim_yaw->AddItem("Fake Zero Down [!]");
	misc_antiaim_yaw->AddItem("Fake Zero Up [!]");
	misc_antiaim_yaw->AddItem("Fake Zero Down 2 [!]");
	misc_antiaim_yaw->AddItem("Fake Zero Up 2 [!]");
	misc_antiaim_yaw->SetValue(&V::HvH::AntiAim_Yaw);
	misc_antiaim_yaw->SetCurrentItem("Backward");
	misc_tab->Add(misc_antiaim_yaw);

	auto misc_antiaim_pitch = new Combobox;
	misc_antiaim_pitch->SetPosition(25 + (groupbox * 145) + 8, hvh_offset + 35);
	misc_antiaim_pitch->SetSize(137, 20);
	misc_antiaim_pitch->SetTitle("Anti-Aim Pitch");
	misc_antiaim_pitch->AddItem("SMAC");
	misc_antiaim_pitch->AddItem("Up");
	misc_antiaim_pitch->AddItem("Fake Up");
	misc_antiaim_pitch->AddItem("Down");
	misc_antiaim_pitch->AddItem("Fake Down");
	misc_antiaim_pitch->AddItem("Emotion");
	misc_antiaim_pitch->AddItem("Angel Down [!]");
	misc_antiaim_pitch->AddItem("Angel Up [!]");
	misc_antiaim_pitch->AddItem("LISP Down [!]");
	misc_antiaim_pitch->AddItem("LISP Up [!]");
	misc_antiaim_pitch->AddItem("Static");
	misc_antiaim_pitch->SetValue(&V::HvH::AntiAim_Pitch);
	misc_antiaim_pitch->SetCurrentItem("Down");
	misc_tab->Add(misc_antiaim_pitch);

	auto misc_forcefakehs = new Checkbox;
	misc_forcefakehs->SetPosition(25 + (groupbox * 145) + 8 + 137 + 4, hvh_offset + 175);
	misc_forcefakehs->SetTitle("Force Fake HS");
	misc_forcefakehs->SetValue(&V::HvH::ForceFakeHS);
	misc_tab->Add(misc_forcefakehs);

	auto misc_resolvertype = new Combobox;
	misc_resolvertype->SetPosition(25 + (groupbox * 145) + 8 + 137 + 5, hvh_offset + 145);
	misc_resolvertype->SetSize(137, 20);
	misc_resolvertype->SetTitle("Resolver Type");
	misc_resolvertype->AddItem("Static");
	misc_resolvertype->AddItem("Dynamic");
	misc_resolvertype->SetValue(&V::HvH::ResolverType);
	misc_resolvertype->SetCurrentItem("Static");
	misc_tab->Add(misc_resolvertype);

	auto misc_glovechanger_glove = new Combobox;
	misc_glovechanger_glove->SetPosition(20 + (groupbox * 145) + 8 + 5, skins_offset + 70 + 30);
	misc_glovechanger_glove->SetSize(137, 20);
	misc_glovechanger_glove->SetTitle("");
	misc_glovechanger_glove->AddItem("Default");
	misc_glovechanger_glove->AddItem("Bloodhound | Charred");
	misc_glovechanger_glove->AddItem("Bloodhound | Snakebite");
	misc_glovechanger_glove->AddItem("Bloodhound | Bronzed");
	misc_glovechanger_glove->AddItem("Bloodhound | Guerilla");
	misc_glovechanger_glove->AddItem("Wraps | Leather");
	misc_glovechanger_glove->AddItem("Wraps | Spruce DDPAT");
	misc_glovechanger_glove->AddItem("Wraps | Slaughter");
	misc_glovechanger_glove->AddItem("Wraps | Badlands");
	misc_glovechanger_glove->AddItem("Driver | Lunar Weave");
	misc_glovechanger_glove->AddItem("Driver | Convoy");
	misc_glovechanger_glove->AddItem("Driver | Crimson Weave");
	misc_glovechanger_glove->AddItem("Driver | Diamondback");
	misc_glovechanger_glove->AddItem("Sport | Hedge Maze");
	misc_glovechanger_glove->AddItem("Sport | Pandoras Box");
	misc_glovechanger_glove->AddItem("Sport | Superconductor");
	misc_glovechanger_glove->AddItem("Sport | Arid");
	misc_glovechanger_glove->AddItem("Moto | Eclipse");
	misc_glovechanger_glove->AddItem("Moto | Spear Mint");
	misc_glovechanger_glove->AddItem("Moto | Boom!");
	misc_glovechanger_glove->AddItem("Moto | Cool Mint");
	misc_glovechanger_glove->AddItem("Specialist | Forest DDPAT");
	misc_glovechanger_glove->AddItem("Specialist | Crimson Kimono");
	misc_glovechanger_glove->AddItem("Specialist | Emerald Web");
	misc_glovechanger_glove->AddItem("Specialist | Foundation");
	misc_glovechanger_glove->SetValue(&V::Skins::GloveID);
	misc_glovechanger_glove->SetCurrentItem("Default");
	misc_tab->Add(misc_glovechanger_glove);

	auto misc_skinchanger_knifemodel = new Combobox;
	misc_skinchanger_knifemodel->SetPosition(20 + (groupbox * 145) + 8 + 5, skins_offset + 70 + 5);
	misc_skinchanger_knifemodel->SetSize(137, 20);
	misc_skinchanger_knifemodel->SetTitle("Knife & Glove Model");
	misc_skinchanger_knifemodel->AddItem("Default");
	misc_skinchanger_knifemodel->AddItem("Bayonet");
	misc_skinchanger_knifemodel->AddItem("Flip");
	misc_skinchanger_knifemodel->AddItem("Gut");
	misc_skinchanger_knifemodel->AddItem("Karambit");
	misc_skinchanger_knifemodel->AddItem("M9 Bayonet");
	misc_skinchanger_knifemodel->AddItem("Huntsman");
	misc_skinchanger_knifemodel->AddItem("Falchion");
	misc_skinchanger_knifemodel->AddItem("Bowie");
	misc_skinchanger_knifemodel->AddItem("Butterfly");
	misc_skinchanger_knifemodel->AddItem("Shadow Daggers");
	misc_skinchanger_knifemodel->SetValue(&V::Skins::KnifeModel);
	misc_skinchanger_knifemodel->SetCurrentItem("Default");
	misc_tab->Add(misc_skinchanger_knifemodel);

	auto misc_skinchanger_weapon = new Combobox;
	misc_skinchanger_weapon->SetPosition(20 + (groupbox * 145) + 8 + 5, skins_offset + 35 + 5);
	misc_skinchanger_weapon->SetSize(137, 20);
	misc_skinchanger_weapon->SetTitle("Weapon");
	misc_skinchanger_weapon->AddItem("Deagle");
	misc_skinchanger_weapon->AddItem("Elites");
	misc_skinchanger_weapon->AddItem("Five-Seven");
	misc_skinchanger_weapon->AddItem("Glock");
	misc_skinchanger_weapon->AddItem("AK-47");
	misc_skinchanger_weapon->AddItem("AUG");
	misc_skinchanger_weapon->AddItem("AWP");
	misc_skinchanger_weapon->AddItem("Famas");
	misc_skinchanger_weapon->AddItem("G3SG1");
	misc_skinchanger_weapon->AddItem("Galil-AR");
	misc_skinchanger_weapon->AddItem("M249");
	misc_skinchanger_weapon->AddItem("M4A1-S");
	misc_skinchanger_weapon->AddItem("M4A4");
	misc_skinchanger_weapon->AddItem("MAC-10");
	misc_skinchanger_weapon->AddItem("P90");
	misc_skinchanger_weapon->AddItem("UMP-45");
	misc_skinchanger_weapon->AddItem("XM-1014");
	misc_skinchanger_weapon->AddItem("PP-Bizon");
	misc_skinchanger_weapon->AddItem("MAG-7");
	misc_skinchanger_weapon->AddItem("Negev");
	misc_skinchanger_weapon->AddItem("Sawed-Off");
	misc_skinchanger_weapon->AddItem("Tec-9");
	misc_skinchanger_weapon->AddItem("P2000");
	misc_skinchanger_weapon->AddItem("MP7");
	misc_skinchanger_weapon->AddItem("MP9");
	misc_skinchanger_weapon->AddItem("Nova");
	misc_skinchanger_weapon->AddItem("P250");
	misc_skinchanger_weapon->AddItem("SCAR-20");
	misc_skinchanger_weapon->AddItem("SG-553");
	misc_skinchanger_weapon->AddItem("SSG-08");
	misc_skinchanger_weapon->AddItem("USP-S");
	misc_skinchanger_weapon->AddItem("CZ75-A");
	misc_skinchanger_weapon->AddItem("Revolver");
	misc_skinchanger_weapon->AddItem("M9 Bayonet");
	misc_skinchanger_weapon->AddItem("Bayonet");
	misc_skinchanger_weapon->AddItem("Flip Knife");
	misc_skinchanger_weapon->AddItem("Gut Knife");
	misc_skinchanger_weapon->AddItem("Karambit");
	misc_skinchanger_weapon->AddItem("Huntsman Knife");
	misc_skinchanger_weapon->AddItem("Falchion Knife");
	misc_skinchanger_weapon->AddItem("Bowie Knife");
	misc_skinchanger_weapon->AddItem("Butterfly Knife");
	misc_skinchanger_weapon->AddItem("Shadow Daggers");
	misc_skinchanger_weapon->SetValue(&V::Skins::ItemDefIndex);
	misc_skinchanger_weapon->SetCurrentItem("Deagle");
	misc_skinchanger_weapon->SetParentSkinList(misc_skinchanger_paintkit);
	misc_tab->Add(misc_skinchanger_weapon);

	/*auto misc_skinchanger_name = new Textbox;
	misc_skinchanger_name->SetPosition(147 + 20 + (groupbox * 145) + 8 + 5 + 5, skins_offset + 80);
	misc_skinchanger_name->SetSize(137 * 1.5, 20);
	misc_skinchanger_name->SetTitle("Name");
	misc_skinchanger_name->SetMaxLen(32);
	misc_skinchanger_name->bIsSkinName = true;
	misc_skinchanger_name->par_WeapList = misc_skinchanger_weapon;
	misc_tab->Add(misc_skinchanger_name);*/

#pragma endregion

	auto players_tab = new Tab;
	players_tab->SetTab(++tab);
	players_tab->SetTitle("Players");

	// PLAYERS ==================================================================

	auto players_active = new Checkbox;
	players_active->SetPosition(20, 68);
	players_active->SetTitle("Active");
	players_active->SetValue(&V::PlayerList::Active);
	players_tab->Add(players_active);

	auto players_window = new Checkbox;
	players_window->SetPosition(20 + 100, 68);
	players_window->SetTitle("Separate Window");
	players_window->SetValue(&V::PlayerList::Windowed);
	players_tab->Add(players_window);

	auto players_speclist = new Checkbox;
	players_speclist->SetPosition(20 + 120 * 2, 68);
	players_speclist->SetTitle("Spectator List");
	players_speclist->SetValue(&V::PlayerList::SpectatorList);
	players_tab->Add(players_speclist);

	auto players_list = new PlayerList;
	players_list->SetPosition(20, 95);
	players_tab->Add(players_list);

	auto specs_list = new SpectatorList;
	specs_list->SetPosition(iScrW / 2 - iMenuW / 2 - 250, iScrH / 2 - iMenuH / 2);
	specs_list->SetSize(250, 0);
	specs_list->is_separate_frame = true;

	auto external_radar = new Radar;
	external_radar->SetPosition(iScrW / 2 + iMenuW / 2, iScrH / 2 - iMenuH / 2);
	external_radar->SetSize(250, 250);
	external_radar->is_separate_frame = true;

	frame->Add(players_tab);

	// ============================================================================

	Add(frame);
	Add(external_radar);
	Add(specs_list);
}
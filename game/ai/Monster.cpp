#include "../../idlib/precompiled.h"

#include "AI.h"
#include "../Game_local.h"
#include "Monster.h"


CLASS_DECLARATION(idAI, Monster)
END_CLASS

Monster::Monster(void) {

}
void Monster::Spawn(void) {
	if (spawnArgs.GetBool("is_friendly")) {
		isFriendly = 1;
	}
}
void Monster::TakeDamage(int dmg) {
	if (dmg > 0) {
		dmg -= stk * 2;		// Reduces damage proportional to how stocky the receiver is.
		dmg = max(dmg, 1);	// Guarantees that attacks always deal damage, and never heal the opponent.
		switch (opponent->attackType) {
		case 1:
			if (attackType = 3)	// Unfavorable matchup: Windspeed < Firetech
				dmg = round(dmg * 1.75);
			if (attackType = 2)	// Favorable matchup: Waterforce > Firetech
				dmg = round(dmg * 0.55);
			break;
		case 2:
			if (attackType = 1)	// Unfavorable matchup: Firetech < Waterforce
				dmg = round(dmg * 1.75);
			if (attackType = 3)	// Favorable matchup: Waterforce > Waterforce
				dmg = round(dmg * 0.55);
			break;
		case 3:
			if (attackType = 2)	// Unfavorable matchup: Waterforce < Windspeed
				dmg = round(dmg * 1.75);
			if (attackType = 1)	// Favorable matchup: Firetech > Windspeed
				dmg = round(dmg * 0.55);
			break;
		}
		if (attackType = 5)		// If failed to recruit, take double damage.
			dmg *= 2;
	}
	HP -= dmg;
	HP = max(HP, 0);
}
void Monster::TakeDamageFixed(int dmg) {
	HP -= dmg;
	HP = max(HP, 0);
}

int Monster::Attack_Firetech(void) {
	attackType = 1;
	int rawDmg = str * 3 + spd;
	return rawDmg;
}
int Monster::Attack_Waterforce(void) {
	attackType = 2;
	int rawDmg = round(str * 1.25 + stk * 3);
	return rawDmg;
}
int Monster::Attack_Windspeed(void) {
	attackType = 3;
	int rawDmg = round(str * 1.5 + spd * 1.75);
	return rawDmg;
}

int Monster::Attack_AI(void) {
	int i;
	int randnum = rand() % 16;

	if (randnum < 9)
		i = 0;
	else if (randnum < 14)
		i = 1;
	else
		i = 2;
	attackType = attackPrefSequence[i];
	switch (attackPrefSequence[i]) {
	case 1:
		return Attack_Firetech();
		break;
	case 2:
		return Attack_Waterforce();
		break;
	case 3:
		return Attack_Windspeed();
		break;
	}
}
int Monster::AI_Choice(void) {
	return Attack_AI();
}

/*
	SPECIAL SKILLS
*/
//Firetech:
int Monster::Skill_PlasmaPunch(void) {
	attackType = 1;
	int rawDmg = round(10 + str * 3 + stk * 0.8 + spd);
	return rawDmg;
}
int Monster::Skill_ThunderShot(void) {
	attackType = 1;
	int rawDmg = 30 + spd * 2;
	return rawDmg;
}
int Monster::Skill_InfernoBreath(void) {
	attackType = 1;
	int rawDmg = 75 + stk;
	return rawDmg;
}

//Waterforce:
int Monster::Skill_MegaPound(void) {
	attackType = 2;
	int rawDmg = str * 2 + stk * 3;
	return rawDmg;
}
int Monster::Skill_BodySlam(void) {
	attackType = 2;
	int rawDmg = stk * 5 + 50;
	TakeDamageFixed(round(rawDmg / 2));
	return rawDmg;
}
int Monster::Skill_TsunamiWrecker(void) {
	attackType = 2;
	int rawDmg = str * 3 + stk + 3 + spd;
	return rawDmg;
}
//Windspeed:
int Monster::Skill_WindShear(void) {
	attackType = 3;
	int rawDmg = round(str * 1.5 + spd * 2 + 15);
	return rawDmg;
}
int Monster::Skill_Vortex(void) {
	attackType = 3;
	int rawDmg = round(str * 2 + spd * 3 + 45);
	return rawDmg;
}
int Monster::Skill_HurricaneStrike(void) {
	attackType = 3;
	int rawDmg = round(str * 2 + spd * 7 + 12);
	return rawDmg;
}
//Other:
int Monster::Skill_Hyperize(void) {
	attackType = 4;
	if(isHyper == 0)
		isHyper = rand() % 3 + 2;
	return 0;
}
int Monster::Skill_Devour(void) {
	attackType = 4;
	TakeDamageFixed(-1 * round(maxHP / 5));
	return 0;
}
int Monster::Skill_Roar(void) {
	attackType = 4;
	int threshold = 10 + (level - opponent->level);
	int randnum = rand() % 50;
	if (randnum < threshold)
		opponent->isAfraid = rand() % 3 + 2;
	return 0;
}
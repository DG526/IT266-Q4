#ifndef __Monster_H__
#define __Monster_H__


//#include "../../idlib/precompiled.h"


#include "AI.h"

class Monster : public idAI {
public:

	CLASS_PROTOTYPE(Monster);

	Monster(void);

	virtual void Spawn(void);
	int Attack_Firetech(void);
	int Attack_Waterforce(void);
	int Attack_Windspeed(void);
	void TakeDamage(int dmg);
	void TakeDamageFixed(int dmg);

	int Attack_AI(void);

	int AI_Choice(void);

	int					canAttack = 0;		// If set to 1, attack.
	Monster* opponent;
	int					isFriendly = 0;		// If set to 1, monster is under Player's control.
	int					level = 1;			// Determines skills & stats.
	int					experience = 0, expToNext = 1;
	int					maxHP = 1, HP = 1, str = 1, stk = 1, spd = 1;
	int					skillsLearned = 0;	// Determines what skills can be learned.
	int					attackPrefSequence[3] = { 2,1,3 }; // 1 = firetech, 2 = waterforce, 3 = windspeed.
	int					attackType; // Shows what type of attack was chosen; 1 = firetech, 2 = waterforce, 3 = windspeed, 4 = other/support, 5 = recruit attempt.

	//Special skill functions:
	//Firetech:
	int Skill_PlasmaPunch(void);
	int Skill_ThunderShot(void);
	int Skill_InfernoBreath(void);
	//Waterforce:
	int Skill_MegaPound(void);
	int Skill_BodySlam(void);
	int Skill_TsunamiWrecker(void);
	//Windspeed:
	int Skill_WindShear(void);
	int Skill_Vortex(void);
	int Skill_HurricaneStrike(void);
	//Other:
	int Skill_Hyperize(void);
	int Skill_Devour(void);
	int Skill_Roar(void);

	//Status:
	int isHyper = 0;	//If > 0, deal and recieve more damage, -1 every round until 0.
	int isAfraid = 0;	//If > 0, recieve more damage, -1 every round until 0.
};

#endif // !__Monster_H__
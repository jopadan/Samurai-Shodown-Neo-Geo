#ifndef __ModuleInput_H__
#define __ModuleInput_H__

#include "Module.h"
#include "Globals.h"
#include "p2Qeue.h"
#include "SDL\include\SDL_scancode.h"
#include "SDL/include/SDL_gamecontroller.h"

#define MAX_KEYS 300
#define JUMP_TIME 900
#define PUNCH_TIME 700
#define MED_PUNCH_TIME 700
#define HEAVY_PUNCH_TIME 700
#define CROUCH_PUNCH_TIME 500
#define CROUCH_KICK_TIME 500
#define HAWK_CARRY_TIME 7000
#define ANNUM_TIME 1500
#define AMUBEYATORO_TIME 700
#define YATORO_TIME 700
#define KAMUI_TIME 700
#define KICK_TIME  700
#define MED_KICK_TIME  700
#define HEAVY_KICK_TIME  700
#define TORNADO_TIME  1100
#define START_TIME  3000
#define MAX_BUTTONS 15


enum player_states
{
	ST_UNKNOWN,
	ST_IDLE,
	ST_WALK_FORWARD,
	ST_WALK_BACKWARD,
	ST_JUMP_NEUTRAL,
	ST_JUMP_FORWARD,
	ST_JUMP_BACKWARD,
	ST_CROUCH,
	ST_PUNCH_STANDING,
	ST_MEDIUM_PUNCH_STANDING,
	ST_HEAVY_PUNCH_STANDING,
	ST_PUNCH_NEUTRAL_JUMP,
	ST_PUNCH_FORWARD_JUMP,
	ST_PUNCH_BACKWARD_JUMP,
	ST_PUNCH_CROUCH,
	ST_MEDIUM_PUNCH_CROUCH,
	ST_HEAVY_PUNCH_CROUCH,
	ST_KICK_STANDING,
	ST_MEDIUM_KICK_STANDING,
	ST_HEAVY_KICK_STANDING,
	ST_KICK_NEUTRAL_JUMP,
	ST_KICK_FORWARD_JUMP,
	ST_KICK_BACKWARD_JUMP,
	ST_KICK_CROUCH,
	ST_MEDIUM_KICK_CROUCH,
	ST_HEAVY_KICK_CROUCH,
	ST_ANNU_MUTSUBE,
	ST_LEYLA_MUTSUBE,
	ST_DAMAGE,
	ST_BLOCK,
	ST_WIN,
	ST_DEFEAT,
	ST_HAWKCARRY,
	ST_YATORO_POKU,
	ST_KAMUI_MUTSUBE,
	ST_AMUBE_YATORO,

};
enum player_inputs
{
	IN_LEFT_DOWN,
	IN_LEFT_UP,
	IN_RIGHT_DOWN,
	IN_RIGHT_UP,
	IN_LEFT_AND_RIGHT,
	IN_JUMP,
	IN_CROUCH_UP,
	IN_CROUCH_DOWN,
	IN_JUMP_AND_CROUCH,
	IN_1,
	IN_2,
	IN_3,
	IN_4,
	IN_JUMP_FINISH,
	IN_PUNCH_FINISH,
	IN_KICK_FINISH,
	IN_TORNADO_FINISH,
	IN_LEFT_DOWN_P2,
	IN_LEFT_UP_P2,
	IN_RIGHT_DOWN_P2,
	IN_RIGHT_UP_P2,
	IN_LEFT_AND_RIGHT_P2,
	IN_JUMP_P2,
	IN_CROUCH_UP_P2,
	IN_CROUCH_DOWN_P2,
	IN_JUMP_AND_CROUCH_P2,
	IN_7,
	IN_8,
	IN_9,
	IN_0,
	IN_JUMP_FINISH_P2,
	IN_PUNCH_FINISH_P2,
	IN_KICK_FINISH_P2,
	IN_TORNADO_FINISH_P2,
	IN_DAMAGE,
	IN_DAMAGE_P2,
	IN_DAMAGE_FINISH,
	IN_DAMAGE_FINISH_P2,
	IN_PUNCH_CROUCH_FINISH,
	IN_PUNCH_CROUCH_FINISH_P2,
	IN_KICK_CROUCH_FINISH,
	IN_KICK_CROUCH_FINISH_P2,
	IN_BLOCK,
	IN_BLOCK_FINISH,
	IN_BLOCK_P2,
	IN_BLOCK_FINISH_P2,
	IN_WIN,
	IN_DEFEAT,
	IN_WIN_P2,
	IN_DEFEAT_P2,
	IN_WIN_FINISH,
	IN_DEFEAT_FINISH,
	IN_WIN_FINISH_P2,
	IN_DEFEAT_FINISH_P2,
	IN_IDLE,
	IN_HAWK_CARRY_FINISH,
	IN_HAWK_CARRY_FINISH_P2,
	IN_ANNU_MUTSUBE_FINISH,
	IN_LEYLA_MUTSUBE_FINISH,
	IN_ANNU_MUTSUBE_FINISH_P2,
	IN_LEYLA_MUTSUBE_FINISH_P2,
	IN_YATORO_POKU_FINISH,
	IN_KAMUI_MUTSUBE_FINISH,
	IN_AMUBE_YATORO_FINISH,


};




enum KEY_STATE
{
	KEY_IDLE = 0,
	KEY_DOWN,
	KEY_REPEAT,
	KEY_UP
};

//typedef unsigned char Uint8;

class ModuleInput : public Module
{
public:
	
	ModuleInput();
	~ModuleInput();

	bool Init();
	update_status PreUpdate();
	update_status PostUpdate();
	bool CleanUp();
	bool external_input();
	void internal_input(p2Qeue<player_inputs>& inputs, p2Qeue<player_inputs>& inputs2);

public:
	int h = 1;
	KEY_STATE keyboard[MAX_KEYS];
	Uint8 gamepad[MAX_BUTTONS];
	p2Qeue<player_inputs> inputs;
	p2Qeue<player_inputs> inputs2;
	int key = -1;
	Uint32 jump_timer = 0;
	Uint32 punch_timer = 0;
	Uint32 med_punch_timer = 0;
	Uint32 heavy_punch_timer = 0;
	Uint32 punch_c_timer = 0;
	Uint32 kick_c_timer = 0;
	Uint32 kick_timer = 0;
	Uint32 med_kick_timer = 0;
	Uint32 heavy_kick_timer = 0;
	Uint32 tornado_timer = 0;
	Uint32 Kamui_timer = 0;
	Uint32 Yatoro_timer = 0;
	Uint32 AnnuM_timer = 0;
	Uint32 LeylaM_timer = 0;
	Uint32 hawk_carry_timer = 0;
	Uint32 Amube_Yatoro_timer = 0;
	Uint32 jump_timer2 = 0;
	Uint32 punch_timer2 = 0;
	Uint32 med_punch_timer2 = 0;
	Uint32 heavy_punch_timer2 = 0;
	Uint32 punch_c_timer2 = 0;
	Uint32 kick_c_timer2 = 0;
	Uint32 kick_timer2 = 0;
	Uint32 med_kick_timer2 = 0;
	Uint32 heavy_kick_timer2 = 0;
	Uint32 tornado_timer2 = 0;
	Uint32 hawk_carry_timer2 = 0;
	Uint32 AnnuM_timer2 = 0;
	Uint32 LeylaM_timer2 = 0;
	Uint32 Yatoro_timer2 = 0;
	Uint32 Kamui_timer2 = 0;
	Uint32 AmubeYatoro_timer2 = 0;
	//Game Controller 1 handler
	SDL_GameController* gGameController = NULL;
	SDL_GameController* gGameController2 = NULL;

	SDL_Joystick *joy;

	const int JOYSTICK_DEAD_ZONE = 12000;
	int o=-1;
	bool left = false;
	bool right = false;
	bool down = false;
	bool up = false;
	bool left2 = false;
	bool right2 = false;
	bool down2 = false;
	bool up2 = false;
	bool playerinput = false;
	bool controller = false;

};

#endif // __ModuleInput_H__
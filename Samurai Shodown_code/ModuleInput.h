#ifndef __ModuleInput_H__
#define __ModuleInput_H__

#include "Module.h"
#include "Globals.h"
#include "p2Qeue.h"
#include "SDL\include\SDL_scancode.h"

#define MAX_KEYS 300
#define JUMP_TIME 800
#define PUNCH_TIME 700
#define CROUCH_PUNCH_TIME 500
#define KICK_TIME  700
#define TORNADO_TIME  1100
#define START_TIME  3000


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
	ST_PUNCH_NEUTRAL_JUMP,
	ST_PUNCH_FORWARD_JUMP,
	ST_PUNCH_BACKWARD_JUMP,
	ST_PUNCH_CROUCH,
	ST_KICK_STANDING,
	ST_KICK_NEUTRAL_JUMP,
	ST_KICK_FORWARD_JUMP,
	ST_KICK_BACKWARD_JUMP,
	ST_KICK_CROUCH,
	ST_TORNADO,
	ST_DAMAGE,
	ST_BLOCK,
	ST_WIN,
	ST_DEFEAT

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
	IN_1_P2,
	IN_2_P2,
	IN_3_P2,
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
	IN_IDLE

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

	KEY_STATE keyboard[MAX_KEYS];
	p2Qeue<player_inputs> inputs;
	p2Qeue<player_inputs> inputs2;
	int key = -1;
	Uint32 jump_timer = 0;
	Uint32 punch_timer = 0;
	Uint32 punch_c_timer = 0;
	Uint32 kick_timer = 0;
	Uint32 tornado_timer = 0;
	Uint32 jump_timer2 = 0;
	Uint32 punch_timer2 = 0;
	Uint32 punch_c_timer2 = 0;
	Uint32 kick_timer2 = 0;
	Uint32 tornado_timer2 = 0;


	bool left = false;
	bool right = false;
	bool down = false;
	bool up = false;
	bool left2 = false;
	bool right2 = false;
	bool down2 = false;
	bool up2 = false;
	bool playerinput = false;

};

#endif // __ModuleInput_H__
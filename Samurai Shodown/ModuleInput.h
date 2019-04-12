#ifndef __ModuleInput_H__
#define __ModuleInput_H__

#include "Module.h"
#include "Globals.h"
#include "p2Qeue.h"
#include "SDL\include\SDL_scancode.h"

#define MAX_KEYS 300
#define JUMP_TIME 1000
#define PUNCH_TIME 700

#define LEFT_DOWN 0
#define LEFT_UP 1
#define RIGHT_DOWN 2
#define RIGHT_UP 3
#define LEFT_AND_RIGHT 4
#define JUMP 5
#define CROUCH_UP 6
#define CROUCH_DOWN 7
#define JUMP_AND_CROUCH 8
#define ONE 9
#define JUMP_FINISH 10
#define PUNCH_FINISH 11
#define JUMP_UP 12

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
	ST_PUNCH_CROUCH
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
	IN_JUMP_FINISH,
	IN_PUNCH_FINISH
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
	bool external_input(p2Qeue<player_inputs>& inputs);
	void internal_input(p2Qeue<player_inputs>& inputs);

public:

	KEY_STATE keyboard[MAX_KEYS];
	p2Qeue<player_inputs> inputs;
	int key = -1;
	Uint32 jump_timer = 0;
	Uint32 punch_timer = 0;


};

#endif // __ModuleInput_H__
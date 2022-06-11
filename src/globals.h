#ifndef __GLOBALS_H__
#define __GLOBALS_H__

#include <cstdio>
#include <cstdlib>
#include <cstdarg>
#include <cstring>
#include <sys/param.h>

void log(const char file[], int line, const char* format, ...);

#define LOG(format, ...) log(__FILE__, __LINE__, format, ##__VA_ARGS__);

enum update_status
{
	UPDATE_CONTINUE = 1,
	UPDATE_STOP,
	UPDATE_ERROR
};

// Useful typedefs ---------
typedef unsigned int uint;

// Configuration -----------
#define SCREEN_SIZE 1
#define SCREEN_WIDTH 304
#define SCREEN_HEIGHT 224
#define WIN_FULLSCREEN 0
#define WIN_FULLSCREEN_DESKTOP 1
#define WIN_BORDERLESS 0
#define WIN_RESIZABLE 0
#define REN_VSYNC 1

#endif // __GLOBALS_H__

#include "game_time.h"
#include "stdint.h"
#include "time.h"

static float deltaTime;
static uint64_t lastFrameTime;

void Time_Init() {
	deltaTime = 0.f;
    lastFrameTime = clock();
}

void Time_Update() {
    uint64_t currentTime = clock();
    deltaTime = (float)(currentTime - lastFrameTime) / CLOCKS_PER_SEC;
    lastFrameTime = currentTime;
}

float Time_GetDeltaTime() {
	return deltaTime;
}

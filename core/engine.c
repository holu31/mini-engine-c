#include "engine.h"
#include "window.h"
#include "world.h"
#include "assets.h"
#include "game_time.h"

#include "GLFW/glfw3.h"

static scene_t* current_scene = NULL;

void Engine_Init() {
	Window_Create();
	Assets_Init();
	Time_Init();
}

void Engine_Run() {
	Window_Show();

	while (Window_IsRunning()) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.f, 0.f, 0.f, 1.f);

		SCENE_CALL(current_scene, Update);
		World_Update();
		Time_Update();

		Window_SwapBuffers();
		glfwPollEvents();
	}

	Window_Destroy();
	Assets_Free();
}

void Engine_SetScene(scene_t* scene) {
	SCENE_CALL(current_scene, Destroy);
	World_Create();
	current_scene = scene;
	SCENE_CALL(current_scene, Init);
}
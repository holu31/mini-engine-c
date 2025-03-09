#ifndef _SCENE_H_
#define _SCENE_H_

#define SCENE_CALL(scene, func, ...) \
	if (scene && scene->func) { \
		scene->func(__VA_ARGS__); \
	}

typedef struct {
	void (*Init)();
	void (*Update)();
	void (*Destroy)();
} scene_t;

#endif // _SCENE_H_
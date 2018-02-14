#include <imgui\imgui.h>
#include <imgui\imgui_impl_sdl_gl3.h>
#include <glm\common.hpp>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#define NPARTICLES 32767
#define GRAVITY -9.81f
#define v0 0.1f

namespace LilSpheres {
	extern const int maxParticles;
	extern void updateParticles(int startIdx, int count, float* array_data);
	extern float velocity;
}

struct particula {
	float x, y, z;
	float v, vo;
	float acc;
};

float array_particles[NPARTICLES * 3];
particula arrayStruct_particles[NPARTICLES];

bool show_test_window = false;
void GUI() {
	bool show = true;
	ImGui::Begin("Physics Parameters", &show, 0);

	// Do your GUI code here....
	{	
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);//FrameRate
		
	}
	// .........................
	
	ImGui::End();

	// Example code -- ImGui test window. Most of the sample code is in ImGui::ShowTestWindow()
	if(show_test_window) {
		ImGui::SetNextWindowPos(ImVec2(650, 20), ImGuiSetCond_FirstUseEver);
		ImGui::ShowTestWindow(&show_test_window);
	}
}

void PhysicsInit() {
	// Do your initialization code here...
	// ...................................
	srand(time(NULL));
	for (int i = 0; i < NPARTICLES; ++i) { //partícula en sí
		for (int j = 0; j < 3; ++j) { // x y z
			switch (j) {
			case 0:	//x
				arrayStruct_particles[i].x = 0;
				arrayStruct_particles[i].v = v0;
				arrayStruct_particles[i].acc = GRAVITY;
				array_particles[i * 3 + j] = 0;
				break;
			case 1: //y
				arrayStruct_particles[i].y = i;
				array_particles[i * 3 + j] = i;
				break;
			case 2:	//z
				arrayStruct_particles[i].z = 0;
				array_particles[i * 3 + j] = 0;
				break;
			}
		}
	}
}

void PhysicsUpdate(float dt) {
	// Do your update code here...
	// ...........................

	for (int i = 0; i < NPARTICLES; ++i) { //partícula en sí
		float velocidadLocal = GRAVITY/dt;
		for (int j = 0; j < 3; ++j) { // x y z [i*3+j]
			switch (j) {
			case 0:	//x

				array_particles[i * 3 + j] = arrayStruct_particles[i].x;
				break;
			case 1: //y
			{
				float aux = arrayStruct_particles[i].vo;
				arrayStruct_particles[i].vo = arrayStruct_particles[i].v;
				arrayStruct_particles[i].v = aux + arrayStruct_particles[i].acc*dt;
				arrayStruct_particles[i].y += arrayStruct_particles[i].v*dt + (1 / 2) * arrayStruct_particles[i].acc * dt *dt;

				array_particles[i * 3 + j] = arrayStruct_particles[i].y;
				break;
			}
			case 2:	//z
				array_particles[i * 3 + j] = arrayStruct_particles[i].z;
				break;
			}
		}
	}
	LilSpheres::updateParticles(0, NPARTICLES, array_particles);
}

void PhysicsCleanup() {
	// Do your cleanup code here...
	// ............................
}
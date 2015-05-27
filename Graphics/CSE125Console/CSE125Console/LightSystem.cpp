#include "stdafx.h"
#include "LightSystem.h"
#include "Window.h"

LightSystem::LightSystem()
{
}


LightSystem::~LightSystem()
{
}
void LightSystem::addLight(Light* l){
	lights.push_back(l);
}

void LightSystem::setCameraOffset(float x, float y, float z){
	camera_offset.x = x;
	camera_offset.y = y;
	camera_offset.z = z;

}
void LightSystem::initLights(){
	Light* l1 = new Light(0.0, 10.0, 0.0);
	Light* l2 = new Light(40.0, 10.0, 0.0);
	Light* l3 = new Light(-40.0, 10.0, 0.0);
	Light* l4 = new Light(0.0, 10.0, 40.0);
	Light* l5 = new Light(0.0, 10.0, -40.0);
	Light* l6 = new Light(28.0, 10.0, 28.0);
	//Light* l7 = new Light(-20.0, 20.0, 20.0);
	//Light* l8 = new Light(20.0, 20.0, 20.0);
	//Light* l9 = new Light(-20.0, 20.0, -20.0);
	//Light* l10 = new Light(20.0, 20.0, -20.0);

	l1->Ld = Vector3(1.0, 0.0, 0.0);
	l2->Ld = Vector3(0.0, 0.0, 1.0);
	l3->Ld = Vector3(0.0, 1.0, 0.4);
	l4->Ld = Vector3(0.8, 0.8, 0.0);
	l5->Ld = Vector3(0.8, 0.3, 0.0);
	l6->Ld = Vector3(0.0, 1.0, 1.0);

	lights.clear();
	lights.push_back(l1);
	lights.push_back(l2);
	lights.push_back(l3);
	lights.push_back(l4);
	lights.push_back(l5);
	lights.push_back(l6);
	//lights.push_back(l7);
	//lights.push_back(l8);
	//lights.push_back(l9);
	//lights.push_back(l10);


}

void LightSystem::renderLights(GameView* view){
	for (int i = 0; i < lights.size(); i++){
		view->PushEnvironmentNode(lights[i]);
	}
}

//This is for passing all the attribute of a light into the shader
void LightSystem::passUniform(GLuint program){
	if (lights.size() == 6){
		for (int i = 0; i < lights.size(); i++){
			float red = 0.0;
			float green = 0.0;
			float blue = 0.0;
			//red to green
			if (counter <= MAXCOUNTER){
				red = (MAXCOUNTER - 1.0*counter) / MAXCOUNTER;
				green = (1.0 * counter) / MAXCOUNTER;
				blue = 0.0;
			}
			//green to blue
			else if (counter <= 2 * MAXCOUNTER){
				green = (MAXCOUNTER - 1.0*(counter - MAXCOUNTER)) / MAXCOUNTER;
				blue = (1.0 * (counter - MAXCOUNTER)) / MAXCOUNTER;
				red = 0.0;
			}
			//blue to red
			else if (counter <= 3 * MAXCOUNTER){
				blue = (MAXCOUNTER - 1.0*(counter-2*MAXCOUNTER)) / MAXCOUNTER;
				red = (1.0 * (counter-2*MAXCOUNTER)) / MAXCOUNTER;
				green = 0.0;
			}
			//reset counter
			else{
				counter = 0;
				red = (MAXCOUNTER - 1.0*counter) / MAXCOUNTER;
				green = (1.0 * counter) / MAXCOUNTER;
				blue = 0.0;
			}
			counter = counter + 1;
			lights[i]->Ld = Vector3(red,green,blue);
		}
		float l1_pos[4] = { Window::light_system->lights[0]->localTransform.position.x, Window::light_system->lights[0]->localTransform.position.y, Window::light_system->lights[0]->localTransform.position.z, 1 };
		//cout << Window::light_system->lights[0]->localTransform.position.x << " " << Window::light_system->lights[0]->localTransform.position.y << " " << Window::light_system->lights[0]->localTransform.position.z << endl;
		glUniform4fv(glGetUniformLocation(program, "lights[0].position"), 1, l1_pos);
		float l2_pos[4] = { Window::light_system->lights[1]->localTransform.position.x, Window::light_system->lights[1]->localTransform.position.y, Window::light_system->lights[1]->localTransform.position.z, 1 };
		glUniform4fv(glGetUniformLocation(program, "lights[1].position"), 1, l2_pos);
		float l3_pos[4] = { Window::light_system->lights[2]->localTransform.position.x, Window::light_system->lights[2]->localTransform.position.y, Window::light_system->lights[2]->localTransform.position.z, 1 };
		glUniform4fv(glGetUniformLocation(program, "lights[2].position"), 1, l3_pos);
		float l4_pos[4] = { Window::light_system->lights[3]->localTransform.position.x, Window::light_system->lights[3]->localTransform.position.y, Window::light_system->lights[3]->localTransform.position.z, 1 };
		glUniform4fv(glGetUniformLocation(program, "lights[3].position"), 1, l4_pos);
		float l5_pos[4] = { Window::light_system->lights[4]->localTransform.position.x, Window::light_system->lights[4]->localTransform.position.y, Window::light_system->lights[4]->localTransform.position.z, 1 };
		glUniform4fv(glGetUniformLocation(program, "lights[4].position"), 1, l5_pos);
		float l6_pos[4] = { Window::light_system->lights[5]->localTransform.position.x, Window::light_system->lights[5]->localTransform.position.y, Window::light_system->lights[5]->localTransform.position.z, 1 };
		glUniform4fv(glGetUniformLocation(program, "lights[5].position"), 1, l6_pos);

		float l1_ld[3] = { Window::light_system->lights[0]->Ld.x, Window::light_system->lights[0]->Ld.y, Window::light_system->lights[0]->Ld.z };
		glUniform3fv(glGetUniformLocation(program, "lights[0].Ld"), 1, l1_ld);
		float l1_la[3] = { Window::light_system->lights[0]->La.x, Window::light_system->lights[0]->La.y, Window::light_system->lights[0]->La.z };
		glUniform3fv(glGetUniformLocation(program, "lights[0].La"), 1, l1_la);
		float l1_ls[3] = { Window::light_system->lights[0]->Ls.x, Window::light_system->lights[0]->Ls.y, Window::light_system->lights[0]->Ls.z };
		glUniform3fv(glGetUniformLocation(program, "lights[0].Ls"), 1, l1_ls);

		float l2_ld[3] = { Window::light_system->lights[1]->Ld.x, Window::light_system->lights[1]->Ld.y, Window::light_system->lights[1]->Ld.z };
		glUniform3fv(glGetUniformLocation(program, "lights[1].Ld"), 1, l2_ld);
		float l2_la[3] = { Window::light_system->lights[1]->La.x, Window::light_system->lights[1]->La.y, Window::light_system->lights[1]->La.z };
		glUniform3fv(glGetUniformLocation(program, "lights[1].La"), 1, l2_la);
		float l2_ls[3] = { Window::light_system->lights[1]->Ls.x, Window::light_system->lights[1]->Ls.y, Window::light_system->lights[1]->Ls.z };
		glUniform3fv(glGetUniformLocation(program, "lights[1].Ls"), 1, l2_ls);

		float l3_ld[3] = { Window::light_system->lights[2]->Ld.x, Window::light_system->lights[2]->Ld.y, Window::light_system->lights[2]->Ld.z };
		glUniform3fv(glGetUniformLocation(program, "lights[2].Ld"), 1, l3_ld);
		float l3_la[3] = { Window::light_system->lights[2]->La.x, Window::light_system->lights[2]->La.y, Window::light_system->lights[2]->La.z };
		glUniform3fv(glGetUniformLocation(program, "lights[2].La"), 1, l3_la);
		float l3_ls[3] = { Window::light_system->lights[2]->Ls.x, Window::light_system->lights[2]->Ls.y, Window::light_system->lights[2]->Ls.z };
		glUniform3fv(glGetUniformLocation(program, "lights[2].Ls"), 1, l3_ls);

		float l4_ld[3] = { Window::light_system->lights[3]->Ld.x, Window::light_system->lights[3]->Ld.y, Window::light_system->lights[3]->Ld.z };
		glUniform3fv(glGetUniformLocation(program, "lights[3].Ld"), 1, l4_ld);
		float l4_la[3] = { Window::light_system->lights[3]->La.x, Window::light_system->lights[3]->La.y, Window::light_system->lights[3]->La.z };
		glUniform3fv(glGetUniformLocation(program, "lights[3].La"), 1, l4_la);
		float l4_ls[3] = { Window::light_system->lights[3]->Ls.x, Window::light_system->lights[3]->Ls.y, Window::light_system->lights[3]->Ls.z };
		glUniform3fv(glGetUniformLocation(program, "lights[3].Ls"), 1, l4_ls);

		float l5_ld[3] = { Window::light_system->lights[4]->Ld.x, Window::light_system->lights[4]->Ld.y, Window::light_system->lights[4]->Ld.z };
		glUniform3fv(glGetUniformLocation(program, "lights[4].Ld"), 1, l5_ld);
		float l5_la[3] = { Window::light_system->lights[4]->La.x, Window::light_system->lights[4]->La.y, Window::light_system->lights[4]->La.z };
		glUniform3fv(glGetUniformLocation(program, "lights[4].La"), 1, l5_la);
		float l5_ls[3] = { Window::light_system->lights[4]->Ls.x, Window::light_system->lights[4]->Ls.y, Window::light_system->lights[4]->Ls.z };
		glUniform3fv(glGetUniformLocation(program, "lights[4].Ls"), 1, l5_ls);

		float l6_ld[3] = { Window::light_system->lights[5]->Ld.x, Window::light_system->lights[5]->Ld.y, Window::light_system->lights[5]->Ld.z };
		glUniform3fv(glGetUniformLocation(program, "lights[5].Ld"), 1, l6_ld);
		float l6_la[3] = { Window::light_system->lights[5]->La.x, Window::light_system->lights[5]->La.y, Window::light_system->lights[5]->La.z };
		glUniform3fv(glGetUniformLocation(program, "lights[5].La"), 1, l6_la);
		float l6_ls[3] = { Window::light_system->lights[5]->Ls.x, Window::light_system->lights[5]->Ls.y, Window::light_system->lights[5]->Ls.z };
		glUniform3fv(glGetUniformLocation(program, "lights[5].Ls"), 1, l6_ls);
	}
}


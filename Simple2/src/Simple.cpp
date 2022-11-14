#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <time.h>

#include "SDL.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"
#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_sdlrenderer.h"

#include "TextureInfo.h"
#include "MediaManager.h"
#include "ProtoGame.h"
#include "Sprite.h"
#include "Animation.h"
#include "Plant.h"
#include "Player.h"
#include "Particle.h"

using namespace std;

bool show_demo_window = true;
bool show_another_window = false;
ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
string filename = "img/player_0.bmp";

class Game:public ProtoGame {
	vector<Sprite *> sprites;
	Player *p;
	Sprite *background;
	Sprite *ground;
	//string filename = "img/player.bmp";
	public:
	Game():ProtoGame("Space Game",640,480,10){  // Size,Seed
		background = new Sprite(renderer, "img/morning_0.bmp");
		sprites.push_back(background);
		sprites.push_back(new Animation(renderer,"img/morning_",7,1000,0,0));
		ground = new Sprite(renderer, "img/ground.bmp");
		sprites.push_back(ground);
		sprites.push_back(new Animation(renderer,"img/HoneyshroomsStage_",3,1000,500,300));
		//double sx=getW()/2.0;
		//double sy=getH()/2.0;
		for (int i=0;i<10;i++) { //  Initialize Level loop
		  //double x=sx;
		  //double y=sy;
		  double vx=100.0*(1.0-(double)(rand()%2000)/1000.0);
		  double vy=100.0*(1.0-(double)(rand()%2000)/1000.0);
		  double ax=0.0;
		  double ay=10.0;
		  sprites.push_back(new Particle(renderer,"img/star.bmp",10,10,vx,vy,ax,ay));
	    } 

		setPlantName("HoneyShrooms", "img/HoneyshroomsStage_");

	    p=new Player(renderer,filename,60.0,60.0);
	    p->setBounds(0,w,60,h);
	    sprites.push_back(p);
		
		//Render text


	    // Start the Dear ImGui frame


        // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).

        
		
		Mix_Chunk *waves=mm.readWAV("img/earthshine.mp3");
	    if(Mix_PlayChannel(-1, waves, -1) == -1)
		{
			cout << "ERROR" << endl;
			cout << Mix_GetError() << endl;
		}
	}
	void doEvent(const SDL_Event &event){
		p->handleEvent(event);
		sprites.push_back(p);
		if(plantTrigger == true){
			sprites.push_back(newplant);
			plantTrigger = false;
		}
	}
	void loop(int millis) {
		ImGui_ImplSDLRenderer_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();
		if (show_demo_window)
            ImGui::ShowDemoWindow(&show_demo_window);
		//ImGui::EndFrame();
		ImGui::Render();
        SDL_SetRenderDrawColor(renderer, (Uint8)(clear_color.x * 255), (Uint8)(clear_color.y * 255), (Uint8)(clear_color.z * 255), (Uint8)(clear_color.w * 255));
		SDL_RenderClear(renderer);
        for (auto p:sprites) p->loop(millis);
		ImGui_ImplSDLRenderer_RenderDrawData(ImGui::GetDrawData());
		SDL_RenderCopy(renderer, texture, NULL, &dstrect);
        SDL_RenderPresent(renderer);
	}
    ~Game() {
		for (auto p:sprites) delete p;
	}
};

int main(int argc, char *argv[])
{
	Game g;
	g.doLoop();
    return 0;
}
#include <string>
#include <cstring>
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

bool show_inventory = false;
bool show_demo_window = true;
bool show_tutorial = false;
//bool npc_talk = false;
//bool my_tool_active = true;
bool show_journal = false;
ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
string filename = "img/player_0.bmp";

class Game:public ProtoGame {
	vector<Sprite *> sprites;
	Player *p;
	Sprite *background;
	Sprite *ground;
	Sprite *npc;
	Sprite *start;
	SDL_Event firstEvent;
	//int SDL_WaitEvent(SDL_Event * event);
	//Sprite *sellchest;
	//string filename = "img/player.bmp";
	public:
	Game():ProtoGame("Space Game",640,480,10){  // Size,Seed
		/* start = new Sprite(renderer, "img/startscreen.bmp");
		sprites.push_back(start);

		SDL_WaitEvent(&firstEvent);
		switch (firstEvent.type) {
			case SDL_KEYDOWN:
				if (firstEvent.key.keysym.sym==SDLK_KP_ENTER)
					SDL_PumpEvents();
				//printf("The %s key was pressed!\n",
					//SDL_GetKeyName(event.key.keysym.sym));
				break;
			case SDL_QUIT:
				exit(0);
   		}
		*/ 
		background = new Sprite(renderer, "img/morning_0.bmp");
		sprites.push_back(background);
		sprites.push_back(new Animation(renderer,"img/morning_",7,1000,0,0));
		ground = new Sprite(renderer, "img/ground.bmp");
		sprites.push_back(ground);
		//sprites.push_back(new Animation(renderer,"img/HoneyshroomsStage_",3,1000,500,300));
		//sellchest = new Sprite(renderer, "sellchest.bmp", (640-(70/2)), (152-(55/2)));
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
		npc = new Sprite(renderer, "img/npc.bmp",260,100);
		sprites.push_back(npc);

		setPlantName("HoneyShrooms", "img/HoneyshroomsStage_", 3, 100);
		setPlantName("Elaberries", "img/ElaberriesStage_", 4, 300);
		setPlantName("Moonflowers", "img/MoonflowersStage_", 3, 1000);

	    p=new Player(renderer,filename,60.0,60.0);
	    p->setBounds(0,w,60,h);
	    sprites.push_back(p);
		
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
		if(plantWaterTrigger == true){
			sprites.push_back(watering);
			plantWaterTrigger = false;
			//sprites.pop_back();
		}
	}
	void loop(int millis) {
		ImGui_ImplSDLRenderer_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();
		if (show_inventory)
		{
			ImGui::Begin("Main Menu", &show_inventory/*, ImGuiWindowFlags_MenuBar*/);
            //ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
			ImGui::Text("Wallet: %02d rocks", p->PlayerWallet);               // Display some text (you can use a format strings too)
			ImGui::TextColored(ImVec4(1,1,0,1), "Inventory");
			ImGui::BeginChild("Scrolling");
			for (int n = 1; n < 6; n++)
				ImGui::Text("%02d: Sample Item", n);
			ImGui::EndChild();
            ImGui::End();
        }
        if (show_tutorial)
        {
            ImGui::Begin("Tutorial", &show_tutorial);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
            ImGui::Text("Use the WASD keys to move.\nPress T to talk to NPCs.\nPress E to plant crops.\nPress Q to water them.\nOn the main menu,\nuse the drop down Choose Plant menu\nto select a plant you would\nlike to plant.");
            ImGui::End();
        }
		if (show_journal)
        {
            ImGui::Begin("Journal", &show_journal);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
            ImGui::Text("Day 1\nI have crash landed on an unknown alien planet. I wonder if it is inhabited?");
            ImGui::End();
		}
		if (npc_talk)
		{
			ImGui::Begin("Glup Shitto", &npc_talk);
			ImGui::Text("Hello there, strange one.");
			ImGui::End();
		}
		if (ImGui::BeginMainMenuBar())
		{
			if (ImGui::BeginMenu("Main Menu"))
			{
				if (ImGui::MenuItem("Tutorial")) {
					show_tutorial = true;
				}
				if (ImGui::MenuItem("Inventory")) {
					show_inventory = true;
				}
				if (ImGui::MenuItem("Journal")) {
					show_journal = true;
				}
				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("Choose Plant"))
			{
				if (ImGui::MenuItem("HoneyShrooms", "100 rocks")) {
					p->filenamePlant = plantNames[0].plantFilename;
					p->StageNum = plantNames[0].NumOfStages;
					p->pricePlant = plantNames[0].plantPrice;
				}
				if (ImGui::MenuItem("Elaberries", "300 rocks"))   {
					p->filenamePlant = plantNames[1].plantFilename;
					p->StageNum = plantNames[1].NumOfStages;
					p->pricePlant = plantNames[1].plantPrice;
					}
				if (ImGui::MenuItem("Moonflowers", "1000 rocks"))  {
					p->filenamePlant = plantNames[2].plantFilename;
					p->StageNum = plantNames[2].NumOfStages;
					p->pricePlant = plantNames[2].plantPrice;
				}
				ImGui::EndMenu();
			}
			ImGui::EndMainMenuBar();
		}
		//if (show_demo_window)
        //    ImGui::ShowDemoWindow(&show_demo_window);

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

/*
class TitleScreen:public ProtoGame
{
	vector<Sprite *> sprites;
	Player *p;
	Sprite *title;
	//Sprite *sellchest;
	//string filename = "img/player.bmp";
	public:
	TitleScreen():ProtoGame("Space Game",640,480,10){  // Size,Seed
		title = new Sprite(renderer, "img/startscreen.bmp");
		sprites.push_back(title);


	void loop()
	{
		const SDL_Event &e;
		if (e.key.keysym.sym==SDLK_KP_ENTER)  
		{
			Game g;
			~TitleScreen();
		}
		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, texture, NULL, &dstrect);
        SDL_RenderPresent(renderer);
	}

	~TitleScreen()
	{
		for (auto p:sprites) delete p;
	}
}
}
*/

int main(int argc, char *argv[])
{
	//TitleScreen t;
	Game g;
	g.doLoop();
    return 0;
}
#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <time.h>

#include "SDL.h"
#include "SDL_mixer.h"

#include "TextureInfo.h"
#include "MediaManager.h"
#include "ProtoGame.h"
#include "Sprite.h"
#include "Animation.h"
#include "Plant.h"
#include "Player.h"
#include "Particle.h"

using namespace std;

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
	}
	void loop(int millis) {
		SDL_RenderClear(renderer);
        for (auto p:sprites) p->loop(millis);
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
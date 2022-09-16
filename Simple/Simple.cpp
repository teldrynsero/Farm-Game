#include <string>
#include <iostream>
#include <vector>
#include <time.h>

#include "SDL2/SDL.h"

using namespace std;

class ProtoGame {
	SDL_Window *win;
	SDL_bool loopShouldStop;
	int w,h;  //  Dimension of screen space
	protected:
	SDL_Renderer *renderer;
	public:
	ProtoGame(string name,int newWidth=640,int newHeight=480,int seed=0) {
		win = NULL;
		renderer = NULL;
		w = newWidth;  //  Dimensions are part of the protogame class
		h = newHeight;
		loopShouldStop = SDL_FALSE;
		SDL_Init(SDL_INIT_VIDEO);
		// Added some parameters to constructor to set and store dimensions
		win = SDL_CreateWindow(name.c_str(),SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,w,h,0);
		renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
		if (seed==0) srand (time(NULL));
		else srand(seed);
	}
	int getW() { return w; } // Read-Only accessor methods
	int getH() { return h; } //  
	void doLoop() {
      int millis=SDL_GetTicks(); 
      while (!loopShouldStop)
      {
		unsigned millisDt=millis-SDL_GetTicks();  // Calculate millis
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_QUIT:
                    loopShouldStop = SDL_TRUE;
                    break;
            }
            doEvent(event);
        }
        if (millisDt>1) {  //
			loop(millisDt);
            millis=SDL_GetTicks();
		}
      }
	}
	virtual void doEvent(const SDL_Event &event)=0;
	virtual void loop(int millis)=0;
	~ProtoGame() {
      SDL_DestroyRenderer(renderer);
      SDL_DestroyWindow(win);
      SDL_Quit();
	}
};

class Player {
	SDL_Renderer *renderer;
	SDL_Texture *player;
	SDL_Rect SrcR,DestR;
	double px,py,vx,vy,ax,ay;
	public:
	Player(SDL_Renderer *newRenderer,
	   double newPx=0.0,double newPy=0.0,
	   double newVx=0.0,double newVy=0.0,
	   double newAx=0.0,double newAy=0.0) {
		renderer=newRenderer;
		player=NULL;
		SDL_Surface *bitmapSurface = NULL;
		bitmapSurface = SDL_LoadBMP("img/player.bmp");
		SrcR.x = 0;
		SrcR.y = 0;
		SrcR.w = bitmapSurface->w;
		SrcR.h = bitmapSurface->h;
		DestR=SrcR;
		player = SDL_CreateTextureFromSurface(renderer, bitmapSurface);		
		SDL_FreeSurface(bitmapSurface);
		px=newPx;
		py=newPy;
		vx=newVx;
		vy=newVy;
		ax=newAx;
		ay=newAy;	
	}
	void loop(int millis) {
		double dt=((float)millis)/1000.0; // Should this be in ProtoGame
        px+=vx*dt;
        py+=vy*dt;
        vx+=ax*dt;
        vy+=ay*dt;
        if (px>=640 || px<0) vx=-vx;
        if (py>=480 || py<0) vy=-vy;
        DestR.x=(int)px; 
        DestR.y=(int)py;            
        SDL_RenderCopy(renderer, player, &SrcR, &DestR);
	}
	~Player() {
		SDL_DestroyTexture(player);
	}
};

class Game:public ProtoGame {
	SDL_Texture *background;
	vector<Player *> players;
	public:
	Game():ProtoGame("Karls Supercool Game",640,480,10){  // Size,Seed
		background = NULL;
		SDL_Surface *bitmapSurface = NULL;
		bitmapSurface = SDL_LoadBMP("img/hello.bmp");
		background = SDL_CreateTextureFromSurface(renderer, bitmapSurface);
		for (int i=0;i<100;i++) { //  Initialize Level loop
		  double x=getW()*(double)(rand()%1000)/1000.0;
		  double y=getH()*(double)(rand()%1000)/1000.0;
		  double vx=0.0;
		  double vy=0.0;
		  double ax=0.0;
		  double ay=10.0;
		  players.push_back(new Player(renderer,x,y,vx,vy,ax,ay));
	    }
		SDL_FreeSurface(bitmapSurface);
	}
	void doEvent(const SDL_Event &event){
	}
	void loop(int millis) {
		SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, background, NULL, NULL);
        for (auto p:players) p->loop(millis);
        SDL_RenderPresent(renderer);
	}
    ~Game() {
		for (auto p:players) delete p;
		SDL_DestroyTexture(background);
	}
};

int main(int argc, char *argv[])
{
	Game g;
	g.doLoop();
    return 0;
}


//  g++ -std=c++17 Simple.cpp -ID:/msys64/mingw64/include/SDL2 -LD:/msys64/mingw64/lib -Wall -lmingw32 -lSDL2main -lSDL2 -o Simple

#include <string>
#include <iostream>
#include <vector>
#include <time.h>

#include "SDL2/SDL.h"

using namespace std;

class ProtoGame {
	SDL_Window *win;
	SDL_bool loopShouldStop;
	protected:
	int w,h;  //  Dimension of screen space
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

class Sprite { // Just draw no physics or keyboard
	SDL_Renderer *renderer;
	SDL_Texture *image;
	SDL_Rect SrcR,DestR;
	protected:
	double px,py;
	public:
	Sprite(SDL_Renderer *newRenderer,string filename,double newPx=0.0,double newPy=0.0) {
		renderer=newRenderer;
		image=NULL;
		SDL_Surface *bitmapSurface = NULL;
		bitmapSurface = SDL_LoadBMP(filename.c_str());
		SrcR.x = 0;
		SrcR.y = 0;
		SrcR.w = bitmapSurface->w;
		SrcR.h = bitmapSurface->h;
		DestR=SrcR;
		image = SDL_CreateTextureFromSurface(renderer, bitmapSurface);		
		SDL_FreeSurface(bitmapSurface);
		px=newPx;
		py=newPy;
	}
	virtual void handleEvent(SDL_Event &e) {} 
	virtual void loop(int millis) {
        DestR.x=(int)px; 
        DestR.y=(int)py;            
        SDL_RenderCopy(renderer, image, &SrcR, &DestR);
	}
	virtual ~Sprite() {
		SDL_DestroyTexture(image);
	}
};

class Player:public Sprite { // keyboard makes you move around
	int minX,maxX,minY,maxY;
	public:
	Player(SDL_Renderer *newRenderer,string filename,
	  double newPx=0.0,double newPy=0.0):Sprite(newRenderer,filename,newPx,newPy) {
		  minX=-1;
		  maxX=-1;
		  minY=-1;
		  maxY=-1;
	}
	void setBounds(int newMinX,int newMaxX,int newMinY,int newMaxY) {
		minX=newMinX;
		maxX=newMaxX;
		minY=newMinY;
		maxY=newMaxY;
	}
	void handleEvent(const SDL_Event &e) {
		// is the event a A keypress
		if (e.type==SDL_KEYDOWN) {
		   if (e.key.keysym.sym==SDLK_a) px--;
		   if (e.key.keysym.sym==SDLK_w) py--;
		   if (e.key.keysym.sym==SDLK_s) py++;
		   if (e.key.keysym.sym==SDLK_d) px++;	    
		}
		if (px<minX && minX!=-1) px=0;
		if (px>maxX && maxX!=-1) px=640;
		if (py<minY && minY!=-1) py=0;
		if (py>maxY && maxY!=-1) py=480;
	}
	~Player() {
	}
};

class Particle:public Sprite{  // Physics is ok
	double vx,vy,ax,ay;
	public:
	Particle(SDL_Renderer *newRenderer,string filename,
	  double newPx=0.0,double newPy=0.0,
	  double newVx=0.0,double newVy=0.0,
	  double newAx=0.0,double newAy=0.0):Sprite(newRenderer,filename,newPx,newPy){
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
        Sprite::loop(millis);
	}
	~Particle() {
	}
};

class Game:public ProtoGame {
	vector<Sprite *> sprites;
	Player *p;
	Sprite *background;
	public:
	Game():ProtoGame("Space Farm Game",640,480,10){  // Size,Seed
		background = new Sprite(renderer, "img/hello.bmp");
		sprites.push_back(background);
		double sx=getW()/2.0;
		double sy=getH()/2.0;
		for (int i=0;i<100;i++) { //  Initialize Level loop
		  double x=sx;
		  double y=sy;
		  double vx=100.0*(1.0-(double)(rand()%2000)/1000.0);
		  double vy=100.0*(1.0-(double)(rand()%2000)/1000.0);
		  double ax=0.0;
		  double ay=10.0;
		  sprites.push_back(new Particle(renderer,"img/player.bmp",x,y,vx,vy,ax,ay));
	    }
	    p=new Player(renderer,"img/player.bmp",10.0,10.0);
	    p->setBounds(0,0,w,h);
	    sprites.push_back(p);
	}
	void doEvent(const SDL_Event &event){
		p->handleEvent(event);
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
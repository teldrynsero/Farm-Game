#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <time.h>

#include "SDL.h"
#include "SDL_mixer.h"

using namespace std;

string filename = "img/player_0.bmp";

class TextureInfo {
	public:
	SDL_Texture* texture;
	SDL_Rect srcRect;
	TextureInfo(SDL_Texture *newTexture=NULL,const SDL_Rect &newSrcRect={0,0,0,0}){
		texture=newTexture;
		srcRect=newSrcRect;
	}
};

/* bool loadMedia()
{
	//Scene sprites
	SDL_Rect gSpriteClips[ 4 ];
	LTexture gSpriteSheetTexture;
    //Loading success flag
    bool success = true;
    //Load sprite sheet texture
    if( !gSpriteSheetTexture.loadFromFile( "spritesheet.bmp" ) )
    {
        printf( "Failed to load sprite sheet texture!\n" );
        success = false;
    }
    else
    {
        //Set front facing sprite
        gSpriteClips[ 0 ].x =   0;
        gSpriteClips[ 0 ].y =   0;
        gSpriteClips[ 0 ].w = 70;
        gSpriteClips[ 0 ].h = 110;
        //Set back facing sprite
        gSpriteClips[ 1 ].x = 70;
        gSpriteClips[ 1 ].y =   0;
        gSpriteClips[ 1 ].w = 70;
        gSpriteClips[ 1 ].h = 110;
        
        //Set left facing sprite
        gSpriteClips[ 2 ].x = 140;
        gSpriteClips[ 2 ].y = 0;
        gSpriteClips[ 2 ].w = 70;
        gSpriteClips[ 2 ].h = 110;
        //Set right facing sprite
        gSpriteClips[ 3 ].x = 210;
        gSpriteClips[ 3 ].y = 0;
        gSpriteClips[ 3 ].w = 70;
        gSpriteClips[ 3 ].h = 110;
    }
    return success;
} */

class MediaManager {
	map<string,TextureInfo> images;
	public:
	SDL_Texture *read(SDL_Renderer *renderer,string filename,SDL_Rect &SrcR) {
		if (images.find(filename)==images.end()) {
	 	  SDL_Texture *image=NULL;
		  SDL_Surface *bitmapSurface = NULL;
		  bitmapSurface = SDL_LoadBMP(filename.c_str());
		  SDL_SetColorKey(bitmapSurface,SDL_TRUE,SDL_MapRGB(bitmapSurface->format,0,0,255));
		  SrcR.x = 0;
		  SrcR.y = 0;
		  SrcR.w = bitmapSurface->w;
		  SrcR.h = bitmapSurface->h;
		  image = SDL_CreateTextureFromSurface(renderer, bitmapSurface);		
		  SDL_FreeSurface(bitmapSurface);
		  images[filename]=TextureInfo(image,SrcR); // should do an insert
		 //images.insert(pair<string,SDL_Texture*>(filename,image));
		  return image;	
	    }
	  TextureInfo texture=images[filename];
	  SrcR=texture.srcRect;  
	  return texture.texture;// find and return second
	}
	Mix_Chunk *readWAV(string music) {
		Mix_Chunk *waves = Mix_LoadWAV(music.c_str());
		if(!waves) cout << "ERROR: " << music << Mix_GetError() << endl; //throw Exception("Could not read WAV file "+filename);
		return waves;
	}	
};
MediaManager mm;

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
		SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
		// Added some parameters to constructor to set and store dimensions
		win = SDL_CreateWindow(name.c_str(),SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,w,h,0);
		renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
		if(Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
		{
		 	cout << "SDL2_mixer ERROR" << endl;
		}
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
	protected:
	SDL_Renderer *renderer;
	SDL_Texture *image;
	SDL_Rect SrcR,DestR;
	double px,py;
	public:
	Sprite(SDL_Renderer *newRenderer,string filename,double newPx=0.0,double newPy=0.0) {
		renderer=newRenderer;
		image=mm.read(renderer,filename,SrcR);
		//cout << "in class Sprite rendering " << filename << endl;
		DestR=SrcR;
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

class AnimationFrame {
	public:
	SDL_Texture *texture;
	int time;
	AnimationFrame(SDL_Texture *newTexture=NULL,int newTime=100){
		texture=newTexture;
		time=newTime;
	}
};

class Animation:public Sprite {
	vector<AnimationFrame> images;
	int totalTime;
	long currentTime;
	public:
	Animation(SDL_Renderer *newRenderer,string filename,int frames=1,int millisPerFrame=100,double newPx=0.0,double newPy=0.0) 
	  :Sprite(newRenderer,filename+"0.bmp",newPx,newPy){
		images.push_back(AnimationFrame(image,millisPerFrame));
		totalTime=millisPerFrame;
		for (int i=1;i<frames;i++) {
			SDL_Texture *t=mm.read(renderer,filename+to_string(i)+".bmp",SrcR);
			images.push_back(AnimationFrame(t,millisPerFrame));
			totalTime+=millisPerFrame;
			cout << filename << i << ".bmp" << endl;
		}
		currentTime=0;
	}
	void loop(int millis) {
        DestR.x=(int)px; 
        DestR.y=(int)py;        
        // convert current time to the frame of animation we need
        unsigned current=currentTime/100;
        if (current>images.size()) current=0;    
        SDL_RenderCopy(renderer, images[current/100].texture, &SrcR, &DestR);
        currentTime+=millis;
        currentTime=currentTime%totalTime;
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
			if (e.key.keysym.sym==SDLK_a)
			{
				px--;
				filename = "img/player_2.bmp";
			}
			if (e.key.keysym.sym==SDLK_w)
			{
				py--;
				//filename = "img/player_1.bmp";
			}
			if (e.key.keysym.sym==SDLK_s)
			{
				py++;
				//filename = "img/player_0.bmp";
			}
			if (e.key.keysym.sym==SDLK_d)
			{
				px++;
				//filename = "img/player_3.bmp";
			}
			//cout << filename << endl;
			//cout << px << endl;
			//cout << py << endl;    
		}
		if (px<minX && minX!=-1) px=0;
		if (px>maxX && maxX!=-1) px=640;
		if (py<minY && minY!=-1) py=0;
		if (py>maxY && maxY!=-1) py=480;

		//return filename;
	}
	~Player() {
	}
};

class Particle:public Sprite{  // Physics
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
        if (py>=150 || py<0) vy=-vy;
        Sprite::loop(millis);
	}
	~Particle() {
	}
};

class Game:public ProtoGame {
	vector<Sprite *> sprites;
	Player *p;
	Sprite *background;
	//string filename = "img/player.bmp";
	public:
	Game():ProtoGame("Space Game",640,480,10){  // Size,Seed
		background = new Sprite(renderer, "img/morning_0.bmp");
		sprites.push_back(background);
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
		//sprites.push_back(new Animation(renderer,"img/player_",3,100,0,0));
	    p=new Player(renderer,filename,30.0,30.0);
	    p->setBounds(0,w,0,h);
	    sprites.push_back(p);

		Mix_Chunk *waves=mm.readWAV("img/Electronic Fantasy.ogg");
	    if(Mix_PlayChannel(-1, waves, -1) == -1)
		{
			cout << "ERROR" << endl;
			cout << Mix_GetError() << endl;
		}
	    	//throw Exception("Could not play waves file");
	}
	void doEvent(const SDL_Event &event){
		p->handleEvent(event);
		//delete p;
		//p=new Player(renderer,filename,0,0);
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
#pragma once

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
			//cout << filename << i << ".bmp" << endl;
		}
		currentTime=rand()%600;
	}
	void loop(int millis) {
        DestR.x=(int)px; 
        DestR.y=(int)py;        
        // convert current time to the frame of animation we need
		//cout << currentTime << endl;
        unsigned current=abs(currentTime)/1000;
		//cout << "CURRENT: " << current << endl;
        if (current>images.size()){
			current=0;
		}
		//cout << currentTime << ' ' << current << endl;  
        SDL_RenderCopy(renderer, images[current].texture, &SrcR, &DestR);
        currentTime=(currentTime+millis)%totalTime;
	}
};
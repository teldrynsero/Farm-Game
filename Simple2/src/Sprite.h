#pragma once

class Sprite { // Just draw no physics or keyboard
	protected:
	SDL_Renderer *renderer;
	SDL_Texture *image;
	SDL_Rect SrcR,DestR;
	double px,py;
	bool watered;
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
	void setWatered(bool m){
		watered = m;
	};
	int getPx(){
		return px;
	}
	int getPy(){
		return py;
	}
	bool getWatered(){
		return watered;
	}
};
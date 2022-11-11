#pragma once

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
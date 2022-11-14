#pragma once

class Plant:public Sprite {
	vector<AnimationFrame> images;
	int totalTime;
	long currentTime;
	unsigned int framesNeeded;
	unsigned current = 0;
	public:
	Plant(SDL_Renderer *newRenderer,string filename,int frames=1,int millisPerFrame=100,double newPx=0.0,double newPy=0.0,int sprX=0,int sprY=0,int sprW=0,int sprH=0) 
	  :Sprite(newRenderer,filename+"0.bmp",newPx,newPy,sprX,sprY,sprW,sprH){
		images.push_back(AnimationFrame(image,millisPerFrame));
		totalTime=millisPerFrame;
		framesNeeded = frames;
		watered = false;
		for (int i=1;i<frames;i++) {
			SDL_Texture *t=mm.read(renderer,filename+to_string(i)+".bmp",SrcR,sprX,sprY,sprW,sprH);
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

        //unsigned current=abs(currentTime)/1000;

		//cout << "CURRENT: " << current << endl;
        /*if (current>images.size()){
			current=0;
		}*/
		//cout << currentTime << ' ' << current << endl;
		/*cout << "Current Time Before" << currentTime << endl;
        SDL_RenderCopy(renderer, images[current].texture, &SrcR, &DestR);
        currentTime=(currentTime+millis)%totalTime;
		cout << "Current Time After" << currentTime << endl; 
		cout << current << "djjjjjjj" << endl;*/
		//cout << framesNeeded << endl;
		//cout << images.size() << endl;
		if(current <= framesNeeded)
		{
			if(watered == true)
			{
				SDL_RenderCopy(renderer, images[current].texture, &SrcR, &DestR);
				currentTime=(currentTime+millis)%totalTime;
				watered = false;
				current++;
			}
			else
			{
				if(current == 0)
				{
					SDL_RenderCopy(renderer, images[current].texture, &SrcR, &DestR);
					currentTime=(currentTime+millis)%totalTime;
				}
				else
				{
					SDL_RenderCopy(renderer, images[current].texture, &SrcR, &DestR);
					currentTime=(currentTime+millis)%totalTime;
				}
			}
		}

	}
	int getPlantpx(){
		return px;
	}
	int getPlantpy(){
		return py;
	}
};

vector<Plant *> plants;
Plant *newplant;

struct plantName
{
	string namePlant;
	string plantFilename;
};
vector<plantName> plantNames;
int plantIndex = 0;
void setPlantName(string Xname, string Xfilename)
{
	plantNames.push_back(plantName());
	plantNames[plantIndex].namePlant = Xname;
	plantNames[plantIndex].plantFilename = Xfilename;
	plantIndex++;
}

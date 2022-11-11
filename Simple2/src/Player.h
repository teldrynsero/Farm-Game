#pragma once

bool plantTrigger = false;
bool plantWaterTrigger = false;
class Player:public Sprite { // keyboard makes you move around
	int minX,maxX,minY,maxY;

	string filename;

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
				image=mm.read(renderer,filename,SrcR);
			}
			if (e.key.keysym.sym==SDLK_w)
			{
				py--;
				filename = "img/player_1.bmp";
				image=mm.read(renderer,filename,SrcR);
			}
			if (e.key.keysym.sym==SDLK_s)
			{
				py++;
				filename = "img/player_0.bmp";
				image=mm.read(renderer,filename,SrcR);
			}
			if (e.key.keysym.sym==SDLK_d)
			{
				px++;
				filename = "img/player_3.bmp";
				image=mm.read(renderer,filename,SrcR);
			}
			if (e.key.keysym.sym==SDLK_e)
			{
				if(py > 164)
				{
					//cout << "THis is Happening" << endl;
					if(plants.empty() == true)
					{
						//cout << "This is empty" << endl;
						Mix_Music *plant = Mix_LoadMUS("img/plant.wav");
						if(Mix_PlayMusic(plant, 1) == -1)
						{
							printf(".WAV sound could not be played!\n"
									"SDL_Error: %s\n", SDL_GetError());
						}
						newplant = new Plant(renderer,"img/HoneyshroomsStage_",3,1000,px,py);
						plants.push_back(newplant);
						plantTrigger = true;
					}
					else
					{
						//cout << "This is not empty" << endl;
						bool plantArea = true;
						for (auto &h : plants) {
							if( ((px < h->getPlantpx() + 70 && px > h->getPlantpx() - 70) && 
								(py < h->getPlantpy() + 55 && py > h->getPlantpy() - 55)) )
							{
								//cout << "px " << px << " < getPx+55 " << h->getPlantpx() + 55 << " px " << px << " > getPx-55 " << h->getPlantpx() - 55 << endl;
								//cout << "py " << py << " < getPy+70 " << h->getPlantpy() + 70 << " py " << py << " > getPy-70 " << h->getPlantpy() - 70 << endl;
								plantArea = false;
							}
						}
						if(plantArea == true)
						{
							Mix_Music *plant = Mix_LoadMUS("img/plant.wav");
							if(Mix_PlayMusic(plant, 1) == -1)
							{
								printf(".WAV sound could not be played!\n"
										"SDL_Error: %s\n", SDL_GetError());
							}
							newplant = new Plant(renderer,"img/HoneyshroomsStage_",3,1000,px,py);
							plants.push_back(newplant);
							plantTrigger = true;
							//cout << "Plant Spawned" << endl;
						}
						else
						{
							plantArea = true;
							//cout << "Plant did Not Spawn" << endl;
						}
					}
				}
			}
			if (e.key.keysym.sym==SDLK_q)
			{
				Mix_Music *plant = Mix_LoadMUS("img/water.wav");
				if(Mix_PlayMusic(plant, 1) == -1)
				{
					printf(".WAV sound could not be played!\n"
							"SDL_Error: %s\n", SDL_GetError());
				}
				for (auto &h : plants) {
					if( (px < h->getPlantpx() + 30 && px > h->getPlantpx() - 30) && 
						(py < h->getPlantpy() + 20 && py > h->getPlantpy() - 20))
					{
						h->setWatered(true);
						plantWaterTrigger = true;
					}
				}
			}
			//cout << filename << endl;
			//cout << px << endl;
			//cout << py << endl;    
		}
		if (px<minX && minX!=-1) px=0;
		if (px>maxX && maxX!=-1) px=640;
		if (py<minY && minY!=-1) py=60;
		if (py>maxY && maxY!=-1) py=480;

		//return filename;
	}
	~Player() {
	}
};
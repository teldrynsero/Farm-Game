#pragma once

bool npc_talk = false;

vector<Sprite *> waterstuff;
Sprite *watering;

bool plantTrigger = false;
bool plantWaterTrigger = false;
class Player:public Sprite { // keyboard makes you move around
	public:
	int minX,maxX,minY,maxY;

	string filename;
	string facingPosition;
	int plantFileIndex = 0;
	string filenamePlant = "img/player_";
	int StageNum = 1;
	int pricePlant = 0;
	//start out with 9000 money
	int PlayerWallet = 9000;
	int HoldingPrice;

	//public:
	Player(SDL_Renderer *newRenderer,string filename,
	  double newPx=0.0,double newPy=0.0,int sprX=0,int sprY=0,int sprW=0,int sprH=0):Sprite(newRenderer,filename,newPx,newPy,sprX,sprY,sprW,sprH) {
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
			//cout << px << endl;
			//cout << py << endl;
			if (e.key.keysym.sym==SDLK_a)
			{
				px--;
				filename = "img/player_2.bmp";
				image=mm.read(renderer,filename,SrcR,0,0,70,110);
				facingPosition = "Left";
			}
			if (e.key.keysym.sym==SDLK_w)
			{
				py--;
				filename = "img/player_1.bmp";
				image=mm.read(renderer,filename,SrcR,0,0,70,110);
				facingPosition = "Up";
			}
			if (e.key.keysym.sym==SDLK_s)
			{
				py++;
				filename = "img/player_0.bmp";
				image=mm.read(renderer,filename,SrcR,0,0,70,110);
				facingPosition = "Down";
			}
			if (e.key.keysym.sym==SDLK_d)
			{
				px++;
				filename = "img/player_3.bmp";
				image=mm.read(renderer,filename,SrcR,0,0,70,110);
				facingPosition = "Right";
			}
			if (e.key.keysym.sym==SDLK_e)
			{

				cout << "px " << px << " py " << py << endl;
				if((px < 640 && px > 640-70) && (py < 150 && py > 150-55))
				{
					PlayerWallet += HoldingPrice;
					HoldingPrice = 0;
					cout << "PlayerWallet " << PlayerWallet << endl;
					cout << "HoldingPrice After Depositing " << HoldingPrice << endl;
				}

				if(facingPosition == "Left")//52
				{
					PlayerPlanting(-35-28+1, 51);
				}
				if(facingPosition == "Up")
				{
					PlayerPlanting(0, 50);
				}
				if(facingPosition == "Down")
				{
					PlayerPlanting(0, 60+35+11);
				}
				if(facingPosition == "Right")
				{
					PlayerPlanting(35+28-1, 51);
				}
			}
			if (e.key.keysym.sym==SDLK_q)
			{
				if(facingPosition == "Left")//52
				{
					PlayerWatering(-35-28+1, 51);
				}
				if(facingPosition == "Up")
				{
					PlayerWatering(0, 50);
				}
				if(facingPosition == "Down")
				{
					PlayerWatering(0, 60+35+11);
				}
				if(facingPosition == "Right")
				{
					PlayerWatering(35+28-1, 51);
				}
			}
			if (e.key.keysym.sym==SDLK_t)
			{
				if(px >= 185 && px <= 350 && py >= 100 && py <= 125)
				{
					//cout << "Glup Shitto NPC will talk here." << endl;
					npc_talk = true;
				}
			}
			/* if (e.key.keysym.sym==SDLK_f)
			{
				//std::cout << "Before " << plantFileIndex << " Space " << plantIndex;
				//std::cout.flush();
				if(plantFileIndex < plantIndex-1)
				{
					filenamePlant = plantNames[plantFileIndex].plantFilename;
					StageNum = plantNames[plantFileIndex].NumOfStages;
					pricePlant = plantNames[plantFileIndex].plantPrice;
					//cout << plantNames[plantFileIndex].namePlant << endl;
					plantFileIndex++;
					//cout << " If After " << plantFileIndex << endl;
				}
				else
				{
					filenamePlant = plantNames[plantFileIndex].plantFilename;
					StageNum = plantNames[plantFileIndex].NumOfStages;
					pricePlant = plantNames[plantFileIndex].plantPrice;
					//cout << plantNames[plantFileIndex].namePlant << endl;
					//cout << "Else After " << plantFileIndex << endl;
					plantFileIndex = 0;
				}
			
			}
			*/
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
	void selectPlant(int x)
	{
		filenamePlant = plantNames[x].plantFilename;
		StageNum = plantNames[x].NumOfStages;
		pricePlant = plantNames[x].plantPrice;
	}
	void PlayerPlanting(int horizontal, int vertical)
	{
		//cout << "This is Happening" << endl;
		if(plants.empty() == true)
		{
			if(py+vertical > 164)
			{
				//cout << "This is empty" << endl;
				Mix_Music *plant = Mix_LoadMUS("img/plant.wav");
				if(Mix_PlayMusic(plant, 1) == -1)
				{
					printf(".WAV sound could not be played!\n"
							"SDL_Error: %s\n", SDL_GetError());
				}
				//cout << filenamePlant << endl;
				//cout << StageNum << endl;
				//cout << pricePlant << endl;
				PlayerWallet -= pricePlant;
				newplant = new Plant(renderer,filenamePlant,StageNum,1000,px+horizontal,py+vertical, pricePlant);
				plants.push_back(newplant);
				plantTrigger = true;
			}
		}
		else
		{
			//cout << "This is not empty" << endl;
			bool plantArea = true;
			for (auto &h : plants) {
				if( ((px+horizontal < h->getPlantpx() + 70 && px+horizontal > h->getPlantpx() - 70) && 
					(py+vertical < h->getPlantpy() + 55 && py+vertical > h->getPlantpy() - 55)) )
				{
					//cout << "px " << px << " < getPx+55 " << h->getPlantpx() + 55 << " px " << px << " > getPx-55 " << h->getPlantpx() - 55 << endl;
					//cout << "py " << py << " < getPy+70 " << h->getPlantpy() + 70 << " py " << py << " > getPy-70 " << h->getPlantpy() - 70 << endl;
					plantArea = false;
				}
			}
			if(plantArea == true)
			{
				if(py+vertical > 164)
				{
					Mix_Music *plant = Mix_LoadMUS("img/plant.wav");
					if(Mix_PlayMusic(plant, 1) == -1)
					{
						printf(".WAV sound could not be played!\n"
								"SDL_Error: %s\n", SDL_GetError());
					}
					//cout << filenamePlant << endl;
					//cout << StageNum << endl;
					//cout << pricePlant << endl;
					PlayerWallet -= pricePlant;
					newplant = new Plant(renderer,filenamePlant,StageNum,1000,px+horizontal,py+vertical, pricePlant);
					plants.push_back(newplant);
					plantTrigger = true;
					//cout << "Plant Spawned" << endl;
				}
			}
			else
			{
				plantArea = true;
				//cout << "Plant did Not Spawn" << endl;
			}
		}
	}
	void PlayerWatering(int horizontal, int vertical)
	{
		watering = new Sprite(renderer,"img/watercan.bmp",px,py);
		waterstuff.push_back(watering);
		//plants.pop_back(watering);
		Mix_Music *plant = Mix_LoadMUS("img/water.wav");
		if(Mix_PlayMusic(plant, 1) == -1)
		{
			printf(".WAV sound could not be played!\n"
					"SDL_Error: %s\n", SDL_GetError());
		}
		for(long long unsigned int i = 0; i < plants.size(); i++){
			if( (px+horizontal < plants[i]->getPlantpx() + 30 && px+horizontal > plants[i]->getPlantpx() - 30) && 
				(py+vertical < plants[i]->getPlantpy() + 20 && py+vertical > plants[i]->getPlantpy() - 20))
			{
				if(plants[i]->isFullyGrown() == true){
					plants[i]->setWatered(true);
					cout << "FULLYGROWN" << endl;
					HoldingPrice = plants[i]->getPrice();
					cout << "HoldingPrice Before Depositing " << HoldingPrice << endl;
					plants.erase(plants.begin()+i);
				}else{
					cout << "NOT FULLYGROWN" << endl;
					plants[i]->setWatered(true);
					plantWaterTrigger = true;
				}
			}
		}
	}
	~Player() {
	}
};
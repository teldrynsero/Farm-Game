#pragma once

#include <string>

using namespace std;

class MediaManager {
	map<string,TextureInfo> images;
	public:
	SDL_Texture *read(SDL_Renderer *renderer,string filename,SDL_Rect &SrcR,int sprX,int sprY,int sprW,int sprH) {
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
		  //return image;	
	    }
	  TextureInfo texture=images[filename];
	  SrcR=texture.srcRect;  
	  if(sprW!=0 && sprH!=0)
	  {
		SrcR.x = sprX;
		SrcR.y = sprY;
		SrcR.w = sprW;
		SrcR.h = sprH;
	  }
	  return texture.texture;// find and return second
	}
	Mix_Chunk *readWAV(string music) {
		Mix_Chunk *waves = Mix_LoadWAV(music.c_str());
		if(!waves) cout << "ERROR: " << music << Mix_GetError() << endl; //throw Exception("Could not read WAV file "+filename);
		return waves;
	}	
};
MediaManager mm;
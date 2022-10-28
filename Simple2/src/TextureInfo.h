#pragma once

class TextureInfo {
	public:
	SDL_Texture* texture;
	SDL_Rect srcRect;
	TextureInfo(SDL_Texture *newTexture=NULL,const SDL_Rect &newSrcRect={0,0,0,0}){
		texture=newTexture;
		srcRect=newSrcRect;
	}
};
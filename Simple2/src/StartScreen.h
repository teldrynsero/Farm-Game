#pragma once
#include "SDL_mouse.h"

class Button: public Sprite{ // Draw starting screen
private:
    SDL_Renderer *renderer;
    SDL_Texture* startButton;
    SDL_Rect srcR, destR;
    int bx, by;
public:
    bool isClicked = false;
    Button(SDL_Renderer *newRenderer, string filename, int buttonX = 20, int buttonY = 400, int buttonH = 100, int buttonW = 400):Sprite(newRenderer, filename){
        renderer=newRenderer;
        // startButton = mm.read(renderer, filename, );
        startButton = mm.read(renderer, filename, srcR, buttonX, buttonY, buttonW, buttonH);
        bx = buttonX;
        by = buttonY;
    }
    void update(){

    }
    void draw(){

    }
};
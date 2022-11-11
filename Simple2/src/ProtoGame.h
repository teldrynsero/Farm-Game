#pragma once

string textname = "Space Game";

class ProtoGame {
	SDL_Window *win;
	SDL_bool loopShouldStop;
	protected:
	int w,h;  //  Dimension of screen space
	SDL_Renderer *renderer;
	SDL_Surface * surface;
	SDL_Texture * texture;
	SDL_Rect dstrect;
	int texW,texH;
	TTF_Font * font;
	SDL_Color color;
	public:
	ProtoGame(string name,int newWidth=640,int newHeight=480,int seed=0) {
		win = NULL;
		renderer = NULL;
		w = newWidth;  //  Dimensions are part of the protogame class
		h = newHeight;
		const char * c = textname.c_str();
		surface = NULL;
		//dstrect = NULL;
		loopShouldStop = SDL_FALSE;
		SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER | SDL_INIT_AUDIO);
		TTF_Init();
		// Added some parameters to constructor to set and store dimensions
		win = SDL_CreateWindow(name.c_str(),SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,w,h,0);
		renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
		if(Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
		{
		 	cout << "SDL2_mixer ERROR" << endl;
		}
		font = TTF_OpenFont("arial.ttf", 25);
		if(!font) {
    		printf("TTF_OpenFont: %s\n", TTF_GetError());
		}
		color = {255, 255, 255};
		surface = TTF_RenderText_Shaded(font, c, color, {255,200,200});
		texture = SDL_CreateTextureFromSurface(renderer, surface);
		texW = 0;
		texH = 0;
		SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
		dstrect = {300, 50, texW, texH};

		// Setup Dear ImGui context
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

		// Setup Dear ImGui style
		ImGui::StyleColorsDark();
		//ImGui::StyleColorsLight();

		// Setup Platform/Renderer backends
		ImGui_ImplSDL2_InitForSDLRenderer(win, renderer);
		ImGui_ImplSDLRenderer_Init(renderer);

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
			ImGui_ImplSDL2_ProcessEvent(&event);
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
	  ImGui_ImplSDLRenderer_Shutdown();
	  ImGui_ImplSDL2_Shutdown();
	  ImGui::DestroyContext();
	  SDL_DestroyTexture(texture);
	  SDL_FreeSurface(surface);
	  TTF_CloseFont(font);
      SDL_DestroyRenderer(renderer);
      SDL_DestroyWindow(win);
	  TTF_Quit();
      SDL_Quit();
	}
};
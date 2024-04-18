#include <SDL2/SDL.h> // include the main SDL header file
// #include <SDL2/SDL_image.h>
#include <iostream>

#define main SDL_main
#define WIDTH 1280 // width of the window
#define HEIGHT 720 // height of the window

bool running, fullscreen; // bool values to tell if program is running or if window is fullscreened

SDL_Renderer* renderer; // a struct that handles all rendering, settings to render, can only render things to the tied window
SDL_Window* window; // a window

int frameCount, timerFPS, lastFrame, fps; // variables to print out the frames each millisecond



int main(int argv, char** args)
{
    running = true;
    fullscreen = 0;
    static int lastTime = 0;
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0) std:: cout << "Failed at SDL_Init()" << std:: endl;
    if(SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, 0, &window, &renderer) < 0) std::cout << "Failed at SDL_CreateWindowAndRenderer()" << std::endl;
    
    SDL_SetWindowTitle(window, "SDL2 Window");
    SDL_ShowCursor(1);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "2");

    SDL_Surface *image = SDL_LoadBMP("pokemonBattleBacground.bmp");
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, image);

    while(running)
    {
        lastFrame = SDL_GetTicks();
        if(lastFrame >= (lastTime + 1000))
        {
            lastTime = lastFrame;
            fps = frameCount;
            frameCount = 0;
        }
        std::cout << fps << std::endl;

        update();
        input();
        draw(image, texture);
        


    }
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(image);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void update()
{
    if(fullscreen) SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
    if(!fullscreen) SDL_SetWindowFullscreen(window, 0);

}

void input()
{
    SDL_Event e;
    while(SDL_PollEvent(&e))
    {
        if(e.type == SDL_QUIT) running = false;
    }
    const Uint8 *keystates = SDL_GetKeyboardState(NULL);
    if(keystates[SDL_SCANCODE_ESCAPE]) running = false;
    if(keystates[SDL_SCANCODE_F11]) fullscreen = !fullscreen;
}

void draw(SDL_Surface *image, SDL_Texture *texture)
{
    // SDL_SetRenderDrawColor(renderer, 40, 43, 200, 255);
    SDL_Rect rect;
   

    rect.x=rect.y=0;
    rect.w=WIDTH;
    rect.h=HEIGHT;
    SDL_RenderFillRect(renderer, &rect);
    
    frameCount++;
    int timerFPS = SDL_GetTicks()-lastFrame;
    if(timerFPS <(1000/60))
    {
        SDL_Delay((1000/60)-timerFPS);
    }

    // SDL_RenderPresent(renderer);
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);
}
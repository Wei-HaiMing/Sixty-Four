#ifndef GAME_HPP
#define GAME_HPP
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>



class Game
{
    public:
        static int lastTime;
        // constructors
        Game();
        // getters
        bool getRunning()const;
        bool getFullscreen()const;
        int getFrameCount()const;
        int getTimerFPS()const;
        int getLastFrame()const;
        int getFps()const;
        SDL_Surface* getSurface()const;
        SDL_Texture* getTexture()const;
        static int getLastTime();
        SDL_Surface* getSprite()const;

        // setters
        void setRunning(bool running);
        void setFullscreen(bool fullscreen);
        void setFrameCount(int frameCount);
        void setTimerFPS(int timerFPS);
        void setLastFrame(int lastFrame);
        void setFps(int fps);
        void setSurface(SDL_Surface* image);
        void setTexture(SDL_Texture* texture);
        void setLastTime(int lastTime);
        void setSurface2(SDL_Surface* image);
        void setTexture2(SDL_Texture* texture2);
        void setSprite(SDL_Surface* sprite);

        // member methods
        void update();
        void input();
        void draw();
        void displayFPS();
        void kill();


    private:
        SDL_Renderer* renderer; // a struct that handles all rendering, settings to render, can only render things to the tied window
        SDL_Window* window; // a window 
        bool running, fullscreen;
        int frameCount, timerFPS, lastFrame, fps; // variables to print out the frames each millisecond
        SDL_Surface *image; // image for the background
        SDL_Texture *texture[7]; // create a texture using the renderer with the desired image
        SDL_Rect spritePosition;
        #define WIDTH 1280
        #define HEIGHT 720
        #define SPRITE_SIZE 32
};  




#endif // GAME_HPP
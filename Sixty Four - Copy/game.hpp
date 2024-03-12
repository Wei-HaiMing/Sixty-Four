#ifndef GAME_HPP
#define GAME_HPP
#include <SDL2/SDL.h>


class Game
{
    public:
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
        int getLastTime()const;
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
        SDL_Texture *texture; // create a texture using the renderer with the desired image
        int lastTime;
        #define WIDTH 1280
        #define HEIGHT 720
};  




#endif // GAME_HPP
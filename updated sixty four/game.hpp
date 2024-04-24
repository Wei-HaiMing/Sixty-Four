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
        SDL_Texture* getTexture(int loc)const;
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
        void setTexture(SDL_Texture* texture, int loc);
        void setLastTime(int lastTime);

        // member methods
        void update();
        void input();
        void draw();
        void displayFPS();
        void kill();
        void countFPS();


    private:
        SDL_Renderer* renderer; // a struct that handles all rendering, settings to render, can only render things to the tied window
        SDL_Window* window; // a window 
        bool running, fullscreen;
        int frameCount, timerFPS, lastFrame, fps; // variables to print out the frames each millisecond
        SDL_Surface *image; // image for the background
        SDL_Texture *texture[7]; // create a texture using the renderer with the desired image, texture[0] is the background image and texture[1:3] are player 1's pokemon and texture[4:] are player 2's pokemon
        SDL_Rect spritePosition;
        #define WIDTH 1280
        #define HEIGHT 720
        #define SPRITE_SIZE 96
        unsigned char userInput; 
        enum {
            USER_UP = (1 << 0),
            USER_DN = (1 << 1),
        };
};  




#endif // GAME_HPP
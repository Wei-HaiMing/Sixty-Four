#ifndef GAME_HPP
#define GAME_HPP
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "Pokemon.hpp"
// extern SDL_Renderer* renderer;
// extern SDL_Window* window;


class Game
{
    public:
        static int lastTime;
        // constructors
        Game(SDL_Renderer* renderer, SDL_Window* window);
        // getters
        bool getRunning()const;
        bool getFullscreen()const;
        int getFrameCount()const;
        int getTimerFPS()const;
        int getLastFrame()const;
        int getFps()const;
        SDL_Surface* getSurface()const;
        // SDL_Texture* getBGTexture()const;
        // SDL_Texture* Game::getP1Text(int loc)const;
        // SDL_Texture* Game::getP2Text(int loc)const;
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
        void setP1Text(SDL_Texture* texture, int loc);
        void setP2Text(SDL_Texture* texture, int loc);
        void setBGTexture(SDL_Texture* texture);
        void setLastTime(int lastTime);

        // member methods
        void update();
        void input();
        void draw();
        void displayFPS();
        void kill();
        void countFPS();
        void initFont();


    protected:
        Pokemon ;
        SDL_Renderer* renderer;
        SDL_Window* window;
        bool running, fullscreen;
        int active1, active2; // index to identify which pokemon sprite is to be displayed
        int frameCount, timerFPS, lastFrame, fps; // variables to print out the frames each millisecond
        SDL_Surface *image; // image for the background
        SDL_Texture *bgTexture, *playerOne[3], *playerTwo[3], *fontText; // create a texture using the renderer with the desired image, texture[0] is the background image and texture[1:3] are player 1's pokemon and texture[4:] are player 2's pokemon
        SDL_Rect spritePosition;
        TTF_Font *font; 
        #define WIDTH 1280
        #define HEIGHT 720
        #define SPRITE_SIZE 96
        unsigned char userInput; 
        enum {
            USER_UP = (1 << 0),
            USER_DN = (1 << 1),
            USER_LT = (1 << 2),
            USER_RT = (1 << 3),
            USER_EN = (1 << 4)
        };
        enum {
            HELLO = 0,
        };
        struct textData{
            SDL_Texture* textTex;
            int w;
            int h;
        };
        textData textArr[34];
        const char* strArr[34] = {"Hello", "Hello", 
        "Hello", "Hello", 
        "Hello", "Hello","Hello", "Hello","Hello", "Hello","Hello", "Hello","Hello", "Hello","Hello", "Hello","Hello", "Hello","Hello", "Hello","Hello", "Hello","Hello", "Hello","Hello", "Hello","Hello", "Hello","Hello", "Hello","Hello", "Hello","Hello", "Hello",};
};  




#endif // GAME_HPP
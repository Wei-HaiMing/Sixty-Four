#ifndef GAME_HPP
#define GAME_HPP
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "Pokemon.hpp"
#include "PokemonMove.hpp"
// #include "PokemonMove.hpp"
#include <string>
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
        Move tackle, razorLeaf, magicalLeaf, bodySlam, ember, quickAttack, flameWheel, scratch, waterGun, aquaTail, slash, vineWhip, waterPulse, fireFang, flameThrower;
        Move chikoritaMoves[4], totodileMoves[4], cyndaquilMoves[4], bulbasaurMoves[4], squirtleMoves[4], charmanderMoves[4];
        // Pokemon chikorita("Chikorita", "Grass", );
        Pokemon team1[3], team2[3];
        SDL_Renderer* renderer;
        SDL_Window* window;
        bool running, fullscreen;
        int active1, active2; // index to identify which pokemon sprite is to be displayed
        int frameCount, timerFPS, lastFrame, fps; // variables to print out the frames each millisecond
        SDL_Surface *image; // image for the background
        SDL_Texture *bgTexture, *playerOne[3], *playerTwo[3], *fontText, *arrowText, *menuText; // create a texture using the renderer with the desired image, texture[0] is the background image and texture[1:3] are player 1's pokemon and texture[4:] are player 2's pokemon
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
            CHIKORITA_NAME = 0,
            TOTODILE_NAME = 1,
            CYNDAQUIL_NAME = 2,
            BULBASAUR_NAME = 3,
            SQUIRTLE_NAME = 4,
            CHARMANDER_NAME = 5,
            CHIKORITA_HP = 6,
            TOTODILE_HP = 7,
            CYNDAQUIL_HP = 8,
            BULBASAUR_HP = 9,
            SQUIRTLE_HP = 10,
            CHARMANDER_HP = 11,
            GRASS = 12,
            WATER = 13,
            FIRE = 14,
            NORMAL = 15,
            TACKLE = 16,
            RAZOR_LEAF = 17,
            MAGICAL_LEAF = 18,
            BODY_SLAM = 19,
            SCRATCH = 20,
            WATER_GUN = 21,
            SLASH = 22,
            AQUA_TAIL = 23,
            EMBER = 24,
            QUICK_ATTACK = 25,
            FLAME_WHEEL = 26,
            VINE_WHIP = 27,
            WATER_PULSE = 28,
            FIRE_FANG = 29,
            FLAMETHROWER = 30,


        };
        struct textData{
            SDL_Texture* textTex;
            int w;
            int h;
        };
        textData textArr[34];
        const char* strArr[34] = {team1[0].getName().c_str(), team1[1].getName().c_str(), 
                team1[2].getName().c_str(), team2[0].getName().c_str(), 
                team2[1].getName().c_str(), team2[2].getName().c_str(), std::to_string(team1[0].getHP()).c_str(), 
                std::to_string(team1[1].getHP()).c_str(), std::to_string(team1[2].getHP()).c_str(), std::to_string(team2[0].getHP()).c_str(),
                std::to_string(team2[1].getHP()).c_str(), std::to_string(team2[2].getHP()).c_str(), "Grass", 
                "Water","Fire", "Normal",
                team1[0].getMove(0).getName().c_str(), team1[0].getMove(1).getName().c_str(), team1[0].getMove(2).getName().c_str(), 
                team1[0].getMove(3).getName().c_str(), team1[1].getMove(0).getName().c_str(), team1[1].getMove(1).getName().c_str(), team1[1].getMove(2).getName().c_str(), 
                team1[1].getMove(3).getName().c_str(), team1[2].getMove(1).getName().c_str(), team1[2].getMove(2).getName().c_str(), team1[2].getMove(3).getName().c_str(), 
                team2[0].getMove(1).getName().c_str(), team2[1].getMove(2).getName().c_str(), team2[2].getMove(2).getName().c_str(), team2[2].getMove(3).getName().c_str(), 
                "Hello","Hello", "Hello",
        };
};  




#endif // GAME_HPP
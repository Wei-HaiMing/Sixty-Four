#ifndef GAME_HPP
#define GAME_HPP
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "Pokemon.hpp"
#include "PokemonMove.hpp"
#include "Items.hpp"
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
        std::string getP1Choice()const;
        std::string getP2Choice()const;
        // SDL_Texture* getBGTexture()const;
        // SDL_Texture* Game::getP1Text(int loc)const;
        // SDL_Texture* Game::getP2Text(int loc)const;
        static int getLastTime();
        SDL_Surface* getSprite()const;
        std::string getMenuState()const;
        std::string getTurn()const;

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
        void setP1Choice(std::string p1Choice);
        void setP2Choice(std::string p1Choice);
        void setMenuState(std::string menuState);
        void setTurn(std::string turn);
        // member methods
        void update();
        void input();
        void draw();
        void displayFPS();
        void kill();
        void countFPS();
        void initFont();
        void heal(std::string whomst);
        void attack();
        void swap();
        // void printArr(const char*, int);


    protected:
        int arrowXPos, arrowYPos;
        int p1SwapTo, p2SwapTo;
        int arrowShiftRt, arrowShiftLt, arrowShiftUp, arrowShiftDn, arrowShiftX, arrowShiftY;
        bool p1Done, p2Done;
        std::string p1Choice, p2Choice, menuState, turn, controlMenu;
        SDL_Rect spriteRect1; // sprite rectangle for player 1's pokemon
        SDL_Rect spriteRect2; // sprite rectangle for player 2's pokemon
        SDL_Rect dstrect;
        SDL_Rect menu;
        SDL_Rect arrow;
        SDL_Rect potion, fullRestore, sodaPop;
        Items inventory1, inventory2;
        Move tackle, razorLeaf, magicalLeaf, bodySlam, ember, quickAttack, flameWheel, scratch, waterGun, aquaTail, slash, vineWhip, waterPulse, fireFang, flameThrower, doubleEdge, takeDown, powerWhip, facade, rapidSpin, hydroPump, aquaJet, falseSwipe, flareBlitz;
        Move chikoritaMoves[4], totodileMoves[4], cyndaquilMoves[4], bulbasaurMoves[4], squirtleMoves[4], charmanderMoves[4];
        // Pokemon chikorita("Chikorita", "Grass", );
        Pokemon team1[3], team2[3];
        SDL_Renderer* renderer;
        SDL_Window* window;
        bool running, fullscreen;
        int active1, active2; // index to identify which pokemon sprite is to be displayed
        int frameCount, timerFPS, lastFrame, fps; // variables to print out the frames each millisecond
        SDL_Surface *image;
        SDL_Texture *bgTexture, *playerOne[3], *playerTwo[3], *fontText, *arrowText, *menuText,  *emptyMenuText, *itemText[3], *itemFontText[3], *moveMenu, *backButton; // create a texture using the renderer with the desired image, texture[0] is the background image and texture[1:3] are player 1's pokemon and texture[4:] are player 2's pokemon
        SDL_Rect spritePosition;
        TTF_Font *font; 
        int timer;
        #define WIDTH 1280
        #define HEIGHT 720
        #define SPRITE_SIZE 96
        unsigned char userInput; 
        enum {
            USER_UP = (1 << 0),
            USER_DN = (1 << 1),
            USER_LT = (1 << 2),
            USER_RT = (1 << 3),
            USER_EN = (1 << 4),
            USER_BK = (1 << 5)
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
            TACKLE = 12,
            RAZOR_LEAF = 13,
            MAGICAL_LEAF = 14,
            BODY_SLAM = 15,
            SCRATCH = 16,
            WATER_GUN = 17,
            SLASH = 18,
            AQUA_TAIL = 19,
            EMBER = 20,
            QUICK_ATTACK = 21,
            FLAME_WHEEL = 22,
            VINE_WHIP = 23,
            WATER_PULSE = 24,
            FIRE_FANG = 25,
            FLAMETHROWER = 26,
            SUPER_EFFECTIVE = 27,
            NOT_EFFECTIVE = 28,
            PROMPT_P1 = 29,
            PROMPT_P2 = 30,
            POTIONS1 = 31,
            FULL_RESTORES1 = 32,
            SODA_POPS1 = 33,
            POTIONS2 = 34,
            FULL_RESTORES2 = 35,
            SODA_POPS2 = 36,
            GRASS = 37,
            WATER = 38,
            FIRE = 39,
            DOUBLE_EDGE = 40,
            TAKE_DOWN = 41,
            POWER_WHIP = 42,
            FACADE = 43,
            RAPID_SPIN = 44,
            HYDRO_PUMP = 45,
            AQUA_JET = 46,
            FALSE_SWIPE = 47,
            FLARE_BLITZ = 48,
            P1_SWAP = 49,
            P2_SWAP = 50,
            P1_HEAL = 51,
            P2_HEAL = 52,
            CHIK_TACKLE_1 = 53,
            CHIK_RAZOR_2 = 54,
            CHIK_MAGIC_3 = 55,
            CHIK_SLAM_4 = 56,
            TOTO_SCRATCH_1 = 57,
            TOTO_GUN_2 = 58,
            TOTO_SLASH_3 = 59,
            TOTO_TAIL_4 = 60,
            CYNDA_EMBER_1 = 61,
            CYNDA_QUICK_2 = 62,
            CYNDA_WHEEL_3 = 63,
            CYNDA_EDGE_4 = 64,
            BULBA_VINE_1 = 65,
            BULBA_TAKE_2 = 66,
            BULBA_POWER_3 = 67,
            BULBA_FACADE_4 = 68,
            SQUI_SPIN_1 = 69,
            SQUI_PULSE_2 = 70,
            SQUI_PUMP_3 = 71,
            SQUI_JET_4 = 72,
            CHARM_FANG_1 = 73,
            CHARM_THROWER_2 = 74,
            CHARM_SWIPE_3 = 75,
            CHARM_BLITZ_4 = 76
        };
        struct textData{
            SDL_Texture* textTex;
            int w;
            int h;
        };
        textData textArr[77];
        const char* strArr[77] = {team1[0].getName().c_str(), team1[1].getName().c_str(), 
                team1[2].getName().c_str(), team2[0].getName().c_str(), 
                team2[1].getName().c_str(), team2[2].getName().c_str(), std::to_string(team1[0].getHP()).c_str(), 
                std::to_string(team1[1].getHP()).c_str(), std::to_string(team1[2].getHP()).c_str(), std::to_string(team2[0].getHP()).c_str(),
                std::to_string(team2[1].getHP()).c_str(), std::to_string(team2[2].getHP()).c_str(), 
                team1[0].getMove(0).getName().c_str(), team1[0].getMove(1).getName().c_str(), team1[0].getMove(2).getName().c_str(), 
                team1[0].getMove(3).getName().c_str(), team1[1].getMove(0).getName().c_str(), team1[1].getMove(1).getName().c_str(), team1[1].getMove(2).getName().c_str(), 
                team1[1].getMove(3).getName().c_str(), team1[2].getMove(1).getName().c_str(), team1[2].getMove(2).getName().c_str(), team1[2].getMove(3).getName().c_str(), 
                team2[0].getMove(1).getName().c_str(), team2[1].getMove(2).getName().c_str(), team2[2].getMove(2).getName().c_str(), team2[2].getMove(3).getName().c_str(), 
                "It's super effective!","It's not very effective...", "Player 1, what will you do?", "Player 2, what will you do?", 
                "", "", "", "", "", "", "Grass", "Water", "Fire",
                team1[2].getMove(0).getName().c_str(), team2[0].getMove(0).getName().c_str(), team2[0].getMove(2).getName().c_str(), team2[0].getMove(3).getName().c_str(), 
                team2[1].getMove(0).getName().c_str(), team2[1].getMove(1).getName().c_str(), team2[1].getMove(3).getName().c_str(), team2[2].getMove(0).getName().c_str(), 
                team2[2].getMove(1).getName().c_str(), "Player 1 switched Pokemon!", "Player 2 switched Pokemon!", "Player 1 healed their active Pokemon!", "Player 2 healed their active Pokemon!",
                "Chikorita used Tackle!", "Chikorita used Razor Leaf!", "Chikorita used Magical Leaf!", "Chikorita used Body Slam!",
                "Totodile used Scratch!", "Totodile used Water Gun!", "Totodile used Slash!", "Totodile used Aqua Tail!",
                "Cyndaquil used Ember!", "Cyndaquil used Quick Attack!", "Cyndaquil used Flame Wheel!", "Cyndaquil used Double Edge!",
                "Bulbasaur used Vine Whip!", "Bulbasaur used Take Down!", "Bulbasaur used Power Whip!", "Bulbasaur used Facade!",
                "Squirtle used Rapid Spin!", "Squirtle used Water Pulse!", "Squirtle used Hydro Pump!", "Squirtle used Aqua Jet!",
                "Charmander used Fire Fang!", "Charmander used Flamethrower!", "Charmander used False Swipe!", "Charmander used Flare Blitz!"
        };
        // const std::string strArr[38] = {team1[0].getName().c_str(), team1[1].getName().c_str(), 
        //         team1[2].getName().c_str(), team2[0].getName().c_str(), 
        //         team2[1].getName().c_str(), team2[2].getName().c_str(), std::to_string(team1[0].getHP()).c_str(), 
        //         std::to_string(team1[1].getHP()).c_str(), std::to_string(team1[2].getHP()).c_str(), std::to_string(team2[0].getHP()).c_str(),
        //         std::to_string(team2[1].getHP()).c_str(), std::to_string(team2[2].getHP()).c_str(), "Grass", 
        //         "Water","Fire", "Normal",
        //         team1[0].getMove(0).getName().c_str(), team1[0].getMove(1).getName().c_str(), team1[0].getMove(2).getName().c_str(), 
        //         team1[0].getMove(3).getName().c_str(), team1[1].getMove(0).getName().c_str(), team1[1].getMove(1).getName().c_str(), team1[1].getMove(2).getName().c_str(), 
        //         team1[1].getMove(3).getName().c_str(), team1[2].getMove(1).getName().c_str(), team1[2].getMove(2).getName().c_str(), team1[2].getMove(3).getName().c_str(), 
        //         team2[0].getMove(1).getName().c_str(), team2[1].getMove(2).getName().c_str(), team2[2].getMove(2).getName().c_str(), team2[2].getMove(3).getName().c_str(), 
        //         "It's super effective!","It's not very effective...", "Player 1, what will you do?", "Player 2, what will you do?", 
        //         "", "", ""
        // };
        // std::string strArr[38] = {team1[0].getName(), team1[1].getName(), 
        //     team1[2].getName(), team2[0].getName(), 
        //     team2[1].getName(), team2[2].getName(), std::to_string(team1[0].getHP()), 
        //     std::to_string(team1[1].getHP()), std::to_string(team1[2].getHP()).c_str(), std::to_string(team2[0].getHP()).c_str(),
        //     std::to_string(team2[1].getHP()), std::to_string(team2[2].getHP()), "Grass", 
        //     "Water","Fire", "Normal",
        //     team1[0].getMove(0).getName(), team1[0].getMove(1).getName(), team1[0].getMove(2).getName(), 
        //     team1[0].getMove(3).getName(), team1[1].getMove(0).getName(), team1[1].getMove(1).getName(), team1[1].getMove(2).getName(), 
        //     team1[1].getMove(3).getName(), team1[2].getMove(1).getName(), team1[2].getMove(2).getName(), team1[2].getMove(3).getName(), 
        //     team2[0].getMove(1).getName(), team2[1].getMove(2).getName(), team2[2].getMove(2).getName(), team2[2].getMove(3).getName(), 
        //     "It's super effective!","It's not very effective...", "Player 1, what will you do?", "Player 2, what will you do?", 
        //     "", "", ""
        // };

};  
// ("x" + to_string(inventory1.getPotions()) + " Potions").c_str(),
// ("x" + to_string(inventory1.getSodaPops()) + " Soda Pops").c_str(),  "Yes", ""
// ("x" + to_string(inventory1.getFullRestores()) + " Full Restores").c_str()




#endif // GAME_HPP
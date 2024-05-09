#include "game.hpp"
#include <cassert>
#include <iostream>


int Game::lastTime = 0;
// constructors
Game::Game(SDL_Renderer* renderer, SDL_Window* window)
{
    timer = 0;
    hold = "";
    p1SwapTo = -1;
    p2SwapTo = -1;
    arrowShiftLt = 0;
    arrowShiftRt = 0;
    arrowShiftDn = 0;
    arrowShiftUp = 0;
    arrowShiftX = 0;
    arrowShiftY = 0;
    arrowXPos = 580;
    arrowYPos = 555;
    death = "yeet";
    controlMenu = "res/trans_menu.png";
    this->renderer = renderer;
    this->window = window;
    winner = "none";
    setRunning(true);
    setFullscreen(0);
    p1isSuperEffective = false;
    p2isSuperEffective = false;
    p1isNotVeryEffective = false;
    p2isNotVeryEffective = false;
    userInput = 0;
    active1 = 0;
    active2 = 0;
    p1Choice = "deciding";
    p2Choice = "deciding";
    menuState = "start";
    p1Done = false;
    p2Done = false;
    turn = "P1";
    SDL_SetWindowTitle(window, "SDL2 Window");
    SDL_ShowCursor(1);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "2");
    font = TTF_OpenFont("fonts/PokemonGb-RAeo (1).ttf", 30);

    inventory1.setFullRestores(1);
    inventory1.setPotions(3);
    inventory1.setSodaPops(2);
    inventory1.print();

    inventory2.setFullRestores(1);
    inventory2.setPotions(3);
    inventory2.setSodaPops(2);
    inventory2.print();


    std::string temp1 = ("x" + to_string(inventory1.getPotions()) + " Potions");
    strArr[POTIONS1] = temp1.c_str();
    std::string temp2 = ("x" + to_string(inventory1.getFullRestores()) + " Full Restores");
    strArr[FULL_RESTORES1] = temp2.c_str();
    std::string temp3 = ("x" + std::to_string(inventory1.getSodaPops()) + " Soda Pops");
    strArr[SODA_POPS1] = temp3.c_str();

    std::string aint = ("x" + to_string(inventory2.getPotions()) + " Potions");
    strArr[POTIONS2] = aint.c_str();
    std::string doin = ("x" + to_string(inventory2.getFullRestores()) + " Full Restores");
    strArr[FULL_RESTORES2] = doin.c_str();
    std::string again = ("x" + std::to_string(inventory2.getSodaPops()) + " Soda Pops");
    strArr[SODA_POPS2] = again.c_str();

    tackle.setName("Tackle: ");
    tackle.setDamage(100);
    tackle.setType("Normal");

    razorLeaf.setName("Razor Leaf: ");
    razorLeaf.setDamage(55);
    razorLeaf.setType("Grass");

    magicalLeaf.setName("Magical Leaf: ");
    magicalLeaf.setDamage(60);
    magicalLeaf.setType("Grass");
    
    bodySlam.setName("Body Slam: ");
    bodySlam.setDamage(85);
    bodySlam.setType("Normal");

    ember.setName("Ember: ");
    ember.setDamage(40);
    ember.setType("Fire");

    quickAttack.setName("Quick Attack: ");
    quickAttack.setDamage(40);
    quickAttack.setType("Normal");

    flameWheel.setName("Flame Wheel: ");
    flameWheel.setDamage(60);
    flameWheel.setType("Fire");

    scratch.setName("Scratch: ");
    scratch.setDamage(40);
    scratch.setType("Normal");

    waterGun.setName("Water Gun: ");
    waterGun.setDamage(40);
    waterGun.setType("Water");

    aquaTail.setName("Aqua Tail: ");
    aquaTail.setDamage(90);
    aquaTail.setType("Water");

    slash.setName("Slash: ");
    slash.setDamage(70);
    slash.setType("Normal");

    vineWhip.setName("Vine Whip: ");
    vineWhip.setDamage(45);
    vineWhip.setType("Grass");

    waterPulse.setName("Water Pulse: ");
    waterPulse.setDamage(60);
    waterPulse.setType("Water");

    fireFang.setName("Fire Fang: ");
    fireFang.setDamage(65);
    fireFang.setType("Fire");

    flameThrower.setName("Flamethrower: ");
    flameThrower.setDamage(90);
    flameThrower.setType("Fire");

    doubleEdge.setName("Double-Edge: ");
    doubleEdge.setDamage(120);
    doubleEdge.setType("Normal");

    takeDown.setName("Take Down: ");
    takeDown.setDamage(90);
    takeDown.setType("Normal");

    powerWhip.setName("Power Whip: ");
    powerWhip.setDamage(120);
    powerWhip.setType("Grass");

    facade.setName("Facade: ");
    facade.setDamage(70);
    facade.setType("Normal");

    rapidSpin.setName("Rapid Spin: ");
    rapidSpin.setDamage(50);
    rapidSpin.setType("Normal");

    hydroPump.setName("Hydro Pump: ");
    hydroPump.setDamage(110);
    hydroPump.setType("Water");

    aquaJet.setName("Aqua Jet: ");
    aquaJet.setDamage(40);
    aquaJet.setType("Water");

    falseSwipe.setName("False Swipe: ");
    falseSwipe.setDamage(40);
    falseSwipe.setType("Normal");

    flareBlitz.setName("Flare Blitz: ");
    flareBlitz.setDamage(120);
    flareBlitz.setType("Fire");


    chikoritaMoves[0] = tackle;
    chikoritaMoves[1] = razorLeaf;
    chikoritaMoves[2] = magicalLeaf;
    chikoritaMoves[3] = bodySlam;

    totodileMoves[0] = scratch;
    totodileMoves[1] = waterGun;
    totodileMoves[2] = slash;
    totodileMoves[3] = aquaTail;

    cyndaquilMoves[0] = ember;
    cyndaquilMoves[1] = quickAttack;
    cyndaquilMoves[2] = flameWheel;
    cyndaquilMoves[3] = doubleEdge;

    bulbasaurMoves[0] = vineWhip;
    bulbasaurMoves[1] = takeDown;
    bulbasaurMoves[2] = powerWhip;
    bulbasaurMoves[3] = facade;

    squirtleMoves[0] = rapidSpin;
    squirtleMoves[1] = waterPulse;
    squirtleMoves[2] = hydroPump;
    squirtleMoves[3] = aquaJet;

    charmanderMoves[0] = fireFang;
    charmanderMoves[1] = flameThrower;
    charmanderMoves[2] = falseSwipe;
    charmanderMoves[3] = flareBlitz;

    team1[0].setHP(294);
    team1[0].setFullHealth(294);
    team1[0].setMove(chikoritaMoves);
    team1[0].setName("Chikorita");
    team1[0].setPokeType("Grass");
    team1[0].setResistance("Water");
    team1[0].setDead(false);
    team1[0].setIsActive(true);
    team1[0].pokeprint();

    team1[1].setHP(304);
    team1[1].setFullHealth(304);
    team1[1].setMove(totodileMoves);
    team1[1].setName("Totodile");
    team1[1].setPokeType("Water");
    team1[1].setResistance("Fire");
    team1[1].setDead(false);
    team1[1].setIsActive(false);
    team1[1].pokeprint();

    team1[2].setHP(282);
    team1[2].setFullHealth(282);
    team1[2].setMove(cyndaquilMoves);
    team1[2].setName("Cyndaquil");
    team1[2].setPokeType("Fire");
    team1[2].setResistance("Grass");
    team1[2].setDead(false);
    team1[2].setIsActive(false);
    team1[2].pokeprint();

    team2[0].setHP(294);
    team2[0].setFullHealth(294);
    team2[0].setMove(bulbasaurMoves);
    team2[0].setName("Bulbasaur");
    team2[0].setPokeType("Grass");
    team2[0].setResistance("Water");
    team2[0].setDead(false);
    team2[0].setIsActive(true);
    team2[0].pokeprint();

    team2[1].setHP(292); // 292
    team2[1].setFullHealth(292);
    team2[1].setMove(squirtleMoves);
    team2[1].setName("Squirtle");
    team2[1].setPokeType("Water");
    team2[1].setResistance("Fire");
    team2[1].setDead(false);
    team2[1].setIsActive(false);
    team2[1].pokeprint();

    team2[2].setHP(282); // 282
    team2[2].setFullHealth(282);
    team2[2].setMove(charmanderMoves);
    team2[2].setName("Charmander");
    team2[2].setPokeType("Fire");
    team2[2].setResistance("Grass");
    team2[2].setDead(false);
    team2[2].setIsActive(false);
    team2[2].pokeprint();


    // setting team 1 names 
    std::string temp4 = team1[0].getName();
    strArr[CHIKORITA_NAME] = temp4.c_str();
    std::string temp5 = team1[1].getName();
    strArr[TOTODILE_NAME] = temp5.c_str();
    std::string temp6 = team1[2].getName();
    strArr[CYNDAQUIL_NAME] = temp6.c_str();

    // setting team 2 names
    std::string temp7 = team2[0].getName();
    strArr[BULBASAUR_NAME] = temp7.c_str();
    std::string temp8 = team2[1].getName();
    strArr[SQUIRTLE_NAME] = temp8.c_str();
    std::string temp9 = team2[2].getName();
    strArr[CHARMANDER_NAME] = temp9.c_str();

    // setting team 1 hp
    std::string temp10 = to_string(team1[0].getHP()) + "/" + to_string(team1[0].getFullHealth());
    strArr[CHIKORITA_HP] = temp10.c_str();
    std::string temp11 = to_string(team1[1].getHP()) + "/" + to_string(team1[1].getFullHealth());
    strArr[TOTODILE_HP] = temp11.c_str();
    std::string temp12 = to_string(team1[2].getHP()) + "/" + to_string(team1[2].getFullHealth());
    strArr[CYNDAQUIL_HP] = temp12.c_str();

    // setting team 2 hp
    std::string temp13 = to_string(team2[0].getHP()) + "/" + to_string(team2[0].getFullHealth());
    strArr[BULBASAUR_HP] = temp13.c_str();
    std::string temp14 = to_string(team2[1].getHP()) + "/" + to_string(team2[1].getFullHealth());
    strArr[SQUIRTLE_HP] = temp14.c_str();
    std::string temp15 = to_string(team2[2].getHP()) + "/" + to_string(team2[2].getFullHealth());
    strArr[CHARMANDER_HP] = temp15.c_str();

    // setting moves
    std::string temp16 = team1[0].getMove(0).getName() + "Normal";
    strArr[TACKLE] = temp16.c_str();

    std::string temp17 = team1[0].getMove(1).getName() + "Grass";
    strArr[RAZOR_LEAF] = temp17.c_str();

    std::string temp18 = team1[0].getMove(2).getName() + "Grass";
    strArr[MAGICAL_LEAF] = temp18.c_str();

    std::string temp19 = team1[0].getMove(3).getName() + "Normal";
    strArr[BODY_SLAM] = temp19.c_str();

    std::string temp20 = team1[1].getMove(0).getName() + "Normal";
    strArr[SCRATCH] = temp20.c_str();

    std::string temp21 = team1[1].getMove(1).getName() + "Water";
    strArr[WATER_GUN] = temp21.c_str();

    std::string temp22 = team1[1].getMove(2).getName() + "Normal";
    strArr[SLASH] = temp22.c_str();

    std::string temp23 = team1[1].getMove(3).getName() + "Water";
    strArr[AQUA_TAIL] = temp23.c_str();

    std::string temp24 = team1[2].getMove(0).getName() + "Fire";
    strArr[EMBER] = temp24.c_str();

    std::string temp25 = team1[2].getMove(1).getName() + "Normal";
    strArr[QUICK_ATTACK] = temp25.c_str();

    std::string temp26 = team1[2].getMove(2).getName() + "Fire";
    strArr[FLAME_WHEEL] = temp26.c_str();

    std::string temp27 = team2[0].getMove(0).getName() + "Grass";
    strArr[VINE_WHIP] = temp27.c_str();

    std::string temp28 = team2[1].getMove(1).getName() + "Water";
    strArr[WATER_PULSE] = temp28.c_str();

    std::string temp29 = team2[2].getMove(0).getName() + "Fire";
    strArr[FIRE_FANG] = temp29.c_str();

    std::string temp30 = team2[2].getMove(1).getName() + "Fire";
    strArr[FLAMETHROWER] = temp30.c_str();


    std::string temp31 = team1[2].getMove(3).getName() + "Normal";
    strArr[DOUBLE_EDGE] = temp31.c_str();
    
    std::string temp32 = team2[0].getMove(1).getName() + "Normal";
    strArr[TAKE_DOWN] = temp32.c_str();

    std::string temp33 = team2[0].getMove(2).getName() + "Grass";
    strArr[POWER_WHIP] = temp33.c_str();

    std::string temp34 = team2[0].getMove(3).getName() + "Normal";
    strArr[FACADE] = temp34.c_str();

    std::string temp35 = team2[1].getMove(0).getName() + "Normal";
    strArr[RAPID_SPIN] = temp35.c_str();

    std::string temp36 = team2[1].getMove(2).getName() + "Water";
    strArr[HYDRO_PUMP] = temp36.c_str();

    std::string temp37 = team2[1].getMove(3).getName() + "Water";
    strArr[AQUA_JET] = temp37.c_str();

    std::string temp38 = team2[2].getMove(2).getName() + "Normal";
    strArr[FALSE_SWIPE] = temp38.c_str();

    std::string temp39 = team2[2].getMove(3).getName() + "Fire";
    strArr[FLARE_BLITZ] = temp39.c_str();


    setSurface(IMG_Load("res/pokemonBattleBacground.png"));
    bgTexture = SDL_CreateTextureFromSurface(renderer, image);

    setSurface(IMG_Load("res/chikorita-back.png"));
    playerOne[0]=SDL_CreateTextureFromSurface(renderer,image);

    setSurface(IMG_Load("res/totodile-back.png"));
    playerOne[1]=SDL_CreateTextureFromSurface(renderer,image);

    setSurface(IMG_Load("res/cyndaquil-back.png"));
    playerOne[2]=SDL_CreateTextureFromSurface(renderer,image);

    setSurface(IMG_Load("res/bulbasaur.png"));
    playerTwo[0] = SDL_CreateTextureFromSurface(renderer, image);

    setSurface(IMG_Load("res/squirtle.png"));
    playerTwo[1]=SDL_CreateTextureFromSurface(renderer,image);

    setSurface(IMG_Load("res/charmander.png"));
    playerTwo[2]=SDL_CreateTextureFromSurface(renderer,image);

    setSurface(IMG_Load("res/pointer_arrow.png"));
    arrowText = SDL_CreateTextureFromSurface(renderer, image);

    setSurface(IMG_Load("res/trans_menu.png"));
    menuText = SDL_CreateTextureFromSurface(renderer, image);

    setSurface(IMG_Load("res/potion.png"));
    itemText[0] = SDL_CreateTextureFromSurface(renderer, image);
    setSurface(IMG_Load("res/full_restore.png"));
    itemText[1] = SDL_CreateTextureFromSurface(renderer, image);
    setSurface(IMG_Load("res/soda_pop.png"));
    itemText[2] = SDL_CreateTextureFromSurface(renderer, image);

    setSurface(IMG_Load("res/empty-start-menu.png"));
    emptyMenuText = SDL_CreateTextureFromSurface(renderer, image);
    // for(int i = 0; i < 49; i++)
    // {
    //     std::cout << strArr[i] << " " << (i + 1) << std::endl;
    // }
    initFont();
    

}


// getters
std::string Game::getP1Choice()const
{
    return p1Choice;
}
std::string Game::getP2Choice()const
{
    return p2Choice;
}
bool Game::getRunning()const
{
    return running;
}
bool Game::getFullscreen()const
{
    return fullscreen;
}
int Game::getFrameCount()const
{
    return frameCount;
}
int Game::getTimerFPS()const
{
    return timerFPS;
}
int Game::getLastFrame()const
{
    return lastFrame;
}
int Game::getFps()const
{
    return fps;
}
static int getLastTime() 
{
    return Game::lastTime;
}
SDL_Surface* Game::getSurface()const
{
    return image;
}
std::string Game::getMenuState()const
{
    return menuState;
}
std::string Game::getTurn()const
{
    return turn;
}

// setters

void Game::setP1Choice(std::string p1Choice)
{
    this->p1Choice = p1Choice;
}
void Game::setP2Choice(std::string p1Choice)
{
    this->p2Choice = p2Choice;
}
void Game::setRunning(bool running)
{
    this->running = running;
}
void Game::setFullscreen(bool fullscreen)
{
    this->fullscreen = fullscreen;
}
void Game::setFrameCount(int frameCount)
{
    this->frameCount = frameCount;
}
void Game::setTimerFPS(int timerFPS)
{
    this->timerFPS = timerFPS;
}
void Game::setLastFrame(int lastFrame)
{
    this->lastFrame = lastFrame;
}
void Game::setFps(int fps)
{
    this->fps = fps;
}
void Game::setSurface(SDL_Surface* image)
{
    this->image = image;

}
void Game::setP1Text(SDL_Texture* texture, int loc) // Index
{
    this->playerOne[loc] = texture;
}
void Game::setP2Text(SDL_Texture* texture, int loc)
{
    this->playerTwo[loc] = texture;
}
void Game::setBGTexture(SDL_Texture* texture)
{
    this->bgTexture = texture;
}
void Game:: setMenuState(std::string menuState)
{
    this->menuState = menuState;
}

void Game::setLastTime(int lastTime)
{
    Game::lastTime = lastTime;
}
void Game::setTurn(std::string turn)
{
    this->turn = turn;
}
// member methods

void Game::assignWinner()
{
    if(team1[0].getDead() && team1[1].getDead() && team1[2].getDead())
    {
        dstrect.x = 120;
        dstrect.y = 565;
        dstrect.w = textArr[P2_WIN].w;
        dstrect.h = textArr[P2_WIN].h;

        SDL_RenderCopy(renderer, textArr[P2_WIN].textTex, NULL, &dstrect);
        winner = "P2";
    }
    else if(team2[0].getDead() && team2[1].getDead() && team2[2].getDead())
    {
        dstrect.x = 120;
        dstrect.y = 565;
        dstrect.w = textArr[P1_WIN].w;
        dstrect.h = textArr[P1_WIN].h;

        SDL_RenderCopy(renderer, textArr[P1_WIN].textTex, NULL, &dstrect);
        winner = "P1";
    }
    // SDL_RenderPresent(renderer);
}

void Game::heal(std::string whomst)
{
    if(whomst == "P1")
    {
        if(p1Choice == "potion")
        {
            if(team1[active1].getHP() + 40 > team1[active1].getFullHealth())
            {
                team1[active1].setHP(team1[active1].getFullHealth());    
            }
            else team1[active1].setHP(team1[active1].getHP() + 40);
        }
        if(p1Choice == "restore")
        {
            team1[active1].setHP(team1[active1].getFullHealth());
        }
        if(p1Choice == "soda")
        {
            if(team1[active1].getHP() + 20 > team1[active1].getFullHealth())
            {
                team1[active1].setHP(team1[active1].getFullHealth());    
            }
            else team1[active1].setHP(team1[active1].getHP() + 20);
        }
    }
    if(whomst == "P2")
    {
        if(p2Choice == "potion")
        {
            if(team2[active2].getHP() + 40 > team2[active2].getFullHealth())
            {
                team2[active2].setHP(team2[active2].getFullHealth());    
            }
            else team2[active2].setHP(team2[active2].getHP() + 40);
        }
        if(p2Choice == "restore")
        {
            team2[active2].setHP(team2[active2].getFullHealth());
        }
        if(p2Choice == "soda")
        {
            if(team2[active2].getHP() + 40 > team2[active2].getFullHealth())
            {
                team2[active2].setHP(team2[active2].getFullHealth());    
            }
            else team2[active2].setHP(team2[active2].getHP() + 20);
        }
    }
}
void Game::attack(string whomst)
{
    if(whomst == "P1")
    {
        if(p1Choice == "move1")
        {
            // Super Effectives
            if((team1[active1].getMove(0).getType() == "Grass" && team2[active2].getPokeType() == "Water") || (team1[active1].getMove(0).getType() == "Water" && team2[active2].getPokeType() == "Fire") || (team1[active1].getMove(0).getType() == "Fire" && team2[active2].getPokeType() == "Grass"))
            {
                if(team2[active2].getHP() - team1[active1].getMove(0).getDamage() * 2 <= 0) // move 1 kills pokemon 2
                {
                    team2[active2].setHP(0);
                    team2[active2].setDead(true);
                }
                else // move 1 damages pokemon 2
                {
                    team2[active2].setHP(team2[active2].getHP() - team1[active1].getMove(0).getDamage() * 2); // super effective damage
                }
                p1isSuperEffective = true;
            }
            // Not Very Effectives
            else if((team1[active1].getMove(0).getType() == team2[active2].getResistance()) || (team1[active1].getMove(0).getType() == team2[active2].getResistance()) || (team1[active1].getMove(0).getType() == team2[active2].getResistance()))
            {
                if(team2[active2].getHP() - team1[active1].getMove(0).getDamage() / 2 <= 0) // move 1 kills pokemon 2
                {
                    team2[active2].setHP(0);
                    team2[active2].setDead(true);
                }
                else // move 1 damages pokemon 2
                {
                    team2[active2].setHP(team2[active2].getHP() - team1[active1].getMove(0).getDamage() / 2); // resisted damage
                }
                p1isNotVeryEffective = true;
            }
            else
            {
                if(team2[active2].getHP() - team1[active1].getMove(0).getDamage() <= 0) // move 1 kills pokemon 2
                {
                    team2[active2].setHP(0);
                    team2[active2].setDead(true);
                }
                else
                {
                    team2[active2].setHP(team2[active2].getHP() - team1[active1].getMove(0).getDamage());
                }
                std::cout << team2[active2].getHP() << std::endl;
            }
        }
        if(p1Choice == "move2")
        {
            // Super Effectives
            if((team1[active1].getMove(1).getType() == "Grass" && team2[active2].getPokeType() == "Water") || (team1[active1].getMove(1).getType() == "Water" && team2[active2].getPokeType() == "Fire") || (team1[active1].getMove(1).getType() == "Fire" && team2[active2].getPokeType() == "Grass"))
            {
                if(team2[active2].getHP() - team1[active1].getMove(1).getDamage() * 2 <= 0) // move 1 kills pokemon 2
                {
                    team2[active2].setHP(0);
                    team2[active2].setDead(true);
                }
                else // move 1 damages pokemon 2
                {
                    team2[active2].setHP(team2[active2].getHP() - team1[active1].getMove(1).getDamage() * 2); // super effective damage
                }
                p1isSuperEffective = true;
            }
            // Not Very Effectives
            else if((team1[active1].getMove(1).getType() == team2[active2].getResistance()) || (team1[active1].getMove(1).getType() == team2[active2].getResistance()) || (team1[active1].getMove(1).getType() == team2[active2].getResistance()))
            {
                if(team2[active2].getHP() - team1[active1].getMove(1).getDamage() / 2 <= 0) // move 1 kills pokemon 2
                {
                    team2[active2].setHP(0);
                    team2[active2].setDead(true);
                }
                else // move 1 damages pokemon 2
                {
                    team2[active2].setHP(team2[active2].getHP() - team1[active1].getMove(1).getDamage() / 2); // resisted damage
                }
                p1isNotVeryEffective = true;
            }
            else
            {
                if(team2[active2].getHP() - team1[active1].getMove(1).getDamage() <= 0) // move 1 kills pokemon 2
                {
                    team2[active2].setHP(0);
                    team2[active2].setDead(true);
                }
                else
                {
                    team2[active2].setHP(team2[active2].getHP() - team1[active1].getMove(1).getDamage());
                }
            }
        }
        if(p1Choice == "move3")
        {
            // Super Effectives
            if((team1[active1].getMove(2).getType() == "Grass" && team2[active2].getPokeType() == "Water") || (team1[active1].getMove(2).getType() == "Water" && team2[active2].getPokeType() == "Fire") || (team1[active1].getMove(2).getType() == "Fire" && team2[active2].getPokeType() == "Grass"))
            {
                if(team2[active2].getHP() - team1[active1].getMove(2).getDamage() * 2 <= 0) // move 1 kills pokemon 2
                {
                    team2[active2].setHP(0);
                    team2[active2].setDead(true);
                }
                else // move 1 damages pokemon 2
                {
                    team2[active2].setHP(team2[active2].getHP() - team1[active1].getMove(2).getDamage() * 2); // super effective damage
                }
                p1isSuperEffective = true;
            }
            // Not Very Effectives
            else if((team1[active1].getMove(2).getType() == team2[active2].getResistance()) || (team1[active1].getMove(2).getType() == team2[active2].getResistance()) || (team1[active1].getMove(2).getType() == team2[active2].getResistance()))
            {
                if(team2[active2].getHP() - team1[active1].getMove(2).getDamage() / 2 <= 0) // move 1 kills pokemon 2
                {
                    team2[active2].setHP(0);
                    team2[active2].setDead(true);
                }
                else // move 1 damages pokemon 2
                {
                    team2[active2].setHP(team2[active2].getHP() - team1[active1].getMove(2).getDamage() / 2); // resisted damage
                }
                p1isNotVeryEffective = true;
            }
            else
            {
                if(team2[active2].getHP() - team1[active1].getMove(2).getDamage() <= 0) // move 1 kills pokemon 2
                {
                    team2[active2].setHP(0);
                    team2[active2].setDead(true);
                }
                else
                {
                    team2[active2].setHP(team2[active2].getHP() - team1[active1].getMove(2).getDamage());
                }
            }
        }
        if(p1Choice == "move4")
        {
            // Super Effectives
            if((team1[active1].getMove(3).getType() == "Grass" && team2[active2].getPokeType() == "Water") || (team1[active1].getMove(3).getType() == "Water" && team2[active2].getPokeType() == "Fire") || (team1[active1].getMove(3).getType() == "Fire" && team2[active2].getPokeType() == "Grass"))
            {
                if(team2[active2].getHP() - team1[active1].getMove(3).getDamage() * 2 <= 0) // move 1 kills pokemon 2
                {
                    team2[active2].setHP(0);
                    team2[active2].setDead(true);
                }
                else // move 1 damages pokemon 2
                {
                    team2[active2].setHP(team2[active2].getHP() - team1[active1].getMove(3).getDamage() * 2); // super effective damage
                }
                p1isSuperEffective = true;
            }
            // Not Very Effectives
            else if((team1[active1].getMove(3).getType() == team2[active2].getResistance()) || (team1[active1].getMove(3).getType() == team2[active2].getResistance()) || (team1[active1].getMove(3).getType() == team2[active2].getResistance()))
            {
                if(team2[active2].getHP() - team1[active1].getMove(3).getDamage() / 2 <= 0) // move 1 kills pokemon 2
                {
                    team2[active2].setHP(0);
                    team2[active2].setDead(true);
                }
                else // move 1 damages pokemon 2
                {
                    team2[active2].setHP(team2[active2].getHP() - team1[active1].getMove(3).getDamage() / 2); // resisted damage
                }
                p1isNotVeryEffective = true;
            }
            else
            {
                if(team2[active2].getHP() - team1[active1].getMove(3).getDamage() <= 0) // move 1 kills pokemon 2
                {
                    team2[active2].setHP(0);
                    team2[active2].setDead(true);
                }
                else
                {
                    team2[active2].setHP(team2[active2].getHP() - team1[active1].getMove(3).getDamage());
                }
            }
        }
    }
    if(whomst == "P2")
    {
        if(p2Choice == "move1")
        {
            // Super Effectives
            if((team2[active2].getMove(0).getType() == "Grass" && team1[active1].getPokeType() == "Water") || (team2[active2].getMove(0).getType() == "Water" && team1[active1].getPokeType() == "Fire") || (team2[active2].getMove(0).getType() == "Fire" && team1[active1].getPokeType() == "Grass"))
            {
                if(team1[active1].getHP() - team2[active2].getMove(0).getDamage() * 2 <= 0) // move 1 kills pokemon 2
                {
                    team1[active1].setHP(0);
                    team1[active1].setDead(true);
                }
                else // move 1 damages pokemon 2
                {
                    team1[active1].setHP(team1[active1].getHP() - team2[active2].getMove(0).getDamage() * 2); // super effective damage
                    std::cout << "Should not be here\n";
                }
                p2isSuperEffective = true;
            }// --
            // Not Very Effectives
            else if((team2[active2].getMove(0).getType() == team1[active1].getResistance()) || (team2[active2].getMove(0).getType() == team1[active1].getResistance()) || (team2[active2].getMove(0).getType() == team1[active1].getResistance()))
            {
                if(team1[active1].getHP() - team2[active2].getMove(0).getDamage() / 2 <= 0) // move 1 kills pokemon 2
                {
                    team1[active1].setHP(0);
                    team1[active1].setDead(true);
                }
                else // move 1 damages pokemon 2
                {
                    team1[active1].setHP(team1[active1].getHP() - team2[active2].getMove(0).getDamage() / 2); // resisted damage
                }
                p2isNotVeryEffective = true;
            }
            else
            {
                if(team1[active1].getHP() - team2[active2].getMove(0).getDamage() <= 0) // move 1 kills pokemon 2
                {
                    team1[active1].setHP(0);
                    team1[active1].setDead(true);
                }
                else
                {
                    team1[active1].setHP(team1[active1].getHP() - team2[active2].getMove(0).getDamage());
                }
                std::cout << "Perfection\n";
            }
        }
        if(p2Choice == "move2")
        {
            // Super Effectives
            if((team2[active2].getMove(1).getType() == "Grass" && team1[active1].getPokeType() == "Water") || (team2[active2].getMove(1).getType() == "Water" && team1[active1].getPokeType() == "Fire") || (team2[active2].getMove(1).getType() == "Fire" && team1[active1].getPokeType() == "Grass"))
            {
                if(team1[active1].getHP() - team2[active2].getMove(1).getDamage() * 2 <= 0) // move 1 kills pokemon 2
                {
                    team1[active1].setHP(0);
                    team1[active1].setDead(true);
                }
                else // move 1 damages pokemon 2
                {
                    team1[active1].setHP(team1[active1].getHP() - team2[active2].getMove(1).getDamage() * 2); // super effective damage
                }
                p2isSuperEffective = true;
            }
            // Not Very Effectives
            else if((team2[active2].getMove(1).getType() == team1[active1].getResistance()) || (team2[active2].getMove(1).getType() == team1[active1].getResistance()) || (team2[active2].getMove(1).getType() == team1[active1].getResistance()))
            {
                if(team1[active1].getHP() - team2[active2].getMove(1).getDamage() / 2 <= 0) // move 1 kills pokemon 2
                {
                    team1[active1].setHP(0);
                    team1[active1].setDead(true);
                }
                else // move 1 damages pokemon 2
                {
                    team1[active1].setHP(team1[active1].getHP() - team2[active2].getMove(1).getDamage() / 2); // resisted damage
                }
                p2isNotVeryEffective = true;
            }
            else
            {
                if(team1[active1].getHP() - team2[active2].getMove(1).getDamage() <= 0) // move 1 kills pokemon 2
                {
                    team1[active1].setHP(0);
                    team1[active1].setDead(true);
                }
                else
                {
                    team1[active1].setHP(team1[active1].getHP() - team2[active2].getMove(1).getDamage());
                }            }
        }
        if(p2Choice == "move3")
        {
            // Super Effectives
            if((team2[active2].getMove(2).getType() == "Grass" && team1[active1].getPokeType() == "Water") || (team2[active2].getMove(2).getType() == "Water" && team1[active1].getPokeType() == "Fire") || (team2[active2].getMove(2).getType() == "Fire" && team1[active1].getPokeType() == "Grass"))
            {
                if(team1[active1].getHP() - team2[active2].getMove(2).getDamage() * 2 <= 0) // move 1 kills pokemon 2
                {
                    team1[active1].setHP(0);
                    team1[active1].setDead(true);
                }
                else // move 1 damages pokemon 2
                {
                    team1[active1].setHP(team1[active1].getHP() - team2[active2].getMove(2).getDamage() * 2); // super effective damage
                }
                p2isSuperEffective = true;
            }
            // Not Very Effectives
            else if((team2[active2].getMove(2).getType() == team1[active1].getResistance()) || (team2[active2].getMove(2).getType() == team1[active1].getResistance()) || (team2[active2].getMove(2).getType() == team1[active1].getResistance()))
            {
                if(team1[active1].getHP() - team2[active2].getMove(2).getDamage() / 2 <= 0) // move 1 kills pokemon 2
                {
                    team1[active1].setHP(0);
                    team1[active1].setDead(true);
                }
                else // move 1 damages pokemon 2
                {
                    team1[active1].setHP(team1[active1].getHP() - team2[active2].getMove(2).getDamage() / 2); // resisted damage
                }
                p2isNotVeryEffective = true;
            }
            else
            {
                if(team1[active1].getHP() - team2[active2].getMove(2).getDamage() <= 0) // move 1 kills pokemon 2
                {
                    team1[active1].setHP(0);
                    team1[active1].setDead(true);
                }
                else
                {
                    team1[active1].setHP(team1[active1].getHP() - team2[active2].getMove(2).getDamage());
                }
            }
        }
        if(p2Choice == "move4")
        {
            // Super Effectives
            if((team2[active2].getMove(3).getType() == "Grass" && team1[active1].getPokeType() == "Water") || (team2[active2].getMove(3).getType() == "Water" && team1[active1].getPokeType() == "Fire") || (team2[active2].getMove(3).getType() == "Fire" && team1[active1].getPokeType() == "Grass"))
            {
                if(team1[active1].getHP() - team2[active2].getMove(3).getDamage() * 2 <= 0) // move 1 kills pokemon 2
                {
                    team1[active1].setHP(0);
                    team1[active1].setDead(true);
                }
                else // move 1 damages pokemon 2
                {
                    team1[active1].setHP(team1[active1].getHP() - team2[active2].getMove(3).getDamage() * 2); // super effective damage
                }
                p2isSuperEffective = true;
            }
            // Not Very Effectives
            else if((team2[active2].getMove(3).getType() == team1[active1].getResistance()) || (team2[active2].getMove(3).getType() == team1[active1].getResistance()) || (team2[active2].getMove(3).getType() == team1[active1].getResistance()))
            {
                if(team1[active1].getHP() - team2[active2].getMove(3).getDamage() / 2 <= 0) // move 1 kills pokemon 2
                {
                    team1[active1].setHP(0);
                    team1[active1].setDead(true);
                }
                else // move 1 damages pokemon 2
                {
                    team1[active1].setHP(team1[active1].getHP() - team2[active2].getMove(3).getDamage() / 2); // resisted damage
                }
                p2isNotVeryEffective = true;
            }
            else
            {
                if(team1[active1].getHP() - team2[active2].getMove(3).getDamage() <= 0) // move 1 kills pokemon 2
                {
                    team1[active1].setHP(0);
                    team1[active1].setDead(true);
                }
                else
                {
                    team1[active1].setHP(team1[active1].getHP() - team2[active2].getMove(3).getDamage());
                }
            }
        }
    }
}
void Game::swap()
{

}

void Game::update()
{
    // if(p1Done && p2Done)
    // {    
    //     
    // }
    if(fullscreen) SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
    if(!fullscreen) SDL_SetWindowFullscreen(window, 0);
    if(menuState == "start") // start menu functionality
    {    
        if(userInput == USER_UP) 
        {
            std::cout << "UP\n";
            arrowXPos = 580;
            arrowYPos = 555;
            userInput = 0;
        } 
        if(userInput == USER_DN) 
        {
            std::cout << "DOWN\n";
            arrowXPos = 580;
            arrowYPos = 620;
            userInput = 0;
        }
        if(userInput == USER_LT) 
        {
            std::cout << "LEFT\n";
            arrowXPos = 580;
            arrowYPos = 555;
            userInput = 0;
        }
        if(userInput == USER_RT) 
        {
            std::cout << "RIGHT\n";
            arrowXPos = 970;
            arrowYPos = 555;
            userInput = 0;
        }
        if(userInput == USER_EN) 
        {
            std::cout << "ENTER\n";
            if((p1Choice == "fight" && turn == "P1") || (p2Choice == "fight" && turn == "P2"))
            {
                arrowXPos = 85;
                arrowYPos = 545;
                if(turn == "P1")
                {
                    menuState = "fightMenu";
                }
                else
                {
                    menuState = "fightMenu";
                }
                // p1Choice = "deciding";
                // p2Choice = "deciding";
            }
            else if((p1Choice == "items" && turn == "P1") || (p2Choice == "items" && turn == "P2"))
            {
                
                arrowXPos = 70;
                arrowYPos = 545;
                if(turn == "P1") 
                {
                    menuState = "itemMenu";
                    p1Choice = "potion";
                }
                else 
                {
                    menuState = "itemMenu";
                    p2Choice = "potion";
                }
                // p1Choice = "deciding";
                // p2Choice = "deciding";
            }
            else if((p1Choice == "swap" && turn == "P1") || (p2Choice == "swap" && turn == "P2"))
            {
                arrowXPos = 970;
                arrowYPos = 555;
                if(turn == "P1")
                {
                    menuState = "swapMenu";
                    // p1Choice = "swap";
                }
                else 
                {
                    menuState = "swapMenu";
                    // p2Choice = "swap";
                }
                // p1Choice = "deciding";
                // p2Choice = "deciding";
            }
            userInput = 0;

        }
    }
    if(menuState == "fightMenu")
    {
        // (85, 545) (285, 545)
        // (85, 590) (285, 590)
        if(userInput == USER_UP) 
        {
            std::cout << "UP\n";
            if(arrowYPos - 45 >= 545)
            {
                arrowShiftY = -45;
                arrowYPos += arrowShiftY;
            }
            // arrowXPos = 85;
            // arrowYPos = 545;
            userInput = 0;
        } 
        if(userInput == USER_DN) 
        {
            std::cout << "DOWN\n";
            if(arrowYPos + 45 <= 590)
            {
                arrowShiftY = 45;
                arrowYPos += arrowShiftY;
            }
            // arrowXPos = 580;
            // arrowYPos = 620;
            userInput = 0;
        }
        if(userInput == USER_LT) 
        {
            std::cout << "LEFT\n";
            if(arrowXPos - 200 >= 85)
            {
                arrowShiftX = -200;
                arrowXPos += arrowShiftX;

            }
            // arrowXPos = 580;
            // arrowYPos = 555;
            userInput = 0;
        }
        if(userInput == USER_RT) 
        {
            std::cout << "RIGHT\n";
            if(arrowXPos + 200 <= 285)
            {
                arrowShiftX = 200;
                arrowXPos += arrowShiftX;

            }
            // arrowXPos = 970;
            // arrowYPos = 555;
            userInput = 0;
        }
        if(userInput == USER_EN) 
        {
            // Move choices
            // (85, 545) (285, 545)
            // (85, 590) (285, 590)
            if(turn == "P1")
            {
                if(arrowXPos == 85 && arrowYPos == 545) p1Choice = "move1";
                if(arrowXPos == 285 && arrowYPos == 545) p1Choice = "move2";
                if(arrowXPos == 85 && arrowYPos == 590) p1Choice = "move3";
                if(arrowXPos == 285 && arrowYPos == 590) p1Choice = "move4";
                menuState = "start";
                p1Done = true;
                turn = "P2";
            }
            else if(turn == "P2")
            {
                if(arrowXPos == 85 && arrowYPos == 545) p2Choice = "move1";
                if(arrowXPos == 285 && arrowYPos == 545) p2Choice = "move2";
                if(arrowXPos == 85 && arrowYPos == 590) p2Choice = "move3";
                if(arrowXPos == 285 && arrowYPos == 590) p2Choice = "move4";
                menuState = "start";
                p2Done = true;
                turn = "P1";
            }

            userInput = 0;

        }
        if(userInput == USER_BK)
        {
            arrowXPos = 580;
            arrowYPos = 555;
            menuState = "start";
            userInput = 0;
            if(turn == "P1")
            {
                p1Choice = "deciding";
            }
            if(turn == "P2")
            {
                p2Choice = "deciding";
            }
        }
    }
    if(menuState == "itemMenu")
    {
        // (70, 545) (275, 545)
        // (85, 570) (285, 570)

        if(userInput == USER_UP) 
        {
            std::cout << "UP\n";
            arrowXPos = 70;
            arrowYPos = 545;
            userInput = 0;
        } 
        if(userInput == USER_DN) 
        {
            std::cout << "DOWN\n";
            arrowXPos = 70;
            arrowYPos = 570;
            userInput = 0;
        }
        if(userInput == USER_LT) 
        {
            std::cout << "LEFT\n";
            arrowXPos = 70;
            arrowYPos = 545;
            userInput = 0;
        }
        if(userInput == USER_RT) 
        {
            std::cout << "RIGHT\n";
            arrowXPos = 265;
            arrowYPos = 545;
            userInput = 0;
        }
        if(userInput == USER_EN) 
        {
            std::cout << "ENTER\n";
            if(turn == "P1")
            {
                if(p1Choice == "potion" && (inventory1.getPotions() != 0))
                {
                    std::cout << "potion 1\n";
                    inventory1.setPotions(inventory1.getPotions() - 1);
                    std::string temp1 = ("x" + to_string(inventory1.getPotions()) + " Potions");
                    strArr[POTIONS1] = temp1.c_str();
                
                    image = TTF_RenderText_Blended(font, strArr[POTIONS1], (SDL_Color){0, 0, 0, 255});
                    textArr[POTIONS1].textTex = SDL_CreateTextureFromSurface(renderer, image);
                    if (TTF_SizeText(font, strArr[POTIONS1], &textArr[POTIONS1].w, &textArr[POTIONS1].h) != 0) {
                        std::cout << "Size Fail\n";
                    }
                    p1Done = true;
                    turn = "P2";
                    menuState = "start";
                    // p1Done = true;
                    // turn = "P2";
                    // menuState = "start";
                    // for(int i = 0; i < 49; i++)
                    // {
                    //     std::cout << strArr[i] << std::endl;
                    // }
                    // initFont();
                }
                if(p1Choice == "soda" && (inventory1.getSodaPops() != 0))
                {   
                    inventory1.setSodaPops(inventory1.getSodaPops() - 1);
                    std::string temp3 = ("x" + std::to_string(inventory1.getSodaPops()) + " Soda Pops");
                    strArr[SODA_POPS1] = temp3.c_str();
                    image = TTF_RenderText_Blended(font, strArr[SODA_POPS1], (SDL_Color){0, 0, 0, 255});
                    textArr[SODA_POPS1].textTex = SDL_CreateTextureFromSurface(renderer, image);
                    if (TTF_SizeText(font, strArr[SODA_POPS1], &textArr[SODA_POPS1].w, &textArr[SODA_POPS1].h) != 0) {
                        std::cout << "Size Fail\n";
                    }
                    p1Done = true;
                    turn = "P2";
                    menuState = "start";
                    // p1Done = true;
                    // turn = "P2";
                    // menuState = "start";

                    // initFont();
                }
                if(p1Choice == "restore" && (inventory1.getFullRestores() != 0))
                {
                    inventory1.setFullRestores(inventory1.getFullRestores() - 1);
                    std::string temp2 = ("x" + to_string(inventory1.getFullRestores()) + " Full Restores");
                    strArr[FULL_RESTORES1] = temp2.c_str();

                    image = TTF_RenderText_Blended(font, strArr[FULL_RESTORES1], (SDL_Color){0, 0, 0, 255});
                    textArr[FULL_RESTORES1].textTex = SDL_CreateTextureFromSurface(renderer, image);
                    if (TTF_SizeText(font, strArr[FULL_RESTORES1], &textArr[FULL_RESTORES1].w, &textArr[FULL_RESTORES1].h) != 0) {
                        std::cout << "Size Fail\n";
                    }
                    p1Done = true;
                    turn = "P2";
                    menuState = "start";
                    // p1Done = true;
                    // turn = "P2";
                    // menuState = "start";

                    // initFont();
                }
                std::cout << "P2 has (" << inventory2.getPotions() << ", " << inventory2.getFullRestores() << ", " << inventory2.getSodaPops() << std::endl;

            }
            else if(turn == "P2")
            {
                if(p2Choice == "potion" && (inventory2.getPotions() != 0))
                {
                    std::cout << "potion 2\n";
                    inventory2.setPotions(inventory2.getPotions() - 1);
                    std::string temp1 = ("x" + to_string(inventory2.getPotions()) + " Potions");
                    strArr[POTIONS2] = temp1.c_str();

                    image = TTF_RenderText_Blended(font, strArr[POTIONS2], (SDL_Color){0, 0, 0, 255});
                    textArr[POTIONS2].textTex = SDL_CreateTextureFromSurface(renderer, image);
                    if (TTF_SizeText(font, strArr[POTIONS2], &textArr[POTIONS2].w, &textArr[POTIONS2].h) != 0) {
                        std::cout << "Size Fail\n";
                    }
                    p2Done = true;
                    turn = "P1";
                    menuState = "start";
                    // p2Done = true;
                    // turn = "P1";
                    // menuState = "start";

                    // initFont();
                }
                if(p2Choice == "soda" && (inventory2.getSodaPops() != 0))
                {
                    inventory2.setSodaPops(inventory2.getSodaPops() - 1);
                    std::string temp3 = ("x" + std::to_string(inventory2.getSodaPops()) + " Soda Pops");
                    strArr[SODA_POPS2] = temp3.c_str();

                    image = TTF_RenderText_Blended(font, strArr[SODA_POPS2], (SDL_Color){0, 0, 0, 255});
                    textArr[SODA_POPS2].textTex = SDL_CreateTextureFromSurface(renderer, image);
                    if (TTF_SizeText(font, strArr[SODA_POPS2], &textArr[SODA_POPS2].w, &textArr[SODA_POPS2].h) != 0) {
                        std::cout << "Size Fail\n";
                    }
                    p2Done = true;
                    turn = "P1";
                    menuState = "start";
                    // p2Done = true;
                    // turn = "P1";
                    // menuState = "start";

                    // initFont();
                }
                if(p2Choice == "restore" && (inventory2.getFullRestores() != 0))
                {
                    inventory2.setFullRestores(inventory2.getFullRestores() - 1);
                    std::string temp2 = ("x" + to_string(inventory2.getFullRestores()) + " Full Restores");
                    strArr[FULL_RESTORES2] = temp2.c_str();

                    image = TTF_RenderText_Blended(font, strArr[FULL_RESTORES2], (SDL_Color){0, 0, 0, 255});
                    textArr[FULL_RESTORES2].textTex = SDL_CreateTextureFromSurface(renderer, image);
                    if (TTF_SizeText(font, strArr[FULL_RESTORES2], &textArr[FULL_RESTORES2].w, &textArr[FULL_RESTORES2].h) != 0) {
                        std::cout << "Size Fail\n";
                    }
                    p2Done = true;
                    turn = "P1";
                    menuState = "start";
                    // p2Done = true;
                    // turn = "P1";
                    // menuState = "start";

                    // initFont();
                }
                std::cout << "P1 has (" << inventory1.getPotions() << ", " << inventory1.getFullRestores() << ", " << inventory1.getSodaPops() << std::endl;
            }
            userInput = 0;

           
        }
        if(userInput == USER_BK)
        {
            arrowXPos = 580;
            arrowYPos = 555;
            menuState = "start";
            userInput = 0;
            if(turn == "P1")
            {
                p1Choice = "deciding";
            }
            if(turn == "P2")
            {
                p2Choice = "deciding";
            }
        }
    }
    if(menuState == "swapMenu")
    {
        // if(turn == "P1")
        // {
        std::cout << "WE ARE IN SWAP MENU" << std::endl;
        // std::cout << p1Choice << std::endl;
        // std::cout << (userInput > 0) << std::endl;
        if(turn == "P1")
        {
            if(!team1[1].getIsActive())
            {
                std::cout << "one" << std::endl;
                if(userInput == USER_DN) 
                {
                    std::cout << "DOWN\n";
                    arrowXPos = 430;
                    arrowYPos = 620;
                    userInput = 0;
                }
            }
            if(!team1[0].getIsActive())
            {
                std::cout << "balls" << std::endl;
                if(userInput == USER_LT) 
                {
                    std::cout << "two" << std::endl;
                    std::cout << "LEFT\n";
                    arrowXPos = 290;
                    arrowYPos = 565;
                    userInput = 0;
                }
            }
            if(!team1[2].getIsActive())
            {
                std::cout << "yeet" << std::endl;
                if(userInput == USER_RT) 
                {
                    std::cout << "three" << std::endl;
                    std::cout << "RIGHT\n";
                    arrowXPos = 550;
                    arrowYPos = 565;
                    userInput = 0;
                }
            }
            if(userInput == USER_EN) 
            {
                std::cout << "ENTER\n";
                // if(turn == "P1")
                // {
                if(arrowXPos == 430 && arrowYPos == 620)
                {
                    p1SwapTo = 1;
                    p1Done = true;
                    turn = "P2";
                    p2Choice = "fight";
                }
                if(arrowXPos == 290 && arrowYPos == 565)
                {
                    p1SwapTo = 0;
                    p1Done = true;
                    turn = "P2";
                    p2Choice = "fight";
                }
                if(arrowXPos == 550 && arrowYPos == 565)
                {
                    p1SwapTo = 2;
                    p1Done = true;
                    turn = "P2";
                    p2Choice = "fight";
                }
                // swap functionality
                userInput = 0;
                menuState = "start";
                
            }
        }
        if(turn == "P2")
        {
            if(!team2[1].getIsActive())
            {
                std::cout << "one" << std::endl;
                if(userInput == USER_DN) 
                {
                    std::cout << "DOWN\n";
                    arrowXPos = 430;
                    arrowYPos = 620;
                    userInput = 0;
                }
            }
            if(!team2[0].getIsActive())
            {
                std::cout << "balls" << std::endl;
                if(userInput == USER_LT) 
                {
                    std::cout << "two" << std::endl;
                    std::cout << "LEFT\n";
                    arrowXPos = 290;
                    arrowYPos = 565;
                    userInput = 0;
                }
            }
            if(!team2[2].getIsActive())
            {
                std::cout << "yeet" << std::endl;
                if(userInput == USER_RT) 
                {
                    std::cout << "three" << std::endl;
                    std::cout << "RIGHT\n";
                    arrowXPos = 550;
                    arrowYPos = 565;
                    userInput = 0;
                }
            }
            if(userInput == USER_EN) 
            {
                std::cout << "ENTER\n";
                // swap functionality
                if(arrowXPos == 430 && arrowYPos == 620)
                {
                    p2SwapTo = 1;
                    p2Done = true;
                    turn = "P1";
                    // menuState = "start";
                    hold = p1Choice;
                }
                if(arrowXPos == 290 && arrowYPos == 565)
                {
                    p2SwapTo = 0;
                    p2Done = true;
                    turn = "P1";
                    // menuState = "start";
                    hold = p1Choice;
                }
                if(arrowXPos == 550 && arrowYPos == 565)
                {
                    p2SwapTo = 2;
                    p2Done = true;
                    turn = "P1";
                    // menuState = "start";
                    hold = p1Choice;
                }
                userInput = 0;
                menuState = "start";
            }
        }
        if(userInput == USER_BK)
        {
            arrowXPos = 580;
            arrowYPos = 555;
            menuState = "start";
            userInput = 0;
            if(turn == "P1")
            {
                p1Choice = "deciding";
            }
            if(turn == "P2")
            {
                p2Choice = "deciding";
            }
        }
        userInput = 0;
    }
    if(menuState == "death")
    {
        if(p2Choice == "death")
        {
            std::cout << "yeetf\n";
            if(!team2[1].getDead())
            {
                if(userInput == USER_DN)
                {
                    arrowXPos = 430;
                    arrowYPos = 620;
                    userInput = 0;
                }
                
            }
            if(!team2[0].getDead())
            {
                if(userInput == USER_LT)
                {
                    arrowXPos = 290;
                    arrowYPos = 565;
                    userInput = 0;
                }
                
            }
            if(!team2[2].getDead())
            {
                if(userInput == USER_RT)
                {
                    arrowXPos = 550;
                    arrowYPos = 565;
                    userInput = 0;
                }
                
            }
            if(userInput == USER_EN)
            { 
                if(arrowXPos == 430 && arrowYPos == 620)
                {
                    active2 = 1;
                    p2Choice = "deciding";
                    menuState = "start";
                    p1Done = false;
                    p2Done = false;
                    team2[1].setIsActive(true);
                }
                else if(arrowXPos == 290 && arrowYPos == 565)
                {
                    active2 = 0;
                    p2Choice = "deciding";
                    menuState = "start";
                    p1Done = false;
                    p2Done = false;
                    team2[0].setIsActive(true);
                }
                else if(arrowXPos == 550 && arrowYPos == 565)
                {
                    active2 = 2;
                    p2Choice = "deciding";
                    menuState = "start";
                    p1Done = false;
                    p2Done = false;
                    team2[2].setIsActive(true);
                }
            }
            userInput = 0;

        }
        else if(p1Choice == "death")
        {
            std::cout << "yeetf\n";
            if(!team1[1].getDead())
            {
                if(userInput == USER_DN)
                {
                    arrowXPos = 430;
                    arrowYPos = 620;
                    userInput = 0;
                }
                
            }
            if(!team1[0].getDead())
            {
                if(userInput == USER_LT)
                {
                    arrowXPos = 290;
                    arrowYPos = 565;
                    userInput = 0;
                }
                
            }
            if(!team1[2].getDead())
            {
                if(userInput == USER_RT)
                {
                    arrowXPos = 550;
                    arrowYPos = 565;
                    userInput = 0;
                }
                
            }
            if(userInput == USER_EN)
            { 
                if(arrowXPos == 430 && arrowYPos == 620)
                {
                    active1 = 1;
                    p1Choice = "deciding";
                    menuState = "start";
                    p1Done = false;
                    p2Done = false;
                    team1[1].setIsActive(true);
                }
                else if(arrowXPos == 290 && arrowYPos == 565)
                {
                    active1 = 0;
                    p1Choice = "deciding";
                    menuState = "start";
                    p1Done = false;
                    p2Done = false;
                    team1[0].setIsActive(true);
                }
                else if(arrowXPos == 550 && arrowYPos == 565)
                {
                    active1 = 2;
                    p1Choice = "deciding";
                    menuState = "start";
                    p1Done = false;
                    p2Done = false;
                    team1[2].setIsActive(true);
                }
            }
            userInput = 0;

        }
    }   
}
void Game::input()
{
    SDL_Event event;
    while(SDL_PollEvent(&event))
    {
        if(event.type == SDL_QUIT) setRunning(false);
    }
    const Uint8 *keystates = SDL_GetKeyboardState(NULL);
    if(keystates[SDL_SCANCODE_ESCAPE]) running = false;
    if(keystates[SDL_SCANCODE_F11]) fullscreen = !fullscreen;
    if(menuState == "start")
    {
        std::cout << "P1 choice: " << p1Choice << std::endl;
        std::cout << "P2 choice: " << p2Choice << std::endl;
        std::cout << "menuState: " << menuState << std::endl;
        if(keystates[SDL_SCANCODE_UP]) 
        {
            userInput |= USER_UP;
            if(turn == "P1")
            {
                p1Choice = "fight";
            }
            else
            {
                p2Choice = "fight";
            }
        }
        if(keystates[SDL_SCANCODE_DOWN]) 
        {    
            userInput |= USER_DN;
            if(turn == "P1")
            {
                p1Choice = "items";
            }
            else
            {
                p2Choice = "items";
            }
        }
        if(keystates[SDL_SCANCODE_LEFT])
        {
            userInput |= USER_LT;
            if(turn == "P1")
            {
                p1Choice = "fight";
            }
            else
            {
                p2Choice = "fight";
            }
        } 
        if(keystates[SDL_SCANCODE_RIGHT]) 
        {
            userInput |= USER_RT;
            if(turn == "P1")
            {
                p1Choice = "swap";
            }
            else
            {
                p2Choice = "swap";
            }
        }
    }
    if(menuState == "fightMenu")
    {
        // p1Choice = "deciding";
        // p2Choice = "deciding";
        if(keystates[SDL_SCANCODE_UP]) 
        {
            userInput |= USER_UP;
        }
        if(keystates[SDL_SCANCODE_DOWN]) 
        {    
            userInput |= USER_DN;
        }
        if(keystates[SDL_SCANCODE_LEFT])
        {
            userInput |= USER_LT;
        } 
        if(keystates[SDL_SCANCODE_RIGHT]) 
        {
            userInput |= USER_RT;
        }
    }
    if(menuState == "itemMenu")
    {
        // p1Choice = "deciding";
        // p2Choice = "deciding";
        if(keystates[SDL_SCANCODE_UP]) 
        {
            userInput |= USER_UP;
            if(turn == "P1")
            {
                // if(inventory1.getPotions() != 0)
                // {
                    p1Choice = "potion";
            //     }
            }
            else
            {
                // if(inventory2.getPotions() != 0)
                // {
                    p2Choice = "potion";
                // }
            }
        }
        if(keystates[SDL_SCANCODE_DOWN]) 
        {   
            userInput |= USER_DN;
            if(turn == "P1")
            {
                // if(inventory1.getSodaPops() != 0)
                // {
                    p1Choice = "soda";
                // }
            }
            else
            {
                // if(inventory2.getSodaPops() != 0)
                // {
                    p2Choice = "soda";
                // }
            } 
        }
        if(keystates[SDL_SCANCODE_LEFT])
        {
            userInput |= USER_LT;
            if(turn == "P1")
            {
                // if(inventory1.getPotions() != 0)
                // {
                    p1Choice = "potion";
                // }
            }
            else
            {
                // if(inventory2.getPotions() != 0)
                // {
                    p2Choice = "potion";
                // }
            }
        } 
        if(keystates[SDL_SCANCODE_RIGHT]) 
        {
            userInput |= USER_RT;
            if(turn == "P1")
            {
                // if(inventory1.getFullRestores() != 0)
                // {
                    p1Choice = "restore";
                // }
            }
            else
            {
                // if(inventory2.getFullRestores() != 0)
                // {
                    p2Choice = "restore";
                // }
            }
        }
    }
    if(menuState == "swapMenu")
    {
        // p1Choice = "deciding";
        // p2Choice = "deciding";
        // if(keystates[SDL_SCANCODE_UP]) 
        // {
        //     userInput |= USER_UP;
        // }
        if(keystates[SDL_SCANCODE_DOWN]) 
        {    
            userInput |= USER_DN;
        }
        if(keystates[SDL_SCANCODE_LEFT])
        {
            userInput |= USER_LT;
        } 
        if(keystates[SDL_SCANCODE_RIGHT]) 
        {
            userInput |= USER_RT;
        }
    }
    if(menuState == "death")
    {
        if(keystates[SDL_SCANCODE_DOWN]) 
        {    
            userInput |= USER_DN;
        }
        if(keystates[SDL_SCANCODE_LEFT])
        {
            userInput |= USER_LT;
        } 
        if(keystates[SDL_SCANCODE_RIGHT]) 
        {
            userInput |= USER_RT;
        }
    }
    if(keystates[SDL_SCANCODE_RETURN]) userInput |= USER_EN;
    if(keystates[SDL_SCANCODE_BACKSPACE]) userInput |= USER_BK;
    
    SDL_ResetKeyboard();
}
void Game::draw()
{
    if(winner != "none")
    {

        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        assignWinner();
        // SDL_RenderCopy(renderer, menuText, &menu, &dstrect);
    }
    else
    {
        SDL_RenderCopy(renderer, bgTexture, NULL, NULL); // background render
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // colors something

        if(p1SwapTo != active1)
        {
            spriteRect1.x = 0; // start at x = 0
            spriteRect1.y = 0; // start at y = 0
            spriteRect1.w = SPRITE_SIZE; // capture SPRITE_SIZE amount of pixels outward from (0, 0)
            spriteRect1.h = SPRITE_SIZE;  // capture SPRITE_SIZE amount of pixels downward from (SPRITESIZE, 0)
            
            // destination rectangle to position and size sprite rectangle
            dstrect.x = 350 - SPRITE_SIZE;
            dstrect.y = 500 - SPRITE_SIZE;
            dstrect.w = spriteRect1.w * 2;
            dstrect.h = spriteRect1.h * 2;

            // if (timer != 0)
            SDL_RenderCopy(renderer, playerOne[active1], &spriteRect1, &dstrect); // player 1 pokemon render
        }  
        if(p2SwapTo != active2)
        {    
            spriteRect2.x = 0; // start at x = 0
            spriteRect2.y = 0; // start at y = 0
            spriteRect2.w = SPRITE_SIZE; // capture SPRITE_SIZE amount of pixels outward from (0, 0)
            spriteRect2.h = SPRITE_SIZE; // capture SPRITE_SIZE amount of pixels downward from (SPRITESIZE, 0)
            
            // destination rectangle to position and size sprite rectangle
            dstrect.x = 800 - SPRITE_SIZE;
            dstrect.y = (475 - SPRITE_SIZE) / 2;
            dstrect.w = spriteRect2.w * 3;
            dstrect.h = spriteRect2.h * 3;
            
            
            SDL_RenderCopy(renderer, playerTwo[active2], &spriteRect2, &dstrect); // player 2 pokemon render
        }

        // Active Pokemon health
        if(active1 == 0)
        {
            dstrect.x = 0;
            dstrect.y = 1;
            dstrect.w = textArr[CHIKORITA_HP].w;
            dstrect.h = textArr[CHIKORITA_HP].h;

            SDL_RenderCopy(renderer, textArr[CHIKORITA_HP].textTex, NULL, &dstrect);
        } 
        if(active2 == 0)
        {
            dstrect.x = WIDTH - textArr[BULBASAUR_HP].w;
            dstrect.y = 1;
            dstrect.w = textArr[BULBASAUR_HP].w;
            dstrect.h = textArr[BULBASAUR_HP].h;

            SDL_RenderCopy(renderer, textArr[BULBASAUR_HP].textTex, NULL, &dstrect);
        }
        if(active1 == 1)
        {
            dstrect.x = 0;
            dstrect.y = 1;
            dstrect.w = textArr[TOTODILE_HP].w;
            dstrect.h = textArr[TOTODILE_HP].h;

            SDL_RenderCopy(renderer, textArr[TOTODILE_HP].textTex, NULL, &dstrect);
        } 
        if(active2 == 1)
        {
            dstrect.x = WIDTH - textArr[SQUIRTLE_HP].w;
            dstrect.y = 1;
            dstrect.w = textArr[SQUIRTLE_HP].w;
            dstrect.h = textArr[SQUIRTLE_HP].h;

            SDL_RenderCopy(renderer, textArr[SQUIRTLE_HP].textTex, NULL, &dstrect);
        }
        if(active1 == 2)
        {
            dstrect.x = 0;
            dstrect.y = 1;
            dstrect.w = textArr[CYNDAQUIL_HP].w;
            dstrect.h = textArr[CYNDAQUIL_HP].h;

            SDL_RenderCopy(renderer, textArr[CYNDAQUIL_HP].textTex, NULL, &dstrect);
        } 
        if(active2 == 2)
        {
            dstrect.x = WIDTH - textArr[CHARMANDER_HP].w;
            dstrect.y = 1;
            dstrect.w = textArr[CHARMANDER_HP].w;
            dstrect.h = textArr[CHARMANDER_HP].h;

            SDL_RenderCopy(renderer, textArr[CHARMANDER_HP].textTex, NULL, &dstrect);
        } 
        // menu
        menu.x = 0;
        menu.y = 0;
        menu.w = 313 + 990;
        menu.h = 93 + 110;

        dstrect.x = 0;
        dstrect.y = 517;
        dstrect.w = menu.w;
        dstrect.h = menu.h;
        if(p1Done && p2Done)
        {
            SDL_RenderCopy(renderer, emptyMenuText, &menu, &dstrect);
            if(p2Choice == "swap" && p1Choice != "swap" && p1Choice != "deciding")
            {
                // p1Choice = hold;
                std::cout << "Whoopty\n";
                if(timer++ == 200) timer = 0;
                // SDL_RenderCopy(renderer, emptyMenuText, &menu, &dstrect);
                if(p2SwapTo != -1)
                {
                    team2[active2].setIsActive(false);
                    active2 = p2SwapTo;
                    team2[active2].setIsActive(true);
                    p2SwapTo = -1;
                }
                spriteRect2.x = 0; // start at x = 0
                spriteRect2.y = 0; // start at y = 0
                spriteRect2.w = SPRITE_SIZE; // capture SPRITE_SIZE amount of pixels outward from (0, 0)
                spriteRect2.h = SPRITE_SIZE;  // capture SPRITE_SIZE amount of pixels downward from (SPRITESIZE, 0)
                
                // destination rectangle to position and size sprite rectangle
                dstrect.x = 800 - SPRITE_SIZE;
                dstrect.y = (475 - SPRITE_SIZE) / 2;
                dstrect.w = spriteRect2.w * 3;
                dstrect.h = spriteRect2.h * 3;

                // if (timer != 0)
                SDL_RenderCopy(renderer, playerTwo[active2], &spriteRect1, &dstrect); // player 1 pokemon render
                if(timer != 0)
                {
                    dstrect.x = 120;
                    dstrect.y = 600;
                    dstrect.w = textArr[P2_SWAP].w;
                    dstrect.h = textArr[P2_SWAP].h;
                    SDL_RenderCopy(renderer, textArr[P2_SWAP].textTex, NULL, &dstrect);
                }
                else
                { 
                    p2Choice = "deciding";
                    p2SwapTo = -1;
                    p1Choice = hold;
                    hold = "";
                }
            }
            if((p1Choice == "potion" || p1Choice == "restore" || p1Choice == "soda") && p2Choice != "swap")
            {
                if(timer++ == 200) timer = 0;
                if(timer != 0)
                {
                    dstrect.x = 120;
                    dstrect.y = 565;
                    dstrect.w = textArr[P1_HEAL].w;
                    dstrect.h = textArr[P1_HEAL].h;
                    SDL_RenderCopy(renderer, textArr[P1_HEAL].textTex, NULL, &dstrect);
                }
                else
                {
                    std::cout << "P1 Health Before: " << team1[active1].getHP() << std::endl;
                    heal("P1");
                    // setting team 1 hp
                    if(active1 == 0)
                    {
                        std::string tempHeal1 = to_string(team1[0].getHP()) + "/" + to_string(team1[0].getFullHealth());
                        strArr[CHIKORITA_HP] = tempHeal1.c_str();
                        image = TTF_RenderText_Blended(font, strArr[CHIKORITA_HP], (SDL_Color){0, 0, 0, 255});
                        textArr[CHIKORITA_HP].textTex = SDL_CreateTextureFromSurface(renderer, image);
                        if (TTF_SizeText(font, strArr[CHIKORITA_HP], &textArr[CHIKORITA_HP].w, &textArr[CHIKORITA_HP].h) != 0) {
                            std::cout << "Size Fail\n";
                        }
                        dstrect.x = 0;
                        dstrect.y = 1;
                        dstrect.w = textArr[CHIKORITA_HP].w;
                        dstrect.h = textArr[CHIKORITA_HP].h;

                        SDL_RenderCopy(renderer, textArr[CHIKORITA_HP].textTex, NULL, &dstrect);
                        
                    } 
                    if(active1 == 1)
                    {
                        std::string tempHeal2 = to_string(team1[1].getHP()) + "/" + to_string(team1[1].getFullHealth());
                        strArr[TOTODILE_HP] = tempHeal2.c_str();
                        image = TTF_RenderText_Blended(font, strArr[TOTODILE_HP], (SDL_Color){0, 0, 0, 255});
                        textArr[TOTODILE_HP].textTex = SDL_CreateTextureFromSurface(renderer, image);
                        if (TTF_SizeText(font, strArr[TOTODILE_HP], &textArr[TOTODILE_HP].w, &textArr[TOTODILE_HP].h) != 0) {
                            std::cout << "Size Fail\n";
                        }
                        dstrect.x = 0;
                        dstrect.y = 1;
                        dstrect.w = textArr[TOTODILE_HP].w;
                        dstrect.h = textArr[TOTODILE_HP].h;

                        SDL_RenderCopy(renderer, textArr[TOTODILE_HP].textTex, NULL, &dstrect);
                    } 
                    if(active1 == 2)
                    {
                        std::string tempHeal3 = to_string(team1[2].getHP()) + "/" + to_string(team1[2].getFullHealth());
                        strArr[CYNDAQUIL_HP] = tempHeal3.c_str();
                        image = TTF_RenderText_Blended(font, strArr[CYNDAQUIL_HP], (SDL_Color){0, 0, 0, 255});
                        textArr[CYNDAQUIL_HP].textTex = SDL_CreateTextureFromSurface(renderer, image);
                        if (TTF_SizeText(font, strArr[CYNDAQUIL_HP], &textArr[CYNDAQUIL_HP].w, &textArr[CYNDAQUIL_HP].h) != 0) {
                            std::cout << "Size Fail\n";
                        }
                        dstrect.x = 0;
                        dstrect.y = 1;
                        dstrect.w = textArr[CYNDAQUIL_HP].w;
                        dstrect.h = textArr[CYNDAQUIL_HP].h;

                        SDL_RenderCopy(renderer, textArr[CYNDAQUIL_HP].textTex, NULL, &dstrect);
                    } 
                    
                    
                    
                    
                    // SDL_RenderCopy(renderer, textArr[CHIKORITA_HP].textTex, NULL, &dstrect);
                    
                    std::cout << "P1 Health After: " << team1[active1].getHP() << std::endl;
                    if(p2Choice == "deciding")
                    {
                        p1Done = false;
                        p2Done = false;
                        menuState = "start";
                        p1Choice = "deciding";
                    }
                    else p1Choice = "deciding";
                    
                }
            }
            if((p1Choice == "move1" || p1Choice == "move2" || p1Choice == "move3" || p1Choice == "move4") && p2Choice != "swap" && !team2[active2].getDead())
            {
                if(timer++ == 200) timer = 0;
                if(timer != 0)
                {
                    // Chikorita Actives
                    if(p1Choice == "move1" && active1 == 0)
                    {
                        std::cout << "wowowo\n";
                        dstrect.x = 120;
                        dstrect.y = 565;
                        dstrect.w = textArr[CHIK_TACKLE_1].w;
                        dstrect.h = textArr[CHIK_TACKLE_1].h;
                        SDL_RenderCopy(renderer, textArr[CHIK_TACKLE_1].textTex, NULL, &dstrect);
                    }
                    else if(p1Choice == "move2" && active1 == 0)
                    {
                        dstrect.x = 120;
                        dstrect.y = 565;
                        dstrect.w = textArr[CHIK_RAZOR_2].w;
                        dstrect.h = textArr[CHIK_RAZOR_2].h;
                        SDL_RenderCopy(renderer, textArr[CHIK_RAZOR_2].textTex, NULL, &dstrect);
                    }
                    else if(p1Choice == "move3" && active1 == 0)
                    {
                        dstrect.x = 120;
                        dstrect.y = 565;
                        dstrect.w = textArr[CHIK_MAGIC_3].w;
                        dstrect.h = textArr[CHIK_MAGIC_3].h;
                        SDL_RenderCopy(renderer, textArr[CHIK_MAGIC_3].textTex, NULL, &dstrect);
                    }
                    else if(p1Choice == "move4" && active1 == 0)
                    {
                        dstrect.x = 120;
                        dstrect.y = 565;
                        dstrect.w = textArr[CHIK_SLAM_4].w;
                        dstrect.h = textArr[CHIK_SLAM_4].h;
                        SDL_RenderCopy(renderer, textArr[CHIK_SLAM_4].textTex, NULL, &dstrect);
                    }

                    // Totodile Actives
                    if(p1Choice == "move1" && active1 == 1)
                    {
                        dstrect.x = 120;
                        dstrect.y = 565;
                        dstrect.w = textArr[TOTO_SCRATCH_1].w;
                        dstrect.h = textArr[TOTO_SCRATCH_1].h;
                        SDL_RenderCopy(renderer, textArr[TOTO_SCRATCH_1].textTex, NULL, &dstrect);
                    }
                    else if(p1Choice == "move2" && active1 == 1)
                    {
                        dstrect.x = 120;
                        dstrect.y = 565;
                        dstrect.w = textArr[TOTO_GUN_2].w;
                        dstrect.h = textArr[TOTO_GUN_2].h;
                        SDL_RenderCopy(renderer, textArr[TOTO_GUN_2].textTex, NULL, &dstrect);
                    }
                    else if(p1Choice == "move3" && active1 == 1)
                    {
                        dstrect.x = 120;
                        dstrect.y = 565;
                        dstrect.w = textArr[TOTO_SLASH_3].w;
                        dstrect.h = textArr[TOTO_SLASH_3].h;
                        SDL_RenderCopy(renderer, textArr[TOTO_SLASH_3].textTex, NULL, &dstrect);
                    }
                    else if(p1Choice == "move4" && active1 == 1)
                    {
                        dstrect.x = 120;
                        dstrect.y = 565;
                        dstrect.w = textArr[TOTO_TAIL_4].w;
                        dstrect.h = textArr[TOTO_TAIL_4].h;
                        SDL_RenderCopy(renderer, textArr[TOTO_TAIL_4].textTex, NULL, &dstrect);
                    }

                    // Cyndaquil Actives
                    if(p1Choice == "move1" && active1 == 2)
                    {
                        dstrect.x = 120;
                        dstrect.y = 565;
                        dstrect.w = textArr[CYNDA_EMBER_1].w;
                        dstrect.h = textArr[CYNDA_EMBER_1].h;
                        SDL_RenderCopy(renderer, textArr[CYNDA_EMBER_1].textTex, NULL, &dstrect);
                    }
                    else if(p1Choice == "move2" && active1 == 2)
                    {
                        dstrect.x = 120;
                        dstrect.y = 565;
                        dstrect.w = textArr[CYNDA_QUICK_2].w;
                        dstrect.h = textArr[CYNDA_QUICK_2].h;
                        SDL_RenderCopy(renderer, textArr[CYNDA_QUICK_2].textTex, NULL, &dstrect);
                    }
                    else if(p1Choice == "move3" && active1 == 2)
                    {
                        dstrect.x = 120;
                        dstrect.y = 565;
                        dstrect.w = textArr[CYNDA_WHEEL_3].w;
                        dstrect.h = textArr[CYNDA_WHEEL_3].h;
                        SDL_RenderCopy(renderer, textArr[CYNDA_WHEEL_3].textTex, NULL, &dstrect);
                    }
                    else if(p1Choice == "move4" && active1 == 2)
                    {
                        dstrect.x = 120;
                        dstrect.y = 565;
                        dstrect.w = textArr[CYNDA_EDGE_4].w;
                        dstrect.h = textArr[CYNDA_EDGE_4].h;
                        SDL_RenderCopy(renderer, textArr[CYNDA_EDGE_4].textTex, NULL, &dstrect);
                    }
                }
                else
                {
                    attack("P1");
                    if(active2 == 0)
                    {
                        std::string tempAtt4 = to_string(team2[0].getHP()) + "/" + to_string(team2[0].getFullHealth());
                        strArr[BULBASAUR_HP] = tempAtt4.c_str();
                        image = TTF_RenderText_Blended(font, strArr[BULBASAUR_HP], (SDL_Color){0, 0, 0, 255});
                        textArr[BULBASAUR_HP].textTex = SDL_CreateTextureFromSurface(renderer, image);
                        if (TTF_SizeText(font, strArr[BULBASAUR_HP], &textArr[BULBASAUR_HP].w, &textArr[BULBASAUR_HP].h) != 0) {
                            std::cout << "Size Fail\n";
                        }
                        dstrect.x = 0;
                        dstrect.y = 1;
                        dstrect.w = textArr[BULBASAUR_HP].w;
                        dstrect.h = textArr[BULBASAUR_HP].h;

                        SDL_RenderCopy(renderer, textArr[BULBASAUR_HP].textTex, NULL, &dstrect);
                        
                    } 
                    if(active2 == 1)
                    {
                        std::string tempAtt5 = to_string(team2[1].getHP()) + "/" + to_string(team2[1].getFullHealth());
                        strArr[SQUIRTLE_HP] = tempAtt5.c_str();
                        image = TTF_RenderText_Blended(font, strArr[SQUIRTLE_HP], (SDL_Color){0, 0, 0, 255});
                        textArr[SQUIRTLE_HP].textTex = SDL_CreateTextureFromSurface(renderer, image);
                        if (TTF_SizeText(font, strArr[SQUIRTLE_HP], &textArr[SQUIRTLE_HP].w, &textArr[SQUIRTLE_HP].h) != 0) {
                            std::cout << "Size Fail\n";
                        }
                        dstrect.x = 0;
                        dstrect.y = 1;
                        dstrect.w = textArr[SQUIRTLE_HP].w;
                        dstrect.h = textArr[SQUIRTLE_HP].h;

                        SDL_RenderCopy(renderer, textArr[SQUIRTLE_HP].textTex, NULL, &dstrect);
                    } 
                    if(active2 == 2)
                    {
                        std::string tempAtt6 = to_string(team2[2].getHP()) + "/" + to_string(team2[2].getFullHealth());
                        strArr[CHARMANDER_HP] = tempAtt6.c_str();
                        image = TTF_RenderText_Blended(font, strArr[CHARMANDER_HP], (SDL_Color){0, 0, 0, 255});
                        textArr[CHARMANDER_HP].textTex = SDL_CreateTextureFromSurface(renderer, image);
                        if (TTF_SizeText(font, strArr[CHARMANDER_HP], &textArr[CHARMANDER_HP].w, &textArr[CHARMANDER_HP].h) != 0) {
                            std::cout << "Size Fail\n";
                        }
                        dstrect.x = 0;
                        dstrect.y = 1;
                        dstrect.w = textArr[CHARMANDER_HP].w;
                        dstrect.h = textArr[CHARMANDER_HP].h;

                        SDL_RenderCopy(renderer, textArr[CHARMANDER_HP].textTex, NULL, &dstrect);
                    }
                    if(team2[active2].getDead()) 
                    {
                        menuState = "death";
                        p2Choice = "death";

                    }
                    else if(p2Choice == "deciding")
                    {
                        p1Choice = "deciding";
                        menuState = "start";
                        p1Done = false;
                        p2Done = false;
                    }
                    else p1Choice = "deciding";
                }
            }
            if((p2Choice == "potion" || p2Choice == "restore" || p2Choice == "soda") && (p1Choice == "deciding"))
            {
                if(timer++ == 200) timer = 0;
                if(timer != 0)
                {
                    dstrect.x = 120;
                    dstrect.y = 565;
                    dstrect.w = textArr[P2_HEAL].w;
                    dstrect.h = textArr[P2_HEAL].h;
                    SDL_RenderCopy(renderer, textArr[P2_HEAL].textTex, NULL, &dstrect);
                }
                else
                {
                    std::cout << "P2 Health Before: " << team1[active2].getHP() << std::endl;
                    heal("P2");
                    if(active2 == 0)
                    {
                        // setting team 2 hp
                        std::string tempHeal4 = to_string(team2[0].getHP()) + "/" + to_string(team2[0].getFullHealth());
                        strArr[BULBASAUR_HP] = tempHeal4.c_str();
                        image = TTF_RenderText_Blended(font, strArr[BULBASAUR_HP], (SDL_Color){0, 0, 0, 255});
                        textArr[BULBASAUR_HP].textTex = SDL_CreateTextureFromSurface(renderer, image);
                        if (TTF_SizeText(font, strArr[BULBASAUR_HP], &textArr[BULBASAUR_HP].w, &textArr[BULBASAUR_HP].h) != 0) {
                            std::cout << "Size Fail\n";
                        }
                        dstrect.x = WIDTH - textArr[BULBASAUR_HP].w;
                        dstrect.y = 1;
                        dstrect.w = textArr[BULBASAUR_HP].w;
                        dstrect.h = textArr[BULBASAUR_HP].h;

                        SDL_RenderCopy(renderer, textArr[BULBASAUR_HP].textTex, NULL, &dstrect);
                    }
                    if(active2 == 1)
                    {
                        std::string tempHeal5 = to_string(team2[1].getHP()) + "/" + to_string(team2[1].getFullHealth());
                        strArr[SQUIRTLE_HP] = tempHeal5.c_str();
                        image = TTF_RenderText_Blended(font, strArr[SQUIRTLE_HP], (SDL_Color){0, 0, 0, 255});
                        textArr[SQUIRTLE_HP].textTex = SDL_CreateTextureFromSurface(renderer, image);
                        if (TTF_SizeText(font, strArr[SQUIRTLE_HP], &textArr[SQUIRTLE_HP].w, &textArr[SQUIRTLE_HP].h) != 0) {
                            std::cout << "Size Fail\n";
                        }
                        dstrect.x = WIDTH - textArr[SQUIRTLE_HP].w;
                        dstrect.y = 1;
                        dstrect.w = textArr[SQUIRTLE_HP].w;
                        dstrect.h = textArr[SQUIRTLE_HP].h;

                        SDL_RenderCopy(renderer, textArr[SQUIRTLE_HP].textTex, NULL, &dstrect);
                    }
                    if(active2 == 2)
                    {
                        std::string tempHeal6 = to_string(team2[2].getHP()) + "/" + to_string(team2[2].getFullHealth());
                        strArr[CHARMANDER_HP] = tempHeal6.c_str();
                        image = TTF_RenderText_Blended(font, strArr[CHARMANDER_HP], (SDL_Color){0, 0, 0, 255});
                        textArr[CHARMANDER_HP].textTex = SDL_CreateTextureFromSurface(renderer, image);
                        if (TTF_SizeText(font, strArr[CHARMANDER_HP], &textArr[CHARMANDER_HP].w, &textArr[CHARMANDER_HP].h) != 0) {
                            std::cout << "Size Fail\n";
                        }
                        dstrect.x = WIDTH - textArr[CHARMANDER_HP].w;
                        dstrect.y = 1;
                        dstrect.w = textArr[CHARMANDER_HP].w;
                        dstrect.h = textArr[CHARMANDER_HP].h;

                        SDL_RenderCopy(renderer, textArr[CHARMANDER_HP].textTex, NULL, &dstrect);
                    }
                    
                    std::cout << "P2 Health After: " << team1[active2].getHP() << std::endl;
                    p2Choice = "deciding";
                    p1Done = false;
                    p2Done = false;
                    menuState = "start";

                }
            }
            if(team2[active2].getDead())
            {
                assignWinner();
                if(timer++ == 200) timer = 0;
                if(timer != 0)
                {
                    std::cout << menuState << "1\n";
                    std::cout << p2Choice << "2\n";
                    dstrect.x = 120;
                    dstrect.y = 565;
                    dstrect.w = textArr[P2_FAINTED].w/2;
                    dstrect.h = textArr[P2_FAINTED].h/2;
                    SDL_RenderCopy(renderer, textArr[P2_FAINTED].textTex, NULL, &dstrect);
                    
                    arrow.x = 0;
                    arrow.y = 0;
                    arrow.w = 750;
                    arrow.h = 750;

                    dstrect.x = arrowXPos;// 580, 970
                                    // 85 
                    
                    dstrect.y = arrowYPos; // 555, 620
                                        // 545
                    dstrect.w = arrow.w / 12;
                    dstrect.h = arrow.h / 9;
                    SDL_RenderCopy(renderer, arrowText, &arrow, &dstrect);

                    if(!team2[0].getDead())
                    {
                        dstrect.x = 350;
                        dstrect.y = 575;
                        dstrect.w = textArr[BULBASAUR_NAME].w / 1;
                        dstrect.h = textArr[BULBASAUR_NAME].h / 1;
                        SDL_RenderCopy(renderer, textArr[BULBASAUR_NAME].textTex, NULL, &dstrect);
                    }
                    if(!team2[1].getDead())
                    {
                        dstrect.x = 500;
                        dstrect.y = 630;
                        dstrect.w = textArr[SQUIRTLE_NAME].w / 1;
                        dstrect.h = textArr[SQUIRTLE_NAME].h / 1;
                        SDL_RenderCopy(renderer, textArr[SQUIRTLE_NAME].textTex, NULL, &dstrect);
                    }
                    if(!team2[2].getDead())
                    {
                        dstrect.x = 620;
                        dstrect.y = 575;
                        dstrect.w = textArr[CHARMANDER_NAME].w / 1;
                        dstrect.h = textArr[CHARMANDER_NAME].h / 1;
                        SDL_RenderCopy(renderer, textArr[CHARMANDER_NAME].textTex, NULL, &dstrect);
                    }
                }
            }
            else if((p2Choice == "move1" || p2Choice == "move2" || p2Choice == "move3" || p2Choice == "move4") && p1Choice == "deciding")
            {
                if(timer++ == 200) timer = 0;
                if(timer != 0)
                {
                    // Bulbasaur Actives
                    if(p2Choice == "move1" && active2 == 0)
                    {
                        dstrect.x = 120;
                        dstrect.y = 565;
                        dstrect.w = textArr[BULBA_VINE_1].w;
                        dstrect.h = textArr[BULBA_VINE_1].h;
                        SDL_RenderCopy(renderer, textArr[BULBA_VINE_1].textTex, NULL, &dstrect);
                    }
                    else if(p2Choice == "move2" && active2 == 0)
                    {
                        dstrect.x = 120;
                        dstrect.y = 565;
                        dstrect.w = textArr[BULBA_TAKE_2].w;
                        dstrect.h = textArr[BULBA_TAKE_2].h;
                        SDL_RenderCopy(renderer, textArr[BULBA_TAKE_2].textTex, NULL, &dstrect);
                    }
                    else if(p2Choice == "move3" && active2 == 0)
                    {
                        dstrect.x = 120;
                        dstrect.y = 565;
                        dstrect.w = textArr[BULBA_POWER_3].w;
                        dstrect.h = textArr[BULBA_POWER_3].h;
                        SDL_RenderCopy(renderer, textArr[BULBA_POWER_3].textTex, NULL, &dstrect);
                    }
                    else if(p2Choice == "move4" && active2 == 0)
                    {
                        dstrect.x = 120;
                        dstrect.y = 565;
                        dstrect.w = textArr[BULBA_FACADE_4].w;
                        dstrect.h = textArr[BULBA_FACADE_4].h;
                        SDL_RenderCopy(renderer, textArr[BULBA_FACADE_4].textTex, NULL, &dstrect);
                    }

                    // Squirtle Actives
                    if(p2Choice == "move1" && active2 == 1)
                    {
                        dstrect.x = 120;
                        dstrect.y = 565;
                        dstrect.w = textArr[SQUI_SPIN_1].w;
                        dstrect.h = textArr[SQUI_SPIN_1].h;
                        SDL_RenderCopy(renderer, textArr[SQUI_SPIN_1].textTex, NULL, &dstrect);
                    }
                    else if(p2Choice == "move2" && active2 == 1)
                    {
                        dstrect.x = 120;
                        dstrect.y = 565;
                        dstrect.w = textArr[SQUI_PULSE_2].w;
                        dstrect.h = textArr[SQUI_PULSE_2].h;
                        SDL_RenderCopy(renderer, textArr[SQUI_PULSE_2].textTex, NULL, &dstrect);
                    }
                    else if(p2Choice == "move3" && active2 == 1)
                    {
                        dstrect.x = 120;
                        dstrect.y = 565;
                        dstrect.w = textArr[SQUI_PUMP_3].w;
                        dstrect.h = textArr[SQUI_PUMP_3].h;
                        SDL_RenderCopy(renderer, textArr[SQUI_PUMP_3].textTex, NULL, &dstrect);
                    }
                    else if(p2Choice == "move4" && active2 == 1)
                    {
                        dstrect.x = 120;
                        dstrect.y = 565;
                        dstrect.w = textArr[SQUI_JET_4].w;
                        dstrect.h = textArr[SQUI_JET_4].h;
                        SDL_RenderCopy(renderer, textArr[SQUI_JET_4].textTex, NULL, &dstrect);
                    }

                    // Charmander Actives
                    if(p2Choice == "move1" && active2 == 2)
                    {
                        dstrect.x = 120;
                        dstrect.y = 565;
                        dstrect.w = textArr[CHARM_FANG_1].w;
                        dstrect.h = textArr[CHARM_FANG_1].h;
                        SDL_RenderCopy(renderer, textArr[CHARM_FANG_1].textTex, NULL, &dstrect);
                    }
                    else if(p2Choice == "move2" && active2 == 2)
                    {
                        dstrect.x = 120;
                        dstrect.y = 565;
                        dstrect.w = textArr[CHARM_THROWER_2].w;
                        dstrect.h = textArr[CHARM_THROWER_2].h;
                        SDL_RenderCopy(renderer, textArr[CHARM_THROWER_2].textTex, NULL, &dstrect);
                    }
                    else if(p2Choice == "move3" && active2 == 2)
                    {
                        dstrect.x = 120;
                        dstrect.y = 565;
                        dstrect.w = textArr[CHARM_SWIPE_3].w;
                        dstrect.h = textArr[CHARM_SWIPE_3].h;
                        SDL_RenderCopy(renderer, textArr[CHARM_SWIPE_3].textTex, NULL, &dstrect);
                    }
                    else if(p2Choice == "move4" && active2 == 2)
                    {
                        dstrect.x = 120;
                        dstrect.y = 565;
                        dstrect.w = textArr[CHARM_BLITZ_4].w;
                        dstrect.h = textArr[CHARM_BLITZ_4].h;
                        SDL_RenderCopy(renderer, textArr[CHARM_BLITZ_4].textTex, NULL, &dstrect);
                    }
                }
                else
                {
                    attack("P2");
                    if(active1 == 0)
                    {
                        std::string tempAtt1 = to_string(team1[0].getHP()) + "/" + to_string(team1[0].getFullHealth());
                        strArr[CHIKORITA_HP] = tempAtt1.c_str();
                        image = TTF_RenderText_Blended(font, strArr[CHIKORITA_HP], (SDL_Color){0, 0, 0, 255});
                        textArr[CHIKORITA_HP].textTex = SDL_CreateTextureFromSurface(renderer, image);
                        if (TTF_SizeText(font, strArr[CHIKORITA_HP], &textArr[CHIKORITA_HP].w, &textArr[CHIKORITA_HP].h) != 0) {
                            std::cout << "Size Fail\n";
                        }
                        dstrect.x = 0;
                        dstrect.y = 1;
                        dstrect.w = textArr[CHIKORITA_HP].w;
                        dstrect.h = textArr[CHIKORITA_HP].h;

                        SDL_RenderCopy(renderer, textArr[CHIKORITA_HP].textTex, NULL, &dstrect);
                        
                    } 
                    if(active1 == 1)
                    {
                        std::string tempAtt2 = to_string(team1[1].getHP()) + "/" + to_string(team1[1].getFullHealth());
                        strArr[TOTODILE_HP] = tempAtt2.c_str();
                        image = TTF_RenderText_Blended(font, strArr[TOTODILE_HP], (SDL_Color){0, 0, 0, 255});
                        textArr[TOTODILE_HP].textTex = SDL_CreateTextureFromSurface(renderer, image);
                        if (TTF_SizeText(font, strArr[TOTODILE_HP], &textArr[TOTODILE_HP].w, &textArr[TOTODILE_HP].h) != 0) {
                            std::cout << "Size Fail\n";
                        }
                        dstrect.x = 0;
                        dstrect.y = 1;
                        dstrect.w = textArr[TOTODILE_HP].w;
                        dstrect.h = textArr[TOTODILE_HP].h;

                        SDL_RenderCopy(renderer, textArr[TOTODILE_HP].textTex, NULL, &dstrect);
                    } 
                    if(active1 == 2)
                    {
                        std::string tempAtt3 = to_string(team1[2].getHP()) + "/" + to_string(team1[2].getFullHealth());
                        strArr[CYNDAQUIL_HP] = tempAtt3.c_str();
                        image = TTF_RenderText_Blended(font, strArr[CYNDAQUIL_HP], (SDL_Color){0, 0, 0, 255});
                        textArr[CYNDAQUIL_HP].textTex = SDL_CreateTextureFromSurface(renderer, image);
                        if (TTF_SizeText(font, strArr[CYNDAQUIL_HP], &textArr[CYNDAQUIL_HP].w, &textArr[CYNDAQUIL_HP].h) != 0) {
                            std::cout << "Size Fail\n";
                        }
                        dstrect.x = 0;
                        dstrect.y = 1;
                        dstrect.w = textArr[CYNDAQUIL_HP].w;
                        dstrect.h = textArr[CYNDAQUIL_HP].h;

                        SDL_RenderCopy(renderer, textArr[CYNDAQUIL_HP].textTex, NULL, &dstrect);
                    }
                    if(team1[active1].getDead()) 
                    {
                        menuState = "death";
                        p1Choice = "death";

                    }
                    else if(p1Choice == "deciding")
                    {
                        menuState = "start";
                        p1Done = false;
                        p2Done = false;
                    }
                }
            }
            if(team1[active1].getDead())
            {
                assignWinner();
                if(timer++ == 200) timer = 0;
                if(timer != 0)
                {
                    std::cout << menuState << "1\n";
                    std::cout << p2Choice << "2\n";
                    dstrect.x = 120;
                    dstrect.y = 565;
                    dstrect.w = textArr[P1_FAINTED].w/2;
                    dstrect.h = textArr[P1_FAINTED].h/2;
                    SDL_RenderCopy(renderer, textArr[P1_FAINTED].textTex, NULL, &dstrect);
                    
                    arrow.x = 0;
                    arrow.y = 0;
                    arrow.w = 750;
                    arrow.h = 750;

                    dstrect.x = arrowXPos;// 580, 970
                                    // 85 
                    
                    dstrect.y = arrowYPos; // 555, 620
                                        // 545
                    dstrect.w = arrow.w / 12;
                    dstrect.h = arrow.h / 9;
                    SDL_RenderCopy(renderer, arrowText, &arrow, &dstrect);

                    if(!team1[0].getDead())
                    {
                        dstrect.x = 350;
                        dstrect.y = 575;
                        dstrect.w = textArr[CHIKORITA_NAME].w / 1;
                        dstrect.h = textArr[CHIKORITA_NAME].h / 1;
                        SDL_RenderCopy(renderer, textArr[CHIKORITA_NAME].textTex, NULL, &dstrect);
                    }
                    if(!team1[1].getDead())
                    {
                        dstrect.x = 500;
                        dstrect.y = 630;
                        dstrect.w = textArr[TOTODILE_NAME].w / 1;
                        dstrect.h = textArr[TOTODILE_NAME].h / 1;
                        SDL_RenderCopy(renderer, textArr[TOTODILE_NAME].textTex, NULL, &dstrect);
                    }
                    if(!team1[2].getDead())
                    {
                        dstrect.x = 620;
                        dstrect.y = 575;
                        dstrect.w = textArr[CYNDAQUIL_NAME].w / 1;
                        dstrect.h = textArr[CYNDAQUIL_NAME].h / 1;
                        SDL_RenderCopy(renderer, textArr[CYNDAQUIL_NAME].textTex, NULL, &dstrect);
                    }
                }
            }
            if(p1Choice == "swap")
            {
                if(timer++ == 200) timer = 0;
                if(p1SwapTo != -1)
                {
                    team1[active1].setIsActive(false);
                    active1 = p1SwapTo;
                    team1[active1].setIsActive(true);
                    p1SwapTo = -1;
                }
                spriteRect1.x = 0; // start at x = 0
                spriteRect1.y = 0; // start at y = 0
                spriteRect1.w = SPRITE_SIZE; // capture SPRITE_SIZE amount of pixels outward from (0, 0)
                spriteRect1.h = SPRITE_SIZE;  // capture SPRITE_SIZE amount of pixels downward from (SPRITESIZE, 0)
                
                // destination rectangle to position and size sprite rectangle
                dstrect.x = 350 - SPRITE_SIZE;
                dstrect.y = 500 - SPRITE_SIZE;
                dstrect.w = spriteRect1.w * 2;
                dstrect.h = spriteRect1.h * 2;

                // if (timer != 0)
                SDL_RenderCopy(renderer, playerOne[active1], &spriteRect1, &dstrect); // player 1 pokemon render
                if(timer != 0)
                {
                    dstrect.x = 120;
                    dstrect.y = 565;
                    dstrect.w = textArr[P1_SWAP].w;
                    dstrect.h = textArr[P1_SWAP].h;
                    SDL_RenderCopy(renderer, textArr[P1_SWAP].textTex, NULL, &dstrect);
                }
                else
                { 
                    p1Choice = "deciding";
                    // p1SwapTo = -1;
                }
            }
            if(p2Choice == "swap" && (p1Choice == "deciding"))
            {
                if(timer++ == 200) timer = 0;

                // SDL_RenderCopy(renderer, emptyMenuText, &menu, &dstrect);
                if(p2SwapTo != -1)
                {
                    team2[active2].setIsActive(false);
                    active2 = p2SwapTo;
                    team2[active2].setIsActive(true);
                    p2SwapTo = -1;
                }
                spriteRect2.x = 0; // start at x = 0
                spriteRect2.y = 0; // start at y = 0
                spriteRect2.w = SPRITE_SIZE; // capture SPRITE_SIZE amount of pixels outward from (0, 0)
                spriteRect2.h = SPRITE_SIZE;  // capture SPRITE_SIZE amount of pixels downward from (SPRITESIZE, 0)
                
                // destination rectangle to position and size sprite rectangle
                dstrect.x = 800 - SPRITE_SIZE;
                dstrect.y = (475 - SPRITE_SIZE) / 2;
                dstrect.w = spriteRect2.w * 3;
                dstrect.h = spriteRect2.h * 3;

                // if (timer != 0)
                SDL_RenderCopy(renderer, playerTwo[active2], &spriteRect1, &dstrect); // player 1 pokemon render
                if(timer != 0)
                {
                    dstrect.x = 120;
                    dstrect.y = 565;
                    dstrect.w = textArr[P2_SWAP].w;
                    dstrect.h = textArr[P2_SWAP].h;
                    SDL_RenderCopy(renderer, textArr[P2_SWAP].textTex, NULL, &dstrect);

                }
                else
                { 
                    p2Choice = "deciding";
                    p2SwapTo = -1;
                    p1Done = false;
                    p2Done = false;
                    menuState = "start";
                    std::cout << "WHoop\n";
                    // arrowXPos = 580;
                    // arrowYPos = 555;
                    // p1Choice = "fight";
                }
            }
            
        }
        else
        {
            // left text
            if(menuState == "start")
            {
                SDL_RenderCopy(renderer, menuText, &menu, &dstrect);
            }
            else
            {
                SDL_RenderCopy(renderer, emptyMenuText, &menu, &dstrect);
            }
            // arrow sprite
            arrow.x = 0;
            arrow.y = 0;
            arrow.w = 750;
            arrow.h = 750;

            dstrect.x = arrowXPos;// 580, 970
                            // 85 
            
            dstrect.y = arrowYPos; // 555, 620
                                // 545
            dstrect.w = arrow.w / 12;
            dstrect.h = arrow.h / 9;
            SDL_RenderCopy(renderer, arrowText, &arrow, &dstrect);

            // prompt text
            if(turn == "P1" && menuState == "start")
            {
                dstrect.x = 90;
                dstrect.y = 565;
                dstrect.w = textArr[PROMPT_P1].w/2;
                dstrect.h = textArr[PROMPT_P1].h/2;
                SDL_RenderCopy(renderer, textArr[PROMPT_P1].textTex, NULL, &dstrect);
            }
            else if(turn == "P2" && menuState == "start")
            {
                dstrect.x = 90;
                dstrect.y = 565;
                dstrect.w = textArr[PROMPT_P2].w/2;
                dstrect.h = textArr[PROMPT_P2].h/2;
                SDL_RenderCopy(renderer, textArr[PROMPT_P2].textTex, NULL, &dstrect);
            }
            if(menuState == "itemMenu")
            {
                // item sprites
                potion.x = 0;
                potion.y = 0;
                potion.w = 24;
                potion.h = 24;

                dstrect.x = 125;
                dstrect.y = 575;
                dstrect.w = potion.w;
                dstrect.h = potion.h;
                SDL_RenderCopy(renderer, itemText[0], &potion, &dstrect);

                fullRestore.x = 0;
                fullRestore.y = 0;
                fullRestore.w = 24;
                fullRestore.h = 24;

                dstrect.x = 325;
                dstrect.y = 575;
                dstrect.w = fullRestore.w;
                dstrect.h = fullRestore.h;
                SDL_RenderCopy(renderer, itemText[1], &fullRestore, &dstrect);

                sodaPop.x = 0;
                sodaPop.y = 0;
                sodaPop.w = 24;
                sodaPop.h = 24;

                dstrect.x = 125;
                dstrect.y = 600;
                dstrect.w = sodaPop.w;
                dstrect.h = sodaPop.h;
                SDL_RenderCopy(renderer, itemText[2], &sodaPop, &dstrect);
                if(turn == "P1")
                {
                    // item fonts
                    dstrect.x = 160;
                    dstrect.y = 575;
                    dstrect.w = textArr[POTIONS1].w / 2;
                    dstrect.h = textArr[POTIONS1].h / 2;
                    SDL_RenderCopy(renderer, textArr[POTIONS1].textTex, NULL, &dstrect);
                    
                    dstrect.x = 350;
                    dstrect.y = 575;
                    dstrect.w = textArr[FULL_RESTORES1].w / 2; 
                    dstrect.h = textArr[FULL_RESTORES1].h / 2;
                    SDL_RenderCopy(renderer, textArr[FULL_RESTORES1].textTex, NULL, &dstrect);

                    dstrect.x = 160;
                    dstrect.y = 600;
                    dstrect.w = textArr[SODA_POPS1].w / 2;
                    dstrect.h = textArr[SODA_POPS1].h / 2;
                    SDL_RenderCopy(renderer, textArr[SODA_POPS1].textTex, NULL, &dstrect);
                }
                if(turn == "P2")
                {
                    // item fonts
                    dstrect.x = 160;
                    dstrect.y = 575;
                    dstrect.w = textArr[POTIONS2].w / 2;
                    dstrect.h = textArr[POTIONS2].h / 2;
                    SDL_RenderCopy(renderer, textArr[POTIONS2].textTex, NULL, &dstrect);
                    
                    dstrect.x = 350;
                    dstrect.y = 575;
                    dstrect.w = textArr[FULL_RESTORES2].w / 2; 
                    dstrect.h = textArr[FULL_RESTORES2].h / 2;
                    SDL_RenderCopy(renderer, textArr[FULL_RESTORES2].textTex, NULL, &dstrect);

                    dstrect.x = 160;
                    dstrect.y = 600;
                    dstrect.w = textArr[SODA_POPS2].w / 2;
                    dstrect.h = textArr[SODA_POPS2].h / 2;
                    SDL_RenderCopy(renderer, textArr[SODA_POPS2].textTex, NULL, &dstrect);
                }
            }

            // IM pretty sure this works now vvvv
            if(active1 == 0 && turn == "P1" && menuState == "fightMenu") // chikorita Moves
            {   
                dstrect.x = 150;
                dstrect.y = 575;
                dstrect.w = textArr[TACKLE].w / 3;
                dstrect.h = textArr[TACKLE].h / 3;
                SDL_RenderCopy(renderer, textArr[TACKLE].textTex, NULL, &dstrect);

                dstrect.x = 350;
                dstrect.y = 575;
                dstrect.w = textArr[RAZOR_LEAF].w / 3;
                dstrect.h = textArr[RAZOR_LEAF].h / 3;
                SDL_RenderCopy(renderer, textArr[RAZOR_LEAF].textTex, NULL, &dstrect);

                dstrect.x = 150;
                dstrect.y = 625;
                dstrect.w = textArr[MAGICAL_LEAF].w / 3;
                dstrect.h = textArr[MAGICAL_LEAF].h / 3;
                SDL_RenderCopy(renderer, textArr[MAGICAL_LEAF].textTex, NULL, &dstrect);

                dstrect.x = 350;
                dstrect.y = 625;
                dstrect.w = textArr[BODY_SLAM].w / 3;
                dstrect.h = textArr[BODY_SLAM].h / 3;
                SDL_RenderCopy(renderer, textArr[BODY_SLAM].textTex, NULL, &dstrect);
                
            }
            if(active1 == 1 && turn == "P1" && menuState == "fightMenu") // Totodile Moves
            {   
                dstrect.x = 150;
                dstrect.y = 575;
                dstrect.w = textArr[SCRATCH].w / 3;
                dstrect.h = textArr[SCRATCH].h / 3;
                SDL_RenderCopy(renderer, textArr[SCRATCH].textTex, NULL, &dstrect);

                dstrect.x = 350;
                dstrect.y = 575;
                dstrect.w = textArr[WATER_GUN].w / 3;
                dstrect.h = textArr[WATER_GUN].h / 3;
                SDL_RenderCopy(renderer, textArr[WATER_GUN].textTex, NULL, &dstrect);

                dstrect.x = 150;
                dstrect.y = 625;
                dstrect.w = textArr[SLASH].w / 3;
                dstrect.h = textArr[SLASH].h / 3;
                SDL_RenderCopy(renderer, textArr[SLASH].textTex, NULL, &dstrect);

                dstrect.x = 350;
                dstrect.y = 625;
                dstrect.w = textArr[AQUA_TAIL].w / 3;
                dstrect.h = textArr[AQUA_TAIL].h / 3;
                SDL_RenderCopy(renderer, textArr[AQUA_TAIL].textTex, NULL, &dstrect);
            }
            if(active1 == 2 && turn == "P1" && menuState == "fightMenu") // Cyndaquil Moves
            {   
                dstrect.x = 150;
                dstrect.y = 575;
                dstrect.w = textArr[EMBER].w / 3;
                dstrect.h = textArr[EMBER].h / 3;
                SDL_RenderCopy(renderer, textArr[EMBER].textTex, NULL, &dstrect);

                dstrect.x = 350;
                dstrect.y = 575;
                dstrect.w = textArr[QUICK_ATTACK].w / 3;
                dstrect.h = textArr[QUICK_ATTACK].h / 3;
                SDL_RenderCopy(renderer, textArr[QUICK_ATTACK].textTex, NULL, &dstrect);

                dstrect.x = 150;
                dstrect.y = 625;
                dstrect.w = textArr[FLAME_WHEEL].w / 3;
                dstrect.h = textArr[FLAME_WHEEL].h / 3;
                SDL_RenderCopy(renderer, textArr[FLAME_WHEEL].textTex, NULL, &dstrect);

                dstrect.x = 350;
                dstrect.y = 625;
                dstrect.w = textArr[DOUBLE_EDGE].w / 3;
                dstrect.h = textArr[DOUBLE_EDGE].h / 3;
                SDL_RenderCopy(renderer, textArr[DOUBLE_EDGE].textTex, NULL, &dstrect);
            }
            if(active2 == 0 && turn == "P2" && menuState == "fightMenu") // Bulbasaur Moves
            {   
                dstrect.x = 150;
                dstrect.y = 575;
                dstrect.w = textArr[VINE_WHIP].w / 3;
                dstrect.h = textArr[VINE_WHIP].h / 3;
                SDL_RenderCopy(renderer, textArr[VINE_WHIP].textTex, NULL, &dstrect);

                dstrect.x = 350;
                dstrect.y = 575;
                dstrect.w = textArr[TAKE_DOWN].w / 3;
                dstrect.h = textArr[TAKE_DOWN].h / 3;
                SDL_RenderCopy(renderer, textArr[TAKE_DOWN].textTex, NULL, &dstrect);

                dstrect.x = 150;
                dstrect.y = 625;
                dstrect.w = textArr[POWER_WHIP].w / 3;
                dstrect.h = textArr[POWER_WHIP].h / 3;
                SDL_RenderCopy(renderer, textArr[POWER_WHIP].textTex, NULL, &dstrect);

                dstrect.x = 350;
                dstrect.y = 625;
                dstrect.w = textArr[FACADE].w / 3;
                dstrect.h = textArr[FACADE].h / 3;
                SDL_RenderCopy(renderer, textArr[FACADE].textTex, NULL, &dstrect);
            }
            if(active2 == 1 && turn == "P2" && menuState == "fightMenu") // Squirtle Moves
            {   
                dstrect.x = 150;
                dstrect.y = 575;
                dstrect.w = textArr[RAPID_SPIN].w / 3;
                dstrect.h = textArr[RAPID_SPIN].h / 3;
                SDL_RenderCopy(renderer, textArr[RAPID_SPIN].textTex, NULL, &dstrect);

                dstrect.x = 350;
                dstrect.y = 575;
                dstrect.w = textArr[WATER_PULSE].w / 3;
                dstrect.h = textArr[WATER_PULSE].h / 3;
                SDL_RenderCopy(renderer, textArr[WATER_PULSE].textTex, NULL, &dstrect);

                dstrect.x = 150;
                dstrect.y = 625;
                dstrect.w = textArr[HYDRO_PUMP].w / 3;
                dstrect.h = textArr[HYDRO_PUMP].h / 3;
                SDL_RenderCopy(renderer, textArr[HYDRO_PUMP].textTex, NULL, &dstrect);

                dstrect.x = 350;
                dstrect.y = 625;
                dstrect.w = textArr[AQUA_JET].w / 3;
                dstrect.h = textArr[AQUA_JET].h / 3;
                SDL_RenderCopy(renderer, textArr[AQUA_JET].textTex, NULL, &dstrect);
            }
            if(active2 == 2 && turn == "P2" && menuState == "fightMenu") // Charmander Moves
            {   
                dstrect.x = 150;
                dstrect.y = 575;
                dstrect.w = textArr[FIRE_FANG].w / 3;
                dstrect.h = textArr[FIRE_FANG].h / 3;
                SDL_RenderCopy(renderer, textArr[FIRE_FANG].textTex, NULL, &dstrect);

                dstrect.x = 350;
                dstrect.y = 575;
                dstrect.w = textArr[FLAMETHROWER].w / 3;
                dstrect.h = textArr[FLAMETHROWER].h / 3;
                SDL_RenderCopy(renderer, textArr[FLAMETHROWER].textTex, NULL, &dstrect);

                dstrect.x = 150;
                dstrect.y = 625;
                dstrect.w = textArr[FALSE_SWIPE].w / 3;
                dstrect.h = textArr[FALSE_SWIPE].h / 3;
                SDL_RenderCopy(renderer, textArr[FALSE_SWIPE].textTex, NULL, &dstrect);

                dstrect.x = 350;
                dstrect.y = 625;
                dstrect.w = textArr[FLARE_BLITZ].w / 3;
                dstrect.h = textArr[FLARE_BLITZ].h / 3;
                SDL_RenderCopy(renderer, textArr[FLARE_BLITZ].textTex, NULL, &dstrect);
            }
            // IM pretty sure this works now ^^^^

            // swap menu
            if(menuState == "swapMenu" && turn == "P1")
            {
                if(!team1[0].getIsActive() && !team1[0].getDead())
                {
                    dstrect.x = 350;
                    dstrect.y = 575;
                    dstrect.w = textArr[CHIKORITA_NAME].w / 1;
                    dstrect.h = textArr[CHIKORITA_NAME].h / 1;
                    SDL_RenderCopy(renderer, textArr[CHIKORITA_NAME].textTex, NULL, &dstrect);
                }
                if(!team1[1].getIsActive() && !team1[1].getDead())
                {
                    dstrect.x = 500;
                    dstrect.y = 630;
                    dstrect.w = textArr[TOTODILE_NAME].w / 1;
                    dstrect.h = textArr[TOTODILE_NAME].h / 1;
                    SDL_RenderCopy(renderer, textArr[TOTODILE_NAME].textTex, NULL, &dstrect);
                }
                if(!team1[2].getIsActive() && !team1[2].getDead())
                {
                    dstrect.x = 620;
                    dstrect.y = 575;
                    dstrect.w = textArr[CYNDAQUIL_NAME].w / 1;
                    dstrect.h = textArr[CYNDAQUIL_NAME].h / 1;
                    SDL_RenderCopy(renderer, textArr[CYNDAQUIL_NAME].textTex, NULL, &dstrect);
                }
            }
            if(menuState == "swapMenu" && turn == "P2")
            {
                if(!team2[0].getIsActive() && !team2[0].getDead())
                {
                    dstrect.x = 350;
                    dstrect.y = 575;
                    dstrect.w = textArr[BULBASAUR_NAME].w / 1;
                    dstrect.h = textArr[BULBASAUR_NAME].h / 1;
                    SDL_RenderCopy(renderer, textArr[BULBASAUR_NAME].textTex, NULL, &dstrect);
                }
                if(!team2[1].getIsActive() && !team2[1].getDead())
                {
                    dstrect.x = 500;
                    dstrect.y = 630;
                    dstrect.w = textArr[SQUIRTLE_NAME].w / 1;
                    dstrect.h = textArr[SQUIRTLE_NAME].h / 1;
                    SDL_RenderCopy(renderer, textArr[SQUIRTLE_NAME].textTex, NULL, &dstrect);
                }
                if(!team2[2].getIsActive() && !team2[2].getDead())
                {
                    dstrect.x = 620;
                    dstrect.y = 575;
                    dstrect.w = textArr[CHARMANDER_NAME].w / 1;
                    dstrect.h = textArr[CHARMANDER_NAME].h / 1;
                    SDL_RenderCopy(renderer, textArr[CHARMANDER_NAME].textTex, NULL, &dstrect);
                }
            }
        }
    }



    SDL_RenderPresent(renderer);
}

void Game::displayFPS()
{
    lastFrame = SDL_GetTicks();
    if(lastFrame >= (Game::lastTime + 1000))
    {
        Game::lastTime = lastFrame;
        fps = frameCount;
        frameCount = 0;
    }
    std::cout << fps << std::endl;
}
void Game::countFPS()
{
    frameCount++;
    timerFPS = SDL_GetTicks()-lastFrame;
    if(timerFPS <(1000/60))
    {
        SDL_Delay((1000/60)-timerFPS);
    }
}
void Game::kill()
{
    SDL_DestroyTexture(bgTexture);
    for(int i = 0; i < 3; i++)
    {
        SDL_DestroyTexture(playerOne[i]);
    }
    for(int i = 0; i < 3; i++)
    {
        SDL_DestroyTexture(playerTwo[i]);
    }

    for (int i = 0; i < 81; i++) {
        SDL_DestroyTexture(textArr[i].textTex);
    }
    for(int i = 0; i < 3; i++)
    {
        SDL_DestroyTexture(itemText[i]);
    }
    for(int i = 0; i < 3; i++)
    {
        SDL_DestroyTexture(itemFontText[i]);
    }
    SDL_DestroyTexture(backButton);
    SDL_DestroyTexture(emptyMenuText);
    SDL_DestroyTexture(moveMenu);
    SDL_DestroyTexture(menuText);
    SDL_DestroyTexture(arrowText);
    SDL_DestroyTexture(fontText);
    SDL_DestroyTexture(bgTexture);
    SDL_FreeSurface(image);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    TTF_Quit();
    IMG_Quit();
}

void Game::initFont() {
    if(font == NULL) std::cout << "Error Loading Font" << TTF_GetError() << std::endl;
    for (int i = 0; i < 81; i++) {
        image = TTF_RenderText_Blended(font, strArr[i], (SDL_Color){0, 0, 0, 255});
        // std::cout << strArr[i] << std::endl;
        textArr[i].textTex = SDL_CreateTextureFromSurface(renderer, image);
        // std::cout << textArr[i].w << std::endl;
        if (TTF_SizeText(font, strArr[i], &textArr[i].w, &textArr[i].h) != 0) {
            std::cout << "Size Fail\n";
        }  
    }
    std::cout << "ran" << std::endl;
}
// void Game::printArr(const char *arr[], int arr_size)
// {
//     for(int i = 0; i < arr_size; i++)
//     {
//         std::cout << arr[i] << std::endl;
//     }
// }
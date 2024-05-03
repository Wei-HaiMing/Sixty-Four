#include "game.hpp"
#include <cassert>
#include <iostream>


int Game::lastTime = 0;
// constructors
Game::Game(SDL_Renderer* renderer, SDL_Window* window)
{
    timer = 0;
    this->renderer = renderer;
    this->window = window;
    setRunning(true);
    setFullscreen(0);
    userInput = 0;
    active1 = 0;
    active2 = 0;
    p1Choice = "deciding";
    p2Choice = "deciding";
    menuState = "start";
    turn = "P1";
    SDL_SetWindowTitle(window, "SDL2 Window");
    SDL_ShowCursor(1);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "2");

    //setSurface(TTF_RenderText_Blended(font, "Hello", (SDL_Color){0, 0, 0, 255}));
    //fontText = SDL_CreateTextureFromSurface(renderer, image);

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
    strArr[POTIONS1] = aint.c_str();
    std::string doin = ("x" + to_string(inventory2.getFullRestores()) + " Full Restores");
    strArr[FULL_RESTORES1] = doin.c_str();
    std::string again = ("x" + std::to_string(inventory2.getSodaPops()) + " Soda Pops");
    strArr[SODA_POPS1] = again.c_str();

    tackle.setName("Tackle");
    tackle.setDamage(100);
    tackle.setType("Normal");

    razorLeaf.setName("Razor Leaf");
    razorLeaf.setDamage(55);
    razorLeaf.setType("Grass");

    magicalLeaf.setName("Magical Leaf");
    magicalLeaf.setDamage(60);
    magicalLeaf.setType("Grass");
    
    bodySlam.setName("Body Slam");
    bodySlam.setDamage(85);
    bodySlam.setType("Normal");

    ember.setName("Ember");
    ember.setDamage(40);
    ember.setType("Fire");

    quickAttack.setName("Quick Attack");
    quickAttack.setDamage(40);
    quickAttack.setType("Normal");

    flameWheel.setName("Flame Wheel");
    flameWheel.setDamage(60);
    flameWheel.setType("Fire");

    scratch.setName("Scratch");
    scratch.setDamage(40);
    scratch.setType("Normal");

    waterGun.setName("Water Gun");
    waterGun.setDamage(40);
    waterGun.setType("Water");

    aquaTail.setName("Aqua Tail");
    aquaTail.setDamage(90);
    aquaTail.setType("Water");

    slash.setName("Slash");
    slash.setDamage(70);
    slash.setType("Normal");

    vineWhip.setName("Vine Whip");
    vineWhip.setDamage(45);
    vineWhip.setType("Grass");

    waterPulse.setName("Water Pulse");
    waterPulse.setDamage(60);
    waterPulse.setType("Water");

    fireFang.setName("Fire Fang");
    fireFang.setDamage(65);
    fireFang.setType("Fire");

    flameThrower.setName("Flame Thrower");
    flameThrower.setDamage(90);
    flameThrower.setType("Fire");

    chikoritaMoves[0] = tackle;
    chikoritaMoves[1] = razorLeaf;
    chikoritaMoves[2] = magicalLeaf;
    chikoritaMoves[3] = bodySlam;

    totodileMoves[0] = scratch;
    totodileMoves[1] = waterGun;
    totodileMoves[2] = slash;
    totodileMoves[3] = aquaTail;

    cyndaquilMoves[0] = tackle;
    cyndaquilMoves[1] = ember;
    cyndaquilMoves[2] = quickAttack;
    cyndaquilMoves[3] = flameWheel;

    bulbasaurMoves[0] = tackle;
    bulbasaurMoves[1] = vineWhip;
    bulbasaurMoves[2] = razorLeaf;
    bulbasaurMoves[3] = magicalLeaf;

    squirtleMoves[0] = tackle;
    squirtleMoves[1] = waterGun;
    squirtleMoves[2] = waterPulse;
    squirtleMoves[3] = aquaTail;

    charmanderMoves[0] = scratch;
    charmanderMoves[1] = ember;
    charmanderMoves[2] = fireFang;
    charmanderMoves[3] = flameThrower;

    team1[0].setHP(294);
    team1[0].setMove(chikoritaMoves);
    team1[0].setName("Chikorita");
    team1[0].setPokeType("Grass");
    team1[0].setResistance("Water");
    team1[0].setDead(false);

    team1[1].setHP(304);
    team1[1].setMove(totodileMoves);
    team1[1].setName("Totodile");
    team1[1].setPokeType("Water");
    team1[1].setResistance("Fire");
    team1[1].setDead(false);

    team1[2].setHP(282);
    team1[2].setMove(cyndaquilMoves);
    team1[2].setName("Cyndaquil");
    team1[2].setPokeType("Fire");
    team1[2].setResistance("Grass");
    team1[2].setDead(false);

    team2[0].setHP(294);
    team2[0].setMove(bulbasaurMoves);
    team2[0].setName("Bulbasaur");
    team2[0].setPokeType("Grass");
    team2[0].setResistance("Water");
    team2[0].setDead(false);

    team2[1].setHP(292);
    team2[1].setMove(squirtleMoves);
    team2[1].setName("Squirtle");
    team2[1].setPokeType("Water");
    team2[1].setResistance("Fire");
    team2[1].setDead(false);

    team2[2].setHP(282);
    team2[2].setMove(charmanderMoves);
    team2[2].setName("Charmander");
    team2[2].setPokeType("Fire");
    team2[2].setResistance("Grass");
    team2[2].setDead(false);

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
    std::string temp10 = to_string(team1[0].getHP());
    strArr[CHIKORITA_HP] = temp10.c_str();
    std::string temp11 = to_string(team1[1].getHP());
    strArr[TOTODILE_HP] = temp11.c_str();
    std::string temp12 = to_string(team1[2].getHP());
    strArr[CYNDAQUIL_HP] = temp12.c_str();

    // setting team 2 hp
    std::string temp13 = to_string(team2[0].getHP());
    strArr[BULBASAUR_NAME] = temp13.c_str();
    std::string temp14 = to_string(team2[1].getHP());
    strArr[SQUIRTLE_NAME] = temp14.c_str();
    std::string temp15 = to_string(team2[2].getHP());
    strArr[CHARMANDER_NAME] = temp15.c_str();

    // setting types
    // temp = "Grass";
    // strArr[GRASS] = temp.c_str();
    // temp = "Water";
    // strArr[WATER] = temp.c_str();
    // temp = "Fire";
    // strArr[FIRE] = temp.c_str();
    // temp = "Normal";
    // strArr[NORMAL] = temp.c_str();

    // setting moves
    std::string temp16 = team1[0].getMove(0).getName();
    strArr[TACKLE] = temp16.c_str();
    std::string temp17 = team1[0].getMove(1).getName();
    strArr[RAZOR_LEAF] = temp17.c_str();
    std::string temp18 = team1[0].getMove(2).getName();
    strArr[MAGICAL_LEAF] = temp18.c_str();
    std::string temp19 = team1[0].getMove(3).getName();
    strArr[BODY_SLAM] = temp19.c_str();
    std::string temp20 = team1[1].getMove(0).getName();
    strArr[SCRATCH] = temp20.c_str();
    std::string temp21 = team1[1].getMove(1).getName();
    strArr[WATER_GUN] = temp21.c_str();
    std::string temp22 = team1[1].getMove(2).getName();
    strArr[SLASH] = temp22.c_str();
    std::string temp23 = team1[1].getMove(3).getName();
    strArr[AQUA_TAIL] = temp23.c_str();
    std::string temp24 = team1[2].getMove(1).getName();
    strArr[EMBER] = temp24.c_str();
    std::string temp25 = team1[2].getMove(2).getName();
    strArr[QUICK_ATTACK] = temp25.c_str();
    std::string temp26 = team1[2].getMove(3).getName();
    strArr[FLAME_WHEEL] = temp26.c_str();
    std::string temp27 = team2[0].getMove(1).getName();
    strArr[VINE_WHIP] = temp27.c_str();
    std::string temp28 = team2[1].getMove(2).getName();
    strArr[WATER_PULSE] = temp28.c_str();
    std::string temp29 = team2[2].getMove(2).getName();
    strArr[FIRE_FANG] = temp29.c_str();
    std::string temp30 = team2[2].getMove(3).getName();
    strArr[FLAMETHROWER] = temp30.c_str();

    // // how effective each move was
    // temp = "It's super effective!";
    // strArr[SUPER_EFFECTIVE] = temp.c_str();
    // temp = "It's not very effective...";
    // strArr[NOT_EFFECTIVE] = temp.c_str();

    // // prompt each player
    // temp = "Player 1, what will you do?";
    // strArr[PROMPT_P1] = temp.c_str();
    // temp = "Player 2, what will you do?";
    // strArr[PROMPT_P2] = temp.c_str();

    // Pokemon chikorita("Name", "Grass", )

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
    // for(int i = 35; i < 39; i++)
    // {
    //     std::cout << strArr[i] << std::endl;
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
// SDL_Texture* Game::getP1Text(int loc)const    // Index for array
// {
//     return playerOne[loc];
// }
// SDL_Texture* Game::getP2Text(int loc)const    // Index for array
// {
//     return playerTwo[loc];
// }
// SDL_Texture* Game::getBGTexture()const
// {
//     return bgTexture;
// }

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


void Game::update()
{
    if(timer++ == 50)
        timer = 0;
    if(fullscreen) SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
    if(!fullscreen) SDL_SetWindowFullscreen(window, 0);
    if(userInput == USER_UP) 
    {
        std::cout << "UP\n";
        userInput = 0;
    } 
    if(userInput == USER_DN) 
    {
        std::cout << "DOWN\n";
        userInput = 0;
    }
    if(userInput == USER_LT) 
    {
        std::cout << "LEFT\n";
        userInput = 0;
    }
    if(userInput == USER_RT) 
    {
        std::cout << "RIGHT\n";
        userInput = 0;
    }
    if(userInput == USER_EN) 
    {
        std::cout << "ENTER\n";
        // if(p1Choice == "fight" || p2Choice == "fight")
        // {
        //     setSurface(IMG_Load("res/empty-start-menu.png"));
        //     menuText = SDL_CreateTextureFromSurface(renderer, image);
        //     p1Choice == "deciding";
        //     p2Choice == "deciding";
        //     menuState = "fightMenu";

        // }
        // if(p1Choice == "items" || p2Choice == "items")
        // {
        //     setSurface(IMG_Load("res/empty-start-menu.png"));
        //     menuText = SDL_CreateTextureFromSurface(renderer, image);
        //     strArr[POTIONS] = ("x" + to_string(inventory1.getPotions()) + " Potions").c_str();
        //     strArr[FULL_RESTORES] = ("x" + to_string(inventory1.getFullRestores()) + " Full Restores").c_str();
        //     strArr[SODA_POPS] = ("x" + to_string(inventory1.getSodaPops()) + " Soda Pops").c_str();
        //     p1Choice == "deciding";
        //     p2Choice == "deciding";
        //     menuState = "itemMenu";
        // }

        userInput = 0;
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
    if(keystates[SDL_SCANCODE_LEFT]) userInput |= USER_LT;
    if(keystates[SDL_SCANCODE_RIGHT]) userInput |= USER_RT;
    if(keystates[SDL_SCANCODE_RETURN]) userInput |= USER_EN;
    SDL_ResetKeyboard();
}
void Game::draw()
{
    SDL_RenderCopy(renderer, bgTexture, NULL, NULL); // background render
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // colors something

    
    spriteRect1.x = 0; // start at x = 0
    spriteRect1.y = 0; // start at y = 0
    spriteRect1.w = SPRITE_SIZE; // capture SPRITE_SIZE amount of pixels outward from (0, 0)
    spriteRect1.h = SPRITE_SIZE;  // capture SPRITE_SIZE amount of pixels downward from (SPRITESIZE, 0)
    
    // destination rectangle to position and size sprite rectangle
    dstrect.x = 350 - SPRITE_SIZE;
    dstrect.y = 500 - SPRITE_SIZE;
    dstrect.w = spriteRect1.w * 2;
    dstrect.h = spriteRect1.h * 2;

    if (timer != 0)
        SDL_RenderCopy(renderer, playerOne[active1], &spriteRect1, &dstrect); // player 1 pokemon render
    
    
    
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


    // menu
    menu.x = 0;
    menu.y = 0;
    menu.w = 313 + 990;
    menu.h = 93 + 110;

    dstrect.x = 0;
    dstrect.y = 517;
    dstrect.w = menu.w;
    dstrect.h = menu.h;
    SDL_RenderCopy(renderer, menuText, &menu, &dstrect);


    // left text
    dstrect.x = 0;
    dstrect.y = 0;
    dstrect.w = textArr[0].w;
    dstrect.h = textArr[0].h;
    SDL_RenderCopy(renderer, textArr[0].textTex, NULL, &dstrect);


    // arrow sprite
    arrow.x = 0;
    arrow.y = 0;
    arrow.w = 750;
    arrow.h = 750;

    dstrect.x = 580;
    dstrect.y = 555;
    dstrect.w = arrow.w / 12;
    dstrect.h = arrow.h / 9;
    SDL_RenderCopy(renderer, arrowText, &arrow, &dstrect);
    
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
    if(active1 == 0 && turn == "P1") // chikorita
    {   
        dstrect.x = 500;
        dstrect.y = 500;
        dstrect.w = textArr[TACKLE].w;
        dstrect.h = textArr[TACKLE].h;
        SDL_RenderCopy(renderer, textArr[TACKLE].textTex, NULL, &dstrect);
    }

    // pokemon moves


    // dstrect.x = 400;
    // dstrect.y = 575;
    // dstrect.w = textArr[SODA_POPS].w / 2;
    // dstrect.h = textArr[SODA_POPS].h / 2;
    // SDL_RenderCopy(renderer, textArr[SODA_POPS].textTex, NULL, &dstrect);


    SDL_RenderPresent(renderer);
  /*  int *count, *extent;
    TTF_MeasureText(font, strArr[FULL_RESTORES], 15, extent, count);
    std::cout << "Extent: " << *extent << std::endl;
    std::cout << "Count: " << *count << std::endl;
*/
    // std::cout << strArr[FULL_RESTORES] << std::endl;
    // std::cout << to_string(inventory1.getFullRestores()).c_str() << std::endl; 
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

    for (int i = 0; i < 36; i++) {
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
    font = TTF_OpenFont("fonts/FreeSerif.ttf", 40);
    if(font == NULL) std::cout << "Error Loading Font" << TTF_GetError() << std::endl;
    
    for (int i = 0; i < 38; i++) {
        image = TTF_RenderText_Blended(font, strArr[i], (SDL_Color){0, 0, 0, 255});
        std::cout << strArr[i] << std::endl;
        textArr[i].textTex = SDL_CreateTextureFromSurface(renderer, image);
        // std::cout << textArr[i].w << std::endl;
        if (TTF_SizeText(font, strArr[i], &textArr[i].w, &textArr[i].h) != 0) {
            std::cout << "Size Fail\n";
        }  
    }
}
// void Game::printArr(const char *arr[], int arr_size)
// {
//     for(int i = 0; i < arr_size; i++)
//     {
//         std::cout << arr[i] << std::endl;
//     }
// }
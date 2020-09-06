#include "engine.h"
#include "game.h"
#include "scenes/menu.h"
#include "scenes/Level.h"
#include <SFML/Graphics.hpp>
#include <iostream>


using namespace std;

MainMenu mainmenu;
OptionMenu optmenu;
CreditsMenu crdmenu;
Level level;


int main(){
    Settings* s = new Settings();
    s->screen_width = 1920;
    s->screen_height = 1080;
    s->vsync = true;
    s->fullscreen = false;
    s->input_type = "KEYBOARD";

    Engine::Start(*s, "Last Man Standing", &mainmenu);
}
#include "menu.h"
#include "Level.h"
#include "../game.h"
#include "../components/cmp_text.h"
#include "../components/cmp_menuitem.h"
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <array>
#include <thread>
#include <vector>

using namespace std;
using namespace sf;

void MainMenu::Load() {
    cout << "Loading main menu..." << endl;
    {   
        // Get midpoint of the screen
        auto scrMiddle = Engine::GetWindowSize().x /2;
        // Make logo
        auto mainLogo = makeEntity();
        auto logoText = mainLogo->addComponent<TextComponent>("Last Man Standing");
        mainLogo->addTag("logo");
        logoText->SetFont("zombie.ttf");
        logoText->SetFontSize(80);
        // Calculate midpoint - offset
        float logoMPoint = scrMiddle - (logoText->getWidth() / 2);
        logoText->SetPosition(Vector2f(static_cast<float>(logoMPoint), 70.0f));
        // Build menu
        std::array<std::string, 5> menuItems {"New Game", "Load Game", "Options", "Credits", "Quit"};
        for(int i = 0; i < menuItems.size(); i++ ){
            auto mItem = makeEntity();
            auto mItemText = mItem->addComponent<MenuComponent>(i+1, menuItems[i]);
            mItem->addTag("menu");
            mItem->addTag(to_string(i));
        }
    }
    setLoaded(true);
}

void MainMenu::Update(const double& dt){
    // Get system events from the window:
    sf::Event event;
    while(Engine::GetWindow().pollEvent(event)){
        if(event.type == Event::Closed){
                Engine::GetWindow().close();
        }
        if(event.type == sf::Event::KeyPressed){
            if(event.key.code == sf::Keyboard::Up){
                if(_selItem > 0){
                    _selItem--;
                }
            }
            if(event.key.code == sf::Keyboard::Down){
                if (_selItem < 4){
                    _selItem++;
                }
            }
        }
    }

    // Update all menu items
    vector<shared_ptr<Entity>> mItems = ents.find("menu");
    for(auto &ent : mItems){
        // Get entity component
        auto entText = ent->get_components<MenuComponent>();
        entText[0]->IsSelected(false);
    }

    // Update the selected menu item
    vector<shared_ptr<Entity>> selItem = ents.find(to_string(_selItem));
    if(selItem[0] != nullptr){
        // Get item component
        auto selEntText = selItem[0]->get_components<MenuComponent>();
        selEntText[0]->IsSelected(true);
    }else{
        std::cout << "No Item Selected!" << std::endl;
    }

    // User selection actionables
    if(Keyboard::isKeyPressed(Keyboard::Return)){
        switch(_selItem){
            case 0 :    Engine::ChangeScene(&level);
                        break;
            case 1 :    std::cout << "Load Saved Game" << std::endl;
                        break;
            case 2 :    Engine::ChangeScene(&optmenu);
                        break;
            case 3 :    Engine::ChangeScene(&crdmenu);
                        break;
            case 4 :    Engine::GetWindow().close();
                        break;
        }
    }
    
    Scene::Update(dt);
}

void OptionMenu::Load(){
    cout << "Loading Options Menu..." << endl;
    {
        // Get midpoint of the screen
        auto scrMiddle = Engine::GetWindowSize().x /2;

        // Make logo
        auto mainLogo = makeEntity();
        auto logoText = mainLogo->addComponent<TextComponent>("Options");
        mainLogo->addTag("logo");
        logoText->SetFont("times_new_yorker.ttf");
        logoText->SetFontSize(80);

        // Calculate midpoint - offset
        float logoMPoint = scrMiddle - (logoText->getWidth() / 2);
        logoText->SetPosition(Vector2f(static_cast<float>(logoMPoint), 70.0f));
    
        // Build options menu
        // Toggle options:
        
        std::array<std::string, 3> menuItems {"Fullscreen", "Vertical Sync (Vsync)", "Use Controller"};
        for(int i = 0; i < menuItems.size(); i++ ){
            auto mItem = makeEntity();
            auto mItemText = mItem->addComponent<MenuSelectableComponent>(i+1, false ,menuItems[i]);
            mItem->addTag("menu");
            mItem->addTag(to_string(i));
        }
    }
    setLoaded(true);
}

void OptionMenu::Update(const double& dt){
     // Update all menu items
    vector<shared_ptr<Entity>> mItems = ents.find("menu");
    for(auto &ent : mItems){
        // Get entity component
        auto entText = ent->get_components<MenuSelectableComponent>();
        if(entText[0] != nullptr){
            entText[0]->IsSelected(false);
        }
    }
    
    // Update the selected menu item
    vector<shared_ptr<Entity>> selItem = ents.find(to_string(_selItem));
    if(selItem[0] != nullptr){
        // Get item component
        auto selEntText = selItem[0]->get_components<MenuSelectableComponent>();
        selEntText[0]->IsSelected(true);
    }else{
        std::cout << "No Item Selected!" << std::endl;
    }
    

    // Get system events from the window:
    sf::Event event;
    while(Engine::GetWindow().pollEvent(event)){
        if(event.type == Event::Closed){
                Engine::GetWindow().close();
        }
        if(event.type == sf::Event::KeyPressed){
            if(event.key.code == sf::Keyboard::Up){
                if(_selItem > 0){
                    _selItem--;
                }
            }
            if(event.key.code == sf::Keyboard::Down){
                if (_selItem < 2){
                    _selItem++;
                }
            }
            if(event.key.code == sf::Keyboard::Left){
                auto entText = mItems[_selItem]->get_components<MenuSelectableComponent>();
                entText[0]->SetSelectedIndex(-1);
            }
            if(event.key.code == sf::Keyboard::Right){
                auto entText = mItems[_selItem]->get_components<MenuSelectableComponent>();
                entText[0]->SetSelectedIndex(1);
            }

            if(event.key.code == sf::Keyboard::Space){
                // Apply settings
                cout << "Applying settings" << endl;
                // Create new settings instance
                Settings* s = new Settings;
                cout << "Created new settings instance" << endl;
                // Get fullscreen configuration
                auto entFullscreen = mItems[0]->get_components<MenuSelectableComponent>();
                if (entFullscreen[0]->GetSelectedIndex() == 1){
                    s->fullscreen = true;
                }else{
                    s->fullscreen = false;
                }
                cout << "Got fullscreen config" << endl;
                // Get vsync configuration
                auto entVsync = mItems[1]->get_components<MenuSelectableComponent>();
                if (entVsync[0]->GetSelectedIndex() == 1){
                    s->vsync = true;
                }else{
                    s->vsync = false;
                }
                cout << "Got vsync configuration" << endl;
                // Get controller configuration
                auto entController = mItems[2]->get_components<MenuSelectableComponent>();
                if (entController[0]->GetSelectedIndex() == 1){
                    s->input_type = "CONTROLLER";
                }else{
                    s->input_type = "KEYBOARD";
                }

                s->screen_width = 1920;
                s->screen_height = 1080;

                // Pass settings to engine to restart
                Engine::GetWindow().close();
                Engine::Start(*s, "Last Man Standing", &mainmenu);
            }
            if(event.key.code == sf::Keyboard::BackSpace){
                Engine::ChangeScene(&mainmenu);
                goto end;
            }
        }
    }
    end:
    Scene::Update(dt);
}

void CreditsMenu::Load(){
    cout << "Loading Credits Menu..." << endl;
    {
        auto txt = makeEntity();
        auto t = txt->addComponent<TextComponent>("Credits Menu...");
    }
    setLoaded(true);
}

void CreditsMenu::Update(const double& dt){
    // Get system events from the window:
    sf::Event event;
    while(Engine::GetWindow().pollEvent(event)){
        if(event.type == Event::Closed){
                Engine::GetWindow().close();
        }
        if(event.type == sf::Event::KeyPressed){
            if(event.key.code == sf::Keyboard::BackSpace){
                Engine::ChangeScene(&mainmenu);
            }
        }
    }
}
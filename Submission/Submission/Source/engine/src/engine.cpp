#include "engine.h"
#include "maths.h"
#include "system_renderer.h"
#include "system_resources.h"
#include <SFML/Graphics.hpp>
#include <future>
#include <iostream>
#include <stdexcept>

using namespace sf;
using namespace std;

Scene* Engine::_currentScene = nullptr;
std::string Engine::_gameName;

static bool loading = false;
static float loadingspinner = 0.f;
static float loadingTime;
static RenderWindow* _window;

void Loading_update(float dt, const Scene* const scn) {
    if (scn->hasLoaded()) {
        loading = false;
    }else{
        loadingspinner += 220.0f * dt;
        loadingTime += dt;
    }
}

void Loading_render(){
    static CircleShape octagon(80, 8);
    octagon.setOrigin(80, 80);
    octagon.setRotation(loadingspinner);
    octagon.setPosition(Vcast<float>(Engine::GetWindowSize()) * 0.5f);
    octagon.setFillColor(Color(255,255,255,min(255.f,40.f*loadingTime)));
    static Text t("Now Loading", *Resources::get<sf::Font>("RobotoMono-Regular.ttf"));
    t.setFillColor(Color(255, 255, 255, min(255.0f, 40.0f*loadingTime)));
    t.setPosition(Vcast<float>(Engine::GetWindowSize()) * Vector2f(0.4f,0.3f));
    Renderer::queue(&t);
    Renderer::queue(&octagon);
}

float frametimes[256] = {};
uint8_t ftc = 0;

void Engine::Update() {
    static sf::Clock clock;
    float dt = clock.restart().asSeconds();
    {
        frametimes[++ftc] = dt;
        static string winTitle = _gameName + " FPS:";
        if (ftc % 60 == 0){
            double davg = 0;
            for (const auto times : frametimes){
                davg += times;
            }
            davg = 1.0 / (davg / 255.0);
            _window->setTitle(winTitle + toStrDecPt(2, davg));
        }
    }

    if (loading){
        Loading_update(dt, _currentScene);
    }else if(_currentScene != nullptr){
        _currentScene->Update(dt);
    } 
}

void Engine::Render(RenderWindow& window){
    if(loading) {
        Loading_render();
    } else if (_currentScene != nullptr){
        _currentScene->Render();
    }

    Renderer::render();
}

void Engine::Start(Settings s, const std::string& gameName, Scene* scn){
    
    
    RenderWindow window(VideoMode(s.screen_width, s.screen_height), gameName);
    _gameName = gameName;
    _window = &window;
    Renderer::initialise(window);
    ChangeScene(scn);
    while (window.isOpen()){
        if (Keyboard::isKeyPressed(Keyboard::Escape)){
            window.close();
        }
        window.clear();
        Update();
        Render(window);
        window.display();
    }
    if (_currentScene != nullptr){
        _currentScene->Unload();
        _currentScene = nullptr;
    }
    window.close();
}

std::shared_ptr<Entity>Scene::makeEntity(){
    auto e = make_shared<Entity>(this);
    ents.list.push_back(e);
    return std::move(e);
}

void Engine::setVsync(bool b){
    _window->setVerticalSyncEnabled(b);
}

void Engine::ChangeScene(Scene* s){
    auto old = _currentScene;
    _currentScene = s;

    if (old != nullptr){
        old->Unload();
    }

    if (!s->hasLoaded()){
        loadingTime = 0;
        _currentScene->LoadAsync();
        loading = true;
    }
}

void Scene::Update(const double& dt){
    ents.update(dt);
}

void Scene::Render(){
    ents.render();
}

bool Scene::hasLoaded() const {
    { // <- why is there an additional context level specified here?
        std::lock_guard<std::mutex> lck(_loaded_mtx);
        if (_loaded_future.valid() && _loaded_future.wait_for(chrono::seconds(0)) == future_status::ready){
            _loaded_future.get();
            _loaded = true;
        }
        return _loaded;
    }
}

void Scene::setLoaded(bool b){
    {   // <- ...and here?
        std::lock_guard<std::mutex> lck(_loaded_mtx);
        _loaded = b;
    }
}

void Scene::Unload(){
    ents.list.clear();
    setLoaded(false);
}

void Scene::LoadAsync() {
    _loaded_future = std::async(&Scene::Load, this);
}

sf::Vector2u Engine::GetWindowSize(){
    return _window->getSize();
}

sf::RenderWindow& Engine::GetWindow(){
    return *_window;
}

namespace timing {
    long long now() {
        return std::chrono::high_resolution_clock::now().time_since_epoch().count();
    }
    long long last(){
        auto n = now();
        static auto then = now();
        auto dt = n - then;
        then = n;
        return dt;
    }
}

Scene::~Scene(){
    Unload();
}
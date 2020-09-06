#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <ecm.h>
#include <future>
#include <maths.h>
#include <mutex>
#include <string>

// Declare struct containing default settings
struct Settings {
    unsigned int screen_width = 640;
    unsigned int screen_height = 480;
    bool fullscreen = false;
    bool vsync = true;
    std::string input_type = "KEYBOARD";
};

class Scene {
public:
    Scene() = default;
    virtual ~Scene();
    virtual void Load() = 0;
    virtual void LoadAsync();
    virtual void Unload();
    virtual void Update(const double& dt);
    virtual void Render();
    bool hasLoaded() const;
    std::shared_ptr<Entity> makeEntity();

    EntityManager ents;

protected:
    void setLoaded(bool);

private:
    mutable bool _loaded;
    mutable std::future<void> _loaded_future;
    mutable std::mutex _loaded_mtx;
};

class Engine {
public:
    Engine() = delete;
    static void Start(Settings s, const std::string& gameName, Scene* scn);
    static void ChangeScene(Scene*);
    static sf::RenderWindow& GetWindow();
    static sf::Vector2u GetWindowSize();
    static void setVsync(bool b);

private:
    static Scene* _currentScene;
    static std::string _gameName;
    static void Update();
    static void Render(sf::RenderWindow& window);
};

namespace timing {
    long long now();    // Return time since Epoc
    long long last();   // Return time since last was last called
}
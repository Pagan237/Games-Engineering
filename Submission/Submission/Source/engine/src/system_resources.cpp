#include "system_resources.h"

namespace Resources {
    template<>
    std::shared_ptr<sf::Font> load(const std::string &name){
        auto f = std::make_shared<sf::Font>();
        if (!f->loadFromFile("res/fonts/" + name)){
            throw("Resource not found: " + name);
        };
        return f;
    };

    template<>
    std::shared_ptr<sf::Texture> load(const std::string &name){
        auto tex = std::make_shared<sf::Texture>();
        if (!tex->loadFromFile("res/img/" + name)){
            throw("Resource not found: " + name);
        };
        return tex;
    };

    #ifdef SOUND
    template<>
    std::shared_ptr<sf::SoundBuffer> load(const std::string &name){
        auto sb = std::make_shared<sf::SoundBuffer>();
        if (!sb->loadFromFile("res/sound/" + name)){
            throw("Resource not found: " + name);
        };
        return sb;
    };

    template<>
    std::shared_ptr<sf::Music> load(const std::string &name){
        auto mu = std::make_shared<sf::Music>();
        if (!mu->openFromFile("res/sound/" + name)){
            throw("Resource not found: " + name);
        };
        return mu;
    };
    #endif
}
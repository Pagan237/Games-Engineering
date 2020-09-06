#pragma once

#include <SFML/Graphics/Text.hpp>
#include <ecm.h>

class TextComponent : public Component {
public:
    TextComponent() = delete;
    ~TextComponent() override = default;

    explicit TextComponent(Entity* p, const std::string& str = "");
    void update(double dt) override;
    void render() override;

    void SetText(const std::string& str);
    void SetFont(const std::string& font);
    void SetFontSize(unsigned int fntSize);
    void SetColour(const sf::Color colour);
    void SetScale(const float scale);
    void SetPosition(const sf::Vector2f position);
    void SetRotation(const float rotation);

    float getWidth();

protected:
    std::shared_ptr<sf::Font> _font;
    std::string _string;
    sf::Text _text;
};
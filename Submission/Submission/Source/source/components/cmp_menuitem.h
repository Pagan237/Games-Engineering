#pragma once

#include <SFML/Graphics/Text.hpp>
#include <ecm.h>

class MenuComponent : public Component {
public:
    MenuComponent() = delete;
    ~MenuComponent() override = default;
    explicit MenuComponent(Entity* const p, const int index, const std::string& str = "");

    void update(double dt) override;
    void render() override;
    void SetItemName(const std::string& itemName);
    void SetFont(const std::string& font);
    void IsSelected(bool isSel);
    void SetIndexPosition(const int index);

protected:
    std::string _itemName;
    sf::Text _itemNameText;
    std::shared_ptr<sf::Font> _font;
    bool _isSelected = false;
    const int _index;
};

class MenuSelectableComponent : public MenuComponent {
public:
    MenuSelectableComponent() = delete;
    ~MenuSelectableComponent() override = default;
    explicit MenuSelectableComponent(Entity* const p, const int mnuIndex, const bool selIndex, const std::string& str = "");
    //explicit MenuSelectableComponent(Entity* const p, const int mnuIndex, const int selIndex, std::vector<std::string> mnuOptns, const std::string& str = "");

    void update(double dt) override;
    void render() override;
    void SetSelectedIndex(const int increment);
    int GetSelectedIndex();
    std::string& GetSelectedIndexText();

    void SetMenuPosition(const int index);

protected:
    int _selectedIndex;
    std::vector<std::string> _selectRange;
    sf::Text _itemStatusText;
};

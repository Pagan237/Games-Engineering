#include "cmp_menuitem.h"
#include "engine.h"
#include <system_renderer.h>
#include <system_resources.h>
#include <iostream>
#include <memory>
#include <vector>

void MenuComponent::update(double dt) {
    
    // Set colour depending on selection status
    if(_isSelected){
        _itemNameText.setFillColor(sf::Color::Red);
    }else{
        _itemNameText.setFillColor(sf::Color::White);
    }
}

void MenuComponent::render() {
    Renderer::queue(&_itemNameText);
}

MenuComponent::MenuComponent(Entity* const p, const int index, const std::string& str) : Component(p), _index(index), _itemName(str){
    SetItemName(str);
    SetIndexPosition(index);
}

void MenuComponent::SetItemName(const std::string& name){
    _itemNameText.setString(name);
    _font = Resources::get<sf::Font>("times_new_yorker.ttf");
    _itemNameText.setFont(*_font);
}

void MenuComponent::SetFont(const std::string& font){
    _font = Resources::get<sf::Font>(font);
    _itemNameText.setFont(*_font);
}

void MenuComponent::IsSelected(bool selStat){
    _isSelected = selStat;
}

void MenuComponent::SetIndexPosition(const int index){
    // Get midpoint of the screen
    auto scrMiddle = Engine::GetWindowSize().x /2;

    // Calculate midpoint - offset
    float mitemMPoint = scrMiddle - (_itemNameText.getLocalBounds().width / 2);
    _itemNameText.setPosition(sf::Vector2f(static_cast<float>(mitemMPoint), 170.0f + (index*30.f)));
}

// =====================================================================================
// Selectable Menu Component
void MenuSelectableComponent::SetSelectedIndex(const int increment){
    _selectedIndex += increment;
    std::cout << (_selectRange.size() -1) << std::endl;
    if (_selectedIndex > (_selectRange.size() -1)){
        _selectedIndex = 0;
    }else if(_selectedIndex < 0){
        _selectedIndex = (_selectRange.size() -1);
    }
}

void MenuSelectableComponent::SetMenuPosition(const int index){
    // Get midpoint of the screen
    auto scrWidth = Engine::GetWindowSize().x;
    auto scrCol1 = scrWidth /3;
    auto scrCol2 = scrWidth - scrCol1;

    // Set text element positions
    _itemNameText.setPosition(sf::Vector2f(static_cast<float>(scrCol1), 170.0f + (index*30.f)));
    _itemStatusText.setPosition(sf::Vector2f(static_cast<float>(scrCol2), 170.0f + (index*30.f)));
}

void MenuSelectableComponent::update(double dt) { //<--- traced to here
    // Set status text depending on stored status
    _itemStatusText.setString(_selectRange[_selectedIndex]);

    // Set colour depending on selection status
    if(_isSelected){
        _itemNameText.setFillColor(sf::Color::Red);
        _itemStatusText.setFillColor(sf::Color::Red);
    }else{
        _itemNameText.setFillColor(sf::Color::White);
        _itemStatusText.setFillColor(sf::Color::White);
    }
}

void MenuSelectableComponent::render() {
    Renderer::queue(&_itemNameText);
    Renderer::queue(&_itemStatusText);
}

int MenuSelectableComponent::GetSelectedIndex(){
    return _selectedIndex;
}

MenuSelectableComponent::MenuSelectableComponent(Entity* const p, const int mnuIndex, const bool status, const std::string& str) : MenuComponent(p, mnuIndex, str){
    _selectRange.push_back("OFF");
    _selectRange.push_back("ON");
    
    if(status){
        _itemStatusText.setString("ON");
        _selectedIndex = 1;
    }else{
        _itemStatusText.setString("OFF");
        _selectedIndex = 0;
    }

    _itemNameText.setString(str);
    
    _font = Resources::get<sf::Font>("times_new_yorker.ttf");
    _itemStatusText.setFont(*_font);
    _itemNameText.setFont(*_font);

    MenuComponent::SetItemName(_itemName);
    SetMenuPosition(mnuIndex);
}

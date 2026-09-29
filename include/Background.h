#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>

class Background
{
private:
    sf::Texture background_texture_;
    sf::Sprite* background_sprite;

    void setTexture(std::string _image_dir);
    void setSprite();

public:
    void renderBackground(sf::RenderTarget& _target);
	void setBackgroundPosition(float _x, float _y);
	void setBackgroundScale(float _scale_x, float _scale_y);
    void setBackgroundOrigin();
	sf::FloatRect getBackgroundGlobalBounds() const;
    Background(std::string _image_dir);
    ~Background();
};

#endif
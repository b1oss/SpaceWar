#include "Background.h"

void Background::setTexture(std::string _image_dir)
{
    // assets\images\maps\245.png
    if (!this->background_texture_.loadFromFile(_image_dir))
        printf("ERROR::BACKGROUND::INITTEXTURE::Could not load texture file.\n");
}

void Background::setSprite()
{
    this->background_sprite = new sf::Sprite(this->background_texture_);
    this->background_sprite->setScale({ 1.5f, 1.5f });
}

void Background::renderBackground(sf::RenderTarget &_target)
{
    _target.draw(*this->background_sprite);
}

void Background::setBackgroundPosition(float _x, float _y)
{
    this->background_sprite->setPosition({ _x, _y });
}

void Background::setBackgroundScale(float _scale_x, float _scale_y)
{
	this->background_sprite->setScale({ _scale_x, _scale_y });
}

void Background::setBackgroundOrigin()
{
	this->background_sprite->setOrigin(this->background_sprite->getLocalBounds().getCenter());
}

sf::FloatRect Background::getBackgroundGlobalBounds() const
{
	return this->background_sprite->getGlobalBounds();
}

Background::Background(std::string _image_dir)
{
    this->setTexture(_image_dir);
    this->setSprite();
}

Background::~Background()
{
    delete this->background_sprite;
    this->background_sprite = nullptr;
}

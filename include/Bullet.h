#ifndef BULLET_H
#define BULLET_H

#include <iostream>
#include <cmath>
#include <SFML/Graphics.hpp>

class Bullet
{
private:
    // sf::Texture* bullet_texture_;
    sf::Sprite* bullet_sprite_;
    sf::Vector2f bullet_direction_;

    float bullet_speed_;
/*     void setTexture();
    void setSprite(); */
public:
    Bullet();
    Bullet(sf::Texture* _texture, float _position_x, float _position_y, float _angle_degrees);
    const sf::FloatRect getBulletBounds() const;
    ~Bullet();
    void bulletUpdate(const float _delta_time);
    void bulletRender(sf::RenderTarget& _target);
};

#endif
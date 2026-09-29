#ifndef ENEMY_H
#define ENEMY_H

#include <iostream>
#include <random>
#include <vector>
#include <algorithm>
#include <SFML/Graphics.hpp>

class Enemy
{
private:
    sf::CircleShape shape_;
    sf::Texture enemy_texture_;
    sf::Sprite* enemy_sprite_;
    sf::Vector2f direction;

    int hp_;
    int damage_;
    int points_;
    float enemy_speed;

    bool is_alive_;

    void initVariables();
    void initTexture();
    void initSprite(float _pos_x, float _pos_y);
    void initShape(float _pos_x, float _pos_y);

public:
    sf::FloatRect getShapeBounds() const;
    void renderEnemy(sf::RenderTarget& _target);
    void update(float _delta_time);
    void setEnemyShipIsAlive();
    bool getEnemyShipIsAlive() const;
    Enemy(float _pos_x, float _pos_y, sf::Vector2f _direction);
    ~Enemy();
};

#endif
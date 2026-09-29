#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <SFML/Graphics.hpp>

class Player
{
private:
    sf::Sprite* player_sprite_;
    sf::Texture player_texture_;
    
    // Ship Shape
	sf::ConvexShape ship_shape_;

    int health_;

    float movement_speed_;
    float attack_cooldown_;
    float attack_max_cooldown_;

    bool is_player_alive_;

    // Private Functions
	void setPlayerShape();
    void initTexture();
    void initSprite();
    void initVariables();
public:
    Player(/* args */);
    virtual ~Player();

    void setPlayerPosition(const sf::Vector2f _pos);
    // void setPlayerIsAlive(bool _is_player_alive);
    void setPlayerIsAlive();
    bool getPlayerIsAlive() const;
    const sf::Vector2f getPlayerPosition() const;
    const sf::FloatRect getBounds() const;
    void playerMovement(const float _dir_x, const float _dir_y, const float _delta_time);
	void setRotation(const float _angle);
    const sf::Vector2f getPlayerOrigin();
    bool canAttack();
    void updateAttack();
    void update();
    void render(sf::RenderTarget& target);
};

#endif
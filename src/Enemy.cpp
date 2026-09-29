#include "Enemy.h"

void Enemy::initVariables()
{
    this->hp_ = 10;
    this->damage_ = 1;
    this->points_ = 5;
    this->enemy_speed = 150.f;
    this->is_alive_ = true;
}

void Enemy::initTexture()
{
    // assets\images\enemies\alien_blue.png
    if (!this->enemy_texture_.loadFromFile("assets/images/enemies/alien_blue.png"))
        printf("ERROR::ENEMY::INITTEXTURE::Could not load texture file.\n");
}

void Enemy::initSprite(float _pos_x, float _pos_y)
{
    this->enemy_sprite_ = new sf::Sprite(enemy_texture_);
    enemy_sprite_->setPosition({_pos_x, _pos_y});
    enemy_sprite_->setScale({4.f, 4.f});
    // enemy_sprite_->setOrigin({200.f, 200.f});
}

void Enemy::initShape(float _pos_x, float _pos_y)
{
    this->shape_.setRadius(20.f);
    this->shape_.setPosition({_pos_x, _pos_y});
    this->shape_.setScale({1.6f, 1.f});
}

sf::FloatRect Enemy::getShapeBounds() const
{
    return this->shape_.getGlobalBounds();
}

void Enemy::renderEnemy(sf::RenderTarget& _target)
{
    //_target.draw(this->shape_);
    _target.draw(*this->enemy_sprite_);
}

void Enemy::update(float _delta_time)
{
    this->enemy_sprite_->move({enemy_speed * _delta_time * this->direction.x, enemy_speed * _delta_time * this->direction.y});
    this->shape_.move({enemy_speed * _delta_time * this->direction.x, enemy_speed * _delta_time * this->direction.y});
}

void Enemy::setEnemyShipIsAlive()
{
    this->is_alive_ = false;
}

bool Enemy::getEnemyShipIsAlive() const
{
    return this->is_alive_;
}

Enemy::Enemy(float _pos_x, float _pos_y, sf::Vector2f _direction)
{
    this->direction = _direction;
    initVariables();
    initTexture();
    initSprite(_pos_x, _pos_y);
    initShape(_pos_x, _pos_y);
}

Enemy::~Enemy()
{
    delete this->enemy_sprite_;
    this->enemy_sprite_ = nullptr;
}

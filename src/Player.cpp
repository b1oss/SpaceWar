#include "Player.h"

void Player::setPlayerShape()
{
	this->ship_shape_.setPointCount(6);

	this->ship_shape_.setPoint(0, sf::Vector2f(1.f, 4.f));
	this->ship_shape_.setPoint(1, sf::Vector2f(15.f, 4.f));
	this->ship_shape_.setPoint(2, sf::Vector2f(15.f, 10.f));
	this->ship_shape_.setPoint(3, sf::Vector2f(10.f, 14.f));
	this->ship_shape_.setPoint(4, sf::Vector2f(7.f, 14.f));
	this->ship_shape_.setPoint(5, sf::Vector2f(1.f, 10.f));
	this->ship_shape_.setScale({ 3.5f, 3.5f });
}

void Player::initTexture()
{
    // assets\images\ships\purple.png
    if (!this->player_texture_.loadFromFile("assets/images/ships/purple.png"))
        printf("ERROR::PLAYER::INITTEXTURE::Could not load texture file.\n");
}

void Player::initSprite()
{
    this->player_sprite_ = new sf::Sprite(this->player_texture_);
    this->player_sprite_->setPosition({550.f, 530.f});
    this->player_sprite_->setScale({4.f, 4.f});
	this->ship_shape_.setOrigin(this->player_sprite_->getLocalBounds().getCenter());
    this->player_sprite_->setOrigin({this->player_sprite_->getLocalBounds().getCenter()});
}

void Player::initVariables()
{
    this->health_ = 3;
	this->is_player_alive_ = true;
    this->movement_speed_ = 300.f;
    this->attack_max_cooldown_ = 10.f;
    this->attack_cooldown_ = attack_max_cooldown_;
}
// �and� 
Player::Player()
{
	this->setPlayerShape();
    this->initVariables();
    this->initTexture();
    this->initSprite();
}

Player::~Player()
{
    delete this->player_sprite_;
    this->player_sprite_ = nullptr;
}

void Player::setPlayerPosition(const sf::Vector2f _pos)
{
    this->ship_shape_.setPosition(_pos);
    this->player_sprite_->setPosition(_pos);
}

void Player::setPlayerIsAlive()
{
    // this->health_ -= 1;
    if (this->health_ -= 1 > 0)
        this->is_player_alive_ = true;
    
    else 
        this->is_player_alive_ = false;
}

bool Player::getPlayerIsAlive() const
{
    return this->is_player_alive_;
}

const sf::Vector2f Player::getPlayerPosition() const
{
    return this->player_sprite_->getPosition();
}

const sf::FloatRect Player::getBounds() const
{
    //return this->player_sprite_->getGlobalBounds();
	return this->ship_shape_.getGlobalBounds();
}

void Player::playerMovement(const float _dir_x, const float _dir_y, const float _delta_time)
{
	this->ship_shape_.move({ this->movement_speed_ * _delta_time * _dir_x, this->movement_speed_ * _delta_time * _dir_y });
    this->player_sprite_->move({this->movement_speed_ * _delta_time * _dir_x, this->movement_speed_ * _delta_time * _dir_y});
}

void Player::setRotation(const float _angle)
{
	this->ship_shape_.setRotation(sf::degrees(_angle));
    this->player_sprite_->setRotation(sf::degrees(_angle));
}

const sf::Vector2f Player::getPlayerOrigin()
{
    return player_sprite_->getOrigin();
}

bool Player::canAttack()
{
    if (this->attack_cooldown_ >= this->attack_max_cooldown_)
    {
        this->attack_cooldown_ = 0.f;
        return true;
    }

    return false;
}

void Player::updateAttack()
{
    if (this->attack_cooldown_ < this->attack_max_cooldown_)
        this->attack_cooldown_ += 1;
}

void Player::update()
{
    this->updateAttack();
}

void Player::render(sf::RenderTarget &target)
{
	//target.draw(this->ship_shape_);
    target.draw(*this->player_sprite_);
}
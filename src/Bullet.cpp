#include "Bullet.h"

Bullet::Bullet() { }

Bullet::Bullet(sf::Texture* _texture, float _position_x, float _position_y, float _angle_degrees)
{
    this->bullet_sprite_ = new sf::Sprite(*_texture);
    
    this->bullet_sprite_->setTextureRect(sf::IntRect({6,5}, {3,5}));
    this->bullet_sprite_->setScale({ 4.f, 4.f });
    sf::FloatRect sprite_bounds = this->bullet_sprite_->getLocalBounds();
    this->bullet_sprite_->setOrigin(sf::Vector2f{ sprite_bounds.size.x / 2.f, sprite_bounds.size.y / 2.f });
    this->bullet_sprite_->setPosition({_position_x, _position_y});
	this->bullet_sprite_->setRotation(sf::degrees(_angle_degrees + 90.f));
    
    float convert_to_radians = _angle_degrees * (3.14159265f / 180.f);
    this->bullet_direction_ = sf::Vector2f(std::cos(convert_to_radians), std::sin(convert_to_radians));
    this->bullet_speed_ = 650.f;
}

const sf::FloatRect Bullet::getBulletBounds() const
{
    return this->bullet_sprite_->getGlobalBounds();
}

Bullet::~Bullet()
{
    delete this->bullet_sprite_;
    this->bullet_sprite_ = nullptr;
}

void Bullet::bulletUpdate(const float _delta_time)
{
    this->bullet_sprite_->move(this->bullet_speed_ * this->bullet_direction_ * _delta_time);
}

void Bullet::bulletRender(sf::RenderTarget &_target)
{
    _target.draw(*this->bullet_sprite_);
}

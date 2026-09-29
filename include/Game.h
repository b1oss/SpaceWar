#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <thread>
#include <string>
#include <vector>
#include <chrono>
#include <cmath>
#include <sstream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Player.h"
#include "Background.h"
#include "Bullet.h"
#include "Enemy.h"

class Game
{
private:
    // window
    sf::RenderWindow* window_;
    sf::VideoMode* video_mode_;
    sf::Vector2u window_size_;
    sf::Clock clock_;
	
    float fps_;
    float delta_time_;
    
    // Fonts
    sf::Font font_;
    sf::Text* enemies_killed_text_;
    sf::Text* points_;
    unsigned counting_enemies_killed_;

	sf::Text* play_text_;
	sf::Text* exit_text_;
    sf::Text* paused_game_text_;
    sf::Text* continue_game_text_;
	sf::Text* exit_game_text_;
    sf::Text* game_over_text_;
    
	bool main_menu_;
	bool play_selected_;
	bool continue_selected_;
	bool in_game_;
    bool paused_game_;
    bool game_over_;

    // Sounds
	sf::SoundBuffer shoot_buffer_;
	sf::Sound* shoot_sound_;
	sf::SoundBuffer explotion_buffer_;
	sf::Sound* explotion_sound_;
    sf::SoundBuffer player_explotes_buffer;
    sf::Sound* player_explotes_sound;
    sf::SoundBuffer background_music_buffer_;
    sf::Sound* background_music_;

    Player* player_;

    Background* background_;
	Background* background_menu_;
	Background* title_main_screen_;
    Background* pause_blur_screen_;

    // Bullets
    sf::Texture* bullet_texture_;
    std::vector<Bullet*> bullets_;
    std::thread bullet_cooldown_;

    std::vector<Enemy*> enemies_;
    float spawn_enemies;
    float spawn_max_enemies;

	// Mouse positions
    sf::Vector2f current_mouse_position_;
    sf::Vector2f last_mouse_position_;
    float angle_;

    // Private functions
    void initGameVariables();
    void initWindow();
    void initTextures();
    void setDeltaTime();
	void initBackgrounds();
	void initMainMenuTextOptions();
	void initPauseMenuTextOptions();
    void mainMenuRender();
	void mainMenuUpdate();
    void pauseMenuRender();
    void pauseMenuUpdate();

    void inGameUpdate();
	void inGameRender();
    void playerMovement();
	// void pauseGameRender();
    void initGameOverText();
    void gameOverRender();
    void updateEnemies();
    void bulletsCollidingEnemies();
    void playerCollidingAllien();
    void updateBullets();
    void initEnemies();
    void initFonts();
    void initBusfferSounds();
	void setSounds();
	sf::Vector2f getMousePosition() const;
    void setCurrentMousePosition();
    float getAngle();
	void updateShipRotation();
public:
    Game();
    void initPlayer();
    void playerCollidingWindow();
    void updateGUI();
    void renderGUI();
    void run();
    bool runningGame() const;
    void pollEvent();
    void update();
    void render();
    ~Game();
};
#endif
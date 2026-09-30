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

enum Game_Status
{
    MainMenu,
    InGame,
    Paused,
    GameOver
};

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

	bool play_selected_;
	bool continue_selected_;

    Game_Status game_status;

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


    // Main Menu
    void initMainMenu();
    void initMainMenuBackground();
    void initTitle();
	void initMainMenuTextOptions();
    void mainMenuRender();
	void mainMenuUpdate();

    void initWindow();
    
    
    // Pause Menu
    void initPauseMenu();
	void initPauseMenuTextOptions();
    void pauseMenuRender();
    void pauseMenuUpdate();
    void pauseBackground();
    
    
    // In Game
    void initGameVariables();
    void initInGame();
    void initTextures();
	void initBackgrounds();
    void initGameOverText();
    void inGameUpdate();
    void initEnemies();
    void initFonts();
    void initBusfferSounds();
	void inGameRender();
	void setSounds();
    float getAngle();
    void playerMovement();
    void updateEnemies();
    void bulletsCollidingEnemies();
    void playerCollidingAllien();
    void updateBullets();
	void updateShipRotation();
    void updateGUI();

    // Game Over
    void gameOverRender();
    
    // Setters & Getters Private
    void setGameStatus(Game_Status _game_status);
    Game_Status getGameStatus() const;
    void setDeltaTime();
	sf::Vector2f getMousePosition() const;
    void setCurrentMousePosition();

public:
    Game();
    ~Game();

    void initPlayer();
    void playerCollidingWindow();

    void update();

    void run();
    bool runningGame() const;

    void pollEvent();

    void render();
    void renderGUI();
};
#endif
#include "Game.h"

void Game::initGameVariables()
{
    this->counting_enemies_killed_ = 0;
}

void Game::initWindow()
{
    this->video_mode_ = new sf::VideoMode({this->window_size_.x, this->window_size_.y});
    this->window_ = new sf::RenderWindow(*this->video_mode_, "Swaglords Of Space", sf::Style::Close | sf::Style::Titlebar, sf::State::Fullscreen);
    this->window_->setFramerateLimit(60);
}

void Game::initMainMenu()
{
    this->play_selected_ = true;
    this->continue_selected_ = true;
    initMainMenuBackground();
    initTitle();
    initMainMenuTextOptions();
}

void Game::initMainMenuBackground()
{
    // assets/images/maps/Nebula.jpg
	this->background_menu_ = new Background("assets/images/maps/Nebula.jpg");
	this->background_menu_->setBackgroundPosition(0.f, 0.f);
	this->background_menu_->setBackgroundScale(1.5f, 1.5f);
}

void Game::initTitle()
{
    // assets/images/maps/Title.png
	this->title_main_screen_ = new Background("assets/images/maps/Title.png");
	this->title_main_screen_->setBackgroundOrigin();
	this->title_main_screen_->setBackgroundScale(0.9f, 0.9f);
    this->title_main_screen_->setBackgroundPosition((static_cast<float>(this->window_->getSize().x) / 2.f) + (title_main_screen_->getBackgroundGlobalBounds().getCenter().x / 2.f), 
                                                    (static_cast<float>(this->window_->getSize().y) / 3.f) - (title_main_screen_->getBackgroundGlobalBounds().getCenter().y / 2.f));
}

void Game::initInGame()
{
    initGameVariables();
    std::cout << "Game Initiated Correctly\n";
    initBackgrounds();
    initTextures();
    initBusfferSounds();
    setSounds();
    initPlayer();
    initEnemies();
}

void Game::initTextures()
{
    // assets\images\laser\projectiles.png
    this->bullet_texture_ = new sf::Texture("assets/images/laser/projectiles.png");
}

void Game::setDeltaTime()
{
    this->delta_time_ = clock_.getElapsedTime().asSeconds();
    if (delta_time_ >= 1.f / 60)
    {
        clock_.restart();
        this->fps_ = 1.f / delta_time_;

        this->update();
        this->render();
    }
}

void Game::initBackgrounds()
{
	// assets/images/maps/245.png
	this->background_ = new Background("assets/images/maps/245.png");
	this->background_->setBackgroundPosition(0.f, 0.f);
	this->background_->setBackgroundScale(1.5f, 1.5f);
}

void Game::initMainMenuTextOptions()
{
	this->play_text_ = new sf::Text(this->font_);
	this->play_text_->setString("Play");
    this->play_text_->setFillColor(sf::Color(255, 204, 0));
	this->play_text_->setCharacterSize(80);
	this->play_text_->setOrigin(this->play_text_->getLocalBounds().getCenter());
    this->play_text_->setPosition({ static_cast<float>(this->window_->getSize().x) / 2.f + play_text_->getGlobalBounds().getCenter().x / 2.f,
                                    static_cast<float>(this->window_->getSize().y) - (static_cast<float>(this->window_->getSize().y) / 3.f) });

	this->exit_text_ = new sf::Text(this->font_);
	this->exit_text_->setString("Exit");
	this->exit_text_->setFillColor(sf::Color(255, 255, 255));
	this->exit_text_->setCharacterSize(80);
    this->exit_text_->setOrigin(this->exit_text_->getLocalBounds().getCenter());
    this->exit_text_->setPosition({ static_cast<float>(this->window_->getSize().x) / 2.f + exit_text_->getGlobalBounds().getCenter().x / 2.f,
                                    this->play_text_->getPosition().y + (static_cast<float>(this->exit_text_->getCharacterSize())) });
}

void Game::initPauseMenuTextOptions()
{
    this->paused_game_text_ = new sf::Text(this->font_);
    this->paused_game_text_->setString("Pause Menu");
    this->paused_game_text_->setFillColor(sf::Color(255, 255, 250));
    this->paused_game_text_->setCharacterSize(120);
    this->paused_game_text_->setOrigin(this->paused_game_text_->getLocalBounds().getCenter());
    this->paused_game_text_->setPosition({ static_cast<float>(this->window_->getSize().x) / 2.f + this->paused_game_text_->getGlobalBounds().getCenter().x / 2.f, 
                                            static_cast<float>(this->paused_game_text_->getCharacterSize()) });

	this->continue_game_text_ = new sf::Text(this->font_);
	this->continue_game_text_->setString("Continue");
    this->continue_game_text_->setFillColor(sf::Color(255, 204, 0));
	this->continue_game_text_->setCharacterSize(80);
	this->continue_game_text_->setOrigin(this->continue_game_text_->getLocalBounds().getCenter());
	this->continue_game_text_->setPosition({ static_cast<float>(this->window_->getSize().x) / 2.f + continue_game_text_->getGlobalBounds().getCenter().x / 2.f,
                                            static_cast<float>(this->window_->getSize().y) / 2.f - continue_game_text_->getGlobalBounds().size.y - 20});
    
	this->exit_game_text_ = new sf::Text(this->font_);
	this->exit_game_text_->setString("Exit");
    this->exit_game_text_->setFillColor(sf::Color(255, 255, 255));
	this->exit_game_text_->setCharacterSize(80);
	this->exit_game_text_->setOrigin(this->exit_game_text_->getLocalBounds().getCenter());
	this->exit_game_text_->setPosition({ static_cast<float>(this->window_->getSize().x) / 2.f + exit_game_text_->getGlobalBounds().getCenter().x / 2.f, 
                                        static_cast<float>(this->window_->getSize().y) / 2.f + exit_game_text_->getGlobalBounds().size.y + 20 });
}

void Game::mainMenuRender()
{
    this->background_menu_->renderBackground(*this->window_);
    this->title_main_screen_->renderBackground(*this->window_);
	this->window_->draw(*this->play_text_);
	this->window_->draw(*this->exit_text_);
}

void Game::mainMenuUpdate()
{
    if (getGameStatus() == MainMenu && sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Up) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Down))
    {
        if (getGameStatus() != InGame && play_text_ && exit_text_)
        {
            play_selected_ = !play_selected_;
            if (play_selected_)
            {
                play_text_->setFillColor(sf::Color(255, 204, 0));
                exit_text_->setFillColor(sf::Color(255, 255, 255));
            }
            else
            {
                play_text_->setFillColor(sf::Color(255, 255, 255));
				exit_text_->setFillColor(sf::Color(255, 204, 0));
            }
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Enter))
    {
        if (getGameStatus() == MainMenu && play_selected_) 
        {
			setGameStatus(InGame);
            initInGame();
        }
        else if (getGameStatus() == MainMenu && !play_selected_)
        {
            this->window_->close();
        }
    }
}

void Game::initPauseMenu()
{
    pauseBackground();
    initPauseMenuTextOptions();
    std::cout << "Pause Menu Initialized correctly\n";
}

void Game::pauseMenuRender()
{
    this->background_music_->pause();
    this->pause_blur_screen_->renderBackground(*this->window_);
    this->window_->draw(*this->paused_game_text_);
    this->window_->draw(*this->continue_game_text_);
    this->window_->draw(*this->exit_game_text_);
}

void Game::pauseMenuUpdate()
{
    if (getGameStatus() == Paused && sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Up) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Down))
    {
        if (getGameStatus() != InGame)
        {
            continue_selected_ = !continue_selected_;
            if (continue_selected_)
            {
                this->exit_game_text_->setFillColor(sf::Color(255, 255, 255));
                this->continue_game_text_->setFillColor(sf::Color(255, 204, 0));
            }
            else
            {
                this->exit_game_text_->setFillColor(sf::Color(255, 204, 0));
                this->continue_game_text_->setFillColor(sf::Color(255, 255, 255));
            }
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Enter))
    {
        if (getGameStatus() == Paused && continue_selected_)
        {
            setGameStatus(InGame);
        }
        else if (getGameStatus() == Paused && !continue_selected_)
        {
            this->window_->close();
        }
    }
}

void Game::pauseBackground()
{
    // assets/images/maps/pause_screen.png
    this->pause_blur_screen_ = new Background("assets/images/maps/pause_screen.png");
    this->pause_blur_screen_->setBackgroundPosition(0.f, 0.f);
}

void Game::setGameStatus(Game_Status _game_status)
{
    this->game_status = _game_status;
}

Game_Status Game::getGameStatus() const
{
    return game_status;
}

void Game::inGameUpdate()
{
    this->playerMovement();
    this->player_->update();
    this->updateShipRotation();
    this->playerCollidingWindow();
    this->playerCollidingAllien();
    this->updateBullets();
    this->updateEnemies();
    this->bulletsCollidingEnemies();
    this->updateGUI();
}

void Game::inGameRender()
{
    if (this->background_music_ && this->background_music_->getStatus() != sf::SoundSource::Status::Playing)
    {
        this->background_music_->play();
    }

    if (this->background_)
        this->background_->renderBackground(*this->window_);

    for (auto* bullet : bullets_)
    {
        bullet->bulletRender(*this->window_);
    }

    this->player_->render(*this->window_);

    for (auto& enemy : enemies_)
    {
        enemy->renderEnemy(*this->window_);
    }

    this->renderGUI();
}

void Game::playerMovement()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::A))
        this->player_->playerMovement(-1.f, 0.f, this->delta_time_);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::D))
        this->player_->playerMovement(1.f, 0.f, this->delta_time_);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::S))
        this->player_->playerMovement(0.f, 1.f, this->delta_time_);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::W))
        this->player_->playerMovement(0.f, -1.f, this->delta_time_);
    
    // Shooting
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && this->player_->canAttack())
    {
        this->bullets_.push_back(new Bullet(this->bullet_texture_, player_->getBounds().getCenter().x, player_->getBounds().getCenter().y, angle_));
		this->shoot_sound_->play();
    }
}

// TODO: Implement game over
void Game::initGameOverText()
{
    this->game_over_text_ = new sf::Text(this->font_);
    this->game_over_text_->setString("Game Over");
    this->game_over_text_->setFillColor(sf::Color(255, 204, 0, 222));
    this->game_over_text_->setCharacterSize(300);
    this->game_over_text_->setOrigin(game_over_text_->getLocalBounds().getCenter());
    this->game_over_text_->setPosition({static_cast<float>(this->window_->getSize().x) / 2.f + (this->game_over_text_->getGlobalBounds().getCenter().x / 2.f),
                                        static_cast<float>(this->window_->getSize().y) / 2.f + (this->game_over_text_->getGlobalBounds().getCenter().y / 2.f) });
    std::cout << "Game Over Initialized Correclty\n";
}

void Game::gameOverRender()
{
    this->background_music_->stop();
    this->background_->renderBackground(*this->window_);
    this->window_->draw(*this->game_over_text_);
}

void Game::updateEnemies()
{
    this->spawn_enemies += 0.5f;
    if (this->spawn_enemies >= this->spawn_max_enemies)
    {
        std::random_device device;
        std::mt19937 generator(device());
        std::uniform_int_distribution<> dist(0, 7);
        int direction = dist(generator);
        sf::Vector2f send_direction;
        
        switch (direction)
        {
            case 0:
                send_direction = {0.f, 1.f};
                break;
            case 1:
                send_direction = {1.f, 1.f};
                break;
            case 2:
                send_direction = {1.f, 0.f};
                break;
            case 3:
                send_direction = {1.f, -1.f};
                break;
            case 4:
                send_direction = {0.f, -1.f};
                break;
            case 5:
                send_direction = {-1.f, 1.f};
                break;
            case 6:
                send_direction = {-1.f, 0.f};
                break;
            case 7:
                send_direction = {-1.f, -1.f};
                break;
        }

        this->enemies_.push_back(new Enemy(rand()%window_size_.x - 64.f, rand()%window_size_.y - 40.f, send_direction));
        this->spawn_enemies = 0.f;
    }

    unsigned counter = 0;
    for (auto* enemy : this->enemies_)
    {
        enemy->update(this->delta_time_);
        if (enemy->getShapeBounds().position.y > this->window_->getSize().y ||
            enemy->getShapeBounds().position.y + enemy->getShapeBounds().size.y < 0.f ||
            enemy->getShapeBounds().position.x > this->window_->getSize().x ||
            enemy->getShapeBounds().position.x + enemy->getShapeBounds().size.x < 0.f
            )
            {
                delete this->enemies_.at(counter);
                this->enemies_.erase(this->enemies_.begin() + counter);
                --counter;
            }
            ++counter;
    }
}

void Game::bulletsCollidingEnemies()
{

    for (int i = 0; i < enemies_.size(); i++)
    {
        bool enemy_killed = false;
        for (int j = 0; j < bullets_.size() && enemy_killed == false; j++)
        {
            if (this->enemies_[i]->getShapeBounds().findIntersection(this->bullets_[j]->getBulletBounds()))
            {
                delete this->enemies_[i];
                this->enemies_.erase(this->enemies_.begin() + i);
                
                delete this->bullets_[j];
                this->bullets_.erase(this->bullets_.begin() + j);
                
                this->explotion_sound_->play();
                enemy_killed = true;
                this->counting_enemies_killed_++;
            }
        }
    }
}

void Game::playerCollidingAllien()
{
    if (this->player_->getPlayerIsAlive())
    {
        for (int i = 0; i < enemies_.size() && enemies_[i]->getEnemyShipIsAlive(); i++)
        {
            if (this->enemies_[i]->getShapeBounds().findIntersection(this->player_->getBounds()))
            {
                this->enemies_[i]->setEnemyShipIsAlive();
                delete this->enemies_[i];
                this->enemies_.erase(this->enemies_.begin() + i);
                this->player_->setPlayerIsAlive();
                this->explotion_sound_->play();
                this->counting_enemies_killed_++;
            }
        }
    }
    else 
    {
        this->player_explotes_sound->play();
        setGameStatus(GameOver);
    }
}

void Game::updateBullets()
{
    unsigned counter = 0;
    for (auto *bullet : bullets_)
    {
        bullet->bulletUpdate(this->delta_time_);
        if (bullet->getBulletBounds().getCenter().y + bullet->getBulletBounds().size.y < 0.f)
        {
            delete bullets_.at(counter);
            this->bullets_.erase(this->bullets_.begin() + counter);
            --counter;
        }
        ++counter;
    }
}

void Game::initEnemies()
{
    this->spawn_max_enemies = 25.f;
    this->spawn_enemies = spawn_max_enemies;
}

void Game::initFonts()
{
    // assets\font\space_invaders.ttf
    if (!this->font_.openFromFile("assets/font/MachineStd-Bold.otf"))
    {
        printf("ERROR::FONT::Could not load font file.\n");
    }
    this->enemies_killed_text_ = new sf::Text(this->font_);
    this->enemies_killed_text_->setCharacterSize(16);
}

void Game::initBusfferSounds()
{
    // assets/sounds/shoot.wav
    if (!this->shoot_buffer_.loadFromFile("assets/sounds/shoot.wav"))
    {
        printf("ERROR::BUFFER::SHOOT::Could not load buffer file\n");
    }

	// assets/sounds/alien_killed.wav
    if (!this->explotion_buffer_.loadFromFile("assets/sounds/alien_killed.wav"))
    {
        printf("ERROR::BUFFER::EXPLOTION::Could not load buffer file\n");
    }
    // assets/sounds/explosion.wav
    if (!this->player_explotes_buffer.loadFromFile("assets/sounds/explosion.wav"))
    {
        printf("ERROR::BUFFER::PLAYER::EXPLOTION::Could not load buffer file\n");
    }

    // assets\sounds\space-invaders-classic-arcade-game-116826.ogg
    if (!this->background_music_buffer_.loadFromFile("assets/sounds/space-invaders-classic-arcade-game-116826.ogg"))
    {
        printf("ERROR::BUFFER::BackgroundMusic::Could not load buffer file\n");
    }
}

void Game::setSounds()
{
	this->shoot_sound_ = new sf::Sound(this->shoot_buffer_);
    
    this->explotion_sound_ = new sf::Sound(this->explotion_buffer_);
	this->explotion_sound_->setVolume(60.f);
    
    this->player_explotes_sound = new sf::Sound(this->player_explotes_buffer);
    this->player_explotes_sound->setVolume(60.f);
	this->background_music_ = new sf::Sound(this->background_music_buffer_);
	this->background_music_->setLooping(true);
}

sf::Vector2f Game::getMousePosition() const
{
	return static_cast<sf::Vector2f>(sf::Mouse::getPosition(*this->window_));
}

void Game::setCurrentMousePosition()
{
	this->current_mouse_position_ = this->getMousePosition();
}

float Game::getAngle()
{
	float angle = std::atan2(current_mouse_position_.y - this->player_->getPlayerPosition().y, current_mouse_position_.x - this->player_->getPlayerPosition().x) * 180.f / 3.14159265f;
    return angle;
}

void Game::updateShipRotation()
{
	current_mouse_position_ = this->getMousePosition();
    if (current_mouse_position_ != last_mouse_position_)
    {
		last_mouse_position_ = current_mouse_position_;
		this->angle_ = getAngle();
		this->player_->setRotation(angle_ + 90.f);
    }
}

Game::Game()
{
    window_size_ = {1980, 1060};
    this->fps_ = 0.f;
    this->delta_time_ = 0.f;
    game_status = MainMenu;

    initWindow();
    initFonts();
    initMainMenu();
    initPauseMenu();
    setCurrentMousePosition();

    initGameOverText();
}

void Game::initPlayer()
{
    this->player_ = new Player();
    sf::Vector2f player_position = {
        static_cast<float>(this->window_size_.x) / 2.f,
        static_cast<float>(this->window_size_.y) / 2.f
    };
    this->player_->setPlayerPosition(player_position);
}

void Game::playerCollidingWindow()
{
    sf::FloatRect player_bounds = this->player_->getBounds();

    sf::Vector2f position = this->player_->getPlayerPosition();

    if (player_bounds.position.x < 0.f)
    {
        position.x -= player_bounds.position.x;
    }
    if (player_bounds.position.y < 0.f)
    {
        position.y -= player_bounds.position.y;
    }

    // Righrt
    float right_overlap = (player_bounds.position.x + player_bounds.size.x) - static_cast<float>(this->window_->getSize().x);
    if (right_overlap > 0.f)
    {
        position.x -= right_overlap;
    }

    // Bottom
    float bottom_overlap = (player_bounds.position.y + player_bounds.size.y) - static_cast<float>(this->window_->getSize().y);
    if (bottom_overlap > 0.f)
    {
        position.y -= bottom_overlap;
    }
    player_->setPlayerPosition(position);
}

void Game::updateGUI()
{
    std::stringstream ss;
    ss << "Enemies Killed : " << this->counting_enemies_killed_;
    this->enemies_killed_text_->setString(ss.str());
}

void Game::renderGUI()
{
    this->window_->draw(*this->enemies_killed_text_);
}

void Game::run()
{
    while (this->window_->isOpen())
    {
        this->setDeltaTime();
    }
}

bool Game::runningGame() const
{
    return false;
}

void Game::pollEvent()
{
    while (std::optional game_event = window_->pollEvent())
    {
        if (game_event->is<sf::Event::Closed>())
            window_->close();
        
        if (const auto* key_pressed = game_event->getIf<sf::Event::KeyPressed>())
        {
			this->mainMenuUpdate();
            this->pauseMenuUpdate();
            if (getGameStatus() == MainMenu && key_pressed->scancode == sf::Keyboard::Scancode::Escape)
            {
                this->window_->close();
            }
            else if (getGameStatus() == Paused && key_pressed->scancode == sf::Keyboard::Scancode::Escape)
            {
                setGameStatus(InGame);
            }
            else if (getGameStatus() == InGame && key_pressed->scancode == sf::Keyboard::Scancode::Escape)
            {
                setGameStatus(Paused);
            }
            else if (getGameStatus() == GameOver && key_pressed->scancode == sf::Keyboard::Scancode::Escape)
            {
                this->window_->close();
            }
            else if (getGameStatus() == GameOver && key_pressed->scancode == sf::Keyboard::Scancode::Enter)
            {
                setGameStatus(GameOver);
            }
        }
    }
}

void Game::update()
{

    this->pollEvent();

    if (getGameStatus() == InGame)
    {
        inGameUpdate();
    }
}

void Game::render()
{
    this->window_->clear();

    switch (game_status)
    {
    case MainMenu:
        this->mainMenuRender(); break;
    case InGame:
        this->inGameRender(); break;
    case Paused:
        this->pauseMenuRender(); break;
    case GameOver:
        this->gameOverRender(); break;
    }

    this->window_->display();
}

Game::~Game()
{
    delete this->window_;
    this->window_ = nullptr;

    delete this->video_mode_;
    this->video_mode_ = nullptr;

	delete this->background_;
	this->background_ = nullptr;

	delete this->background_menu_;
	this->background_menu_ = nullptr;

	delete this->title_main_screen_;
	this->title_main_screen_ = nullptr;

    delete this->pause_blur_screen_;
    this->pause_blur_screen_ = nullptr;

	delete this->play_text_;
	this->play_text_ = nullptr;

	delete this->exit_text_;
	this->exit_text_ = nullptr;

    delete this->paused_game_text_;
    this->paused_game_text_ = nullptr;

    delete this->exit_game_text_;
    this->exit_game_text_ = nullptr;

    delete this->continue_game_text_;
    this->continue_game_text_ = nullptr;

    delete this->game_over_text_;
    this->game_over_text_ = nullptr;

    delete this->player_;
    this->player_ = nullptr;

    delete this->bullet_texture_;
    this->bullet_texture_ = nullptr;
    
    for (auto *bullet : bullets_)
    {
        delete bullet;
    }

    for (auto* enemy : enemies_)
    {
        delete enemy;
    }

    delete this->enemies_killed_text_;
    this->enemies_killed_text_ = nullptr;

	delete this->shoot_sound_;
	this->shoot_sound_ = nullptr;

	delete this->explotion_sound_;
	this->explotion_sound_ = nullptr;

    delete this->player_explotes_sound;
    this->player_explotes_sound = nullptr;

	delete this->background_music_;
	this->background_music_ = nullptr;
}

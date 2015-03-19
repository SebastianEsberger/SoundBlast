#include "Game.hpp"
#include <math.h>

Game::Game()
	:windowSettings(0,0,4,2,0),
	gameWindow(sf::VideoMode(1366,768),"SoundBlast",sf::Style::None, windowSettings),
	mTextureHolder(),
	mSoundBufferHolder(),
	mFontHolder()
{

}

Game::~Game()
{

}

bool Game::Init()
{
	Game::loadTextures();
	Game::setTextures();

	Game::loadSoundBuffers();

	shot_sound.setBuffer(mSoundBufferHolder.get("shot"));

	Game::loadFonts();


	//TODO: redesign
	playerShip.Init();
	
	gameWindow.setFramerateLimit(120);
	gameWindow.setMouseCursorVisible(false);

	if(!gameMusic.openFromFile("media/music/Nero - Innocence.wav"))
	{
		//TODO: Logger should say that file is not available or not at right place -> create Logger first
	}

	gameMouse.Init();

	//For now, just return true. Later, when real critical loading is implemented -> redesign
	return true;
}

void Game::Run()
{
	gameMusic.play();
	sf::Clock clock;

	while(gameWindow.isOpen())
	{
		Game::getInput();
		Game::Update(clock.restart());
		Game::Render();
	}
}

void Game::Close()
{

}

void Game::Update(sf::Time deltaTime)
{
	gameMouse.Update(deltaTime);
	playerShip.update(deltaTime);
	if(playerShip.getfiring())
	{
		playerShip.fire(&shots,&shotSprite,&shot_sound);
	}

	std::list<Shot*>::const_iterator iter2;
	for(iter2=shots.begin();iter2!=shots.end();iter2++)
	{
		(*iter2)->update(deltaTime);
	}
}

void Game::getInput()
{
	sf::Event event;
	while (gameWindow.pollEvent(event))
	{
		switch (event.type)
		{
			case sf::Event::Closed:
				gameWindow.close();
				break;
			case sf::Event::KeyPressed:
				if(event.key.code==sf::Keyboard::Escape)
				{
					gameWindow.close();
				}
				if(event.key.code==sf::Keyboard::W)
				{
					playerShip.moveUp(true);
				}
				if(event.key.code==sf::Keyboard::A)
				{
					playerShip.moveLeft(true);
				}
				if(event.key.code==sf::Keyboard::S)
				{
					playerShip.moveDown(true);
				}
				if(event.key.code==sf::Keyboard::D)
				{
					playerShip.moveRight(true);
				}
				break;
			case sf::Event::KeyReleased:
				if(event.key.code==sf::Keyboard::W)
				{
					playerShip.moveUp(false);
				}
				if(event.key.code==sf::Keyboard::A)
				{
					playerShip.moveLeft(false);
				}
				if(event.key.code==sf::Keyboard::S)
				{
					playerShip.moveDown(false);
				}
				if(event.key.code==sf::Keyboard::D)
				{
					playerShip.moveRight(false);
				}
				break;
			case sf::Event::MouseButtonPressed:
				if(event.key.code==sf::Mouse::Left)
				{
					gameMouse.setRotationSpeed(360.f);
					gameMouse.setMouseScaling(true);

					playerShip.setfiring(true);

				}
				break;
			case sf::Event::MouseButtonReleased:
				if(event.mouseButton.button==sf::Mouse::Left)
				{
					gameMouse.setRotationSpeed(180.f);
					gameMouse.setMouseScaling(false);

					playerShip.setfiring(false);
				}
		}
	}
}

void Game::Render()
{
	gameWindow.clear();

	gameWindow.draw(background);
	gameWindow.draw(playerShip);
	
	std::list<Shot*>::const_iterator iter;
	for(iter=shots.begin();iter!=shots.end();iter++)
	{
		gameWindow.draw(**iter);
	}
	gameWindow.draw(gameMouse);
	gameWindow.display();
}

void Game::loadTextures()
{
	mTextureHolder.load("wingsquad","media/png/WingSquad.png");
	mTextureHolder.load("background","media/png/background.png");
	mTextureHolder.load("shot","media/png/Shot.png");
	mTextureHolder.load("cursor","media/png/Cursor.png");
}

void Game::loadSoundBuffers()
{
	mSoundBufferHolder.load("shot","media/sound/laser1.wav");
}

void Game::loadFonts()
{
	mFontHolder.load("photonica","media/fonts/Photonica_regular.ttf");
}

void Game::setTextures()
{
	background.setTexture(mTextureHolder.get("background"));
	shotSprite.setTexture(mTextureHolder.get("shot"));
	gameMouse.setTexture(mTextureHolder.get("cursor"));
	playerShip.setTexture(mTextureHolder.get("wingsquad"));
}
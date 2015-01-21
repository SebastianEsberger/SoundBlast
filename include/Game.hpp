#include "SFML\Graphics.hpp"
#include "SFML\Audio.hpp"
#include "Ship.hpp"
#include "Mouse.hpp"
#include <string>
#include "ResourceHolder.hpp"


#include <list>

#define ANTIALIASING 4;

class Game
{
public:
							Game();
							~Game();

	bool					Init();
	void					Run();
	void					Close();


private:
	void					Update(sf::Time deltaTime);
	void					Render();
	void					getInput();

	void					loadTextures();
	void					loadSoundBuffers();
	void					loadFonts();

	sf::ContextSettings		windowSettings;
	sf::RenderWindow		gameWindow;

	std::list<Shot*>		shots;

	ResourceHolder<sf::Texture,std::string> mTextureHolder; 
	ResourceHolder<sf::SoundBuffer,std::string> mSoundBufferHolder;
	ResourceHolder<sf::Font,std::string> mFontHolder;
	
	Mouse					gameMouse;

	Ship					playerShip;

	sf::Music				gameMusic;

	
	sf::Sprite				background;
	sf::Sprite				shotSprite;

	sf::Font				myFont;
	sf::Text				myText;

	sf::Sound				shot_sound;
};
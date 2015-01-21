#include "Shot.hpp"
#include <string>
#include <list>
#include "SFML\Graphics.hpp"
#include "SFML\Audio.hpp"
#include <stdexcept>


class Ship : public sf::Drawable
{
public:
							Ship();
							Ship(const sf::Texture &texture);
							~Ship();

	bool					Init();
	void					setPosition(float x, float y);
	void					setPosition(sf::Vector2f position);
	sf::Vector2f			getPosition();
	void					move(float x, float y);
	void					move(sf::Vector2f distance);
	void					update(sf::Time &deltaTime);

	void					setTexture(const sf::Texture &tex);

	void					moveUp(bool is);
	void					moveDown(bool is);
	void					moveRight(bool is);
	void					moveLeft(bool is);

	void					setfiring(bool is);
	bool					getfiring();

	void					fire(std::list<Shot*>* ptr_shots, sf::Sprite* ptr_spr, sf::Sound* shot_sound);

	float					getShipRotation();

private:
	float					x;
	float					y;

	sf::Texture				shipTexture;
	sf::Sprite				shipSprite;

	void					draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void					setRotation();

	bool					ismovingUp;
	bool					ismovingDown;
	bool					ismovingRight;
	bool					ismovingLeft;

	bool					isfiring;

	sf::Vector2f			shipVelocity;
	sf::Vector2f			maxVelocity;

	sf::Vector2f			shipAcceleration;
	sf::Vector2f			maxAcceleration;

	sf::Clock				reloadTime;
};
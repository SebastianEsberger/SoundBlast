#include "SFML\Graphics.hpp"

class Shot : public sf::Drawable
{
public:
							Shot();
							Shot(sf::Sprite &shotSprite, int speed,sf::Vector2f direction);
							Shot(sf::Sprite &shotSprite, int speed,float angle,sf::Vector2f pos);


	void					update(sf::Time deltaTime);


private:
	void					draw(sf::RenderTarget& target, sf::RenderStates states) const;

	sf::Sprite				shotSprite;
	float					speed;
	sf::Vector2f			direction;
};
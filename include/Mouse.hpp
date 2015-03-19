#pragma once

#include "SFML\Graphics.hpp"

class Mouse : public sf::Drawable
{
public:
							Mouse();
							~Mouse();

	bool					Init();
	void					Update(sf::Time deltaTime);
	void					draw(sf::RenderTarget& target, sf::RenderStates states) const;

	void					setMouseScaling(bool is);
	void					setRotationSpeed(float speed);
	void					setPosition(float x, float y);

	void					setTexture(const sf::Texture &tex);


private:
	sf::Sprite				mouseSprite;

	float					mouseRotationSpeed;
	float					mouseSizeNormal;
	float					mouseSizePressed;
	float					mouseShrinkTime;
	bool					mouseIsScaling;
};
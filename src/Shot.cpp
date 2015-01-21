#include "Shot.hpp"
#include <math.h>

#define PI180 0.01745329

Shot::Shot()
{

}

Shot::Shot(sf::Sprite &shotSprite, int speed,sf::Vector2f direction)
{
	Shot::shotSprite=shotSprite;
	Shot::shotSprite.setPosition(200,100);
	Shot::speed=speed;
	Shot::direction=direction;

}

Shot::Shot(sf::Sprite &shotSprite, int speed,float angle, sf::Vector2f pos)
{
	Shot::shotSprite=shotSprite;
	Shot::shotSprite.setOrigin(shotSprite.getLocalBounds().width/2,shotSprite.getLocalBounds().height/2);
	Shot::shotSprite.setPosition(pos);
	Shot::speed=speed;
	Shot::shotSprite.setRotation(angle);
	
	Shot::direction.y=-1*cos(angle*PI180)*speed;
	Shot::direction.x=sin(angle*PI180)*speed;
}

void Shot::update(sf::Time deltaTime)
{
	//Move
	shotSprite.move(direction*deltaTime.asSeconds());
}

// Inheritance from Drawable.hpp
void Shot::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(shotSprite,states);
}
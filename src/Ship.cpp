#include "Ship.hpp"
#include <math.h>

Ship::Ship()
	:shipVelocity(0.f,0.f),
	maxVelocity(200.f,200.f),
	shipAcceleration(0.f,0.f),
	maxAcceleration(400.f,400.f),
	ismovingUp(false),
	ismovingDown(false),
	ismovingRight(false),
	ismovingLeft(false),
	isfiring(false)
{

}

Ship::Ship(const sf::Texture& texture)
{
	shipSprite.setTexture(texture);
	Ship();
}


Ship::~Ship()
{

}

bool Ship::Init()
{
	setPosition(400,400);
	shipSprite.setOrigin(shipSprite.getLocalBounds().width/2,shipSprite.getLocalBounds().height/2);

	return true;
}

void Ship::setTexture(const sf::Texture &tex)
{
	Ship::shipSprite.setTexture(tex);
}

void Ship::setPosition(float x, float y)
{
	Ship::shipSprite.setPosition(x,y);
}

void Ship::setPosition(sf::Vector2f position)
{
	Ship::shipSprite.setPosition(position);
}

void Ship::move(float x, float y)
{
	Ship::shipSprite.move(x,y);
}

void Ship::move(sf::Vector2f distance)
{
	Ship::shipSprite.move(distance);
}

sf::Vector2f Ship::getPosition()
{
	return sf::Vector2f(x,y);
}

void Ship::moveUp(bool is)
{
	ismovingUp=is;
}

void Ship::moveDown(bool is)
{
	ismovingDown=is;
}

void Ship::moveRight(bool is)
{
	ismovingRight=is;
}

void Ship::moveLeft(bool is)
{
	ismovingLeft=is;
}

void Ship::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(shipSprite,states);
}

void Ship::update(sf::Time &deltaTime)
{
	setRotation();

	if(ismovingUp && !ismovingDown)
	{
		shipVelocity.y-=1000.f*deltaTime.asSeconds();
	}
	if(!ismovingUp && ismovingDown)
	{
		shipVelocity.y+=1000.f*deltaTime.asSeconds();
	}
	if(ismovingRight && !ismovingLeft)
	{
		shipVelocity.x+=1000.f*deltaTime.asSeconds();
	}
	if(!ismovingRight && ismovingLeft)
	{
		shipVelocity.x-=1000.f*deltaTime.asSeconds();
	}

	shipSprite.move(shipVelocity*deltaTime.asSeconds());

	//Check Boundaries; TODO: replace numbers with window-width
	if(shipSprite.getPosition().x<0)
	{
		shipSprite.setPosition(0,shipSprite.getPosition().y);
		shipVelocity.x*=-0.7;
	}
	else if(shipSprite.getPosition().x>1366)
	{
		shipSprite.setPosition(1366,shipSprite.getPosition().y);
		shipVelocity.x*=-0.7;
	}
	if(shipSprite.getPosition().y<0)
	{
		shipSprite.setPosition(shipSprite.getPosition().x,0);
		shipVelocity.y*=-0.7;
	}
	else if(shipSprite.getPosition().y>768)
	{
		shipSprite.setPosition(shipSprite.getPosition().x,768);
		shipVelocity.y*=-0.7;
	}

	shipVelocity*=1.f-0.9f*deltaTime.asSeconds()*2;
}

float Ship::getShipRotation()
{
	return shipSprite.getRotation();
}

void Ship::setRotation()
{
	shipSprite.setRotation(atan2(sf::Mouse::getPosition().y-shipSprite.getPosition().y,sf::Mouse::getPosition().x-shipSprite.getPosition().x)*180/3.1415926+90);
}

void Ship::fire(std::list<Shot*>* ptr_shots, sf::Sprite* ptr_spr,sf::Sound* shot_sound)
{
	if(reloadTime.getElapsedTime().asSeconds()>=0.20)
	{
		reloadTime.restart();
		ptr_shots->push_front(new Shot(*ptr_spr,1300,shipSprite.getRotation(),sf::Vector2f(shipSprite.getPosition().x,shipSprite.getPosition().y-shipSprite.getLocalBounds().height/2)));
		shot_sound->play();
	}
}

void Ship::setfiring(bool is)
{
	isfiring=is;
}

bool Ship::getfiring()
{
	return isfiring;
}
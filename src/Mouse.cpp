#include "Mouse.hpp"

Mouse::Mouse()
	:mouseRotationSpeed(180.f)
{

}

Mouse::~Mouse()
{

}

bool Mouse::Init()
{
	mouseRotationSpeed=180.f;
	mouseSizeNormal=0.3f;
	mouseSizePressed=0.2f;
	mouseIsScaling=false;

	mouseSprite.setScale(mouseSizeNormal,mouseSizeNormal);
	mouseSprite.setOrigin(mouseSprite.getLocalBounds().width/2,mouseSprite.getLocalBounds().height/2);

	return true;
}

void Mouse::Update(sf::Time deltaTime)
{
	mouseSprite.setPosition(sf::Mouse::getPosition().x,sf::Mouse::getPosition().y);
	mouseSprite.rotate(mouseRotationSpeed*deltaTime.asSeconds());

	if(mouseIsScaling && mouseSprite.getScale().x>mouseSizePressed)
	{
		mouseSprite.setScale	(mouseSprite.getScale().x-(mouseSizeNormal-mouseSizePressed)*deltaTime.asSeconds()*8,
								 mouseSprite.getScale().x-(mouseSizeNormal-mouseSizePressed)*deltaTime.asSeconds()*8);
	}
	else if(mouseSprite.getScale().x<mouseSizeNormal)
	{
		mouseSprite.setScale	(mouseSprite.getScale().x+(mouseSizeNormal-mouseSizePressed)*deltaTime.asSeconds()*8,
								 mouseSprite.getScale().x+(mouseSizeNormal-mouseSizePressed)*deltaTime.asSeconds()*8);
	}
}

void Mouse::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(mouseSprite,states);
}

void Mouse::setMouseScaling(bool is)
{
	mouseIsScaling=is;
}

void Mouse::setRotationSpeed(float speed)
{
	mouseRotationSpeed=speed;
}

void Mouse::setPosition(float x, float y)
{
	mouseSprite.setPosition(x,y);
}

void Mouse::setTexture(const sf::Texture &tex)
{
	Mouse::mouseSprite.setTexture(tex);
}
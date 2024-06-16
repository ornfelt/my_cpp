#pragma once

#include <SFML/Graphics.hpp>


struct CustomDrawable : public sf::Drawable
{
	CustomDrawable(sf::PrimitiveType type, uint64_t n)
		: va(type, n)
	{
	}

	void draw(sf::RenderTarget& target, const sf::RenderStates state) const override
	{
		target.draw(va, rs);
	}

	sf::VertexArray va;
	sf::RenderStates rs;
};

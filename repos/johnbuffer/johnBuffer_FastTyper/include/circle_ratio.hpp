#pragma once

#pragma once

#include <SFML/Graphics.hpp>

class CircleRatio : public sf::Drawable
{
public:
	CircleRatio(float radius, float x, float y, float ratio)
		: m_radius(radius)
		, m_x(x)
		, m_y(y)
		, m_ratio(ratio)
		, m_color(sf::Color::White)
	{}

	void setX(float x)
	{
		m_x = x;
	}

	void setY(float y)
	{
		m_y = y;
	}

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override
	{
		const float thickness(8.0f);
		const float quality(64.0f);

		sf::VertexArray va(sf::TrianglesStrip, 2 * quality);

		const float pi(3.141592653f);
		const float angle(m_ratio * 2.0f * pi);
		const float da(angle / (quality - 1.0f));
		for (uint32_t i(0); i < quality; ++i)
		{
			float a(i * da - pi * 0.5f);
			const float x1(m_x - m_radius * cos(a));
			const float y1(m_y + m_radius * sin(a));

			const float x2(m_x - (m_radius - thickness) * cos(a));
			const float y2(m_y + (m_radius - thickness) * sin(a));

			va[2 * i + 0].position = sf::Vector2f(x1, y1);
			va[2 * i + 1].position = sf::Vector2f(x2, y2);
			va[2 * i + 0].color = m_color;
			va[2 * i + 1].color = m_color;
		}

		target.draw(va, states);
	}

	void setFillColor(const sf::Color& color)
	{
		m_color = color;
	}

	void setRatio(float ratio)
	{
		m_ratio = ratio;
	}

private:
	float m_radius;
	trn::Transition<float> m_x;
	trn::Transition<float> m_y;

	float m_ratio;
	sf::Color m_color;
};

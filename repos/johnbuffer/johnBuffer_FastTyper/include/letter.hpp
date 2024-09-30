#pragma once

#include <SFML/Graphics.hpp>
#include <transition.hpp>
#include <iostream>
#include "theme.hpp"
#include "font_dependant.hpp"
#include "utils.hpp"

class Letter : public sf::Drawable, public FontDependant
{
public:
	enum LetterState
	{
		Ok,
		Wrong,
		Outside,
		Skipped,
		Corrected,
		Unknown,
	};

	Letter(char c, const sf::Vector2f& position, uint32_t line, const sf::Font& font, uint32_t character_size) 
		: m_char(c)
		, FontDependant(font, character_size)
		, m_line(line)
		, m_state(Letter::Unknown)
		, m_x(position.x)
		, m_y(position.y)
		, m_r(255.0f)
		, m_g(255.0f)
		, m_b(255.0f)
		, m_alpha(255.0f)
	{
		setColor(Theme<>::LetterUnknown);
		m_y.setSpeed(3.0f);
		m_r.setSpeed(3.0f);
		m_g.setSpeed(3.0f);
		m_b.setSpeed(3.0f);

		m_advance = font.getGlyph(c, character_size, false).advance;
	}

	float getAdvance() const
	{
		return m_advance;
	}

	int32_t getLine() const
	{
		return m_line;
	}

	void setY(float y)
	{
		m_y = y;
	}

	void addY(float dy)
	{
		m_y += dy;
	}

	void setX(float x)
	{
		m_x = x;
	}

	void setAlpha(float alpha)
	{
		m_alpha = alpha;
	}

	void addLine()
	{
		++m_line;
	}

	void setState(LetterState state)
	{
		m_state = state;
		switch (state)
		{
		case Letter::Ok:
			setColor(Theme<>::LetterOk);
			break;
		case Letter::Wrong:
			setColor(Theme<>::LetterWrong);
			break;
		case Letter::Corrected:
			setColor(Theme<>::LetterCorrected);
			break;
		case Letter::Unknown:
			setColor(Theme<>::LetterUnknown);
			break;
		case Letter::Skipped:
			setColor(Theme<>::LetterSkipped);
			break;
		default:
			break;
		}
	}

	LetterState getTypedState() const
	{
		LetterState state(LetterState::Wrong);
		if (m_state == LetterState::Skipped) {
			state = Letter::LetterState::Corrected;
		} else if (m_state == LetterState::Unknown) {
			state = Letter::LetterState::Ok;
		}

		return state;
	}

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override
	{
		sf::Uint8 r(static_cast<sf::Uint8>(m_r));
		sf::Uint8 g(static_cast<sf::Uint8>(m_g));
		sf::Uint8 b(static_cast<sf::Uint8>(m_b));
		sf::Text text = textBuilder(getFont(), m_char_size, sf::Color(r, g, b), std::string(1, m_char));
		text.setPosition(m_x, m_y);
		target.draw(text, states);
	}

	char getChar() const
	{
		return m_char;
	}

	float getX() const
	{
		return m_x;
	}

	float getY() const
	{
		return m_y;
	}

	const LetterState getState() const
	{
		return m_state;
	}

	static bool isCorrect(LetterState state)
	{
		return state == Letter::Ok || state == Letter::Corrected;
	}

private:
	const char       m_char;
	int32_t          m_line;
	LetterState      m_state;
	float            m_advance;

	float m_x;
	trn::Transition<float> m_y;
	trn::Transition<float> m_r;
	trn::Transition<float> m_g;
	trn::Transition<float> m_b;
	float m_alpha;

	void setColor(const sf::Color& color)
	{
		m_r = color.r;
		m_g = color.g;
		m_b = color.b;
	}
};

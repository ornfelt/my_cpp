#pragma once

#include <SFML/System/Clock.hpp>
#include <stdint.h>
#include <string>
#include "utils.hpp"

struct ChallengeStatus
{
	ChallengeStatus()
		: entry_no_error(0)
		, entry_count(0)
		, error_count(0)
		, correct_word_count(0)
		, perfect_word_count(0)
		, total_word_count(0)
		, started(false)
		, current_word_perfect(true)
		, current_word_str("")
		, replay_mode(false)
	{}

	Letter::LetterState addChar(const std::string& typed, const Letter& current_letter)
	{
		Letter::LetterState letter_state(Letter::LetterState::Wrong);
		const std::size_t typed_size(typed.size());
		const std::size_t check_size(current_word_str.size());

		++entry_count;
		if (typed_size > check_size) {
			error();
			letter_state = Letter::LetterState::Outside;
		} else {
			if (isTypedCharValid(typed)) {
				++entry_no_error;
				letter_state = current_letter.getTypedState();
			} else {
				error();
			}
		}
		
		return letter_state;
	}

	bool isTypedCharValid(const std::string& typed) const
	{
		const std::size_t typed_size(typed.size());
		const char        last_char = getLastCharOfString(typed);
		const char        current_word_char(current_word_str[typed_size - 1]);
		
		return last_char == current_word_char;
	}

	void error()
	{
		last_error.restart();
		entry_no_error = 0;
		++error_count;
		current_word_perfect = false;
	}

	void reset()
	{
		started = false;
		entry_count = 0;
		entry_no_error = 0;
		error_count = 0;
		current_word_perfect = true;
		correct_word_count = 0;
		perfect_word_count = 0;
		total_word_count = 0;

		current_word_str = std::string();

		clock.restart();
		last_error.restart();
	}

	WordInfo::WordStatus nextWord(const std::string& typed, const std::string& next_word_str)
	{
		bool current_word_correct(true);
		if (typed != current_word_str) {
			error();
			current_word_correct = false;
		} else {
			++correct_word_count;
			if (current_word_perfect) {
				++perfect_word_count;
			}
		}

		WordInfo::WordStatus current_word_status(WordInfo::WordStatus::Wrong);
		if (current_word_perfect) {
			current_word_status = WordInfo::WordStatus::Perfect;
		} else if (current_word_correct) {
			current_word_status = WordInfo::WordStatus::Correct;
		}

		++total_word_count;
		current_word_perfect = true;
		current_word_str = next_word_str;
		
		return current_word_status;
	}

	float getElapsedSeconds() const
	{
		return clock.getElapsedTime().asSeconds();
	}

	int32_t getElapsedMilliseconds() const
	{
		return clock.getElapsedTime().asMilliseconds	();
	}

	void pop()
	{
		error();
	}

	float getAccuracy() const
	{
		if (getElapsedSeconds() < 1 || !entry_count) {
			return 0.0f;
		}

		const float accuracy((entry_count - error_count) / float(entry_count));

		return std::max(0.0f, accuracy);
	}

	float getWPM()const
	{
		if (getElapsedSeconds() < 1)
			return 0.0f;

		const float time(getElapsedMilliseconds() * 0.001f / 60.0f);
		const float wpm((entry_count * 0.2f - (!current_word_perfect) * 5) / time);

		return std::max(0.0f, wpm);
	}

	bool started;
	bool current_word_perfect;
	bool replay_mode;

	uint32_t entry_no_error;
	uint32_t entry_count;
	uint32_t error_count;
	uint32_t correct_word_count;
	uint32_t perfect_word_count;
	uint32_t total_word_count;
	
	std::string current_word_str;

	sf::Clock clock;
	sf::Clock last_error;
};

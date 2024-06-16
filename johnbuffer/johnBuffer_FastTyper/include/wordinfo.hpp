#pragma once
#include <stdint.h>
#include <string>
#include "letter.hpp"
#include <iostream>

struct WordInfo
{
	enum WordStatus
	{
		Correct,
		Perfect,
		Wrong
	};

	WordInfo()
		: string("")
		, start_index(0)
		, length(0)
		, first_of_line(false)
		, width(0.0f)
	{}

	WordInfo(const std::string& str, uint32_t index)
		: string(str)
		, start_index(index)
		, length(string.size())
		, first_of_line(false)
		, width(0.0f)
	{}

	float getWordWidth(const std::vector<Letter>& letters) const
	{
		const Letter& first(letters[start_index]);
		const Letter& last(letters[start_index+length-1]);
		return last.getX() + last.getAdvance() - first.getX();
	}

	uint32_t skipRest(std::vector<Letter>& letters)
	{
		uint32_t skipped(0U);
		for (std::size_t i(0); i < length; ++i) {
			if (letters[start_index + i].getState() == Letter::Unknown) {
				letters[start_index + i].setState(Letter::Skipped);
				++skipped;
			}
		}

		return skipped;
	}

	const std::string string;
	uint32_t          start_index;
	std::size_t       length;
	bool              first_of_line;
	float             width;
};
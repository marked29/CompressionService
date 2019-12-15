#include "StringCompressor.h"



void StringCompressor::construct_response(std::ostream & result, char symbol, int character_counter)
{
	// replacing a with 1a increases the character count instead of reducing it
	// don't do it
	if (character_counter == 1) {
		result << symbol;
	}
	// replacing aa with 2a doesn't reduce the character count;
	// don't do it
	else if (character_counter == 2) {
		result << symbol << symbol;
	}
	else {
		result << character_counter << symbol;
	}
}

void StringCompressor::compress_data() 
{
	char character = ' ';
	char next_character = ' ';
	std::ostringstream compression_result;

	std::stringstream stream(m_raw_data);
	stream >> character;

	int character_count = 1;

	while ((next_character = stream.peek()) != EOF) {
		if (next_character == character) {
			character_count++;
			stream >> next_character;
		}
		else {
			// replacing a with 1a increases the character count instead of reducing it; 
			// don't do it
			construct_response(compression_result, character, character_count);

			character_count = 1;
			stream >> next_character;
			character = next_character;
		}
	}

	// now one more character (and its count) is not pushed into compression_result, so we have to do this.
	// this is because we peeked and found EOF therefore we stopped 
	construct_response(compression_result, character, character_count);

	m_result =  compression_result.str();   // return the stringstream as a string
}

std::string StringCompressor::get_result() const 
{
	return m_result;
}
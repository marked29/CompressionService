#include <iostream>
#include <sstream>

void construct_response(std::ostream& result, char symbol, int character_counter) 
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

std::string compress(std::stringstream& stream) {
	char character = ' ';
	char next_character = ' ';
	std::ostringstream compression_result;

	stream >> character;    
	int character_count = 1;  
	
	while ((next_character = stream.peek()) != EOF) {
		if (next_character == character) {  
			character_count++;
			stream >> next_character;   
		}
		else {
			construct_response(compression_result, character, character_count);
			character_count = 1;
			stream >> next_character;
			character = next_character;
		}
	}

	//Now one more character (and its count) is not pushed into compression_result, so we have to do this.
	//This is because we peeked and found EOF therefore we stopped 
	construct_response(compression_result, character, character_count);

	return compression_result.str();
}

int main() {
	std::string input;
	getline(std::cin, input);
	std::stringstream ss(input);   
	std::string str = compress(ss);
	std::cout << str;

	system("pause");
	return 0;
}
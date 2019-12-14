#include <iostream>
#include <sstream>

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
			// replacing a with 1a increases the character count instead of reducing it; 
			// don't do it
			if (character_count == 1) {
				compression_result << character;
			}
			// replacing aa with 2a doesn't reduce the character count;
			// don't do it
			else if (character_count == 2) {
				compression_result << character << character;
			}
			else {
				compression_result << character_count << character;
			}

			character_count = 1;
			stream >> next_character;
			character = next_character;
		}
	}

	//Now one more character (and its count) is not pushed into compression_result, so we have to do this.
	//This is because we peeked and found EOF therefore we stopped 
	if (character_count == 1) {
		compression_result << character;
	}
	else if (character_count == 2) {
		compression_result << character << character;
	}
	else {
		compression_result << character_count << character;
	}

	return compression_result.str();   // return the stringstream as a string
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
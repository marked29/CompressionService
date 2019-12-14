#include <iostream>
#include <sstream>

std::string parse(std::stringstream& stream) {
	char character, temp_character, prev_temp_char;  // characters for reading from stream
	std::ostringstream ret;     // return stream (will be returend as string)

	stream >> character;    // get first character
	int character_count = 1;  // set character_count to 1

	//peek() gets the next character in the stream WITHOUT extracting it!
	//It is therefore perfect to get a look at upcoming characters without
	//using them 
	while ((temp_character = stream.peek()) != EOF) {
		if (temp_character == character) {  // compare the peeked character with ours
			character_count++;
			prev_temp_char = temp_character;
			stream >> temp_character;   // this is the real extraction
		}
		else {
			 //if the peeked character is not ours anymore, we push everything
			 //into our ret stream and reset character_count. I assumed that you
			 //don't want to print a1 if there is just 1 a so i checked the cases 
			if (character_count == 1) {
				ret << character;
			}
			else if (character_count == 2) {
				ret << character << prev_temp_char;
			}
			else {
				ret << character_count << character;
			}
			character_count = 1;
			stream >> temp_character;
			character = temp_character;
		}
	}

	//Now one more character (and its count) is not pushed into ret, so we have to do this.
	//This is because we peeked and found EOF therefore we stopped 
	if (character_count == 1) {
		ret << character;
	}
	else if (character_count == 2) {
		ret << character << prev_temp_char;
	}
	else {
		ret << character_count << character;
	}

	return ret.str();   // return the stringstream as a string
}

int main() {
	std::string input;
	getline(std::cin, input);   // get line from std::cin into std::string input
	std::stringstream ss(input);   // build str::stringstream from input
	std::string str = parse(ss);    // our function
	std::cout << str;

	system("pause");
	return 0;
}
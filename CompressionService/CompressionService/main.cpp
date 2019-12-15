#include <iostream>
#include "StringCompressor.h"

int main() {
	std::string input;
	std::cin >> input;
	std::unique_ptr<iDataCompressor> Compressor = std::make_unique<StringCompressor>(input);
	Compressor->compress_data();
	std::cout << Compressor->get_result();
	system("pause");
	return 0;
}
#include <iostream>
#include <string>

enum Status {
	Ping = 1,
	GetStats,
	ResetStats,
	Compress
};

struct Header
{
	uint32_t wide_magic_value = 0x53545259;
	uint16_t payload_size ;
	uint16_t status_code ;
};


int main()
{
	
	Header msg;
	char data[] = "suckit";
	msg.payload_size = strlen(data);
	msg.status_code = 1;
	std::string sheisse = std::to_string(msg.wide_magic_value) + std::to_string(msg.payload_size) + std::to_string(msg.status_code) + data;
	

	const char * some = sheisse.c_str();

	


	std::cout << sheisse<< std::endl;

	system("pause");
	return 0;
}
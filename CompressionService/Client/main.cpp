//
// blocking_tcp_echo_client.cpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2018 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>
#define ASIO_STANDALONE
#include "asio.hpp"

using asio::ip::tcp;


enum Status {
	Ping = 1,
	GetStats,
	ResetStats,
	Compress
};

struct Header
{
	uint32_t wide_magic_value = 0x53545259;
	uint16_t payload_size = 0;
	uint16_t code_status;
	std::string payload;
};

std::vector<char> Serialize(const Header &raw_header)
{
	std::vector<char> bytes;
	bytes.insert(bytes.end(), reinterpret_cast<const char *>(&raw_header.wide_magic_value),reinterpret_cast<const char *>(&raw_header.wide_magic_value)+sizeof(uint32_t));
	bytes.insert(bytes.end(), reinterpret_cast<const char *>(&raw_header.payload_size),reinterpret_cast<const char *>(&raw_header.payload_size)+sizeof(uint16_t));
	bytes.insert(bytes.end(), reinterpret_cast<const char *>(&raw_header.code_status),reinterpret_cast<const char *>(&raw_header.code_status)+sizeof(uint16_t));
	bytes.insert(bytes.end(), reinterpret_cast<const char *>(&raw_header.payload),reinterpret_cast<const char *>(&raw_header.payload)+raw_header.payload_size);

	return bytes;
}

void Deserialize(const char* data_)
{
	std::vector<char> bytes;
 	
	
	Header message;
	std::cout << message.wide_magic_value << ": " << message.payload_size << ": " << message.code_status << ": " << std::endl;
	std::cout << "Payload: " << message.payload << std::endl;
};


enum { max_length = 1024 };

int main(int argc, char* argv[])
{
	try
	{
		if (argc != 3)
		{
			std::cerr << "Usage: blocking_tcp_echo_client <host> <port>\n";
			return 1;
		}

		asio::io_context io_context;

		tcp::socket s(io_context);
		tcp::resolver resolver(io_context);
		asio::connect(s, resolver.resolve(argv[1], argv[2]));

		Header msg;
		std::string payload = "";
		std::cout << "Enter message: ";
		std::cin >> payload;
		std::cout << "Enter command: ";
		std::cin >> msg.code_status;

		;
		msg.payload_size = msg.payload.length();


		asio::write(s, asio::buffer(Serialize(msg), sizeof(Header)));

		
		char reply[max_length];
		size_t reply_length = asio::read(s, asio::buffer(reply, sizeof(Header)));
		Deserialize(reply);
	
	}
	catch (std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << "\n";
	}

	return 0;
}
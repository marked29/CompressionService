//
// async_tcp_echo_server.cpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2018 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#include <cstdlib>
#include <iostream>
#include <memory>
#include <utility>
#include <string>
#include <sstream>

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
	uint16_t payload_size;
	uint16_t code_status;
	std::string payload;

};


void Deserialize(const char* data_)
{
	Header message;
	memcpy(&message, data_, sizeof(Header));
	std::cout << "Header: " << message.wide_magic_value << " :" << message.payload_size << " :" << message.code_status << std::endl;
	std::cout << "Payload: " << message.payload << std::endl;
};

const int max_length = 1024;

void session(tcp::socket sock)
{
	try
	{
		for (;;)
		{
			char data[max_length];
			char payload[max_length];

			asio::error_code error;
			size_t length = sock.read_some(asio::buffer(data), error);

			Deserialize(data);

			if (error == asio::error::eof)
				break; // Connection closed cleanly by peer.
			else if (error)
				throw asio::system_error(error); // Some other error.

			asio::write(sock, asio::buffer(data, sizeof(Header)));
		}
	}
	catch (std::exception& e)
	{
		std::cerr << "Exception in thread: " << e.what() << "\n";
	}
}

void server(asio::io_context& io_context, unsigned short port)
{
	tcp::acceptor a(io_context, tcp::endpoint(tcp::v4(), port));
	for (;;)
	{
		std::thread(session, a.accept()).detach();
	}
}

int main(int argc, char* argv[])
{
	try
	{
		//if (argc != 2)
		//{
		//	std::cerr << "Usage: blocking_tcp_echo_server <port>\n";
		//	return 1;
		//}

		asio::io_context io_context;

		server(io_context, 4000);
	}
	catch (std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << "\n";
	}

	return 0;
}
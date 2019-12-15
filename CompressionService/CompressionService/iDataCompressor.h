#pragma once
#include <string>

class iDataCompressor
{
public:

	virtual void compress_data() = 0;
	virtual std::string get_result() const = 0;
};


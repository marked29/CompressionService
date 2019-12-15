#pragma once
#include "iDataCompressor.h"
#include <string>
#include <sstream>

class StringCompressor : public iDataCompressor
{
private:
	std::string m_raw_data = "";
	std::string m_result = "";

	void construct_response(std::ostream& result, char symbol, int character_counter);

public:
	StringCompressor() = default;
	explicit StringCompressor(std::string data) : m_raw_data(data) {}
	StringCompressor(const StringCompressor& obj) : m_raw_data(obj.m_raw_data), m_result(obj.m_result) {};
	StringCompressor(StringCompressor&& obj) : m_raw_data(std::move(obj.m_raw_data)), m_result(std::move(obj.m_result)) {};
	virtual ~StringCompressor() {};

	StringCompressor& operator=(const StringCompressor& obj) {
		if (this == &obj)
		{
			return *this;
		}

		m_raw_data = obj.m_raw_data;
		m_result = obj.m_result;

		return *this;
	}
	StringCompressor& operator=(StringCompressor&& obj) {
		if (this == &obj)
		{
			return *this;
		}
		m_raw_data= std::move(obj.m_raw_data);
		m_result = std::move(obj.m_result);

		return *this;
	}
	
	void compress_data() override;
	std::string get_result() const;

};


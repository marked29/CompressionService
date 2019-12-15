#pragma once
class iDataCompressor
{
public:
	iDataCompressor();
	virtual ~iDataCompressor();

	virtual void compress_data() = 0;
};


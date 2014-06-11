#pragma once

#include "ChannelFormat.h"

public ref class FtfImageData
{
public:
	int width, height;
	ChannelFormat^ fileFormat;
	array<double,2>^ rData;
	array<double,2>^ gData;
	array<double,2>^ bData;
	array<double,2>^ iData;
	array<double,2>^ aData;

	FtfImageData();
	~FtfImageData();
	void reset();
	void initData();
};


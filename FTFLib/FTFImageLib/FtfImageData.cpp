#include "StdAfx.h"
#include "FtfImageData.h"

FtfImageData::FtfImageData()
{
	reset();
}

FtfImageData::~FtfImageData()
{
	reset();
}

void FtfImageData::reset()
{
	fileFormat = gcnew ChannelFormat();
	width = 0;
	height = 0;

	if (rData)
	{
		delete(rData);
	}
	if (gData)
	{
		delete(gData);
	}
	if (bData)
	{
		delete(bData);
	}
	if (iData)
	{
		delete(iData);
	}
	if (aData)
	{
		delete(aData);
	}
}

void FtfImageData::initData()
{
	if (!fileFormat->grayscaleMode)
	{
		// color
		rData = gcnew array<double,2>(height, width);
		gData = gcnew array<double,2>(height, width);
		bData = gcnew array<double,2>(height, width);

		delete iData;
	}
	else
	{
		// grayscale
		iData = gcnew array<double,2>(height, width);

		delete rData;
		delete gData;
		delete bData;
	}

	if (fileFormat->hasAlpha)
	{
		aData = gcnew array<double,2>(height, width);
	}
	else
	{
		delete aData;
	}
}

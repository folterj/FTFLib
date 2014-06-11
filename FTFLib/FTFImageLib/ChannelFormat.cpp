#include "StdAfx.h"
#include "ChannelFormat.h"

using namespace System::Drawing;

ChannelFormat::ChannelFormat()
{
	floatMode = false;
	grayscaleMode = false;
	colorChannelsFormat = ColorChannelsFormat::RGB;
	hasAlpha = false;
	compressed = true;

	setColor(hasAlpha);
}

ChannelFormat::ChannelFormat(ChannelFormat^ format)
{
	grayscaleMode = format->grayscaleMode;
	floatMode = format->floatMode;
	colorChannelsFormat = format->colorChannelsFormat;
	hasAlpha = format->hasAlpha;
	compressed = format->compressed;
	channels = format->channels;
	bytesPerChannel = format->bytesPerChannel;
	bitsPerChannel = format->bitsPerChannel;
	bytesPerPixel = format->bytesPerPixel;
	bitsPerPixel = format->bitsPerPixel;
	pixelFormat = format->pixelFormat;
}

void ChannelFormat::setColor(bool alpha)
{
	floatMode = true;
	grayscaleMode = false;
	hasAlpha = alpha;
	compressed = true;
	if (alpha)
	{
		colorChannelsFormat = ColorChannelsFormat::RGBA;
		channels = 4;
	}
	else
	{
		colorChannelsFormat = ColorChannelsFormat::RGB;
		channels = 3;
	}
	bytesPerChannel = 4;
	bitsPerChannel = bytesPerChannel * 8;
	bytesPerPixel = channels * bytesPerChannel;
	bitsPerPixel = bytesPerPixel * 8;
}

void ChannelFormat::setGrayscale(bool alpha)
{
	floatMode = true;
	grayscaleMode = true;
	hasAlpha = alpha;
	compressed = true;
	if (alpha)
	{
		colorChannelsFormat = ColorChannelsFormat::IA;
		channels = 2;
	}
	else
	{
		colorChannelsFormat = ColorChannelsFormat::I;
		channels = 1;
	}
	bytesPerChannel = 4;
	bitsPerChannel = bytesPerChannel * 8;
	bytesPerPixel = channels * bytesPerChannel;
	bitsPerPixel = bytesPerPixel * 8;
}

void ChannelFormat::setColorScreen(bool alpha)
{
	if (alpha)
	{
		init(PixelFormat::Format32bppArgb);
	}
	else
	{
		init(PixelFormat::Format24bppRgb);
	}
}

void ChannelFormat::setGrayscaleScreen()
{
	init(PixelFormat::Format16bppGrayScale);	// Format16bppGrayScale not supported for display
}

void ChannelFormat::init(PixelFormat pixelFormat)
{
	this->pixelFormat = pixelFormat;
	grayscaleMode = (pixelFormat == PixelFormat::Format16bppGrayScale);
	hasAlpha = Image::IsAlphaPixelFormat(pixelFormat);
	floatMode = false;	// PixelFormat contains no float formats
	compressed = true;

	if (grayscaleMode)
	{
		if (hasAlpha)
		{
			colorChannelsFormat = ColorChannelsFormat::AI;
			channels = 2;
		}
		else
		{
			colorChannelsFormat = ColorChannelsFormat::I;
			channels = 1;
		}
	}
	else
	{
		if (hasAlpha)
		{
			colorChannelsFormat = ColorChannelsFormat::ARGB;
			channels = 4;
		}
		else
		{
			colorChannelsFormat = ColorChannelsFormat::RGB;
			channels = 3;
		}
	}

	bitsPerPixel = Image::GetPixelFormatSize(pixelFormat);
	if (Image::IsExtendedPixelFormat(pixelFormat))
	{
		bitsPerChannel = 16;
	}
	else
	{
		bitsPerChannel = 8;
	}

	bytesPerPixel = bitsPerPixel / 8;
	bytesPerChannel = bitsPerChannel / 8;
}

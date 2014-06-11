#pragma once

using namespace System::Drawing::Imaging;

public enum class ColorChannelsFormat
{
	None,
	I,
	IA,
	AI,
	RGB,
	BGR,
	ARGB,
	RGBA,
	BGRA
};

public ref class ChannelFormat
{
public:
	bool grayscaleMode;
	bool floatMode;
	ColorChannelsFormat colorChannelsFormat;
	bool hasAlpha;
	bool compressed;
	int channels;
	int bytesPerChannel, bitsPerChannel;
	int bytesPerPixel, bitsPerPixel;
	PixelFormat pixelFormat;

	ChannelFormat();
	ChannelFormat(ChannelFormat^ format);

	void setColor(bool alpha);
	void setGrayscale(bool alpha);
	void setColorScreen(bool alpha);
	void setGrayscaleScreen();
	void init(PixelFormat pixelFormat);
};


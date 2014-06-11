#pragma once

#include "ChannelFormat.h"
#include "FtfFileReader.h"
#include "FtfImageData.h"

using namespace System;
using namespace System::Drawing;
using namespace System::Drawing::Imaging;

public ref class FtfImage
{
public:
	List<FtfImageData^>^ imageDatas;

	bool readError;
	String^ errorMessage;

	static double gammaCorrection = 2.2;

	FtfImage();

	void clear();
	bool readImage(String^ filename);
	bool writeImage(String^ filename);
	bool writeImage(String^ filename, ChannelFormat^ outputFormat);
	String^ getErrorMessage();

	Bitmap^ getBitmap(ChannelFormat^ channelFormat, int imagei);
	array<Byte>^ bufferToBytes(FtfImageData^ imageData, ChannelFormat^ channelFormat, bool floatGammaCorrection, bool reverse);
	Bitmap^ bytesToBitmap(array<Byte>^ byteData, int width, int height, ChannelFormat^ channelFormat);
	void bytesToBuffer(array<Byte>^ byteData, FtfImageData^ imageData, bool floatGammaCorrection, bool reverse);
	String^ getTag(FtfFileReader^ reader, String^ label, bool required);
	int getIntTag(FtfFileReader^ reader, String^ label, bool required);
};

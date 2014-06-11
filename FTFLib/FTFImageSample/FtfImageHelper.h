#pragma once

using namespace System;
using namespace System::Drawing;

ref class FtfImageHelper
{
public:
	FtfImage ftfImage;
	int imagei;

	FtfImageHelper();
	Bitmap^ createImage();
	Bitmap^ readImage(String^ filename);
	bool writeImage(String^ filename);
	String^ getErrorMessage();
};

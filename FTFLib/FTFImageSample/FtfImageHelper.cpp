#include "StdAfx.h"
#include "FtfImageHelper.h"

FtfImageHelper::FtfImageHelper()
{
	imagei = 0;
}

Bitmap^ FtfImageHelper::createImage()
{
	FtfImageData^ imageData;
	int nimages = 2;
	int width = 1000;
	int height = 1000;
	double v, a;

	ftfImage.clear();

	for (int i = 0; i < nimages; i++)
	{
		imageData = gcnew FtfImageData();
		imageData->width = width;
		imageData->height = height;
		imageData->fileFormat->setColor(true);
		imageData->initData();

		for (int y = 0; y < height; y++)
		{
			for (int x = 0; x < width; x++)
			{
				v = (double)(x + y * width) / (width * height);
				a = (double)x / width;
				if (i > 0)
				{
					a = 1 - a;
				}
				imageData->rData[y, x] = 1 - v;
				imageData->gData[y, x] = v;
				imageData->bData[y, x] = 0;
				imageData->aData[y, x] = a;
			}
		}

		ftfImage.imageDatas->Add(imageData);
	}

	imagei = 0;
	ChannelFormat channelFormat;
	channelFormat.setColorScreen(true);
	return ftfImage.getBitmap(%channelFormat, imagei);
}

Bitmap^ FtfImageHelper::readImage(String^ filename)
{
	Bitmap^ bitmap;

	if (ftfImage.readImage(filename))
	{
		imagei = 0;
		ChannelFormat channelFormat;
		channelFormat.setColorScreen(true);
		bitmap = ftfImage.getBitmap(%channelFormat, imagei);
	}
	return bitmap;
}

bool FtfImageHelper::writeImage(String^ filename)
{
	return ftfImage.writeImage(filename);
}

String^ FtfImageHelper::getErrorMessage()
{
	return ftfImage.getErrorMessage();
}

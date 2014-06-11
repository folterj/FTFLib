#pragma once

#include "FtfFile.h"
#include "FtfElement.h"

using namespace System;

public ref class FtfFileWriter : FtfFile
{
private:
	FtfElement^ nextElement;

	bool writeHash();

public:
	bool open(String^ filename);
	bool open(String^ filename, HashAlgorithm^ hashAlgorythm);
	void setGlobalTag(String^ label, String^ content);
	void setElementTag(String^ label, String^ content);
	bool writeElement(array<Byte>^ content);
	bool writeElement(array<Byte>^ content, FtfCompression compression);
	bool close();
};

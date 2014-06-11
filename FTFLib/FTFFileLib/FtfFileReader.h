#pragma once

#include "FtfFile.h"
#include "FtfElement.h"

using namespace System;

public ref class FtfFileReader : FtfFile
{
public:
	bool open(String^ filename);
	String^ getTag(String^ label);
	FtfCompression elementCompression();
	bool elementCompressed();
	array<Byte>^ readElement();
	bool readHash();
	bool close();
};

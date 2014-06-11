#pragma once

#include "FtfHeader.h"
#include "FtfElement.h"

using namespace System;

public ref class FtfContent
{
public:
	static array<Byte>^ fileHeader = gcnew array<Byte>{ 0x46, 0x54, 0x46, 0x4F, 0x52, 0x4D, 0x41, 0x54 };
	static UInt64 endianness = 0x454E4449414E4553;

	FtfHeader globalHeader;

	FtfElement^ currentElement;

	bool reverse;

	FtfContent();
	FtfTag^ getTag(String^ label);
	void setGlobalTag(String^ label, String^ content);
	void setTag(String^ label, String^ content);
	bool readHeader(Stream^ stream);
	bool readElement(Stream^ stream, bool readContent);
	bool writeHeader(Stream^ stream);
	bool writeElement(Stream^ stream, FtfElement^ element);
	FtfElement^ findElement(Stream^ stream, String^ label);
	FtfElement^ findElement(Stream^ stream, String^ label, String^ content);
	array<Byte>^ getCurrentElementContent();
};

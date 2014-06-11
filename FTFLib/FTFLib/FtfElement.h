#pragma once

#include "FtfHeader.h"
#include "FtfTag.h"

public ref class FtfElement
{
public:
	FtfHeader header;
	array<Byte>^ content;

	FtfElement();
	FtfElement(Stream^ stream, bool reverse, bool readContent);
	FtfTag^ getTag(String^ label);
	void setTag(String^ label, String^ content);
	bool read(Stream^ stream, bool reverse, bool readContent);
	bool readElementContent(Stream^ stream);
	bool skipElementContent(Stream^ stream);
	bool write(Stream^ stream);
};

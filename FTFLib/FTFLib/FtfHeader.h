#pragma once

#include "FtfTag.h"

using namespace System;
using namespace System::Collections;
using namespace System::Collections::Generic;
using namespace System::IO;

public ref class FtfHeader
{
public:
	UInt64 tagsSize;
	Dictionary<String^, String^>^ tags;
	UInt64 contentSize;

private:
	UInt64 position;

public:
	FtfHeader();

	void clearTags();
	void setTag(String^ label, String^ content);
	FtfTag^ getTag(String^ label);
	String^ getTags();
	bool read(Stream^ stream, bool reverse);
	bool write(Stream^ stream, UInt64 contentSize);

private:
	String^ readString(Stream^ stream, UInt64 maxPosition);
};

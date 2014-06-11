#pragma once

#include "FtfTag.h"

using namespace System;
using namespace System::IO;
using namespace System::Collections::Generic;

public ref class Util
{
public:
	static array<Byte>^ getBytes(String^ s);
	static UInt64 readUInt64(Stream^ stream, bool reverse);
	static String^ tagListToString(List<FtfTag^>^ tags);
	static double getDouble(array<Byte>^ data, int pos, bool floatMode, int nbytes);
	static array<Byte>^ getBytes(double x, bool floatMode, int nbytes);
	static void copyBytes(array<Byte>^ dest, double x, bool floatMode, int index, int nbytes);
};

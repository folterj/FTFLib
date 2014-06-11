#pragma once

using namespace System;

ref class FtfHelper
{
public:
	static array<Byte>^ readFile(String^ filename);
	static bool writeFile(String^ filename, array<Byte>^ content);
};

#pragma once

using namespace System;

ref class FtfFileHelper
{
public:
	static String^ readInfo(String^ filename);
	static array<Byte>^ readFile(String^ filename);
	static bool writeFile(String^ filename, array<Byte>^ content);
};


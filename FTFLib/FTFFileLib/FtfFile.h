#pragma once

#include "FtfContent.h"

using namespace System;
using namespace System::IO;
using namespace System::Security::Cryptography;

public ref class FtfFile
{
public:
	FtfContent^ ftfContent;
	String^ filename;
	HashAlgorithm^ hashAlgorythm;
	bool useHash, hashDone;
	int hashSize;

	static String^ fileExtension = ".ftf";

	static int bufferSize = 1000000;

	FileStream^ fileStream;
	BufferedStream^ bufferedStream;
	CryptoStream^ cryptoStream;
	Stream^ ioStream;

	FtfFile();
	void reset();
};

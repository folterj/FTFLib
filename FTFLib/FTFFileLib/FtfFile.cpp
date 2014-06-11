#include "StdAfx.h"
#include "FTFFile.h"

FtfFile::FtfFile()
{
	reset();
}

void FtfFile::reset()
{
	ftfContent = gcnew FtfContent();
	filename = "";
	hashAlgorythm = nullptr;
	useHash = false;
	hashDone = false;
	hashSize = 0;
}

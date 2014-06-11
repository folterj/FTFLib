#include "StdAfx.h"
#include "FtfHelper.h"

using namespace System::IO;

array<Byte>^ FtfHelper::readFile(String^ filename)
{
	array<Byte>^ content;
	FtfContent ftfContent;
	FileStream^ fileStream;
	
	try
	{
		fileStream = gcnew FileStream(filename, FileMode::Open);

		ftfContent.readHeader(fileStream);
		ftfContent.readElement(fileStream, true);

		content = ftfContent.getCurrentElementContent();

		fileStream->Close();
	}
	catch (Exception^)
	{
	}
	return content;
}

bool FtfHelper::writeFile(String^ filename, array<Byte>^ content)
{
	bool ok = false;
	FtfContent ftfContent;
	FtfElement ftfElement;
	FileStream^ fileStream;

	try
	{
		fileStream = File::Create(filename);

		ftfContent.setGlobalTag(FtfTag::applicationLabel, "FTFLib");
		ftfContent.writeHeader(fileStream);
		ftfElement.content = content;
		ok = ftfContent.writeElement(fileStream, %ftfElement);

		fileStream->Flush();
		fileStream->Close();
	}
	catch (Exception^)
	{
	}
	return ok;
}

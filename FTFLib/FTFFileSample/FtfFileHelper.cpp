#include "StdAfx.h"
#include "FtfFileHelper.h"

using namespace System::Security::Cryptography;

String^ FtfFileHelper::readInfo(String^ filename)
{
	String^ s = "";
	FtfFileReader reader;
	array<Byte>^ content;

	if (reader.open(filename))
	{
		s += "Global tags:\n" + reader.ftfContent->globalHeader.getTags();
		content = reader.readElement();
		s += "\n\nElement tags:\n" + reader.ftfContent->currentElement->header.getTags();
	}
	reader.close();

	return s;
}

array<Byte>^ FtfFileHelper::readFile(String^ filename)
{
	FtfFileReader reader;
	array<Byte>^ content;
	bool hashOk;

	if (reader.open(filename))
	{
		content = reader.readElement();
	}
	hashOk = reader.readHash();
	reader.close();

	return content;
}

bool FtfFileHelper::writeFile(String^ filename, array<Byte>^ content)
{
	bool ok = false;

	FtfFileWriter writer;
	writer.setGlobalTag(FtfTag::applicationLabel, "FTFFileLib");
	writer.setGlobalTag(FtfTag::elementsLabel, "1");
	if (writer.open(filename, gcnew SHA512Managed()))
	{
		ok = true;
		writer.setElementTag(FtfTag::elementLabel, "0");
		ok &= writer.writeElement(content);
	}
	ok &= writer.close();

	return ok;
}

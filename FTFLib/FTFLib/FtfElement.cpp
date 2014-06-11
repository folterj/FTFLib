#include "StdAfx.h"
#include "FtfElement.h"

FtfElement::FtfElement()
{
}

FtfElement::FtfElement(Stream^ stream, bool reverse, bool readContent)
{
	read(stream, reverse, readContent);
}

FtfTag^ FtfElement::getTag(String^ label)
{
	return header.getTag(label);
}

void FtfElement::setTag(String^ label, String^ content)
{
	header.setTag(label, content);
}

bool FtfElement::read(Stream^ stream, bool reverse, bool readContent)
{
	bool ok = header.read(stream, reverse);

	if (readContent && ok)
	{
		ok = readElementContent(stream);
	}
	return ok;
}

bool FtfElement::readElementContent(Stream^ stream)
{
	try
	{
		content = gcnew array<Byte>((int)header.contentSize);
		stream->Read(content, 0, (int)header.contentSize);
		return true;
	}
	catch(Exception^)
	{
	}
	return false;
}

bool FtfElement::skipElementContent(Stream^ stream)
{
	try
	{
		stream->Seek(header.contentSize, SeekOrigin::Current);
		return true;
	}
	catch(Exception^)
	{
	}
	return false;
}

bool FtfElement::write(Stream^ stream)
{
	try
	{
		header.write(stream, (UInt64)content->Length);
		stream->Write(content, 0, content->Length);
		return true;
	}
	catch (Exception^)
	{
	}
	return false;
}

#include "StdAfx.h"
#include "FtfContent.h"
#include "util.h"

FtfContent::FtfContent()
{
	reverse = false;
}

FtfTag^ FtfContent::getTag(String^ label)
{
	FtfTag^ tag;

	if (currentElement)
	{
		// look in current element header first
		tag = currentElement->getTag(label);
	}
	if (!tag)
	{
		// if not found; look in global header
		tag = globalHeader.getTag(label);
	}
	return tag;
}

void FtfContent::setGlobalTag(String^ label, String^ content)
{
	globalHeader.setTag(label, content);
}

void FtfContent::setTag(String^ label, String^ content)
{
	if (!currentElement)
	{
		currentElement->setTag(label, content);
	}
}

bool FtfContent::readHeader(Stream^ stream)
{
	array<Byte>^ fileHeader0 = gcnew array<Byte>(fileHeader->Length);
	UInt64 endianness0;
	IStructuralEquatable^ equ;

	stream->Read(fileHeader0, 0, fileHeader->Length);
	// check if matching header
	equ = fileHeader;
	if (equ->Equals(fileHeader0, StructuralComparisons::StructuralEqualityComparer))
	{
		// check if size fields need reversing
		endianness0 = Util::readUInt64(stream, false);
		reverse = (endianness0 != endianness);

		globalHeader.read(stream, reverse);

		return true;
	}
	return false;
}

bool FtfContent::readElement(Stream^ stream, bool readContent)
{
	currentElement = gcnew FtfElement(stream, reverse, readContent);
	if (currentElement)
	{
		return true;
	}
	return false;
}

bool FtfContent::writeHeader(Stream^ stream)
{
	try
	{
		stream->Write(fileHeader, 0, fileHeader->Length);
		stream->Write(BitConverter::GetBytes(endianness), 0, sizeof(UInt64));
		return globalHeader.write(stream, 0);
	}
	catch (Exception^)
	{
	}
	return false;
}

bool FtfContent::writeElement(Stream^ stream, FtfElement^ element)
{
	try
	{
		element->write(stream);
		currentElement = element;
		return true;
	}
	catch (Exception^)
	{
	}
	return false;
}

FtfElement^ FtfContent::findElement(Stream^ stream, String^ label)
{
	FtfElement^ foundElement;
	FtfElement^ element = gcnew FtfElement();
	FtfTag^ tag;

	while (stream->Position < stream->Length)
	{
		element->read(stream, reverse, true);
		tag = element->getTag(FtfTag::labelLabel);
		if (tag)
		{
			foundElement = element;
			break;
		}
	}
	return foundElement;
}

FtfElement^ FtfContent::findElement(Stream^ stream, String^ label, String^ content)
{
	FtfElement^ foundElement;
	FtfElement^ element = gcnew FtfElement();
	FtfTag^ tag;

	while (stream->Position < stream->Length)
	{
		element->read(stream, reverse, true);
		tag = element->getTag(FtfTag::labelLabel);
		if (tag)
		{
			if (tag->content == content)
			{
				foundElement = element;
				break;
			}
		}
	}
	return foundElement;
}

array<Byte>^ FtfContent::getCurrentElementContent()
{
	return currentElement->content;
}

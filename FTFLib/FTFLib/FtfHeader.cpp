#include "StdAfx.h"
#include "FtfHeader.h"
#include "Util.h"

FtfHeader::FtfHeader()
{
	tags = gcnew Dictionary<String^, String^>(StringComparer::InvariantCultureIgnoreCase);
	tagsSize = 0;
	contentSize = 0;
	position = 0;
}

void FtfHeader::clearTags()
{
	tags->Clear();
}

void FtfHeader::setTag(String^ label, String^ content)
{
	if (tags->ContainsKey(label))
	{
		tags[label] = content;
	}
	else
	{
		tags->Add(label, content);
	}
}

FtfTag^ FtfHeader::getTag(String^ label)
{
	FtfTag^ tag;
	String^ content = "";

	if (tags->ContainsKey(label))
	{
		tags->TryGetValue(label, content);
		tag = gcnew FtfTag(label, content);
	}
	return tag;
}

String^ FtfHeader::getTags()
{
	String^ s = "";

	for each(KeyValuePair<String^, String^>^ tagKeyValue in tags)
	{
		if (s != "")
		{
			s += "\n";
		}
		s += String::Format("{0} : {1}",tagKeyValue->Key, tagKeyValue->Value);
	}
	return s;
}

bool FtfHeader::read(Stream^ stream, bool reverse)
{
	String^ label;
	String^ content;

	try
	{
		tagsSize = Util::readUInt64(stream, reverse);

		position = 0;
		while (position < tagsSize)
		{
			// read tags until tags size is reached
			label = readString(stream, tagsSize);
			content = readString(stream, tagsSize);
			if (label != "")
			{
				setTag(label, content);
			}
		}

		contentSize = Util::readUInt64(stream, reverse);

		return true;
	}
	catch(Exception^)
	{
	}
	return false;
}

bool FtfHeader::write(Stream^ stream, UInt64 contentSize)
{
	this->contentSize = contentSize;
	tagsSize = 0;
	for each (KeyValuePair<String^, String^>^ tag in tags)
	{
		tagsSize += (UInt64)tag->Key->Length + 1 + (UInt64)tag->Value->Length + 1;
	}

	try
	{
		stream->Write(BitConverter::GetBytes(tagsSize), 0, sizeof(UInt64));

		for each (KeyValuePair<String^, String^>^ tag in tags)
		{
			stream->Write(Util::getBytes(tag->Key), 0, tag->Key->Length + 1);
			stream->Write(Util::getBytes(tag->Value), 0, tag->Value->Length + 1);
		}

		stream->Write(BitConverter::GetBytes(contentSize), 0, sizeof(UInt64));

		return true;
	}
	catch (Exception^)
	{
	}
	return false;
}

String^ FtfHeader::readString(Stream^ stream, UInt64 maxPosition)
{
	String^ s = "";
	Char c = ' ';

	while (c != 0 && position < maxPosition)
	{
		c = (Char)stream->ReadByte();
		position++;
		if (c != 0)
		{
			s += c;
		}
	}
	return s;
}

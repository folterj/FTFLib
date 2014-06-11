#include "StdAfx.h"
#include "FtfTag.h"

FtfTag::FtfTag(String^ label, String^ content)
{
	this->label = label;
	this->content = content;
}

String^ FtfTag::ToString()
{
	String^ s = "";

	if (label != "")
	{
		s = label;
		if (content != "")
		{
			s += ":" + content;
		}
	}
	return s;
}

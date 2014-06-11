#include "StdAfx.h"
#include "Util.h"

using namespace System::Text;
using namespace System::Collections::Generic;

array<Byte>^ Util::getBytes(String^ s)
{
	Encoding^ encoding = UTF8Encoding::Default;
	array<Byte>^ bytes = encoding->GetBytes(s);
	array<Byte>^ bytes2 = gcnew array<Byte>(bytes->Length + 1);

	Array::Copy(bytes, bytes2, bytes->Length);
	bytes2[bytes2->Length - 1] = 0;

	return bytes2;
}

UInt64 Util::readUInt64(Stream^ stream, bool reverse)
{
	array<Byte>^ sizeBuffer = gcnew array<Byte>(sizeof(UInt64));

	stream->Read(sizeBuffer, 0, sizeBuffer->Length);

	if (reverse)
	{
		Array::Reverse(sizeBuffer);
	}
	return BitConverter::ToUInt64(sizeBuffer, 0);
}

String^ Util::tagListToString(List<FtfTag^>^ tags)
{
	String^ s = "";

	for each (FtfTag^ tag in tags)
	{
		if (s != "")
		{
			s += "\n";
		}
		s += tag->ToString();
	}
	return s;
}

double Util::getDouble(array<Byte>^ data, int pos, bool floatMode, int nbytes)
{
	double x;
	UInt64 maxValue = (UInt64)Math::Pow(2, nbytes * 8) - 1;

	if (floatMode)
	{
		// float mode
		if (nbytes == 8)
		{
			x = BitConverter::ToDouble(data, pos);
		}
		else
		{
			x = BitConverter::ToSingle(data, pos);
		}
	}
	else
	{
		// int mode
		switch (nbytes)
		{
			case 8:		x = (double)BitConverter::ToUInt64(data, pos) / maxValue;	break;
			case 4:		x = (double)BitConverter::ToUInt32(data, pos) / maxValue;	break;
			case 2:		x = (double)BitConverter::ToUInt16(data, pos) / maxValue;	break;
			default:	x = (double)data[pos] / maxValue;							break;
		}
	}
	return x;
}

array<Byte>^ Util::getBytes(double x, bool floatMode, int nbytes)
{
	array<Byte>^ data;
	UInt64 maxValue = (UInt64)Math::Pow(2, nbytes * 8) - 1;
		
	if (floatMode)
	{
		// float mode
		if (nbytes == 8)
		{
			data = BitConverter::GetBytes(x);
		}
		else
		{
			data = BitConverter::GetBytes((float)x);
		}
	}
	else
	{
		// int mode
		switch (nbytes)
		{
			case 8:		data = BitConverter::GetBytes((UInt64)(x * maxValue));	break;
			case 4:		data = BitConverter::GetBytes((UInt32)(x * maxValue));	break;
			case 2:		data = BitConverter::GetBytes((UInt16)(x * maxValue));	break;
			default:	data = BitConverter::GetBytes((Byte)(x * maxValue));	break;
		}
	}
	return data;
}

void Util::copyBytes(array<Byte>^ dest, double x, bool floatMode, int index, int nbytes)
{
	Array::Copy(Util::getBytes(x, floatMode, nbytes), 0, dest, index, nbytes);
}

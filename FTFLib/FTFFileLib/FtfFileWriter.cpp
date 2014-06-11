#include "StdAfx.h"
#include "FtfFileWriter.h"

using namespace System::IO::Compression;

bool FtfFileWriter::open(String^ filename)
{
	this->filename = filename;

	try
	{
		fileStream = File::Create(filename);
		bufferedStream = gcnew BufferedStream(fileStream, bufferSize);
		ioStream = bufferedStream;

		ftfContent->writeHeader(ioStream);
		nextElement = gcnew FtfElement();
		return true;
	}
	catch (Exception^)
	{
	}
	return false;
}

bool FtfFileWriter::open(String^ filename, HashAlgorithm^ hashAlgorythm)
{
	String^ hashtype;

	this->filename = filename;
	this->hashAlgorythm = hashAlgorythm;
	useHash = true;

	try
	{
		fileStream = File::Create(filename);
		bufferedStream = gcnew BufferedStream(fileStream, bufferSize);
		cryptoStream = gcnew CryptoStream(bufferedStream, hashAlgorythm, CryptoStreamMode::Write);
		ioStream = cryptoStream;

		if (hashAlgorythm->GetType() == SHA512Managed::typeid)
		{
			hashtype = "SHA512";
		}
		else if (hashAlgorythm->GetType() == SHA384Managed::typeid)
		{
			hashtype = "SHA384";
		}
		else if (hashAlgorythm->GetType() == SHA256Managed::typeid)
		{
			hashtype = "SHA256";
		}
		else if (hashAlgorythm->GetType() == SHA1Managed::typeid)
		{
			hashtype = "SHA1";
		}
		else
		{
			String^ s = hashAlgorythm->ToString();
			array<String^>^ parts = s->Split('.');
			hashtype = parts[parts->Length - 1];
		}

		ftfContent->setGlobalTag(FtfTag::hashtypeLabel, hashtype);

		ftfContent->setGlobalTag(FtfTag::hashsizeLabel, (hashAlgorythm->HashSize / 8).ToString());

		ftfContent->writeHeader(ioStream);
		nextElement = gcnew FtfElement();
		return true;
	}
	catch (Exception^)
	{
	}
	return false;
}

void FtfFileWriter::setGlobalTag(String^ label, String^ content)
{
	ftfContent->setGlobalTag(label, content);
}

void FtfFileWriter::setElementTag(String^ label, String^ content)
{
	nextElement->setTag(label, content);
}

bool FtfFileWriter::writeElement(array<Byte>^ content, FtfCompression compression)
{
	bool ok;

	if (compression != FtfCompression::NONE)
	{
		nextElement->setTag(FtfTag::compressionLabel, compression.ToString());
	}

	if (compression == FtfCompression::DEFLATE)
	{
		// context for MemoryStream
		{
			MemoryStream^ compressedStream = gcnew MemoryStream();

			// context for DeflateStream
			{
				DeflateStream^ zipStream = gcnew DeflateStream(compressedStream, CompressionMode::Compress);

				zipStream->Write(content, 0, content->Length);
				zipStream->Close();
				nextElement->content = compressedStream->ToArray();
			}
		}
	}
	else if (compression == FtfCompression::GZIP)
	{
		// context for MemoryStream
		{
			MemoryStream^ compressedStream = gcnew MemoryStream();

			// context for GZipStream
			{
				GZipStream^ zipStream = gcnew GZipStream(compressedStream, CompressionMode::Compress);

				zipStream->Write(content, 0, content->Length);
				zipStream->Close();
				nextElement->content = compressedStream->ToArray();
			}
		}
	}
	else
	{
		nextElement->content = content;
	}

	ok = ftfContent->writeElement(ioStream, nextElement);
	nextElement = gcnew FtfElement();

	return ok;
}

bool FtfFileWriter::writeElement(array<Byte>^ content)
{
	return writeElement(content, FtfCompression::NONE);
}

bool FtfFileWriter::writeHash()
{
	array<Byte>^ hashBytes;

	try
	{
		if (useHash && !hashDone)
		{
			cryptoStream->FlushFinalBlock();
			hashBytes = hashAlgorythm->Hash;
			ioStream->Write(hashBytes, 0, hashBytes->Length);
			hashDone = true;
		}
		return true;
	}
	catch (Exception^)
	{
	}
	return false;
}

bool FtfFileWriter::close()
{
	bool ok;

	try
	{
		ok = writeHash();

		if (ioStream)
		{
			ioStream->Flush();
		}
		if (bufferedStream)
		{
			bufferedStream->Flush();
		}
		if (fileStream)
		{
			fileStream->Flush();
			fileStream->Close();
		}
	}
	catch (Exception^)
	{
	}
	return ok;
}

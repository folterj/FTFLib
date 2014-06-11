#include "StdAfx.h"
#include "FtfFileReader.h"
#include "FtfTag.h"

using namespace System::IO::Compression;

bool FtfFileReader::open(String^ filename)
{
	FtfTag^ tag;
	String^ hashtype;

	this->filename = filename;

	try
	{
		fileStream = gcnew FileStream(filename, FileMode::Open);
		bufferedStream = gcnew BufferedStream(fileStream, bufferSize);
		ioStream = bufferedStream;
		ftfContent->readHeader(ioStream);

		tag = ftfContent->getTag(FtfTag::hashtypeLabel);
		if (tag)
		{
			useHash = true;
			hashtype = tag->content;
			
			if (hashtype == "SHA512")
			{
				hashAlgorythm = gcnew SHA512Managed();
			}
			else if (hashtype == "SHA384")
			{
				hashAlgorythm = gcnew SHA384Managed();
			}
			else if (hashtype == "SHA256")
			{
				hashAlgorythm = gcnew SHA256Managed();
			}
			else if (hashtype == "SHA1")
			{
				hashAlgorythm = gcnew SHA1Managed();
			}

			tag = ftfContent->getTag(FtfTag::hashsizeLabel);
			if (tag)
			{
				int::TryParse(tag->content, hashSize);
			}
		}
		return true;
	}
	catch (Exception^)
	{
	}
	return false;
}

String^ FtfFileReader::getTag(String^ label)
{
	String^ content;

	FtfTag^ tag = ftfContent->getTag(label);
	if (tag)
	{
		content = tag->content;
	}
	return content;
}

FtfCompression FtfFileReader::elementCompression()
{
	FtfCompression compression = FtfCompression::NONE;
	FtfTag^ tag;

	tag = ftfContent->getTag(FtfTag::compressionLabel);
	if (tag)
	{
		Enum::TryParse(tag->content, true, compression);
	}
	return compression;
}

bool FtfFileReader::elementCompressed()
{
	return (elementCompression() != FtfCompression::NONE);
}

array<Byte>^ FtfFileReader::readElement()
{
	array<Byte>^ outcontent;
	array<Byte>^ content;
	FtfCompression compression = FtfCompression::NONE;

	if (ftfContent->readElement(ioStream, true))
	{
		content = ftfContent->getCurrentElementContent();

		compression = elementCompression();

		if (compression == FtfCompression::DEFLATE)
		{
			// context for MemoryStream
			{
				MemoryStream^ compressedStream = gcnew MemoryStream(content);

				// context for DeflateStream
				{
					DeflateStream^ zipStream = gcnew DeflateStream(compressedStream, CompressionMode::Decompress);

					// context for MemoryStream
					{
						MemoryStream^ resultStream = gcnew MemoryStream();

						zipStream->CopyTo(resultStream);
						outcontent = resultStream->ToArray();
					}
				}
			}
		}
		else if (compression == FtfCompression::GZIP)
		{
			// context for MemoryStream
			{
				MemoryStream^ compressedStream = gcnew MemoryStream(content);

				// context for DeflateStream
				{
					DeflateStream^ zipStream = gcnew DeflateStream(compressedStream, CompressionMode::Decompress);
								
					// context for MemoryStream
					{
						MemoryStream^ resultStream = gcnew MemoryStream();

						zipStream->CopyTo(resultStream);
						outcontent = resultStream->ToArray();
					}
				}
			}
		}
		else
		{
			outcontent = content;
		}
	}

	return outcontent;
}

bool FtfFileReader::readHash()
{
	array<Byte>^ calcHashBytes;
	array<Byte>^ fileHashBytes;
	bool hashOk = true;
	array<Byte>^ data;
	UInt64 dataLen;

	try
	{
		if (useHash && !hashDone && hashAlgorythm)
		{
			// calculate data length
			dataLen = fileStream->Length - hashSize;
			data = gcnew array<Byte>((int)dataLen);
			// reset both streams
			fileStream->Seek(0, SeekOrigin::Begin);
			bufferedStream->Seek(0, SeekOrigin::Begin);
			// create crypto stream on top
			cryptoStream = gcnew CryptoStream(bufferedStream, hashAlgorythm, CryptoStreamMode::Read);
			// re-read until position
			cryptoStream->Read(data, 0, (int)dataLen);

			// can only check hash if all elements are read
			cryptoStream->FlushFinalBlock();

			calcHashBytes = hashAlgorythm->Hash;
			fileHashBytes = gcnew array<Byte>(calcHashBytes->Length);
			if (bufferedStream->Read(fileHashBytes, 0, hashSize) > 0)
			{
				IStructuralEquatable^ eqa1 = calcHashBytes;
				hashOk = eqa1->Equals(fileHashBytes, StructuralComparisons::StructuralEqualityComparer);
			}
			hashDone = true;
		}
		return hashOk;
	}
	catch (Exception^)
	{
	}
	return false;
}

bool FtfFileReader::close()
{
	bool ok;

	try
	{
		ok = readHash();

		if (fileStream)
		{
			fileStream->Close();
		}
	}
	catch (Exception^)
	{
	}
	return ok;
}
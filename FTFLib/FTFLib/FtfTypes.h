#pragma once

public enum class FtfColorModel
{
	NONE,
	GRAYSCALE,
	RGB
};

public enum class FtfColorChannelsFormat
{
	NONE,
	I,
	IA,
	AI,
	RGB,
	BGR,
	ARGB,
	RGBA,
	BGRA
};

public enum class FtfComponentFormat
{
	NONE,
	FP,
	INT
};

public enum class FtfCompression
{
	NONE,
	DEFLATE,
	GZIP
};

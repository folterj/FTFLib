#pragma once

#include "FtfTypes.h"

using namespace System;

public ref class FtfTag
{
public:
	String^ label;
	String^ content;

	// general tags (global)
	static String^ elementsLabel = "ELEMENTS";
	static String^ hashtypeLabel = "HASHTYPE";
	static String^ hashsizeLabel = "HASHSIZE";
	static String^ descriptionLabel = "DESCRIPTION";
	static String^ applicationLabel = "APPLICATION";
	static String^ authorLabel = "AUTHOR";
	static String^ subjectLabel = "SUBJECT";

	// general tags (global / elements)
	static String^ labelLabel = "LABEL";
	static String^ elementLabel = "ELEMENT";
	static String^ timestampLabel = "TIMESTAMP";
	static String^ dimensionsLabel = "DIMENSIONS";

	// specific image tags:
	static String^ widthLabel = "WIDTH";
	static String^ heightLabel = "HEIGHT";
	static String^ channelsLabel = "CHANNELS";
	static String^ colormodelLabel = "COLORMODEL";
	static String^ colorchannelsformatLabel = "COLORCHANNELSFORMAT";
	static String^ componentformatLabel = "COMPONENTFORMAT";
	static String^ componentbitsLabel = "COMPONENTBITS";
	static String^ compressionLabel = "COMPRESSION";
	
	FtfTag(String^ label, String^ content);
	virtual String^ ToString() override;
};

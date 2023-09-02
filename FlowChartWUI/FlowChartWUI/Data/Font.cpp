#include "pch.h"
#include "Font.h"

namespace System
{
	namespace Drawing
	{
		Font::Font()
		{
			Name = L"";
			Size = 8.0f;
			Style = FontStyle::Regular;
			Bold = false;
			Italic = false;
			Underline = false;
			Strikeout = false;
		}
		
		Font::Font(winrt::hstring familyName, float emSize, FontStyle style)
		{
			Name = familyName;
			Size = emSize;
			Style = style;
			Bold = false;
			Italic = false;
			Underline = false;
			Strikeout = false;
		}
	}
}
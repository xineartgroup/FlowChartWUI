#pragma once

#include <string>
#include "FontStyle.h"

namespace System
{
	namespace Drawing
	{
		class Font
		{
		public:
			winrt::hstring Name;
			float Size;
			FontStyle Style;
			bool Bold;
			bool Italic;
			bool Underline;
			bool Strikeout;

			Font();

			Font(winrt::hstring familyName, float emSize, FontStyle style);
		};
	}
}


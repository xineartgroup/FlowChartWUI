#pragma once

#include "PropertyType.h"
#include "PropertyVisibility.h"
#include "Font.h"
#include <vector>

using namespace winrt::Microsoft::UI::Xaml::Media;
using namespace winrt::Microsoft::UI::Xaml::Controls;

namespace FlowChart
{
	namespace Data
	{
		class Utility
		{
		public:
			static winrt::Windows::Foundation::Point MousePosition;
			static int LinkingIndex;
			static int FormWidth;
			static int FormHeight;
			static int CanvasWidth;
			static int CanvasHeight;
			static int SelectedAttributeIndex;
			static int SelectedOperationIndex;
			static int LinkItem;
			static int PADDING;
			static int HALFLINK;
			static int LINKCONNECTOR;
			static double FlowSize;
			static winrt::Windows::UI::Color BrushLinkHover;
			static winrt::Windows::UI::Color BrushAnchor;
			static winrt::Windows::UI::Color BrushLink;
			static winrt::Windows::UI::Color BrushFlow;
			static System::Drawing::Font* GeneralFont;

			static winrt::hstring GetNextName(const winrt::hstring &name);

			static winrt::hstring Display(const winrt::hstring &text, int maxlenght);

			static winrt::Windows::UI::Color HighlightBrush(winrt::Windows::UI::Color color);

			static winrt::hstring GetVisibilityString(PropertyVisibility propertyVisibility);
			
			static winrt::hstring GetPropertyString(PropertyType propertyVisibility);

			static BOOL CALLBACK EnumFontFamiliesExProcA(const ENUMLOGFONTEXA* lpelfe, const NEWTEXTMETRICEXA* lpntme, DWORD FontType, LPARAM lParam);
		};
	}
}

#include "pch.h"
#include "Utility.h"

namespace FlowChart
{
	namespace Data
	{
		winrt::Windows::Foundation::Point Utility::MousePosition;
		int Utility::LinkingIndex = -1;
		int Utility::FormWidth = 1000;
		int Utility::FormHeight = 700;
		int Utility::CanvasWidth = 720;
		int Utility::CanvasHeight = 600;
		int Utility::SelectedAttributeIndex = -1;
		int Utility::SelectedOperationIndex = -1;
		int Utility::LinkItem = -1;
		int Utility::PADDING = 2;
		int Utility::HALFLINK = 5;
		int Utility::LINKCONNECTOR = 5;
		double Utility::FlowSize = 1.0;
		winrt::Windows::UI::Color Utility::BrushLinkHover = winrt::Windows::UI::Colors::White();
		winrt::Windows::UI::Color Utility::BrushAnchor = winrt::Windows::UI::Colors::Orange();
		winrt::Windows::UI::Color Utility::BrushLink = winrt::Windows::UI::Colors::Yellow();
		winrt::Windows::UI::Color Utility::BrushFlow = winrt::Windows::UI::Colors::Blue();
		System::Drawing::Font* Utility::GeneralFont = new System::Drawing::Font(L"Arial", 8.0f, System::Drawing::FontStyle::Regular);
		std::vector<winrt::hstring> names = std::vector<winrt::hstring>();

		winrt::hstring Utility::GetNextName(const winrt::hstring& name)
		{
			int count = 0;

			for (int i = 0; i < names.size(); i++)
			{
				if (name + winrt::to_hstring(count) == names[i])
				{
					count++;
				}
			}

			names.push_back(name + winrt::to_hstring(count));

			return name + winrt::to_hstring(count);
		}

		winrt::hstring Utility::Display(const winrt::hstring& text, int maxlenght)
		{
			//if (text.size() > maxlenght)
			//	return text.substr(0, maxlenght - 3) + "...";
			return text;
		}

		winrt::Windows::UI::Color Utility::HighlightBrush(winrt::Windows::UI::Color color)
		{
			color.R = static_cast<unsigned char>(color.R + 32 < 255 ? color.R + 32 : 255);
			color.G = static_cast<unsigned char>(color.G + 32 < 255 ? color.G + 32 : 255);
			color.B = static_cast<unsigned char>(color.B + 32 < 255 ? color.B + 32 : 255);
			return (color);
		}

		winrt::hstring Utility::GetVisibilityString(PropertyVisibility propertyVisibility)
		{
			if (propertyVisibility == Public)
				return L"+";
			else if (propertyVisibility == Private)
				return L"-";
			else
				return L"#";
		}

		winrt::hstring Utility::GetPropertyString(PropertyType propertyType)
		{
			if (propertyType == Void)
				return L"";
			else if (propertyType == Boolean)
				return L"Boolean";
			else if (propertyType == Integer)
				return L"Integer";
			else if (propertyType == Float)
				return L"Float";
			else if (propertyType == String)
				return L"String";
			else if (propertyType == Enumeration)
				return L"Enumeration";
			else if (propertyType == Entity)
				return L"Entity";
			else
				return L"";
		}

		BOOL CALLBACK Utility::EnumFontFamiliesExProcA(const ENUMLOGFONTEXA* lpelfe, const NEWTEXTMETRICEXA* lpntme, DWORD FontType, LPARAM lParam)
		{
			std::vector<winrt::hstring>* fonts = reinterpret_cast<std::vector<winrt::hstring>*>(lParam);
			fonts->push_back(winrt::to_hstring(lpelfe->elfLogFont.lfFaceName));
			return TRUE;
		}
	}
}

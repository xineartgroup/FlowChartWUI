#pragma once

#include "AnchorPoint.h"
#include "ItemProperty.h"
#include "Font.h"

#include "winrt/Microsoft.UI.Xaml.h"
#include <winrt/impl/Windows.UI.Xaml.Media.2.h>
using namespace winrt::Microsoft::UI::Xaml::Media;
using namespace winrt::Microsoft::UI::Xaml::Controls;

namespace FlowChart
{
	namespace Data
	{
		class ISymbol
		{
		public:
			virtual const winrt::hstring &getName() const = 0;
			virtual void setName(const winrt::hstring&) = 0;

			virtual const winrt::hstring &getCaption() const = 0;
			virtual void setCaption(const winrt::hstring&) = 0;

			virtual const bool &getIsSelected() const = 0;
			virtual void setIsSelected(const bool&) = 0;

			virtual const bool &getIsHover() const = 0;
			virtual void setIsHover(const bool&) = 0;

			virtual const bool &getIsEditing() const = 0;
			virtual void setIsEditing(const bool&) = 0;

			virtual winrt::hstring getIconName() = 0;

			virtual const winrt::Windows::UI::Color &getLineColor() const = 0;
			virtual void setLineColor(const winrt::Windows::UI::Color&) = 0;

			virtual const winrt::Windows::UI::Color &getFillColor() const = 0;
			virtual void setFillColor(const winrt::Windows::UI::Color&) = 0;

			virtual const winrt::Windows::UI::Color &getFontColor() const = 0;
			virtual void setFontColor(const winrt::Windows::UI::Color&) = 0;

			virtual const System::Drawing::Font &getTextFont() const = 0;
			virtual void setTextFont(const System::Drawing::Font&) = 0;

			virtual bool IsHit() = 0;

			virtual int InputAnchorHit() = 0;

			virtual int OutputAnchorHit() = 0;

			virtual float GetWidth() = 0;

			virtual float GetHeight() = 0;

			virtual void Draw(Canvas) = 0;

			virtual void SetPosition(float, float) = 0;

			virtual winrt::Windows::Foundation::Point GetPosition() = 0;

			virtual std::vector<AnchorPoint*> GetInputAnchorPoints() = 0;

			virtual std::vector<AnchorPoint*> GetOutputAnchorPoints() = 0;

			virtual AnchorPoint* GetInputAnchorPoint(int) = 0;

			virtual AnchorPoint* GetOutputAnchorPoint(int) = 0;

			virtual ItemProperty GetProperty(int) = 0;

			virtual void SetProperty(int, ItemProperty) = 0;

			virtual int GetPropertyCount() = 0;

			virtual winrt::hstring GetString() = 0;

			virtual winrt::hstring GetTypeString() = 0;
		};
	}
}

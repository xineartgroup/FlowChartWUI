#pragma once

#include "ISymbolChart.h"
#include "ItemProperty.h"
#include "Utility.h"
#include "AnchorPoint.h"
#include "LinkAnchorPlacement.h"
#include <string>
#include <vector>

namespace FlowChart
{
	namespace Data
	{
		class SymbolMerge : public ISymbolChart
		{
		private:
			float height;
			float width;
			float xPos;
			float yPos;
			ItemProperty properties[1];
			std::vector<AnchorPoint*> inputAnchoPoints = std::vector<AnchorPoint*>();
			std::vector<AnchorPoint*> outputAnchoPoints = std::vector<AnchorPoint*>();

				winrt::hstring privateName;
			public:
				const winrt::hstring &getName() const;
				void setName(const winrt::hstring &value);

			private:
				winrt::hstring privateCaption;
			public:
				const winrt::hstring &getCaption() const;
				void setCaption(const winrt::hstring &value);

			private:
				bool privateIsSelected;
			public:
				const bool &getIsSelected() const;
				void setIsSelected(const bool &value);

			private:
				bool privateIsHover;
			public:
				const bool &getIsHover() const;
				void setIsHover(const bool &value);

			private:
				bool privateIsEditing;
			public:
				const bool &getIsEditing() const;
				void setIsEditing(const bool &value);

			winrt::hstring getIconName();

			private:
				winrt::Windows::UI::Color privateLineColor;
			public:
				const winrt::Windows::UI::Color &getLineColor() const;
				void setLineColor(const winrt::Windows::UI::Color& value);

			private:
				winrt::Windows::UI::Color privateFillColor;
			public:
				const winrt::Windows::UI::Color &getFillColor() const;
				void setFillColor(const winrt::Windows::UI::Color &value);

			private:
				winrt::Windows::UI::Color privateFontColor;
			public:
				const winrt::Windows::UI::Color &getFontColor() const;
				void setFontColor(const winrt::Windows::UI::Color &value);

			private:
				System::Drawing::Font privateTextFont;
			public:
				const System::Drawing::Font &getTextFont() const;
				void setTextFont(const System::Drawing::Font &value);

			SymbolMerge();

			bool IsHit();

			int InputAnchorHit();

			int OutputAnchorHit();

			float GetWidth();

			float GetHeight();

			void Draw(Canvas canvas);

			void SetPosition(float x, float y);

			winrt::Windows::Foundation::Point GetPosition();

			std::vector<AnchorPoint*> GetInputAnchorPoints();

			std::vector<AnchorPoint*> GetOutputAnchorPoints();

			AnchorPoint* GetInputAnchorPoint(int anchorIndex);

			AnchorPoint* GetOutputAnchorPoint(int OutputAnchorIndex);

			ItemProperty GetProperty(int index);

			void SetProperty(int index, ItemProperty property_Renamed);

			int GetPropertyCount();

			ISymbolChart *GetInstance();

			ISymbolChart *GetDuplicate();

			void RotateAnchorPoints();

			winrt::hstring GetString();

			winrt::hstring GetTypeString();

			virtual winrt::hstring ToString();
		};
	}
}

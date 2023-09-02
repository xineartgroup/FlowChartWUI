#pragma once

#include "ISymbolClass.h"
#include "ItemProperty.h"
#include "Link.h"
#include "Settings.h"
#include "PropertyType.h"
#include "PropertyVisibility.h"
#include "AnchorPoint.h"
#include "LinkAnchorPlacement.h"
#include <string>
#include <vector>

namespace FlowChart
{
	namespace Data
	{
		class SymbolClass : public ISymbolClass
		{
		private:
			float headHeight;
			float bodyHeight;
			float width;
			float xPos;
			float yPos;
			ItemProperty properties[1];
			std::vector<AnchorPoint*> inputAnchoPoints = std::vector<AnchorPoint*>();
			std::vector<AnchorPoint*> outputAnchoPoints = std::vector<AnchorPoint*>();
			std::vector<ItemProperty> attributes;
			std::vector<ItemProperty> operations;

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

			private:
				std::vector<Link*> privateLinksToNextSymbols;
			public:
				const std::vector<Link*> &getLinksToNextSymbols() const;
				void setLinksToNextSymbols(const std::vector<Link*> &value);

			SymbolClass();

			bool IsHit();

			int AttributeHit();

			int OperationHit();

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

			void AddAttribute(ItemProperty property_Renamed);

			ItemProperty GetSelectedAttribute();

			void UpdateSelectedAttribute(ItemProperty property_Renamed);

			void RemoveSelectedAttribute();

			int GetAttributeCount();

			void AddOperation(ItemProperty property_Renamed);

			ItemProperty GetSelectedOperation();

			void UpdateSelectedOperation(ItemProperty property_Renamed);

			void RemoveSelectedOperation();

			int GetOperationCount();

			ISymbolClass *GetInstance();

			ISymbolClass *GetDuplicate();

			winrt::hstring GetString();

			winrt::hstring GetTypeString();
		};
	}
}

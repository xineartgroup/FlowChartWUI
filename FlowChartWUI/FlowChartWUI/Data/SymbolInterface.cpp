#include "pch.h"
#include "SymbolInterface.h"

namespace FlowChart
{
	namespace Data
	{

		const winrt::hstring &SymbolInterface::getName() const
		{
			return privateName;
		}

		void SymbolInterface::setName(const winrt::hstring &value)
		{
			privateName = value;
		}

		const winrt::hstring &SymbolInterface::getCaption() const
		{
			return privateCaption;
		}

		void SymbolInterface::setCaption(const winrt::hstring &value)
		{
			privateCaption = value;
		}

		const bool &SymbolInterface::getIsSelected() const
		{
			return privateIsSelected;
		}

		void SymbolInterface::setIsSelected(const bool &value)
		{
			privateIsSelected = value;
		}

		const bool &SymbolInterface::getIsHover() const
		{
			return privateIsHover;
		}

		void SymbolInterface::setIsHover(const bool &value)
		{
			privateIsHover = value;
		}

		const bool &SymbolInterface::getIsEditing() const
		{
			return privateIsEditing;
		}

		void SymbolInterface::setIsEditing(const bool &value)
		{
			privateIsEditing = value;
		}

		winrt::hstring SymbolInterface::getIconName()
		{
			return L"imgInterface.png";
		}

		const winrt::Windows::UI::Color &SymbolInterface::getLineColor() const
		{
			return privateLineColor;
		}

		void SymbolInterface::setLineColor(const winrt::Windows::UI::Color& value)
		{
			privateLineColor = value;
		}

		const winrt::Windows::UI::Color &SymbolInterface::getFillColor() const
		{
			return privateFillColor;
		}

		void SymbolInterface::setFillColor(const winrt::Windows::UI::Color &value)
		{
			privateFillColor = value;
		}

		const winrt::Windows::UI::Color &SymbolInterface::getFontColor() const
		{
			return privateFontColor;
		}

		void SymbolInterface::setFontColor(const winrt::Windows::UI::Color &value)
		{
			privateFontColor = value;
		}

		const System::Drawing::Font &SymbolInterface::getTextFont() const
		{
			return privateTextFont;
		}

		void SymbolInterface::setTextFont(const System::Drawing::Font &value)
		{
			privateTextFont = value;
		}

		SymbolInterface::SymbolInterface()
		{
			headHeight = 25;
			bodyHeight = 20;
			width = 120;
			xPos = 0.0f;
			yPos = 0.0f;
			attributes = std::vector<ItemProperty>();
			operations = std::vector<ItemProperty>();

			setName(Utility::GetNextName(GetString()));
			setCaption(getName());

			setLineColor(winrt::Windows::UI::Colors::Black());
			setFillColor(winrt::Windows::UI::Colors::SkyBlue());
			setFontColor(winrt::Windows::UI::Colors::Black());
			setTextFont(System::Drawing::Font(L"Arial", 8.0f, System::Drawing::FontStyle::Regular));
			GetOutputAnchorPoints();
		}

		bool SymbolInterface::IsHit()
		{
			return (Utility::MousePosition.X >= GetPosition().X && Utility::MousePosition.X <= GetPosition().X + GetWidth() && Utility::MousePosition.Y >= GetPosition().Y && Utility::MousePosition.Y <= GetPosition().Y + GetHeight());
		}

		int SymbolInterface::AttributeHit()
		{
			for (int i = 0; i < attributes.size(); i++)
			{
				float offsetY = GetPosition().Y + headHeight + (bodyHeight * i);
				if (Utility::MousePosition.X >= GetPosition().X && Utility::MousePosition.X <= GetPosition().X + GetWidth() && Utility::MousePosition.Y >= offsetY && Utility::MousePosition.Y <= offsetY + bodyHeight)
				{
					return i;
				}
			}
			return -1;
		}

		int SymbolInterface::OperationHit()
		{
			for (int i = 0; i < operations.size(); i++)
			{
				float offsetY = GetPosition().Y + headHeight + (bodyHeight * (attributes.size() + i));
				if (Utility::MousePosition.X >= GetPosition().X && Utility::MousePosition.X <= GetPosition().X + GetWidth() && Utility::MousePosition.Y >= offsetY && Utility::MousePosition.Y <= offsetY + bodyHeight)
				{
					return i;
				}
			}
			return -1;
		}

		int SymbolInterface::InputAnchorHit()
		{
			std::vector<AnchorPoint*> list = GetInputAnchorPoints();

			for (int i = 0; i < list.size(); i++)
			{
				if (Utility::MousePosition.X >= list[i]->getPosition().X - (Utility::LINKCONNECTOR / 2) && Utility::MousePosition.X <= list[i]->getPosition().X + (Utility::LINKCONNECTOR / 2) && Utility::MousePosition.Y >= list[i]->getPosition().Y - (Utility::LINKCONNECTOR / 2) && Utility::MousePosition.Y <= list[i]->getPosition().Y + (Utility::LINKCONNECTOR / 2))
				{
					return i;
				}
			}

			return -1;
		}

		int SymbolInterface::OutputAnchorHit()
		{
			std::vector<AnchorPoint*> list = GetOutputAnchorPoints();

			for (int i = 0; i < list.size(); i++)
			{
				if (Utility::MousePosition.X >= list[i]->getPosition().X - (Utility::LINKCONNECTOR / 2) && Utility::MousePosition.X <= list[i]->getPosition().X + (Utility::LINKCONNECTOR / 2) && Utility::MousePosition.Y >= list[i]->getPosition().Y - (Utility::LINKCONNECTOR / 2) && Utility::MousePosition.Y <= list[i]->getPosition().Y + (Utility::LINKCONNECTOR / 2))
				{
					return i;
				}
			}

			return -1;
		}

		float SymbolInterface::GetWidth()
		{
			return width;
		}

		float SymbolInterface::GetHeight()
		{
			return headHeight + (bodyHeight * attributes.size()) + (bodyHeight * operations.size());
		}

		void SymbolInterface::Draw(Canvas canvas)
		{
			//header section
			RectangleGeometry myRectangleGeometry1;
			myRectangleGeometry1.Rect(winrt::Windows::Foundation::Rect(GetPosition().X, GetPosition().Y, GetWidth(), headHeight));

			winrt::Microsoft::UI::Xaml::Shapes::Path path1;
			path1.Fill(SolidColorBrush(getIsSelected() || getIsHover() ? Utility::HighlightBrush(getFillColor()) : getFillColor()));
			path1.Stroke(SolidColorBrush(getLineColor()));
			path1.StrokeThickness(getIsSelected() ? 1.0 : 0.5);
			path1.Data(myRectangleGeometry1);

			canvas.Children().Append(path1);

			TextBlock textBlock;
			textBlock.Text(winrt::to_hstring(getCaption()));
			textBlock.FontFamily(FontFamily(winrt::to_hstring(getTextFont().Name)));
			textBlock.FontSize(getTextFont().Size * 96.0 / 72.0);
			textBlock.FontWeight(getTextFont().Bold ? winrt::Windows::UI::Text::FontWeights::Bold() : winrt::Windows::UI::Text::FontWeights::Normal());
			textBlock.FontStyle(getTextFont().Italic ? winrt::Windows::UI::Text::FontStyle::Italic : winrt::Windows::UI::Text::FontStyle::Normal);
			textBlock.TextDecorations(getTextFont().Underline ? winrt::Windows::UI::Text::TextDecorations::Underline : winrt::Windows::UI::Text::TextDecorations::None);
			textBlock.TextDecorations(getTextFont().Strikeout ? winrt::Windows::UI::Text::TextDecorations::Strikethrough | textBlock.TextDecorations() : textBlock.TextDecorations());
			textBlock.Foreground(SolidColorBrush(getFontColor()));
			textBlock.TextAlignment(winrt::Microsoft::UI::Xaml::TextAlignment::Center);
			textBlock.Width(GetWidth());
			Canvas::SetLeft(textBlock, GetPosition().X);
			Canvas::SetTop(textBlock, (GetPosition().Y + (headHeight / 2)) - (10.0 / 2));
			canvas.Children().Append(textBlock);

			//attributes section
			RectangleGeometry myRectangleGeometry2;
			myRectangleGeometry2.Rect(winrt::Windows::Foundation::Rect(GetPosition().X, GetPosition().Y + headHeight, GetWidth(), bodyHeight * attributes.size()));

			winrt::Microsoft::UI::Xaml::Shapes::Path path2;
			path2.Fill(SolidColorBrush(getIsSelected() || getIsHover() ? Utility::HighlightBrush(getFillColor()) : getFillColor()));
			path2.Stroke(SolidColorBrush(getLineColor()));
			path2.StrokeThickness(getIsSelected() ? 1.0 : 0.5);
			path2.Data(myRectangleGeometry2);

			canvas.Children().Append(path2);

			for (int i = 0; i < attributes.size(); i++)
			{
				float y = headHeight + (bodyHeight * i) + (bodyHeight / 2.0f);

				TextBlock textBlock1;
				textBlock1.Text(winrt::to_hstring(Utility::GetVisibilityString(attributes[i].getPropertyVisibility()) + L" " + attributes[i].getName() + L" : " + Utility::GetPropertyString(attributes[i].getPropertyType())));
				textBlock1.FontFamily(FontFamily(winrt::to_hstring(getTextFont().Name)));
				textBlock1.FontSize(getTextFont().Size); //TextFont.Size * 96.0 / 72.0;
				textBlock1.FontWeight(getTextFont().Bold ? winrt::Windows::UI::Text::FontWeights::Bold() : winrt::Windows::UI::Text::FontWeights::Normal());
				textBlock1.FontStyle(getTextFont().Italic ? winrt::Windows::UI::Text::FontStyle::Italic : winrt::Windows::UI::Text::FontStyle::Normal);
				textBlock1.TextDecorations(getTextFont().Underline ? winrt::Windows::UI::Text::TextDecorations::Underline : winrt::Windows::UI::Text::TextDecorations::None);
				textBlock1.TextDecorations(getTextFont().Strikeout ? winrt::Windows::UI::Text::TextDecorations::Strikethrough : winrt::Windows::UI::Text::TextDecorations::None);
				textBlock1.Foreground(SolidColorBrush((Utility::SelectedAttributeIndex == i) ? winrt::Windows::UI::Colors::White() : getFontColor()));
				textBlock1.TextAlignment(winrt::Microsoft::UI::Xaml::TextAlignment::Center);
				textBlock1.Width(GetWidth());
				Canvas::SetLeft(textBlock1, GetPosition().X);
				Canvas::SetTop(textBlock1, GetPosition().Y + y - (10.0 / 2));
				canvas.Children().Append(textBlock1);
			}

			//operations section
			RectangleGeometry myRectangleGeometry3;
			myRectangleGeometry3.Rect(winrt::Windows::Foundation::Rect(GetPosition().X, GetPosition().Y + headHeight + (attributes.size() * bodyHeight), GetWidth(), bodyHeight * operations.size()));

			winrt::Microsoft::UI::Xaml::Shapes::Path path3;
			path3.Fill(SolidColorBrush(getIsSelected() || getIsHover() ? Utility::HighlightBrush(getFillColor()) : getFillColor()));
			path3.Stroke(SolidColorBrush(getLineColor()));
			path3.StrokeThickness(getIsSelected() ? 1.0 : 0.5);
			path3.Data(myRectangleGeometry3);

			canvas.Children().Append(path3);

			for (int i = 0; i < operations.size(); i++)
			{
				float y = headHeight + (bodyHeight * (attributes.size() + i)) + (bodyHeight / 2.0f);

				TextBlock textBlock1;
				textBlock1.Text(winrt::to_hstring(Utility::GetVisibilityString(operations[i].getPropertyVisibility()) + L" " + operations[i].getName() + L"() : " + operations[i].getPropertyType()));
				textBlock1.FontFamily(FontFamily(winrt::to_hstring(getTextFont().Name)));
				textBlock1.FontSize(getTextFont().Size); //TextFont.Size * 96.0 / 72.0;
				textBlock1.FontWeight(getTextFont().Bold ? winrt::Windows::UI::Text::FontWeights::Bold() : winrt::Windows::UI::Text::FontWeights::Normal());
				textBlock1.FontStyle(getTextFont().Italic ? winrt::Windows::UI::Text::FontStyle::Italic : winrt::Windows::UI::Text::FontStyle::Normal);
				textBlock1.TextDecorations(getTextFont().Underline ? winrt::Windows::UI::Text::TextDecorations::Underline : winrt::Windows::UI::Text::TextDecorations::None);
				textBlock1.TextDecorations(getTextFont().Strikeout ? winrt::Windows::UI::Text::TextDecorations::Strikethrough : winrt::Windows::UI::Text::TextDecorations::None);
				textBlock1.Foreground(SolidColorBrush((Utility::SelectedOperationIndex == i) ? winrt::Windows::UI::Colors::White() : getFontColor()));
				textBlock1.TextAlignment(winrt::Microsoft::UI::Xaml::TextAlignment::Center);
				textBlock1.Width(GetWidth());
				Canvas::SetLeft(textBlock1, GetPosition().X);
				Canvas::SetTop(textBlock1, GetPosition().Y + y - (10.0 / 2));
				canvas.Children().Append(textBlock1);
			}
		}

		void SymbolInterface::SetPosition(float x, float y)
		{
			xPos = x;
			yPos = y;
		}

		winrt::Windows::Foundation::Point SymbolInterface::GetPosition()
		{
			return winrt::Windows::Foundation::Point(xPos, yPos);
		}

		std::vector<AnchorPoint*> SymbolInterface::GetInputAnchorPoints()
		{
			std::vector<AnchorPoint*> list = std::vector<AnchorPoint*>();

			float offsetY = (headHeight / 2.0f);
			offsetY = offsetY / GetHeight();
			list.push_back(new AnchorPoint(0.0f, offsetY, GetPosition(), GetWidth(), GetHeight(), Left));
			list.push_back(new AnchorPoint(1.0f, offsetY, GetPosition(), GetWidth(), GetHeight(), Right));

			for (int i = 0; i < attributes.size(); i++)
			{
				if (attributes[i].getPropertyType() == Entity)
				{
					offsetY = headHeight + (bodyHeight * i) + (bodyHeight / 2.0f);
					offsetY = offsetY / GetHeight();
					list.push_back(new AnchorPoint(0.0f, offsetY, GetPosition(), GetWidth(), GetHeight(), Left));
					list.push_back(new AnchorPoint(1.0f, offsetY, GetPosition(), GetWidth(), GetHeight(), Right));
				}
			}

			for (int i = 0; i < operations.size(); i++)
			{
				if (operations[i].getPropertyType() == Entity)
				{
					offsetY = headHeight + (bodyHeight * (attributes.size() + i)) + (bodyHeight / 2.0f);
					offsetY = offsetY / GetHeight();
					list.push_back(new AnchorPoint(0.0f, offsetY, GetPosition(), GetWidth(), GetHeight(), Left));
					list.push_back(new AnchorPoint(1.0f, offsetY, GetPosition(), GetWidth(), GetHeight(), Right));
				}
			}

			list.push_back(new AnchorPoint(0.5f, 0.0f, GetPosition(), GetWidth(), GetHeight(), Top));
			list.push_back(new AnchorPoint(0.5f, 1.0f, GetPosition(), GetWidth(), GetHeight(), Bottom));

			return list;
		}

		std::vector<AnchorPoint*> SymbolInterface::GetOutputAnchorPoints()
		{
			std::vector<AnchorPoint*> list = GetInputAnchorPoints();

			return list;
		}

		AnchorPoint* SymbolInterface::GetInputAnchorPoint(int anchorIndex)
		{
			std::vector<AnchorPoint*> list = GetInputAnchorPoints();

			if (anchorIndex >= 0 && anchorIndex < list.size())
				return list[anchorIndex];

			return 0;
		}

		AnchorPoint* SymbolInterface::GetOutputAnchorPoint(int OutputAnchorIndex)
		{
			std::vector<AnchorPoint*> list = GetOutputAnchorPoints();

			if (OutputAnchorIndex >= 0 && OutputAnchorIndex < list.size())
				return list[OutputAnchorIndex];

			return 0;
		}

		ItemProperty SymbolInterface::GetProperty(int index)
		{
			if (GetPropertyCount() > index && index >= 0)
			{
				return properties[index];
			}
			return ItemProperty();
		}

		void SymbolInterface::SetProperty(int index, ItemProperty property_Renamed)
		{
			if (GetPropertyCount() > index && index >= 0)
			{
				properties[index] = property_Renamed;
			}
		}

		int SymbolInterface::GetPropertyCount()
		{
			return 0;
		}

		void SymbolInterface::AddAttribute(ItemProperty property_Renamed)
		{
			attributes.push_back(property_Renamed);
			Utility::SelectedAttributeIndex = (int)attributes.size() - 1;
			Utility::SelectedOperationIndex = -1;
		}

		ItemProperty SymbolInterface::GetSelectedAttribute()
		{
			if (attributes.size() > Utility::SelectedAttributeIndex && Utility::SelectedAttributeIndex >= 0)
			{
				return attributes[Utility::SelectedAttributeIndex];
			}
			return ItemProperty();
		}

		void SymbolInterface::UpdateSelectedAttribute(ItemProperty property_Renamed)
		{
			if (attributes.size() > Utility::SelectedAttributeIndex && Utility::SelectedAttributeIndex >= 0)
			{
				attributes[Utility::SelectedAttributeIndex] = property_Renamed;
			}
		}

		void SymbolInterface::RemoveSelectedAttribute()
		{
			if (attributes.size() > Utility::SelectedAttributeIndex && Utility::SelectedAttributeIndex >= 0)
			{
				attributes.erase(attributes.begin() + Utility::SelectedAttributeIndex);
				Utility::SelectedAttributeIndex = -1;
			}
		}

		int SymbolInterface::GetAttributeCount()
		{
			return (int)attributes.size();
		}

		void SymbolInterface::AddOperation(ItemProperty property_Renamed)
		{
			operations.push_back(property_Renamed);
			Utility::SelectedAttributeIndex = -1;
			Utility::SelectedOperationIndex = (int)operations.size() - 1;
		}

		ItemProperty SymbolInterface::GetSelectedOperation()
		{
			if (operations.size() > Utility::SelectedOperationIndex && Utility::SelectedOperationIndex >= 0)
			{
				return operations[Utility::SelectedOperationIndex];
			}
			return ItemProperty();
		}

		void SymbolInterface::UpdateSelectedOperation(ItemProperty property_Renamed)
		{
			if (operations.size() > Utility::SelectedOperationIndex && Utility::SelectedOperationIndex >= 0)
			{
				operations[Utility::SelectedOperationIndex] = property_Renamed;
			}
		}

		void SymbolInterface::RemoveSelectedOperation()
		{
			if (operations.size() > Utility::SelectedOperationIndex && Utility::SelectedOperationIndex >= 0)
			{
				operations.erase(operations.begin() + Utility::SelectedOperationIndex);
				Utility::SelectedOperationIndex = -1;
			}
		}

		int SymbolInterface::GetOperationCount()
		{
			return (int)operations.size();
		}

		FlowChart::Data::ISymbolClass *SymbolInterface::GetInstance()
		{
			return new SymbolInterface();
		}

		FlowChart::Data::ISymbolClass *SymbolInterface::GetDuplicate()
		{
			SymbolInterface *duplictate = new SymbolInterface();

			for (int i = 0; i < GetPropertyCount(); i++)
				duplictate->properties[i] = properties[i];
			duplictate->attributes = attributes;
			duplictate->operations = operations;
			
			return duplictate;
		}

		winrt::hstring SymbolInterface::GetString()
		{
			return L"Interface";
		}

		winrt::hstring SymbolInterface::GetTypeString()
		{
			return L"InterfaceSymbol";
		}
	}
}

#include "pch.h"
#include "SymbolData.h"

namespace FlowChart
{
	namespace Data
	{

		const winrt::hstring &SymbolData::getName() const
		{
			return privateName;
		}

		void SymbolData::setName(const winrt::hstring &value)
		{
			privateName = value;
		}

		const winrt::hstring &SymbolData::getCaption() const
		{
			return privateCaption;
		}

		void SymbolData::setCaption(const winrt::hstring &value)
		{
			privateCaption = value;
		}

		const bool &SymbolData::getIsSelected() const
		{
			return privateIsSelected;
		}

		void SymbolData::setIsSelected(const bool &value)
		{
			privateIsSelected = value;
		}

		const bool &SymbolData::getIsHover() const
		{
			return privateIsHover;
		}

		void SymbolData::setIsHover(const bool &value)
		{
			privateIsHover = value;
		}

		const bool &SymbolData::getIsEditing() const
		{
			return privateIsEditing;
		}

		void SymbolData::setIsEditing(const bool &value)
		{
			privateIsEditing = value;
		}

		winrt::hstring SymbolData::getIconName()
		{
			return L"imgData.png";
		}

		const winrt::Windows::UI::Color &SymbolData::getLineColor() const
		{
			return privateLineColor;
		}

		void SymbolData::setLineColor(const winrt::Windows::UI::Color& value)
		{
			privateLineColor = value;
		}

		const winrt::Windows::UI::Color &SymbolData::getFillColor() const
		{
			return privateFillColor;
		}

		void SymbolData::setFillColor(const winrt::Windows::UI::Color &value)
		{
			privateFillColor = value;
		}

		const winrt::Windows::UI::Color &SymbolData::getFontColor() const
		{
			return privateFontColor;
		}

		void SymbolData::setFontColor(const winrt::Windows::UI::Color &value)
		{
			privateFontColor = value;
		}

		const System::Drawing::Font &SymbolData::getTextFont() const
		{
			return privateTextFont;
		}

		void SymbolData::setTextFont(const System::Drawing::Font &value)
		{
			privateTextFont = value;
		}

		SymbolData::SymbolData()
		{
			height = 40;
			width = 150;
			xPos = 0.0f;
			yPos = 0.0f;

			setName(Utility::GetNextName(GetString()));
			setCaption(getName());

			setLineColor(winrt::Windows::UI::Colors::Black());
			setFillColor(winrt::Windows::UI::Colors::SkyBlue());
			setFontColor(winrt::Windows::UI::Colors::Black());
			setTextFont(System::Drawing::Font(L"Arial", 8.0f, System::Drawing::FontStyle::Regular));
			properties[0] = ItemProperty(L"dataType", L"Data Type", L"Input", Enumeration, Public, std::vector<winrt::hstring>{L"Input", L"Output"});

			inputAnchoPoints.push_back(new AnchorPoint(1.0f, 0.5f, GetPosition(), GetWidth(), GetHeight(), Right));
			inputAnchoPoints.push_back(new AnchorPoint(0.5f, 0.0f, GetPosition(), GetWidth(), GetHeight(), Top));
			inputAnchoPoints.push_back(new AnchorPoint(0.0f, 0.5f, GetPosition(), GetWidth(), GetHeight(), Left));

			outputAnchoPoints.push_back(new AnchorPoint(0.5f, 1.0f, GetPosition(), GetWidth(), GetHeight(), Bottom));
		}

		bool SymbolData::IsHit()
		{
			return (Utility::MousePosition.X >= GetPosition().X && Utility::MousePosition.X <= GetPosition().X + GetWidth() && Utility::MousePosition.Y >= GetPosition().Y && Utility::MousePosition.Y <= GetPosition().Y + GetHeight());
		}

		int SymbolData::InputAnchorHit()
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

		int SymbolData::OutputAnchorHit()
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

		float SymbolData::GetWidth()
		{
			return width;
		}

		float SymbolData::GetHeight()
		{
			return height;
		}

		void SymbolData::Draw(Canvas canvas)
		{
			winrt::Windows::Foundation::Point points[5];
			points[0].X = GetPosition().X + (GetWidth() / 20);
			points[0].Y = GetPosition().Y;
			points[1].X = GetPosition().X + GetWidth() + (GetWidth() / 20);
			points[1].Y = GetPosition().Y;
			points[2].X = GetPosition().X + GetWidth() - (GetWidth() / 20);
			points[2].Y = GetPosition().Y + GetHeight();
			points[3].X = GetPosition().X - (GetWidth() / 20);
			points[3].Y = GetPosition().Y + GetHeight();
			points[4].X = points[0].X;
			points[4].Y = points[0].Y;

			PathGeometry myPathGeometry1;

			PathFigure pathFigure1;
			pathFigure1.StartPoint(points[0]);
			for (int i = 0; i < 5; i++)
			{
				LineSegment lineSegment;
				lineSegment.Point(points[i]);
				pathFigure1.Segments().Append(lineSegment);
			}
			myPathGeometry1.Figures().Append(pathFigure1);

			winrt::Microsoft::UI::Xaml::Shapes::Path path1;
			path1.Fill(SolidColorBrush(getIsSelected() || getIsHover() ? Utility::HighlightBrush(getFillColor()) : getFillColor()));
			path1.Stroke(SolidColorBrush(getLineColor()));
			path1.StrokeThickness(getIsSelected() ? 1.0 : 0.5);
			path1.Data(myPathGeometry1);
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
			Canvas::SetTop(textBlock, (GetPosition().Y + (GetHeight() / 2)) - (10.0 / 2));
			canvas.Children().Append(textBlock);
		}

		void SymbolData::SetPosition(float x, float y)
		{
			xPos = x;
			yPos = y;
		}

		winrt::Windows::Foundation::Point SymbolData::GetPosition()
		{
			return winrt::Windows::Foundation::Point(xPos, yPos);
		}

		std::vector<AnchorPoint*> SymbolData::GetInputAnchorPoints()
		{
			for (size_t i = 0; i < inputAnchoPoints.size(); i++)
			{
				inputAnchoPoints[i]->RefreshPosition(GetPosition(), GetWidth(), GetHeight());
			}
			return inputAnchoPoints;
		}

		std::vector<AnchorPoint*> SymbolData::GetOutputAnchorPoints()
		{
			for (size_t i = 0; i < outputAnchoPoints.size(); i++)
			{
				outputAnchoPoints[i]->RefreshPosition(GetPosition(), GetWidth(), GetHeight());
			}
			return outputAnchoPoints;
		}

		AnchorPoint* SymbolData::GetInputAnchorPoint(int anchorIndex)
		{
			std::vector<AnchorPoint*> list = GetInputAnchorPoints();

			if (anchorIndex >= 0 && anchorIndex < list.size())
				return list[anchorIndex];

			return 0;
		}

		AnchorPoint* SymbolData::GetOutputAnchorPoint(int OutputAnchorIndex)
		{
			std::vector<AnchorPoint*> list = GetOutputAnchorPoints();

			if (OutputAnchorIndex >= 0 && OutputAnchorIndex < list.size())
				return list[OutputAnchorIndex];

			return 0;
		}

		ItemProperty SymbolData::GetProperty(int index)
		{
			if (GetPropertyCount() > index && index >= 0)
			{
				return properties[index];
			}
			return ItemProperty();
		}

		void SymbolData::SetProperty(int index, ItemProperty property_Renamed)
		{
			if (GetPropertyCount() > index && index >= 0)
			{
				properties[index] = property_Renamed;
			}
		}

		int SymbolData::GetPropertyCount()
		{
			return 1;
		}

		FlowChart::Data::ISymbolChart *SymbolData::GetInstance()
		{
			return new SymbolData();
		}

		FlowChart::Data::ISymbolChart *SymbolData::GetDuplicate()
		{
			SymbolData *duplictate = new SymbolData();

			for (int i = 0; i < GetPropertyCount(); i++)
				duplictate->properties[i] = properties[i];
			
			return duplictate;
		}

		void SymbolData::RotateAnchorPoints()
		{
			AnchorPoint* tempAnchor1 = new AnchorPoint(outputAnchoPoints.size() > 0 ?
				outputAnchoPoints[0] :
				inputAnchoPoints[0]);

			AnchorPoint* tempAnchor2 = new AnchorPoint(inputAnchoPoints.size() > 0 ?
				inputAnchoPoints[0] :
				outputAnchoPoints[0]);

			for (size_t i = 0; i < inputAnchoPoints.size() - 1; i++)
			{
				inputAnchoPoints[i] = inputAnchoPoints[i + 1];
			}

			inputAnchoPoints[inputAnchoPoints.size() - 1] = tempAnchor1;

			for (size_t i = 0; i < outputAnchoPoints.size() - 1; i++)
			{
				outputAnchoPoints[i] = outputAnchoPoints[i + 1];
			}

			outputAnchoPoints[outputAnchoPoints.size() - 1] = tempAnchor2;
		}

		winrt::hstring SymbolData::GetString()
		{
			return L"Data";
		}

		winrt::hstring SymbolData::GetTypeString()
		{
			return L"SymbolData";
		}

		winrt::hstring SymbolData::ToString()
		{
			winrt::hstring result = L"";

			return L"\t\tName:" + getName() + L"\r\n\t\tTitle:" + getCaption() + L"\r\n\t\tPosition:" + winrt::to_hstring(xPos) + L" " + winrt::to_hstring(yPos) + L"\r\n" + result;
		}
	}
}

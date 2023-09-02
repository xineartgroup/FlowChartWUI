#include "pch.h"
#include "SymbolCard.h"

namespace FlowChart
{
	namespace Data
	{

		const winrt::hstring &SymbolCard::getName() const
		{
			return privateName;
		}

		void SymbolCard::setName(const winrt::hstring &value)
		{
			privateName = value;
		}

		const winrt::hstring &SymbolCard::getCaption() const
		{
			return privateCaption;
		}

		void SymbolCard::setCaption(const winrt::hstring &value)
		{
			privateCaption = value;
		}

		const bool &SymbolCard::getIsSelected() const
		{
			return privateIsSelected;
		}

		void SymbolCard::setIsSelected(const bool &value)
		{
			privateIsSelected = value;
		}

		const bool &SymbolCard::getIsHover() const
		{
			return privateIsHover;
		}

		void SymbolCard::setIsHover(const bool &value)
		{
			privateIsHover = value;
		}

		const bool &SymbolCard::getIsEditing() const
		{
			return privateIsEditing;
		}

		void SymbolCard::setIsEditing(const bool &value)
		{
			privateIsEditing = value;
		}

		winrt::hstring SymbolCard::getIconName()
		{
			return L"imgCard.png";
		}

		const winrt::Windows::UI::Color &SymbolCard::getLineColor() const
		{
			return privateLineColor;
		}

		void SymbolCard::setLineColor(const winrt::Windows::UI::Color& value)
		{
			privateLineColor = value;
		}

		const winrt::Windows::UI::Color &SymbolCard::getFillColor() const
		{
			return privateFillColor;
		}

		void SymbolCard::setFillColor(const winrt::Windows::UI::Color &value)
		{
			privateFillColor = value;
		}

		const winrt::Windows::UI::Color &SymbolCard::getFontColor() const
		{
			return privateFontColor;
		}

		void SymbolCard::setFontColor(const winrt::Windows::UI::Color &value)
		{
			privateFontColor = value;
		}

		const System::Drawing::Font &SymbolCard::getTextFont() const
		{
			return privateTextFont;
		}

		void SymbolCard::setTextFont(const System::Drawing::Font &value)
		{
			privateTextFont = value;
		}

		SymbolCard::SymbolCard()
		{
			height = 65;
			width = 65;
			xPos = 0.0f;
			yPos = 0.0f;

			setName(Utility::GetNextName(GetString()));
			setCaption(getName());

			setLineColor(winrt::Windows::UI::Colors::Black());
			setFillColor(winrt::Windows::UI::Colors::SkyBlue());
			setFontColor(winrt::Windows::UI::Colors::Black());
			setTextFont(System::Drawing::Font(L"Arial", 8.0f, System::Drawing::FontStyle::Regular));

			inputAnchoPoints.push_back(new AnchorPoint(1.0f, 0.5f, GetPosition(), GetWidth(), GetHeight(), Right));
			inputAnchoPoints.push_back(new AnchorPoint(0.5f, 0.0f, GetPosition(), GetWidth(), GetHeight(), Top));
			inputAnchoPoints.push_back(new AnchorPoint(0.0f, 0.5f, GetPosition(), GetWidth(), GetHeight(), Left));

			outputAnchoPoints.push_back(new AnchorPoint(0.5f, 1.0f, GetPosition(), GetWidth(), GetHeight(), Bottom));
		}

		bool SymbolCard::IsHit()
		{
			return (Utility::MousePosition.X >= GetPosition().X && Utility::MousePosition.X <= GetPosition().X + GetWidth() && Utility::MousePosition.Y >= GetPosition().Y && Utility::MousePosition.Y <= GetPosition().Y + GetHeight());
		}

		int SymbolCard::InputAnchorHit()
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

		int SymbolCard::OutputAnchorHit()
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

		float SymbolCard::GetWidth()
		{
			return width;
		}

		float SymbolCard::GetHeight()
		{
			return height;
		}

		void SymbolCard::Draw(Canvas canvas)
		{
			winrt::Windows::Foundation::Point points[6];
			points[0].X = GetPosition().X;
			points[0].Y = GetPosition().Y + (GetHeight() / 2);
			points[1].X = GetPosition().X + (GetWidth() / 2);
			points[1].Y = GetPosition().Y;
			points[2].X = GetPosition().X + GetWidth();
			points[2].Y = GetPosition().Y;
			points[3].X = GetPosition().X + GetWidth();
			points[3].Y = GetPosition().Y + GetHeight();
			points[4].X = GetPosition().X;
			points[4].Y = GetPosition().Y + GetHeight();
			points[5].X = points[0].X;
			points[5].Y = points[0].Y;

			PathGeometry myPathGeometry1;

			PathFigure pathFigure1;
			pathFigure1.StartPoint(points[0]);
			for (int i = 0; i < 6; i++)
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

		void SymbolCard::SetPosition(float x, float y)
		{
			xPos = x;
			yPos = y;
		}

		winrt::Windows::Foundation::Point SymbolCard::GetPosition()
		{
			return winrt::Windows::Foundation::Point(xPos, yPos);
		}

		std::vector<AnchorPoint*> SymbolCard::GetInputAnchorPoints()
		{
			for (size_t i = 0; i < inputAnchoPoints.size(); i++)
			{
				inputAnchoPoints[i]->RefreshPosition(GetPosition(), GetWidth(), GetHeight());
			}
			return inputAnchoPoints;
		}

		std::vector<AnchorPoint*> SymbolCard::GetOutputAnchorPoints()
		{
			for (size_t i = 0; i < outputAnchoPoints.size(); i++)
			{
				outputAnchoPoints[i]->RefreshPosition(GetPosition(), GetWidth(), GetHeight());
			}
			return outputAnchoPoints;
		}

		AnchorPoint* SymbolCard::GetInputAnchorPoint(int anchorIndex)
		{
			std::vector<AnchorPoint*> list = GetInputAnchorPoints();

			if (anchorIndex >= 0 && anchorIndex < list.size())
				return list[anchorIndex];

			return 0;
		}

		AnchorPoint* SymbolCard::GetOutputAnchorPoint(int OutputAnchorIndex)
		{
			std::vector<AnchorPoint*> list = GetOutputAnchorPoints();

			if (OutputAnchorIndex >= 0 && OutputAnchorIndex < list.size())
				return list[OutputAnchorIndex];

			return 0;
		}

		ItemProperty SymbolCard::GetProperty(int index)
		{
			if (GetPropertyCount() > index && index >= 0)
			{
				return properties[index];
			}
			return ItemProperty();
		}

		void SymbolCard::SetProperty(int index, ItemProperty property_Renamed)
		{
			if (GetPropertyCount() > index && index >= 0)
			{
				properties[index] = property_Renamed;
			}
		}

		int SymbolCard::GetPropertyCount()
		{
			return 0;
		}

		FlowChart::Data::ISymbolChart *SymbolCard::GetInstance()
		{
			return new SymbolCard();
		}

		FlowChart::Data::ISymbolChart *SymbolCard::GetDuplicate()
		{
			SymbolCard *duplictate = new SymbolCard();

			for (int i = 0; i < GetPropertyCount(); i++)
				duplictate->properties[i] = properties[i];

			for (size_t i = 0; i < inputAnchoPoints.size(); i++)
				duplictate->inputAnchoPoints[i] = inputAnchoPoints[i];

			for (size_t i = 0; i < outputAnchoPoints.size(); i++)
				duplictate->outputAnchoPoints[i] = outputAnchoPoints[i];

			return duplictate;
		}

		void SymbolCard::RotateAnchorPoints()
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

		winrt::hstring SymbolCard::GetString()
		{
			return L"Card";
		}

		winrt::hstring SymbolCard::GetTypeString()
		{
			return L"SymbolCard";
		}

		winrt::hstring SymbolCard::ToString()
		{
			winrt::hstring result = L"";

			return L"\t\tName:" + getName() + L"\r\n\t\tTitle:" + getCaption() + L"\r\n\t\tPosition:" + winrt::to_hstring(xPos) + L" " + winrt::to_hstring(yPos) + L"\r\n" + result;
		}
	}
}

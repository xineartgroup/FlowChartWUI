#include "pch.h"
#include "SymbolDecision.h"

namespace FlowChart
{
	namespace Data
	{

		const winrt::hstring &SymbolDecision::getName() const
		{
			return privateName;
		}

		void SymbolDecision::setName(const winrt::hstring &value)
		{
			privateName = value;
		}

		const winrt::hstring &SymbolDecision::getCaption() const
		{
			return privateCaption;
		}

		void SymbolDecision::setCaption(const winrt::hstring &value)
		{
			privateCaption = value;
		}

		const bool &SymbolDecision::getIsSelected() const
		{
			return privateIsSelected;
		}

		void SymbolDecision::setIsSelected(const bool &value)
		{
			privateIsSelected = value;
		}

		const bool &SymbolDecision::getIsHover() const
		{
			return privateIsHover;
		}

		void SymbolDecision::setIsHover(const bool &value)
		{
			privateIsHover = value;
		}

		const bool &SymbolDecision::getIsEditing() const
		{
			return privateIsEditing;
		}

		void SymbolDecision::setIsEditing(const bool &value)
		{
			privateIsEditing = value;
		}

		winrt::hstring SymbolDecision::getIconName()
		{
			return L"imgDecision.png";
		}

		const winrt::Windows::UI::Color &SymbolDecision::getLineColor() const
		{
			return privateLineColor;
		}

		void SymbolDecision::setLineColor(const winrt::Windows::UI::Color& value)
		{
			privateLineColor = value;
		}

		const winrt::Windows::UI::Color &SymbolDecision::getFillColor() const
		{
			return privateFillColor;
		}

		void SymbolDecision::setFillColor(const winrt::Windows::UI::Color &value)
		{
			privateFillColor = value;
		}

		const winrt::Windows::UI::Color &SymbolDecision::getFontColor() const
		{
			return privateFontColor;
		}

		void SymbolDecision::setFontColor(const winrt::Windows::UI::Color &value)
		{
			privateFontColor = value;
		}

		const System::Drawing::Font &SymbolDecision::getTextFont() const
		{
			return privateTextFont;
		}

		void SymbolDecision::setTextFont(const System::Drawing::Font &value)
		{
			privateTextFont = value;
		}

		SymbolDecision::SymbolDecision()
		{
			height = 100;
			width = 100;
			xPos = 0.0f;
			yPos = 0.0f;

			setName(Utility::GetNextName(GetString()));
			setCaption(getName());

			setLineColor(winrt::Windows::UI::Colors::Blue());
			setFillColor(winrt::Windows::UI::Colors::DeepSkyBlue());
			setFontColor(winrt::Windows::UI::Colors::Black());
			setTextFont(System::Drawing::Font(L"Arial", 8.0f, System::Drawing::FontStyle::Regular));

			inputAnchoPoints.push_back(new AnchorPoint(0.5f, 0.0f, GetPosition(), GetWidth(), GetHeight(), Top));
			inputAnchoPoints.push_back(new AnchorPoint(0.0f, 0.5f, GetPosition(), GetWidth(), GetHeight(), Left));

			outputAnchoPoints.push_back(new AnchorPoint(0.5f, 1.0f, GetPosition(), GetWidth(), GetHeight(), Bottom));
			outputAnchoPoints.push_back(new AnchorPoint(1.0f, 0.5f, GetPosition(), GetWidth(), GetHeight(), Right));
		}

		float SymbolDecision::GetWidth()
		{
			return width;
		}

		float SymbolDecision::GetHeight()
		{
			return height;
		}

		bool SymbolDecision::IsHit()
		{
			winrt::Windows::Foundation::Point vert[4];
			vert[0].X = GetPosition().X;
			vert[0].Y = GetPosition().Y + (GetHeight() / 2);
			vert[1].X = GetPosition().X + (GetWidth() / 2);
			vert[1].Y = GetPosition().Y;
			vert[2].X = GetPosition().X + GetWidth();
			vert[2].Y = GetPosition().Y + (GetHeight() / 2);
			vert[3].X = GetPosition().X + (GetWidth() / 2);
			vert[3].Y = GetPosition().Y + GetHeight();

			bool c = false;
			int j = 4 - 1;
			for (int i = 0; i < 4; j = i++)
			{
				if (((vert[i].Y > Utility::MousePosition.Y) != (vert[j].Y > Utility::MousePosition.Y)) && 
					(Utility::MousePosition.X < (vert[j].X - vert[i].X) * (Utility::MousePosition.Y - vert[i].Y) / (vert[j].Y - vert[i].Y) + vert[i].X))
					c = !c;
			}
			return c;
		}

		int SymbolDecision::InputAnchorHit()
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

		int SymbolDecision::OutputAnchorHit()
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

		void SymbolDecision::Draw(Canvas canvas)
		{
			winrt::Windows::Foundation::Point points[5];
			points[0].X = GetPosition().X; // + PADDING;
			points[0].Y = GetPosition().Y + (GetHeight() / 2);
			points[1].X = GetPosition().X + (GetWidth() / 2);
			points[1].Y = GetPosition().Y; // + PADDING;
			points[2].X = GetPosition().X + GetWidth(); // - PADDING;
			points[2].Y = GetPosition().Y + (GetHeight() / 2);
			points[3].X = GetPosition().X + (GetWidth() / 2);
			points[3].Y = GetPosition().Y + GetHeight(); // - PADDING;
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

			TextBlock textBlock1;
			textBlock1.Text(L"False");
			textBlock1.FontFamily(FontFamily(winrt::to_hstring(Utility::GeneralFont->Name)));
			textBlock1.FontSize(Utility::GeneralFont->Size);
			textBlock1.Foreground(SolidColorBrush(Utility::BrushLink));
			Canvas::SetLeft(textBlock1, GetPosition().X + (GetWidth() / 2) - Utility::HALFLINK);
			Canvas::SetTop(textBlock1, GetPosition().Y + GetHeight() + Utility::HALFLINK);
			canvas.Children().Append(textBlock1);

			TextBlock textBlock2;
			textBlock2.Text(L"True");
			textBlock2.FontFamily(FontFamily(winrt::to_hstring(Utility::GeneralFont->Name)));
			textBlock2.FontSize(Utility::GeneralFont->Size);
			textBlock2.Foreground(SolidColorBrush(Utility::BrushLink));
			Canvas::SetLeft(textBlock2, (GetPosition().X + GetWidth()) + (2 * Utility::HALFLINK));
			Canvas::SetTop(textBlock2, GetPosition().Y + (GetHeight() / 2) - Utility::HALFLINK);
			canvas.Children().Append(textBlock2);

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

		void SymbolDecision::SetPosition(float x, float y)
		{
			xPos = x;
			yPos = y;
		}

		winrt::Windows::Foundation::Point SymbolDecision::GetPosition()
		{
			return winrt::Windows::Foundation::Point(xPos, yPos);
		}

		std::vector<AnchorPoint*> SymbolDecision::GetInputAnchorPoints()
		{
			for (size_t i = 0; i < inputAnchoPoints.size(); i++)
			{
				inputAnchoPoints[i]->RefreshPosition(GetPosition(), GetWidth(), GetHeight());
			}
			return inputAnchoPoints;
		}

		std::vector<AnchorPoint*> SymbolDecision::GetOutputAnchorPoints()
		{
			for (size_t i = 0; i < outputAnchoPoints.size(); i++)
			{
				outputAnchoPoints[i]->RefreshPosition(GetPosition(), GetWidth(), GetHeight());
			}
			return outputAnchoPoints;
		}

		AnchorPoint* SymbolDecision::GetInputAnchorPoint(int anchorIndex)
		{
			std::vector<AnchorPoint*> list = GetInputAnchorPoints();

			if (anchorIndex >= 0 && anchorIndex < list.size())
				return list[anchorIndex];

			return 0;
		}

		AnchorPoint* SymbolDecision::GetOutputAnchorPoint(int OutputAnchorIndex)
		{
			std::vector<AnchorPoint*> list = GetOutputAnchorPoints();

			if (OutputAnchorIndex >= 0 && OutputAnchorIndex < list.size())
				return list[OutputAnchorIndex];

			return 0;
		}

		ItemProperty SymbolDecision::GetProperty(int index)
		{
			if (GetPropertyCount() > index && index >= 0)
			{
				return properties[index];
			}
			return ItemProperty();
		}

		void SymbolDecision::SetProperty(int index, ItemProperty property_Renamed)
		{
			if (GetPropertyCount() > index && index >= 0)
			{
				properties[index] = property_Renamed;
			}
		}

		int SymbolDecision::GetPropertyCount()
		{
			return 0;
		}

		FlowChart::Data::ISymbolChart *SymbolDecision::GetInstance()
		{
			return new SymbolDecision();
		}

		FlowChart::Data::ISymbolChart *SymbolDecision::GetDuplicate()
		{
			SymbolDecision *duplictate = new SymbolDecision();

			for (int i = 0; i < GetPropertyCount(); i++)
				duplictate->properties[i] = properties[i];
			
			return duplictate;
		}

		void SymbolDecision::RotateAnchorPoints()
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

		winrt::hstring SymbolDecision::GetString()
		{
			return L"Decision";
		}

		winrt::hstring SymbolDecision::GetTypeString()
		{
			return L"SymbolDecision";
		}

		winrt::hstring SymbolDecision::ToString()
		{
			winrt::hstring result = L"";

			return L"\t\tName:" + getName() + L"\r\n\t\tTitle:" + getCaption() + L"\r\n\t\tPosition:" + winrt::to_hstring(xPos) + L" " + winrt::to_hstring(yPos) + L"\r\n" + result;
		}
	}
}

#include "pch.h"
#include "SymbolDisplay.h"

namespace FlowChart
{
	namespace Data
	{

		const winrt::hstring &SymbolDisplay::getName() const
		{
			return privateName;
		}

		void SymbolDisplay::setName(const winrt::hstring &value)
		{
			privateName = value;
		}

		const winrt::hstring &SymbolDisplay::getCaption() const
		{
			return privateCaption;
		}

		void SymbolDisplay::setCaption(const winrt::hstring &value)
		{
			privateCaption = value;
		}

		const bool &SymbolDisplay::getIsSelected() const
		{
			return privateIsSelected;
		}

		void SymbolDisplay::setIsSelected(const bool &value)
		{
			privateIsSelected = value;
		}

		const bool &SymbolDisplay::getIsHover() const
		{
			return privateIsHover;
		}

		void SymbolDisplay::setIsHover(const bool &value)
		{
			privateIsHover = value;
		}

		const bool &SymbolDisplay::getIsEditing() const
		{
			return privateIsEditing;
		}

		void SymbolDisplay::setIsEditing(const bool &value)
		{
			privateIsEditing = value;
		}

		winrt::hstring SymbolDisplay::getIconName()
		{
			return L"imgDisplay.png";
		}

		const std::vector<Link*> &SymbolDisplay::getLinksToNextSymbols() const
		{
			return privateLinksToNextSymbols;
		}

		void SymbolDisplay::setLinksToNextSymbols(const std::vector<Link*> &value)
		{
			privateLinksToNextSymbols = value;
		}

		const winrt::Windows::UI::Color &SymbolDisplay::getLineColor() const
		{
			return privateLineColor;
		}

		void SymbolDisplay::setLineColor(const winrt::Windows::UI::Color& value)
		{
			privateLineColor = value;
		}

		const winrt::Windows::UI::Color &SymbolDisplay::getFillColor() const
		{
			return privateFillColor;
		}

		void SymbolDisplay::setFillColor(const winrt::Windows::UI::Color &value)
		{
			privateFillColor = value;
		}

		const winrt::Windows::UI::Color &SymbolDisplay::getFontColor() const
		{
			return privateFontColor;
		}

		void SymbolDisplay::setFontColor(const winrt::Windows::UI::Color &value)
		{
			privateFontColor = value;
		}

		const System::Drawing::Font &SymbolDisplay::getTextFont() const
		{
			return privateTextFont;
		}

		void SymbolDisplay::setTextFont(const System::Drawing::Font &value)
		{
			privateTextFont = value;
		}

		SymbolDisplay::SymbolDisplay()
		{
			height = 60;
			width = 90;
			xPos = 0.0f;
			yPos = 0.0f;

			setName(Utility::GetNextName(GetString()));
			setCaption(getName());

			setLinksToNextSymbols(std::vector<Link*>());
			setLineColor(winrt::Windows::UI::Colors::Black());
			setFillColor(winrt::Windows::UI::Colors::SkyBlue());
			setFontColor(winrt::Windows::UI::Colors::Black());
			setTextFont(System::Drawing::Font(L"Arial", 8.0f, System::Drawing::FontStyle::Regular));
			properties[0] = ItemProperty(L"delayAmount", L"Display Amount", L"5", Integer, Public, std::vector<winrt::hstring>());

			inputAnchoPoints.push_back(new AnchorPoint(1.0f, 0.5f, GetPosition(), GetWidth(), GetHeight(), Right));
			inputAnchoPoints.push_back(new AnchorPoint(0.5f, 0.0f, GetPosition(), GetWidth(), GetHeight(), Top));
			inputAnchoPoints.push_back(new AnchorPoint(0.0f, 0.5f, GetPosition(), GetWidth(), GetHeight(), Left));

			outputAnchoPoints.push_back(new AnchorPoint(0.5f, 1.0f, GetPosition(), GetWidth(), GetHeight(), Bottom));
		}

		bool SymbolDisplay::IsHit()
		{
			return (Utility::MousePosition.X >= GetPosition().X && Utility::MousePosition.X <= GetPosition().X + GetWidth() && Utility::MousePosition.Y >= GetPosition().Y && Utility::MousePosition.Y <= GetPosition().Y + GetHeight());
		}

		int SymbolDisplay::InputAnchorHit()
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

		int SymbolDisplay::OutputAnchorHit()
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

		float SymbolDisplay::GetWidth()
		{
			return width;
		}

		float SymbolDisplay::GetHeight()
		{
			return height;
		}

		void SymbolDisplay::Draw(Canvas canvas)
		{
			PathFigure myPathFigure;

			float width1 = 2 * GetWidth() / 3;

			winrt::Windows::Foundation::Point points[5];
			points[0].X = GetPosition().X + width1;
			points[0].Y = GetPosition().Y + GetHeight();
			points[1].X = GetPosition().X + (width1 / 2);
			points[1].Y = GetPosition().Y + GetHeight();
			points[2].X = GetPosition().X;
			points[2].Y = GetPosition().Y + (GetHeight() / 2);
			points[3].X = GetPosition().X + (width1 / 2);
			points[3].Y = GetPosition().Y;
			points[4].X = GetPosition().X + width1;
			points[4].Y = GetPosition().Y;

			myPathFigure.StartPoint(points[0]);
			for (int i = 0; i < 5; i++)
			{
				LineSegment lineSegment;
				lineSegment.Point(points[i]);
				myPathFigure.Segments().Append(lineSegment);
			}

			ArcSegment arcSegment2;
			arcSegment2.Point(winrt::Windows::Foundation::Point(GetPosition().X + width1, GetPosition().Y + GetHeight()));
			arcSegment2.Size(winrt::Windows::Foundation::Size(GetHeight() / 2, GetHeight() / 2));
			arcSegment2.RotationAngle(0);
			arcSegment2.IsLargeArc(true);
			arcSegment2.SweepDirection(SweepDirection::Clockwise);
			myPathFigure.Segments().Append(arcSegment2);

			PathGeometry myPathGeometry;
			myPathGeometry.Figures().Append(myPathFigure);

			winrt::Microsoft::UI::Xaml::Shapes::Path myPath;
			myPath.Fill(SolidColorBrush(getIsSelected() || getIsHover() ? Utility::HighlightBrush(getFillColor()) : getFillColor()));
			myPath.Stroke(SolidColorBrush(getLineColor()));
			myPath.StrokeThickness(getIsSelected() ? 1.0 : 0.5);
			myPath.Data(myPathGeometry);
			canvas.Children().Append(myPath);

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

		void SymbolDisplay::SetPosition(float x, float y)
		{
			xPos = x;
			yPos = y;
		}

		winrt::Windows::Foundation::Point SymbolDisplay::GetPosition()
		{
			return winrt::Windows::Foundation::Point(xPos, yPos);
		}

		std::vector<AnchorPoint*> SymbolDisplay::GetInputAnchorPoints()
		{
			for (size_t i = 0; i < inputAnchoPoints.size(); i++)
			{
				inputAnchoPoints[i]->RefreshPosition(GetPosition(), GetWidth(), GetHeight());
			}
			return inputAnchoPoints;
		}

		std::vector<AnchorPoint*> SymbolDisplay::GetOutputAnchorPoints()
		{
			for (size_t i = 0; i < outputAnchoPoints.size(); i++)
			{
				outputAnchoPoints[i]->RefreshPosition(GetPosition(), GetWidth(), GetHeight());
			}
			return outputAnchoPoints;
		}

		AnchorPoint* SymbolDisplay::GetInputAnchorPoint(int anchorIndex)
		{
			std::vector<AnchorPoint*> list = GetInputAnchorPoints();

			if (anchorIndex >= 0 && anchorIndex < list.size())
				return list[anchorIndex];

			return 0;
		}

		AnchorPoint* SymbolDisplay::GetOutputAnchorPoint(int OutputAnchorIndex)
		{
			std::vector<AnchorPoint*> list = GetOutputAnchorPoints();

			if (OutputAnchorIndex >= 0 && OutputAnchorIndex < list.size())
				return list[OutputAnchorIndex];

			return 0;
		}

		ItemProperty SymbolDisplay::GetProperty(int index)
		{
			if (GetPropertyCount() > index && index >= 0)
			{
				return properties[index];
			}
			return ItemProperty();
		}

		void SymbolDisplay::SetProperty(int index, ItemProperty property_Renamed)
		{
			if (GetPropertyCount() > index && index >= 0)
			{
				properties[index] = property_Renamed;
			}
		}

		int SymbolDisplay::GetPropertyCount()
		{
			return 1;
		}

		FlowChart::Data::ISymbolChart *SymbolDisplay::GetInstance()
		{
			return new SymbolDisplay();
		}

		FlowChart::Data::ISymbolChart *SymbolDisplay::GetDuplicate()
		{
			SymbolDisplay *duplictate = new SymbolDisplay();

			for (int i = 0; i < GetPropertyCount(); i++)
				duplictate->properties[i] = properties[i];
			

			return duplictate;
		}

		void SymbolDisplay::RotateAnchorPoints()
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

		winrt::hstring SymbolDisplay::GetString()
		{
			return L"Display";
		}

		winrt::hstring SymbolDisplay::GetTypeString()
		{
			return L"SymbolDisplay";
		}

		winrt::hstring SymbolDisplay::ToString()
		{
			winrt::hstring result = L"";
			for (Link* link : getLinksToNextSymbols())
			{
				ISymbol* symbol = link->NextSymbol;
				if (symbol)
				{
					result = result + L"\t\tNext:" + symbol->getName() + L"\r\n";
				}
			}

			return L"\t\tName:" + getName() + L"\r\n\t\tTitle:" + getCaption() + L"\r\n\t\tPosition:" + winrt::to_hstring(xPos) + L" " + winrt::to_hstring(yPos) + L"\r\n" + result;
		}
	}
}

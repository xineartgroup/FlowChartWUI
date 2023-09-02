#include "pch.h"
#include "SymbolDataStored.h"

namespace FlowChart
{
	namespace Data
	{

		const winrt::hstring &SymbolDataStored::getName() const
		{
			return privateName;
		}

		void SymbolDataStored::setName(const winrt::hstring &value)
		{
			privateName = value;
		}

		const winrt::hstring &SymbolDataStored::getCaption() const
		{
			return privateCaption;
		}

		void SymbolDataStored::setCaption(const winrt::hstring &value)
		{
			privateCaption = value;
		}

		const bool &SymbolDataStored::getIsSelected() const
		{
			return privateIsSelected;
		}

		void SymbolDataStored::setIsSelected(const bool &value)
		{
			privateIsSelected = value;
		}

		const bool &SymbolDataStored::getIsHover() const
		{
			return privateIsHover;
		}

		void SymbolDataStored::setIsHover(const bool &value)
		{
			privateIsHover = value;
		}

		const bool &SymbolDataStored::getIsEditing() const
		{
			return privateIsEditing;
		}

		void SymbolDataStored::setIsEditing(const bool &value)
		{
			privateIsEditing = value;
		}

		winrt::hstring SymbolDataStored::getIconName()
		{
			return L"imgDataStored.png";
		}

		const winrt::Windows::UI::Color &SymbolDataStored::getLineColor() const
		{
			return privateLineColor;
		}

		void SymbolDataStored::setLineColor(const winrt::Windows::UI::Color& value)
		{
			privateLineColor = value;
		}

		const winrt::Windows::UI::Color &SymbolDataStored::getFillColor() const
		{
			return privateFillColor;
		}

		void SymbolDataStored::setFillColor(const winrt::Windows::UI::Color &value)
		{
			privateFillColor = value;
		}

		const winrt::Windows::UI::Color &SymbolDataStored::getFontColor() const
		{
			return privateFontColor;
		}

		void SymbolDataStored::setFontColor(const winrt::Windows::UI::Color &value)
		{
			privateFontColor = value;
		}

		const System::Drawing::Font &SymbolDataStored::getTextFont() const
		{
			return privateTextFont;
		}

		void SymbolDataStored::setTextFont(const System::Drawing::Font &value)
		{
			privateTextFont = value;
		}

		SymbolDataStored::SymbolDataStored()
		{
			height = 60;
			width = 80;
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

		bool SymbolDataStored::IsHit()
		{
			return (Utility::MousePosition.X >= GetPosition().X && Utility::MousePosition.X <= GetPosition().X + GetWidth() && Utility::MousePosition.Y >= GetPosition().Y && Utility::MousePosition.Y <= GetPosition().Y + GetHeight());
		}

		int SymbolDataStored::InputAnchorHit()
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

		int SymbolDataStored::OutputAnchorHit()
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

		float SymbolDataStored::GetWidth()
		{
			return width;
		}

		float SymbolDataStored::GetHeight()
		{
			return height;
		}

		void SymbolDataStored::Draw(Canvas canvas)
		{
			PathFigure myPathFigure;

			winrt::Windows::Foundation::Point points[4];
			points[0].X = GetPosition().X + (3 * GetWidth() / 16);
			points[0].Y = GetPosition().Y;
			points[1].X = GetPosition().X + GetWidth() + (3 * GetWidth() / 16);
			points[1].Y = GetPosition().Y;
			points[2].X = GetPosition().X + GetWidth() + (3 * GetWidth() / 16);
			points[2].Y = GetPosition().Y + GetHeight();
			points[3].X = GetPosition().X + (3 * GetWidth() / 16);
			points[3].Y = GetPosition().Y + GetHeight();

			myPathFigure.StartPoint(points[0]);

			LineSegment lineSegment1;
			lineSegment1.Point(points[1]);
			myPathFigure.Segments().Append(lineSegment1);

			ArcSegment arcSegment1;
			arcSegment1.Point(points[2]);
			arcSegment1.Size(winrt::Windows::Foundation::Size(3 * GetWidth() / 16, GetHeight() / 2));
			arcSegment1.RotationAngle(0);
			arcSegment1.IsLargeArc(false);
			arcSegment1.SweepDirection(SweepDirection::Counterclockwise);
			myPathFigure.Segments().Append(arcSegment1);

			LineSegment lineSegment2;
			lineSegment2.Point(points[3]);
			myPathFigure.Segments().Append(lineSegment2);

			ArcSegment arcSegment2;
			arcSegment2.Point(points[0]);
			arcSegment2.Size(winrt::Windows::Foundation::Size(3 * GetWidth() / 16, GetHeight() / 2));
			arcSegment2.RotationAngle(0);
			arcSegment2.IsLargeArc(false);
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

		void SymbolDataStored::SetPosition(float x, float y)
		{
			xPos = x;
			yPos = y;
		}

		winrt::Windows::Foundation::Point SymbolDataStored::GetPosition()
		{
			return winrt::Windows::Foundation::Point(xPos, yPos);
		}

		std::vector<AnchorPoint*> SymbolDataStored::GetInputAnchorPoints()
		{
			for (size_t i = 0; i < inputAnchoPoints.size(); i++)
			{
				inputAnchoPoints[i]->RefreshPosition(GetPosition(), GetWidth(), GetHeight());
			}
			return inputAnchoPoints;
		}

		std::vector<AnchorPoint*> SymbolDataStored::GetOutputAnchorPoints()
		{
			for (size_t i = 0; i < outputAnchoPoints.size(); i++)
			{
				outputAnchoPoints[i]->RefreshPosition(GetPosition(), GetWidth(), GetHeight());
			}
			return outputAnchoPoints;
		}

		AnchorPoint* SymbolDataStored::GetInputAnchorPoint(int anchorIndex)
		{
			std::vector<AnchorPoint*> list = GetInputAnchorPoints();

			if (anchorIndex >= 0 && anchorIndex < list.size())
				return list[anchorIndex];

			return 0;
		}

		AnchorPoint* SymbolDataStored::GetOutputAnchorPoint(int OutputAnchorIndex)
		{
			std::vector<AnchorPoint*> list = GetOutputAnchorPoints();

			if (OutputAnchorIndex >= 0 && OutputAnchorIndex < list.size())
				return list[OutputAnchorIndex];

			return 0;
		}

		ItemProperty SymbolDataStored::GetProperty(int index)
		{
			if (GetPropertyCount() > index && index >= 0)
			{
				return properties[index];
			}
			return ItemProperty();
		}

		void SymbolDataStored::SetProperty(int index, ItemProperty property_Renamed)
		{
			if (GetPropertyCount() > index && index >= 0)
			{
				properties[index] = property_Renamed;
			}
		}

		int SymbolDataStored::GetPropertyCount()
		{
			return 0;
		}

		FlowChart::Data::ISymbolChart *SymbolDataStored::GetInstance()
		{
			return new SymbolDataStored();
		}

		FlowChart::Data::ISymbolChart *SymbolDataStored::GetDuplicate()
		{
			SymbolDataStored *duplictate = new SymbolDataStored();

			for (int i = 0; i < GetPropertyCount(); i++) duplictate->properties[i] = properties[i];
			

			return duplictate;
		}

		void SymbolDataStored::RotateAnchorPoints()
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

		winrt::hstring SymbolDataStored::GetString()
		{
			return L"Stored Data";
		}

		winrt::hstring SymbolDataStored::GetTypeString()
		{
			return L"SymbolDataStored";
		}

		winrt::hstring SymbolDataStored::ToString()
		{
			winrt::hstring result = L"";

			return L"\t\tName:" + getName() + L"\r\n\t\tTitle:" + getCaption() + L"\r\n\t\tPosition:" + winrt::to_hstring(xPos) + L" " + winrt::to_hstring(yPos) + L"\r\n" + result;
		}
	}
}

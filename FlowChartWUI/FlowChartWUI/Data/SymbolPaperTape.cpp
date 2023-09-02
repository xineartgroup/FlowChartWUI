#include "pch.h"
#include "SymbolPaperTape.h"

namespace FlowChart
{
	namespace Data
	{

		const winrt::hstring &SymbolPaperTape::getName() const
		{
			return privateName;
		}

		void SymbolPaperTape::setName(const winrt::hstring &value)
		{
			privateName = value;
		}

		const winrt::hstring &SymbolPaperTape::getCaption() const
		{
			return privateCaption;
		}

		void SymbolPaperTape::setCaption(const winrt::hstring &value)
		{
			privateCaption = value;
		}

		const bool &SymbolPaperTape::getIsSelected() const
		{
			return privateIsSelected;
		}

		void SymbolPaperTape::setIsSelected(const bool &value)
		{
			privateIsSelected = value;
		}

		const bool &SymbolPaperTape::getIsHover() const
		{
			return privateIsHover;
		}

		void SymbolPaperTape::setIsHover(const bool &value)
		{
			privateIsHover = value;
		}

		const bool &SymbolPaperTape::getIsEditing() const
		{
			return privateIsEditing;
		}

		void SymbolPaperTape::setIsEditing(const bool &value)
		{
			privateIsEditing = value;
		}

		winrt::hstring SymbolPaperTape::getIconName()
		{
			return L"imgPaperTape.png";
		}

		const winrt::Windows::UI::Color &SymbolPaperTape::getLineColor() const
		{
			return privateLineColor;
		}

		void SymbolPaperTape::setLineColor(const winrt::Windows::UI::Color& value)
		{
			privateLineColor = value;
		}

		const winrt::Windows::UI::Color &SymbolPaperTape::getFillColor() const
		{
			return privateFillColor;
		}

		void SymbolPaperTape::setFillColor(const winrt::Windows::UI::Color &value)
		{
			privateFillColor = value;
		}

		const winrt::Windows::UI::Color &SymbolPaperTape::getFontColor() const
		{
			return privateFontColor;
		}

		void SymbolPaperTape::setFontColor(const winrt::Windows::UI::Color &value)
		{
			privateFontColor = value;
		}

		const System::Drawing::Font &SymbolPaperTape::getTextFont() const
		{
			return privateTextFont;
		}

		void SymbolPaperTape::setTextFont(const System::Drawing::Font &value)
		{
			privateTextFont = value;
		}

		SymbolPaperTape::SymbolPaperTape()
		{
			height = 60;
			width = 90;
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

		bool SymbolPaperTape::IsHit()
		{
			return (Utility::MousePosition.X >= GetPosition().X && Utility::MousePosition.X <= GetPosition().X + GetWidth() && Utility::MousePosition.Y >= GetPosition().Y && Utility::MousePosition.Y <= GetPosition().Y + GetHeight());
		}

		int SymbolPaperTape::InputAnchorHit()
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

		int SymbolPaperTape::OutputAnchorHit()
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

		float SymbolPaperTape::GetWidth()
		{
			return width;
		}

		float SymbolPaperTape::GetHeight()
		{
			return height;
		}

		void SymbolPaperTape::Draw(Canvas canvas)
		{
			PathFigure myPathFigure;

			winrt::Windows::Foundation::Point points[6];
			points[0].X = GetPosition().X;
			points[0].Y = GetPosition().Y;
			points[1].X = GetPosition().X + (GetWidth() / 2);
			points[1].Y = GetPosition().Y;
			points[2].X = GetPosition().X + GetWidth();
			points[2].Y = GetPosition().Y;
			points[3].X = GetPosition().X + GetWidth();
			points[3].Y = GetPosition().Y + GetHeight();
			points[4].X = GetPosition().X + (GetWidth() / 2);
			points[4].Y = GetPosition().Y + GetHeight();
			points[5].X = GetPosition().X;
			points[5].Y = GetPosition().Y + GetHeight();

			myPathFigure.StartPoint(points[0]);

			ArcSegment arcSegment1;
			arcSegment1.Point(points[1]);
			arcSegment1.Size(winrt::Windows::Foundation::Size(GetWidth() / 4, GetHeight() / 8));
			arcSegment1.RotationAngle(0);
			arcSegment1.IsLargeArc(true);
			arcSegment1.SweepDirection(SweepDirection::Counterclockwise);
			myPathFigure.Segments().Append(arcSegment1);

			ArcSegment arcSegment2;
			arcSegment2.Point(points[2]);
			arcSegment2.Size(winrt::Windows::Foundation::Size(GetWidth() / 4, GetHeight() / 8));
			arcSegment2.RotationAngle(0);
			arcSegment2.IsLargeArc(true);
			arcSegment2.SweepDirection(SweepDirection::Clockwise);
			myPathFigure.Segments().Append(arcSegment2);

			LineSegment lineSegment1;
			lineSegment1.Point(points[3]);
			myPathFigure.Segments().Append(lineSegment1);

			ArcSegment arcSegment3;
			arcSegment3.Point(points[4]);
			arcSegment3.Size(winrt::Windows::Foundation::Size(GetWidth() / 4, GetHeight() / 8));
			arcSegment3.RotationAngle(0);
			arcSegment3.IsLargeArc(true);
			arcSegment3.SweepDirection(SweepDirection::Counterclockwise);
			myPathFigure.Segments().Append(arcSegment3);

			ArcSegment arcSegment4;
			arcSegment4.Point(points[5]);
			arcSegment4.Size(winrt::Windows::Foundation::Size(GetWidth() / 4, GetHeight() / 8));
			arcSegment4.RotationAngle(0);
			arcSegment4.IsLargeArc(true);
			arcSegment4.SweepDirection(SweepDirection::Clockwise);
			myPathFigure.Segments().Append(arcSegment4);

			LineSegment lineSegment2;
			lineSegment2.Point(points[0]);
			myPathFigure.Segments().Append(lineSegment2);

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

		void SymbolPaperTape::SetPosition(float x, float y)
		{
			xPos = x;
			yPos = y;
		}

		winrt::Windows::Foundation::Point SymbolPaperTape::GetPosition()
		{
			return winrt::Windows::Foundation::Point(xPos, yPos);
		}

		std::vector<AnchorPoint*> SymbolPaperTape::GetInputAnchorPoints()
		{
			for (size_t i = 0; i < inputAnchoPoints.size(); i++)
			{
				inputAnchoPoints[i]->RefreshPosition(GetPosition(), GetWidth(), GetHeight());
			}
			return inputAnchoPoints;
		}

		std::vector<AnchorPoint*> SymbolPaperTape::GetOutputAnchorPoints()
		{
			for (size_t i = 0; i < outputAnchoPoints.size(); i++)
			{
				outputAnchoPoints[i]->RefreshPosition(GetPosition(), GetWidth(), GetHeight());
			}
			return outputAnchoPoints;
		}

		AnchorPoint* SymbolPaperTape::GetInputAnchorPoint(int anchorIndex)
		{
			std::vector<AnchorPoint*> list = GetInputAnchorPoints();

			if (anchorIndex >= 0 && anchorIndex < list.size())
				return list[anchorIndex];

			return 0;
		}

		AnchorPoint* SymbolPaperTape::GetOutputAnchorPoint(int OutputAnchorIndex)
		{
			std::vector<AnchorPoint*> list = GetOutputAnchorPoints();

			if (OutputAnchorIndex >= 0 && OutputAnchorIndex < list.size())
				return list[OutputAnchorIndex];

			return 0;
		}

		ItemProperty SymbolPaperTape::GetProperty(int index)
		{
			if (GetPropertyCount() > index && index >= 0)
			{
				return properties[index];
			}
			return ItemProperty();
		}

		void SymbolPaperTape::SetProperty(int index, ItemProperty property_Renamed)
		{
			if (GetPropertyCount() > index && index >= 0)
			{
				properties[index] = property_Renamed;
			}
		}

		int SymbolPaperTape::GetPropertyCount()
		{
			return 0;
		}

		FlowChart::Data::ISymbolChart *SymbolPaperTape::GetInstance()
		{
			return new SymbolPaperTape();
		}

		FlowChart::Data::ISymbolChart *SymbolPaperTape::GetDuplicate()
		{
			SymbolPaperTape *duplictate = new SymbolPaperTape();

			for (int i = 0; i < GetPropertyCount(); i++)
				duplictate->properties[i] = properties[i];
			
			return duplictate;
		}

		void SymbolPaperTape::RotateAnchorPoints()
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

		winrt::hstring SymbolPaperTape::GetString()
		{
			return L"Paper Tape";
		}

		winrt::hstring SymbolPaperTape::GetTypeString()
		{
			return L"SymbolPaperTape";
		}

		winrt::hstring SymbolPaperTape::ToString()
		{
			winrt::hstring result = L"";

			return L"\t\tName:" + getName() + L"\r\n\t\tTitle:" + getCaption() + L"\r\n\t\tPosition:" + winrt::to_hstring(xPos) + L" " + winrt::to_hstring(yPos) + L"\r\n" + result;
		}
	}
}

#include "pch.h"
#include "SymbolTerminator.h"

namespace FlowChart
{
	namespace Data
	{

		const winrt::hstring &SymbolTerminator::getName() const
		{
			return privateName;
		}

		void SymbolTerminator::setName(const winrt::hstring &value)
		{
			privateName = value;
		}

		const winrt::hstring &SymbolTerminator::getCaption() const
		{
			return privateCaption;
		}

		void SymbolTerminator::setCaption(const winrt::hstring &value)
		{
			privateCaption = value;
		}

		const bool &SymbolTerminator::getIsSelected() const
		{
			return privateIsSelected;
		}

		void SymbolTerminator::setIsSelected(const bool &value)
		{
			privateIsSelected = value;
		}

		const bool &SymbolTerminator::getIsHover() const
		{
			return privateIsHover;
		}

		void SymbolTerminator::setIsHover(const bool &value)
		{
			privateIsHover = value;
		}

		const bool &SymbolTerminator::getIsEditing() const
		{
			return privateIsEditing;
		}

		void SymbolTerminator::setIsEditing(const bool &value)
		{
			privateIsEditing = value;
		}

		winrt::hstring SymbolTerminator::getIconName()
		{
			return L"imgTerminator.png";
		}

		const winrt::Windows::UI::Color &SymbolTerminator::getLineColor() const
		{
			return privateLineColor;
		}

		void SymbolTerminator::setLineColor(const winrt::Windows::UI::Color& value)
		{
			privateLineColor = value;
		}

		const winrt::Windows::UI::Color& SymbolTerminator::getFillColor() const
		{
			return privateFillColor;
		}

		void SymbolTerminator::setFillColor(const winrt::Windows::UI::Color &value)
		{
			privateFillColor = value;
		}

		const winrt::Windows::UI::Color &SymbolTerminator::getFontColor() const
		{
			return privateFontColor;
		}

		void SymbolTerminator::setFontColor(const winrt::Windows::UI::Color &value)
		{
			privateFontColor = value;
		}

		const System::Drawing::Font &SymbolTerminator::getTextFont() const
		{
			return privateTextFont;
		}

		void SymbolTerminator::setTextFont(const System::Drawing::Font &value)
		{
			privateTextFont = value;
		}

		SymbolTerminator::SymbolTerminator()
		{
			height = 40;
			width = 150;
			xPos = 0.0f;
			yPos = 0.0f;

			setName(Utility::GetNextName(GetString()));
			setCaption(getName());

			setLineColor(winrt::Windows::UI::Colors::DarkGray());
			setFillColor(winrt::Windows::UI::Colors::LightSkyBlue());
			setFontColor(winrt::Windows::UI::Colors::Black());
			setTextFont(System::Drawing::Font(L"Arial", 8.0f, System::Drawing::FontStyle::Regular));
			properties[0] = ItemProperty(L"terminatorType", L"Terminator Type", L"Begin", Enumeration, Public, std::vector<winrt::hstring>{L"Begin", L"End"});

			inputAnchoPoints.push_back(new AnchorPoint(1.0f, 0.5f, GetPosition(), GetWidth(), GetHeight(), Right));
			inputAnchoPoints.push_back(new AnchorPoint(0.5f, 0.0f, GetPosition(), GetWidth(), GetHeight(), Top));
			inputAnchoPoints.push_back(new AnchorPoint(0.0f, 0.5f, GetPosition(), GetWidth(), GetHeight(), Left));

			if (properties[0].getValue() == L"End")
			{
				inputAnchoPoints.push_back(new AnchorPoint(0.5f, 1.0f, GetPosition(), GetWidth(), GetHeight(), Bottom));
			}

			if (properties[0].getValue() == L"Begin")
			{
				outputAnchoPoints.push_back(new AnchorPoint(0.5f, 1.0f, GetPosition(), GetWidth(), GetHeight(), Bottom));
			}
		}

		bool SymbolTerminator::IsHit()
		{
			return (Utility::MousePosition.X >= GetPosition().X && 
				Utility::MousePosition.X <= GetPosition().X + GetWidth() && 
				Utility::MousePosition.Y >= GetPosition().Y && 
				Utility::MousePosition.Y <= GetPosition().Y + GetHeight());
		}

		int SymbolTerminator::InputAnchorHit()
		{
			std::vector<AnchorPoint*> list = GetInputAnchorPoints();

			for (int i = 0; i < list.size(); i++)
			{
				if (Utility::MousePosition.X >= list[i]->getPosition().X - (Utility::LINKCONNECTOR / 2) && 
					Utility::MousePosition.X <= list[i]->getPosition().X + (Utility::LINKCONNECTOR / 2) && 
					Utility::MousePosition.Y >= list[i]->getPosition().Y - (Utility::LINKCONNECTOR / 2) && 
					Utility::MousePosition.Y <= list[i]->getPosition().Y + (Utility::LINKCONNECTOR / 2))
				{
					return i;
				}
			}

			return -1;
		}

		int SymbolTerminator::OutputAnchorHit()
		{
			std::vector<AnchorPoint*> list = GetOutputAnchorPoints();

			for (int i = 0; i < list.size(); i++)
			{
				if (Utility::MousePosition.X >= list[i]->getPosition().X - (Utility::LINKCONNECTOR / 2) && 
					Utility::MousePosition.X <= list[i]->getPosition().X + (Utility::LINKCONNECTOR / 2) && 
					Utility::MousePosition.Y >= list[i]->getPosition().Y - (Utility::LINKCONNECTOR / 2) && 
					Utility::MousePosition.Y <= list[i]->getPosition().Y + (Utility::LINKCONNECTOR / 2))
				{
					return i;
				}
			}

			return -1;
		}

		float SymbolTerminator::GetWidth()
		{
			return width;
		}

		float SymbolTerminator::GetHeight()
		{
			return height;
		}

		void SymbolTerminator::Draw(Canvas canvas)
		{
			//RectangleGeometry myRectangleGeometry1;
			//myRectangleGeometry1.Rect(winrt::Windows::Foundation::Rect(GetPosition().X, GetPosition().Y, GetWidth(), GetHeight()));
			//myRectangleGeometry1.RadiusX(GetHeight() / 2);
			//myRectangleGeometry1.RadiusY(GetHeight() / 2);

			//winrt::Microsoft::UI::Xaml::Shapes::Path path1;
			//path1.Fill(SolidColorBrush(getIsSelected() || getIsHover() ? Utility::HighlightBrush(getFillColor()) : getFillColor()));
			//path1.Stroke(SolidColorBrush(getLineColor()));
			//path1.StrokeThickness(getIsSelected() ? 1.0 : 0.5);
			//path1.Data(myRectangleGeometry1);

			//canvas.Children().Append(path1);

			float offset = GetWidth() < GetHeight() ? GetWidth() / 2 : GetHeight() / 2;

			winrt::Windows::Foundation::Point points[8];
			points[0].X = GetPosition().X;
			points[0].Y = GetPosition().Y + offset;
			points[1].X = GetPosition().X + offset;
			points[1].Y = GetPosition().Y;
			points[2].X = GetPosition().X + GetWidth() - offset;
			points[2].Y = GetPosition().Y;
			points[3].X = GetPosition().X + GetWidth();
			points[3].Y = GetPosition().Y + offset;
			points[4].X = GetPosition().X + GetWidth();
			points[4].Y = GetPosition().Y + GetHeight() - offset;
			points[5].X = GetPosition().X + GetWidth() - offset;
			points[5].Y = GetPosition().Y + GetHeight();
			points[6].X = GetPosition().X + offset;
			points[6].Y = GetPosition().Y + GetHeight();
			points[7].X = GetPosition().X;
			points[7].Y = GetPosition().Y + GetHeight() - offset;

			PathFigure myPathFigure;

			myPathFigure.StartPoint(points[0]);

			ArcSegment arcSegment1;
			arcSegment1.Point(winrt::Windows::Foundation::Point(points[1]));
			arcSegment1.Size(winrt::Windows::Foundation::Size(offset, offset));
			arcSegment1.RotationAngle(0);
			arcSegment1.IsLargeArc(false);
			arcSegment1.SweepDirection(SweepDirection::Clockwise);
			myPathFigure.Segments().Append(arcSegment1);

			LineSegment lineSegment2;
			lineSegment2.Point(points[2]);
			myPathFigure.Segments().Append(lineSegment2);

			ArcSegment arcSegment3;
			arcSegment3.Point(winrt::Windows::Foundation::Point(points[3]));
			arcSegment3.Size(winrt::Windows::Foundation::Size(offset, offset));
			arcSegment3.RotationAngle(0);
			arcSegment3.IsLargeArc(false);
			arcSegment3.SweepDirection(SweepDirection::Clockwise);
			myPathFigure.Segments().Append(arcSegment3);

			LineSegment lineSegment4;
			lineSegment4.Point(points[4]);
			myPathFigure.Segments().Append(lineSegment4);

			ArcSegment arcSegment5;
			arcSegment5.Point(winrt::Windows::Foundation::Point(points[5]));
			arcSegment5.Size(winrt::Windows::Foundation::Size(offset, offset));
			arcSegment5.RotationAngle(0);
			arcSegment5.IsLargeArc(false);
			arcSegment5.SweepDirection(SweepDirection::Clockwise);
			myPathFigure.Segments().Append(arcSegment5);

			LineSegment lineSegment6;
			lineSegment6.Point(points[6]);
			myPathFigure.Segments().Append(lineSegment6);

			ArcSegment arcSegment7;
			arcSegment7.Point(winrt::Windows::Foundation::Point(points[7]));
			arcSegment7.Size(winrt::Windows::Foundation::Size(offset, offset));
			arcSegment7.RotationAngle(0);
			arcSegment7.IsLargeArc(false);
			arcSegment7.SweepDirection(SweepDirection::Clockwise);
			myPathFigure.Segments().Append(arcSegment7);

			LineSegment lineSegment8;
			lineSegment8.Point(points[0]);
			myPathFigure.Segments().Append(lineSegment8);

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

		void SymbolTerminator::SetPosition(float x, float y)
		{
			xPos = x;
			yPos = y;
		}

		winrt::Windows::Foundation::Point SymbolTerminator::GetPosition()
		{
			return winrt::Windows::Foundation::Point(xPos, yPos);
		}

		std::vector<AnchorPoint*> SymbolTerminator::GetInputAnchorPoints()
		{
			for (size_t i = 0; i < inputAnchoPoints.size(); i++)
			{
				inputAnchoPoints[i]->RefreshPosition(GetPosition(), GetWidth(), GetHeight());
			}
			return inputAnchoPoints;
		}

		std::vector<AnchorPoint*> SymbolTerminator::GetOutputAnchorPoints()
		{
			for (size_t i = 0; i < outputAnchoPoints.size(); i++)
			{
				outputAnchoPoints[i]->RefreshPosition(GetPosition(), GetWidth(), GetHeight());
			}
			return outputAnchoPoints;
		}

		AnchorPoint* SymbolTerminator::GetInputAnchorPoint(int anchorIndex)
		{
			std::vector<AnchorPoint*> list = GetInputAnchorPoints();

			if (anchorIndex >= 0 && anchorIndex < list.size())
				return list[anchorIndex];

			return 0;
		}

		AnchorPoint* SymbolTerminator::GetOutputAnchorPoint(int OutputAnchorIndex)
		{
			std::vector<AnchorPoint*> list = GetOutputAnchorPoints();

			if (OutputAnchorIndex >= 0 && OutputAnchorIndex < list.size())
				return list[OutputAnchorIndex];

			return 0;
		}

		ItemProperty SymbolTerminator::GetProperty(int index)
		{
			if (GetPropertyCount() > index && index >= 0)
			{
				return properties[index];
			}
			return ItemProperty();
		}

		void SymbolTerminator::SetProperty(int index, ItemProperty property_Renamed)
		{
			if (GetPropertyCount() > index && index >= 0)
			{
				properties[index] = property_Renamed;
			}
		}

		int SymbolTerminator::GetPropertyCount()
		{
			return 1;
		}

		FlowChart::Data::ISymbolChart *SymbolTerminator::GetInstance()
		{
			return new SymbolTerminator();
		}

		FlowChart::Data::ISymbolChart *SymbolTerminator::GetDuplicate()
		{
			SymbolTerminator *duplictate = new SymbolTerminator();

			for (int i = 0; i < GetPropertyCount(); i++)
				duplictate->properties[i] = properties[i];
			
			return duplictate;
		}

		void SymbolTerminator::RotateAnchorPoints()
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

		winrt::hstring SymbolTerminator::GetString()
		{
			return L"Terminator";
		}

		winrt::hstring SymbolTerminator::GetTypeString()
		{
			return L"SymbolTerminator";
		}

		winrt::hstring SymbolTerminator::ToString()
		{
			winrt::hstring result = L"";

			return L"\t\tName:" + getName() + L"\r\n\t\tTitle:" + getCaption() + L"\r\n\t\tPosition:" + winrt::to_hstring(xPos) + L" " + winrt::to_hstring(yPos) + L"\r\n" + result;
		}
	}
}

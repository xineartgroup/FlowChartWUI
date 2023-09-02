#include "pch.h"
#include "SymbolCloud.h"

namespace FlowChart
{
	namespace Data
	{

		const winrt::hstring &SymbolCloud::getName() const
		{
			return privateName;
		}

		void SymbolCloud::setName(const winrt::hstring &value)
		{
			privateName = value;
		}

		const winrt::hstring &SymbolCloud::getCaption() const
		{
			return privateCaption;
		}

		void SymbolCloud::setCaption(const winrt::hstring &value)
		{
			privateCaption = value;
		}

		const bool &SymbolCloud::getIsSelected() const
		{
			return privateIsSelected;
		}

		void SymbolCloud::setIsSelected(const bool &value)
		{
			privateIsSelected = value;
		}

		const bool &SymbolCloud::getIsHover() const
		{
			return privateIsHover;
		}

		void SymbolCloud::setIsHover(const bool &value)
		{
			privateIsHover = value;
		}

		const bool &SymbolCloud::getIsEditing() const
		{
			return privateIsEditing;
		}

		void SymbolCloud::setIsEditing(const bool &value)
		{
			privateIsEditing = value;
		}

		winrt::hstring SymbolCloud::getIconName()
		{
			return L"imgCloud.png";
		}

		const winrt::Windows::UI::Color &SymbolCloud::getLineColor() const
		{
			return privateLineColor;
		}

		void SymbolCloud::setLineColor(const winrt::Windows::UI::Color& value)
		{
			privateLineColor = value;
		}

		const winrt::Windows::UI::Color &SymbolCloud::getFillColor() const
		{
			return privateFillColor;
		}

		void SymbolCloud::setFillColor(const winrt::Windows::UI::Color &value)
		{
			privateFillColor = value;
		}

		const winrt::Windows::UI::Color &SymbolCloud::getFontColor() const
		{
			return privateFontColor;
		}

		void SymbolCloud::setFontColor(const winrt::Windows::UI::Color &value)
		{
			privateFontColor = value;
		}

		const System::Drawing::Font &SymbolCloud::getTextFont() const
		{
			return privateTextFont;
		}

		void SymbolCloud::setTextFont(const System::Drawing::Font &value)
		{
			privateTextFont = value;
		}

		SymbolCloud::SymbolCloud()
		{
			height = 60;
			width = 120;
			xPos = 0.0f;
			yPos = 0.0f;

			setName(Utility::GetNextName(GetString()));
			setCaption(getName());

			setLineColor(winrt::Windows::UI::Colors::SkyBlue());
			setFillColor(winrt::Windows::UI::Colors::White());
			setFontColor(winrt::Windows::UI::Colors::Black());
			setTextFont(System::Drawing::Font(L"Arial", 8.0f, System::Drawing::FontStyle::Regular));

			inputAnchoPoints.push_back(new AnchorPoint(0.95f, 0.75f, GetPosition(), GetWidth(), GetHeight(), Right));
			inputAnchoPoints.push_back(new AnchorPoint(0.60f, 0.00f, GetPosition(), GetWidth(), GetHeight(), Top));
			inputAnchoPoints.push_back(new AnchorPoint(0.07f, 0.85f, GetPosition(), GetWidth(), GetHeight(), Left));

			outputAnchoPoints.push_back(new AnchorPoint(0.5f, 1.0f, GetPosition(), GetWidth(), GetHeight(), Bottom));
		}

		bool SymbolCloud::IsHit()
		{
			return (Utility::MousePosition.X >= GetPosition().X && Utility::MousePosition.X <= GetPosition().X + GetWidth() && Utility::MousePosition.Y >= GetPosition().Y && Utility::MousePosition.Y <= GetPosition().Y + GetHeight());
		}

		int SymbolCloud::InputAnchorHit()
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

		int SymbolCloud::OutputAnchorHit()
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

		float SymbolCloud::GetWidth()
		{
			return width;
		}

		float SymbolCloud::GetHeight()
		{
			return height;
		}

		void SymbolCloud::Draw(Canvas canvas)
		{
			PathFigure myPathFigure;

			float heightT = GetHeight() * 0.75f;
			float heightN = GetHeight() - heightT;

			winrt::Windows::Foundation::Point points[5];
			points[0].X = GetPosition().X + (3 * GetWidth() / 16);
			points[0].Y = GetPosition().Y + (5 * heightT / 9) + heightN;
			points[1].X = GetPosition().X + (3 * GetWidth() / 16);
			points[1].Y = GetPosition().Y + heightT + heightN;
			points[2].X = GetPosition().X + GetWidth() - (3 * GetWidth() / 16);
			points[2].Y = GetPosition().Y + heightT + heightN;
			points[3].X = GetPosition().X + GetWidth() - (3 * GetWidth() / 16);
			points[3].Y = GetPosition().Y + (1 * heightT / 3) + heightN;
			points[4].X = GetPosition().X + (GetWidth() / 2) - (3 * GetWidth() / 32);
			points[4].Y = GetPosition().Y + (1 * heightT / 6) + heightN;

			myPathFigure.StartPoint(points[0]);

			ArcSegment arcSegment2;
			arcSegment2.Point(winrt::Windows::Foundation::Point(points[1]));
			arcSegment2.Size(winrt::Windows::Foundation::Size(5 * heightT / 18, 4 * heightT / 18));
			arcSegment2.RotationAngle(0);
			arcSegment2.IsLargeArc(false);
			arcSegment2.SweepDirection(SweepDirection::Counterclockwise);
			myPathFigure.Segments().Append(arcSegment2);
			
			LineSegment lineSegment2;
			lineSegment2.Point(points[2]);
			myPathFigure.Segments().Append(lineSegment2);

			ArcSegment arcSegment3;
			arcSegment3.Point(winrt::Windows::Foundation::Point(points[3]));
			arcSegment3.Size(winrt::Windows::Foundation::Size(2 * heightT / 6, 2 * heightT / 6));
			arcSegment3.RotationAngle(0);
			arcSegment3.IsLargeArc(false);
			arcSegment3.SweepDirection(SweepDirection::Counterclockwise);
			myPathFigure.Segments().Append(arcSegment3);

			ArcSegment arcSegment4;
			arcSegment4.Point(winrt::Windows::Foundation::Point(points[4]));
			arcSegment4.Size(winrt::Windows::Foundation::Size(5 * heightT / 12, 5 * heightT / 12));
			arcSegment4.RotationAngle(0);
			arcSegment4.IsLargeArc(false);
			arcSegment4.SweepDirection(SweepDirection::Counterclockwise);
			myPathFigure.Segments().Append(arcSegment4);

			ArcSegment arcSegment5;
			arcSegment5.Point(winrt::Windows::Foundation::Point(points[0]));
			arcSegment5.Size(winrt::Windows::Foundation::Size(2 * heightT / 6, 2 * heightT / 6));
			arcSegment5.RotationAngle(0);
			arcSegment5.IsLargeArc(false);
			arcSegment5.SweepDirection(SweepDirection::Counterclockwise);
			myPathFigure.Segments().Append(arcSegment5);

			PathGeometry myPathGeometry;
			myPathGeometry.Figures().Append(myPathFigure);

			winrt::Microsoft::UI::Xaml::Shapes::Path myPath;
			//myPath.Fill(SolidColorBrush(getIsSelected() || getIsHover() ? Utility::HighlightBrush(getFillColor()) : getFillColor()));
			myPath.Stroke(SolidColorBrush(getLineColor()));
			myPath.StrokeThickness(getIsSelected() ? 5.0 : 2.5);
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

		void SymbolCloud::SetPosition(float x, float y)
		{
			xPos = x;
			yPos = y;
		}

		winrt::Windows::Foundation::Point SymbolCloud::GetPosition()
		{
			return winrt::Windows::Foundation::Point(xPos, yPos);
		}

		std::vector<AnchorPoint*> SymbolCloud::GetInputAnchorPoints()
		{
			for (size_t i = 0; i < inputAnchoPoints.size(); i++)
			{
				inputAnchoPoints[i]->RefreshPosition(GetPosition(), GetWidth(), GetHeight());
			}
			return inputAnchoPoints;
		}

		std::vector<AnchorPoint*> SymbolCloud::GetOutputAnchorPoints()
		{
			for (size_t i = 0; i < outputAnchoPoints.size(); i++)
			{
				outputAnchoPoints[i]->RefreshPosition(GetPosition(), GetWidth(), GetHeight());
			}
			return outputAnchoPoints;
		}

		AnchorPoint* SymbolCloud::GetInputAnchorPoint(int anchorIndex)
		{
			std::vector<AnchorPoint*> list = GetInputAnchorPoints();

			if (anchorIndex >= 0 && anchorIndex < list.size())
				return list[anchorIndex];

			return 0;
		}

		AnchorPoint* SymbolCloud::GetOutputAnchorPoint(int OutputAnchorIndex)
		{
			std::vector<AnchorPoint*> list = GetOutputAnchorPoints();

			if (OutputAnchorIndex >= 0 && OutputAnchorIndex < list.size())
				return list[OutputAnchorIndex];

			return 0;
		}

		ItemProperty SymbolCloud::GetProperty(int index)
		{
			if (GetPropertyCount() > index && index >= 0)
			{
				return properties[index];
			}
			return ItemProperty();
		}

		void SymbolCloud::SetProperty(int index, ItemProperty property_Renamed)
		{
			if (GetPropertyCount() > index && index >= 0)
			{
				properties[index] = property_Renamed;
			}
		}

		int SymbolCloud::GetPropertyCount()
		{
			return 0;
		}

		FlowChart::Data::ISymbolChart *SymbolCloud::GetInstance()
		{
			return new SymbolCloud();
		}

		FlowChart::Data::ISymbolChart *SymbolCloud::GetDuplicate()
		{
			SymbolCloud *duplictate = new SymbolCloud();

			for (int i = 0; i < GetPropertyCount(); i++)
				duplictate->properties[i] = properties[i];
			
			return duplictate;
		}

		void SymbolCloud::RotateAnchorPoints()
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

		winrt::hstring SymbolCloud::GetString()
		{
			return L"Cloud";
		}

		winrt::hstring SymbolCloud::GetTypeString()
		{
			return L"SymbolCloud";
		}

		winrt::hstring SymbolCloud::ToString()
		{
			winrt::hstring result = L"";

			return L"\t\tName:" + getName() + L"\r\n\t\tTitle:" + getCaption() + L"\r\n\t\tPosition:" + winrt::to_hstring(xPos) + L" " + winrt::to_hstring(yPos) + L"\r\n" + result;
		}
	}
}

#include "pch.h"
#include "SymbolDatabase.h"

namespace FlowChart
{
	namespace Data
	{

		const winrt::hstring &SymbolDatabase::getName() const
		{
			return privateName;
		}

		void SymbolDatabase::setName(const winrt::hstring &value)
		{
			privateName = value;
		}

		const winrt::hstring &SymbolDatabase::getCaption() const
		{
			return privateCaption;
		}

		void SymbolDatabase::setCaption(const winrt::hstring &value)
		{
			privateCaption = value;
		}

		const bool &SymbolDatabase::getIsSelected() const
		{
			return privateIsSelected;
		}

		void SymbolDatabase::setIsSelected(const bool &value)
		{
			privateIsSelected = value;
		}

		const bool &SymbolDatabase::getIsHover() const
		{
			return privateIsHover;
		}

		void SymbolDatabase::setIsHover(const bool &value)
		{
			privateIsHover = value;
		}

		const bool &SymbolDatabase::getIsEditing() const
		{
			return privateIsEditing;
		}

		void SymbolDatabase::setIsEditing(const bool &value)
		{
			privateIsEditing = value;
		}

		winrt::hstring SymbolDatabase::getIconName()
		{
			return L"imgDatabase.png";
		}

		const winrt::Windows::UI::Color &SymbolDatabase::getLineColor() const
		{
			return privateLineColor;
		}

		void SymbolDatabase::setLineColor(const winrt::Windows::UI::Color& value)
		{
			privateLineColor = value;
		}

		const winrt::Windows::UI::Color &SymbolDatabase::getFillColor() const
		{
			return privateFillColor;
		}

		void SymbolDatabase::setFillColor(const winrt::Windows::UI::Color &value)
		{
			privateFillColor = value;
		}

		const winrt::Windows::UI::Color &SymbolDatabase::getFontColor() const
		{
			return privateFontColor;
		}

		void SymbolDatabase::setFontColor(const winrt::Windows::UI::Color &value)
		{
			privateFontColor = value;
		}

		const System::Drawing::Font &SymbolDatabase::getTextFont() const
		{
			return privateTextFont;
		}

		void SymbolDatabase::setTextFont(const System::Drawing::Font &value)
		{
			privateTextFont = value;
		}

		SymbolDatabase::SymbolDatabase()
		{
			height = 80;
			width = 60.0f;
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

		bool SymbolDatabase::IsHit()
		{
			return (Utility::MousePosition.X >= GetPosition().X && Utility::MousePosition.X <= GetPosition().X + GetWidth() && Utility::MousePosition.Y >= GetPosition().Y && Utility::MousePosition.Y <= GetPosition().Y + GetHeight());
		}

		int SymbolDatabase::InputAnchorHit()
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

		int SymbolDatabase::OutputAnchorHit()
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

		float SymbolDatabase::GetWidth()
		{
			return width;
		}

		float SymbolDatabase::GetHeight()
		{
			return height;
		}

		void SymbolDatabase::Draw(Canvas canvas)
		{
			PathFigure myPathFigure;

			winrt::Windows::Foundation::Point points[4];
			points[0].X = GetPosition().X;
			points[0].Y = GetPosition().Y + GetHeight() - (3 * GetHeight() / 16);
			points[1].X = GetPosition().X;
			points[1].Y = GetPosition().Y + (3 * GetHeight() / 16);
			points[2].X = GetPosition().X + GetWidth();
			points[2].Y = GetPosition().Y + (3 * GetHeight() / 16);
			points[3].X = GetPosition().X + GetWidth();
			points[3].Y = GetPosition().Y + GetHeight() - (3 * GetHeight() / 16);

			myPathFigure.StartPoint(points[0]);

			LineSegment lineSegment1;
			lineSegment1.Point(points[1]);
			myPathFigure.Segments().Append(lineSegment1);

			ArcSegment arcSegment1;
			arcSegment1.Point(points[2]);
			arcSegment1.Size(winrt::Windows::Foundation::Size(GetWidth() / 2, 3 * GetHeight() / 16));
			arcSegment1.RotationAngle(0);
			arcSegment1.IsLargeArc(false);
			arcSegment1.SweepDirection(SweepDirection::Counterclockwise);
			myPathFigure.Segments().Append(arcSegment1);

			LineSegment lineSegment2;
			lineSegment2.Point(points[3]);
			myPathFigure.Segments().Append(lineSegment2);

			ArcSegment arcSegment2;
			arcSegment2.Point(points[0]);
			arcSegment2.Size(winrt::Windows::Foundation::Size(GetWidth() / 2, 3 * GetHeight() / 16));
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

			EllipseGeometry myEllipseGeometry;
			myEllipseGeometry.Center(winrt::Windows::Foundation::Point(GetPosition().X + (GetWidth() / 2), GetPosition().Y + (3 * GetHeight() / 16)));
			myEllipseGeometry.RadiusX(GetWidth() / 2);
			myEllipseGeometry.RadiusY(3 * GetHeight() / 16);

			winrt::Microsoft::UI::Xaml::Shapes::Path path1;
			path1.Fill(SolidColorBrush(getIsSelected() || getIsHover() ? Utility::HighlightBrush(getFillColor()) : getFillColor()));
			path1.Stroke(SolidColorBrush(getLineColor()));
			path1.StrokeThickness(getIsSelected() ? 1.0 : 0.5);
			path1.Data(myEllipseGeometry);
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

		void SymbolDatabase::SetPosition(float x, float y)
		{
			xPos = x;
			yPos = y;
		}

		winrt::Windows::Foundation::Point SymbolDatabase::GetPosition()
		{
			return winrt::Windows::Foundation::Point(xPos, yPos);
		}

		std::vector<AnchorPoint*> SymbolDatabase::GetInputAnchorPoints()
		{
			for (size_t i = 0; i < inputAnchoPoints.size(); i++)
			{
				inputAnchoPoints[i]->RefreshPosition(GetPosition(), GetWidth(), GetHeight());
			}
			return inputAnchoPoints;
		}

		std::vector<AnchorPoint*> SymbolDatabase::GetOutputAnchorPoints()
		{
			for (size_t i = 0; i < outputAnchoPoints.size(); i++)
			{
				outputAnchoPoints[i]->RefreshPosition(GetPosition(), GetWidth(), GetHeight());
			}
			return outputAnchoPoints;
		}

		AnchorPoint* SymbolDatabase::GetInputAnchorPoint(int anchorIndex)
		{
			std::vector<AnchorPoint*> list = GetInputAnchorPoints();

			if (anchorIndex >= 0 && anchorIndex < list.size())
				return list[anchorIndex];

			return 0;
		}

		AnchorPoint* SymbolDatabase::GetOutputAnchorPoint(int OutputAnchorIndex)
		{
			std::vector<AnchorPoint*> list = GetOutputAnchorPoints();

			if (OutputAnchorIndex >= 0 && OutputAnchorIndex < list.size())
				return list[OutputAnchorIndex];

			return 0;
		}

		ItemProperty SymbolDatabase::GetProperty(int index)
		{
			if (GetPropertyCount() > index && index >= 0)
			{
				return properties[index];
			}
			return ItemProperty();
		}

		void SymbolDatabase::SetProperty(int index, ItemProperty property_Renamed)
		{
			if (GetPropertyCount() > index && index >= 0)
			{
				properties[index] = property_Renamed;
			}
		}

		int SymbolDatabase::GetPropertyCount()
		{
			return 0;
		}

		ISymbolChart* SymbolDatabase::GetInstance()
		{
			return new SymbolDatabase();
		}

		ISymbolChart* SymbolDatabase::GetDuplicate()
		{
			SymbolDatabase *duplictate = new SymbolDatabase();

			for (int i = 0; i < GetPropertyCount(); i++)
				duplictate->properties[i] = properties[i];
			
			return duplictate;
		}

		void SymbolDatabase::RotateAnchorPoints()
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

		winrt::hstring SymbolDatabase::GetString()
		{
			return L"Database";
		}

		winrt::hstring SymbolDatabase::GetTypeString()
		{
			return L"SymbolDatabase";
		}

		winrt::hstring SymbolDatabase::ToString()
		{
			winrt::hstring result = L"";

			return L"\t\tName:" + getName() + L"\r\n\t\tTitle:" + getCaption() + L"\r\n\t\tPosition:" + winrt::to_hstring(xPos) + L" " + winrt::to_hstring(yPos) + L"\r\n" + result;
		}
	}
}

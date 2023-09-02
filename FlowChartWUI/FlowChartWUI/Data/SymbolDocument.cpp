#include "pch.h"
#include "SymbolDocument.h"

namespace FlowChart
{
	namespace Data
	{

		const winrt::hstring &SymbolDocument::getName() const
		{
			return privateName;
		}

		void SymbolDocument::setName(const winrt::hstring &value)
		{
			privateName = value;
		}

		const winrt::hstring &SymbolDocument::getCaption() const
		{
			return privateCaption;
		}

		void SymbolDocument::setCaption(const winrt::hstring &value)
		{
			privateCaption = value;
		}

		const bool &SymbolDocument::getIsSelected() const
		{
			return privateIsSelected;
		}

		void SymbolDocument::setIsSelected(const bool &value)
		{
			privateIsSelected = value;
		}

		const bool &SymbolDocument::getIsHover() const
		{
			return privateIsHover;
		}

		void SymbolDocument::setIsHover(const bool &value)
		{
			privateIsHover = value;
		}

		const bool &SymbolDocument::getIsEditing() const
		{
			return privateIsEditing;
		}

		void SymbolDocument::setIsEditing(const bool &value)
		{
			privateIsEditing = value;
		}

		winrt::hstring SymbolDocument::getIconName()
		{
			return L"imgDocument.png";
		}

		const winrt::Windows::UI::Color &SymbolDocument::getLineColor() const
		{
			return privateLineColor;
		}

		void SymbolDocument::setLineColor(const winrt::Windows::UI::Color& value)
		{
			privateLineColor = value;
		}

		const winrt::Windows::UI::Color &SymbolDocument::getFillColor() const
		{
			return privateFillColor;
		}

		void SymbolDocument::setFillColor(const winrt::Windows::UI::Color &value)
		{
			privateFillColor = value;
		}

		const winrt::Windows::UI::Color &SymbolDocument::getFontColor() const
		{
			return privateFontColor;
		}

		void SymbolDocument::setFontColor(const winrt::Windows::UI::Color &value)
		{
			privateFontColor = value;
		}

		const System::Drawing::Font &SymbolDocument::getTextFont() const
		{
			return privateTextFont;
		}

		void SymbolDocument::setTextFont(const System::Drawing::Font &value)
		{
			privateTextFont = value;
		}

		SymbolDocument::SymbolDocument()
		{
			height = 60;
			width = 90;
			xPos = 0.0f;
			yPos = 0.0f;

			setName(Utility::GetNextName(GetString()));
			setCaption(getName());

			setLineColor(winrt::Windows::UI::Colors::CadetBlue());
			setFillColor(winrt::Windows::UI::Colors::AliceBlue());
			setFontColor(winrt::Windows::UI::Colors::Black());
			setTextFont(System::Drawing::Font(L"Arial", 8.0f, System::Drawing::FontStyle::Regular));
			properties[0] = ItemProperty(L"documentType", L"Document Type", L"Single", Enumeration, Public, std::vector<winrt::hstring>{L"Single", L"Multi"});

			inputAnchoPoints.push_back(new AnchorPoint(1.0f, 0.5f, GetPosition(), GetWidth(), GetHeight(), Right));
			inputAnchoPoints.push_back(new AnchorPoint(0.5f, 0.0f, GetPosition(), GetWidth(), GetHeight(), Top));
			inputAnchoPoints.push_back(new AnchorPoint(0.0f, 0.5f, GetPosition(), GetWidth(), GetHeight(), Left));

			outputAnchoPoints.push_back(new AnchorPoint(0.5f, 1.0f, GetPosition(), GetWidth(), GetHeight(), Bottom));
		}

		bool SymbolDocument::IsHit()
		{
			return (Utility::MousePosition.X >= GetPosition().X && Utility::MousePosition.X <= GetPosition().X + GetWidth() && Utility::MousePosition.Y >= GetPosition().Y && Utility::MousePosition.Y <= GetPosition().Y + GetHeight());
		}

		int SymbolDocument::InputAnchorHit()
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

		int SymbolDocument::OutputAnchorHit()
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

		float SymbolDocument::GetWidth()
		{
			return width;
		}

		float SymbolDocument::GetHeight()
		{
			return height;
		}

		void SymbolDocument::DrawSingle(Canvas canvas, float x, float y)
		{
			PathFigure myPathFigure;

			winrt::Windows::Foundation::Point points[4];
			points[0].X = x;
			points[0].Y = y + GetHeight();
			points[1].X = x;
			points[1].Y = y;
			points[2].X = x + GetWidth();
			points[2].Y = y;
			points[3].X = x + GetWidth();
			points[3].Y = y + GetHeight();

			myPathFigure.StartPoint(points[0]);
			for (int i = 0; i < 4; i++)
			{
				LineSegment lineSegment;
				lineSegment.Point(points[i]);
				myPathFigure.Segments().Append(lineSegment);
			}

			ArcSegment arcSegment1;
			arcSegment1.Point(winrt::Windows::Foundation::Point(x + (GetWidth() / 2), y + GetHeight()));
			arcSegment1.Size(winrt::Windows::Foundation::Size(GetWidth() / 4, GetHeight() / 8));
			arcSegment1.RotationAngle(0);
			arcSegment1.IsLargeArc(true);
			arcSegment1.SweepDirection(SweepDirection::Counterclockwise);
			myPathFigure.Segments().Append(arcSegment1);

			ArcSegment arcSegment2;
			arcSegment2.Point(winrt::Windows::Foundation::Point(x, y + GetHeight()));
			arcSegment2.Size(winrt::Windows::Foundation::Size(GetWidth() / 4, GetHeight() / 8));
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
		}

		void SymbolDocument::Draw(Canvas canvas)
		{
			if (properties[0].getValue() == L"Multi")
			{
				for (int i = 0; i < 3; i++)
				{
					DrawSingle(canvas, GetPosition().X + (5.0 * i), GetPosition().Y + (5.0 * i));
				}
			}
			else
			{
				DrawSingle(canvas, GetPosition().X, GetPosition().Y);
			}

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

		void SymbolDocument::SetPosition(float x, float y)
		{
			xPos = x;
			yPos = y;
		}

		winrt::Windows::Foundation::Point SymbolDocument::GetPosition()
		{
			return winrt::Windows::Foundation::Point(xPos, yPos);
		}

		std::vector<AnchorPoint*> SymbolDocument::GetInputAnchorPoints()
		{
			for (size_t i = 0; i < inputAnchoPoints.size(); i++)
			{
				inputAnchoPoints[i]->RefreshPosition(GetPosition(), GetWidth(), GetHeight());
			}
			return inputAnchoPoints;
		}

		std::vector<AnchorPoint*> SymbolDocument::GetOutputAnchorPoints()
		{
			for (size_t i = 0; i < outputAnchoPoints.size(); i++)
			{
				outputAnchoPoints[i]->RefreshPosition(GetPosition(), GetWidth(), GetHeight());
			}
			return outputAnchoPoints;
		}

		AnchorPoint* SymbolDocument::GetInputAnchorPoint(int anchorIndex)
		{
			std::vector<AnchorPoint*> list = GetInputAnchorPoints();

			if (anchorIndex >= 0 && anchorIndex < list.size())
				return list[anchorIndex];

			return 0;
		}

		AnchorPoint* SymbolDocument::GetOutputAnchorPoint(int OutputAnchorIndex)
		{
			std::vector<AnchorPoint*> list = GetOutputAnchorPoints();

			if (OutputAnchorIndex >= 0 && OutputAnchorIndex < list.size())
				return list[OutputAnchorIndex];

			return 0;
		}

		ItemProperty SymbolDocument::GetProperty(int index)
		{
			if (GetPropertyCount() > index && index >= 0)
			{
				return properties[index];
			}
			return ItemProperty();
		}

		void SymbolDocument::SetProperty(int index, ItemProperty property_Renamed)
		{
			if (GetPropertyCount() > index && index >= 0)
			{
				properties[index] = property_Renamed;
			}
		}

		int SymbolDocument::GetPropertyCount()
		{
			return 1;
		}

		FlowChart::Data::ISymbolChart *SymbolDocument::GetInstance()
		{
			return new SymbolDocument();
		}

		FlowChart::Data::ISymbolChart *SymbolDocument::GetDuplicate()
		{
			SymbolDocument *duplictate = new SymbolDocument();

			for (int i = 0; i < GetPropertyCount(); i++)
				duplictate->properties[i] = properties[i];
			
			return duplictate;
		}

		void SymbolDocument::RotateAnchorPoints()
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

		winrt::hstring SymbolDocument::GetString()
		{
			return L"Document";
		}

		winrt::hstring SymbolDocument::GetTypeString()
		{
			return L"SymbolDocument";
		}

		winrt::hstring SymbolDocument::ToString()
		{
			winrt::hstring result = L"";

			return L"\t\tName:" + getName() + L"\r\n\t\tTitle:" + getCaption() + L"\r\n\t\tPosition:" + winrt::to_hstring(xPos) + L" " + winrt::to_hstring(yPos) + L"\r\n" + result;
		}
	}
}

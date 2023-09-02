#include "pch.h"
#include "SymbolMerge.h"

namespace FlowChart
{
	namespace Data
	{

		const winrt::hstring &SymbolMerge::getName() const
		{
			return privateName;
		}

		void SymbolMerge::setName(const winrt::hstring &value)
		{
			privateName = value;
		}

		const winrt::hstring &SymbolMerge::getCaption() const
		{
			return privateCaption;
		}

		void SymbolMerge::setCaption(const winrt::hstring &value)
		{
			privateCaption = value;
		}

		const bool &SymbolMerge::getIsSelected() const
		{
			return privateIsSelected;
		}

		void SymbolMerge::setIsSelected(const bool &value)
		{
			privateIsSelected = value;
		}

		const bool &SymbolMerge::getIsHover() const
		{
			return privateIsHover;
		}

		void SymbolMerge::setIsHover(const bool &value)
		{
			privateIsHover = value;
		}

		const bool &SymbolMerge::getIsEditing() const
		{
			return privateIsEditing;
		}

		void SymbolMerge::setIsEditing(const bool &value)
		{
			privateIsEditing = value;
		}

		winrt::hstring SymbolMerge::getIconName()
		{
			return L"imgMerge.png";
		}

		const winrt::Windows::UI::Color &SymbolMerge::getLineColor() const
		{
			return privateLineColor;
		}

		void SymbolMerge::setLineColor(const winrt::Windows::UI::Color& value)
		{
			privateLineColor = value;
		}

		const winrt::Windows::UI::Color &SymbolMerge::getFillColor() const
		{
			return privateFillColor;
		}

		void SymbolMerge::setFillColor(const winrt::Windows::UI::Color &value)
		{
			privateFillColor = value;
		}

		const winrt::Windows::UI::Color &SymbolMerge::getFontColor() const
		{
			return privateFontColor;
		}

		void SymbolMerge::setFontColor(const winrt::Windows::UI::Color &value)
		{
			privateFontColor = value;
		}

		const System::Drawing::Font &SymbolMerge::getTextFont() const
		{
			return privateTextFont;
		}

		void SymbolMerge::setTextFont(const System::Drawing::Font &value)
		{
			privateTextFont = value;
		}

		SymbolMerge::SymbolMerge()
		{
			height = 40;
			width = 60.0f;
			xPos = 0.0f;
			yPos = 0.0f;

			setName(Utility::GetNextName(GetString()));
			setCaption(getName());

			setLineColor(winrt::Windows::UI::Colors::Black());
			setFillColor(winrt::Windows::UI::Colors::SkyBlue());
			setFontColor(winrt::Windows::UI::Colors::Black());
			setTextFont(System::Drawing::Font(L"Arial", 8.0f, System::Drawing::FontStyle::Regular));

			inputAnchoPoints.push_back(new AnchorPoint(0.75f, 0.5f, GetPosition(), GetWidth(), GetHeight(), Right));
			inputAnchoPoints.push_back(new AnchorPoint(0.5f, 0.0f, GetPosition(), GetWidth(), GetHeight(), Top));
			inputAnchoPoints.push_back(new AnchorPoint(0.25f, 0.5f, GetPosition(), GetWidth(), GetHeight(), Left));

			outputAnchoPoints.push_back(new AnchorPoint(0.5f, 1.0f, GetPosition(), GetWidth(), GetHeight(), Bottom));
		}

		bool SymbolMerge::IsHit()
		{
			return (Utility::MousePosition.X >= GetPosition().X && Utility::MousePosition.X <= GetPosition().X + GetWidth() && Utility::MousePosition.Y >= GetPosition().Y && Utility::MousePosition.Y <= GetPosition().Y + GetHeight());
		}

		int SymbolMerge::InputAnchorHit()
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

		int SymbolMerge::OutputAnchorHit()
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

		float SymbolMerge::GetWidth()
		{
			return width;
		}

		float SymbolMerge::GetHeight()
		{
			return height;
		}

		void SymbolMerge::Draw(Canvas canvas)
		{
			PathFigure myPathFigure;

			winrt::Windows::Foundation::Point points[4];
			points[0].X = GetPosition().X;
			points[0].Y = GetPosition().Y;
			points[1].X = GetPosition().X + GetWidth();
			points[1].Y = GetPosition().Y;
			points[2].X = GetPosition().X + (GetWidth() / 2);
			points[2].Y = GetPosition().Y + GetHeight();
			points[3].X = points[0].X;
			points[3].Y = points[0].Y;

			myPathFigure.StartPoint(points[0]);
			for (int i = 0; i < 4; i++)
			{
				LineSegment lineSegment;
				lineSegment.Point(points[i]);
				myPathFigure.Segments().Append(lineSegment);
			}

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

		void SymbolMerge::SetPosition(float x, float y)
		{
			xPos = x;
			yPos = y;
		}

		winrt::Windows::Foundation::Point SymbolMerge::GetPosition()
		{
			return winrt::Windows::Foundation::Point(xPos, yPos);
		}

		std::vector<AnchorPoint*> SymbolMerge::GetInputAnchorPoints()
		{
			for (size_t i = 0; i < inputAnchoPoints.size(); i++)
			{
				inputAnchoPoints[i]->RefreshPosition(GetPosition(), GetWidth(), GetHeight());
			}
			return inputAnchoPoints;
		}

		std::vector<AnchorPoint*> SymbolMerge::GetOutputAnchorPoints()
		{
			for (size_t i = 0; i < outputAnchoPoints.size(); i++)
			{
				outputAnchoPoints[i]->RefreshPosition(GetPosition(), GetWidth(), GetHeight());
			}
			return outputAnchoPoints;
		}

		AnchorPoint* SymbolMerge::GetInputAnchorPoint(int anchorIndex)
		{
			std::vector<AnchorPoint*> list = GetInputAnchorPoints();

			if (anchorIndex >= 0 && anchorIndex < list.size())
				return list[anchorIndex];

			return 0;
		}

		AnchorPoint* SymbolMerge::GetOutputAnchorPoint(int OutputAnchorIndex)
		{
			std::vector<AnchorPoint*> list = GetOutputAnchorPoints();

			if (OutputAnchorIndex >= 0 && OutputAnchorIndex < list.size())
				return list[OutputAnchorIndex];

			return 0;
		}

		ItemProperty SymbolMerge::GetProperty(int index)
		{
			if (GetPropertyCount() > index && index >= 0)
			{
				return properties[index];
			}
			return ItemProperty();
		}

		void SymbolMerge::SetProperty(int index, ItemProperty property_Renamed)
		{
			if (GetPropertyCount() > index && index >= 0)
			{
				properties[index] = property_Renamed;
			}
		}

		int SymbolMerge::GetPropertyCount()
		{
			return 0;
		}

		FlowChart::Data::ISymbolChart *SymbolMerge::GetInstance()
		{
			return new SymbolMerge();
		}

		FlowChart::Data::ISymbolChart *SymbolMerge::GetDuplicate()
		{
			SymbolMerge *duplictate = new SymbolMerge();

			for (int i = 0; i < GetPropertyCount(); i++)
				duplictate->properties[i] = properties[i];
			
			return duplictate;
		}

		void SymbolMerge::RotateAnchorPoints()
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

		winrt::hstring SymbolMerge::GetString()
		{
			return L"Merge";
		}

		winrt::hstring SymbolMerge::GetTypeString()
		{
			return L"SymbolMerge";
		}

		winrt::hstring SymbolMerge::ToString()
		{
			winrt::hstring result = L"";

			return L"\t\tName:" + getName() + L"\r\n\t\tTitle:" + getCaption() + L"\r\n\t\tPosition:" + winrt::to_hstring(xPos) + L" " + winrt::to_hstring(yPos) + L"\r\n" + result;
		}
	}
}

#include "pch.h"
#include "SymbolNote.h"

namespace FlowChart
{
	namespace Data
	{

		const winrt::hstring &SymbolNote::getName() const
		{
			return privateName;
		}

		void SymbolNote::setName(const winrt::hstring &value)
		{
			privateName = value;
		}

		const winrt::hstring &SymbolNote::getCaption() const
		{
			return privateCaption;
		}

		void SymbolNote::setCaption(const winrt::hstring &value)
		{
			privateCaption = value;
		}

		const bool &SymbolNote::getIsSelected() const
		{
			return privateIsSelected;
		}

		void SymbolNote::setIsSelected(const bool &value)
		{
			privateIsSelected = value;
		}

		const bool &SymbolNote::getIsHover() const
		{
			return privateIsHover;
		}

		void SymbolNote::setIsHover(const bool &value)
		{
			privateIsHover = value;
		}

		const bool &SymbolNote::getIsEditing() const
		{
			return privateIsEditing;
		}

		void SymbolNote::setIsEditing(const bool &value)
		{
			privateIsEditing = value;
		}

		winrt::hstring SymbolNote::getIconName()
		{
			return L"imgNote.png";
		}

		const winrt::Windows::UI::Color &SymbolNote::getLineColor() const
		{
			return privateLineColor;
		}

		void SymbolNote::setLineColor(const winrt::Windows::UI::Color& value)
		{
			privateLineColor = value;
		}

		const winrt::Windows::UI::Color &SymbolNote::getFillColor() const
		{
			return privateFillColor;
		}

		void SymbolNote::setFillColor(const winrt::Windows::UI::Color &value)
		{
			privateFillColor = value;
		}

		const winrt::Windows::UI::Color &SymbolNote::getFontColor() const
		{
			return privateFontColor;
		}

		void SymbolNote::setFontColor(const winrt::Windows::UI::Color &value)
		{
			privateFontColor = value;
		}

		const System::Drawing::Font &SymbolNote::getTextFont() const
		{
			return privateTextFont;
		}

		void SymbolNote::setTextFont(const System::Drawing::Font &value)
		{
			privateTextFont = value;
		}

		SymbolNote::SymbolNote()
		{
			headHeight = 40;
			width = 180;
			xPos = 0.0f;
			yPos = 0.0f;
			attributes = std::vector<ItemProperty>();
			operations = std::vector<ItemProperty>();

			setName(Utility::GetNextName(GetString()));
			setCaption(getName());

			setLineColor(winrt::Windows::UI::Colors::Black());
			setFillColor(winrt::Windows::UI::Colors::SkyBlue());
			setFontColor(winrt::Windows::UI::Colors::Black());
			setTextFont(System::Drawing::Font(L"Arial", 8.0f, System::Drawing::FontStyle::Regular));
			GetOutputAnchorPoints();
		}

		bool SymbolNote::IsHit()
		{
			return (Utility::MousePosition.X >= GetPosition().X && Utility::MousePosition.X <= GetPosition().X + GetWidth() && Utility::MousePosition.Y >= GetPosition().Y && Utility::MousePosition.Y <= GetPosition().Y + GetHeight());
		}

		int SymbolNote::AttributeHit()
		{
			return -1;
		}

		int SymbolNote::OperationHit()
		{
			return -1;
		}

		int SymbolNote::InputAnchorHit()
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

		int SymbolNote::OutputAnchorHit()
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

		float SymbolNote::GetWidth()
		{
			return width;
		}

		float SymbolNote::GetHeight()
		{
			return headHeight;
		}

		void SymbolNote::Draw(Canvas canvas)
		{
			winrt::Windows::Foundation::Point points1[6];
			points1[0].X = GetPosition().X + GetWidth();
			points1[0].Y = GetPosition().Y + GetHeight();
			points1[1].X = GetPosition().X;
			points1[1].Y = GetPosition().Y + GetHeight();
			points1[2].X = GetPosition().X;
			points1[2].Y = GetPosition().Y;
			points1[3].X = GetPosition().X + (15 * GetWidth() / 16);
			points1[3].Y = GetPosition().Y;
			points1[4].X = GetPosition().X + GetWidth();
			points1[4].Y = GetPosition().Y + (GetWidth() / 16);
			points1[5].X = points1[0].X;
			points1[5].Y = points1[0].Y;

			PathGeometry myPathGeometry1;

			PathFigure pathFigure1;
			pathFigure1.StartPoint(points1[0]);
			for (int i = 0; i < 6; i++)
			{
				LineSegment lineSegment;
				lineSegment.Point(points1[i]);
				pathFigure1.Segments().Append(lineSegment);
			}
			myPathGeometry1.Figures().Append(pathFigure1);

			winrt::Microsoft::UI::Xaml::Shapes::Path path1;
			path1.Fill(SolidColorBrush(getIsSelected() || getIsHover() ? Utility::HighlightBrush(getFillColor()) : getFillColor()));
			path1.Stroke(SolidColorBrush(getLineColor()));
			path1.StrokeThickness(getIsSelected() ? 1.0 : 0.5);
			path1.Data(myPathGeometry1);

			canvas.Children().Append(path1);

			winrt::Windows::Foundation::Point points2[4];
			points2[0].X = GetPosition().X + (15 * GetWidth() / 16);
			points2[0].Y = GetPosition().Y + (GetWidth() / 16);
			points2[1].X = GetPosition().X + (15 * GetWidth() / 16);
			points2[1].Y = GetPosition().Y;
			points2[2].X = GetPosition().X + GetWidth();
			points2[2].Y = GetPosition().Y + (GetWidth() / 16);
			points2[3].X = points2[0].X;
			points2[3].Y = points2[0].Y;

			PathGeometry myPathGeometry2;

			PathFigure pathFigure2;
			pathFigure2.StartPoint(points2[0]);
			for (int i = 0; i < 4; i++)
			{
				LineSegment lineSegment;
				lineSegment.Point(points2[i]);
				pathFigure2.Segments().Append(lineSegment);
			}
			myPathGeometry2.Figures().Append(pathFigure2);

			winrt::Microsoft::UI::Xaml::Shapes::Path path2;
			path2.Fill(SolidColorBrush(winrt::Windows::UI::Colors::White()));
			path2.Stroke(SolidColorBrush(getLineColor()));
			path2.StrokeThickness(getIsSelected() ? 1.0 : 0.5);
			path2.Data(myPathGeometry2);

			canvas.Children().Append(path2);

			TextBlock textBlock;
			textBlock.Text(winrt::to_hstring(getCaption()));
			textBlock.FontFamily(FontFamily(winrt::to_hstring(getTextFont().Name)));
			textBlock.FontSize(getTextFont().Size * 96.0 / 72.0);
			textBlock.FontWeight(getTextFont().Bold ? winrt::Windows::UI::Text::FontWeights::Bold() : winrt::Windows::UI::Text::FontWeights::Normal());
			textBlock.FontStyle(getTextFont().Italic ? winrt::Windows::UI::Text::FontStyle::Italic : winrt::Windows::UI::Text::FontStyle::Normal);
			textBlock.TextDecorations(getTextFont().Underline ? winrt::Windows::UI::Text::TextDecorations::Underline : winrt::Windows::UI::Text::TextDecorations::None);
			//if (getTextFont().Underline)
			// tdc->Add(TextDecorations::Underline);
			//if (getTextFont().Strikeout)
			// tdc->Add(TextDecorations::Strikethrough);
			//textBlock.TextDecorations(tdc);
			textBlock.Foreground(SolidColorBrush(getFontColor()));
			textBlock.TextAlignment(winrt::Microsoft::UI::Xaml::TextAlignment::Center);
			textBlock.Width(GetWidth());
			Canvas::SetLeft(textBlock, GetPosition().X);
			Canvas::SetTop(textBlock, (GetPosition().Y + (headHeight / 2)) - (10.0 / 2));
			canvas.Children().Append(textBlock);
		}

		void SymbolNote::SetPosition(float x, float y)
		{
			xPos = x;
			yPos = y;
		}

		winrt::Windows::Foundation::Point SymbolNote::GetPosition()
		{
			return winrt::Windows::Foundation::Point(xPos, yPos);
		}

		std::vector<AnchorPoint*> SymbolNote::GetInputAnchorPoints()
		{
			inputAnchoPoints.clear();

			float offsetY = (headHeight / 2.0f);
			offsetY = offsetY / GetHeight();
			inputAnchoPoints.push_back(new AnchorPoint(1.0f, offsetY, GetPosition(), GetWidth(), GetHeight(), Right));
			inputAnchoPoints.push_back(new AnchorPoint(0.5f, 0.0f, GetPosition(), GetWidth(), GetHeight(), Top));
			inputAnchoPoints.push_back(new AnchorPoint(0.0f, offsetY, GetPosition(), GetWidth(), GetHeight(), Left));
			inputAnchoPoints.push_back(new AnchorPoint(0.5f, 1.0f, GetPosition(), GetWidth(), GetHeight(), Bottom));

			return inputAnchoPoints;
		}

		std::vector<AnchorPoint*> SymbolNote::GetOutputAnchorPoints()
		{
			outputAnchoPoints = GetInputAnchorPoints();

			return outputAnchoPoints;
		}

		AnchorPoint* SymbolNote::GetInputAnchorPoint(int anchorIndex)
		{
			std::vector<AnchorPoint*> list = GetInputAnchorPoints();

			if (anchorIndex >= 0 && anchorIndex < list.size())
				return list[anchorIndex];

			return 0;
		}

		AnchorPoint* SymbolNote::GetOutputAnchorPoint(int OutputAnchorIndex)
		{
			std::vector<AnchorPoint*> list = GetOutputAnchorPoints();

			if (OutputAnchorIndex >= 0 && OutputAnchorIndex < list.size())
				return list[OutputAnchorIndex];

			return 0;
		}

		ItemProperty SymbolNote::GetProperty(int index)
		{
			if (GetPropertyCount() > index && index >= 0)
			{
				return properties[index];
			}
			return ItemProperty();
		}

		void SymbolNote::SetProperty(int index, ItemProperty property_Renamed)
		{
			if (GetPropertyCount() > index && index >= 0)
			{
				properties[index] = property_Renamed;
			}
		}

		int SymbolNote::GetPropertyCount()
		{
			return 0;
		}

		void SymbolNote::AddAttribute(ItemProperty property_Renamed)
		{

		}

		ItemProperty SymbolNote::GetSelectedAttribute()
		{
			return ItemProperty();
		}

		void SymbolNote::UpdateSelectedAttribute(ItemProperty property_Renamed)
		{

		}

		void SymbolNote::RemoveSelectedAttribute()
		{

		}

		int SymbolNote::GetAttributeCount()
		{
			return 0;
		}

		void SymbolNote::AddOperation(ItemProperty property_Renamed)
		{

		}

		ItemProperty SymbolNote::GetSelectedOperation()
		{
			return ItemProperty();
		}

		void SymbolNote::UpdateSelectedOperation(ItemProperty property_Renamed)
		{

		}

		void SymbolNote::RemoveSelectedOperation()
		{

		}

		int SymbolNote::GetOperationCount()
		{
			return (int)operations.size();
		}

		FlowChart::Data::ISymbolClass *SymbolNote::GetInstance()
		{
			return new SymbolNote();
		}

		FlowChart::Data::ISymbolClass *SymbolNote::GetDuplicate()
		{
			SymbolNote *duplictate = new SymbolNote();

			for (int i = 0; i < GetPropertyCount(); i++)
				duplictate->properties[i] = properties[i];
			duplictate->attributes = attributes;
			duplictate->operations = operations;
			
			return duplictate;
		}

		winrt::hstring SymbolNote::GetString()
		{
			return L"Note";
		}

		winrt::hstring SymbolNote::GetTypeString()
		{
			return L"NoteSymbol";
		}
	}
}

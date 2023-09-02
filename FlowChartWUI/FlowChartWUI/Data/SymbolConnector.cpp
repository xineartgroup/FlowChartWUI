#include "pch.h"
#include "SymbolConnector.h"

namespace FlowChart
{
	namespace Data
	{

		const winrt::hstring &SymbolConnector::getName() const
		{
			return privateName;
		}

		void SymbolConnector::setName(const winrt::hstring &value)
		{
			privateName = value;
		}

		const winrt::hstring &SymbolConnector::getCaption() const
		{
			return privateCaption;
		}

		void SymbolConnector::setCaption(const winrt::hstring &value)
		{
			privateCaption = value;
		}

		const bool &SymbolConnector::getIsSelected() const
		{
			return privateIsSelected;
		}

		void SymbolConnector::setIsSelected(const bool &value)
		{
			privateIsSelected = value;
		}

		const bool &SymbolConnector::getIsHover() const
		{
			return privateIsHover;
		}

		void SymbolConnector::setIsHover(const bool &value)
		{
			privateIsHover = value;
		}

		const bool &SymbolConnector::getIsEditing() const
		{
			return privateIsEditing;
		}

		void SymbolConnector::setIsEditing(const bool &value)
		{
			privateIsEditing = value;
		}

		winrt::hstring SymbolConnector::getIconName()
		{
			return L"imgConnector.png";
		}

		const winrt::Windows::UI::Color &SymbolConnector::getLineColor() const
		{
			return privateLineColor;
		}

		void SymbolConnector::setLineColor(const winrt::Windows::UI::Color& value)
		{
			privateLineColor = value;
		}

		const winrt::Windows::UI::Color &SymbolConnector::getFillColor() const
		{
			return privateFillColor;
		}

		void SymbolConnector::setFillColor(const winrt::Windows::UI::Color &value)
		{
			privateFillColor = value;
		}

		const winrt::Windows::UI::Color &SymbolConnector::getFontColor() const
		{
			return privateFontColor;
		}

		void SymbolConnector::setFontColor(const winrt::Windows::UI::Color &value)
		{
			privateFontColor = value;
		}

		const System::Drawing::Font &SymbolConnector::getTextFont() const
		{
			return privateTextFont;
		}

		void SymbolConnector::setTextFont(const System::Drawing::Font &value)
		{
			privateTextFont = value;
		}

		SymbolConnector::SymbolConnector()
		{
			height = 60;
			width = 50;
			xPos = 0.0f;
			yPos = 0.0f;

			setName(Utility::GetNextName(GetString()));
			setCaption(getName());

			setLineColor(winrt::Windows::UI::Colors::Black());
			setFillColor(winrt::Windows::UI::Colors::SkyBlue());
			setFontColor(winrt::Windows::UI::Colors::Black());
			setTextFont(System::Drawing::Font(L"Arial", 8.0f, System::Drawing::FontStyle::Regular));
			properties[0] = ItemProperty(L"connectorType", L"Connector Type", L"Normal", Enumeration, Public, std::vector<winrt::hstring>{L"Normal", L"Off-Page"});

			inputAnchoPoints.push_back(new AnchorPoint(1.0f, 0.5f, GetPosition(), GetWidth(), GetHeight(), Right));
			inputAnchoPoints.push_back(new AnchorPoint(0.5f, 0.0f, GetPosition(), GetWidth(), GetHeight(), Top));
			inputAnchoPoints.push_back(new AnchorPoint(0.0f, 0.5f, GetPosition(), GetWidth(), GetHeight(), Left));

			outputAnchoPoints.push_back(new AnchorPoint(0.5f, 1.0f, GetPosition(), GetWidth(), GetHeight(), Bottom));
		}

		bool SymbolConnector::IsHit()
		{
			return (Utility::MousePosition.X >= GetPosition().X && Utility::MousePosition.X <= GetPosition().X + GetWidth() && Utility::MousePosition.Y >= GetPosition().Y && Utility::MousePosition.Y <= GetPosition().Y + GetHeight());
		}

		int SymbolConnector::GetInputAnchorCount()
		{
			return 3;
		}

		int SymbolConnector::InputAnchorHit()
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

		int SymbolConnector::OutputAnchorHit()
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

		float SymbolConnector::GetWidth()
		{
			return width;
		}

		float SymbolConnector::GetHeight()
		{
			return height;
		}

		void SymbolConnector::Draw(Canvas canvas)
		{
			if (properties[0].getValue() == L"Normal")
			{
				width = height;
				EllipseGeometry myEllipseGeometry;
				myEllipseGeometry.Center(winrt::Windows::Foundation::Point(GetPosition().X + (GetWidth() / 2), GetPosition().Y + (GetHeight() / 2)));
				myEllipseGeometry.RadiusX(GetWidth() / 2);
				myEllipseGeometry.RadiusY(GetHeight() / 2);

				winrt::Microsoft::UI::Xaml::Shapes::Path path1;
				path1.Fill(SolidColorBrush(getIsSelected() || getIsHover() ? Utility::HighlightBrush(getFillColor()) : getFillColor()));
				path1.Stroke(SolidColorBrush(getLineColor()));
				path1.StrokeThickness(getIsSelected() ? 1.0 : 0.5);
				path1.Data(myEllipseGeometry);
				canvas.Children().Append(path1);
			}
			else if (properties[0].getValue() == L"Off-Page")
			{
				width = 5 * height / 6;
				winrt::Windows::Foundation::Point points[6];
				points[0].X = GetPosition().X;
				points[0].Y = GetPosition().Y;
				points[1].X = GetPosition().X + GetWidth();
				points[1].Y = GetPosition().Y;
				points[2].X = GetPosition().X + GetWidth();
				points[2].Y = GetPosition().Y + (3 * GetHeight() / 4);
				points[3].X = GetPosition().X + (GetWidth() / 2);
				points[3].Y = GetPosition().Y + GetHeight();
				points[4].X = GetPosition().X;
				points[4].Y = GetPosition().Y + (3 * GetHeight() / 4);
				points[5].X = points[0].X;
				points[5].Y = points[0].Y;

				PathGeometry myPathGeometry1;

				PathFigure pathFigure1;
				pathFigure1.StartPoint(points[0]);
				for (int i = 0; i < 6; i++)
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
			}

			//TextBlock textBlock = new TextBlock();
			//textBlock.Text = Caption;
			//textBlock.FontFamily = new FontFamily(TextFont.Name);
			//textBlock.FontSize = TextFont.Size * 96.0 / 72.0;
			//textBlock.FontWeight = TextFont.Bold ? System.Windows.FontWeights.Bold : System.Windows.FontWeights.Regular;
			//textBlock.FontStyle = TextFont.Italic ? System.Windows.FontStyles.Italic : System.Windows.FontStyles.Normal;
			//TextDecorationCollection tdc = new TextDecorationCollection();
			//if (TextFont.Underline) tdc.Add(TextDecorations.Underline);
			//if (TextFont.Strikeout) tdc.Add(TextDecorations.Strikethrough);
			//textBlock.TextDecorations = tdc;
			//textBlock.Foreground = FontColor;
			//textBlock.TextAlignment = TextAlignment.Center;
			//textBlock.Width = GetWidth();
			//Canvas.SetLeft(textBlock, GetPosition().X);
			//Canvas.SetTop(textBlock, (GetPosition().Y + (GetHeight() / 2)) - (10.0 / 2));
			//canvas.Children.Add(textBlock);
		}

		void SymbolConnector::SetPosition(float x, float y)
		{
			xPos = x;
			yPos = y;
		}

		winrt::Windows::Foundation::Point SymbolConnector::GetPosition()
		{
			return winrt::Windows::Foundation::Point(xPos, yPos);
		}

		std::vector<AnchorPoint*> SymbolConnector::GetInputAnchorPoints()
		{
			for (size_t i = 0; i < inputAnchoPoints.size(); i++)
			{
				inputAnchoPoints[i]->RefreshPosition(GetPosition(), GetWidth(), GetHeight());
			}
			return inputAnchoPoints;
		}

		std::vector<AnchorPoint*> SymbolConnector::GetOutputAnchorPoints()
		{
			for (size_t i = 0; i < outputAnchoPoints.size(); i++)
			{
				outputAnchoPoints[i]->RefreshPosition(GetPosition(), GetWidth(), GetHeight());
			}
			return outputAnchoPoints;
		}

		AnchorPoint* SymbolConnector::GetInputAnchorPoint(int anchorIndex)
		{
			std::vector<AnchorPoint*> list = GetInputAnchorPoints();

			if (anchorIndex >= 0 && anchorIndex < list.size())
				return list[anchorIndex];

			return 0;
		}

		AnchorPoint* SymbolConnector::GetOutputAnchorPoint(int OutputAnchorIndex)
		{
			std::vector<AnchorPoint*> list = GetOutputAnchorPoints();

			if (OutputAnchorIndex >= 0 && OutputAnchorIndex < list.size())
				return list[OutputAnchorIndex];

			return 0;
		}

		ItemProperty SymbolConnector::GetProperty(int index)
		{
			if (GetPropertyCount() > index && index >= 0)
			{
				return properties[index];
			}
			return ItemProperty();
		}

		void SymbolConnector::SetProperty(int index, ItemProperty property_Renamed)
		{
			if (GetPropertyCount() > index && index >= 0)
			{
				properties[index] = property_Renamed;
			}
		}

		int SymbolConnector::GetPropertyCount()
		{
			return 1;
		}

		FlowChart::Data::ISymbolChart *SymbolConnector::GetInstance()
		{
			return new SymbolConnector();
		}

		FlowChart::Data::ISymbolChart *SymbolConnector::GetDuplicate()
		{
			SymbolConnector *duplictate = new SymbolConnector();

			for (int i = 0; i < GetPropertyCount(); i++)
				duplictate->properties[i] = properties[i];
			

			return duplictate;
		}

		void SymbolConnector::RotateAnchorPoints()
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

		winrt::hstring SymbolConnector::GetString()
		{
			return L"Connector";
		}

		winrt::hstring SymbolConnector::GetTypeString()
		{
			return L"SymbolConnector";
		}

		winrt::hstring SymbolConnector::ToString()
		{
			winrt::hstring result = L"";

			return L"\t\tName:" + getName() + L"\r\n\t\tTitle:" + getCaption() + L"\r\n\t\tPosition:" + winrt::to_hstring(xPos) + L" " + winrt::to_hstring(yPos) + L"\r\n" + result;
		}
	}
}

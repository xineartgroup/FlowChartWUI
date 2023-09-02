#include "pch.h"
#include "SymbolSum.h"

namespace FlowChart
{
	namespace Data
	{

		const winrt::hstring &SymbolSum::getName() const
		{
			return privateName;
		}

		void SymbolSum::setName(const winrt::hstring &value)
		{
			privateName = value;
		}

		const winrt::hstring &SymbolSum::getCaption() const
		{
			return privateCaption;
		}

		void SymbolSum::setCaption(const winrt::hstring &value)
		{
			privateCaption = value;
		}

		const bool &SymbolSum::getIsSelected() const
		{
			return privateIsSelected;
		}

		void SymbolSum::setIsSelected(const bool &value)
		{
			privateIsSelected = value;
		}

		const bool &SymbolSum::getIsHover() const
		{
			return privateIsHover;
		}

		void SymbolSum::setIsHover(const bool &value)
		{
			privateIsHover = value;
		}

		const bool &SymbolSum::getIsEditing() const
		{
			return privateIsEditing;
		}

		void SymbolSum::setIsEditing(const bool &value)
		{
			privateIsEditing = value;
		}

		winrt::hstring SymbolSum::getIconName()
		{
			return L"imgSum.png";
		}

		const winrt::Windows::UI::Color &SymbolSum::getLineColor() const
		{
			return privateLineColor;
		}

		void SymbolSum::setLineColor(const winrt::Windows::UI::Color& value)
		{
			privateLineColor = value;
		}

		const winrt::Windows::UI::Color &SymbolSum::getFillColor() const
		{
			return privateFillColor;
		}

		void SymbolSum::setFillColor(const winrt::Windows::UI::Color &value)
		{
			privateFillColor = value;
		}

		const winrt::Windows::UI::Color &SymbolSum::getFontColor() const
		{
			return privateFontColor;
		}

		void SymbolSum::setFontColor(const winrt::Windows::UI::Color &value)
		{
			privateFontColor = value;
		}

		const System::Drawing::Font &SymbolSum::getTextFont() const
		{
			return privateTextFont;
		}

		void SymbolSum::setTextFont(const System::Drawing::Font &value)
		{
			privateTextFont = value;
		}

		SymbolSum::SymbolSum()
		{
			height = 60;
			width = 60.0f;
			xPos = 0.0f;
			yPos = 0.0f;

			setName(Utility::GetNextName(GetString()));
			setCaption(getName());

			setLineColor(winrt::Windows::UI::Colors::Black());
			setFillColor(winrt::Windows::UI::Colors::SkyBlue());
			setFontColor(winrt::Windows::UI::Colors::Black());
			setTextFont(System::Drawing::Font(L"Arial", 8.0f, System::Drawing::FontStyle::Regular));

			inputAnchoPoints.push_back(new AnchorPoint(0.5f, 1.0f, GetPosition(), GetWidth(), GetHeight(), Bottom));

			outputAnchoPoints.push_back(new AnchorPoint(1.0f, 0.5f, GetPosition(), GetWidth(), GetHeight(), Right));
			outputAnchoPoints.push_back(new AnchorPoint(0.5f, 0.0f, GetPosition(), GetWidth(), GetHeight(), Top));
			outputAnchoPoints.push_back(new AnchorPoint(0.0f, 0.5f, GetPosition(), GetWidth(), GetHeight(), Left));
		}

		bool SymbolSum::IsHit()
		{
			return (Utility::MousePosition.X >= GetPosition().X && Utility::MousePosition.X <= GetPosition().X + GetWidth() && Utility::MousePosition.Y >= GetPosition().Y && Utility::MousePosition.Y <= GetPosition().Y + GetHeight());
		}

		int SymbolSum::GetInputAnchorCount()
		{
			return 3;
		}

		int SymbolSum::InputAnchorHit()
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

		int SymbolSum::OutputAnchorHit()
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

		float SymbolSum::GetWidth()
		{
			return width;
		}

		float SymbolSum::GetHeight()
		{
			return height;
		}

		void SymbolSum::Draw(Canvas canvas)
		{
			width = height;
			EllipseGeometry myEllipseGeometry;
			myEllipseGeometry.Center(winrt::Windows::Foundation::Point(GetPosition().X + (GetWidth() / 2), GetPosition().Y + (GetHeight() / 2)));
			myEllipseGeometry.RadiusX(GetWidth() / 2);
			myEllipseGeometry.RadiusY(GetHeight() / 2);

			winrt::Windows::Foundation::Point points[4];
			points[0].X = GetPosition().X + (1.1f * GetWidth() / 8);
			points[0].Y = GetPosition().Y + (1.1f * GetHeight() / 8);
			points[1].X = GetPosition().X + (6.9f * GetWidth() / 8);
			points[1].Y = GetPosition().Y + (6.9f * GetHeight() / 8);
			points[2].X = GetPosition().X + (6.9f * GetWidth() / 8);
			points[2].Y = GetPosition().Y + (1.1f * GetHeight() / 8);
			points[3].X = GetPosition().X + (1.1f * GetWidth() / 8);
			points[3].Y = GetPosition().Y + (6.9f * GetWidth() / 8);

			LineGeometry myLineGeometry1;
			myLineGeometry1.StartPoint(points[0]);
			myLineGeometry1.EndPoint(points[1]);

			LineGeometry myLineGeometry2;
			myLineGeometry2.StartPoint(points[2]);
			myLineGeometry2.EndPoint(points[3]);

			winrt::Microsoft::UI::Xaml::Shapes::Path path1;
			path1.Fill(SolidColorBrush(getIsSelected() || getIsHover() ? Utility::HighlightBrush(getFillColor()) : getFillColor()));
			path1.Stroke(SolidColorBrush(getLineColor()));
			path1.StrokeThickness(getIsSelected() ? 1.0 : 0.5);
			path1.Data(myEllipseGeometry);
			canvas.Children().Append(path1);

			winrt::Microsoft::UI::Xaml::Shapes::Path path2;
			path2.Fill(SolidColorBrush(getIsSelected() || getIsHover() ? Utility::HighlightBrush(getFillColor()) : getFillColor()));
			path2.Stroke(SolidColorBrush(getLineColor()));
			path2.StrokeThickness(getIsSelected() ? 1.0 : 0.5);
			path2.Data(myLineGeometry1);
			canvas.Children().Append(path2);

			winrt::Microsoft::UI::Xaml::Shapes::Path path3;
			path3.Fill(SolidColorBrush(getIsSelected() || getIsHover() ? Utility::HighlightBrush(getFillColor()) : getFillColor()));
			path3.Stroke(SolidColorBrush(getLineColor()));
			path3.StrokeThickness(getIsSelected() ? 1.0 : 0.5);
			path3.Data(myLineGeometry2);
			canvas.Children().Append(path3);
		}

		void SymbolSum::SetPosition(float x, float y)
		{
			xPos = x;
			yPos = y;
		}

		winrt::Windows::Foundation::Point SymbolSum::GetPosition()
		{
			return winrt::Windows::Foundation::Point(xPos, yPos);
		}

		std::vector<AnchorPoint*> SymbolSum::GetInputAnchorPoints()
		{
			for (size_t i = 0; i < inputAnchoPoints.size(); i++)
			{
				inputAnchoPoints[i]->RefreshPosition(GetPosition(), GetWidth(), GetHeight());
			}
			return inputAnchoPoints;
		}

		std::vector<AnchorPoint*> SymbolSum::GetOutputAnchorPoints()
		{
			for (size_t i = 0; i < outputAnchoPoints.size(); i++)
			{
				outputAnchoPoints[i]->RefreshPosition(GetPosition(), GetWidth(), GetHeight());
			}
			return outputAnchoPoints;
		}

		AnchorPoint* SymbolSum::GetInputAnchorPoint(int anchorIndex)
		{
			std::vector<AnchorPoint*> list = GetInputAnchorPoints();

			if (anchorIndex >= 0 && anchorIndex < list.size())
				return list[anchorIndex];

			return 0;
		}

		AnchorPoint* SymbolSum::GetOutputAnchorPoint(int OutputAnchorIndex)
		{
			std::vector<AnchorPoint*> list = GetOutputAnchorPoints();

			if (OutputAnchorIndex >= 0 && OutputAnchorIndex < list.size())
				return list[OutputAnchorIndex];

			return 0;
		}

		ItemProperty SymbolSum::GetProperty(int index)
		{
			if (GetPropertyCount() > index && index >= 0)
			{
				return properties[index];
			}
			return ItemProperty();
		}

		void SymbolSum::SetProperty(int index, ItemProperty property_Renamed)
		{
			if (GetPropertyCount() > index && index >= 0)
			{
				properties[index] = property_Renamed;
			}
		}

		int SymbolSum::GetPropertyCount()
		{
			return 0;
		}

		FlowChart::Data::ISymbolChart *SymbolSum::GetInstance()
		{
			return new SymbolSum();
		}

		FlowChart::Data::ISymbolChart *SymbolSum::GetDuplicate()
		{
			SymbolSum *duplictate = new SymbolSum();

			for (int i = 0; i < GetPropertyCount(); i++)
				duplictate->properties[i] = properties[i];
			
			return duplictate;
		}

		void SymbolSum::RotateAnchorPoints()
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

		winrt::hstring SymbolSum::GetString()
		{
			return L"Sum";
		}

		winrt::hstring SymbolSum::GetTypeString()
		{
			return L"SymbolSum";
		}

		winrt::hstring SymbolSum::ToString()
		{
			winrt::hstring result = L"";

			return L"\t\tName:" + getName() + L"\r\n\t\tTitle:" + getCaption() + L"\r\n\t\tPosition:" + winrt::to_hstring(xPos) + L" " + winrt::to_hstring(yPos) + L"\r\n" + result;
		}
	}
}

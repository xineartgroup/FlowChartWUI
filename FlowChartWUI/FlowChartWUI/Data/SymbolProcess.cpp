#include "pch.h"
#include "SymbolProcess.h"

namespace FlowChart
{
	namespace Data
	{

		const winrt::hstring &SymbolProcess::getName() const
		{
			return privateName;
		}

		void SymbolProcess::setName(const winrt::hstring &value)
		{
			privateName = value;
		}

		const winrt::hstring &SymbolProcess::getCaption() const
		{
			return privateCaption;
		}

		void SymbolProcess::setCaption(const winrt::hstring &value)
		{
			privateCaption = value;
		}

		const bool &SymbolProcess::getIsSelected() const
		{
			return privateIsSelected;
		}

		void SymbolProcess::setIsSelected(const bool &value)
		{
			privateIsSelected = value;
		}

		const bool &SymbolProcess::getIsHover() const
		{
			return privateIsHover;
		}

		void SymbolProcess::setIsHover(const bool &value)
		{
			privateIsHover = value;
		}

		const bool &SymbolProcess::getIsEditing() const
		{
			return privateIsEditing;
		}

		void SymbolProcess::setIsEditing(const bool &value)
		{
			privateIsEditing = value;
		}

		winrt::hstring SymbolProcess::getIconName()
		{
			return L"imgProcess.png";
		}

		const winrt::Windows::UI::Color &SymbolProcess::getLineColor() const
		{
			return privateLineColor;
		}

		void SymbolProcess::setLineColor(const winrt::Windows::UI::Color& value)
		{
			privateLineColor = value;
		}

		const winrt::Windows::UI::Color &SymbolProcess::getFillColor() const
		{
			return privateFillColor;
		}

		void SymbolProcess::setFillColor(const winrt::Windows::UI::Color &value)
		{
			privateFillColor = value;
		}

		const winrt::Windows::UI::Color &SymbolProcess::getFontColor() const
		{
			return privateFontColor;
		}

		void SymbolProcess::setFontColor(const winrt::Windows::UI::Color &value)
		{
			privateFontColor = value;
		}

		const System::Drawing::Font &SymbolProcess::getTextFont() const
		{
			return privateTextFont;
		}

		void SymbolProcess::setTextFont(const System::Drawing::Font &value)
		{
			privateTextFont = value;
		}

		SymbolProcess::SymbolProcess()
		{
			height = 40;
			width = 150;
			xPos = 0.0f;
			yPos = 0.0f;

			setName(Utility::GetNextName(GetString()));
			setCaption(getName());

			setLineColor(winrt::Windows::UI::Colors::Black());
			setFillColor(winrt::Windows::UI::Colors::SkyBlue());
			setFontColor(winrt::Windows::UI::Colors::Black());
			setTextFont(System::Drawing::Font(L"Arial", 8.0f, System::Drawing::FontStyle::Regular));
			properties[0] = ItemProperty(L"processType", L"Process Type", L"Simple", Enumeration, Public, std::vector<winrt::hstring>{L"Simple", L"Alternate", L"Predefined"});
			properties[1] = ItemProperty(L"subFlowchart", L"Sub Flowchart", L"False", Boolean, Public, std::vector<winrt::hstring>());
			properties[2] = ItemProperty(L"flowchartName", L"Flowchart Name", L"", String, Public, std::vector<winrt::hstring>());

			inputAnchoPoints.push_back(new AnchorPoint(1.0f, 0.5f, GetPosition(), GetWidth(), GetHeight(), Right));
			inputAnchoPoints.push_back(new AnchorPoint(0.5f, 0.0f, GetPosition(), GetWidth(), GetHeight(), Top));
			inputAnchoPoints.push_back(new AnchorPoint(0.0f, 0.5f, GetPosition(), GetWidth(), GetHeight(), Left));

			outputAnchoPoints.push_back(new AnchorPoint(0.5f, 1.0f, GetPosition(), GetWidth(), GetHeight(), Bottom));
		}

		bool SymbolProcess::IsHit()
		{
			return (Utility::MousePosition.X >= GetPosition().X && Utility::MousePosition.X <= GetPosition().X + GetWidth() && Utility::MousePosition.Y >= GetPosition().Y && Utility::MousePosition.Y <= GetPosition().Y + GetHeight());
		}

		int SymbolProcess::InputAnchorHit()
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

		int SymbolProcess::OutputAnchorHit()
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

		float SymbolProcess::GetWidth()
		{
			return width;
		}

		float SymbolProcess::GetHeight()
		{
			return height;
		}

		void SymbolProcess::Draw(Canvas canvas)
		{
			RectangleGeometry myRectangleGeometry1;
			myRectangleGeometry1.Rect(winrt::Windows::Foundation::Rect(GetPosition().X, GetPosition().Y, GetWidth(), GetHeight()));

			winrt::Microsoft::UI::Xaml::Shapes::Path path1;
			path1.Fill(SolidColorBrush(getIsSelected() || getIsHover() ? Utility::HighlightBrush(getFillColor()) : getFillColor()));
			path1.Stroke(SolidColorBrush(getLineColor()));
			path1.StrokeThickness(getIsSelected() ? 1.0 : 0.5);
			path1.Data(myRectangleGeometry1);

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

		void SymbolProcess::SetPosition(float x, float y)
		{
			xPos = x;
			yPos = y;
		}

		winrt::Windows::Foundation::Point SymbolProcess::GetPosition()
		{
			return winrt::Windows::Foundation::Point(xPos, yPos);
		}

		std::vector<AnchorPoint*> SymbolProcess::GetInputAnchorPoints()
		{
			for (size_t i = 0; i < inputAnchoPoints.size(); i++)
			{
				inputAnchoPoints[i]->RefreshPosition(GetPosition(), GetWidth(), GetHeight());
			}
			return inputAnchoPoints;
		}

		std::vector<AnchorPoint*> SymbolProcess::GetOutputAnchorPoints()
		{
			for (size_t i = 0; i < outputAnchoPoints.size(); i++)
			{
				outputAnchoPoints[i]->RefreshPosition(GetPosition(), GetWidth(), GetHeight());
			}
			return outputAnchoPoints;
		}

		AnchorPoint* SymbolProcess::GetInputAnchorPoint(int anchorIndex)
		{
			std::vector<AnchorPoint*> list = GetInputAnchorPoints();

			if (anchorIndex >= 0 && anchorIndex < list.size())
				return list[anchorIndex];

			return 0;
		}

		AnchorPoint* SymbolProcess::GetOutputAnchorPoint(int OutputAnchorIndex)
		{
			std::vector<AnchorPoint*> list = GetOutputAnchorPoints();

			if (OutputAnchorIndex >= 0 && OutputAnchorIndex < list.size())
				return list[OutputAnchorIndex];

			return 0;
		}

		ItemProperty SymbolProcess::GetProperty(int index)
		{
			if (GetPropertyCount() > index && index >= 0)
			{
				return properties[index];
			}
			return ItemProperty();
		}

		void SymbolProcess::SetProperty(int index, ItemProperty property_Renamed)
		{
			if (GetPropertyCount() > index && index >= 0)
			{
				properties[index] = property_Renamed;
			}
		}

		int SymbolProcess::GetPropertyCount()
		{
			return 3;
		}

		FlowChart::Data::ISymbolChart *SymbolProcess::GetInstance()
		{
			return new SymbolProcess();
		}

		FlowChart::Data::ISymbolChart *SymbolProcess::GetDuplicate()
		{
			SymbolProcess *duplictate = new SymbolProcess();

			for (int i = 0; i < GetPropertyCount(); i++)
				duplictate->properties[i] = properties[i];

			for (size_t i = 0; i < inputAnchoPoints.size(); i++)
				duplictate->inputAnchoPoints[i] = inputAnchoPoints[i];

			for (size_t i = 0; i < outputAnchoPoints.size(); i++)
				duplictate->outputAnchoPoints[i] = outputAnchoPoints[i];

			return duplictate;
		}

		void SymbolProcess::RotateAnchorPoints()
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

		winrt::hstring SymbolProcess::GetString()
		{
			return L"Process";
		}

		winrt::hstring SymbolProcess::GetTypeString()
		{
			return L"SymbolProcess";
		}

		winrt::hstring SymbolProcess::ToString()
		{
			winrt::hstring result = L"";

			return L"\t\tName:" + getName() + L"\r\n\t\tTitle:" + getCaption() + L"\r\n\t\tPosition:" + winrt::to_hstring(xPos) + L" " + winrt::to_hstring(yPos) + L"\r\n" + result;
		}
	}
}

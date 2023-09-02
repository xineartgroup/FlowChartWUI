#include "pch.h"
#include "Settings.h"

namespace FlowChart
{
	namespace Data
	{
		ISymbol* Settings::NewSymbol = 0;
		std::vector<Link*> Settings::Links = std::vector<Link*>();
		std::vector<ISymbolChart*> Settings::ChartSymbols = std::vector<ISymbolChart*>();
		std::vector<ISymbolClass*> Settings::ClassSymbols = std::vector<ISymbolClass*>();
		
		void Settings::InitializeSymbols()
		{
			ChartSymbols.push_back(new SymbolTerminator());
			ChartSymbols.push_back(new SymbolProcess());
			ChartSymbols.push_back(new SymbolDecision());
			ChartSymbols.push_back(new SymbolData());
			ChartSymbols.push_back(new SymbolInput());
			ChartSymbols.push_back(new SymbolDelay());
			ChartSymbols.push_back(new SymbolExtract());
			ChartSymbols.push_back(new SymbolMerge());
			ChartSymbols.push_back(new SymbolCollate());
			ChartSymbols.push_back(new SymbolSort());
			ChartSymbols.push_back(new SymbolDisplay());
			ChartSymbols.push_back(new SymbolDataStored());
			ChartSymbols.push_back(new SymbolCard());
			ChartSymbols.push_back(new SymbolOperation());
			ChartSymbols.push_back(new SymbolConnector());
			ChartSymbols.push_back(new SymbolPreparation());
			ChartSymbols.push_back(new SymbolDocument());
			ChartSymbols.push_back(new SymbolPaperTape());
			ChartSymbols.push_back(new SymbolHardDisk());
			ChartSymbols.push_back(new SymbolDatabase());
			ChartSymbols.push_back(new SymbolSum());
			ChartSymbols.push_back(new SymbolOr());
			ChartSymbols.push_back(new SymbolComment());
			ChartSymbols.push_back(new SymbolCloud());

			ClassSymbols.push_back(new SymbolClass());
			ClassSymbols.push_back(new SymbolInterface());
			ClassSymbols.push_back(new SymbolNote());
		}

		int Settings::GetChartSymbolCount()
		{
			return (int)ChartSymbols.size();
		}

		int Settings::GetClassSymbolCount()
		{
			return (int)ClassSymbols.size();
		}

		ISymbolChart* Settings::GetChartSymbol(int index)
		{
			if (ChartSymbols.size() > index)
			{
				return ChartSymbols[index];
			}
			return 0;
		}

		ISymbolClass* Settings::GetClassSymbol(int index)
		{
			if (ClassSymbols.size() > index)
			{
				return ClassSymbols[index];
			}
			return 0;
		}

		winrt::hstring Settings::GetJSON()
		{
			winrt::hstring result = L"BEGIN\r\n{\r\n\r\n";

			result = result + L"\r\n\r\n}";

			return result;
		}

		void Settings::DrawInputAnchors(Canvas canvas, ISymbol* symbol)
		{
			if (symbol->getIsHover())
			{
				std::vector<AnchorPoint*> list = symbol->GetInputAnchorPoints();

				for (size_t i = 0; i < list.size(); i++)
				{
					AnchorPoint* anchorPoint1 = symbol->GetInputAnchorPoint((int)i);

					if (anchorPoint1)
					{
						winrt::Windows::Foundation::Point inputPosition = anchorPoint1->getPosition();

						EllipseGeometry myEllipseGeometry;
						myEllipseGeometry.Center(winrt::Windows::Foundation::Point(inputPosition.X, inputPosition.Y));
						myEllipseGeometry.RadiusX(Utility::LINKCONNECTOR);
						myEllipseGeometry.RadiusY(Utility::LINKCONNECTOR);

						winrt::Microsoft::UI::Xaml::Shapes::Path path;
						path.Fill(SolidColorBrush(Utility::BrushAnchor));
						path.Stroke(SolidColorBrush(Utility::BrushFlow));
						path.StrokeThickness(Utility::FlowSize);
						path.Data(myEllipseGeometry);
						canvas.Children().Append(path);
					}
				}
			}
		}

		void Settings::DrawOutputAnchors(Canvas canvas, ISymbol* symbol)
		{
			std::vector<AnchorPoint*> anchors = symbol->GetOutputAnchorPoints();

			Link* link = NULL;

			for (size_t i = 0; i < Links.size(); i++)
			{
				if (Links[i] && Links[i]->ParentSymbol)
				{
					if (Links[i]->ParentSymbol->getName() == symbol->getName())
					{
						link = Links[i];
						break;
					}
				}
			}

			for (size_t i = 0; i < anchors.size(); i++)
			{
				AnchorPoint* anchorPoint = anchors[i]; // symbol->GetOutputAnchorPoint(i);

				if (anchorPoint)
				{
					winrt::Windows::Foundation::Point outputPosition = anchorPoint->getPosition();

					EllipseGeometry myEllipseGeometry;
					myEllipseGeometry.Center(winrt::Windows::Foundation::Point(outputPosition.X, outputPosition.Y));
					myEllipseGeometry.RadiusX(Utility::LINKCONNECTOR);
					myEllipseGeometry.RadiusY(Utility::LINKCONNECTOR);

					winrt::Microsoft::UI::Xaml::Shapes::Path path;
					path.Fill(SolidColorBrush(symbol->OutputAnchorHit() == i ? Utility::BrushLinkHover : Utility::BrushLink));
					path.Stroke(SolidColorBrush(Utility::BrushFlow));
					path.StrokeThickness(Utility::FlowSize);
					path.Data(myEllipseGeometry);
					canvas.Children().Append(path);
				}
			}
		}

		winrt::hstring Settings::Display(const winrt::hstring& text, int maxlenght)
		{
			//if (text.size() > maxlenght)
			//	return text.substr(0, maxlenght - 3) + L"...";
			return text;
		}
	}
}

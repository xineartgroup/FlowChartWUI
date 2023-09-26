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

		winrt::hstring Settings::WriteJSON(std::vector<ISymbol*> symbols)
		{
			std::string result = "";

			try
			{
				json j;

				for (ISymbol* symbol : symbols)
				{
					json s;
					s["Type"] = winrt::to_string(symbol->GetTypeString());
					s["Name"] = winrt::to_string(symbol->getName());
					s["Caption"] = winrt::to_string(symbol->getCaption());
					s["IsSelected"] = symbol->getIsSelected();
					winrt::Windows::Foundation::Point position = symbol->GetPosition();
					s["Position"] = std::to_string((int)position.X) + "," + std::to_string((int)position.Y);
					j.push_back(s);
				}

				for (Link* link : Links)
				{
					json s;
					s["Type"] = "Link";
					s["InputAnchorIndex"] = link->InputAnchorIndex;
					s["OutputAnchorIndex"] = link->OutputAnchorIndex;
					s["Stroke"] = (int)link->Stroke;
					s["StrokeSize"] = link->StrokeSize;
					s["IsSelected"] = link->IsSelected;
					s["ParentSymbol"] = winrt::to_string(link->ParentSymbol->getName());
					s["NextSymbol"] = winrt::to_string(link->NextSymbol->getName());
					j.push_back(s);
				}

				result = j.dump();
			}
			catch (...)
			{

			}

			return winrt::to_hstring(result);
		}

		std::vector<ISymbol*> Settings::ReadJSON(const winrt::hstring& text)
		{
			std::vector<ISymbol*> symbols;

			try
			{
				if (Settings::ChartSymbols.empty())
				{
					Settings::InitializeSymbols();
				}

				json j = json::parse(winrt::to_string(text));

				if (j.is_array())
				{
					for (const auto& s : j)
					{
						winrt::hstring strType = winrt::to_hstring(s["Type"]);

						if (strType == L"Link")
						{
							FlowChart::Data::Link* link = new FlowChart::Data::Link();
							link->InputAnchorIndex = s["InputAnchorIndex"];
							link->OutputAnchorIndex = s["OutputAnchorIndex"];
							link->Stroke = (StrokeStyle)s["Stroke"];
							link->StrokeSize = s["StrokeSize"];
							link->IsSelected = s["IsSelected"];
							link->ParentSymbol = GetSymbol(symbols, winrt::to_hstring(s["ParentSymbol"]));
							link->NextSymbol = GetSymbol(symbols, winrt::to_hstring(s["NextSymbol"]));
							Links.push_back(link);
						}
						else
						{
							for (ISymbolChart* cmd : Settings::ChartSymbols)
							{
								if (strType == cmd->GetTypeString())
								{
									ISymbolChart* symbol = cmd->GetDuplicate();
									symbol->setName(winrt::to_hstring(s["Name"]));
									symbol->setCaption(winrt::to_hstring(s["Caption"]));
									symbol->setIsSelected(s["IsSelected"]);
									winrt::hstring strPos = winrt::to_hstring(s["Position"]);
									std::vector<winrt::hstring> pos = Utility::Split(strPos, L",");
									if (pos.size() >= 2)
									{
										symbol->SetPosition(std::stof(winrt::to_string(pos[0])), std::stof(winrt::to_string(pos[1])));
									}
									symbols.push_back(symbol);
									break;
								}
							}
						}
					}
				}
			}
			catch (...)
			{

			}

			return symbols;
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

		ISymbol* Settings::GetSymbol(std::vector<ISymbol*> symbols, winrt::hstring name)
		{
			for (size_t i = 0; i < symbols.size(); i++)
			{
				if (symbols[i]->getName() == name)
				{
					return symbols[i];
				}
			}
			return nullptr;
		}

		winrt::hstring Settings::Display(const winrt::hstring& text, int maxlenght)
		{
			//if (text.size() > maxlenght)
			//	return text.substr(0, maxlenght - 3) + L"...";
			return text;
		}
	}
}

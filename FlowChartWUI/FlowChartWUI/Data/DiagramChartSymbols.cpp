#include "pch.h"
#include "DiagramChartSymbols.h"

namespace FlowChart
{
	namespace Data
	{
		void DiagramChartSymbols::Draw(Canvas canvas)
		{
			if (Utility::LinkItem >= 0 && Utility::LinkItem < Symbols.size() &&
				Utility::LinkingIndex >= 0 && Utility::LinkingIndex < Symbols[Utility::LinkItem]->GetInputAnchorPoints().size())
			{
				FlowChart::Data::Link* link = new FlowChart::Data::Link();
				link->OutputAnchorIndex = Utility::LinkingIndex;
				link->ParentSymbol = Symbols[Utility::LinkItem];
				link->DrawLinking(canvas);
			}
			for (size_t i = 0; i < Symbols.size(); i++)
			{
				Settings::DrawInputAnchors(canvas, Symbols[i]);
				Symbols[i]->Draw(canvas);
				Settings::DrawOutputAnchors(canvas, Symbols[i]);
			}
			for (size_t j = 0; j < Settings::Links.size(); j++)
			{
				Settings::Links[j]->Draw(canvas);
			}
		}

		void DiagramChartSymbols::SetHoverItem()
		{
			for (size_t i = 0; i < Symbols.size(); i++)
			{
				Symbols[i]->setIsHover(Symbols[i]->IsHit());
				for (size_t j = 0; j < Settings::Links.size(); j++)
				{
					if (Settings::Links[j] && Settings::Links[j]->ParentSymbol)
					{
						if (Settings::Links[j]->ParentSymbol->getName() == Symbols[i]->getName())
						{
							Settings::Links[j]->IsHover = Settings::Links[j]->IsHit();
						}
					}
				}
			}
		}

		FlowChart::Data::PointerHit *DiagramChartSymbols::SelectHit()
		{
			PointerHit *result = new PointerHit();

			if (Utility::LinkingIndex >= 0)
			{
				Utility::LinkItem = -1;
			}

			for (size_t i = 0; i < Symbols.size(); i++)
			{
				if (Utility::LinkingIndex < 0)
				{
					int outputAnchorHit = Symbols[i]->OutputAnchorHit();
					if (outputAnchorHit >= 0)
					{
						Utility::LinkingIndex = outputAnchorHit;
						Utility::LinkItem = (int)i;
						result->ItemIndex = outputAnchorHit;
						result->Itemtype = Anchor;
					}
				}

				Symbols[i]->setIsSelected(Symbols[i]->IsHit());

				if (Symbols[i]->getIsSelected())
				{
					Utility::LinkItem = (int)i;
					result->ItemIndex = (int)i;
					result->Itemtype = Symbol;
				}

				for (size_t j = 0; j < Settings::Links.size(); j++)
				{
					Settings::Links[j]->IsSelected = Settings::Links[j]->IsHit();
					//Settings::Links[j]->OutputAnchorIndex = Utility::LinkingIndex;
					if (Settings::Links[j]->IsSelected)
					{
						result->ItemIndex = (int)j;
						result->Itemtype = ItemType::Linker;
					}
				}
			}

			return result;
		}

		void DiagramChartSymbols::Link()
		{
			for (size_t i = 0; i < Symbols.size(); i++)
			{
				if (Symbols[i]->IsHit())
				{
					if (Utility::LinkItem >= 0 && Utility::LinkItem < Symbols.size())
					{
						if (Utility::LinkingIndex >= 0 && Utility::LinkingIndex < Symbols[Utility::LinkItem]->GetInputAnchorPoints().size())
						{
							if (Utility::LinkItem != i)
							{
								FlowChart::Data::Link *link = new FlowChart::Data::Link();
								link->InputAnchorIndex = Symbols[i]->InputAnchorHit();
								link->OutputAnchorIndex = Utility::LinkingIndex;
								link->ParentSymbol = Symbols[Utility::LinkItem];
								link->NextSymbol = Symbols[i];
								Settings::Links.push_back(link);
							}
						}
					}
				}
			}
		}

		void DiagramChartSymbols::MoveSelection(float changeX, float changeY)
		{
			for (size_t i = 0; i < Symbols.size(); i++)
			{
				if (Symbols[i]->getIsSelected())
				{
					float x = Symbols[i]->GetPosition().X + changeX;
					float y = Symbols[i]->GetPosition().Y + changeY;
					Symbols[i]->SetPosition(x, y);
				}
			}
		}

		void DiagramChartSymbols::AddSymbol(ISymbolChart *symbol)
		{
			Symbols.push_back(symbol);
		}

		ISymbolChart* DiagramChartSymbols::GetSelection()
		{
			for (size_t i = 0; i < Symbols.size(); i++)
			{
				if (Symbols[i]->getIsSelected())
				{
					return Symbols[i];
				}
			}
			return 0;
		}

		void DiagramChartSymbols::DeleteSelectedSymbol()
		{
			size_t count = Symbols.size();
			for (size_t i = 0; i < count; i++)
			{
				if (Symbols[i]->getIsSelected())
				{
					for (size_t j = 0; j < count; j++)
					{
						for (size_t k = 0; k < Settings::Links.size(); k++)
						{
							if (Settings::Links[k] && Settings::Links[k]->NextSymbol)
							{
								if (Symbols[i]->getName() == Settings::Links[k]->NextSymbol->getName())
								{
									Settings::Links.erase(Settings::Links.begin() + k);
								}
							}
						}
					}
					Symbols.erase(Symbols.begin() + i);
				}
				count = Symbols.size();
			}
		}

		void DiagramChartSymbols::DeleteSelectedLink()
		{
			//if a symbol is selected
			for (size_t i = 0; i < Symbols.size(); i++)
			{
				for (size_t k = 0; k < Settings::Links.size(); k++)
				{
					if (Settings::Links[k] && Settings::Links[k]->NextSymbol)
					{
						if (Symbols[i]->getIsSelected())
						{
							Settings::Links.erase(Settings::Links.begin() + k);
						}
					}
				}
			}
			//if a link is selected
			for (size_t i = 0; i < Symbols.size(); i++)
			{
				for (size_t k = 0; k < Settings::Links.size(); k++)
				{
					if (Settings::Links[k] != 0)
					{
						if (Settings::Links[k]->IsSelected)
						{
							Settings::Links.erase(Settings::Links.begin() + k);
						}
					}
				}
			}
		}

		void DiagramChartSymbols::ClearSymbols()
		{
			Symbols.clear();
		}

		void DiagramChartSymbols::DuplicateSymbol()
		{
			size_t count = Symbols.size();
			for (size_t i = 0; i < count; i++)
			{
				if (Symbols[i]->getIsSelected())
				{
					Symbols.push_back(Symbols[i]->GetDuplicate());
				}
			}
		}

		void DiagramChartSymbols::ReadJSON(const winrt::hstring &text)
		{
			/*
			bool addingCmd = false;
			for (winrt::hstring::const_iterator line = text.Split("\r\n"->ToCharArray(), StringSplitOptions::RemoveEmptyEntries).begin(); line != text.Split("\r\n"->ToCharArray(), StringSplitOptions::RemoveEmptyEntries).end(); ++line)
			{
				bool isSymbol = false;

				if (Settings::ChartSymbols.empty())
				{
					Settings::InitializeSymbols();
				}

				for (std::vector<ISymbolChart*>::const_iterator cmd = Settings::ChartSymbols.begin(); cmd != Settings::ChartSymbols.end(); ++cmd)
				{
					if ((*line).Trim()->EndsWith((*cmd)->GetTypeString()))
					{
						Symbols.push_back(*cmd);
						isSymbol = true;
						break;
					}
				}

				if (!isSymbol)
				{
					if ((*line).Trim()->Contains("Name:"))
					{
						if (addingCmd)
						{
							Symbols[Symbols.size() - 1]->setName((*line).Replace("Name:", "")->Trim());
						}
					}
					else if ((*line).Trim()->Contains("Caption:"))
					{
						if (addingCmd)
						{
							Symbols[Symbols.size() - 1]->setCaption((*line).Replace("Caption:", "")->Trim());
						}
					}
					else if ((*line).Trim()->Contains("Position:"))
					{
						try
						{
							winrt::hstring strPos = (*line).Replace("Position:", "")->Trim();
							winrt::hstring *pos = strPos.Split((winrt::hstring(" "))->ToCharArray(), StringSplitOptions::RemoveEmptyEntries);
							if (sizeof(pos) / sizeof(pos[0]) >= 2)
							{
								Symbols[Symbols.size() - 1]->SetPosition(StringConverterHelper::fromString<int>(pos[0]), StringConverterHelper::fromString<int>(pos[1]));
							}
						}
						catch (...)
						{

						}
					}
					else if ((*line).Trim()->Contains("Next:"))
					{
						//ISymbolChart tempCmd = new Symbol();
						//tempCmd.Name = line.Replace("Next:", "").Trim();
						//tempCmd.Caption = string.Empty;
						//ChartSymbols[ChartSymbols.Count - 1].SetNextSymbol(tempCmd);
					}
					else if ((*line).Trim()->Contains("Next2:"))
					{
						//ISymbolChart tempCmd = new Symbol();
						//tempCmd.Name = line.Replace("Next2:", "").Trim();
						//tempCmd.Caption = string.Empty;
						//ChartSymbols[ChartSymbols.Count - 1].SetNextSymbols(new List<ISymbolChart>() { tempCmd });
					}
				}
			}
			*/
		}
	}
}

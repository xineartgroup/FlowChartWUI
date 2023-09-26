#include "pch.h"
#include "DiagramChartSymbols.h"

namespace FlowChart
{
	namespace Data
	{
		void DiagramChartSymbols::Draw(Canvas canvas)
		{
			if (Utility::LinkItem >= 0 && Utility::LinkItem < symbols.size() &&
				Utility::LinkingIndex >= 0 && Utility::LinkingIndex < symbols[Utility::LinkItem]->GetInputAnchorPoints().size())
			{
				FlowChart::Data::Link* link = new FlowChart::Data::Link();
				link->OutputAnchorIndex = Utility::LinkingIndex;
				link->ParentSymbol = symbols[Utility::LinkItem];
				link->DrawLinking(canvas);
			}
			for (size_t i = 0; i < symbols.size(); i++)
			{
				Settings::DrawInputAnchors(canvas, symbols[i]);
				symbols[i]->Draw(canvas);
				Settings::DrawOutputAnchors(canvas, symbols[i]);
			}
			for (size_t j = 0; j < Settings::Links.size(); j++)
			{
				Settings::Links[j]->Draw(canvas);
			}
		}

		void DiagramChartSymbols::SetHoverItem()
		{
			for (size_t i = 0; i < symbols.size(); i++)
			{
				symbols[i]->setIsHover(symbols[i]->IsHit());
				for (size_t j = 0; j < Settings::Links.size(); j++)
				{
					if (Settings::Links[j] && Settings::Links[j]->ParentSymbol)
					{
						if (Settings::Links[j]->ParentSymbol->getName() == symbols[i]->getName())
						{
							Settings::Links[j]->IsHover = Settings::Links[j]->IsHit();
						}
					}
				}
			}
		}

		FlowChart::Data::PointerHit DiagramChartSymbols::SelectHit(bool multi)
		{
			PointerHit result;

			if (Utility::LinkingIndex >= 0)
			{
				Utility::LinkItem = -1;
			}

			for (size_t i = 0; i < symbols.size(); i++)
			{
				if (Utility::LinkingIndex < 0)
				{
					int outputAnchorHit = symbols[i]->OutputAnchorHit();
					if (outputAnchorHit >= 0)
					{
						Utility::LinkingIndex = outputAnchorHit;
						Utility::LinkItem = (int)i;
						result.ItemIndex = outputAnchorHit;
						result.Itemtype = Anchor;
					}
				}

				bool select = multi && symbols[i]->getIsSelected();

				symbols[i]->setIsSelected(symbols[i]->IsHit() || select);

				if (symbols[i]->getIsSelected())
				{
					Utility::LinkItem = (int)i;
					result.ItemIndex = (int)i;
					result.Itemtype = Symbol;
				}

				for (size_t j = 0; j < Settings::Links.size(); j++)
				{
					Settings::Links[j]->IsSelected = Settings::Links[j]->IsHit();
					//Settings::Links[j]->OutputAnchorIndex = Utility::LinkingIndex;
					if (Settings::Links[j]->IsSelected)
					{
						result.ItemIndex = (int)j;
						result.Itemtype = ItemType::Linker;
					}
				}
			}

			return result;
		}

		void DiagramChartSymbols::Link()
		{
			for (size_t i = 0; i < symbols.size(); i++)
			{
				if (symbols[i]->IsHit())
				{
					if (Utility::LinkItem >= 0 && Utility::LinkItem < symbols.size())
					{
						if (Utility::LinkingIndex >= 0 && Utility::LinkingIndex < symbols[Utility::LinkItem]->GetInputAnchorPoints().size())
						{
							if (Utility::LinkItem != i)
							{
								FlowChart::Data::Link *link = new FlowChart::Data::Link();
								link->InputAnchorIndex = symbols[i]->InputAnchorHit();
								link->OutputAnchorIndex = Utility::LinkingIndex;
								link->ParentSymbol = symbols[Utility::LinkItem];
								link->NextSymbol = symbols[i];
								Settings::Links.push_back(link);
							}
						}
					}
				}
			}
		}

		void DiagramChartSymbols::MoveSelection(float changeX, float changeY)
		{
			for (size_t i = 0; i < symbols.size(); i++)
			{
				if (symbols[i]->getIsSelected())
				{
					float x = symbols[i]->GetPosition().X + changeX;
					float y = symbols[i]->GetPosition().Y + changeY;
					symbols[i]->SetPosition(x, y);
				}
			}
		}

		void DiagramChartSymbols::AddSymbol(ISymbolChart *symbol)
		{
			symbols.push_back(symbol);
		}

		ISymbolChart* DiagramChartSymbols::GetSelection()
		{
			for (size_t i = 0; i < symbols.size(); i++)
			{
				if (symbols[i]->getIsSelected())
				{
					return symbols[i];
				}
			}
			return NULL;
		}

		void DiagramChartSymbols::DeleteSelectedSymbol()
		{
			size_t count = symbols.size();
			for (size_t i = 0; i < count; i++)
			{
				if (symbols[i]->getIsSelected())
				{
					for (size_t j = 0; j < count; j++)
					{
						for (size_t k = 0; k < Settings::Links.size(); k++)
						{
							if (Settings::Links[k] && Settings::Links[k]->NextSymbol)
							{
								if (symbols[i]->getName() == Settings::Links[k]->NextSymbol->getName())
								{
									Settings::Links.erase(Settings::Links.begin() + k);
								}
							}
						}
					}
					symbols.erase(symbols.begin() + i);
				}
				count = symbols.size();
			}
		}

		void DiagramChartSymbols::DeleteSelectedLink()
		{
			//if a symbol is selected
			for (size_t i = 0; i < symbols.size(); i++)
			{
				for (size_t k = 0; k < Settings::Links.size(); k++)
				{
					if (Settings::Links[k] && Settings::Links[k]->NextSymbol)
					{
						if (symbols[i]->getIsSelected())
						{
							Settings::Links.erase(Settings::Links.begin() + k);
						}
					}
				}
			}
			//if a link is selected
			for (size_t i = 0; i < symbols.size(); i++)
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
			symbols.clear();
		}

		void DiagramChartSymbols::DuplicateSymbol()
		{
			size_t count = symbols.size();
			for (size_t i = 0; i < count; i++)
			{
				if (symbols[i]->getIsSelected())
				{
					symbols.push_back(symbols[i]->GetDuplicate());
				}
			}
		}

		std::vector<ISymbolChart*> DiagramChartSymbols::GetAllSymbols()
		{
			return symbols;
		}
	}
}

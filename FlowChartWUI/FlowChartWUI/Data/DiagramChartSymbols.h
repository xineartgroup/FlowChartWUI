#pragma once

#include "ISymbolChart.h"
#include "Settings.h"
#include "PointerHit.h"
#include "Link.h"
#include <string>
#include <vector>

using namespace winrt::Microsoft::UI::Xaml::Controls;

namespace FlowChart
{
	namespace Data
	{
		class DiagramChartSymbols
		{
		public:
			std::vector<ISymbolChart*> Symbols;

			void Draw(Canvas canvas);

			void SetHoverItem();

			PointerHit *SelectHit();

			void Link();

			void MoveSelection(float changeX, float changeY);

			void AddSymbol(ISymbolChart *symbol);

			ISymbolChart* GetSelection();

			void DeleteSelectedSymbol();

			void DeleteSelectedLink();

			void ClearSymbols();

			void DuplicateSymbol();

			void ReadJSON(const winrt::hstring &text);
		};
	}
}

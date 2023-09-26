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
		private:
			std::vector<ISymbolChart*> symbols;

		public:
			void Draw(Canvas canvas);

			void SetHoverItem();

			PointerHit SelectHit(bool multi);

			void Link();

			void MoveSelection(float changeX, float changeY);

			void AddSymbol(ISymbolChart *symbol);

			ISymbolChart* GetSelection();

			void DeleteSelectedSymbol();

			void DeleteSelectedLink();

			void ClearSymbols();

			void DuplicateSymbol();

			std::vector<ISymbolChart*> GetAllSymbols();
		};
	}
}

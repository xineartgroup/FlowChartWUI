#pragma once

#include "ISymbolClass.h"
#include "Settings.h"
#include "PointerHit.h"
#include "Link.h"
#include "ItemProperty.h"
#include "PropertyType.h"
#include "PropertyVisibility.h"
#include <string>
#include <vector>

namespace FlowChart
{
	namespace Data
	{
		class DiagramClassSymbols
		{
		public:
			DiagramClassSymbols();

			std::vector<ISymbolClass*> Symbols;

			void Draw(Canvas canvas);

			void SetHoverItem();

			PointerHit *SelectHit();

			void Link();

			void MoveSelection(float changeX, float changeY);

			void AddSymbol(ISymbolClass *symbol);

			ISymbolClass* GetSelection();

			void DeleteSelectedSymbol();

			void DeleteSelectedLink();

			void ClearSymbols();

			void ReadJSON(const winrt::hstring &text);

			void AddAttribute();

			void AddOperation();

			void DuplicateSymbol();
		};
	}
}

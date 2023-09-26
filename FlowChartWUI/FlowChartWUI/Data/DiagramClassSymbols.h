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
		private:
			std::vector<ISymbolClass*> symbols;

		public:
			DiagramClassSymbols();

			void Draw(Canvas canvas);

			void SetHoverItem();

			PointerHit SelectHit(bool multi);

			void Link();

			void MoveSelection(float changeX, float changeY);

			void AddSymbol(ISymbolClass *symbol);

			ISymbolClass* GetSelection();

			void DeleteSelectedSymbol();

			void DeleteSelectedLink();

			void ClearSymbols();

			void AddAttribute();

			void AddOperation();

			void DuplicateSymbol();
		};
	}
}

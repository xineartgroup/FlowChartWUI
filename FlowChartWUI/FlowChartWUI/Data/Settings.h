#pragma once

#include "SymbolTerminator.h"
#include "SymbolProcess.h"
#include "SymbolDecision.h"
#include "SymbolData.h"
#include "SymbolInput.h"
#include "SymbolDelay.h"
#include "SymbolExtract.h"
#include "SymbolMerge.h"
#include "SymbolCollate.h"
#include "SymbolSort.h"
#include "SymbolDisplay.h"
#include "SymbolDataStored.h"
#include "SymbolCard.h"
#include "SymbolOperation.h"
#include "SymbolConnector.h"
#include "SymbolPreparation.h"
#include "SymbolDocument.h"
#include "SymbolPaperTape.h"
#include "SymbolHardDisk.h"
#include "SymbolDatabase.h"
#include "SymbolSum.h"
#include "SymbolOr.h"
#include "SymbolComment.h"
#include "SymbolCloud.h"
#include "SymbolClass.h"
#include "SymbolInterface.h"
#include "SymbolNote.h"
#include "PropertyVisibility.h"
#include "Link.h"
#include <string>
#include <vector>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

namespace FlowChart
{
	namespace Data
	{
		class Settings
		{
		public:
			static ISymbol* NewSymbol;
			static std::vector<Link*> Links;
			static std::vector<ISymbolChart*> ChartSymbols;
			static std::vector<ISymbolClass*> ClassSymbols;

			static void InitializeSymbols();

			static int GetChartSymbolCount();

			static int GetClassSymbolCount();

			static ISymbolChart* GetChartSymbol(int index);

			static ISymbolClass* GetClassSymbol(int index);

			static winrt::hstring WriteJSON(std::vector<ISymbol*> symbols);

			static std::vector<ISymbol*>  ReadJSON(const winrt::hstring& text);

			static void DrawInputAnchors(Canvas canvas, ISymbol *symbol);

			static void DrawOutputAnchors(Canvas canvas, ISymbol *symbol);

			static ISymbol* GetSymbol(std::vector<ISymbol*> symbols, winrt::hstring name);

			static winrt::hstring Display(const winrt::hstring &text, int maxlenght);
		};
	}
}

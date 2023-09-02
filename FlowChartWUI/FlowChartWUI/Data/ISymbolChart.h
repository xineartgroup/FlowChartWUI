#pragma once

#include "ISymbol.h"

namespace FlowChart
{
	namespace Data
	{
		class ISymbolChart : public FlowChart::Data::ISymbol
		{
		public:
			virtual ISymbolChart *GetInstance() = 0;

			virtual ISymbolChart *GetDuplicate() = 0;

			virtual void RotateAnchorPoints() = 0;
		};
	}
}

#pragma once

#include "ISymbol.h"

namespace FlowChart
{
	namespace Data
	{
		class ISymbolClass : public FlowChart::Data::ISymbol
		{
		public:
			virtual int AttributeHit() = 0;

			virtual int OperationHit() = 0;

			virtual ISymbolClass *GetInstance() = 0;

			virtual ISymbolClass *GetDuplicate() = 0;

			virtual ItemProperty GetSelectedAttribute() = 0;

			virtual void AddAttribute(ItemProperty) = 0;

			virtual void UpdateSelectedAttribute(ItemProperty) = 0;

			virtual void RemoveSelectedAttribute() = 0;

			virtual int GetAttributeCount() = 0;

			virtual ItemProperty GetSelectedOperation() = 0;

			virtual void AddOperation(ItemProperty) = 0;

			virtual void UpdateSelectedOperation(ItemProperty) = 0;

			virtual void RemoveSelectedOperation() = 0;

			virtual int GetOperationCount() = 0;
		};
	}
}

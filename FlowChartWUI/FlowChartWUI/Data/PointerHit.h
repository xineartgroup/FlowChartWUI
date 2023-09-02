#pragma once

#include "ItemType.h"

namespace FlowChart
{
	namespace Data
	{
		class PointerHit
		{
		public:
			ItemType Itemtype;
			int ItemIndex;
			int SubItemIndex;

			PointerHit();

			PointerHit(ItemType itemType, int itemIndex, int subItemIndex);
		};
	}
}

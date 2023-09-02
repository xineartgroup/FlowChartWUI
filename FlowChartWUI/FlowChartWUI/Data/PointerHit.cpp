#include "pch.h"
#include "PointerHit.h"

namespace FlowChart
{
	namespace Data
	{

		PointerHit::PointerHit()
		{
			Itemtype = ItemType::None;
			ItemIndex = -1;
			SubItemIndex = -1;
		}

		PointerHit::PointerHit(ItemType itemType, int itemIndex, int subItemIndex)
		{
			Itemtype = itemType;
			ItemIndex = itemIndex;
			SubItemIndex = subItemIndex;
		}
	}
}

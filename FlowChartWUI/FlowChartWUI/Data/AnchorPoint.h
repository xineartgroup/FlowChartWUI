#pragma once

#include "LinkAnchorPlacement.h"
#include <string>

namespace FlowChart
{
	namespace Data
	{
		class AnchorPoint
		{
		public:
			float OffsetX;
			float OffsetY;

			private:
				winrt::Windows::Foundation::Point privatePosition;
			public:
				const winrt::Windows::Foundation::Point getPosition() const;
				void setPosition(const winrt::Windows::Foundation::Point &value);

			private:
				LinkAnchorPlacement privatePlacement;
			public:
				const LinkAnchorPlacement getPlacement() const;
				void setPlacement(const LinkAnchorPlacement &value);

				void RefreshPosition(winrt::Windows::Foundation::Point parentPosition, float parentWidth, float parentHeight);

			AnchorPoint();

			AnchorPoint(float offsetX, float offsetY, winrt::Windows::Foundation::Point parentPosition, float parentWidth, float parentHeight, LinkAnchorPlacement placement);

			AnchorPoint(AnchorPoint* temp);

			virtual winrt::hstring ToString();
		};
	}
}

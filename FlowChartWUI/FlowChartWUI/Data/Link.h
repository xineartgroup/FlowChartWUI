#pragma once

#include "StrokeStyle.h"
#include "ISymbol.h"
#include "Utility.h"
#include "AnchorPoint.h"
#include "LinkAnchorPlacement.h"
#include "Spline2D.h"
#include <vector>
#include <cmath>

using namespace winrt::Microsoft::UI::Xaml::Media;

namespace FlowChart
{
	namespace Data
	{
		class Link
		{
		private:
			float MARGIN;
			std::vector<winrt::Windows::Foundation::Point> linkPoints;

		public:
			bool IsHover;
			bool IsSelected;
			int InputAnchorIndex;
			int OutputAnchorIndex;
			float StrokeSize = 1.0f;
			StrokeStyle Stroke = StrokeStyle::Solid;
			ISymbol* NextSymbol;
			ISymbol* ParentSymbol;

			Link();

			bool IsHit();

			void Draw(Canvas canvas);

			void DrawLinking(Canvas canvas);

		private:
			void SetLinkPoints(bool recalculate);
		};
	}
}

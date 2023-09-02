#include "pch.h"
#include "AnchorPoint.h"

namespace FlowChart
{
	namespace Data
	{
		AnchorPoint::AnchorPoint()
		{
			OffsetX = 0.0f;
			OffsetY = 0.5f;
			setPlacement(Center);
			setPosition(winrt::Windows::Foundation::Point());
		}

		AnchorPoint::AnchorPoint(float offsetX, float offsetY, winrt::Windows::Foundation::Point parentPosition, float parentWidth, float parentHeight, LinkAnchorPlacement placement)
		{
			OffsetX = offsetX;
			OffsetY = offsetY;
			setPlacement(placement);
			setPosition(winrt::Windows::Foundation::Point(parentPosition.X + parentWidth * OffsetX, parentPosition.Y + parentHeight * OffsetY));
		}

		AnchorPoint::AnchorPoint(AnchorPoint* temp)
		{
			OffsetX = temp->OffsetX;
			OffsetY = temp->OffsetY;
			setPlacement(temp->privatePlacement);
			setPosition(temp->getPosition());
		}

		const winrt::Windows::Foundation::Point AnchorPoint::getPosition() const
		{
			return privatePosition;
		}

		void AnchorPoint::setPosition(const winrt::Windows::Foundation::Point &value)
		{
			privatePosition = value;
		}

		const FlowChart::Data::LinkAnchorPlacement AnchorPoint::getPlacement() const
		{
			return privatePlacement;
		}

		void AnchorPoint::setPlacement(const LinkAnchorPlacement &value)
		{
			privatePlacement = value;
		}

		void AnchorPoint::RefreshPosition(winrt::Windows::Foundation::Point parentPosition, float parentWidth, float parentHeight)
		{
			setPosition(winrt::Windows::Foundation::Point(parentPosition.X + parentWidth * OffsetX, parentPosition.Y + parentHeight * OffsetY));
		}

		winrt::hstring AnchorPoint::ToString()
		{
			return winrt::to_hstring(std::to_string(getPosition().X) + " " + std::to_string(getPosition().Y) + std::to_string(getPlacement()));
		}
	}
}

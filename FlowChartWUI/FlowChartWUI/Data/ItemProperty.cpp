#include "pch.h"
#include "ItemProperty.h"

namespace FlowChart
{
	namespace Data
	{

		const winrt::hstring &ItemProperty::getName() const
		{
			return privateName;
		}

		void ItemProperty::setName(const winrt::hstring &value)
		{
			privateName = value;
		}

		const winrt::hstring &ItemProperty::getTitle() const
		{
			return privateTitle;
		}

		void ItemProperty::setTitle(const winrt::hstring &value)
		{
			privateTitle = value;
		}

		const winrt::hstring &ItemProperty::getValue() const
		{
			return privateValue;
		}

		void ItemProperty::setValue(const winrt::hstring &value)
		{
			privateValue = value;
		}

		const FlowChart::Data::PropertyType &ItemProperty::getPropertyType() const
		{
			return privatePropertyType;
		}

		void ItemProperty::setPropertyType(const FlowChart::Data::PropertyType &value)
		{
			privatePropertyType = value;
		}

		const FlowChart::Data::PropertyVisibility &ItemProperty::getPropertyVisibility() const
		{
			return privatePropertyVisibility;
		}

		void ItemProperty::setPropertyVisibility(const FlowChart::Data::PropertyVisibility &value)
		{
			privatePropertyVisibility = value;
		}

		const std::vector<winrt::hstring> &ItemProperty::getEnumerations() const
		{
			return privateEnumerations;
		}

		void ItemProperty::setEnumerations(const std::vector<winrt::hstring> &value)
		{
			privateEnumerations = value;
		}

		ItemProperty::ItemProperty()
		{
			setName(L"");
			setTitle(L"");
			setValue(L"");
			setPropertyType(PropertyType::Void);
			setPropertyVisibility(Public);
			setEnumerations(std::vector<winrt::hstring>());
		}

		ItemProperty::ItemProperty(const winrt::hstring &name, const winrt::hstring &title, const winrt::hstring &val, FlowChart::Data::PropertyType propertyType, FlowChart::Data::PropertyVisibility propertyVisibility, std::vector<winrt::hstring> &enumerations)
		{
			setName(name);
			setTitle(title);
			setValue(val);
			setPropertyType(propertyType);
			setPropertyVisibility(propertyVisibility);
			setEnumerations(enumerations);
		}
	}
}

#pragma once

#include "PropertyType.h"
#include "PropertyVisibility.h"
#include <string>
#include <vector>

namespace FlowChart
{
	namespace Data
	{
		class ItemProperty
		{
			private:
				winrt::hstring privateName;
			public:
				const winrt::hstring &getName() const;
				void setName(const winrt::hstring &value);

			private:
				winrt::hstring privateTitle;
			public:
				const winrt::hstring &getTitle() const;
				void setTitle(const winrt::hstring &value);

			private:
				winrt::hstring privateValue;
			public:
				const winrt::hstring &getValue() const;
				void setValue(const winrt::hstring &value);

			private:
				FlowChart::Data::PropertyType privatePropertyType;
			public:
				const FlowChart::Data::PropertyType &getPropertyType() const;
				void setPropertyType(const FlowChart::Data::PropertyType &value);

			private:
				FlowChart::Data::PropertyVisibility privatePropertyVisibility;
			public:
				const FlowChart::Data::PropertyVisibility &getPropertyVisibility() const;
				void setPropertyVisibility(const FlowChart::Data::PropertyVisibility &value);

			private:
				std::vector<winrt::hstring> privateEnumerations;
			public:
				const std::vector<winrt::hstring> &getEnumerations() const;
				void setEnumerations(const std::vector<winrt::hstring> &value);

			ItemProperty();

			ItemProperty(const winrt::hstring &name, const winrt::hstring &title, const winrt::hstring &val, FlowChart::Data::PropertyType propertyType, FlowChart::Data::PropertyVisibility propertyVisibility, std::vector<winrt::hstring> &enumerations);
		};
	}
}

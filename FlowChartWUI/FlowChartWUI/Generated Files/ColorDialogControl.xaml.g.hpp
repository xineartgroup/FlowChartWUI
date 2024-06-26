﻿//------------------------------------------------------------------------------
//     This code was generated by a tool.
//
//     Changes to this file may cause incorrect behavior and will be lost if
//     the code is regenerated.
//------------------------------------------------------------------------------
#include "pch.h"
#include "ColorDialogControl.xaml.h"

#pragma warning(push)
#pragma warning(disable: 4100) // unreferenced formal parameter

namespace winrt::FlowChartWUI::implementation
{
    using Application = ::winrt::Microsoft::UI::Xaml::Application;
    using ComponentResourceLocation = ::winrt::Microsoft::UI::Xaml::Controls::Primitives::ComponentResourceLocation;
    using DataTemplate = ::winrt::Microsoft::UI::Xaml::DataTemplate;
    using DependencyObject = ::winrt::Microsoft::UI::Xaml::DependencyObject;
    using DependencyProperty = ::winrt::Microsoft::UI::Xaml::DependencyProperty;
    using IComponentConnector = ::winrt::Microsoft::UI::Xaml::Markup::IComponentConnector;
    using Uri = ::winrt::Windows::Foundation::Uri;
    using XamlBindingHelper = ::winrt::Microsoft::UI::Xaml::Markup::XamlBindingHelper;

    template <typename D, typename ... I>
    void ColorDialogControlT<D, I...>::InitializeComponent()
    {
        if (!_contentLoaded)
        {
            _contentLoaded = true;
            ::winrt::Windows::Foundation::Uri resourceLocator{ L"ms-appx:///ColorDialogControl.xaml" };
            ::winrt::Microsoft::UI::Xaml::Application::LoadComponent(*this, resourceLocator, ComponentResourceLocation::Application);
        }
    }

    template <typename D, typename ... I>
    void ColorDialogControlT<D, I...>::Connect(int32_t connectionId, IInspectable const& target)
    {
        switch (connectionId)
        {
        case 2:
            {
                auto targetElement = target.as<::winrt::Microsoft::UI::Xaml::Controls::StackPanel>();
                this->pnlMain(targetElement);
            }
            break;
        }
        _contentLoaded = true;
    }

    template <typename D, typename ... I>
    void ColorDialogControlT<D, I...>::DisconnectUnloadedObject(int32_t)
    {
        throw ::winrt::hresult_invalid_argument { L"No unloadable objects to disconnect." };
    }

    template <typename D, typename ... I>
    void ColorDialogControlT<D, I...>::UnloadObject(DependencyObject const&)
    {
        throw ::winrt::hresult_invalid_argument { L"No unloadable objects." };
    }


    template <typename D, typename... I>
    IComponentConnector ColorDialogControlT<D, I...>::GetBindingConnector(int32_t, IInspectable const&)
    {
        return nullptr;
    }

    template struct ColorDialogControlT<struct ColorDialogControl>;
}


#pragma warning(pop)



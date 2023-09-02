// WARNING: Please don't edit this file. It was generated by C++/WinRT v2.0.220929.3

#pragma once
#ifndef WINRT_FlowChartWUI_2_H
#define WINRT_FlowChartWUI_2_H
#include "winrt/impl/Microsoft.UI.Composition.1.h"
#include "winrt/impl/Microsoft.UI.Xaml.1.h"
#include "winrt/impl/Microsoft.UI.Xaml.Controls.1.h"
#include "winrt/impl/Microsoft.UI.Xaml.Markup.1.h"
#include "winrt/impl/FlowChartWUI.1.h"
WINRT_EXPORT namespace winrt::FlowChartWUI
{
    struct __declspec(empty_bases) ColorDialogControl : winrt::FlowChartWUI::IColorDialogControl,
        impl::base<ColorDialogControl, winrt::Microsoft::UI::Xaml::Controls::UserControl, winrt::Microsoft::UI::Xaml::Controls::Control, winrt::Microsoft::UI::Xaml::FrameworkElement, winrt::Microsoft::UI::Xaml::UIElement, winrt::Microsoft::UI::Xaml::DependencyObject>,
        impl::require<ColorDialogControl, winrt::Microsoft::UI::Xaml::Controls::IUserControl, winrt::Microsoft::UI::Xaml::Controls::IControl, winrt::Microsoft::UI::Xaml::Controls::IControlProtected, winrt::Microsoft::UI::Xaml::Controls::IControlOverrides, winrt::Microsoft::UI::Xaml::IFrameworkElement, winrt::Microsoft::UI::Xaml::IFrameworkElementProtected, winrt::Microsoft::UI::Xaml::IFrameworkElementOverrides, winrt::Microsoft::UI::Xaml::IUIElement, winrt::Microsoft::UI::Xaml::IUIElementProtected, winrt::Microsoft::UI::Xaml::IUIElementOverrides, winrt::Microsoft::UI::Composition::IAnimationObject, winrt::Microsoft::UI::Composition::IVisualElement, winrt::Microsoft::UI::Composition::IVisualElement2, winrt::Microsoft::UI::Xaml::IDependencyObject>
    {
        ColorDialogControl(std::nullptr_t) noexcept {}
        ColorDialogControl(void* ptr, take_ownership_from_abi_t) noexcept : winrt::FlowChartWUI::IColorDialogControl(ptr, take_ownership_from_abi) {}
        ColorDialogControl();
    };
    struct __declspec(empty_bases) MainWindow : winrt::FlowChartWUI::IMainWindow,
        impl::base<MainWindow, winrt::Microsoft::UI::Xaml::Window>,
        impl::require<MainWindow, winrt::Microsoft::UI::Xaml::IWindow>
    {
        MainWindow(std::nullptr_t) noexcept {}
        MainWindow(void* ptr, take_ownership_from_abi_t) noexcept : winrt::FlowChartWUI::IMainWindow(ptr, take_ownership_from_abi) {}
        MainWindow();
    };
    struct __declspec(empty_bases) XamlMetaDataProvider : winrt::Microsoft::UI::Xaml::Markup::IXamlMetadataProvider
    {
        XamlMetaDataProvider(std::nullptr_t) noexcept {}
        XamlMetaDataProvider(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Microsoft::UI::Xaml::Markup::IXamlMetadataProvider(ptr, take_ownership_from_abi) {}
        XamlMetaDataProvider();
    };
}
#endif

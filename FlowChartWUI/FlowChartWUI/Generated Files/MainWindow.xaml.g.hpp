﻿//------------------------------------------------------------------------------
//     This code was generated by a tool.
//
//     Changes to this file may cause incorrect behavior and will be lost if
//     the code is regenerated.
//------------------------------------------------------------------------------
#include "pch.h"
#include "MainWindow.xaml.h"

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
    void MainWindowT<D, I...>::InitializeComponent()
    {
        if (!_contentLoaded)
        {
            _contentLoaded = true;
            ::winrt::Windows::Foundation::Uri resourceLocator{ L"ms-appx:///MainWindow.xaml" };
            ::winrt::Microsoft::UI::Xaml::Application::LoadComponent(*this, resourceLocator, ComponentResourceLocation::Application);
        }
    }

    template <typename D, typename ... I>
    void MainWindowT<D, I...>::Connect(int32_t connectionId, IInspectable const& target)
    {
        switch (connectionId)
        {
        case 2:
            {
                auto targetElement = target.as<::winrt::Microsoft::UI::Xaml::Controls::StackPanel>();
                this->pnlTopBar(targetElement);
            }
            break;
        case 3:
            {
                auto targetElement = target.as<::winrt::Microsoft::UI::Xaml::Controls::TabView>();
                this->tabDiagram(targetElement);
            }
            break;
        case 4:
            {
                auto targetElement = target.as<::winrt::Microsoft::UI::Xaml::Controls::TextBlock>();
                this->lblMousePosition(targetElement);
            }
            break;
        case 5:
            {
                auto targetElement = target.as<::winrt::Microsoft::UI::Xaml::Controls::StackPanel>();
                this->pnlProperty(targetElement);
            }
            break;
        case 6:
            {
                auto targetElement = target.as<::winrt::Microsoft::UI::Xaml::Controls::StackPanel>();
                this->pnlClassProperty(targetElement);
            }
            break;
        case 7:
            {
                auto targetElement = target.as<::winrt::Microsoft::UI::Xaml::Controls::StackPanel>();
                this->pnlLinkProperty(targetElement);
            }
            break;
        case 8:
            {
                auto targetElement = target.as<::winrt::Microsoft::UI::Xaml::Controls::TextBox>();
                this->txtLinkPropertySize(targetElement);
                auto weakThis = ::winrt::make_weak<class_type>(*this);
                targetElement.TextChanged([weakThis](::winrt::Windows::Foundation::IInspectable const& p0, ::winrt::Microsoft::UI::Xaml::Controls::TextChangedEventArgs const& p1){
                    if (auto t = weakThis.get())
                    {
                        ::winrt::get_self<D>(t)->txtLinkPropertySize_TextChanged(p0, p1);
                    }
                });
            }
            break;
        case 9:
            {
                auto targetElement = target.as<::winrt::Microsoft::UI::Xaml::Controls::ComboBox>();
                this->cboLinkPropertyStroke(targetElement);
                auto weakThis = ::winrt::make_weak<class_type>(*this);
                targetElement.SelectionChanged([weakThis](::winrt::Windows::Foundation::IInspectable const& p0, ::winrt::Microsoft::UI::Xaml::Controls::SelectionChangedEventArgs const& p1){
                    if (auto t = weakThis.get())
                    {
                        ::winrt::get_self<D>(t)->cboLinkPropertyStroke_SelectionChanged(p0, p1);
                    }
                });
            }
            break;
        case 10:
            {
                auto targetElement = target.as<::winrt::Microsoft::UI::Xaml::Controls::Button>();
                this->btnDeleteClassProperty(targetElement);
                auto weakThis = ::winrt::make_weak<class_type>(*this);
                targetElement.Click([weakThis](::winrt::Windows::Foundation::IInspectable const& p0, ::winrt::Microsoft::UI::Xaml::RoutedEventArgs const& p1){
                    if (auto t = weakThis.get())
                    {
                        ::winrt::get_self<D>(t)->btnDeleteClassProperty_Click(p0, p1);
                    }
                });
            }
            break;
        case 11:
            {
                auto targetElement = target.as<::winrt::Microsoft::UI::Xaml::Controls::TextBox>();
                this->txtClassPropertyName(targetElement);
                auto weakThis = ::winrt::make_weak<class_type>(*this);
                targetElement.TextChanged([weakThis](::winrt::Windows::Foundation::IInspectable const& p0, ::winrt::Microsoft::UI::Xaml::Controls::TextChangedEventArgs const& p1){
                    if (auto t = weakThis.get())
                    {
                        ::winrt::get_self<D>(t)->txtClassPropertyName_TextChanged(p0, p1);
                    }
                });
            }
            break;
        case 12:
            {
                auto targetElement = target.as<::winrt::Microsoft::UI::Xaml::Controls::ComboBox>();
                this->cboClassPropertyType(targetElement);
                auto weakThis = ::winrt::make_weak<class_type>(*this);
                targetElement.SelectionChanged([weakThis](::winrt::Windows::Foundation::IInspectable const& p0, ::winrt::Microsoft::UI::Xaml::Controls::SelectionChangedEventArgs const& p1){
                    if (auto t = weakThis.get())
                    {
                        ::winrt::get_self<D>(t)->cboClassPropertyType_SelectionChanged(p0, p1);
                    }
                });
            }
            break;
        case 13:
            {
                auto targetElement = target.as<::winrt::Microsoft::UI::Xaml::Controls::ComboBox>();
                this->cboClassPropertyVisibility(targetElement);
                auto weakThis = ::winrt::make_weak<class_type>(*this);
                targetElement.SelectionChanged([weakThis](::winrt::Windows::Foundation::IInspectable const& p0, ::winrt::Microsoft::UI::Xaml::Controls::SelectionChangedEventArgs const& p1){
                    if (auto t = weakThis.get())
                    {
                        ::winrt::get_self<D>(t)->cboClassPropertyVisibility_SelectionChanged(p0, p1);
                    }
                });
            }
            break;
        case 14:
            {
                auto targetElement = target.as<::winrt::Microsoft::UI::Xaml::Controls::StackPanel>();
                this->pnlSide3(targetElement);
            }
            break;
        case 15:
            {
                auto targetElement = target.as<::winrt::Microsoft::UI::Xaml::Controls::StackPanel>();
                this->pnlSide2(targetElement);
            }
            break;
        case 16:
            {
                auto targetElement = target.as<::winrt::Microsoft::UI::Xaml::Controls::StackPanel>();
                this->pnlSide1(targetElement);
            }
            break;
        case 17:
            {
                auto targetElement = target.as<::winrt::Microsoft::UI::Xaml::Controls::Grid>();
                this->ShellTitlebarInset(targetElement);
            }
            break;
        case 18:
            {
                auto targetElement = target.as<::winrt::Microsoft::UI::Xaml::Controls::Grid>();
                this->CustomDragRegion(targetElement);
            }
            break;
        case 19:
            {
                auto targetElement = target.as<::winrt::Microsoft::UI::Xaml::Controls::Canvas>();
                this->canvas(targetElement);
                auto weakThis = ::winrt::make_weak<class_type>(*this);
                targetElement.PointerPressed([weakThis](::winrt::Windows::Foundation::IInspectable const& p0, ::winrt::Microsoft::UI::Xaml::Input::PointerRoutedEventArgs const& p1){
                    if (auto t = weakThis.get())
                    {
                        ::winrt::get_self<D>(t)->pictureBox1_MouseDown(p0, p1);
                    }
                });
                targetElement.PointerMoved([weakThis](::winrt::Windows::Foundation::IInspectable const& p0, ::winrt::Microsoft::UI::Xaml::Input::PointerRoutedEventArgs const& p1){
                    if (auto t = weakThis.get())
                    {
                        ::winrt::get_self<D>(t)->pictureBox1_MouseMove(p0, p1);
                    }
                });
                targetElement.PointerReleased([weakThis](::winrt::Windows::Foundation::IInspectable const& p0, ::winrt::Microsoft::UI::Xaml::Input::PointerRoutedEventArgs const& p1){
                    if (auto t = weakThis.get())
                    {
                        ::winrt::get_self<D>(t)->pictureBox1_MouseUp(p0, p1);
                    }
                });
                targetElement.DoubleTapped([weakThis](::winrt::Windows::Foundation::IInspectable const& p0, ::winrt::Microsoft::UI::Xaml::Input::DoubleTappedRoutedEventArgs const& p1){
                    if (auto t = weakThis.get())
                    {
                        ::winrt::get_self<D>(t)->pictureBox1_DoubleTapped(p0, p1);
                    }
                });
            }
            break;
        case 20:
            {
                auto targetElement = target.as<::winrt::Microsoft::UI::Xaml::Controls::MenuFlyout>();
                this->contextMenu1(targetElement);
            }
            break;
        case 21:
            {
                auto targetElement = target.as<::winrt::Microsoft::UI::Xaml::Controls::MenuFlyoutItem>();
                auto weakThis = ::winrt::make_weak<class_type>(*this);
                targetElement.Click([weakThis](::winrt::Windows::Foundation::IInspectable const& p0, ::winrt::Microsoft::UI::Xaml::RoutedEventArgs const& p1){
                    if (auto t = weakThis.get())
                    {
                        ::winrt::get_self<D>(t)->ClearScreen_Click(p0, p1);
                    }
                });
            }
            break;
        case 22:
            {
                auto targetElement = target.as<::winrt::Microsoft::UI::Xaml::Controls::MenuFlyoutItem>();
                auto weakThis = ::winrt::make_weak<class_type>(*this);
                targetElement.Click([weakThis](::winrt::Windows::Foundation::IInspectable const& p0, ::winrt::Microsoft::UI::Xaml::RoutedEventArgs const& p1){
                    if (auto t = weakThis.get())
                    {
                        ::winrt::get_self<D>(t)->ToggleLinkSmoothing_Click(p0, p1);
                    }
                });
            }
            break;
        case 23:
            {
                auto targetElement = target.as<::winrt::Microsoft::UI::Xaml::Controls::MenuFlyoutItem>();
                auto weakThis = ::winrt::make_weak<class_type>(*this);
                targetElement.Click([weakThis](::winrt::Windows::Foundation::IInspectable const& p0, ::winrt::Microsoft::UI::Xaml::RoutedEventArgs const& p1){
                    if (auto t = weakThis.get())
                    {
                        ::winrt::get_self<D>(t)->RotateAllAnchorPoints_Click(p0, p1);
                    }
                });
            }
            break;
        case 24:
            {
                auto targetElement = target.as<::winrt::Microsoft::UI::Xaml::Controls::ComboBox>();
                this->cboFontName(targetElement);
                auto weakThis = ::winrt::make_weak<class_type>(*this);
                targetElement.SelectionChanged([weakThis](::winrt::Windows::Foundation::IInspectable const& p0, ::winrt::Microsoft::UI::Xaml::Controls::SelectionChangedEventArgs const& p1){
                    if (auto t = weakThis.get())
                    {
                        ::winrt::get_self<D>(t)->cboFontName_SelectionChanged(p0, p1);
                    }
                });
            }
            break;
        case 25:
            {
                auto targetElement = target.as<::winrt::Microsoft::UI::Xaml::Controls::ComboBox>();
                this->cboFontSize(targetElement);
                auto weakThis = ::winrt::make_weak<class_type>(*this);
                targetElement.SelectionChanged([weakThis](::winrt::Windows::Foundation::IInspectable const& p0, ::winrt::Microsoft::UI::Xaml::Controls::SelectionChangedEventArgs const& p1){
                    if (auto t = weakThis.get())
                    {
                        ::winrt::get_self<D>(t)->cboFontSize_SelectionChanged(p0, p1);
                    }
                });
            }
            break;
        case 26:
            {
                auto targetElement = target.as<::winrt::Microsoft::UI::Xaml::Controls::Button>();
                this->btnFontBold(targetElement);
                auto weakThis = ::winrt::make_weak<class_type>(*this);
                targetElement.Click([weakThis](::winrt::Windows::Foundation::IInspectable const& p0, ::winrt::Microsoft::UI::Xaml::RoutedEventArgs const& p1){
                    if (auto t = weakThis.get())
                    {
                        ::winrt::get_self<D>(t)->btnFontBold_Click(p0, p1);
                    }
                });
            }
            break;
        case 27:
            {
                auto targetElement = target.as<::winrt::Microsoft::UI::Xaml::Controls::Button>();
                this->btnFontItalic(targetElement);
                auto weakThis = ::winrt::make_weak<class_type>(*this);
                targetElement.Click([weakThis](::winrt::Windows::Foundation::IInspectable const& p0, ::winrt::Microsoft::UI::Xaml::RoutedEventArgs const& p1){
                    if (auto t = weakThis.get())
                    {
                        ::winrt::get_self<D>(t)->btnFontItalic_Click(p0, p1);
                    }
                });
            }
            break;
        case 28:
            {
                auto targetElement = target.as<::winrt::Microsoft::UI::Xaml::Controls::Button>();
                this->btnFontUnderline(targetElement);
                auto weakThis = ::winrt::make_weak<class_type>(*this);
                targetElement.Click([weakThis](::winrt::Windows::Foundation::IInspectable const& p0, ::winrt::Microsoft::UI::Xaml::RoutedEventArgs const& p1){
                    if (auto t = weakThis.get())
                    {
                        ::winrt::get_self<D>(t)->btnFontUnderline_Click(p0, p1);
                    }
                });
            }
            break;
        case 29:
            {
                auto targetElement = target.as<::winrt::Microsoft::UI::Xaml::Controls::Button>();
                this->btnFontStrikethrough(targetElement);
                auto weakThis = ::winrt::make_weak<class_type>(*this);
                targetElement.Click([weakThis](::winrt::Windows::Foundation::IInspectable const& p0, ::winrt::Microsoft::UI::Xaml::RoutedEventArgs const& p1){
                    if (auto t = weakThis.get())
                    {
                        ::winrt::get_self<D>(t)->btnFontStrikethrough_Click(p0, p1);
                    }
                });
            }
            break;
        case 30:
            {
                auto targetElement = target.as<::winrt::Microsoft::UI::Xaml::Controls::DropDownButton>();
                this->btnFontColor(targetElement);
            }
            break;
        case 31:
            {
                auto targetElement = target.as<::winrt::Microsoft::UI::Xaml::Controls::DropDownButton>();
                this->btnLineColor(targetElement);
                auto weakThis = ::winrt::make_weak<class_type>(*this);
                targetElement.Click([weakThis](::winrt::Windows::Foundation::IInspectable const& p0, ::winrt::Microsoft::UI::Xaml::RoutedEventArgs const& p1){
                    if (auto t = weakThis.get())
                    {
                        ::winrt::get_self<D>(t)->btnLineColor_Click(p0, p1);
                    }
                });
            }
            break;
        case 32:
            {
                auto targetElement = target.as<::winrt::Microsoft::UI::Xaml::Controls::DropDownButton>();
                this->btnFillColor(targetElement);
                auto weakThis = ::winrt::make_weak<class_type>(*this);
                targetElement.Click([weakThis](::winrt::Windows::Foundation::IInspectable const& p0, ::winrt::Microsoft::UI::Xaml::RoutedEventArgs const& p1){
                    if (auto t = weakThis.get())
                    {
                        ::winrt::get_self<D>(t)->btnFillColor_Click(p0, p1);
                    }
                });
            }
            break;
        case 33:
            {
                auto targetElement = target.as<::winrt::Microsoft::UI::Xaml::Controls::MenuFlyoutItem>();
                auto weakThis = ::winrt::make_weak<class_type>(*this);
                targetElement.Click([weakThis](::winrt::Windows::Foundation::IInspectable const& p0, ::winrt::Microsoft::UI::Xaml::RoutedEventArgs const& p1){
                    if (auto t = weakThis.get())
                    {
                        ::winrt::get_self<D>(t)->Settings_Click(p0, p1);
                    }
                });
            }
            break;
        case 34:
            {
                auto targetElement = target.as<::winrt::Microsoft::UI::Xaml::Controls::MenuFlyoutItem>();
                auto weakThis = ::winrt::make_weak<class_type>(*this);
                targetElement.Click([weakThis](::winrt::Windows::Foundation::IInspectable const& p0, ::winrt::Microsoft::UI::Xaml::RoutedEventArgs const& p1){
                    if (auto t = weakThis.get())
                    {
                        ::winrt::get_self<D>(t)->OpenFile_Click(p0, p1);
                    }
                });
            }
            break;
        case 35:
            {
                auto targetElement = target.as<::winrt::Microsoft::UI::Xaml::Controls::MenuFlyoutItem>();
                auto weakThis = ::winrt::make_weak<class_type>(*this);
                targetElement.Click([weakThis](::winrt::Windows::Foundation::IInspectable const& p0, ::winrt::Microsoft::UI::Xaml::RoutedEventArgs const& p1){
                    if (auto t = weakThis.get())
                    {
                        ::winrt::get_self<D>(t)->SaveFile_Click(p0, p1);
                    }
                });
            }
            break;
        case 36:
            {
                auto targetElement = target.as<::winrt::Microsoft::UI::Xaml::Controls::MenuFlyoutItem>();
                auto weakThis = ::winrt::make_weak<class_type>(*this);
                targetElement.Click([weakThis](::winrt::Windows::Foundation::IInspectable const& p0, ::winrt::Microsoft::UI::Xaml::RoutedEventArgs const& p1){
                    if (auto t = weakThis.get())
                    {
                        ::winrt::get_self<D>(t)->CloseFile_Click(p0, p1);
                    }
                });
            }
            break;
        }
        _contentLoaded = true;
    }

    template <typename D, typename ... I>
    void MainWindowT<D, I...>::DisconnectUnloadedObject(int32_t)
    {
        throw ::winrt::hresult_invalid_argument { L"No unloadable objects to disconnect." };
    }

    template <typename D, typename ... I>
    void MainWindowT<D, I...>::UnloadObject(DependencyObject const&)
    {
        throw ::winrt::hresult_invalid_argument { L"No unloadable objects." };
    }


    template <typename D, typename... I>
    IComponentConnector MainWindowT<D, I...>::GetBindingConnector(int32_t, IInspectable const&)
    {
        return nullptr;
    }

    template struct MainWindowT<struct MainWindow>;
}


#pragma warning(pop)



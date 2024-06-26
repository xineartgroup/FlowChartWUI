﻿//------------------------------------------------------------------------------
//     This code was generated by a tool.
//
//     Changes to this file may cause incorrect behavior and will be lost if
//     the code is regenerated.
//------------------------------------------------------------------------------
#pragma once


namespace winrt::FlowChartWUI::implementation
{
    using IInspectable = ::winrt::Windows::Foundation::IInspectable;

    template <typename D, typename ... I>
    struct MainWindowT : public ::winrt::FlowChartWUI::implementation::MainWindow_base<D,
        ::winrt::Microsoft::UI::Xaml::Markup::IComponentConnector,
        I...>
    {
        using base_type = typename MainWindowT::base_type;
        using base_type::base_type;
        using class_type = typename MainWindowT::class_type;

        void InitializeComponent();
        virtual void Connect(int32_t connectionId, IInspectable const& target);
        virtual ::winrt::Microsoft::UI::Xaml::Markup::IComponentConnector GetBindingConnector(int32_t connectionId, IInspectable const& target);
        void UnloadObject(::winrt::Microsoft::UI::Xaml::DependencyObject const& dependencyObject);
        void DisconnectUnloadedObject(int32_t connectionId);

        ::winrt::Microsoft::UI::Xaml::Controls::StackPanel pnlTopBar()
        {
            return _pnlTopBar;
        }
        void pnlTopBar(::winrt::Microsoft::UI::Xaml::Controls::StackPanel value)
        {
            _pnlTopBar = value;
        }

        ::winrt::Microsoft::UI::Xaml::Controls::TabView tabDiagram()
        {
            return _tabDiagram;
        }
        void tabDiagram(::winrt::Microsoft::UI::Xaml::Controls::TabView value)
        {
            _tabDiagram = value;
        }

        ::winrt::Microsoft::UI::Xaml::Controls::TextBlock lblMousePosition()
        {
            return _lblMousePosition;
        }
        void lblMousePosition(::winrt::Microsoft::UI::Xaml::Controls::TextBlock value)
        {
            _lblMousePosition = value;
        }

        ::winrt::Microsoft::UI::Xaml::Controls::StackPanel pnlProperty()
        {
            return _pnlProperty;
        }
        void pnlProperty(::winrt::Microsoft::UI::Xaml::Controls::StackPanel value)
        {
            _pnlProperty = value;
        }

        ::winrt::Microsoft::UI::Xaml::Controls::StackPanel pnlClassProperty()
        {
            return _pnlClassProperty;
        }
        void pnlClassProperty(::winrt::Microsoft::UI::Xaml::Controls::StackPanel value)
        {
            _pnlClassProperty = value;
        }

        ::winrt::Microsoft::UI::Xaml::Controls::StackPanel pnlLinkProperty()
        {
            return _pnlLinkProperty;
        }
        void pnlLinkProperty(::winrt::Microsoft::UI::Xaml::Controls::StackPanel value)
        {
            _pnlLinkProperty = value;
        }

        ::winrt::Microsoft::UI::Xaml::Controls::TextBox txtLinkPropertySize()
        {
            return _txtLinkPropertySize;
        }
        void txtLinkPropertySize(::winrt::Microsoft::UI::Xaml::Controls::TextBox value)
        {
            _txtLinkPropertySize = value;
        }

        ::winrt::Microsoft::UI::Xaml::Controls::ComboBox cboLinkPropertyStroke()
        {
            return _cboLinkPropertyStroke;
        }
        void cboLinkPropertyStroke(::winrt::Microsoft::UI::Xaml::Controls::ComboBox value)
        {
            _cboLinkPropertyStroke = value;
        }

        ::winrt::Microsoft::UI::Xaml::Controls::Button btnDeleteClassProperty()
        {
            return _btnDeleteClassProperty;
        }
        void btnDeleteClassProperty(::winrt::Microsoft::UI::Xaml::Controls::Button value)
        {
            _btnDeleteClassProperty = value;
        }

        ::winrt::Microsoft::UI::Xaml::Controls::TextBox txtClassPropertyName()
        {
            return _txtClassPropertyName;
        }
        void txtClassPropertyName(::winrt::Microsoft::UI::Xaml::Controls::TextBox value)
        {
            _txtClassPropertyName = value;
        }

        ::winrt::Microsoft::UI::Xaml::Controls::ComboBox cboClassPropertyType()
        {
            return _cboClassPropertyType;
        }
        void cboClassPropertyType(::winrt::Microsoft::UI::Xaml::Controls::ComboBox value)
        {
            _cboClassPropertyType = value;
        }

        ::winrt::Microsoft::UI::Xaml::Controls::ComboBox cboClassPropertyVisibility()
        {
            return _cboClassPropertyVisibility;
        }
        void cboClassPropertyVisibility(::winrt::Microsoft::UI::Xaml::Controls::ComboBox value)
        {
            _cboClassPropertyVisibility = value;
        }

        ::winrt::Microsoft::UI::Xaml::Controls::StackPanel pnlSide3()
        {
            return _pnlSide3;
        }
        void pnlSide3(::winrt::Microsoft::UI::Xaml::Controls::StackPanel value)
        {
            _pnlSide3 = value;
        }

        ::winrt::Microsoft::UI::Xaml::Controls::StackPanel pnlSide2()
        {
            return _pnlSide2;
        }
        void pnlSide2(::winrt::Microsoft::UI::Xaml::Controls::StackPanel value)
        {
            _pnlSide2 = value;
        }

        ::winrt::Microsoft::UI::Xaml::Controls::StackPanel pnlSide1()
        {
            return _pnlSide1;
        }
        void pnlSide1(::winrt::Microsoft::UI::Xaml::Controls::StackPanel value)
        {
            _pnlSide1 = value;
        }

        ::winrt::Microsoft::UI::Xaml::Controls::Grid ShellTitlebarInset()
        {
            return _ShellTitlebarInset;
        }
        void ShellTitlebarInset(::winrt::Microsoft::UI::Xaml::Controls::Grid value)
        {
            _ShellTitlebarInset = value;
        }

        ::winrt::Microsoft::UI::Xaml::Controls::Grid CustomDragRegion()
        {
            return _CustomDragRegion;
        }
        void CustomDragRegion(::winrt::Microsoft::UI::Xaml::Controls::Grid value)
        {
            _CustomDragRegion = value;
        }

        ::winrt::Microsoft::UI::Xaml::Controls::Canvas canvas()
        {
            return _canvas;
        }
        void canvas(::winrt::Microsoft::UI::Xaml::Controls::Canvas value)
        {
            _canvas = value;
        }

        ::winrt::Microsoft::UI::Xaml::Controls::MenuFlyout contextMenu1()
        {
            return _contextMenu1;
        }
        void contextMenu1(::winrt::Microsoft::UI::Xaml::Controls::MenuFlyout value)
        {
            _contextMenu1 = value;
        }

        ::winrt::Microsoft::UI::Xaml::Controls::ComboBox cboFontName()
        {
            return _cboFontName;
        }
        void cboFontName(::winrt::Microsoft::UI::Xaml::Controls::ComboBox value)
        {
            _cboFontName = value;
        }

        ::winrt::Microsoft::UI::Xaml::Controls::ComboBox cboFontSize()
        {
            return _cboFontSize;
        }
        void cboFontSize(::winrt::Microsoft::UI::Xaml::Controls::ComboBox value)
        {
            _cboFontSize = value;
        }

        ::winrt::Microsoft::UI::Xaml::Controls::Button btnFontBold()
        {
            return _btnFontBold;
        }
        void btnFontBold(::winrt::Microsoft::UI::Xaml::Controls::Button value)
        {
            _btnFontBold = value;
        }

        ::winrt::Microsoft::UI::Xaml::Controls::Button btnFontItalic()
        {
            return _btnFontItalic;
        }
        void btnFontItalic(::winrt::Microsoft::UI::Xaml::Controls::Button value)
        {
            _btnFontItalic = value;
        }

        ::winrt::Microsoft::UI::Xaml::Controls::Button btnFontUnderline()
        {
            return _btnFontUnderline;
        }
        void btnFontUnderline(::winrt::Microsoft::UI::Xaml::Controls::Button value)
        {
            _btnFontUnderline = value;
        }

        ::winrt::Microsoft::UI::Xaml::Controls::Button btnFontStrikethrough()
        {
            return _btnFontStrikethrough;
        }
        void btnFontStrikethrough(::winrt::Microsoft::UI::Xaml::Controls::Button value)
        {
            _btnFontStrikethrough = value;
        }

        ::winrt::Microsoft::UI::Xaml::Controls::DropDownButton btnFontColor()
        {
            return _btnFontColor;
        }
        void btnFontColor(::winrt::Microsoft::UI::Xaml::Controls::DropDownButton value)
        {
            _btnFontColor = value;
        }

        ::winrt::Microsoft::UI::Xaml::Controls::DropDownButton btnLineColor()
        {
            return _btnLineColor;
        }
        void btnLineColor(::winrt::Microsoft::UI::Xaml::Controls::DropDownButton value)
        {
            _btnLineColor = value;
        }

        ::winrt::Microsoft::UI::Xaml::Controls::DropDownButton btnFillColor()
        {
            return _btnFillColor;
        }
        void btnFillColor(::winrt::Microsoft::UI::Xaml::Controls::DropDownButton value)
        {
            _btnFillColor = value;
        }
        
    protected:
        bool _contentLoaded{false};

    private:
        struct MainWindow_obj1_Bindings;

        ::winrt::Microsoft::UI::Xaml::Controls::StackPanel _pnlTopBar{nullptr};
        ::winrt::Microsoft::UI::Xaml::Controls::TabView _tabDiagram{nullptr};
        ::winrt::Microsoft::UI::Xaml::Controls::TextBlock _lblMousePosition{nullptr};
        ::winrt::Microsoft::UI::Xaml::Controls::StackPanel _pnlProperty{nullptr};
        ::winrt::Microsoft::UI::Xaml::Controls::StackPanel _pnlClassProperty{nullptr};
        ::winrt::Microsoft::UI::Xaml::Controls::StackPanel _pnlLinkProperty{nullptr};
        ::winrt::Microsoft::UI::Xaml::Controls::TextBox _txtLinkPropertySize{nullptr};
        ::winrt::Microsoft::UI::Xaml::Controls::ComboBox _cboLinkPropertyStroke{nullptr};
        ::winrt::Microsoft::UI::Xaml::Controls::Button _btnDeleteClassProperty{nullptr};
        ::winrt::Microsoft::UI::Xaml::Controls::TextBox _txtClassPropertyName{nullptr};
        ::winrt::Microsoft::UI::Xaml::Controls::ComboBox _cboClassPropertyType{nullptr};
        ::winrt::Microsoft::UI::Xaml::Controls::ComboBox _cboClassPropertyVisibility{nullptr};
        ::winrt::Microsoft::UI::Xaml::Controls::StackPanel _pnlSide3{nullptr};
        ::winrt::Microsoft::UI::Xaml::Controls::StackPanel _pnlSide2{nullptr};
        ::winrt::Microsoft::UI::Xaml::Controls::StackPanel _pnlSide1{nullptr};
        ::winrt::Microsoft::UI::Xaml::Controls::Grid _ShellTitlebarInset{nullptr};
        ::winrt::Microsoft::UI::Xaml::Controls::Grid _CustomDragRegion{nullptr};
        ::winrt::Microsoft::UI::Xaml::Controls::Canvas _canvas{nullptr};
        ::winrt::Microsoft::UI::Xaml::Controls::MenuFlyout _contextMenu1{nullptr};
        ::winrt::Microsoft::UI::Xaml::Controls::ComboBox _cboFontName{nullptr};
        ::winrt::Microsoft::UI::Xaml::Controls::ComboBox _cboFontSize{nullptr};
        ::winrt::Microsoft::UI::Xaml::Controls::Button _btnFontBold{nullptr};
        ::winrt::Microsoft::UI::Xaml::Controls::Button _btnFontItalic{nullptr};
        ::winrt::Microsoft::UI::Xaml::Controls::Button _btnFontUnderline{nullptr};
        ::winrt::Microsoft::UI::Xaml::Controls::Button _btnFontStrikethrough{nullptr};
        ::winrt::Microsoft::UI::Xaml::Controls::DropDownButton _btnFontColor{nullptr};
        ::winrt::Microsoft::UI::Xaml::Controls::DropDownButton _btnLineColor{nullptr};
        ::winrt::Microsoft::UI::Xaml::Controls::DropDownButton _btnFillColor{nullptr};
    };
}


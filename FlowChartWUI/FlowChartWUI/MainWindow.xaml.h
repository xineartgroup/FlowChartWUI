// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include "MainWindow.g.h"

#include <winrt/Windows.UI.Xaml.Controls.h>

#include "Data\Settings.h"
#include "Data\ItemType.h"
#include "Data\PointerHit.h"
#include "Data\DiagramChartSymbols.h"
#include "Data\DiagramClassSymbols.h"

using namespace winrt;
using namespace Microsoft::UI::Xaml;
using namespace Microsoft::UI::Xaml::Markup;
using namespace FlowChart::Data;

namespace winrt::FlowChartWUI::implementation
{
    struct MainWindow : MainWindowT<MainWindow>
    {
    private:
        const int _ROWS = 16;
        bool forceMouseCapture;
        bool Dragging;
        int pageIndex;
        hstring fileName;
        hstring basePath;
        MenuFlyout contextMenu2;
        MenuFlyout contextMenu3;
        MenuFlyout contextMenu4;
        std::vector<DiagramChartSymbols*> DiagramChartsymbols = std::vector<DiagramChartSymbols*>();
        std::vector<DiagramClassSymbols*> DiagramClasssymbols = std::vector<DiagramClassSymbols*>();

    public:
        MainWindow();
        void InitializeComponent2();
        void Form1_Load();
        void RedrawImage();
        ControlTemplate GetColorPaletteTemplate();
        int LoadProperties(ISymbol* symbol);
        int LoadClassProperties(ISymbol* symbol);
        int LoadLinkProperties(Link* link);
        void TextChangeEvent(Windows::Foundation::IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& args);
        void OpenFile_Click(Windows::Foundation::IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& args);
        void SaveFile_Click(Windows::Foundation::IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& args);
        void CloseFile_Click(Windows::Foundation::IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& args);
        void Settings_Click(Windows::Foundation::IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& args);
        void pictureBox1_DoubleTapped(Windows::Foundation::IInspectable const& sender, Microsoft::UI::Xaml::Input::DoubleTappedRoutedEventArgs const& e);
        void pictureBox1_MouseDown(Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Input::PointerRoutedEventArgs const& args);
        void pictureBox1_MouseMove(Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Input::PointerRoutedEventArgs const& args);
        void pictureBox1_MouseUp(Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Input::PointerRoutedEventArgs const& args);
        void deleteLinkToolStripMenuItem_Click(IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& args);
        void deleteToolStripMenuItem_Click(IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& args);
        void addAttributeToolStripMenuItem_Click(IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& args);
        void addOperationToolStripMenuItem_Click(IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& args);
        void duplicateClassToolStripMenuItem_Click(IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& args);
        void duplicateChartToolStripMenuItem_Click(IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& args);
        void ComboBox1_SelectionChanged(Windows::Foundation::IInspectable const&, Microsoft::UI::Xaml::RoutedEventArgs const&);
        void cboClassPropertyType_SelectionChanged(Windows::Foundation::IInspectable const&, Microsoft::UI::Xaml::RoutedEventArgs const&);
        void cboClassPropertyVisibility_SelectionChanged(Windows::Foundation::IInspectable const&, Microsoft::UI::Xaml::RoutedEventArgs const&);
        void txtClassPropertyName_TextChanged(Windows::Foundation::IInspectable const&, Microsoft::UI::Xaml::RoutedEventArgs const&);
        void btnDeleteClassProperty_Click(Windows::Foundation::IInspectable const&, Microsoft::UI::Xaml::RoutedEventArgs const&);
        void btnLineColor_Click(Windows::Foundation::IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& args);
        void btnFillColor_Click(Windows::Foundation::IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& args);
        void btnFontColor_Click(Windows::Foundation::IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& args);
        void btnFont_Click(Windows::Foundation::IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& args);
        void btnFontBold_Click(Windows::Foundation::IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& args);
        void btnFontItalic_Click(Windows::Foundation::IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& args);
        void btnFontUnderline_Click(Windows::Foundation::IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& args);
        void btnFontStrikethrough_Click(Windows::Foundation::IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& args);
        void cboFontName_SelectionChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Controls::SelectionChangedEventArgs const& args);
        void cboFontSize_SelectionChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Controls::SelectionChangedEventArgs const& args);
        void Button1_Click(Windows::Foundation::IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& args);
        void Button2_Click(Windows::Foundation::IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& args);
        void TextBox1_TextChanged(Windows::Foundation::IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& args);
        void CheckBox1_Checked(Windows::Foundation::IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& args);
        void ClearScreen_Click(Windows::Foundation::IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& args);
        void ToggleLinkSmoothing_Click(Windows::Foundation::IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& args);
        void RotateAnchorPoints_Click(Windows::Foundation::IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& args);
        void RotateAllAnchorPoints_Click(Windows::Foundation::IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& args);
        void cboLinkPropertyStroke_SelectionChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Controls::SelectionChangedEventArgs const& args);
        void txtLinkPropertySize_TextChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Controls::TextChangedEventArgs const& args);
    };
}

namespace winrt::FlowChartWUI::factory_implementation
{
    struct MainWindow : MainWindowT<MainWindow, implementation::MainWindow>
    {
    };
}

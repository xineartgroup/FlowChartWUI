// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include "ColorDialogControl.xaml.h"
#if __has_include("ColorDialogControl.g.cpp")
#include "ColorDialogControl.g.cpp"
#endif

using namespace winrt;
using namespace Microsoft::UI::Xaml;
using namespace winrt::Microsoft::UI::Xaml::Controls;
using namespace winrt::Microsoft::UI::Xaml::Media;
using namespace winrt::Windows::UI;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::FlowChartWUI::implementation
{
    ColorDialogControl::ColorDialogControl()
    {
        InitializeComponent();
        InitializeComponent2();
    }

    void ColorDialogControl::InitializeComponent2()
    {
        Thickness thickness;
        thickness.Bottom = 5.0;
        thickness.Left = 5.0;
        thickness.Right = 5.0;
        thickness.Top = 5.0;

        Grid grid;
        grid.Margin(thickness);
        grid.HorizontalAlignment(HorizontalAlignment::Center);

        const uint8_t _ROWS = 8;

        for (uint8_t i = 0; i < _ROWS; i++)
        {
            grid.ColumnDefinitions().Append(ColumnDefinition());
        }

        for (uint8_t i = 0; i < _ROWS; i++)
        {
            grid.RowDefinitions().Append(RowDefinition());
        }

        for (uint8_t i = 1; i < _ROWS; i++)
        {
            for (uint8_t j = 1; j < _ROWS; j++)
            {
                uint8_t r = (i == 1 || i == 2 || i == 7 || i == 8 || i == 9 || i == 10 || i == 15 || i == 16) ? j : 1;
                uint8_t g = (i == 3 || i == 4 || i == 9 || i == 10 || i == 11 || i == 12 || i == 15 || i == 16) ? j : 1;
                uint8_t b = (i == 5 || i == 6 || i == 11 || i == 12 || i == 13 || i == 14 || i == 15 || i == 16) ? j : 1;

                Color color;
                color.A = 255;
                color.R = (i % 2 == 0 ? r * _ROWS : r * _ROWS / 2) - 1;
                color.G = (i % 2 == 0 ? g * _ROWS : g * _ROWS / 2) - 1;
                color.B = (i % 2 == 0 ? b * _ROWS : b * _ROWS / 2) - 1;

                Button button;
                button.Width(10.0);
                button.Height(10.0);
                button.Background(SolidColorBrush(color));
                Grid::SetColumn(button, i);
                Grid::SetRow(button, j);

                grid.Children().Append(button);
            }
        }

        pnlMain().Children().Append(grid);
    }

    void ColorDialogControl::myButton_Click(IInspectable const&, RoutedEventArgs const&)
    {
        
    }
}

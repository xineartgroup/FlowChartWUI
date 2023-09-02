// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include "winrt/Microsoft.UI.Xaml.h"
#include "winrt/Microsoft.UI.Xaml.Markup.h"
#include "winrt/Microsoft.UI.Xaml.Controls.Primitives.h"
#include "ColorDialogControl.g.h"

namespace winrt::FlowChartWUI::implementation
{
    struct ColorDialogControl : ColorDialogControlT<ColorDialogControl>
    {
        ColorDialogControl();

        void InitializeComponent2();

        void myButton_Click(Windows::Foundation::IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& args);
    };
}

namespace winrt::FlowChartWUI::factory_implementation
{
    struct ColorDialogControl : ColorDialogControlT<ColorDialogControl, implementation::ColorDialogControl>
    {
    };
}

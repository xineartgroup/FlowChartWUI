// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include "MainWindow.xaml.h"
#if __has_include("MainWindow.g.cpp")
#include "MainWindow.g.cpp"
#endif

using namespace Windows::Foundation::Collections;

namespace winrt::FlowChartWUI::implementation
{
    MainWindow::MainWindow()
    {
        InitializeComponent();
        InitializeComponent2();
    }

    void MainWindow::InitializeComponent2()
    {
        basePath = winrt::Windows::ApplicationModel::Package::Current().InstalledLocation().Path();

        try
        {
            //init_apartment();
            //Application app = Application::Current();
            //app.RequestedTheme(winrt::Microsoft::UI::Xaml::ApplicationTheme::Dark);
        }
        catch (const winrt::hresult_error& ex)
        {
            MessageBox(NULL, ex.message().c_str(), L"Error Loading Icons", 0);
        }

        DiagramChartsymbols.push_back(new FlowChart::Data::DiagramChartSymbols());
        DiagramClasssymbols.push_back(new FlowChart::Data::DiagramClassSymbols());

        Settings::InitializeSymbols();

        std::vector<ISymbol*> symbols = std::vector<ISymbol*>();

        int symbolCount = FlowChart::Data::Settings::GetChartSymbolCount();

        for (int index = 0; index < symbolCount; index++)
        {
            FlowChart::Data::ISymbol* symbol = FlowChart::Data::Settings::GetChartSymbol(index);
            if (symbol)
            {
                symbols.push_back(symbol);
            }
        }

        symbolCount = FlowChart::Data::Settings::GetClassSymbolCount();

        for (int index = 0; index < symbolCount; index++)
        {
            FlowChart::Data::ISymbol* symbol = FlowChart::Data::Settings::GetClassSymbol(index);
            if (symbol)
            {
                symbols.push_back(symbol);
            }
        }

        Thickness thickness;
        thickness.Bottom = 0.0;
        thickness.Left = 0.0;
        thickness.Right = 0.0;
        thickness.Top = 0.0;

        Thickness thickness1;
        thickness1.Bottom = 3.0;
        thickness1.Left = 3.0;
        thickness1.Right = 3.0;
        thickness1.Top = 3.0;

        CornerRadius cornerRadius;
        cornerRadius.BottomLeft = 0.0;
        cornerRadius.BottomRight = 0.0;
        cornerRadius.TopLeft = 0.0;
        cornerRadius.TopRight = 0.0;

        for (int32_t index = 0; index < symbols.size(); index++)
        {
            Grid gridSymbol;
            gridSymbol.Name(symbols[index]->GetTypeString());
            gridSymbol.Margin(thickness);
            gridSymbol.HorizontalAlignment(HorizontalAlignment::Stretch);
            gridSymbol.ColumnDefinitions().Append(ColumnDefinition());
            gridSymbol.ColumnDefinitions().Append(ColumnDefinition());

            gridSymbol.RowDefinitions().Append(RowDefinition());

            gridSymbol.RowDefinitions().Append(RowDefinition());

            TextBlock lblSymbolCaption;
            lblSymbolCaption.Name(L"lbl_Caption_" + symbols[index]->GetTypeString());
            lblSymbolCaption.Text(L"Caption: ");
            lblSymbolCaption.Width(120);
            lblSymbolCaption.Height(30);
            lblSymbolCaption.Margin(thickness1);
            lblSymbolCaption.FontFamily(FontFamily(L"Segoe UI Semilight"));
            lblSymbolCaption.FontSize(11.0);
            Grid::SetColumn(lblSymbolCaption, 0);
            Grid::SetRow(lblSymbolCaption, 1);
            gridSymbol.Children().Append(lblSymbolCaption);

            TextBox txtSymbolCaption;
            txtSymbolCaption.Name(L"txt_Caption_" + symbols[index]->GetTypeString());
            txtSymbolCaption.Text(symbols[index]->getCaption());
            txtSymbolCaption.Width(120);
            txtSymbolCaption.Height(30);
            txtSymbolCaption.Margin(thickness1);
            txtSymbolCaption.FontFamily(FontFamily(L"Segoe UI Semilight"));
            txtSymbolCaption.FontSize(11.0);
            txtSymbolCaption.CornerRadius(cornerRadius);
            txtSymbolCaption.TextChanged({ this, &MainWindow::TextBox1_TextChanged });
            Grid::SetColumn(txtSymbolCaption, 1);
            Grid::SetRow(txtSymbolCaption, 1);
            gridSymbol.Children().Append(txtSymbolCaption);

            int _COUNT = (int)gridSymbol.RowDefinitions().Size();

            int count = symbols[index]->GetPropertyCount();

            for (int i = 0; i < count; i++)
            {
                ItemProperty property_ = symbols[index]->GetProperty(i);

                gridSymbol.RowDefinitions().Append(RowDefinition());

                //if (property_)
                {

                    TextBlock labelProperty;
                    labelProperty.Margin(thickness1);
                    labelProperty.Text(property_.getTitle() + L": ");
                    labelProperty.Width(120);
                    labelProperty.Height(30);
                    labelProperty.FontFamily(FontFamily(L"Segoe UI Semilight"));
                    labelProperty.FontSize(11.0);
                    Grid::SetColumn(labelProperty, 0);
                    Grid::SetRow(labelProperty, i + _COUNT);

                    gridSymbol.Children().Append(labelProperty);

                    if (property_.getPropertyType() == Enumeration)
                    {
                        ComboBox comboBox1;
                        comboBox1.Name(property_.getName());
                        comboBox1.Margin(thickness1);
                        comboBox1.Width(120);
                        comboBox1.Height(30);
                        comboBox1.FontFamily(FontFamily(L"Segoe UI Semilight"));
                        comboBox1.FontSize(11.0);
                        comboBox1.CornerRadius(cornerRadius);
                        comboBox1.SelectionChanged({ this, &MainWindow::ComboBox1_SelectionChanged });
                        for (int32_t j = 0; j < property_.getEnumerations().size(); j++)
                        {
                            comboBox1.Items().Append(winrt::box_value(property_.getEnumerations()[j]));
                            if (property_.getEnumerations()[j] == property_.getValue())
                                comboBox1.SelectedIndex(j);
                        }
                        Grid::SetColumn(comboBox1, 1);
                        Grid::SetRow(comboBox1, i + _COUNT);

                        gridSymbol.Children().Append(comboBox1);
                    }
                    else if (property_.getPropertyType() == Boolean)
                    {
                        CheckBox checkBox1;
                        checkBox1.Name(property_.getName());
                        checkBox1.Margin(thickness1);
                        checkBox1.Height(20);
                        checkBox1.IsChecked(property_.getValue() == L"True");
                        checkBox1.Checked({ this, &MainWindow::CheckBox1_Checked });
                        checkBox1.Unchecked({ this, &MainWindow::CheckBox1_Checked });
                        Grid::SetColumn(checkBox1, 1);
                        Grid::SetRow(checkBox1, i + _COUNT);

                        gridSymbol.Children().Append(checkBox1);
                    }
                    else
                    {
                        TextBox textBox1;
                        textBox1.Name(property_.getName());
                        textBox1.Margin(thickness1);
                        textBox1.Width(120);
                        textBox1.Height(30);
                        textBox1.FontFamily(FontFamily(L"Segoe UI Semilight"));
                        textBox1.FontSize(11.0);
                        textBox1.CornerRadius(cornerRadius);
                        textBox1.Text(property_.getValue());
                        textBox1.TextChanged({ this, &MainWindow::TextBox1_TextChanged });
                        Grid::SetColumn(textBox1, 1);
                        Grid::SetRow(textBox1, i + _COUNT);

                        gridSymbol.Children().Append(textBox1);
                    }
                }
            }

            gridSymbol.Visibility(Visibility::Collapsed);
            pnlProperty().Children().Append(gridSymbol);
        }

        MenuFlyoutItem mi2;
        mi2.Text(L"Delete Symbol");
        mi2.Click({ this, &MainWindow::deleteToolStripMenuItem_Click });
        contextMenu2.Items().Append(mi2);

        MenuFlyoutItem mi3;
        mi3.Text(L"Duplicate Symbol");
        mi3.Click({ this, &MainWindow::duplicateChartToolStripMenuItem_Click });
        contextMenu2.Items().Append(mi3);

        MenuFlyoutItem mi9;
        mi9.Text(L"Rotate Anchor Points");
        mi9.Click({ this, &MainWindow::RotateAnchorPoints_Click });
        contextMenu2.Items().Append(mi9);

        MenuFlyoutItem mi4;
        mi4.Text(L"Delete Symbol");
        mi4.Click({ this, &MainWindow::deleteToolStripMenuItem_Click });
        contextMenu3.Items().Append(mi4);

        MenuFlyoutItem mi5;
        mi5.Text(L"Duplicate Symbol");
        mi5.Click({ this, &MainWindow::duplicateClassToolStripMenuItem_Click });
        contextMenu3.Items().Append(mi5);

        MenuFlyoutItem mi6;
        mi6.Text(L"Add Attribute");
        mi6.Click({ this, &MainWindow::addAttributeToolStripMenuItem_Click });
        contextMenu3.Items().Append(mi6);

        MenuFlyoutItem mi7;
        mi7.Text(L"Add Operation");
        mi7.Click({ this, &MainWindow::addOperationToolStripMenuItem_Click });
        contextMenu3.Items().Append(mi7);

        MenuFlyoutItem mi8;
        mi8.Text(L"Delete Link");
        mi8.Click({ this, &MainWindow::deleteLinkToolStripMenuItem_Click });
        contextMenu4.Items().Append(mi8);



        HDC hdc = GetDC(nullptr);

        LOGFONTA logFont;
        logFont.lfFaceName[0] = '\0';
        logFont.lfCharSet = DEFAULT_CHARSET;

        std::vector<winrt::hstring> fonts;

        EnumFontFamiliesExA(hdc, &logFont, reinterpret_cast<FONTENUMPROCA>(Utility::EnumFontFamiliesExProcA), reinterpret_cast<LPARAM>(&fonts), 0);

        ReleaseDC(nullptr, hdc);

        std::map<winrt::hstring, winrt::hstring> fontsDictionary;

        for (size_t i = 0; i < fonts.size(); i++)
        {
            if (fontsDictionary.find(fonts[i]) == fontsDictionary.end())
            {
                fontsDictionary.emplace(fonts[i], fonts[i]);
            }
        }

        for (std::map<winrt::hstring, winrt::hstring>::iterator it = fontsDictionary.begin(); it != fontsDictionary.end(); ++it)
        {
            if (winrt::to_string(it->first).substr(0, 1) != "@")
            {
                cboFontName().Items().Append(winrt::box_value(it->first));
            }
        }

        cboFontSize().Items().Append(winrt::box_value(L"8"));
        cboFontSize().Items().Append(winrt::box_value(L"9"));
        cboFontSize().Items().Append(winrt::box_value(L"10"));
        cboFontSize().Items().Append(winrt::box_value(L"11"));
        cboFontSize().Items().Append(winrt::box_value(L"12"));
        cboFontSize().Items().Append(winrt::box_value(L"14"));
        cboFontSize().Items().Append(winrt::box_value(L"16"));
        cboFontSize().Items().Append(winrt::box_value(L"18"));
        cboFontSize().Items().Append(winrt::box_value(L"20"));
        cboFontSize().Items().Append(winrt::box_value(L"24"));
        cboFontSize().Items().Append(winrt::box_value(L"28"));
        cboFontSize().Items().Append(winrt::box_value(L"36"));
        cboFontSize().Items().Append(winrt::box_value(L"48"));
        cboFontSize().Items().Append(winrt::box_value(L"72"));

        ControlTemplate ctrlTemplate = GetColorPaletteTemplate();

        MenuFlyout menuFlyout1;
        MenuFlyoutItem menuItem1;
        menuItem1.Template(ctrlTemplate);
        menuFlyout1.Items().Append(menuItem1);
        btnFontColor().Flyout(menuFlyout1);

        MenuFlyout menuFlyout2;
        MenuFlyoutItem menuItem2;
        menuItem2.Template(ctrlTemplate);
        menuFlyout2.Items().Append(menuItem2);
        btnFillColor().Flyout(menuFlyout2);

        MenuFlyout menuFlyout3;
        MenuFlyoutItem menuItem3;
        menuItem3.Template(ctrlTemplate);
        menuFlyout3.Items().Append(menuItem3);
        btnLineColor().Flyout(menuFlyout3);

        menuItem1.ApplyTemplate();
        menuItem2.ApplyTemplate();
        menuItem2.ApplyTemplate();

        for (int j = 1; j <= _ROWS; j++)
        {
            for (int i = 1; i <= _ROWS; i++)
            {
                Button button1 = menuItem1.GetTemplateChild(L"btn" +
                    to_hstring(std::to_string(i)) +
                    L"_" +
                    to_hstring(std::to_string(j))).try_as<Button>();
                if (button1)
                {
                    button1.Click({ this, &MainWindow::btnFontColor_Click });
                }

                Button button2 = menuItem2.GetTemplateChild(L"btn" +
                    to_hstring(std::to_string(i)) +
                    L"_" +
                    to_hstring(std::to_string(j))).try_as<Button>();
                if (button2)
                {
                    button2.Click({ this, &MainWindow::btnFillColor_Click });
                }

                Button button3 = menuItem3.GetTemplateChild(L"btn" +
                    to_hstring(std::to_string(i)) +
                    L"_" +
                    to_hstring(std::to_string(j))).try_as<Button>();
                if (button3)
                {
                    button3.Click({ this, &MainWindow::btnLineColor_Click });
                }
            }
        }

        Form1_Load();
    }

    ControlTemplate MainWindow::GetColorPaletteTemplate()
    {
        hstring str1 = L"";

        for (int i = 0; i < _ROWS; i++)
        {
            str1 = str1 + L"    <ColumnDefinition/>\n";
        }

        hstring str2 = L"";

        for (int i = 0; i < _ROWS; i++)
        {
            str2 = str2 + L"    <RowDefinition/>\n";
        }

        hstring str3 = L"";

        for (int j = 1; j <= _ROWS; j++)
        {
            for (int i = 1; i <= _ROWS; i++)
            {
                int r = (i == 1 || i == 4 || i == 5 || i == 16) ? j * _ROWS : 1;
                int g = (i == 2 || i == 5 || i == 6 || i == 16) ? j * _ROWS : 1;
                int b = (i == 3 || i == 4 || i == 6 || i == 16) ? j * _ROWS : 1;

                if (i == 7)
                {
                    r = 128;
                    g = j * _ROWS;
                    b = (_ROWS - j + 1) * _ROWS;
                }
                else if (i == 10)
                {
                    r = 1;
                    g = j * _ROWS;
                    b = (_ROWS - j + 1) * _ROWS;
                }
                else if (i == 13)
                {
                    r = 256;
                    g = j * _ROWS;
                    b = (_ROWS - j + 1) * _ROWS;
                }

                if (i == 8)
                {
                    r = (_ROWS - j + 1) * _ROWS;
                    g = 128;
                    b = j * _ROWS;
                }
                else if (i == 11)
                {
                    r = j * _ROWS;
                    g = 1;
                    b = (_ROWS - j + 1) * _ROWS;
                }
                else if (i == 14)
                {
                    r = (_ROWS - j + 1) * _ROWS;
                    g = 256;
                    b = j * _ROWS;
                }

                if (i == 9)
                {
                    r = j * _ROWS;
                    b = 128;
                    b = (_ROWS - j + 1) * _ROWS;
                }
                else if (i == 12)
                {
                    r = j * _ROWS;
                    b = 1;
                    b = (_ROWS - j + 1) * _ROWS;
                }
                else if (i == 15)
                {
                    r = j * _ROWS;
                    b = 256;
                    b = (_ROWS - j + 1) * _ROWS;
                }

                r = r - 1;
                g = g - 1;
                b = b - 1;

                std::stringstream sstream1;
                sstream1 << std::setfill('0') << std::setw(2) << std::hex << r;
                sstream1 << std::setfill('0') << std::setw(2) << std::hex << g;
                sstream1 << std::setfill('0') << std::setw(2) << std::hex << b;

                str3 = str3 + L"    <Button x:Name=\"btn" +
                    to_hstring(std::to_string(i)) +
                    L"_" +
                    to_hstring(std::to_string(j)) +
                    L"\" Grid.Column=\"" +
                    to_hstring(std::to_string(i)) +
                    L"\" Grid.Row=\"" +
                    to_hstring(std::to_string(j)) + 
                    L"\"" + 
                    L" Width=\"14\" Height=\"14\"" +
                    L" Background=\"#" +
                    to_hstring(sstream1.str()) +
                    L"\" CornerRadius=\"0\"" + 
                    L" BorderThickness=\"1\" ></Button>\n";
            }
        }

        hstring templateString = L"<ControlTemplate xmlns=\"http://schemas.microsoft.com/winfx/2006/xaml/presentation\" "
            L"xmlns:x=\"http://schemas.microsoft.com/winfx/2006/xaml\">\n"
            L"<Grid x:Name=\"grid1\" HorizontalAlignment=\"Center\" Margin=\"8,8,8,8\">\n"
            L"  <Grid.ColumnDefinitions>\n"
            + str1 +
            L"  </Grid.ColumnDefinitions>\n"
            L"  <Grid.RowDefinitions>\n"
            + str2 +
            L"  </Grid.RowDefinitions>\n"
            + str3 +
            L"</Grid>\n"
            L"</ControlTemplate>\n";

        return XamlReader::Load(templateString).as<ControlTemplate>();
    }

    void MainWindow::Form1_Load() //winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::WindowActivatedEventArgs const& args
    {
        int ctCount = Settings::GetChartSymbolCount();

        RedrawImage();

        int col = 0;
        int row = 0;

        Grid grid1;
        grid1.ColumnDefinitions().Append(ColumnDefinition());
        grid1.ColumnDefinitions().Append(ColumnDefinition());
        grid1.ColumnDefinitions().Append(ColumnDefinition());
        grid1.ColumnDefinitions().Append(ColumnDefinition());
        grid1.ColumnDefinitions().Append(ColumnDefinition());
        grid1.ColumnDefinitions().Append(ColumnDefinition());
        for (int i = 0; i < ctCount; i += 2)
        {
            grid1.RowDefinitions().Append(RowDefinition());
        }

        Thickness margin;
        margin.Bottom = 2.0;
        margin.Left = 2.0;
        margin.Right = 2.0;
        margin.Top = 2.0;

        CornerRadius cr;
        cr.BottomLeft = 21.0;
        cr.BottomRight = 21.0;
        cr.TopLeft = 21.0;
        cr.TopRight = 21.0;

        for (int i = 0; i < FlowChart::Data::Settings::GetChartSymbolCount(); i++)
        {
            FlowChart::Data::ISymbol* symbol = FlowChart::Data::Settings::GetChartSymbol(i);
            if (symbol)
            {
                Microsoft::UI::Xaml::Controls::Image image;
                try
                {
                    Microsoft::UI::Xaml::Media::Imaging::BitmapImage bitmapImage;
                    bitmapImage.UriSource(Windows::Foundation::Uri(basePath + L"\\Assets\\" + symbol->getIconName()));
                    image.Source(bitmapImage);
                }
                catch (...)
                {
                }

                winrt::hstring str = symbol->GetString();
                Button button;
                button.Content(image);
                button.Width(42.0);
                button.Height(42.0);
                button.Margin(margin);
                button.CornerRadius(cr);
                Grid::SetColumn(button, col);
                Grid::SetRow(button, row);
                button.Click({ this, &MainWindow::Button1_Click });

                ToolTip tooltip;
                tooltip.Content(box_value(str));
                ToolTipService::SetToolTip(button, tooltip);

                grid1.Children().Append(button);

                col++;
                if (col > 5)
                {
                    col = 0;
                    row++;
                }
            }
        }

        pnlSide1().Children().Append(grid1);

        col = 0;
        col = 0;

        Grid grid2;
        grid2.ColumnDefinitions().Append(ColumnDefinition());
        grid2.ColumnDefinitions().Append(ColumnDefinition());
        grid2.ColumnDefinitions().Append(ColumnDefinition());
        grid2.ColumnDefinitions().Append(ColumnDefinition());
        grid2.ColumnDefinitions().Append(ColumnDefinition());
        grid2.ColumnDefinitions().Append(ColumnDefinition());
        for (int i = 0; i < ctCount; i += 2)
        {
            grid2.RowDefinitions().Append(RowDefinition());
        }

        for (int i = 0; i < FlowChart::Data::Settings::GetClassSymbolCount(); i++)
        {
            FlowChart::Data::ISymbol* symbol = FlowChart::Data::Settings::GetClassSymbol(i);
            if (symbol)
            {
                Microsoft::UI::Xaml::Controls::Image image;
                try
                {
                    Microsoft::UI::Xaml::Media::Imaging::BitmapImage bitmapImage;
                    bitmapImage.UriSource(Windows::Foundation::Uri(basePath + L"\\Assets\\" + symbol->getIconName()));
                    image.Source(bitmapImage);
                }
                catch (...)
                {
                }

                winrt::hstring str = symbol->GetString();
                Button button;
                button.Content(image);
                button.Width(42.0);
                button.Height(42.0);
                button.Margin(margin);
                button.CornerRadius(cr);
                Grid::SetColumn(button, col);
                Grid::SetRow(button, row);
                button.Click({ this, &MainWindow::Button2_Click });

                ToolTip tooltip;
                tooltip.Content(box_value(str));
                ToolTipService::SetToolTip(button, tooltip);

                grid2.Children().Append(button);

                col++;
                if (col > 5)
                {
                    col = 0;
                    row++;
                }
            }
        }

        pnlSide2().Children().Append(grid2);
    }

    void MainWindow::RedrawImage()
    {
        //Window window = Window::Current();
        //if (window.Width() != Utility::FormWidth)
        //    window.Width(Utility::FormWidth);
        //if (window.Height() != Utility::FormHeight)
        //    window.Height(Utility::FormHeight);
        if (canvas().Width() != Utility::CanvasWidth)
            canvas().Width(Utility::CanvasWidth);
        if (canvas().Height() != Utility::CanvasHeight)
            canvas().Height(Utility::CanvasHeight);

        //canvas.Children.Clear(); //it causes the mouse event not to trigger for some reason
        for (uint32_t i = 0; i < canvas().Children().Size(); i++)
        {
            canvas().Children().RemoveAt(0);
        }

        FlowChart::Data::ISymbol* symbol = NULL;
        Link* link = NULL;

        if (tabDiagram().SelectedIndex() == 0)
        {
            DiagramChartsymbols[pageIndex]->Draw(canvas());
            symbol = DiagramChartsymbols[pageIndex]->GetSelection();
            LoadProperties(symbol);
            int propLoaded = LoadClassProperties(NULL);

            if (symbol)
            {
                if (propLoaded >= 0)
                {
                    if (pnlClassProperty().Visibility() != Visibility::Visible)
                    {
                        pnlClassProperty().Visibility(Visibility::Visible);
                        pnlProperty().Visibility(Visibility::Collapsed);
                    }
                }
                else
                {
                    if (pnlProperty().Visibility() != Visibility::Visible)
                    {
                        pnlProperty().Visibility(Visibility::Visible);
                        pnlClassProperty().Visibility(Visibility::Collapsed);
                    }
                }
            }
            else
            {
                if (pnlProperty().Visibility() != Visibility::Collapsed)
                {
                    pnlProperty().Visibility(Visibility::Collapsed);
                }
                if (pnlClassProperty().Visibility() != Visibility::Collapsed)
                {
                    pnlClassProperty().Visibility(Visibility::Collapsed);
                }
            }
        }
        else if (tabDiagram().SelectedIndex() == 1)
        {
            DiagramClasssymbols[pageIndex]->Draw(canvas());
            symbol = DiagramClasssymbols[pageIndex]->GetSelection();
            LoadProperties(symbol);
            int propLoaded = LoadClassProperties(symbol);

            if (symbol)
            {
                if (propLoaded >= 0)
                {
                    if (pnlClassProperty().Visibility() != Visibility::Visible)
                    {
                        pnlClassProperty().Visibility(Visibility::Visible);
                        pnlProperty().Visibility(Visibility::Collapsed);
                    }
                }
                else
                {
                    if (pnlProperty().Visibility() != Visibility::Visible)
                    {
                        pnlProperty().Visibility(Visibility::Visible);
                        pnlClassProperty().Visibility(Visibility::Collapsed);
                    }
                }
            }
            else
            {
                if (pnlProperty().Visibility() != Visibility::Collapsed)
                {
                    pnlProperty().Visibility(Visibility::Collapsed);
                }
                if (pnlClassProperty().Visibility() != Visibility::Collapsed)
                {
                    pnlClassProperty().Visibility(Visibility::Collapsed);
                }
            }
        }

        if (symbol)
        {
            System::Drawing::Font font = symbol->getTextFont();

            Thickness thicknessBold;
            Thickness thicknessItalic;
            Thickness thicknessUnderline;
            Thickness thicknessStrikethrough;
            thicknessBold.Bottom = font.Bold ? 2.0 : 0.0;
            thicknessBold.Left = font.Bold ? 2.0 : 0.0;
            thicknessBold.Right = font.Bold ? 2.0 : 0.0;
            thicknessBold.Top = font.Bold ? 2.0 : 0.0;
            thicknessItalic.Bottom = font.Italic ? 2.0 : 0.0;
            thicknessItalic.Left = font.Italic ? 2.0 : 0.0;
            thicknessItalic.Right = font.Italic ? 2.0 : 0.0;
            thicknessItalic.Top = font.Italic ? 2.0 : 0.0;
            thicknessUnderline.Bottom = font.Underline ? 2.0 : 0.0;
            thicknessUnderline.Left = font.Underline ? 2.0 : 0.0;
            thicknessUnderline.Right = font.Underline ? 2.0 : 0.0;
            thicknessUnderline.Top = font.Underline ? 2.0 : 0.0;
            thicknessStrikethrough.Bottom = font.Strikeout ? 2.0 : 0.0;
            thicknessStrikethrough.Left = font.Strikeout ? 2.0 : 0.0;
            thicknessStrikethrough.Right = font.Strikeout ? 2.0 : 0.0;
            thicknessStrikethrough.Top = font.Strikeout ? 2.0 : 0.0;

            cboFontName().IsEnabled(true);
            cboFontSize().IsEnabled(true);
            btnFontBold().IsEnabled(true);
            btnFontItalic().IsEnabled(true);
            btnFontUnderline().IsEnabled(true);
            btnFontStrikethrough().IsEnabled(true);
            btnFontColor().IsEnabled(true);
            btnLineColor().IsEnabled(true);
            btnFillColor().IsEnabled(true);

            cboFontName().SelectedValue(winrt::box_value(font.Name));
            cboFontSize().SelectedValue(winrt::box_value(winrt::to_hstring(std::to_string(static_cast<int>(font.Size)))));
            btnFontColor().Foreground(SolidColorBrush(symbol->getFontColor()));
            btnFontBold().BorderThickness(thicknessBold);
            btnFontItalic().BorderThickness(thicknessItalic);
            btnFontUnderline().BorderThickness(thicknessUnderline);
            btnFontStrikethrough().BorderThickness(thicknessStrikethrough);
            btnLineColor().Foreground(SolidColorBrush(symbol->getLineColor()));
            btnFillColor().Background(SolidColorBrush(symbol->getFillColor()));
        }
        else
        {
            Thickness thickness;
            thickness.Bottom = 0.0;
            thickness.Left = 0.0;
            thickness.Right = 0.0;
            thickness.Top = 0.0;

            cboFontName().SelectedValue(winrt::box_value(L""));
            cboFontSize().SelectedValue(winrt::box_value(L""));
            btnFontBold().BorderThickness(thickness);
            btnFontItalic().BorderThickness(thickness);
            btnFontUnderline().BorderThickness(thickness);
            btnFontStrikethrough().BorderThickness(thickness);

            cboFontName().IsEnabled(false);
            cboFontSize().IsEnabled(false);
            btnFontBold().IsEnabled(false);
            btnFontItalic().IsEnabled(false);
            btnFontUnderline().IsEnabled(false);
            btnFontStrikethrough().IsEnabled(false);
            btnFontColor().IsEnabled(false);
            btnLineColor().IsEnabled(false);
            btnFillColor().IsEnabled(false);

            for (size_t i = 0; i < Settings::Links.size(); i++)
            {
                if (Settings::Links[i]->IsSelected)
                {
                    link = Settings::Links[i];
                    break;
                }
            }
        }

        LoadLinkProperties(link);
        if (link)
        {
            pnlLinkProperty().Visibility(Visibility::Visible);
        }
        else
        {
            pnlLinkProperty().Visibility(Visibility::Collapsed);
        }
    }

    int MainWindow::LoadProperties(ISymbol* symbol)
    {
        if (symbol)
        {
            //reload property panels here
            for (uint32_t i = 0; i < pnlProperty().Children().Size(); i++)
            {
                UIElement element = (pnlProperty().Children().GetAt(i));
                Grid gridSymbol = element.as<Grid>();
                if (gridSymbol)
                {
                    gridSymbol.Visibility(Visibility::Collapsed);
                    if (gridSymbol.Name() == symbol->GetTypeString())
                    {
                        gridSymbol.Visibility(Visibility::Visible);
                        for (uint32_t k = 0; k <= gridSymbol.Children().Size(); k++)
                        {
                            for (int j = 0; j <= symbol->GetPropertyCount(); j++)
                            {
                                ItemProperty property_Renamed = symbol->GetProperty(j);
                                if (gridSymbol.Children().Size() > k)
                                {
                                    UIElement elmnt = gridSymbol.Children().GetAt(k);
                                    TextBox textBox = elmnt.try_as<TextBox>();
                                    ComboBox comboBox = elmnt.try_as<ComboBox>();
                                    CheckBox checkBox = elmnt.try_as<CheckBox>();

                                    if (textBox)
                                    {
                                        if (L"txt_Name_" + symbol->GetTypeString() == textBox.Name())
                                        {
                                            textBox.Text(symbol->getName());
                                        }
                                        else if (L"txt_Caption_" + symbol->GetTypeString() == textBox.Name())
                                        {
                                            textBox.Text(symbol->getCaption());
                                        }
                                        else if (property_Renamed.getName() == textBox.Name())
                                        {
                                            textBox.Text(property_Renamed.getValue());
                                        }
                                    }
                                    else if (comboBox)
                                    {
                                        if (property_Renamed.getName() == comboBox.Name())
                                        {
                                            for (int32_t index = 0; index < property_Renamed.getEnumerations().size(); index++)
                                            {
                                                if (property_Renamed.getEnumerations()[index] == property_Renamed.getValue())
                                                    comboBox.SelectedIndex(index);
                                            }
                                        }
                                    }
                                    else if (checkBox)
                                    {
                                        if (property_Renamed.getName() == checkBox.Name())
                                        {
                                            checkBox.IsChecked(property_Renamed.getValue() == L"True");
                                        }
                                    }

                                }
                            }
                        }
                    }
                }
            }
        }

        return 0;
    }

    int MainWindow::LoadClassProperties(ISymbol* symbol)
    {
        if (symbol)
        {
            ISymbolClass* symbolClass = static_cast<ISymbolClass*>(symbol);
            ItemProperty itemProp = symbolClass->GetSelectedAttribute();

            btnDeleteClassProperty().Content(winrt::box_value(L"Delete Attribute"));

            if (itemProp.getName() == L"")
            {
                itemProp = symbolClass->GetSelectedOperation();
                btnDeleteClassProperty().Content(winrt::box_value(L"Delete Operation"));
            }

            if (itemProp.getName() != L"")
            {
                if (txtClassPropertyName().Text() != itemProp.getName())
                    txtClassPropertyName().Text(itemProp.getName());
                if (cboClassPropertyType().SelectedIndex() != itemProp.getPropertyType())
                    cboClassPropertyType().SelectedIndex(itemProp.getPropertyType());
                if (cboClassPropertyVisibility().SelectedIndex() != itemProp.getPropertyVisibility())
                    cboClassPropertyVisibility().SelectedIndex(itemProp.getPropertyVisibility());
                return 0;
            }
        }

        return -1;
    }

    int MainWindow::LoadLinkProperties(Link* link)
    {
        if (link)
        {
            if (txtLinkPropertySize().Text() != winrt::to_hstring(link->StrokeSize))
                txtLinkPropertySize().Text(winrt::to_hstring(link->StrokeSize));
            if (cboLinkPropertyStroke().SelectedIndex() != link->Stroke)
                cboLinkPropertyStroke().SelectedIndex(link->Stroke);
        }
        return 0;
    }

    void MainWindow::TextChangeEvent(Windows::Foundation::IInspectable const&, Microsoft::UI::Xaml::RoutedEventArgs const&)
    {
        //if (TextChangeEvent)
        {
            Window window = Window::Current();
            StackPanel stackPanel;
            stackPanel.Orientation(Orientation::Vertical);
            //stackPanel.Children().Append(Label{Content = "Label"});
            //stackPanel.Children().Append(Button{ Content = "Button" });
            window.Content(stackPanel);

            /*
             * new QuadraticBezierSegment(
                new Point(200, 200),
                new Point(300, 100),
                true)
            */
        }
    }

    void MainWindow::OpenFile_Click(IInspectable const&, Microsoft::UI::Xaml::RoutedEventArgs const&)
    {
        
    }

    void MainWindow::SaveFile_Click(IInspectable const&, Microsoft::UI::Xaml::RoutedEventArgs const&)
    {
        
    }

    void MainWindow::CloseFile_Click(IInspectable const&, Microsoft::UI::Xaml::RoutedEventArgs const&)
    {
        
    }

    void MainWindow::Settings_Click(IInspectable const&, Microsoft::UI::Xaml::RoutedEventArgs const&)
    {
        
    }

    void MainWindow::pictureBox1_DoubleTapped(IInspectable const&, Microsoft::UI::Xaml::Input::DoubleTappedRoutedEventArgs const& e)
    {
        winrt::Windows::Foundation::Point point = e.GetPosition(canvas());

        FlowChart::Data::Utility::MousePosition = winrt::Windows::Foundation::Point(point.X, point.Y);

        DiagramChartsymbols[pageIndex]->SelectHit();

        FlowChart::Data::ISymbol* symbol = DiagramChartsymbols[pageIndex]->GetSelection();
        if (symbol)
        {
            symbol->setIsEditing(true);
        }
    }

    void MainWindow::pictureBox1_MouseDown(IInspectable const&, winrt::Microsoft::UI::Xaml::Input::PointerRoutedEventArgs const& args)
    {
        winrt::Microsoft::UI::Input::PointerPoint point = args.GetCurrentPoint(canvas());

        FlowChart::Data::Utility::MousePosition = winrt::Windows::Foundation::Point(point.Position().X, point.Position().Y);

        Dragging = true;

        canvas().ContextFlyout(contextMenu1());

        FlowChart::Data::PointerHit* selectedItem = new FlowChart::Data::PointerHit();

        if (tabDiagram().SelectedIndex() == 0)
        {
            selectedItem = DiagramChartsymbols[pageIndex]->SelectHit();

            if (selectedItem->ItemIndex >= 0)
            {
                if (selectedItem->Itemtype == FlowChart::Data::ItemType::Symbol)
                {
                    //forceMouseCapture = canvas().CapturePointer();
                    canvas().ContextFlyout(contextMenu2);
                }
                else if (selectedItem->Itemtype == FlowChart::Data::ItemType::Linker)
                {
                    //forceMouseCapture = canvas().CapturePointer();
                    canvas().ContextFlyout(contextMenu4);
                }
            }

            if (FlowChart::Data::Utility::LinkingIndex >= 0)
            {
                Dragging = false;
            }
            else
            {
                if (FlowChart::Data::Settings::NewSymbol)
                {
                    ISymbolChart* symbol = static_cast<ISymbolChart*>(FlowChart::Data::Settings::NewSymbol);

                    float x = point.Position().X - (symbol->GetWidth() / 2);
                    float y = point.Position().Y - (symbol->GetHeight() / 2);

                    FlowChart::Data::Settings::NewSymbol->SetPosition(x, y);
                    FlowChart::Data::Settings::NewSymbol->setIsSelected(true);
                    DiagramChartsymbols[pageIndex]->AddSymbol(symbol);
                    FlowChart::Data::Settings::NewSymbol = NULL;
                    RedrawImage();

                    Dragging = false;
                }
            }
        }
        else if (tabDiagram().SelectedIndex() == 1)
        {
            selectedItem = DiagramClasssymbols[pageIndex]->SelectHit();

            if (selectedItem->ItemIndex >= 0)
            {
                if (selectedItem->Itemtype == FlowChart::Data::ItemType::Symbol)
                {
                    //forceMouseCapture = canvas().CapturePointer();
                    canvas().ContextFlyout(contextMenu3);
                }
                else if (selectedItem->Itemtype == FlowChart::Data::ItemType::Linker)
                {
                    //forceMouseCapture = canvas().CapturePointer();
                    canvas().ContextFlyout(contextMenu4);
                }
            }

            if (FlowChart::Data::Utility::LinkingIndex >= 0)
            {
                Dragging = false;
            }
            else
            {
                if (FlowChart::Data::Settings::NewSymbol)
                {
                    ISymbolClass* symbol = static_cast<ISymbolClass*>(FlowChart::Data::Settings::NewSymbol);

                    float x = point.Position().X - (symbol->GetWidth() / 2);
                    float y = point.Position().Y - (symbol->GetHeight() / 2);

                    FlowChart::Data::Settings::NewSymbol->SetPosition(x, y);
                    FlowChart::Data::Settings::NewSymbol->setIsSelected(true);
                    DiagramClasssymbols[pageIndex]->AddSymbol(symbol);
                    FlowChart::Data::Settings::NewSymbol = NULL;
                    RedrawImage();

                    Dragging = false;
                }
            }
        }
    }

    void MainWindow::pictureBox1_MouseMove(IInspectable const&, winrt::Microsoft::UI::Xaml::Input::PointerRoutedEventArgs const& args)
    {
        winrt::Microsoft::UI::Input::PointerPoint point = args.GetCurrentPoint(canvas());

        winrt::Windows::Foundation::Point secondPoint = winrt::Windows::Foundation::Point(point.Position().X, point.Position().Y);

        lblMousePosition().Text(winrt::to_hstring(static_cast<int>(secondPoint.X)) + L", " + winrt::to_hstring(static_cast<int>(secondPoint.Y)));

        float changeX = secondPoint.X - FlowChart::Data::Utility::MousePosition.X;
        float changeY = secondPoint.Y - FlowChart::Data::Utility::MousePosition.Y;

        if (Dragging)
        {
            if (tabDiagram().SelectedIndex() == 0)
            {
                DiagramChartsymbols[pageIndex]->MoveSelection(changeX, changeY);
            }
            else if (tabDiagram().SelectedIndex() == 1)
            {
                DiagramClasssymbols[pageIndex]->MoveSelection(changeX, changeY);
            }
        }

        if (tabDiagram().SelectedIndex() == 0)
        {
            DiagramChartsymbols[pageIndex]->SetHoverItem();
        }
        else if (tabDiagram().SelectedIndex() == 1)
        {
            DiagramClasssymbols[pageIndex]->SetHoverItem();
        }

        FlowChart::Data::Utility::MousePosition = winrt::Windows::Foundation::Point(point.Position().X, point.Position().Y);

        RedrawImage();

        if (forceMouseCapture)
        {
            //canvas().ReleaseMouseCapture();
            forceMouseCapture = false;
        }
    }

    void MainWindow::pictureBox1_MouseUp(IInspectable const&, winrt::Microsoft::UI::Xaml::Input::PointerRoutedEventArgs const&)
    {
        if (tabDiagram().SelectedIndex() == 0)
        {
            DiagramChartsymbols[pageIndex]->Link();
        }
        else if (tabDiagram().SelectedIndex() == 1)
        {
            DiagramClasssymbols[pageIndex]->Link();
        }

        FlowChart::Data::Utility::LinkItem = -1;
        FlowChart::Data::Utility::LinkingIndex = -1;

        Dragging = false;

        RedrawImage();
    }

    void MainWindow::deleteLinkToolStripMenuItem_Click(IInspectable const&, winrt::Microsoft::UI::Xaml::RoutedEventArgs const&)
    {
        DiagramChartsymbols[pageIndex]->DeleteSelectedLink();
        RedrawImage();
    }

    void MainWindow::deleteToolStripMenuItem_Click(IInspectable const&, winrt::Microsoft::UI::Xaml::RoutedEventArgs const&)
    {
        DiagramChartsymbols[pageIndex]->DeleteSelectedSymbol();
        RedrawImage();
    }

    void MainWindow::addAttributeToolStripMenuItem_Click(IInspectable const&, winrt::Microsoft::UI::Xaml::RoutedEventArgs const&)
    {
        DiagramClasssymbols[pageIndex]->AddAttribute();
        RedrawImage();
    }

    void MainWindow::addOperationToolStripMenuItem_Click(IInspectable const&, winrt::Microsoft::UI::Xaml::RoutedEventArgs const&)
    {
        DiagramClasssymbols[pageIndex]->AddOperation();
        RedrawImage();
    }

    void MainWindow::duplicateClassToolStripMenuItem_Click(IInspectable const&, winrt::Microsoft::UI::Xaml::RoutedEventArgs const&)
    {
        DiagramClasssymbols[pageIndex]->DuplicateSymbol();
        RedrawImage();
    }

    void MainWindow::duplicateChartToolStripMenuItem_Click(IInspectable const&, winrt::Microsoft::UI::Xaml::RoutedEventArgs const&)
    {
        DiagramChartsymbols[pageIndex]->DuplicateSymbol();
        RedrawImage();
    }

    void MainWindow::ComboBox1_SelectionChanged(IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const&)
    {
        ComboBox comboBox = sender.as<ComboBox>();

        ISymbol* symbol = NULL;

        if (tabDiagram().SelectedIndex() == 0)
        {
            symbol = DiagramChartsymbols[pageIndex]->GetSelection();
        }
        else if (tabDiagram().SelectedIndex() == 1)
        {
            symbol = DiagramClasssymbols[pageIndex]->GetSelection();
        }

        if (symbol)
        {
            int count = symbol->GetPropertyCount();

            for (int i = 0; i < count; i++)
            {
                ItemProperty property = symbol->GetProperty(i);

                //if (property)
                {
                    if (property.getName() == comboBox.Name())
                    {
                        property.setValue(winrt::unbox_value<hstring>(comboBox.SelectedValue()));
                        symbol->SetProperty(i, property);
                        RedrawImage();
                    }
                }
            }
        }
    }

    void MainWindow::cboClassPropertyType_SelectionChanged(IInspectable const&, Microsoft::UI::Xaml::RoutedEventArgs const&)
    {
        FlowChart::Data::ISymbol* symbol = NULL;

        if (tabDiagram().SelectedIndex() == 0)
        {
            symbol = DiagramChartsymbols[pageIndex]->GetSelection();
        }
        else if (tabDiagram().SelectedIndex() == 1)
        {
            symbol = DiagramClasssymbols[pageIndex]->GetSelection();
            if (symbol != NULL)
            {
                ISymbolClass* symbolClass = (ISymbolClass*)symbol;
                ItemProperty itemProp = symbolClass->GetSelectedAttribute();
                if (itemProp.getName() != L"")
                {
                    if (itemProp.getPropertyType() != (PropertyType)cboClassPropertyType().SelectedIndex())
                    {
                        itemProp.setPropertyType((PropertyType)cboClassPropertyType().SelectedIndex());
                        symbolClass->UpdateSelectedAttribute(itemProp);
                        RedrawImage();
                    }
                }
                itemProp = symbolClass->GetSelectedOperation();
                if (itemProp.getName() != L"")
                {
                    if (itemProp.getPropertyType() != (PropertyType)cboClassPropertyType().SelectedIndex())
                    {
                        itemProp.setPropertyType((PropertyType)cboClassPropertyType().SelectedIndex());
                        symbolClass->UpdateSelectedOperation(itemProp);
                        RedrawImage();
                    }
                }
            }
        }
    }

    void MainWindow::cboClassPropertyVisibility_SelectionChanged(IInspectable const&, Microsoft::UI::Xaml::RoutedEventArgs const&)
    {
        FlowChart::Data::ISymbol* symbol = NULL;

        if (tabDiagram().SelectedIndex() == 0)
        {
            symbol = DiagramChartsymbols[pageIndex]->GetSelection();
        }
        else if (tabDiagram().SelectedIndex() == 1)
        {
            symbol = DiagramClasssymbols[pageIndex]->GetSelection();
            if (symbol != NULL)
            {
                ISymbolClass* symbolClass = (ISymbolClass*)symbol;

                ItemProperty itemProp = symbolClass->GetSelectedAttribute();
                if (itemProp.getName() != L"")
                {
                    if (itemProp.getPropertyVisibility() != (PropertyVisibility)cboClassPropertyVisibility().SelectedIndex())
                    {
                        itemProp.setPropertyVisibility((PropertyVisibility)cboClassPropertyVisibility().SelectedIndex());
                        symbolClass->UpdateSelectedAttribute(itemProp);
                        RedrawImage();
                    }
                }

                itemProp = symbolClass->GetSelectedOperation();
                if (itemProp.getName() != L"")
                {
                    if (itemProp.getPropertyVisibility() != (PropertyVisibility)cboClassPropertyVisibility().SelectedIndex())
                    {
                        itemProp.setPropertyVisibility((PropertyVisibility)cboClassPropertyVisibility().SelectedIndex());
                        symbolClass->UpdateSelectedOperation(itemProp);
                        RedrawImage();
                    }
                }
            }
        }
    }

    void MainWindow::txtClassPropertyName_TextChanged(IInspectable const&, Microsoft::UI::Xaml::RoutedEventArgs const&)
    {
        FlowChart::Data::ISymbol* symbol = NULL;

        if (tabDiagram().SelectedIndex() == 0)
        {
            symbol = DiagramChartsymbols[pageIndex]->GetSelection();
        }
        else if (tabDiagram().SelectedIndex() == 1)
        {
            symbol = DiagramClasssymbols[pageIndex]->GetSelection();
            if (symbol != NULL)
            {
                ISymbolClass* symbolClass = (ISymbolClass*)symbol;
                ItemProperty itemProp = symbolClass->GetSelectedAttribute();
                if (itemProp.getName() != L"")
                {
                    if (itemProp.getName() != txtClassPropertyName().Text())
                    {
                        itemProp.setName(txtClassPropertyName().Text());
                        symbolClass->UpdateSelectedAttribute(itemProp);
                        RedrawImage();
                    }
                }
                itemProp = symbolClass->GetSelectedOperation();
                if (itemProp.getName() != L"")
                {
                    if (itemProp.getName() != txtClassPropertyName().Text())
                    {
                        itemProp.setName(txtClassPropertyName().Text());
                        symbolClass->UpdateSelectedOperation(itemProp);
                        RedrawImage();
                    }
                }
            }
        }
    }

    void MainWindow::btnDeleteClassProperty_Click(IInspectable const&, Microsoft::UI::Xaml::RoutedEventArgs const&)
    {
        FlowChart::Data::ISymbol* symbol = NULL;

        if (tabDiagram().SelectedIndex() == 0)
        {
            symbol = DiagramChartsymbols[pageIndex]->GetSelection();
        }
        else if (tabDiagram().SelectedIndex() == 1)
        {
            symbol = DiagramClasssymbols[pageIndex]->GetSelection();
            if (symbol != NULL)
            {
                ISymbolClass* symbolClass = (ISymbolClass*)symbol;
                ItemProperty itemProp = symbolClass->GetSelectedAttribute();
                if (itemProp.getName() != L"")
                {
                    symbolClass->RemoveSelectedAttribute();
                    RedrawImage();
                }
                itemProp = symbolClass->GetSelectedOperation();
                if (itemProp.getName() != L"")
                {
                    symbolClass->RemoveSelectedOperation();
                    RedrawImage();
                }
            }
        }
    }

    void MainWindow::btnLineColor_Click(IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const&)
    {
        FlowChart::Data::ISymbol* symbol = DiagramChartsymbols[pageIndex]->GetSelection();
        if (symbol)
        {
            Button button = sender.as<Button>();
            if (SolidColorBrush solidBrush = button.Background().try_as<SolidColorBrush>())
            {
                symbol->setLineColor(solidBrush.Color());
            }
            RedrawImage();
        }
    }

    void MainWindow::btnFillColor_Click(IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const&)
    {
        FlowChart::Data::ISymbol* symbol = DiagramChartsymbols[pageIndex]->GetSelection();
        if (symbol)
        {
            Button button = sender.as<Button>();
            if (SolidColorBrush solidBrush = button.Background().try_as<SolidColorBrush>())
            {
                symbol->setFillColor(solidBrush.Color());
            }
            RedrawImage();
        }
    }

    void MainWindow::btnFontColor_Click(IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const&)
    {
        FlowChart::Data::ISymbol* symbol = DiagramChartsymbols[pageIndex]->GetSelection();
        if (symbol)
        {
            Button button = sender.as<Button>();
            if (SolidColorBrush solidBrush = button.Background().try_as<SolidColorBrush>())
            {
                symbol->setFontColor(solidBrush.Color());
            }
            RedrawImage();
        }
    }

    void MainWindow::btnFont_Click(IInspectable const&, Microsoft::UI::Xaml::RoutedEventArgs const&)
    {
        FlowChart::Data::ISymbol* symbol = DiagramChartsymbols[pageIndex]->GetSelection();
        if (symbol)
        {
            /*System::Windows::Forms::FontDialog fd;
            if (fd.ShowDialog() == System.Windows.Forms.DialogResult.OK)
            {
                symbol->setTextFont(fd.Font);
            }*/
        }
    }

    void MainWindow::btnFontBold_Click(IInspectable const&, Microsoft::UI::Xaml::RoutedEventArgs const&)
    {
        FlowChart::Data::ISymbol* symbol = DiagramChartsymbols[pageIndex]->GetSelection();
        if (symbol)
        {
            System::Drawing::Font font = symbol->getTextFont();
            font.Bold = !font.Bold;
            symbol->setTextFont(font);
            RedrawImage();
        }
    }

    void MainWindow::btnFontItalic_Click(IInspectable const&, Microsoft::UI::Xaml::RoutedEventArgs const&)
    {
        FlowChart::Data::ISymbol* symbol = DiagramChartsymbols[pageIndex]->GetSelection();
        if (symbol)
        {
            System::Drawing::Font font = symbol->getTextFont();
            font.Italic = !font.Italic;
            symbol->setTextFont(font);
            RedrawImage();
        }
    }

    void MainWindow::btnFontUnderline_Click(IInspectable const&, Microsoft::UI::Xaml::RoutedEventArgs const&)
    {
        FlowChart::Data::ISymbol* symbol = DiagramChartsymbols[pageIndex]->GetSelection();
        if (symbol)
        {
            System::Drawing::Font font = symbol->getTextFont();
            font.Underline = !font.Underline;
            symbol->setTextFont(font);
            RedrawImage();
        }
    }

    void MainWindow::btnFontStrikethrough_Click(IInspectable const&, Microsoft::UI::Xaml::RoutedEventArgs const&)
    {
        FlowChart::Data::ISymbol* symbol = DiagramChartsymbols[pageIndex]->GetSelection();
        if (symbol)
        {
            System::Drawing::Font font = symbol->getTextFont();
            font.Strikeout = !font.Strikeout;
            symbol->setTextFont(font);
            RedrawImage();
        }
    }

    void MainWindow::cboFontName_SelectionChanged(IInspectable const&, winrt::Microsoft::UI::Xaml::Controls::SelectionChangedEventArgs const&)
    {
        FlowChart::Data::ISymbol* symbol = DiagramChartsymbols[pageIndex]->GetSelection();
        if (symbol)
        {
            System::Drawing::Font font = symbol->getTextFont();
            font.Name = winrt::unbox_value<winrt::hstring>(cboFontName().SelectedValue());
            symbol->setTextFont(font);
            RedrawImage();
        }
    }

    void MainWindow::cboFontSize_SelectionChanged(IInspectable const&, winrt::Microsoft::UI::Xaml::Controls::SelectionChangedEventArgs const&)
    {
        FlowChart::Data::ISymbol* symbol = DiagramChartsymbols[pageIndex]->GetSelection();
        if (symbol)
        {
            System::Drawing::Font font = symbol->getTextFont();
            font.Size = static_cast<float>(std::atoi(winrt::to_string(winrt::unbox_value<winrt::hstring>(cboFontSize().SelectedValue())).c_str()));
            if (font.Size < 1.0)
                font.Size = 8.0;
            symbol->setTextFont(font);
            RedrawImage();
        }
    }

    void MainWindow::Button1_Click(IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const&)
    {
        Button button = sender.as<Button>();
        IInspectable iis = ToolTipService::GetToolTip(button);
        ToolTip toolTip = unbox_value<ToolTip>(iis);
        IInspectable content = toolTip.Content();

        if (content)
        {
            hstring str = unbox_value<hstring>(content);

            for (int i = 0; i < FlowChart::Data::Settings::GetChartSymbolCount(); i++)
            {
                FlowChart::Data::ISymbolChart* symbol = FlowChart::Data::Settings::GetChartSymbol(i);
                if (symbol)
                {
                    if (symbol->GetString() == str)
                    {
                        FlowChart::Data::Settings::NewSymbol = symbol->GetInstance();
                        FlowChart::Data::Settings::NewSymbol->setIsSelected(true);
                        break;
                    }
                }
            }
        }
    }

    void MainWindow::Button2_Click(IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const&)
    {
        Button button = sender.as<Button>();
        IInspectable iis = ToolTipService::GetToolTip(button);
        ToolTip toolTip = unbox_value<ToolTip>(iis);
        IInspectable content = toolTip.Content();

        if (content)
        {
            hstring str = unbox_value<hstring>(content);

            for (int i = 0; i < FlowChart::Data::Settings::GetClassSymbolCount(); i++)
            {
                FlowChart::Data::ISymbolClass* symbol = FlowChart::Data::Settings::GetClassSymbol(i);
                if (symbol)
                {
                    if (symbol->GetString() == str)
                    {
                        FlowChart::Data::Settings::NewSymbol = symbol->GetInstance();
                        FlowChart::Data::Settings::NewSymbol->setIsSelected(true);
                        break;
                    }
                }
            }
        }
    }

    void MainWindow::TextBox1_TextChanged(IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const&)
    {
        TextBox textBox = sender.try_as<TextBox>();

        FlowChart::Data::ISymbol* symbol = NULL;

        if (tabDiagram().SelectedIndex() == 0)
        {
            symbol = DiagramChartsymbols[pageIndex]->GetSelection();
        }
        else if (tabDiagram().SelectedIndex() == 1)
        {
            symbol = DiagramClasssymbols[pageIndex]->GetSelection();
        }

        if (symbol)
        {
            if (textBox.Name() == L"txt_Name_" + symbol->GetTypeString())
            {
                symbol->setName(textBox.Text());
            }

            if (textBox.Name() == L"txt_Caption_" + symbol->GetTypeString())
            {
                symbol->setCaption(textBox.Text());
            }

            int count = symbol->GetPropertyCount();

            for (int i = 0; i < count; i++)
            {
                ItemProperty property_Renamed = symbol->GetProperty(i);

                if (property_Renamed.getName() != L"")
                {
                    if (property_Renamed.getName() == textBox.Name())
                    {
                        property_Renamed.setValue(textBox.Text());
                        break;
                    }
                }
            }
        }

        RedrawImage();

        textBox.Focus(FocusState::Keyboard);
    }

    void MainWindow::CheckBox1_Checked(IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const&)
    {
        FlowChart::Data::ISymbol* symbol = NULL;

        if (tabDiagram().SelectedIndex() == 0)
        {
            symbol = DiagramChartsymbols[pageIndex]->GetSelection();
        }
        else if (tabDiagram().SelectedIndex() == 1)
        {
            symbol = DiagramClasssymbols[pageIndex]->GetSelection();
        }

        if (symbol)
        {
            int count = symbol->GetPropertyCount();

            for (int i = 0; i < count; i++)
            {
                ItemProperty property_Renamed = symbol->GetProperty(i);

                //if (property_Renamed)
                {
                    CheckBox val = sender.as<CheckBox>();
                    if (property_Renamed.getName() == val.Name())
                    {
                        property_Renamed.setValue((val.IsChecked() != 0) ? (static_cast<bool>(val.IsChecked()) ? L"True" : L"False") : L"False");
                    }
                }
            }
        }
    }

    void MainWindow::ClearScreen_Click(IInspectable const&, Microsoft::UI::Xaml::RoutedEventArgs const&)
    {
        DiagramChartsymbols[pageIndex]->ClearSymbols();
        DiagramClasssymbols[pageIndex]->ClearSymbols();
        Settings::Links.clear();
        RedrawImage();
    }

    void MainWindow::ToggleLinkSmoothing_Click(IInspectable const&, Microsoft::UI::Xaml::RoutedEventArgs const&)
    {
        Spline2D::Smoothing = !Spline2D::Smoothing;
        RedrawImage();
    }

    void MainWindow::RotateAnchorPoints_Click(IInspectable const&, Microsoft::UI::Xaml::RoutedEventArgs const&)
    {
        FlowChart::Data::ISymbolChart* symbol = NULL;

        if (tabDiagram().SelectedIndex() == 0)
        {
            symbol = DiagramChartsymbols[pageIndex]->GetSelection();
        }

        if (symbol)
        {
            symbol->RotateAnchorPoints();
        }

        RedrawImage();
    }

    void MainWindow::RotateAllAnchorPoints_Click(IInspectable const&, Microsoft::UI::Xaml::RoutedEventArgs const&)
    {
        
        RedrawImage();
    }

    void MainWindow::cboLinkPropertyStroke_SelectionChanged(IInspectable const&, winrt::Microsoft::UI::Xaml::Controls::SelectionChangedEventArgs const&)
    {
        for (size_t i = 0; i < Settings::Links.size(); i++)
        {
            if (Settings::Links[i]->IsSelected)
            {
                Settings::Links[i]->Stroke = (StrokeStyle)cboLinkPropertyStroke().SelectedIndex();
                RedrawImage();
                break;
            }
        }
    }

    void MainWindow::txtLinkPropertySize_TextChanged(IInspectable const&, winrt::Microsoft::UI::Xaml::Controls::TextChangedEventArgs const&)
    {
        for (size_t i = 0; i < Settings::Links.size(); i++)
        {
            if (Settings::Links[i]->IsSelected)
            {
                Settings::Links[i]->StrokeSize = std::atoi(winrt::to_string(txtLinkPropertySize().Text()).c_str());
                RedrawImage();
                break;
            }
        }
    }
}

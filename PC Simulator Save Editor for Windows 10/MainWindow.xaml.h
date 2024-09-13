#pragma once

#include "MainWindow.g.h"

using namespace winrt::Windows::Storage;

namespace winrt::PC_Simulator_Save_Editor_for_Windows_10::implementation
{
    struct MainWindow : MainWindowT<MainWindow>
    {
        MainWindow()
        {
            // Xaml objects should not call InitializeComponent during construction.
            // See https://github.com/microsoft/cppwinrt/tree/master/nuget#initializecomponent
            Title(L"PC Simulator Save Editor");
            winrt::Microsoft::UI::Windowing::IAppWindow window = AppWindow();
            window.SetIcon(L"PC Simulator Save Editor.ico");
        }

        int32_t MyProperty();
        void MyProperty(int32_t value);

        void myButton_Click(IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& args);

        void copy(IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& args);

        fire_and_forget openFile_Click(IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& args);

        fire_and_forget saveFile_Click(IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& args);

        HWND MainWindow::GetWindowHandleFromThis();
    };
}

namespace winrt::PC_Simulator_Save_Editor_for_Windows_10::factory_implementation
{
    struct MainWindow : MainWindowT<MainWindow, implementation::MainWindow>
    {
    };
}

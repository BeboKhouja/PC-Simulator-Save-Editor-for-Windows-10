#pragma once

#include "App.xaml.g.h"

namespace winrt::PC_Simulator_Save_Editor_for_Windows_10::implementation
{
    struct App : AppT<App>
    {
        App();

        void OnLaunched(Microsoft::UI::Xaml::LaunchActivatedEventArgs const&);

    private:
        winrt::Microsoft::UI::Xaml::Window window{ nullptr };
    };
}

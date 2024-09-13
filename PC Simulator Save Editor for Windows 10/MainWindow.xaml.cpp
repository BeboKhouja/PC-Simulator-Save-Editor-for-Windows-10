#include "pch.h"
#include "MainWindow.xaml.h"
#if __has_include("MainWindow.g.cpp")
#include "MainWindow.g.cpp"
#include "iostream"
#include <microsoft.ui.xaml.window.h>
#include <winrt/Windows.Foundation.Collections.h>
#include "winrt/Windows.Storage.Pickers.h"
#include <ShObjIdl_core.h>
#include <winrt/Windows.ApplicationModel.DataTransfer.h>
#include <thread>
#endif

using namespace winrt::Windows::Storage::Streams;

using namespace winrt;
using namespace Microsoft::UI::Xaml;
using namespace winrt::Windows::ApplicationModel::DataTransfer;

using namespace winrt::Windows::Storage;
using namespace winrt::Windows::Storage::Pickers;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::PC_Simulator_Save_Editor_for_Windows_10::implementation
{
    int32_t MainWindow::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void MainWindow::MyProperty(int32_t /* value */)
    {
        throw hresult_not_implemented();
    }



    void MainWindow::myButton_Click(IInspectable const&, RoutedEventArgs const&)
    {
        std::wstring result = L"";
        int key = 0x81;
        for (char16_t c : textbox().Text()) {
            result += (c ^ key);
        }
        textbox().Text(result);
    }

    void MainWindow::copy(IInspectable const&, Microsoft::UI::Xaml::RoutedEventArgs const&)
    {
        auto package = DataPackage();
        package.SetText(textbox().Text());
        Clipboard::SetContent(package);
        Clipboard::Flush();
    }

    HWND MainWindow::GetWindowHandleFromThis() {
        HWND hWnd{ 0 };
        auto windowNative{ this->try_as<::IWindowNative>() };
        winrt::check_bool(windowNative);
        winrt::check_hresult(windowNative->get_WindowHandle(&hWnd));
        return hWnd;
    }

    fire_and_forget MainWindow::saveFile_Click(IInspectable const&, RoutedEventArgs const&) {
        HWND hWnd = GetWindowHandleFromThis();
        assert(::IsWindow(hWnd) != 0);
        FileSavePicker openPicker = FileSavePicker();
        openPicker.as<IInitializeWithWindow>()->Initialize(hWnd);
        openPicker.SuggestedStartLocation(PickerLocationId::Downloads);
        auto saveExtension{winrt::single_threaded_vector<winrt::hstring>()};
        saveExtension.Append(L".pc");
        openPicker.FileTypeChoices().Insert(L"PC Simulator Save File (*.pc)", saveExtension);
        openPicker.SuggestedFileName();
        StorageFile file = co_await openPicker.PickSaveFileAsync();
        if (file != nullptr) {
            std::wstring result = L"";
            int key = 0x81;
            for (char16_t c : textbox().Text()) {
                result += (c ^ key);
            }
            co_await Windows::Storage::FileIO::WriteTextAsync(file, result);
        }
    }

    fire_and_forget MainWindow::openFile_Click(IInspectable const&, RoutedEventArgs const&) {
        HWND hWnd = GetWindowHandleFromThis();
        assert(::IsWindow(hWnd) != 0);
        FileOpenPicker openPicker = FileOpenPicker();
        openPicker.as<IInitializeWithWindow>()->Initialize(hWnd);
        openPicker.ViewMode(PickerViewMode::List);
        openPicker.SuggestedStartLocation(PickerLocationId::Downloads);
        openPicker.FileTypeFilter().Append(L".pc");
        StorageFile file = co_await openPicker.PickSingleFileAsync();
        if (file != nullptr) {
            winrt::hstring text = co_await Windows::Storage::FileIO::ReadTextAsync(file);
            std::wstring result = L"";
            int key = 0x81;
            for (char16_t c : text) {
                result += (c ^ key);
            }
            textbox().Text(result);
        }
    }
}

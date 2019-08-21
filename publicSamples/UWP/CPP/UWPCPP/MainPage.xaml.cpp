//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"
#include "MainPage.xaml.h"

using namespace UWPCPP;

using namespace concurrency;
using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;
using namespace Windows::Storage;

using namespace AdaptiveCards::Rendering::Uwp;

MainPage::MainPage()
{
	InitializeComponent();
}


void UWPCPP::MainPage::BrowseClicked(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
    auto picker = ref new Windows::Storage::Pickers::FileOpenPicker();
    picker->FileTypeFilter->Append(".json");
    auto filePickTask = create_task(picker->PickSingleFileAsync());

    filePickTask.then([this](StorageFile^ chosenFile)
        {
            fileToLoad->Text = chosenFile->Name;
        });
}


void UWPCPP::MainPage::FileToLoad_TextChanged(Platform::Object^ sender, Windows::UI::Xaml::Controls::TextChangedEventArgs^ e)
{

}


void UWPCPP::MainPage::LoadClicked(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
    auto fileTask = create_task(StorageFile::GetFileFromPathAsync(fileToLoad->Text));
    fileTask.then([this](StorageFile^ file) -> IAsyncOperation^
        {
            return FileIO::ReadTextAsync(file);
        }).then([this](String^ json)
            {
                auto renderer = ref new AdaptiveCardRenderer();
                auto renderedCard = renderer->RenderAdaptiveCardFromJsonString(json);
                //renderedCardGoesHere-
                //renderedCard->FrameworkElement
            });
}

//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"
#include "MainPage.xaml.h"

using namespace PerfApp;

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
using namespace AdaptiveCards::Rendering::Uwp;

// The Blank Page item template is documented at https://go.microsoft.com/fwlink/?LinkId=402352&clcid=0x409

MainPage::MainPage()
{
    AdaptiveTextBlock^ textBlock = ref new AdaptiveTextBlock();
    textBlock->Text = "This is some text";

    AdaptiveCard^ card = ref new AdaptiveCard();
    card->Body->Append(textBlock);

    AdaptiveCardRenderer^ renderer = ref new AdaptiveCardRenderer();
    RenderedAdaptiveCard^ renderedCard = renderer->RenderAdaptiveCard(card);

	InitializeComponent();
}

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
using namespace Windows::Storage;
using namespace Windows::Storage::Pickers;
using namespace Platform;
using namespace concurrency;
using namespace Windows::Data::Json;

// The Blank Page item template is documented at https://go.microsoft.com/fwlink/?LinkId=402352&clcid=0x409

task<void> MainPage::DoStuff()
{
	AdaptiveCardRenderer^ renderer = ref new AdaptiveCardRenderer();
	ULONGLONG totalParseTicks = 0, totalRenderTicks = 0, count = 0;


	FolderPicker^ folderPicker = ref new FolderPicker();
	folderPicker->FileTypeFilter->Append(".json");
	auto pickedFolder = co_await folderPicker->PickSingleFolderAsync();

	auto files = co_await pickedFolder->GetFilesAsync();

	for each(auto file in files)
	{
		String^ payload = co_await FileIO::ReadTextAsync(file);

		ULONGLONG startTicks = GetTickCount64();
		AdaptiveCardParseResult^ parseResult = AdaptiveCard::FromJsonString(payload);
		ULONGLONG parseEndTicks = GetTickCount64();

		RenderedAdaptiveCard^ renderedCard = renderer->RenderAdaptiveCard(parseResult->AdaptiveCard);
		ULONGLONG endTicks = GetTickCount64();

		ULONGLONG parseTicks = parseEndTicks - startTicks;
		ULONGLONG renderTicks = endTicks - parseEndTicks;
		ULONGLONG totalTicks = endTicks - startTicks;

		totalParseTicks += parseTicks;
		totalRenderTicks += renderTicks;
		count++;
	}

	ULONGLONG averageParseTicks = totalParseTicks / count;
	ULONGLONG averageRenderTicks = totalRenderTicks / count;

	double parsePercent = (double)totalParseTicks / ((double)totalParseTicks + (double)totalRenderTicks);
	double renderPercent = (double)totalRenderTicks / ((double)totalParseTicks + (double)totalRenderTicks);
	ULONG foo = 0;
}

MainPage::MainPage()
{
	InitializeComponent();

	DoStuff();
}

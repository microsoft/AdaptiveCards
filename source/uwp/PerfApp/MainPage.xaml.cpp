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

MainPage::MainPage()
{
	m_renderer = ref new AdaptiveCardRenderer();
	totalParseTicks = totalRenderTicks = count = 0;
	InitializeCriticalSection(&ticksCriticalSection);


	FolderPicker^ folderPicker = ref new FolderPicker();
	folderPicker->FileTypeFilter->Append(".json");

	auto pickFolderTask = create_task(folderPicker->PickSingleFolderAsync());
	pickFolderTask.then([&](StorageFolder^ pickedFolder) -> IAsyncOperation<IVectorView<StorageFile^>^>^
	{
		return pickedFolder->GetFilesAsync();
	}).then([&](IVectorView<StorageFile^>^ files)
	{
		for each(auto file in files)
		{
			create_task(FileIO::ReadTextAsync(file)).then([&](String^ payload)
			{
				ULONGLONG startTicks = GetTickCount64();
				AdaptiveCardParseResult^ parseResult = AdaptiveCard::FromJsonString(payload);
				ULONGLONG parseEndTicks = GetTickCount64();

				RenderedAdaptiveCard^ renderedCard = m_renderer->RenderAdaptiveCard(parseResult->AdaptiveCard);
				ULONGLONG endTicks = GetTickCount64();

				ULONGLONG parseTicks = parseEndTicks - startTicks;
				ULONGLONG renderTicks = endTicks - parseEndTicks;
				ULONGLONG totalTicks = endTicks - startTicks;

				{
					EnterCriticalSection(&ticksCriticalSection);
					totalParseTicks += parseTicks;
					totalRenderTicks += renderTicks;
					count++;
					LeaveCriticalSection(&ticksCriticalSection);
				}

				ULONGLONG averageParseTicks = totalParseTicks / count;
				ULONGLONG averageRenderTicks = totalRenderTicks / count;
			});
		}
	});

	//FileOpenPicker^ picker = ref new FileOpenPicker();
	//picker->FileTypeFilter->Append(".json");

	//auto pickFolderTask = create_task(picker->PickSingleFileAsync());
	//pickFolderTask.then([&](StorageFile^ pickedFile) -> IAsyncOperation<String^>^
	//{
	//	return FileIO::ReadTextAsync(pickedFile);
	//}).then([&](String^ payload) {

	//	AdaptiveCardRenderer^ renderer = ref new AdaptiveCardRenderer();
	//	RenderedAdaptiveCard^ renderedCard = renderer->RenderAdaptiveCardFromJsonString(payload);
	//});

    //AdaptiveTextBlock^ textBlock = ref new AdaptiveTextBlock();
    //textBlock->Text = "This is some text";

    //AdaptiveCard^ card = ref new AdaptiveCard();
    //card->Body->Append(textBlock);

    //AdaptiveCardRenderer^ renderer = ref new AdaptiveCardRenderer();
    //RenderedAdaptiveCard^ renderedCard = renderer->RenderAdaptiveCard(card);

	InitializeComponent();
}

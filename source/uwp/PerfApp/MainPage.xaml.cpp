//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"
#include "MainPage.xaml.h"
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <iostream> 
#include <sstream> 

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
using namespace Windows::Storage::Search;
using namespace Platform;
using namespace concurrency;
using namespace Windows::Data::Json;

// The Blank Page item template is documented at https://go.microsoft.com/fwlink/?LinkId=402352&clcid=0x409

ref class MyTextBlockRenderer sealed : public IAdaptiveElementRenderer 
{
public:
    MyTextBlockRenderer(MainPageViewModel^ viewModel)
    {
        m_viewModel = viewModel;
    }

    virtual Windows::UI::Xaml::UIElement^ Render(IAdaptiveCardElement^ element, AdaptiveRenderContext^ context, AdaptiveRenderArgs^ renderArgs)
    {
        AdaptiveTextBlockRenderer^ textBlockRenderer = ref new AdaptiveTextBlockRenderer();

        ULONGLONG startTextBlockTicks = GetTickCount64();
        Windows::UI::Xaml::UIElement^ object = textBlockRenderer->Render(element, context, renderArgs);
        ULONGLONG endTextBlockTicks = GetTickCount64();

        m_viewModel->AddTextBlockDataPoint(endTextBlockTicks - startTextBlockTicks);

        return object;
    }
private:
    MainPageViewModel ^ m_viewModel;
};


task<void> MainPage::RenderCards()
{
	runButton->IsEnabled = false;

    MyTextBlockRenderer^ myTextBlockRenderer = ref new MyTextBlockRenderer(m_viewModel);

	AdaptiveCardRenderer^ renderer = ref new AdaptiveCardRenderer();
    renderer->ElementRenderers->Set("TextBlock", myTextBlockRenderer);

	ULONGLONG totalParseTicks = 0, totalRenderTicks = 0, count = 0;

	UINT parseIterations;
	std::wstringstream parseIterationsStringStream(ParseIterations->Text->Data());
	parseIterationsStringStream >> parseIterations;

	UINT renderIterations;
	std::wstringstream renderIterationsStringStream(RenderIterations->Text->Data());
	renderIterationsStringStream >> renderIterations;

	FolderPicker^ folderPicker = ref new FolderPicker();
	folderPicker->FileTypeFilter->Append(".json");
	auto pickedFolder = co_await folderPicker->PickSingleFolderAsync();
	if (pickedFolder == nullptr)
	{
		runButton->IsEnabled = true;
		return;
	}

	auto files = co_await pickedFolder->GetFilesAsync(CommonFileQuery::OrderByName);

	for each(auto file in files)
	{
		String^ payload = co_await FileIO::ReadTextAsync(file);

		for (UINT iParse = 0; iParse < parseIterations; iParse++)
		{
			ULONGLONG startParseTicks = GetTickCount64();
			AdaptiveCardParseResult^ parseResult = AdaptiveCard::FromJsonString(payload);
			ULONGLONG endParseTicks = GetTickCount64();

			m_viewModel->AddParseDataPoint(file->Name, iParse, endParseTicks - startParseTicks);

			for (UINT iRender = 0; iRender < renderIterations; iRender++)
			{
				ULONGLONG startRenderTicks = GetTickCount64();
				RenderedAdaptiveCard^ renderedCard = renderer->RenderAdaptiveCard(parseResult->AdaptiveCard);
				ULONGLONG endRenderTicks = GetTickCount64();

				m_viewModel->AddRenderDataPoint(file->Name, iRender, endRenderTicks - startRenderTicks);
			}
		}
	}

	m_viewModel->DoneRunning();
	runButton->IsEnabled = true;
}

MainPage::MainPage()
{
	InitializeComponent();

	m_viewModel = ref new MainPageViewModel();
	DataContext = m_viewModel;
}

void PerfApp::MainPage::runButton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	RenderCards();
}


void PerfApp::MainPage::resetButton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	m_viewModel->Reset();
}

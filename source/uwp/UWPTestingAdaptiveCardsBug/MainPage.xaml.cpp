//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"
#include "MainPage.xaml.h"
#include <sstream>

using namespace UWPTestingAdaptiveCardsBug;

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
using namespace AdaptiveCards::ObjectModel::Uwp;
using namespace AdaptiveCards::Rendering::Uwp;

// The Blank Page item template is documented at https://go.microsoft.com/fwlink/?LinkId=402352&clcid=0x409

MainPage::MainPage()
{
	InitializeComponent();
}

void MainPage::ShowButton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	Platform::String^ cardJson = jsonInputBox->Text;

	if (cardJson == nullptr || cardJson->IsEmpty())
	{
		errorText->Text = "Please enter JSON";
		return;
	}

	errorText->Text = "";
	RenderAdaptiveCard(cardJson);
}

void MainPage::RenderAdaptiveCard(Platform::String^ jsonString)
{
	try
	{
		OutputDebugStringW(L"\n========== ADAPTIVE CARD RENDERING START ==========\n");

		// ========== STEP 1: PARSE JSON ==========
		// SET BREAKPOINT HERE to debug parsing
		errorText->Text = "Parsing JSON...";
		OutputDebugStringW(L"[DEBUG] Step 1: Parsing JSON...\n");

		auto parseResult = AdaptiveCard::FromJsonString(jsonString);
		OutputDebugStringW(L"[DEBUG] Parse completed\n");

		if (parseResult == nullptr)
		{
			OutputDebugStringW(L"[ERROR] Parse result is null\n");
			errorText->Text = "ERROR: Parse result is null";
			return;
		}

		if (parseResult->AdaptiveCard == nullptr)
		{
			OutputDebugStringW(L"[ERROR] Parsed card is null\n");
			errorText->Text = "ERROR: Parsed card is null";
			return;
		}

		OutputDebugStringW(L"[DEBUG] Parse successful\n");

		// Display any parse errors/warnings
		Platform::String^ errors = "";
		if (parseResult->Errors != nullptr && parseResult->Errors->Size > 0)
		{
			errors += "PARSE ERRORS:\n";
			for (auto error : parseResult->Errors)
			{
				errors += "  - " + error->Message + "\n";
			}
		}

		if (parseResult->Warnings != nullptr && parseResult->Warnings->Size > 0)
		{
			errors += "PARSE WARNINGS:\n";
			for (auto warning : parseResult->Warnings)
			{
				errors += "  - " + warning->Message + "\n";
			}
		}

		// ========== STEP 2: CREATE RENDERER ==========
		errorText->Text = "Creating renderer...";
		OutputDebugStringW(L"[DEBUG] Step 2: Creating renderer...\n");

		auto renderer = ref new AdaptiveCardRenderer();

		if (renderer == nullptr)
		{
			OutputDebugStringW(L"[ERROR] Renderer is null\n");
			errorText->Text = "ERROR: Renderer is null";
			return;
		}

		OutputDebugStringW(L"[DEBUG] Renderer created successfully\n");

		// ========== STEP 3: RENDER CARD ==========
		// SET BREAKPOINT HERE to debug rendering
		// Press F11 to step into the C++ renderer code
		errorText->Text = "Rendering card...";
		OutputDebugStringW(L"[DEBUG] Step 3: Rendering card...\n");
		OutputDebugStringW(L"[DEBUG] About to call RenderAdaptiveCard() - THIS IS WHERE IT MAY CRASH\n");

		RenderedAdaptiveCard^ renderedCard = nullptr;
		try
		{
			renderedCard = renderer->RenderAdaptiveCard(parseResult->AdaptiveCard);
			OutputDebugStringW(L"[DEBUG] RenderAdaptiveCard() returned successfully\n");
		}
		catch (Platform::Exception^ renderEx)
		{
			std::wstringstream ss;
			ss << L"[CRASH] Exception during RenderAdaptiveCard():\n";
			ss << L"  Message: " << renderEx->Message->Data() << L"\n";
			ss << L"  HRESULT: 0x" << std::hex << renderEx->HResult << L"\n";
			OutputDebugStringW(ss.str().c_str());

			errorText->Text = "CRASH during rendering:\n" + renderEx->Message + "\nHRESULT: 0x" + renderEx->HResult.ToString();
			errorText->Foreground = ref new SolidColorBrush(Windows::UI::Colors::Red);
			return;
		}

		if (renderedCard == nullptr)
		{
			OutputDebugStringW(L"[ERROR] Rendered card is null\n");
			errorText->Text = "ERROR: Rendered card is null";
			return;
		}

		OutputDebugStringW(L"[DEBUG] Rendered card object exists\n");

		// ========== STEP 4: CHECK FRAMEWORK ELEMENT ==========
		// THIS IS WHERE C# VISUALIZER FAILS
		// If FrameworkElement is null here, the rendering failed
		OutputDebugStringW(L"[DEBUG] Step 4: Checking FrameworkElement...\n");

		if (renderedCard->FrameworkElement == nullptr)
		{
			OutputDebugStringW(L"[ERROR] FrameworkElement is null!\n");
			errorText->Text = "ERROR: FrameworkElement is null!\n\n";
			errorText->Text += "This means rendering completed but produced no UI.\n\n";

			// Display render errors
			if (renderedCard->Errors != nullptr && renderedCard->Errors->Size > 0)
			{
				errorText->Text += "RENDER ERRORS:\n";
				for (auto error : renderedCard->Errors)
				{
					errorText->Text += "  - " + error->Message + "\n";
				}
			}

			if (renderedCard->Warnings != nullptr && renderedCard->Warnings->Size > 0)
			{
				errorText->Text += "\nRENDER WARNINGS:\n";
				for (auto warning : renderedCard->Warnings)
				{
					errorText->Text += "  - " + warning->Message + "\n";
				}
			}

			if (!errors->IsEmpty())
			{
				errorText->Text += "\n" + errors;
			}
			return;
		}

		// ========== STEP 5: DISPLAY CARD ==========
		OutputDebugStringW(L"[DEBUG] Step 5: Displaying card...\n");
		errorText->Text = "Success! Displaying card...";

		try
		{
			cardGrid->Children->Clear();
			OutputDebugStringW(L"[DEBUG] Cleared previous children\n");

			cardGrid->Children->Append(renderedCard->FrameworkElement);
			OutputDebugStringW(L"[DEBUG] Appended FrameworkElement to grid\n");
		}
		catch (Platform::Exception^ displayEx)
		{
			std::wstringstream ss;
			ss << L"[CRASH] Exception during display:\n";
			ss << L"  Message: " << displayEx->Message->Data() << L"\n";
			ss << L"  HRESULT: 0x" << std::hex << displayEx->HResult << L"\n";
			OutputDebugStringW(ss.str().c_str());

			errorText->Text = "CRASH during display:\n" + displayEx->Message;
			errorText->Foreground = ref new SolidColorBrush(Windows::UI::Colors::Red);
			return;
		}

		// Show any warnings if present
		if (renderedCard->Warnings != nullptr && renderedCard->Warnings->Size > 0)
		{
			errorText->Text = "WARNINGS:\n";
			for (auto warning : renderedCard->Warnings)
			{
				errorText->Text += "  - " + warning->Message + "\n";
			}
			errorText->Foreground = ref new SolidColorBrush(Windows::UI::Colors::Orange);
		}
		else if (!errors->IsEmpty())
		{
			errorText->Text = errors;
			errorText->Foreground = ref new SolidColorBrush(Windows::UI::Colors::Orange);
		}
		else
		{
			errorText->Text = "Card rendered successfully!";
			errorText->Foreground = ref new SolidColorBrush(Windows::UI::Colors::Green);
		}

		OutputDebugStringW(L"========== RENDERING COMPLETE ==========\n\n");
	}
	catch (Platform::Exception^ ex)
	{
		std::wstringstream ss;
		ss << L"[CRASH] Unhandled exception:\n";
		ss << L"  Message: " << ex->Message->Data() << L"\n";
		ss << L"  HRESULT: 0x" << std::hex << ex->HResult << L"\n";
		ss << L"  Stack trace may be available in debugger\n";
		OutputDebugStringW(ss.str().c_str());

		errorText->Text = "EXCEPTION:\n" + ex->Message + "\n\nHRESULT: 0x" + ex->HResult.ToString();
		errorText->Foreground = ref new SolidColorBrush(Windows::UI::Colors::Red);
	}
	catch (...)
	{
		OutputDebugStringW(L"[CRASH] Unknown exception (non-Platform::Exception)\n");
		errorText->Text = "CRASH: Unknown exception type";
		errorText->Foreground = ref new SolidColorBrush(Windows::UI::Colors::Red);
	}
}

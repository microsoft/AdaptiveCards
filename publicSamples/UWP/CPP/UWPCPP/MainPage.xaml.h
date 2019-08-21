//
// MainPage.xaml.h
// Declaration of the MainPage class.
//

#pragma once

#include "MainPage.g.h"

namespace UWPCPP
{
	/// <summary>
	/// An empty page that can be used on its own or navigated to within a Frame.
	/// </summary>
	public ref class MainPage sealed
	{
	public:
		MainPage();

    private:
        void BrowseClicked(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
        void FileToLoad_TextChanged(Platform::Object^ sender, Windows::UI::Xaml::Controls::TextChangedEventArgs^ e);
        void LoadClicked(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);

    };
}

// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
//
// MainPage.xaml.h
// Declaration of the MainPage class.
//

#pragma once

#include "MainPage.g.h"
#include "MainPageViewModel.h"

namespace PerfApp
{
    /// <summary>
    /// An empty page that can be used on its own or navigated to within a Frame.
    /// </summary>
    public ref class MainPage sealed
        {
        public:
        MainPage();

        property Platform::String^ CurrentFile
        {
            Platform::String^ get() { return m_currentFile; }
            void set(Platform::String^ currentFile) { m_currentFile = currentFile; }
        }

        private:
        concurrency::task<void> MainPage::RenderCards();

        MainPageViewModel^ m_viewModel;

        Platform::String^ m_currentFile;

        AdaptiveCards::Rendering::Uwp::AdaptiveCardRenderer ^ m_renderer;
        void runButton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
        void resetButton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
    };
}

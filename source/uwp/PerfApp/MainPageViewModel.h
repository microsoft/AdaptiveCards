// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "pch.h"

namespace PerfApp
{
    [Windows::UI::Xaml::Data::Bindable]
    public ref class MainPageViewModel sealed : public Windows::UI::Xaml::Data::INotifyPropertyChanged
    {
        public:
        MainPageViewModel() { Reset(); }

        property Platform::String^ CurrentFile
        {
            Platform::String^ get();
        }

        property Platform::String^ MaxParseFile
        {
            Platform::String^ get();
        }

        property Platform::String^ MaxRenderFile
        {
            Platform::String^ get();
        }

        property ULONGLONG AverageRenderTicks
        {
            ULONGLONG get();
        }

        property ULONGLONG AverageParseTicks
        {
            ULONGLONG get();
        }

        property UINT RenderPercentage
        {
            UINT get();
        }

        property UINT ParsePercentage
        {
            UINT get();
        }

        property ULONGLONG MaxRenderTicks
        {
            ULONGLONG get();
        }

        property ULONGLONG MaxParseTicks
        {
            ULONGLONG get();
        }

        property UINT CurrentParseIteration
        {
            UINT get();
        }

        property UINT CurrentRenderIteration
        {
            UINT get();
        }

        property ULONGLONG TotalRenderTicks
        {
            ULONGLONG get();
        }

        property ULONGLONG TotalTextBlockTicks
        {
            ULONGLONG get();
        }

        property ULONGLONG AverageTextBlockTicks
        {
            ULONGLONG get();
        }

        void AddParseDataPoint(Platform::String^ filename, UINT currentIteration, ULONGLONG parseTicks);
        void AddRenderDataPoint(Platform::String^ filename, UINT currentIteration, ULONGLONG renderTicks);
        void AddTextBlockDataPoint(ULONGLONG renderTicks);
        void Reset();
        void DoneRunning();

        virtual event Windows::UI::Xaml::Data::PropertyChangedEventHandler^ PropertyChanged;

    private:

        Platform::String^ m_currentFile;
        UINT m_currentParseIteration;
        UINT m_currentRenderIteration;

        Platform::String^ m_maxParseFile;
        Platform::String^ m_maxRenderFile;

        ULONG m_renderCount;
        ULONG m_parseCount;
        ULONG m_textBlockCount;

        ULONGLONG m_totalRenderTicks;
        ULONGLONG m_totalParseTicks;

        ULONGLONG m_maxRenderTicks;
        ULONGLONG m_maxParseTicks;

        ULONGLONG m_totalTextBlockTicks;

        void NotifyPropertyChanged(Platform::String^ prop);
    };
}

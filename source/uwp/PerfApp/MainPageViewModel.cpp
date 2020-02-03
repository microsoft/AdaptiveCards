// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "MainPageViewModel.h"

using namespace Platform;
using namespace Windows::UI::Xaml::Data;

namespace PerfApp
{
    void MainPageViewModel::Reset()
    {
        m_currentFile = nullptr;
        m_maxParseFile = nullptr;
        m_maxRenderFile = nullptr;

        m_renderCount = 0;
        m_parseCount = 0;
        m_totalRenderTicks = 0;
        m_totalParseTicks = 0;
        m_maxRenderTicks = 0;
        m_maxParseTicks = 0;
        m_currentParseIteration = 0;
        m_currentRenderIteration = 0;
        m_totalTextBlockTicks = 0;

        NotifyPropertyChanged(nullptr);
    }

    void MainPageViewModel::DoneRunning()
    {
        m_currentFile = nullptr;
        m_currentParseIteration = 0;
        m_currentRenderIteration = 0;

        NotifyPropertyChanged(nullptr);
    }

    void MainPageViewModel::AddParseDataPoint(String^ filename, UINT currentIteration, ULONGLONG parseTicks)
    {
        m_currentFile = filename;
        m_currentParseIteration = currentIteration;

        m_totalParseTicks += parseTicks;
        m_parseCount++;

            if (parseTicks > m_maxParseTicks )
            {
                m_maxParseTicks = parseTicks;
                m_maxParseFile = filename;
            }

        NotifyPropertyChanged(nullptr);
    }

    void MainPageViewModel::AddRenderDataPoint(String^ filename, UINT currentIteration, ULONGLONG renderTicks)
    {
        m_currentFile = filename;
        m_currentRenderIteration = currentIteration;

        m_totalRenderTicks += renderTicks;
        m_renderCount++;

            if (renderTicks > m_maxRenderTicks)
            {
                m_maxRenderTicks = renderTicks;
                m_maxRenderFile = filename;
            }

        NotifyPropertyChanged(nullptr);
    }

    void MainPageViewModel::AddTextBlockDataPoint(ULONGLONG renderTicks)
    {
        m_totalTextBlockTicks += renderTicks;
        m_textBlockCount++;

        ULONGLONG averageTextBlockTicks = m_totalTextBlockTicks / m_textBlockCount;
        averageTextBlockTicks++;
        NotifyPropertyChanged(nullptr);
    }

    void MainPageViewModel::NotifyPropertyChanged(String^ prop)
    {
        PropertyChangedEventArgs^ args = ref new PropertyChangedEventArgs(prop);
        PropertyChanged(this, args);
    }

    String^ MainPageViewModel::CurrentFile::get()
    {
        return m_currentFile;
    }

    String^ MainPageViewModel::MaxParseFile::get()
    {
        return m_maxParseFile;
    }

    String^ MainPageViewModel::MaxRenderFile::get()
    {
        return m_maxRenderFile;
    }

    ULONGLONG MainPageViewModel::MaxRenderTicks::get()
    {
        return m_maxRenderTicks;
    }

    ULONGLONG MainPageViewModel::MaxParseTicks::get()
    {
        return m_maxParseTicks;
    }

    ULONGLONG MainPageViewModel::AverageRenderTicks::get()
    {
        if (m_renderCount > 0)
            return m_totalRenderTicks / m_renderCount;
        else
            return 0;
    }

    ULONGLONG MainPageViewModel::AverageParseTicks::get()
    {
        if (m_parseCount > 0)
            return m_totalParseTicks / m_parseCount;
        else
            return 0;
    }

    UINT MainPageViewModel::RenderPercentage::get()
    {
        if (AverageParseTicks + AverageRenderTicks > 0)
            return (UINT)(((double)AverageRenderTicks / ((double)AverageParseTicks + (double)AverageRenderTicks)) * 100 + .5);
        else
            return 0;
    }

    UINT MainPageViewModel::ParsePercentage::get()
    {
        if (AverageParseTicks + AverageRenderTicks > 0)
            return (UINT)(((double)AverageParseTicks / ((double)AverageParseTicks + (double)AverageRenderTicks)) * 100 + .5);
        else
            return 0;
    }

    UINT MainPageViewModel::CurrentParseIteration::get()
    {
        return m_currentParseIteration;
    }

    UINT MainPageViewModel::CurrentRenderIteration::get()
    {
        return m_currentRenderIteration;
    }

    ULONGLONG MainPageViewModel::TotalRenderTicks::get()
    {
        return m_totalRenderTicks;
    }

    ULONGLONG MainPageViewModel::TotalTextBlockTicks::get()
    {
        return m_totalTextBlockTicks;
    }

    ULONGLONG MainPageViewModel::AverageTextBlockTicks::get()
    {
        if (m_textBlockCount > 0)
            return m_totalTextBlockTicks / m_textBlockCount;
        else
            return 0;
    }
}

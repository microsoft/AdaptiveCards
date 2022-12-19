// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
//
// App.xaml.h
// Declaration of the App class.
//

#pragma once

#include "App.g.h"

using namespace Windows::UI::Xaml::Navigation;

namespace PerfApp
{
    /// <summary>
    /// Provides application-specific behavior to supplement the default Application class.
    /// </summary>
    ref class App sealed
    {
    protected:
        virtual void OnLaunched(Windows::ApplicationModel::Activation::LaunchActivatedEventArgs^ e) override;

    internal:
        App();

    private:
        void OnSuspending(Platform::Object^ sender, Windows::ApplicationModel::SuspendingEventArgs^ e);
        void OnNavigationFailed(Platform::Object ^sender, NavigationFailedEventArgs ^e);
    };
}

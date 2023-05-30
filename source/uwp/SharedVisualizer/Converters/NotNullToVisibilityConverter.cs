// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System;
#if USE_WINUI3
using Microsoft.UI.Xaml;
using Microsoft.UI.Xaml.Data;
#else
using Windows.UI.Xaml;
using Windows.UI.Xaml.Data;
#endif

namespace AdaptiveCardVisualizer.Converters
{
    public class NotNullToVisibilityConverter : IValueConverter
    {
        public object Convert(object value, Type targetType, object parameter, string language)
        {
            return value != null ? Visibility.Visible : Visibility.Collapsed;
        }

        public object ConvertBack(object value, Type targetType, object parameter, string language)
        {
            throw new NotImplementedException();
        }
    }
}

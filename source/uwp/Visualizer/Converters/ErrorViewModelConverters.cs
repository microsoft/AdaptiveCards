// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Windows.UI;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Data;
using Windows.UI.Xaml.Media;
using AdaptiveCardVisualizer.ViewModel;

namespace AdaptiveCardVisualizer.Converters
{
    public class ErrorViewModelTypeToIconBackgroundConverter : IValueConverter
    {
        public object Convert(object value, Type targetType, object parameter, string language)
        {
            if (value is ErrorViewModelType)
            {
                switch ((ErrorViewModelType)value)
                {
                    case ErrorViewModelType.Error:
                    case ErrorViewModelType.ErrorButRenderAllowed:
                        return new SolidColorBrush(Colors.Red);

                    case ErrorViewModelType.Warning:
                        return new SolidColorBrush(Colors.Orange);

                    default:
                        throw new NotImplementedException();
                }
            }

            return value;
        }

        public object ConvertBack(object value, Type targetType, object parameter, string language)
        {
            throw new NotImplementedException();
        }
    }

    public sealed class ErrorViewModelTypeToIconForegroundConverter : IValueConverter
    {
        public object Convert(object value, Type targetType, object parameter, string language)
        {
            if (value is ErrorViewModelType)
            {
                switch ((ErrorViewModelType)value)
                {
                    case ErrorViewModelType.Error:
                    case ErrorViewModelType.ErrorButRenderAllowed:
                        return new SolidColorBrush(Colors.White);

                    case ErrorViewModelType.Warning:
                        return new SolidColorBrush(Colors.Black);

                    default:
                        throw new NotImplementedException();
                }
            }

            return value;
        }

        public object ConvertBack(object value, Type targetType, object parameter, string language)
        {
            throw new NotImplementedException();
        }
    }

    public sealed class ErrorViewModelTypeToSymbolConverter : IValueConverter
    {
        public object Convert(object value, Type targetType, object parameter, string language)
        {
            if (value is ErrorViewModelType)
            {
                switch ((ErrorViewModelType)value)
                {
                    case ErrorViewModelType.Error:
                    case ErrorViewModelType.ErrorButRenderAllowed:
                        return Symbol.Cancel;

                    case ErrorViewModelType.Warning:
                        return Symbol.Important;

                    default:
                        throw new NotImplementedException();
                }
            }

            return value;
        }

        public object ConvertBack(object value, Type targetType, object parameter, string language)
        {
            throw new NotImplementedException();
        }
    }
}

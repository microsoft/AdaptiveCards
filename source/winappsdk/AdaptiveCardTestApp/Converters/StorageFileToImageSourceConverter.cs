// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Windows.Storage;
using Windows.UI.Xaml.Data;
using Windows.UI.Xaml.Media.Imaging;

namespace AdaptiveCardTestApp.Converters
{
    public class StorageFileToImageSourceConverter : IValueConverter
    {
        public object Convert(object value, Type targetType, object parameter, string language)
        {
            if (value is StorageFile)
            {
                var file = value as StorageFile;

                BitmapImage bmp = new BitmapImage();
                LoadBitmap(bmp, file);
                return bmp;
            }

            return null;
        }

        private static async void LoadBitmap(BitmapImage img, StorageFile file)
        {
            try
            {
                await img.SetSourceAsync(await file.OpenAsync(FileAccessMode.Read));
            }
            catch { }
        }

        public object ConvertBack(object value, Type targetType, object parameter, string language)
        {
            throw new NotImplementedException();
        }
    }
}

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Windows.UI.Xaml.Data;

namespace UWPUITestApp
{
    public class InputValuePropertyNameConverter : IValueConverter
    {
        public object Convert(object value, Type targetType, object parameter, string language)
        {
            return value.ToString() + "_retrievedValue";
        }

        public object ConvertBack(object value, Type targetType, object parameter, string language)
        {
            throw new NotImplementedException();
        }
    }
}

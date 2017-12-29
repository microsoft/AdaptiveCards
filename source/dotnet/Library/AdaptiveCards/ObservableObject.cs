using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;

namespace AdaptiveCards
{
    public class ObservableObject : INotifyPropertyChanged
    {
        public event PropertyChangedEventHandler PropertyChanged;

        protected void FirePropertyChanged([CallerMemberName] string caller = "")
        {
            if (PropertyChanged != null)
                PropertyChanged(this, new PropertyChangedEventArgs(caller));
        }

        /// <summary>
        /// set the target to value if it is different and file Property Changed 
        /// </summary>
        /// <typeparam name="T"></typeparam>
        /// <param name="target"></param>
        /// <param name="value"></param>
        /// <param name="caller"></param>
        protected void SetPropertyValue<T>(ref T target, T value, [CallerMemberName] string caller = "")
        {
            if (target == null || !target.Equals(value))
            {
                target = value;
                if (PropertyChanged != null)
                    PropertyChanged(this, new PropertyChangedEventArgs(caller));
            }
        }
    }
}

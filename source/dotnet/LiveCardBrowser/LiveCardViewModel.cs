using LiveCardClient;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;

namespace LiveCardBrowser
{
    public class LiveCardViewModel : ObservableObject
    {

        private string url;
        public string Url { get { return url; } set { url = value; Notify(); } }


        private LiveCard liveCard;
        public LiveCard LiveCard
        {
            get { return liveCard; }
            set
            {
                liveCard = value; Notify();
            }
        }


        public FrameworkElement CardContent { get; set; }
    }
}

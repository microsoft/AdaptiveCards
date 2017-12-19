using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;

namespace LiveCardBrowser
{
    public class AppViewModel : ObservableObject
    {
        private LiveCardViewModel selectedCard;
        public LiveCardViewModel SelectedCard { get { return selectedCard; } set { selectedCard = value; Notify(); } }

        public ObservableCollection<LiveCardViewModel> Cards { get; set; } = new ObservableCollection<LiveCardViewModel>();
    }

}

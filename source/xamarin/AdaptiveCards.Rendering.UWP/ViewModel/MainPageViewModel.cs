using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using AdaptiveCards.Rendering.UWP.Helpers;

namespace AdaptiveCards.Rendering.UWP.ViewModel
{
    public class MainPageViewModel : BindableBase
    {

        private AdaptiveCardViewModel m_viewModel = null;
        public AdaptiveCardViewModel AdaptiveCard
        {
            get { return m_viewModel; }
            set
            {
                SetProperty(ref m_viewModel, value);

                if (value != null)
                {
                    value.ReloadIfNeeded();
                }
            }
        }

        public MainPageViewModel()
        {
            m_viewModel = new AdaptiveCardViewModel(this);

            this.AdaptiveCard = m_viewModel;
        }

    }
}

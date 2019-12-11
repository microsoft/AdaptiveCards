using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using AdaptiveCards.Rendering.Xamarin.Android.ObjectModel;
using AdaptiveCards.Rendering.Xamarin.Android.Renderer;
using AdaptiveCards.Rendering.Xamarin.Android.Renderer.ActionHandler;
using Android.App;
using Android.Content;
using Android.OS;
using Android.Runtime;
using Android.Views;
using Android.Widget;
using Android.Support.V4.App;

namespace AdaptiveCards.Rendering.Xamarin.Android.Sample
{
    class ShowCardFragment : global::Android.Support.V4.App.DialogFragment
    {

        public void initialize(Context _context, global::Android.Support.V4.App.FragmentManager _fragmentManager, ShowCardAction showCardAction, ICardActionHandler cardActionHandler, HostConfig hostConfig)
        {
            context = _context;
            fragmentManager = _fragmentManager;
            ShowCardAction = showCardAction;
            CardActionHandler = cardActionHandler;
            HostConfig = hostConfig;
        }

        public override View OnCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState)
        {
            Dialog.Window.SetSoftInputMode(SoftInput.AdjustResize);

            View v = inflater.Inflate(Resource.Layout.popup_fragment, container);

            RenderedAdaptiveCard renderedCard = AdaptiveCardRenderer.Instance.Render(context, fragmentManager, ShowCardAction.Card, CardActionHandler, HostConfig);

            ViewGroup viewGroup = (ViewGroup)renderedCard.View;
            Dialog.SetTitle(ShowCardAction.Title);

            ViewGroup insertPoint = (ViewGroup)v.FindViewById(Resource.Id.popup_fragment);
            insertPoint.AddView(viewGroup);
            v.Focusable = true;
            return v;
        }

        public override void OnResume()
        {
            base.OnResume();

            Dialog dialog = Dialog;
            if (dialog != null)
            {
                dialog.Window.SetLayout(ViewGroup.LayoutParams.MatchParent, ViewGroup.LayoutParams.WrapContent);
            }
        }

        private Context context;
        private global::Android.Support.V4.App.FragmentManager fragmentManager;
        private ShowCardAction ShowCardAction;
        private ICardActionHandler CardActionHandler;
        private HostConfig HostConfig;
    }
}

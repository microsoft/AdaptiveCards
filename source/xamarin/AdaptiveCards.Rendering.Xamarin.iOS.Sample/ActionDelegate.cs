using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using Foundation;
using UIKit;

using AdaptiveCards.Rendering.Xamarin.iOS;
using AdaptiveCards;
using SafariServices;
using iAd;

namespace AdaptiveCards.Rendering.Xamarin.iOS.Sample
{
    class ActionDelegate : ACRActionDelegate
    {
        public UIViewController ViewController { get; set; }

        public ActionDelegate(UIViewController viewController)
        {
            ViewController = viewController;
        }

        public override void DidFetchUserResponses(ACOAdaptiveCard card, ACOBaseActionElement action)
        {

            if (action.Type == ACRActionType.OpenUrl)
            {
                NSUrl url = new NSUrl(action.Url);
                SFSafariViewController safariViewController = new SFSafariViewController(url);
                ViewController.PresentViewController(safariViewController, animated: true, completionHandler: null);
            }
            else if (action.Type == ACRActionType.Submit)
            {
                NSData userInputsAsJson = card.InputsAsMap;
                NSString inputsAsString = new NSString(userInputsAsJson, NSStringEncoding.UTF8);

                UIAlertController alertController = new UIAlertController {
                    Title = "SubmitAction",
                    Message = inputsAsString
                };

                UIAlertAction alertAction = UIAlertAction.Create("Dismiss", UIAlertActionStyle.Default, handler: null);
                alertController.AddAction(alertAction);

                ViewController.PresentViewController(alertController, animated: true, completionHandler: null);
            }
            else if (action.Type == ACRActionType.UnknownAction)
            {

            }

        }

        public override void DidFetchSecondaryView(ACOAdaptiveCard card, UINavigationController naviationController) { }


    }
}

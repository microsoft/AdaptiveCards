
using System;
using System.Drawing;

using Foundation;
using UIKit;

using AdaptiveCards.BotConnection;
using AdaptiveCards;
using CoreGraphics;

namespace AdaptiveCards.Rendering.Xamarin.iOS.Sample
{
    public partial class ViewController : UIViewController
    {
        private ACOHostConfigParseResult Config = null;
        private PayloadRetriever PayloadRetriever = null;
        private UIView LastRenderedCard = null;
        private UIScrollView ScrollView = null;

        private ActionDelegate ActionDelegate;

        private UIButton LocalButton;
        private UIButton RemoteButton;

        string hostconfig = @"
        {
          ""spacing"": {
            ""small"": 3,
            ""default"": 8,
            ""medium"": 20,
            ""large"": 30,
            ""extraLarge"": 40,
            ""padding"": 20
          },
          ""separator"": {
            ""lineThickness"": 1,
            ""lineColor"": ""#EEEEEE""
          },
        ""supportsInteractivity"": true,
        ""fontFamily"": ""Segoe UI"",
        ""fontSizes"": {
           ""small"": 12,
           ""default"": 14,
           ""medium"": 17,
           ""large"": 21,
           ""extraLarge"": 26
          },
          ""fontWeights"": {
            ""lighter"": 200,
            ""default"": 400,
            ""bolder"": 600
          },
          ""containerStyles"": {
            ""default"": {
              ""backgroundColor"": ""#00000000"",
              ""fontColors"": {
                ""default"": {
                  ""normal"": ""#333333"",
                  ""subtle"": ""#EE333333""
                },
                ""accent"": {
                  ""normal"": ""#2E89FC"",
                  ""subtle"": ""#882E89FC""
                },
                ""attention"": {
                  ""normal"": ""#cc3300"",
                  ""subtle"": ""#DDcc3300""
                },
                ""good"": {
                  ""normal"": ""#54a254"",
                  ""subtle"": ""#DD54a254""
                },
                ""warning"": {
                  ""normal"": ""#e69500"",
                  ""subtle"": ""#DDe69500""
                }
              }
            },
            ""emphasis"": {
              ""backgroundColor"": ""#08000000"",
              ""fontColors"": {
                ""default"": {
                  ""normal"": ""#333333"",
                  ""subtle"": ""#EE333333""
                },
                ""accent"": {
                  ""normal"": ""#2E89FC"",
                  ""subtle"": ""#882E89FC""
                },
                ""attention"": {
                  ""normal"": ""#cc3300"",
                  ""subtle"": ""#DDcc3300""
                },
                ""good"": {
                  ""normal"": ""#54a254"",
                  ""subtle"": ""#DD54a254""
                },
                ""warning"": {
                  ""normal"": ""#e69500"",
                  ""subtle"": ""#DDe69500""
                }
              }
            }
          },
          ""imageSizes"": {
            ""small"": 50,
            ""medium"": 80,
            ""large"": 120
          },
          ""actions"": {
            ""maxActions"": 5,
            ""spacing"": ""default"",
            ""buttonSpacing"": 10,
            ""showCard"": {
              ""actionMode"": ""inline"",
              ""inlineTopMargin"": 16
            },
            ""actionsOrientation"": ""horizontal"",
            ""actionAlignment"": ""stretch""
          },
          ""adaptiveCard"": {
            ""allowCustomStyle"": false
          },
          ""image"": {
            ""size"": ""medium""
          },
          ""imageSet"": {
            ""imageSize"": ""medium"",
            ""maxImageHeight"": 100
          },
          ""factSet"": {
            ""title"": {
              ""color"": ""default"",
              ""size"": ""default"",
              ""isSubtle"": false,
              ""weight"": ""bolder"",
              ""wrap"": true,
              ""maxWidth"": 150
            },
            ""value"": {
              ""color"": ""default"",
              ""size"": ""default"",
              ""isSubtle"": false,
              ""weight"": ""default"",
              ""wrap"": true
            },
            ""spacing"": 10
          }
        }";


        public ViewController(IntPtr handle) : base(handle)
        {
        }

        public ViewController() : base()
        {
        }

        private UIView ReGenerateAdaptiveCard(string json)
        {
            var retrievedCard = ACOAdaptiveCard.FromJson(json);

            if (retrievedCard.IsValid == true)
            {
                nfloat adaptiveCardsWidth = 330;

                var renderResult = ACRRenderer.Render(retrievedCard.Card,
                                                      Config.Config,
                                                      adaptiveCardsWidth,
                                                      ActionDelegate);
                // actionDelegate.LabelContainer = renderResult.View;
                // actionDelegate.ResponseLabel = null;
                return renderResult.View;
            }
            return null;
        }

        private void RenderAdaptiveCard(string cardToRender, UIViewController controller)
        {
            var renderedCard = ReGenerateAdaptiveCard(cardToRender);
            if (LastRenderedCard != null)
            {
                LastRenderedCard.RemoveFromSuperview();
            }

            if (renderedCard != null)
            {
                ScrollView.AddSubview(renderedCard);

                renderedCard.TranslatesAutoresizingMaskIntoConstraints = false;

                NSLayoutConstraint.Create(renderedCard,
                                         NSLayoutAttribute.Top,
                                         NSLayoutRelation.Equal,
                                         ScrollView,
                                         NSLayoutAttribute.Top,
                                         multiplier: (nfloat)1.0,
                                         constant: 0).Active = true;

                NSLayoutConstraint.Create(renderedCard,
                                          NSLayoutAttribute.Bottom,
                                          NSLayoutRelation.Equal,
                                          ScrollView,
                                          NSLayoutAttribute.Bottom,
                                          multiplier: (nfloat)1.0,
                                          constant: 0).Active = true;

                NSLayoutConstraint.Create(renderedCard,
                                          NSLayoutAttribute.CenterX,
                                          NSLayoutRelation.Equal,
                                          ScrollView,
                                          NSLayoutAttribute.CenterX,
                                          multiplier: (nfloat)1.0,
                                          constant: 3).Active = true;

                NSLayoutConstraint.ActivateConstraints(new NSLayoutConstraint[] {
                    renderedCard.LeadingAnchor.ConstraintEqualTo(ScrollView.LeadingAnchor),
                    renderedCard.TrailingAnchor.ConstraintEqualTo(ScrollView.TrailingAnchor)
                });

                LastRenderedCard = renderedCard;
            }
        }

        public override void ViewDidLoad()
        {
            base.ViewDidLoad();

            RegisterForKeyboardNotifications();

            ActionDelegate = new ActionDelegate(this);

            Config = ACOHostConfig.FromJson(hostconfig);
            PayloadRetriever = new PayloadRetriever();

            // Add button
            LocalButton = UIButton.FromType(UIButtonType.System);
            LocalButton.Frame = new CoreGraphics.CGRect(UIScreen.MainScreen.Bounds.Size.Width * 0.1f,
                                                        UIScreen.MainScreen.Bounds.Size.Height * 0.05f,
                                                        UIScreen.MainScreen.Bounds.Size.Width * 0.9f,
                                                        UIScreen.MainScreen.Bounds.Size.Height * 0.05f);
            LocalButton.SetTitle("Local", UIControlState.Normal);
            LocalButton.TouchUpInside += (sender, e) =>
            {
                RenderAdaptiveCard(PayloadRetriever.RequestLocalAdaptiveCard(), this);
            };
            View.AddSubview(LocalButton);

            RemoteButton = UIButton.FromType(UIButtonType.System);
            RemoteButton.Frame = new CoreGraphics.CGRect(UIScreen.MainScreen.Bounds.Size.Width * 0.1f,
                                                         UIScreen.MainScreen.Bounds.Size.Height * 0.1f,
                                                         UIScreen.MainScreen.Bounds.Size.Width * 0.9f,
                                                         UIScreen.MainScreen.Bounds.Size.Height * 0.05f);
            RemoteButton.SetTitle("remote", UIControlState.Normal);
            RemoteButton.TouchUpInside += async (sender, e) =>
            {
                RenderAdaptiveCard(await PayloadRetriever.RequestRemoteAdaptiveCard(), this);
            };
            View.AddSubview(RemoteButton);

            ScrollView = new UIScrollView()
            {
                ShowsHorizontalScrollIndicator = false,
                ShowsVerticalScrollIndicator = true,
                ScrollEnabled = true,
                TranslatesAutoresizingMaskIntoConstraints = false
            };

            View.AddSubview(ScrollView);

            ActionDelegate.ScrollView = ScrollView;

            NSDictionary viewMap = new NSDictionary(
                "LocalButton", LocalButton,
                "RemoteButton", RemoteButton,
                "ScrollView", ScrollView);

            NSArray<NSString> formats = NSArray<NSString>.FromNSObjects(
                new NSString("V:|-70-[LocalButton]-[RemoteButton]-[ScrollView]-40@100-|"),
                new NSString("H:|-[ScrollView]-|"));

            NSLayoutConstraint[] constraints = null;

            foreach (NSString format in formats)
            {
                constraints = NSLayoutConstraint.FromVisualFormat(format, 0, null, viewMap);
                NSLayoutConstraint.ActivateConstraints(constraints);
            }
        }

        public override void ViewWillAppear(bool animated)
        {
            base.ViewWillAppear(animated);
        }

        public override void DidReceiveMemoryWarning()
        {
            // Releases the view if it doesn't have a superview.
            base.DidReceiveMemoryWarning();

            // Release any cached data, images, etc that aren't in use.
        }

        private void RegisterForKeyboardNotifications()
        {
            // NSNotificationCenter.DefaultCenter.AddObserver(this, new ObjCRuntime.Selector("KeyboardWasShown:"), UIKeyboard.WillShowNotification, null);
            // NSNotificationCenter.DefaultCenter.AddObserver(this, new ObjCRuntime.Selector("KeyboardWillBeHidden:"), UIKeyboard.WillHideNotification, null);
        }

        [Export("KeyboardWasShown:")]
        public void KeyboardWasShown(NSNotification notification)
        {
            /*
            NSDictionary info = notification.UserInfo;
            CGRect kbFrame = ((NSValue)info.ObjectForKey(UIKeyboard.FrameEndUserInfoKey)).CGRectValue;
            CGSize kbSize = kbFrame.Size;

            UIEdgeInsets contentInsets = new UIEdgeInsets((nfloat)0.0, (nfloat)0.0, kbSize.Height, (nfloat)0.0);
            CGRect scrollViewFrame = ScrollView.Frame;
            if (scrollViewFrame.Bottom + scrollViewFrame.Size.Height > kbFrame.Bottom)
            {
                ScrollView.ContentInset = contentInsets;
                ScrollView.ScrollIndicatorInsets = contentInsets;
            }
            */
        }

        [Export("KeyboardWillBeHidden:")]
        public void KeyboardWillBeHidden(NSNotification notification)
        {
            UIEdgeInsets contentInsets = UIEdgeInsets.Zero;
            ScrollView.ContentInset = contentInsets;
            ScrollView.ScrollIndicatorInsets = contentInsets;
        }
    }
}

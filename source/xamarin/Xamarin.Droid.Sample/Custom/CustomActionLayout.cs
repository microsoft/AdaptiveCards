using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using AdaptiveCards.Rendering.Xamarin.Android.ObjectModel;
using AdaptiveCards.Rendering.Xamarin.Android.Renderer;
using AdaptiveCards.Rendering.Xamarin.Android.Renderer.ActionHandler;
using AdaptiveCards.Rendering.Xamarin.Android.Renderer.Registration;
using Android.App;
using Android.Content;
using Android.OS;
using Android.Runtime;
using Android.Support.V4.App;
using Android.Views;
using Android.Widget;
using Java.Lang;

namespace AdaptiveCards.Rendering.Xamarin.Android.Sample.Custom
{
    class CustomActionLayout : Java.Lang.Object, IActionLayoutRenderer
    {
        public View RenderActions(RenderedAdaptiveCard renderedCard, Context context, global::Android.Support.V4.App.FragmentManager p2, ViewGroup viewGroup, BaseActionElementVector baseActionElementList, ICardActionHandler p5, HostConfig hostConfig, RenderArgs renderArgs)
        {
            long size;

            if (baseActionElementList == null || (size = baseActionElementList.Size()) <= 0)
            {
                return null;
            }

            LinearLayout actionsLayout = new LinearLayout(context);
            actionsLayout.LayoutParameters = new LinearLayout.LayoutParams(ViewGroup.LayoutParams.MatchParent, ViewGroup.LayoutParams.WrapContent);
            ActionAlignment actionAlignment = hostConfig.Actions.ActionAlignment;

            GravityFlags nativeAlignment = GravityFlags.Start | GravityFlags.Top;
            if (actionAlignment == ActionAlignment.Right)
            {
                nativeAlignment = GravityFlags.Right;
            }
            else if (actionAlignment == ActionAlignment.Center)
            {
                nativeAlignment = GravityFlags.CenterHorizontal;
            }

            actionsLayout.SetGravity(nativeAlignment);
            actionsLayout.SetBackgroundColor(global::Android.Graphics.Color.AliceBlue);

            ActionsOrientation orientation = hostConfig.Actions.ActionsOrientation;
            if (orientation == ActionsOrientation.Vertical)
            {
                actionsLayout.Orientation = Orientation.Vertical;
            }
            else
            {
                actionsLayout.Orientation = Orientation.Horizontal;
            }

            Spacing spacing = hostConfig.Actions.Spacing;
            // Passing false for separator since we do not have any configuration for separator in actionsConfig 
            // BaseCardElementRenderer.setSpacingAndSeparator(context, viewGroup, spacing, false, hostConfig, true * Horizontal Line *);

            if (viewGroup != null)
            {
                if (orientation == ActionsOrientation.Horizontal)
                {
                    HorizontalScrollView actionButtonsContainer = new HorizontalScrollView(context);
                    // Make elements alignment works when not enough space to make them scroll
                    LinearLayout.LayoutParams layoutParams = new LinearLayout.LayoutParams(ViewGroup.LayoutParams.WrapContent, ViewGroup.LayoutParams.WrapContent);
                    layoutParams.Gravity = nativeAlignment;
                    actionButtonsContainer.LayoutParameters = layoutParams;

                    actionButtonsContainer.HorizontalScrollBarEnabled = false;
                    actionButtonsContainer.AddView(actionsLayout);
                    viewGroup.AddView(actionButtonsContainer);
                }
                else
                {
                    viewGroup.AddView(actionsLayout);
                }
            }

            int i = 0;
            long maxActions = hostConfig.Actions.MaxActions;

            // Allow the actions to have the icon drawn at the top as long as all actions have an icon
            renderArgs.AllowAboveTitleIconPlacement = true;
            for (; i < size && i < maxActions; ++i)
            {
                BaseActionElement actionElement = (BaseActionElement)baseActionElementList.Get(i);
                if (System.String.IsNullOrWhiteSpace(actionElement.IconUrl))
                {
                    renderArgs.AllowAboveTitleIconPlacement = false;
                    break;
                }
            }

            if (i >= maxActions && size != maxActions)
            {
                renderedCard.AddWarning(new AdaptiveWarning(AdaptiveWarning.MaxActionsExceeded, "A maximum of " + maxActions + " actions are allowed"));
            }

            FeatureRegistration featureRegistration = CardRendererRegistration.Instance.FeatureRegistration;
            for (i = 0; i < size && i < maxActions; i++)
            {
                BaseActionElement actionElement = (BaseActionElement)baseActionElementList.Get(i);

                IBaseActionElementRenderer actionRenderer = CardRendererRegistration.Instance.GetActionRenderer(actionElement.ElementTypeString);

                try
                {
                    if (actionRenderer == null)
                    {
                        throw new AdaptiveFallbackException(actionElement);
                    }

                    if ((featureRegistration != null) && (!actionElement.MeetsRequirements(featureRegistration)))
                    {
                        throw new AdaptiveFallbackException(actionElement, featureRegistration);
                    }

                    actionRenderer.Render(renderedCard, context, p2, actionsLayout, actionElement, p5, hostConfig, renderArgs);
                }
                catch (AdaptiveFallbackException e)
                {
                    bool elementHasFallback = (actionElement.FallbackType != FallbackType.None);

                    if (elementHasFallback)
                    {
                        if (actionElement.FallbackType == FallbackType.Content)
                        {
                            BaseElement fallbackElement = actionElement.FallbackContent;

                            while (fallbackElement != null)
                            {
                                try
                                {
                                    BaseActionElement fallbackActionElement = null;
                                    if (fallbackElement is BaseActionElement)
                                    {
                                        fallbackActionElement = (BaseActionElement)fallbackElement;
                                    }
                                    else if ((fallbackActionElement = BaseActionElement.Dynamic_cast(fallbackElement)) == null)
                                    {
                                        throw new InternalError("Unable to convert BaseElement to BaseActionElement object model.");
                                    }

                                    IBaseActionElementRenderer fallbackActionRenderer = CardRendererRegistration.Instance.GetActionRenderer(fallbackActionElement.ElementTypeString);

                                    if (fallbackActionRenderer == null)
                                    {
                                        throw new AdaptiveFallbackException(fallbackElement);
                                    }

                                    if ((featureRegistration != null) && (!fallbackElement.MeetsRequirements(featureRegistration)))
                                    {
                                        throw new AdaptiveFallbackException(fallbackElement, featureRegistration);
                                    }

                                    fallbackActionRenderer.Render(renderedCard, context, p2, actionsLayout, fallbackActionElement, p5, hostConfig, renderArgs);
                                    break;
                                }
                                catch (AdaptiveFallbackException e2)
                                {
                                    // As the fallback element didn't exist, go back to trying
                                    if (fallbackElement.FallbackType == FallbackType.Content)
                                    {
                                        fallbackElement = fallbackElement.FallbackContent;
                                    }
                                    else
                                    {
                                        // The element has no fallback, just clear the element so the cycle ends
                                        fallbackElement = null;
                                    }
                                }
                            }
                        }
                    }
                    else if (renderArgs.AncestorHasFallback)
                    {
                        // There's an ancestor with fallback so we throw to trigger it
                        throw e;
                    }
                    else
                    {
                        renderedCard.AddWarning(new AdaptiveWarning(AdaptiveWarning.UnknownElementType, "Unsupported card element type: " + actionElement.ElementTypeString));
                        continue;
                    }
                }
            }

            return actionsLayout;
        }
    }
}

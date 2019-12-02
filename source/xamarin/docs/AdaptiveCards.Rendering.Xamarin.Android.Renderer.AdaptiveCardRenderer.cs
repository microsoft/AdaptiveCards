using System;
using System.Collections.Generic;
using Android.Runtime;
using Java.Interop;

namespace AdaptiveCards.Rendering.Xamarin.Android.Renderer {

	// Metadata.xml XPath class reference: path="/api/package[@name='io.adaptivecards.renderer']/class[@name='AdaptiveCardRenderer']"
	[global::Android.Runtime.Register ("io/adaptivecards/renderer/AdaptiveCardRenderer", DoNotGenerateAcw=true)]
	public partial class AdaptiveCardRenderer : global::Java.Lang.Object {

		public static unsafe global::AdaptiveCards.Rendering.Xamarin.Android.Renderer.AdaptiveCardRenderer Instance {

		// Metadata.xml XPath method reference: path="/api/package[@name='io.adaptivecards.renderer']/class[@name='AdaptiveCardRenderer']/method[@name='render' and count(parameter)=4 and parameter[1][@type='android.content.Context'] and parameter[2][@type='android.support.v4.app.FragmentManager'] and parameter[3][@type='io.adaptivecards.objectmodel.AdaptiveCard'] and parameter[4][@type='io.adaptivecards.renderer.actionhandler.ICardActionHandler']]"
		[Register ("render", "(Landroid/content/Context;Landroid/support/v4/app/FragmentManager;Lio/adaptivecards/objectmodel/AdaptiveCard;Lio/adaptivecards/renderer/actionhandler/ICardActionHandler;)Lio/adaptivecards/renderer/RenderedAdaptiveCard;", "GetRender_Landroid_content_Context_Landroid_support_v4_app_FragmentManager_Lio_adaptivecards_objectmodel_AdaptiveCard_Lio_adaptivecards_renderer_actionhandler_ICardActionHandler_Handler")]
		public virtual unsafe global::AdaptiveCards.Rendering.Xamarin.Android.Renderer.RenderedAdaptiveCard Render (global::Android.Content.Context context, global::Android.Support.V4.App.FragmentManager fragmentManager, global::AdaptiveCards.Rendering.Xamarin.Android.ObjectModel.AdaptiveCard adaptiveCard, global::AdaptiveCards.Rendering.Xamarin.Android.Renderer.ActionHandler.ICardActionHandler cardActionHandler)

		// Metadata.xml XPath method reference: path="/api/package[@name='io.adaptivecards.renderer']/class[@name='AdaptiveCardRenderer']/method[@name='render' and count(parameter)=5 and parameter[1][@type='android.content.Context'] and parameter[2][@type='android.support.v4.app.FragmentManager'] and parameter[3][@type='io.adaptivecards.objectmodel.AdaptiveCard'] and parameter[4][@type='io.adaptivecards.renderer.actionhandler.ICardActionHandler'] and parameter[5][@type='io.adaptivecards.objectmodel.HostConfig']]"
		[Register ("render", "(Landroid/content/Context;Landroid/support/v4/app/FragmentManager;Lio/adaptivecards/objectmodel/AdaptiveCard;Lio/adaptivecards/renderer/actionhandler/ICardActionHandler;Lio/adaptivecards/objectmodel/HostConfig;)Lio/adaptivecards/renderer/RenderedAdaptiveCard;", "GetRender_Landroid_content_Context_Landroid_support_v4_app_FragmentManager_Lio_adaptivecards_objectmodel_AdaptiveCard_Lio_adaptivecards_renderer_actionhandler_ICardActionHandler_Lio_adaptivecards_objectmodel_HostConfig_Handler")]
		public virtual unsafe global::AdaptiveCards.Rendering.Xamarin.Android.Renderer.RenderedAdaptiveCard Render (global::Android.Content.Context context, global::Android.Support.V4.App.FragmentManager fragmentManager, global::AdaptiveCards.Rendering.Xamarin.Android.ObjectModel.AdaptiveCard adaptiveCard, global::AdaptiveCards.Rendering.Xamarin.Android.Renderer.ActionHandler.ICardActionHandler cardActionHandler, global::AdaptiveCards.Rendering.Xamarin.Android.ObjectModel.HostConfig hostConfig)

	}
}

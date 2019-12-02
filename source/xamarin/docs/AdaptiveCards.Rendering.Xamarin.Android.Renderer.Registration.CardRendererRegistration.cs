using System;
using System.Collections.Generic;
using Android.Runtime;
using Java.Interop;

namespace AdaptiveCards.Rendering.Xamarin.Android.Renderer.Registration {

	// Metadata.xml XPath class reference: path="/api/package[@name='io.adaptivecards.renderer.registration']/class[@name='CardRendererRegistration']"
	[global::Android.Runtime.Register ("io/adaptivecards/renderer/registration/CardRendererRegistration", DoNotGenerateAcw=true)]
	public partial class CardRendererRegistration : global::Java.Lang.Object {

		public virtual unsafe global::AdaptiveCards.Rendering.Xamarin.Android.ObjectModel.FeatureRegistration FeatureRegistration

		public static unsafe global::AdaptiveCards.Rendering.Xamarin.Android.Renderer.Registration.CardRendererRegistration Instance

		// Metadata.xml XPath method reference: path="/api/package[@name='io.adaptivecards.renderer.registration']/class[@name='CardRendererRegistration']/method[@name='notifyInputChange' and count(parameter)=2 and parameter[1][@type='java.lang.String'] and parameter[2][@type='java.lang.String']]"
		[Register ("notifyInputChange", "(Ljava/lang/String;Ljava/lang/String;)V", "GetNotifyInputChange_Ljava_lang_String_Ljava_lang_String_Handler")]
		public virtual unsafe void NotifyInputChange (string id, string value)

		// Metadata.xml XPath method reference: path="/api/package[@name='io.adaptivecards.renderer.registration']/class[@name='CardRendererRegistration']/method[@name='registerFeatureRegistration' and count(parameter)=1 and parameter[1][@type='io.adaptivecards.objectmodel.FeatureRegistration']]"
		[Register ("registerFeatureRegistration", "(Lio/adaptivecards/objectmodel/FeatureRegistration;)V", "GetRegisterFeatureRegistration_Lio_adaptivecards_objectmodel_FeatureRegistration_Handler")]
		public virtual unsafe void RegisterFeatureRegistration (global::AdaptiveCards.Rendering.Xamarin.Android.ObjectModel.FeatureRegistration featureRegistration)

		// Metadata.xml XPath method reference: path="/api/package[@name='io.adaptivecards.renderer.registration']/class[@name='CardRendererRegistration']/method[@name='render' and count(parameter)=9 and parameter[1][@type='io.adaptivecards.renderer.RenderedAdaptiveCard'] and parameter[2][@type='android.content.Context'] and parameter[3][@type='android.support.v4.app.FragmentManager'] and parameter[4][@type='android.view.ViewGroup'] and parameter[5][@type='java.lang.Object'] and parameter[6][@type='io.adaptivecards.objectmodel.BaseCardElementVector'] and parameter[7][@type='io.adaptivecards.renderer.actionhandler.ICardActionHandler'] and parameter[8][@type='io.adaptivecards.objectmodel.HostConfig'] and parameter[9][@type='io.adaptivecards.renderer.RenderArgs']]"
		[Register ("render", "(Lio/adaptivecards/renderer/RenderedAdaptiveCard;Landroid/content/Context;Landroid/support/v4/app/FragmentManager;Landroid/view/ViewGroup;Ljava/lang/Object;Lio/adaptivecards/objectmodel/BaseCardElementVector;Lio/adaptivecards/renderer/actionhandler/ICardActionHandler;Lio/adaptivecards/objectmodel/HostConfig;Lio/adaptivecards/renderer/RenderArgs;)Landroid/view/View;", "GetRender_Lio_adaptivecards_renderer_RenderedAdaptiveCard_Landroid_content_Context_Landroid_support_v4_app_FragmentManager_Landroid_view_ViewGroup_Ljava_lang_Object_Lio_adaptivecards_objectmodel_BaseCardElementVector_Lio_adaptivecards_renderer_actionhandler_ICardActionHandler_Lio_adaptivecards_objectmodel_HostConfig_Lio_adaptivecards_renderer_RenderArgs_Handler")]
		public virtual unsafe global::Android.Views.View Render (global::AdaptiveCards.Rendering.Xamarin.Android.Renderer.RenderedAdaptiveCard renderedCard, global::Android.Content.Context context, global::Android.Support.V4.App.FragmentManager fragmentManager, global::Android.Views.ViewGroup viewGroup, global::Java.Lang.Object tag, global::AdaptiveCards.Rendering.Xamarin.Android.ObjectModel.BaseCardElementVector baseCardElementList, global::AdaptiveCards.Rendering.Xamarin.Android.Renderer.ActionHandler.ICardActionHandler cardActionHandler, global::AdaptiveCards.Rendering.Xamarin.Android.ObjectModel.HostConfig hostConfig, global::AdaptiveCards.Rendering.Xamarin.Android.Renderer.RenderArgs renderArgs)

		// Metadata.xml XPath method reference: path="/api/package[@name='io.adaptivecards.renderer.registration']/class[@name='CardRendererRegistration']/method[@name='renderElementAndPerformFallback' and count(parameter)=9 and parameter[1][@type='io.adaptivecards.renderer.RenderedAdaptiveCard'] and parameter[2][@type='android.content.Context'] and parameter[3][@type='android.support.v4.app.FragmentManager'] and parameter[4][@type='io.adaptivecards.objectmodel.BaseCardElement'] and parameter[5][@type='android.view.ViewGroup'] and parameter[6][@type='io.adaptivecards.renderer.actionhandler.ICardActionHandler'] and parameter[7][@type='io.adaptivecards.objectmodel.HostConfig'] and parameter[8][@type='io.adaptivecards.renderer.RenderArgs'] and parameter[9][@type='io.adaptivecards.objectmodel.FeatureRegistration']]"
		[Register ("renderElementAndPerformFallback", "(Lio/adaptivecards/renderer/RenderedAdaptiveCard;Landroid/content/Context;Landroid/support/v4/app/FragmentManager;Lio/adaptivecards/objectmodel/BaseCardElement;Landroid/view/ViewGroup;Lio/adaptivecards/renderer/actionhandler/ICardActionHandler;Lio/adaptivecards/objectmodel/HostConfig;Lio/adaptivecards/renderer/RenderArgs;Lio/adaptivecards/objectmodel/FeatureRegistration;)V", "GetRenderElementAndPerformFallback_Lio_adaptivecards_renderer_RenderedAdaptiveCard_Landroid_content_Context_Landroid_support_v4_app_FragmentManager_Lio_adaptivecards_objectmodel_BaseCardElement_Landroid_view_ViewGroup_Lio_adaptivecards_renderer_actionhandler_ICardActionHandler_Lio_adaptivecards_objectmodel_HostConfig_Lio_adaptivecards_renderer_RenderArgs_Lio_adaptivecards_objectmodel_FeatureRegistration_Handler")]
		public virtual unsafe void RenderElementAndPerformFallback (global::AdaptiveCards.Rendering.Xamarin.Android.Renderer.RenderedAdaptiveCard renderedCard, global::Android.Content.Context context, global::Android.Support.V4.App.FragmentManager fragmentManager, global::AdaptiveCards.Rendering.Xamarin.Android.ObjectModel.BaseCardElement cardElement, global::Android.Views.ViewGroup viewGroup, global::AdaptiveCards.Rendering.Xamarin.Android.Renderer.ActionHandler.ICardActionHandler cardActionHandler, global::AdaptiveCards.Rendering.Xamarin.Android.ObjectModel.HostConfig hostConfig, global::AdaptiveCards.Rendering.Xamarin.Android.Renderer.RenderArgs renderArgs, global::AdaptiveCards.Rendering.Xamarin.Android.ObjectModel.FeatureRegistration featureRegistration)

	}
}

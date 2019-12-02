using System;
using System.Collections.Generic;
using Android.Runtime;
using Java.Interop;

namespace AdaptiveCards.Rendering.Xamarin.Android.Renderer.ActionHandler {

	// Metadata.xml XPath interface reference: path="/api/package[@name='io.adaptivecards.renderer.actionhandler']/interface[@name='ICardActionHandler']"
	[Register ("io/adaptivecards/renderer/actionhandler/ICardActionHandler", "", "AdaptiveCards.Rendering.Xamarin.Android.Renderer.ActionHandler.ICardActionHandlerInvoker")]
	public partial interface ICardActionHandler : IJavaObject {

		// Metadata.xml XPath method reference: path="/api/package[@name='io.adaptivecards.renderer.actionhandler']/interface[@name='ICardActionHandler']/method[@name='onAction' and count(parameter)=2 and parameter[1][@type='io.adaptivecards.objectmodel.BaseActionElement'] and parameter[2][@type='io.adaptivecards.renderer.RenderedAdaptiveCard']]"
		[Register ("onAction", "(Lio/adaptivecards/objectmodel/BaseActionElement;Lio/adaptivecards/renderer/RenderedAdaptiveCard;)V", "GetOnAction_Lio_adaptivecards_objectmodel_BaseActionElement_Lio_adaptivecards_renderer_RenderedAdaptiveCard_Handler:AdaptiveCards.Rendering.Xamarin.Android.Renderer.ActionHandler.ICardActionHandlerInvoker, AdaptiveCards.Rendering.Xamarin.Android")]
		void OnAction (global::AdaptiveCards.Rendering.Xamarin.Android.ObjectModel.BaseActionElement p0, global::AdaptiveCards.Rendering.Xamarin.Android.Renderer.RenderedAdaptiveCard p1);

		// Metadata.xml XPath method reference: path="/api/package[@name='io.adaptivecards.renderer.actionhandler']/interface[@name='ICardActionHandler']/method[@name='onMediaPlay' and count(parameter)=2 and parameter[1][@type='io.adaptivecards.objectmodel.BaseCardElement'] and parameter[2][@type='io.adaptivecards.renderer.RenderedAdaptiveCard']]"
		[Register ("onMediaPlay", "(Lio/adaptivecards/objectmodel/BaseCardElement;Lio/adaptivecards/renderer/RenderedAdaptiveCard;)V", "GetOnMediaPlay_Lio_adaptivecards_objectmodel_BaseCardElement_Lio_adaptivecards_renderer_RenderedAdaptiveCard_Handler:AdaptiveCards.Rendering.Xamarin.Android.Renderer.ActionHandler.ICardActionHandlerInvoker, AdaptiveCards.Rendering.Xamarin.Android")]
		void OnMediaPlay (global::AdaptiveCards.Rendering.Xamarin.Android.ObjectModel.BaseCardElement p0, global::AdaptiveCards.Rendering.Xamarin.Android.Renderer.RenderedAdaptiveCard p1);

		// Metadata.xml XPath method reference: path="/api/package[@name='io.adaptivecards.renderer.actionhandler']/interface[@name='ICardActionHandler']/method[@name='onMediaStop' and count(parameter)=2 and parameter[1][@type='io.adaptivecards.objectmodel.BaseCardElement'] and parameter[2][@type='io.adaptivecards.renderer.RenderedAdaptiveCard']]"
		[Register ("onMediaStop", "(Lio/adaptivecards/objectmodel/BaseCardElement;Lio/adaptivecards/renderer/RenderedAdaptiveCard;)V", "GetOnMediaStop_Lio_adaptivecards_objectmodel_BaseCardElement_Lio_adaptivecards_renderer_RenderedAdaptiveCard_Handler:AdaptiveCards.Rendering.Xamarin.Android.Renderer.ActionHandler.ICardActionHandlerInvoker, AdaptiveCards.Rendering.Xamarin.Android")]
		void OnMediaStop (global::AdaptiveCards.Rendering.Xamarin.Android.ObjectModel.BaseCardElement p0, global::AdaptiveCards.Rendering.Xamarin.Android.Renderer.RenderedAdaptiveCard p1);
	}

}

using System;
using System.Collections.Generic;
using Android.Runtime;
using Java.Interop;

namespace AdaptiveCards.Rendering.Xamarin.Android.Renderer {

	// Metadata.xml XPath class reference: path="/api/package[@name='io.adaptivecards.renderer']/class[@name='RenderedAdaptiveCard']"
	[global::Android.Runtime.Register ("io/adaptivecards/renderer/RenderedAdaptiveCard", DoNotGenerateAcw=true)]
	public partial class RenderedAdaptiveCard : global::Java.Lang.Object {

		// Metadata.xml XPath constructor reference: path="/api/package[@name='io.adaptivecards.renderer']/class[@name='RenderedAdaptiveCard']/constructor[@name='RenderedAdaptiveCard' and count(parameter)=1 and parameter[1][@type='io.adaptivecards.objectmodel.AdaptiveCard']]"
		[Register (".ctor", "(Lio/adaptivecards/objectmodel/AdaptiveCard;)V", "")]
		protected unsafe RenderedAdaptiveCard (global::AdaptiveCards.Rendering.Xamarin.Android.ObjectModel.AdaptiveCard adaptiveCard)

		public virtual unsafe global::AdaptiveCards.Rendering.Xamarin.Android.ObjectModel.AdaptiveCard AdaptiveCard

		public virtual unsafe global::System.Collections.Generic.IDictionary<string, string> Inputs

		public virtual unsafe global::Android.Views.View View

		public virtual unsafe global::Java.Util.Vector Warnings

		// Metadata.xml XPath method reference: path="/api/package[@name='io.adaptivecards.renderer']/class[@name='RenderedAdaptiveCard']/method[@name='addWarning' and count(parameter)=1 and parameter[1][@type='io.adaptivecards.renderer.AdaptiveWarning']]"
		[Register ("addWarning", "(Lio/adaptivecards/renderer/AdaptiveWarning;)V", "GetAddWarning_Lio_adaptivecards_renderer_AdaptiveWarning_Handler")]
		public virtual unsafe void AddWarning (global::AdaptiveCards.Rendering.Xamarin.Android.Renderer.AdaptiveWarning warning)

		// Metadata.xml XPath method reference: path="/api/package[@name='io.adaptivecards.renderer']/class[@name='RenderedAdaptiveCard']/method[@name='registerInputHandler' and count(parameter)=1 and parameter[1][@type='io.adaptivecards.renderer.inputhandler.IInputHandler']]"
		[Register ("registerInputHandler", "(Lio/adaptivecards/renderer/inputhandler/IInputHandler;)V", "GetRegisterInputHandler_Lio_adaptivecards_renderer_inputhandler_IInputHandler_Handler")]
		public virtual unsafe void RegisterInputHandler (global::AdaptiveCards.Rendering.Xamarin.Android.Renderer.InputHandler.IInputHandler handler)

	}
}

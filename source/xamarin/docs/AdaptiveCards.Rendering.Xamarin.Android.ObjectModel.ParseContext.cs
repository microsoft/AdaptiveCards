using System;
using System.Collections.Generic;
using Android.Runtime;
using Java.Interop;

namespace AdaptiveCards.Rendering.Xamarin.Android.ObjectModel {

	// Metadata.xml XPath class reference: path="/api/package[@name='io.adaptivecards.objectmodel']/class[@name='ParseContext']"
	[global::Android.Runtime.Register ("io/adaptivecards/objectmodel/ParseContext", DoNotGenerateAcw=true)]
	public partial class ParseContext : global::Java.Lang.Object {

		// Metadata.xml XPath constructor reference: path="/api/package[@name='io.adaptivecards.objectmodel']/class[@name='ParseContext']/constructor[@name='ParseContext' and count(parameter)=0]"
		[Register (".ctor", "()V", "")]
		public unsafe ParseContext ()

		// Metadata.xml XPath constructor reference: path="/api/package[@name='io.adaptivecards.objectmodel']/class[@name='ParseContext']/constructor[@name='ParseContext' and count(parameter)=2 and parameter[1][@type='io.adaptivecards.objectmodel.ElementParserRegistration'] and parameter[2][@type='io.adaptivecards.objectmodel.ActionParserRegistration']]"
		[Register (".ctor", "(Lio/adaptivecards/objectmodel/ElementParserRegistration;Lio/adaptivecards/objectmodel/ActionParserRegistration;)V", "")]
		public unsafe ParseContext (global::AdaptiveCards.Rendering.Xamarin.Android.ObjectModel.ElementParserRegistration elementRegistration, global::AdaptiveCards.Rendering.Xamarin.Android.ObjectModel.ActionParserRegistration actionRegistration)

		public virtual unsafe global::AdaptiveCards.Rendering.Xamarin.Android.ObjectModel.ActionParserRegistration ActionParserRegistration

		public virtual unsafe global::AdaptiveCards.Rendering.Xamarin.Android.ObjectModel.ElementParserRegistration ElementParserRegistration

		// Metadata.xml XPath method reference: path="/api/package[@name='io.adaptivecards.objectmodel']/class[@name='ParseContext']/method[@name='delete' and count(parameter)=0]"
		[Register ("delete", "()V", "GetDeleteHandler")]
		public virtual unsafe void Delete ()

	}
}

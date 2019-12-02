using System;
using System.Collections.Generic;
using Android.Runtime;
using Java.Interop;

namespace AdaptiveCards.Rendering.Xamarin.Android.ObjectModel {

	// Metadata.xml XPath class reference: path="/api/package[@name='io.adaptivecards.objectmodel']/class[@name='ParseResult']"
	[global::Android.Runtime.Register ("io/adaptivecards/objectmodel/ParseResult", DoNotGenerateAcw=true)]
	public partial class ParseResult : global::Java.Lang.Object {

		// Metadata.xml XPath constructor reference: path="/api/package[@name='io.adaptivecards.objectmodel']/class[@name='ParseResult']/constructor[@name='ParseResult' and count(parameter)=2 and parameter[1][@type='io.adaptivecards.objectmodel.AdaptiveCard'] and parameter[2][@type='io.adaptivecards.objectmodel.AdaptiveCardParseWarningVector']]"
		[Register (".ctor", "(Lio/adaptivecards/objectmodel/AdaptiveCard;Lio/adaptivecards/objectmodel/AdaptiveCardParseWarningVector;)V", "")]
		public unsafe ParseResult (global::AdaptiveCards.Rendering.Xamarin.Android.ObjectModel.AdaptiveCard adaptiveCard, global::AdaptiveCards.Rendering.Xamarin.Android.ObjectModel.AdaptiveCardParseWarningVector warnings)

		public virtual unsafe global::AdaptiveCards.Rendering.Xamarin.Android.ObjectModel.AdaptiveCard AdaptiveCard

		public virtual unsafe global::AdaptiveCards.Rendering.Xamarin.Android.ObjectModel.AdaptiveCardParseWarningVector Warnings

		// Metadata.xml XPath method reference: path="/api/package[@name='io.adaptivecards.objectmodel']/class[@name='ParseResult']/method[@name='delete' and count(parameter)=0]"
		[Register ("delete", "()V", "GetDeleteHandler")]
		public virtual unsafe void Delete ()

	}
}

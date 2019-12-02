using System;
using System.Collections.Generic;
using Android.Runtime;
using Java.Interop;

namespace AdaptiveCards.Rendering.Xamarin.Android.ObjectModel {

	// Metadata.xml XPath class reference: path="/api/package[@name='io.adaptivecards.objectmodel']/class[@name='BaseCardElement']"
	[global::Android.Runtime.Register ("io/adaptivecards/objectmodel/BaseCardElement", DoNotGenerateAcw=true)]
	public partial class BaseCardElement : global::AdaptiveCards.Rendering.Xamarin.Android.ObjectModel.BaseElement {

		// Metadata.xml XPath constructor reference: path="/api/package[@name='io.adaptivecards.objectmodel']/class[@name='BaseCardElement']/constructor[@name='BaseCardElement' and count(parameter)=0]"
		[Register (".ctor", "()V", "")]
		public unsafe BaseCardElement ()

		// Metadata.xml XPath constructor reference: path="/api/package[@name='io.adaptivecards.objectmodel']/class[@name='BaseCardElement']/constructor[@name='BaseCardElement' and count(parameter)=1 and parameter[1][@type='io.adaptivecards.objectmodel.BaseCardElement']]"
		[Register (".ctor", "(Lio/adaptivecards/objectmodel/BaseCardElement;)V", "")]
		public unsafe BaseCardElement (global::AdaptiveCards.Rendering.Xamarin.Android.ObjectModel.BaseCardElement arg0)

		// Metadata.xml XPath constructor reference: path="/api/package[@name='io.adaptivecards.objectmodel']/class[@name='BaseCardElement']/constructor[@name='BaseCardElement' and count(parameter)=1 and parameter[1][@type='io.adaptivecards.objectmodel.CardElementType']]"
		[Register (".ctor", "(Lio/adaptivecards/objectmodel/CardElementType;)V", "")]
		public unsafe BaseCardElement (global::AdaptiveCards.Rendering.Xamarin.Android.ObjectModel.CardElementType type)

		// Metadata.xml XPath constructor reference: path="/api/package[@name='io.adaptivecards.objectmodel']/class[@name='BaseCardElement']/constructor[@name='BaseCardElement' and count(parameter)=4 and parameter[1][@type='io.adaptivecards.objectmodel.CardElementType'] and parameter[2][@type='io.adaptivecards.objectmodel.Spacing'] and parameter[3][@type='boolean'] and parameter[4][@type='io.adaptivecards.objectmodel.HeightType']]"
		[Register (".ctor", "(Lio/adaptivecards/objectmodel/CardElementType;Lio/adaptivecards/objectmodel/Spacing;ZLio/adaptivecards/objectmodel/HeightType;)V", "")]
		public unsafe BaseCardElement (global::AdaptiveCards.Rendering.Xamarin.Android.ObjectModel.CardElementType type, global::AdaptiveCards.Rendering.Xamarin.Android.ObjectModel.Spacing spacing, bool separator, global::AdaptiveCards.Rendering.Xamarin.Android.ObjectModel.HeightType height)

		public virtual unsafe global::AdaptiveCards.Rendering.Xamarin.Android.ObjectModel.CardElementType ElementType

		public virtual unsafe global::AdaptiveCards.Rendering.Xamarin.Android.ObjectModel.HeightType Height

		public virtual unsafe bool IsVisible

		public virtual unsafe bool Separator

		public virtual unsafe global::AdaptiveCards.Rendering.Xamarin.Android.ObjectModel.Spacing Spacing

		// Metadata.xml XPath method reference: path="/api/package[@name='io.adaptivecards.objectmodel']/class[@name='BaseCardElement']/method[@name='ParseJsonObject' and count(parameter)=3 and parameter[1][@type='io.adaptivecards.objectmodel.ParseContext'] and parameter[2][@type='io.adaptivecards.objectmodel.JsonValue'] and parameter[3][@type='io.adaptivecards.objectmodel.BaseElement']]"
		[Register ("ParseJsonObject", "(Lio/adaptivecards/objectmodel/ParseContext;Lio/adaptivecards/objectmodel/JsonValue;Lio/adaptivecards/objectmodel/BaseElement;)V", "")]
		public static unsafe void ParseJsonObject (global::AdaptiveCards.Rendering.Xamarin.Android.ObjectModel.ParseContext context, global::AdaptiveCards.Rendering.Xamarin.Android.ObjectModel.JsonValue json, global::AdaptiveCards.Rendering.Xamarin.Android.ObjectModel.BaseElement element)

		// Metadata.xml XPath method reference: path="/api/package[@name='io.adaptivecards.objectmodel']/class[@name='BaseCardElement']/method[@name='dynamic_cast' and count(parameter)=1 and parameter[1][@type='io.adaptivecards.objectmodel.BaseElement']]"
		[Register ("dynamic_cast", "(Lio/adaptivecards/objectmodel/BaseElement;)Lio/adaptivecards/objectmodel/BaseCardElement;", "")]
		public static unsafe global::AdaptiveCards.Rendering.Xamarin.Android.ObjectModel.BaseCardElement Dynamic_cast (global::AdaptiveCards.Rendering.Xamarin.Android.ObjectModel.BaseElement baseElement)

		// Metadata.xml XPath method reference: path="/api/package[@name='io.adaptivecards.objectmodel']/class[@name='BaseCardElement']/method[@name='findImplObj' and count(parameter)=0]"
		[Register ("findImplObj", "()Lio/adaptivecards/objectmodel/BaseCardElement;", "GetFindImplObjHandler")]
		public virtual unsafe global::AdaptiveCards.Rendering.Xamarin.Android.ObjectModel.BaseCardElement FindImplObj ()

		// Metadata.xml XPath method reference: path="/api/package[@name='io.adaptivecards.objectmodel']/class[@name='BaseCardElement']/method[@name='getCPtr' and count(parameter)=1 and parameter[1][@type='io.adaptivecards.objectmodel.BaseCardElement']]"
		[Register ("getCPtr", "(Lio/adaptivecards/objectmodel/BaseCardElement;)J", "")]
		protected static unsafe long GetCPtr (global::AdaptiveCards.Rendering.Xamarin.Android.ObjectModel.BaseCardElement obj)

		// Metadata.xml XPath method reference: path="/api/package[@name='io.adaptivecards.objectmodel']/class[@name='BaseCardElement']/method[@name='swigOriginalObject' and count(parameter)=0]"
		[Register ("swigOriginalObject", "()Ljava/lang/Object;", "GetSwigOriginalObjectHandler")]
		public virtual unsafe global::Java.Lang.Object SwigOriginalObject ()

	}
}

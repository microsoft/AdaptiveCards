using System;
using System.Collections.Generic;
using Android.Runtime;
using Java.Interop;

namespace AdaptiveCards.Rendering.Xamarin.Android.ObjectModel {

	// Metadata.xml XPath class reference: path="/api/package[@name='io.adaptivecards.objectmodel']/class[@name='BaseActionElement']"
	[global::Android.Runtime.Register ("io/adaptivecards/objectmodel/BaseActionElement", DoNotGenerateAcw=true)]
	public partial class BaseActionElement : global::AdaptiveCards.Rendering.Xamarin.Android.ObjectModel.BaseElement {

		// Metadata.xml XPath constructor reference: path="/api/package[@name='io.adaptivecards.objectmodel']/class[@name='BaseActionElement']/constructor[@name='BaseActionElement' and count(parameter)=0]"
		[Register (".ctor", "()V", "")]
		public unsafe BaseActionElement ()

		// Metadata.xml XPath constructor reference: path="/api/package[@name='io.adaptivecards.objectmodel']/class[@name='BaseActionElement']/constructor[@name='BaseActionElement' and count(parameter)=1 and parameter[1][@type='io.adaptivecards.objectmodel.ActionType']]"
		[Register (".ctor", "(Lio/adaptivecards/objectmodel/ActionType;)V", "")]
		public unsafe BaseActionElement (global::AdaptiveCards.Rendering.Xamarin.Android.ObjectModel.ActionType type)

		// Metadata.xml XPath constructor reference: path="/api/package[@name='io.adaptivecards.objectmodel']/class[@name='BaseActionElement']/constructor[@name='BaseActionElement' and count(parameter)=1 and parameter[1][@type='io.adaptivecards.objectmodel.BaseActionElement']]"
		[Register (".ctor", "(Lio/adaptivecards/objectmodel/BaseActionElement;)V", "")]
		public unsafe BaseActionElement (global::AdaptiveCards.Rendering.Xamarin.Android.ObjectModel.BaseActionElement arg0)

		public virtual unsafe global::AdaptiveCards.Rendering.Xamarin.Android.ObjectModel.ActionType ElementType

		public virtual unsafe string IconUrl

		public virtual unsafe string Style

		public virtual unsafe string Title

		// Metadata.xml XPath method reference: path="/api/package[@name='io.adaptivecards.objectmodel']/class[@name='BaseActionElement']/method[@name='ParseJsonObject' and count(parameter)=3 and parameter[1][@type='io.adaptivecards.objectmodel.ParseContext'] and parameter[2][@type='io.adaptivecards.objectmodel.JsonValue'] and parameter[3][@type='io.adaptivecards.objectmodel.BaseElement']]"
		[Register ("ParseJsonObject", "(Lio/adaptivecards/objectmodel/ParseContext;Lio/adaptivecards/objectmodel/JsonValue;Lio/adaptivecards/objectmodel/BaseElement;)V", "")]
		public static unsafe void ParseJsonObject (global::AdaptiveCards.Rendering.Xamarin.Android.ObjectModel.ParseContext context, global::AdaptiveCards.Rendering.Xamarin.Android.ObjectModel.JsonValue json, global::AdaptiveCards.Rendering.Xamarin.Android.ObjectModel.BaseElement element)

		// Metadata.xml XPath method reference: path="/api/package[@name='io.adaptivecards.objectmodel']/class[@name='BaseActionElement']/method[@name='dynamic_cast' and count(parameter)=1 and parameter[1][@type='io.adaptivecards.objectmodel.BaseElement']]"
		[Register ("dynamic_cast", "(Lio/adaptivecards/objectmodel/BaseElement;)Lio/adaptivecards/objectmodel/BaseActionElement;", "")]
		public static unsafe global::AdaptiveCards.Rendering.Xamarin.Android.ObjectModel.BaseActionElement Dynamic_cast (global::AdaptiveCards.Rendering.Xamarin.Android.ObjectModel.BaseElement baseElement)

		// Metadata.xml XPath method reference: path="/api/package[@name='io.adaptivecards.objectmodel']/class[@name='BaseActionElement']/method[@name='findImplObj' and count(parameter)=0]"
		[Register ("findImplObj", "()Lio/adaptivecards/objectmodel/BaseActionElement;", "GetFindImplObjHandler")]
		public virtual unsafe global::AdaptiveCards.Rendering.Xamarin.Android.ObjectModel.BaseActionElement FindImplObj ()

		// Metadata.xml XPath method reference: path="/api/package[@name='io.adaptivecards.objectmodel']/class[@name='BaseActionElement']/method[@name='getCPtr' and count(parameter)=1 and parameter[1][@type='io.adaptivecards.objectmodel.BaseActionElement']]"
		[Register ("getCPtr", "(Lio/adaptivecards/objectmodel/BaseActionElement;)J", "")]
		protected static unsafe long GetCPtr (global::AdaptiveCards.Rendering.Xamarin.Android.ObjectModel.BaseActionElement obj)

		// Metadata.xml XPath method reference: path="/api/package[@name='io.adaptivecards.objectmodel']/class[@name='BaseActionElement']/method[@name='swigOriginalObject' and count(parameter)=0]"
		[Register ("swigOriginalObject", "()Ljava/lang/Object;", "GetSwigOriginalObjectHandler")]
		public virtual unsafe global::Java.Lang.Object SwigOriginalObject ()

	}
}

using System;
using System.Collections.Generic;
using Android.Runtime;
using Java.Interop;

namespace AdaptiveCards.Rendering.Xamarin.Android.ObjectModel {

	// Metadata.xml XPath class reference: path="/api/package[@name='io.adaptivecards.objectmodel']/class[@name='ActionElementParser']"
	[global::Android.Runtime.Register ("io/adaptivecards/objectmodel/ActionElementParser", DoNotGenerateAcw=true)]
	public partial class ActionElementParser : global::Java.Lang.Object {

		protected ActionElementParser (IntPtr javaReference, JniHandleOwnership transfer)

		// Metadata.xml XPath constructor reference: path="/api/package[@name='io.adaptivecards.objectmodel']/class[@name='ActionElementParser']/constructor[@name='ActionElementParser' and count(parameter)=0]"
		[Register (".ctor", "()V", "")]
		public unsafe ActionElementParser ()

		// Metadata.xml XPath constructor reference: path="/api/package[@name='io.adaptivecards.objectmodel']/class[@name='ActionElementParser']/constructor[@name='ActionElementParser' and count(parameter)=2 and parameter[1][@type='long'] and parameter[2][@type='boolean']]"
		[Register (".ctor", "(JZ)V", "")]
		protected unsafe ActionElementParser (long cPtr, bool cMemoryOwn)

		// Metadata.xml XPath method reference: path="/api/package[@name='io.adaptivecards.objectmodel']/class[@name='ActionElementParser']/method[@name='Deserialize' and count(parameter)=2 and parameter[1][@type='io.adaptivecards.objectmodel.ParseContext'] and parameter[2][@type='io.adaptivecards.objectmodel.JsonValue']]"
		[Register ("Deserialize", "(Lio/adaptivecards/objectmodel/ParseContext;Lio/adaptivecards/objectmodel/JsonValue;)Lio/adaptivecards/objectmodel/BaseActionElement;", "GetDeserialize_Lio_adaptivecards_objectmodel_ParseContext_Lio_adaptivecards_objectmodel_JsonValue_Handler")]
		public virtual unsafe global::AdaptiveCards.Rendering.Xamarin.Android.ObjectModel.BaseActionElement Deserialize (global::AdaptiveCards.Rendering.Xamarin.Android.ObjectModel.ParseContext context, global::AdaptiveCards.Rendering.Xamarin.Android.ObjectModel.JsonValue value)

		// Metadata.xml XPath method reference: path="/api/package[@name='io.adaptivecards.objectmodel']/class[@name='ActionElementParser']/method[@name='DeserializeFromString' and count(parameter)=2 and parameter[1][@type='io.adaptivecards.objectmodel.ParseContext'] and parameter[2][@type='java.lang.String']]"
		[Register ("DeserializeFromString", "(Lio/adaptivecards/objectmodel/ParseContext;Ljava/lang/String;)Lio/adaptivecards/objectmodel/BaseActionElement;", "GetDeserializeFromString_Lio_adaptivecards_objectmodel_ParseContext_Ljava_lang_String_Handler")]
		public virtual unsafe global::AdaptiveCards.Rendering.Xamarin.Android.ObjectModel.BaseActionElement DeserializeFromString (global::AdaptiveCards.Rendering.Xamarin.Android.ObjectModel.ParseContext context, string value)

		// Metadata.xml XPath method reference: path="/api/package[@name='io.adaptivecards.objectmodel']/class[@name='ActionElementParser']/method[@name='delete' and count(parameter)=0]"
		[Register ("delete", "()V", "GetDeleteHandler")]
		public virtual unsafe void Delete ()

		// Metadata.xml XPath method reference: path="/api/package[@name='io.adaptivecards.objectmodel']/class[@name='ActionElementParser']/method[@name='getCPtr' and count(parameter)=1 and parameter[1][@type='io.adaptivecards.objectmodel.ActionElementParser']]"
		[Register ("getCPtr", "(Lio/adaptivecards/objectmodel/ActionElementParser;)J", "")]
		protected static unsafe long GetCPtr (global::AdaptiveCards.Rendering.Xamarin.Android.ObjectModel.ActionElementParser obj)

		// Metadata.xml XPath method reference: path="/api/package[@name='io.adaptivecards.objectmodel']/class[@name='ActionElementParser']/method[@name='swigDirectorDisconnect' and count(parameter)=0]"
		[Register ("swigDirectorDisconnect", "()V", "GetSwigDirectorDisconnectHandler")]
		protected virtual unsafe void SwigDirectorDisconnect ()
	}
}

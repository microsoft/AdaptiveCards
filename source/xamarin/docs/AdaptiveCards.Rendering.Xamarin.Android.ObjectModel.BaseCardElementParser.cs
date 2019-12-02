using System;
using System.Collections.Generic;
using Android.Runtime;
using Java.Interop;

namespace AdaptiveCards.Rendering.Xamarin.Android.ObjectModel {

	// Metadata.xml XPath class reference: path="/api/package[@name='io.adaptivecards.objectmodel']/class[@name='BaseCardElementParser']"
	[global::Android.Runtime.Register ("io/adaptivecards/objectmodel/BaseCardElementParser", DoNotGenerateAcw=true)]
	public partial class BaseCardElementParser : global::Java.Lang.Object {

		// Metadata.xml XPath constructor reference: path="/api/package[@name='io.adaptivecards.objectmodel']/class[@name='BaseCardElementParser']/constructor[@name='BaseCardElementParser' and count(parameter)=0]"
		[Register (".ctor", "()V", "")]
		public unsafe BaseCardElementParser ()

		// Metadata.xml XPath method reference: path="/api/package[@name='io.adaptivecards.objectmodel']/class[@name='BaseCardElementParser']/method[@name='Deserialize' and count(parameter)=2 and parameter[1][@type='io.adaptivecards.objectmodel.ParseContext'] and parameter[2][@type='io.adaptivecards.objectmodel.JsonValue']]"
		[Register ("Deserialize", "(Lio/adaptivecards/objectmodel/ParseContext;Lio/adaptivecards/objectmodel/JsonValue;)Lio/adaptivecards/objectmodel/BaseCardElement;", "GetDeserialize_Lio_adaptivecards_objectmodel_ParseContext_Lio_adaptivecards_objectmodel_JsonValue_Handler")]
		public virtual unsafe global::AdaptiveCards.Rendering.Xamarin.Android.ObjectModel.BaseCardElement Deserialize (global::AdaptiveCards.Rendering.Xamarin.Android.ObjectModel.ParseContext context, global::AdaptiveCards.Rendering.Xamarin.Android.ObjectModel.JsonValue value)

		// Metadata.xml XPath method reference: path="/api/package[@name='io.adaptivecards.objectmodel']/class[@name='BaseCardElementParser']/method[@name='DeserializeFromString' and count(parameter)=2 and parameter[1][@type='io.adaptivecards.objectmodel.ParseContext'] and parameter[2][@type='java.lang.String']]"
		[Register ("DeserializeFromString", "(Lio/adaptivecards/objectmodel/ParseContext;Ljava/lang/String;)Lio/adaptivecards/objectmodel/BaseCardElement;", "GetDeserializeFromString_Lio_adaptivecards_objectmodel_ParseContext_Ljava_lang_String_Handler")]
		public virtual unsafe global::AdaptiveCards.Rendering.Xamarin.Android.ObjectModel.BaseCardElement DeserializeFromString (global::AdaptiveCards.Rendering.Xamarin.Android.ObjectModel.ParseContext context, string value)

		// Metadata.xml XPath method reference: path="/api/package[@name='io.adaptivecards.objectmodel']/class[@name='BaseCardElementParser']/method[@name='delete' and count(parameter)=0]"
		[Register ("delete", "()V", "GetDeleteHandler")]
		public virtual unsafe void Delete ()

		// Metadata.xml XPath method reference: path="/api/package[@name='io.adaptivecards.objectmodel']/class[@name='BaseCardElementParser']/method[@name='swigReleaseOwnership' and count(parameter)=0]"
		[Register ("swigReleaseOwnership", "()V", "GetSwigReleaseOwnershipHandler")]
		public virtual unsafe void SwigReleaseOwnership ()

		// Metadata.xml XPath method reference: path="/api/package[@name='io.adaptivecards.objectmodel']/class[@name='BaseCardElementParser']/method[@name='swigSetCMemOwn' and count(parameter)=1 and parameter[1][@type='boolean']]"
		[Register ("swigSetCMemOwn", "(Z)V", "GetSwigSetCMemOwn_ZHandler")]
		protected virtual unsafe void SwigSetCMemOwn (bool own)

		// Metadata.xml XPath method reference: path="/api/package[@name='io.adaptivecards.objectmodel']/class[@name='BaseCardElementParser']/method[@name='swigTakeOwnership' and count(parameter)=0]"
		[Register ("swigTakeOwnership", "()V", "GetSwigTakeOwnershipHandler")]
		public virtual unsafe void SwigTakeOwnership ()
	}
}

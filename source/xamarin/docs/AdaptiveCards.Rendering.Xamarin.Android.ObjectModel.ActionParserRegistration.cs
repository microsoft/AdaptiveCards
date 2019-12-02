using System;
using System.Collections.Generic;
using Android.Runtime;
using Java.Interop;

namespace AdaptiveCards.Rendering.Xamarin.Android.ObjectModel {

	// Metadata.xml XPath class reference: path="/api/package[@name='io.adaptivecards.objectmodel']/class[@name='ActionParserRegistration']"
	[global::Android.Runtime.Register ("io/adaptivecards/objectmodel/ActionParserRegistration", DoNotGenerateAcw=true)]
	public partial class ActionParserRegistration : global::Java.Lang.Object {

		// Metadata.xml XPath constructor reference: path="/api/package[@name='io.adaptivecards.objectmodel']/class[@name='ActionParserRegistration']/constructor[@name='ActionParserRegistration' and count(parameter)=0]"
		[Register (".ctor", "()V", "")]
		public unsafe ActionParserRegistration ()

		// Metadata.xml XPath constructor reference: path="/api/package[@name='io.adaptivecards.objectmodel']/class[@name='ActionParserRegistration']/constructor[@name='ActionParserRegistration' and count(parameter)=2 and parameter[1][@type='long'] and parameter[2][@type='boolean']]"
		[Register (".ctor", "(JZ)V", "")]
		protected unsafe ActionParserRegistration (long cPtr, bool cMemoryOwn)

		// Metadata.xml XPath method reference: path="/api/package[@name='io.adaptivecards.objectmodel']/class[@name='ActionParserRegistration']/method[@name='AddParser' and count(parameter)=2 and parameter[1][@type='java.lang.String'] and parameter[2][@type='io.adaptivecards.objectmodel.ActionElementParser']]"
		[Register ("AddParser", "(Ljava/lang/String;Lio/adaptivecards/objectmodel/ActionElementParser;)V", "GetAddParser_Ljava_lang_String_Lio_adaptivecards_objectmodel_ActionElementParser_Handler")]
		public virtual unsafe void AddParser (string elementType, global::AdaptiveCards.Rendering.Xamarin.Android.ObjectModel.ActionElementParser parser)

		// Metadata.xml XPath method reference: path="/api/package[@name='io.adaptivecards.objectmodel']/class[@name='ActionParserRegistration']/method[@name='GetParser' and count(parameter)=1 and parameter[1][@type='java.lang.String']]"
		[Register ("GetParser", "(Ljava/lang/String;)Lio/adaptivecards/objectmodel/ActionElementParser;", "GetGetParser_Ljava_lang_String_Handler")]
		public virtual unsafe global::AdaptiveCards.Rendering.Xamarin.Android.ObjectModel.ActionElementParser GetParser (string elementType)

		// Metadata.xml XPath method reference: path="/api/package[@name='io.adaptivecards.objectmodel']/class[@name='ActionParserRegistration']/method[@name='RemoveParser' and count(parameter)=1 and parameter[1][@type='java.lang.String']]"
		[Register ("RemoveParser", "(Ljava/lang/String;)V", "GetRemoveParser_Ljava_lang_String_Handler")]
		public virtual unsafe void RemoveParser (string elementType)

		// Metadata.xml XPath method reference: path="/api/package[@name='io.adaptivecards.objectmodel']/class[@name='ActionParserRegistration']/method[@name='delete' and count(parameter)=0]"
		[Register ("delete", "()V", "GetDeleteHandler")]
		public virtual unsafe void Delete ()

		// Metadata.xml XPath method reference: path="/api/package[@name='io.adaptivecards.objectmodel']/class[@name='ActionParserRegistration']/method[@name='getCPtr' and count(parameter)=1 and parameter[1][@type='io.adaptivecards.objectmodel.ActionParserRegistration']]"
		[Register ("getCPtr", "(Lio/adaptivecards/objectmodel/ActionParserRegistration;)J", "")]
		protected static unsafe long GetCPtr (global::AdaptiveCards.Rendering.Xamarin.Android.ObjectModel.ActionParserRegistration obj)

		// Metadata.xml XPath method reference: path="/api/package[@name='io.adaptivecards.objectmodel']/class[@name='ActionParserRegistration']/method[@name='swigSetCMemOwn' and count(parameter)=1 and parameter[1][@type='boolean']]"
		[Register ("swigSetCMemOwn", "(Z)V", "GetSwigSetCMemOwn_ZHandler")]
		protected virtual unsafe void SwigSetCMemOwn (bool own)

	}
}

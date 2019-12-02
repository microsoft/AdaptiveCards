using System;
using System.Collections.Generic;
using Android.Runtime;
using Java.Interop;

namespace AdaptiveCards.Rendering.Xamarin.Android.ObjectModel {

	// Metadata.xml XPath class reference: path="/api/package[@name='io.adaptivecards.objectmodel']/class[@name='FeatureRegistration']"
	[global::Android.Runtime.Register ("io/adaptivecards/objectmodel/FeatureRegistration", DoNotGenerateAcw=true)]
	public partial class FeatureRegistration : global::Java.Lang.Object {

		// Metadata.xml XPath constructor reference: path="/api/package[@name='io.adaptivecards.objectmodel']/class[@name='FeatureRegistration']/constructor[@name='FeatureRegistration' and count(parameter)=0]"
		[Register (".ctor", "()V", "")]
		public unsafe FeatureRegistration ()

		// Metadata.xml XPath constructor reference: path="/api/package[@name='io.adaptivecards.objectmodel']/class[@name='FeatureRegistration']/constructor[@name='FeatureRegistration' and count(parameter)=2 and parameter[1][@type='long'] and parameter[2][@type='boolean']]"
		[Register (".ctor", "(JZ)V", "")]
		protected unsafe FeatureRegistration (long cPtr, bool cMemoryOwn)

		public virtual unsafe global::AdaptiveCards.Rendering.Xamarin.Android.ObjectModel.SemanticVersion AdaptiveCardsVersion

		// Metadata.xml XPath method reference: path="/api/package[@name='io.adaptivecards.objectmodel']/class[@name='FeatureRegistration']/method[@name='AddFeature' and count(parameter)=2 and parameter[1][@type='java.lang.String'] and parameter[2][@type='java.lang.String']]"
		[Register ("AddFeature", "(Ljava/lang/String;Ljava/lang/String;)V", "GetAddFeature_Ljava_lang_String_Ljava_lang_String_Handler")]
		public virtual unsafe void AddFeature (string featureName, string featureVersion)

		// Metadata.xml XPath method reference: path="/api/package[@name='io.adaptivecards.objectmodel']/class[@name='FeatureRegistration']/method[@name='GetFeatureVersion' and count(parameter)=1 and parameter[1][@type='java.lang.String']]"
		[Register ("GetFeatureVersion", "(Ljava/lang/String;)Ljava/lang/String;", "GetGetFeatureVersion_Ljava_lang_String_Handler")]
		public virtual unsafe string GetFeatureVersion (string featureName)

		// Metadata.xml XPath method reference: path="/api/package[@name='io.adaptivecards.objectmodel']/class[@name='FeatureRegistration']/method[@name='RemoveFeature' and count(parameter)=1 and parameter[1][@type='java.lang.String']]"
		[Register ("RemoveFeature", "(Ljava/lang/String;)V", "GetRemoveFeature_Ljava_lang_String_Handler")]
		public virtual unsafe void RemoveFeature (string featureName)

		// Metadata.xml XPath method reference: path="/api/package[@name='io.adaptivecards.objectmodel']/class[@name='FeatureRegistration']/method[@name='delete' and count(parameter)=0]"
		[Register ("delete", "()V", "GetDeleteHandler")]
		public virtual unsafe void Delete ()

	}
}

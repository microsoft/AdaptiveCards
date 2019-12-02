using System;
using System.Collections.Generic;
using Android.Runtime;
using Java.Interop;

namespace AdaptiveCards.Rendering.Xamarin.Android.ObjectModel {

	// Metadata.xml XPath class reference: path="/api/package[@name='io.adaptivecards.objectmodel']/class[@name='AdaptiveCard']"
	[global::Android.Runtime.Register ("io/adaptivecards/objectmodel/AdaptiveCard", DoNotGenerateAcw=true)]
	public partial class AdaptiveCard : global::Java.Lang.Object {

		// Metadata.xml XPath constructor reference: path="/api/package[@name='io.adaptivecards.objectmodel']/class[@name='AdaptiveCard']/constructor[@name='AdaptiveCard' and count(parameter)=0]"
		[Register (".ctor", "()V", "")]
		public unsafe AdaptiveCard ()

		// Metadata.xml XPath constructor reference: path="/api/package[@name='io.adaptivecards.objectmodel']/class[@name='AdaptiveCard']/constructor[@name='AdaptiveCard' and count(parameter)=9 and parameter[1][@type='java.lang.String'] and parameter[2][@type='java.lang.String'] and parameter[3][@type='io.adaptivecards.objectmodel.BackgroundImage'] and parameter[4][@type='io.adaptivecards.objectmodel.ContainerStyle'] and parameter[5][@type='java.lang.String'] and parameter[6][@type='java.lang.String'] and parameter[7][@type='io.adaptivecards.objectmodel.VerticalContentAlignment'] and parameter[8][@type='io.adaptivecards.objectmodel.HeightType'] and parameter[9][@type='long']]"
		[Register (".ctor", "(Ljava/lang/String;Ljava/lang/String;Lio/adaptivecards/objectmodel/BackgroundImage;Lio/adaptivecards/objectmodel/ContainerStyle;Ljava/lang/String;Ljava/lang/String;Lio/adaptivecards/objectmodel/VerticalContentAlignment;Lio/adaptivecards/objectmodel/HeightType;J)V", "")]
		public unsafe AdaptiveCard (string version, string fallbackText, global::AdaptiveCards.Rendering.Xamarin.Android.ObjectModel.BackgroundImage backgroundImage, global::AdaptiveCards.Rendering.Xamarin.Android.ObjectModel.ContainerStyle style, string speak, string language, global::AdaptiveCards.Rendering.Xamarin.Android.ObjectModel.VerticalContentAlignment verticalContentAlignment, global::AdaptiveCards.Rendering.Xamarin.Android.ObjectModel.HeightType height, long minHeight)

		// Metadata.xml XPath constructor reference: path="/api/package[@name='io.adaptivecards.objectmodel']/class[@name='AdaptiveCard']/constructor[@name='AdaptiveCard' and count(parameter)=11 and parameter[1][@type='java.lang.String'] and parameter[2][@type='java.lang.String'] and parameter[3][@type='io.adaptivecards.objectmodel.BackgroundImage'] and parameter[4][@type='io.adaptivecards.objectmodel.ContainerStyle'] and parameter[5][@type='java.lang.String'] and parameter[6][@type='java.lang.String'] and parameter[7][@type='io.adaptivecards.objectmodel.VerticalContentAlignment'] and parameter[8][@type='io.adaptivecards.objectmodel.HeightType'] and parameter[9][@type='long'] and parameter[10][@type='io.adaptivecards.objectmodel.BaseCardElementVector'] and parameter[11][@type='io.adaptivecards.objectmodel.BaseActionElementVector']]"
		[Register (".ctor", "(Ljava/lang/String;Ljava/lang/String;Lio/adaptivecards/objectmodel/BackgroundImage;Lio/adaptivecards/objectmodel/ContainerStyle;Ljava/lang/String;Ljava/lang/String;Lio/adaptivecards/objectmodel/VerticalContentAlignment;Lio/adaptivecards/objectmodel/HeightType;JLio/adaptivecards/objectmodel/BaseCardElementVector;Lio/adaptivecards/objectmodel/BaseActionElementVector;)V", "")]
		public unsafe AdaptiveCard (string version, string fallbackText, global::AdaptiveCards.Rendering.Xamarin.Android.ObjectModel.BackgroundImage backgroundImage, global::AdaptiveCards.Rendering.Xamarin.Android.ObjectModel.ContainerStyle style, string speak, string language, global::AdaptiveCards.Rendering.Xamarin.Android.ObjectModel.VerticalContentAlignment verticalContentAlignment, global::AdaptiveCards.Rendering.Xamarin.Android.ObjectModel.HeightType height, long minHeight, global::AdaptiveCards.Rendering.Xamarin.Android.ObjectModel.BaseCardElementVector body, global::AdaptiveCards.Rendering.Xamarin.Android.ObjectModel.BaseActionElementVector actions)

		// Metadata.xml XPath constructor reference: path="/api/package[@name='io.adaptivecards.objectmodel']/class[@name='AdaptiveCard']/constructor[@name='AdaptiveCard' and count(parameter)=9 and parameter[1][@type='java.lang.String'] and parameter[2][@type='java.lang.String'] and parameter[3][@type='java.lang.String'] and parameter[4][@type='io.adaptivecards.objectmodel.ContainerStyle'] and parameter[5][@type='java.lang.String'] and parameter[6][@type='java.lang.String'] and parameter[7][@type='io.adaptivecards.objectmodel.VerticalContentAlignment'] and parameter[8][@type='io.adaptivecards.objectmodel.HeightType'] and parameter[9][@type='long']]"
		[Register (".ctor", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Lio/adaptivecards/objectmodel/ContainerStyle;Ljava/lang/String;Ljava/lang/String;Lio/adaptivecards/objectmodel/VerticalContentAlignment;Lio/adaptivecards/objectmodel/HeightType;J)V", "")]
		public unsafe AdaptiveCard (string version, string fallbackText, string backgroundImageUrl, global::AdaptiveCards.Rendering.Xamarin.Android.ObjectModel.ContainerStyle style, string speak, string language, global::AdaptiveCards.Rendering.Xamarin.Android.ObjectModel.VerticalContentAlignment verticalContentAlignment, global::AdaptiveCards.Rendering.Xamarin.Android.ObjectModel.HeightType height, long minHeight)

		// Metadata.xml XPath constructor reference: path="/api/package[@name='io.adaptivecards.objectmodel']/class[@name='AdaptiveCard']/constructor[@name='AdaptiveCard' and count(parameter)=11 and parameter[1][@type='java.lang.String'] and parameter[2][@type='java.lang.String'] and parameter[3][@type='java.lang.String'] and parameter[4][@type='io.adaptivecards.objectmodel.ContainerStyle'] and parameter[5][@type='java.lang.String'] and parameter[6][@type='java.lang.String'] and parameter[7][@type='io.adaptivecards.objectmodel.VerticalContentAlignment'] and parameter[8][@type='io.adaptivecards.objectmodel.HeightType'] and parameter[9][@type='long'] and parameter[10][@type='io.adaptivecards.objectmodel.BaseCardElementVector'] and parameter[11][@type='io.adaptivecards.objectmodel.BaseActionElementVector']]"
		[Register (".ctor", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Lio/adaptivecards/objectmodel/ContainerStyle;Ljava/lang/String;Ljava/lang/String;Lio/adaptivecards/objectmodel/VerticalContentAlignment;Lio/adaptivecards/objectmodel/HeightType;JLio/adaptivecards/objectmodel/BaseCardElementVector;Lio/adaptivecards/objectmodel/BaseActionElementVector;)V", "")]
		public unsafe AdaptiveCard (string version, string fallbackText, string backgroundImageUrl, global::AdaptiveCards.Rendering.Xamarin.Android.ObjectModel.ContainerStyle style, string speak, string language, global::AdaptiveCards.Rendering.Xamarin.Android.ObjectModel.VerticalContentAlignment verticalContentAlignment, global::AdaptiveCards.Rendering.Xamarin.Android.ObjectModel.HeightType height, long minHeight, global::AdaptiveCards.Rendering.Xamarin.Android.ObjectModel.BaseCardElementVector body, global::AdaptiveCards.Rendering.Xamarin.Android.ObjectModel.BaseActionElementVector actions)

		// Metadata.xml XPath constructor reference: path="/api/package[@name='io.adaptivecards.objectmodel']/class[@name='AdaptiveCard']/constructor[@name='AdaptiveCard' and count(parameter)=2 and parameter[1][@type='long'] and parameter[2][@type='boolean']]"
		[Register (".ctor", "(JZ)V", "")]
		protected unsafe AdaptiveCard (long cPtr, bool cMemoryOwn)

		public virtual unsafe global::AdaptiveCards.Rendering.Xamarin.Android.ObjectModel.BaseActionElementVector Actions

		public virtual unsafe global::AdaptiveCards.Rendering.Xamarin.Android.ObjectModel.BackgroundImage BackgroundImage

		public virtual unsafe global::AdaptiveCards.Rendering.Xamarin.Android.ObjectModel.BaseCardElementVector Body

		public virtual unsafe global::AdaptiveCards.Rendering.Xamarin.Android.ObjectModel.CardElementType ElementType

		public virtual unsafe string FallbackText

		public virtual unsafe global::AdaptiveCards.Rendering.Xamarin.Android.ObjectModel.HeightType Height

		public virtual unsafe global::AdaptiveCards.Rendering.Xamarin.Android.ObjectModel.InputNecessityIndicators InputNecessityIndicators

		public virtual unsafe global::AdaptiveCards.Rendering.Xamarin.Android.ObjectModel.InternalId InternalId

		public virtual unsafe string Language

		public virtual unsafe long MinHeight

		public virtual unsafe global::AdaptiveCards.Rendering.Xamarin.Android.ObjectModel.RemoteResourceInformationVector ResourceInformation

		public virtual unsafe global::AdaptiveCards.Rendering.Xamarin.Android.ObjectModel.BaseActionElement SelectAction

		public virtual unsafe string Speak

		public virtual unsafe global::AdaptiveCards.Rendering.Xamarin.Android.ObjectModel.ContainerStyle Style

		public virtual unsafe string Version

		public virtual unsafe global::AdaptiveCards.Rendering.Xamarin.Android.ObjectModel.VerticalContentAlignment VerticalContentAlignment

		// Metadata.xml XPath method reference: path="/api/package[@name='io.adaptivecards.objectmodel']/class[@name='AdaptiveCard']/method[@name='DeserializeFromString' and count(parameter)=2 and parameter[1][@type='java.lang.String'] and parameter[2][@type='java.lang.String']]"
		[Register ("DeserializeFromString", "(Ljava/lang/String;Ljava/lang/String;)Lio/adaptivecards/objectmodel/ParseResult;", "")]
		public static unsafe global::AdaptiveCards.Rendering.Xamarin.Android.ObjectModel.ParseResult DeserializeFromString (string jsonString, string rendererVersion)

		// Metadata.xml XPath method reference: path="/api/package[@name='io.adaptivecards.objectmodel']/class[@name='AdaptiveCard']/method[@name='DeserializeFromString' and count(parameter)=3 and parameter[1][@type='java.lang.String'] and parameter[2][@type='java.lang.String'] and parameter[3][@type='io.adaptivecards.objectmodel.ParseContext']]"
		[Register ("DeserializeFromString", "(Ljava/lang/String;Ljava/lang/String;Lio/adaptivecards/objectmodel/ParseContext;)Lio/adaptivecards/objectmodel/ParseResult;", "")]
		public static unsafe global::AdaptiveCards.Rendering.Xamarin.Android.ObjectModel.ParseResult DeserializeFromString (string jsonString, string rendererVersion, global::AdaptiveCards.Rendering.Xamarin.Android.ObjectModel.ParseContext context)

		// Metadata.xml XPath method reference: path="/api/package[@name='io.adaptivecards.objectmodel']/class[@name='AdaptiveCard']/method[@name='MakeFallbackTextCard' and count(parameter)=3 and parameter[1][@type='java.lang.String'] and parameter[2][@type='java.lang.String'] and parameter[3][@type='java.lang.String']]"
		[Register ("MakeFallbackTextCard", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)Lio/adaptivecards/objectmodel/AdaptiveCard;", "")]
		public static unsafe global::AdaptiveCards.Rendering.Xamarin.Android.ObjectModel.AdaptiveCard MakeFallbackTextCard (string fallbackText, string language, string speak)

		// Metadata.xml XPath method reference: path="/api/package[@name='io.adaptivecards.objectmodel']/class[@name='AdaptiveCard']/method[@name='Serialize' and count(parameter)=0]"
		[Register ("Serialize", "()Ljava/lang/String;", "GetSerializeHandler")]
		public virtual unsafe string Serialize ()

		// Metadata.xml XPath method reference: path="/api/package[@name='io.adaptivecards.objectmodel']/class[@name='AdaptiveCard']/method[@name='SerializeToJsonValue' and count(parameter)=0]"
		[Register ("SerializeToJsonValue", "()Lio/adaptivecards/objectmodel/JsonValue;", "GetSerializeToJsonValueHandler")]
		public virtual unsafe global::AdaptiveCards.Rendering.Xamarin.Android.ObjectModel.JsonValue SerializeToJsonValue ()

		// Metadata.xml XPath method reference: path="/api/package[@name='io.adaptivecards.objectmodel']/class[@name='AdaptiveCard']/method[@name='delete' and count(parameter)=0]"
		[Register ("delete", "()V", "GetDeleteHandler")]
		public virtual unsafe void Delete ()

		// Metadata.xml XPath method reference: path="/api/package[@name='io.adaptivecards.objectmodel']/class[@name='AdaptiveCard']/method[@name='getCPtr' and count(parameter)=1 and parameter[1][@type='io.adaptivecards.objectmodel.AdaptiveCard']]"
		[Register ("getCPtr", "(Lio/adaptivecards/objectmodel/AdaptiveCard;)J", "")]
		protected static unsafe long GetCPtr (global::AdaptiveCards.Rendering.Xamarin.Android.ObjectModel.AdaptiveCard obj)
#pragma warning restore 0169

		// Metadata.xml XPath method reference: path="/api/package[@name='io.adaptivecards.objectmodel']/class[@name='AdaptiveCard']/method[@name='swigSetCMemOwn' and count(parameter)=1 and parameter[1][@type='boolean']]"
		[Register ("swigSetCMemOwn", "(Z)V", "GetSwigSetCMemOwn_ZHandler")]
		protected virtual unsafe void SwigSetCMemOwn (bool own)

	}
}

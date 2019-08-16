using System;
using ObjCRuntime;
using Foundation;


namespace AdaptiveCards.Rendering.Xamarin.iOS
{
	[Native]
	public enum ACRParseWarningStatusCode : long
	{
		UnknownElementType = 0,
		UnknownPropertyOnElement,
		UnknownEnumValue,
		NoRendererForType,
		InteractivityNotSupported,
		MaxActionsExceeded,
		AssetLoadFailed,
		UnsupportedSchemaVersion
	}

	[Native]
	public enum ACRActionType : long
	{
		ShowCard = 1,
		Submit,
		OpenUrl,
        ToggleVisibility,
        UnknownAction
	}

	[Native]
	public enum ACRCardElementType : long
	{
		Unsupported = 0,
		AdaptiveCard,
		TextBlock,
		Image,
		Container,
		Column,
		ColumnSet,
		FactSet,
		Fact,
		ImageSet,
		ChoiceInput,
		ChoiceSetInput,
		DateInput,
		NumberInput,
		TextInput,
		TimeInput,
		ToggleInput,
		Custom,
		Unknown
	}

	[Native]
	public enum ACRContainerStyle : long
	{
		None,
		Default,
		Emphasis
	}

	[Native]
	public enum ACRInputError : long
	{
		ValueMissing,
		LessThanMin,
		GreaterThanMax,
		LessThanMinDate,
		GreaterThanMaxDate
	}
}

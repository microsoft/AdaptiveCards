export const Size = Object.freeze({
	Auto: 0,
	Stretch: 1,
	Small: 2,
	Medium: 3,
	Large: 4
});

export const SizeUnit = Object.freeze({
	Weight: 0,
	Pixel: 1
});

export const TextSize = Object.freeze({
	Small: 0,
	Default: 1,
	Medium: 2,
	Large: 3,
	ExtraLarge: 4
});

export const Spacing = Object.freeze({
	None: 0,
	Small: 1,
	Default: 2,
	Medium: 3,
	Large: 4,
	ExtraLarge: 5,
	Padding: 6
});

export const TextWeight = Object.freeze({
	Lighter: 0,
	Default: 1,
	Bolder: 2
});

export const TextColor = Object.freeze({
	Default: 0,
	Dark: 1,
	Light: 2,
	Accent: 3,
	Good: 4,
	Warning: 5,
	Attention: 6
});

export const HorizontalAlignment = Object.freeze({
	Left: 0,
	Center: 1,
	Right: 2
});

export const VerticalAlignment = Object.freeze({
	Top: 0,
	Center: 1,
	Bottom: 2
});

export const ActionAlignment = Object.freeze({
	Left: 0,
	Center: 1,
	Right: 2,
	Stretch: 3
});

export const ImageStyle = Object.freeze({
	Default: 0,
	Person: 1
});

export const ShowCardActionMode = Object.freeze({
	Inline: 0,
	Popup: 1
});

export const Orientation = Object.freeze({
	Horizontal: 0,
	Vertical: 1
});

export const BackgroundImageMode = Object.freeze({
	Stretch: 0,
	Cover: 1, 
	RepeatHorizontally: 2,
	RepeatVertically: 3,
	Repeat: 4
});

export const ActionIconPlacement = Object.freeze({
	LeftOfTitle: 0,
	AboveTitle: 1
});

export const InputTextStyle = Object.freeze({
	Text: 0,
	Tel: 1,
	Url: 2,
	Email: 3,
	Number: 4
});

export const ContainerStyle = Object.freeze({
	Default: "default",
	Emphasis: "emphasis",
	Accent: "accent",
	Good: "good",
	Attention: "attention",
	Warning: "warning"
});

export const ValidationError = Object.freeze({
	Hint: "Hint",
	ActionTypeNotAllowed: "ActionTypeNotAllowed",
	CollectionCantBeEmpty: "CollectionCantBeEmpty",
	Deprecated: "Deprecated",
	ElementTypeNotAllowed: "ElementTypeNotAllowed",
	InteractivityNotAllowed: "InteractivityNotAllowed",
	InvalidPropertyValue: "InvalidPropertyValue",
	MissingCardType: "MissingCardType",
	PropertyCantBeNull: "PropertyCantBeNull",
	TooManyActions: "TooManyActions",
	UnknownActionType: "UnknownActionType",
	UnknownElementType: "UnknownElementType",
	UnsupportedCardVersion: "UnsupportedCardVersion"
});

export const ContainerFitStatus = Object.freeze({
	FullyInContainer: 0,
	Overflowing: 1,
	FullyOutOfContainer: 2
});

export const Height = Object.freeze({
	Auto: 0,
	Stretch: 1
});

export const ValidationNecessity = {
	Optional: 'Optional',
	Required: 'Required',
	RequiredWithVisualCue: 'RequiredWithVisualCue'
}

export const Sentiment = Object.freeze({
	Default: 0,
	Positive: 1,
	Destructive: 2
});

export const FontStyle = Object.freeze({
	Default: 0,
	Monospace: 1,
});

export const ElementType = Object.freeze({
	AdaptiveCard: 'AdaptiveCard',
	Container: 'Container',
	ColumnSet: 'ColumnSet',
	ImageSet: 'ImageSet',
	Column: 'Column',
	FactSet: 'FactSet',

	TextInput: 'Input.Text',
	NumberInput: 'Input.Number',
	ToggleInput: 'Input.Toggle',
	DateInput: 'Input.Date',
	TimeInput: 'Input.Time',
	ChoiceSetInput: 'Input.ChoiceSet',

	TextBlock: 'TextBlock',
	Media: 'Media',
	Image: 'Image',
	RichTextBlock: 'RichTextBlock',

	ActionShowCard: 'Action.ShowCard',
	ActionSubmit: 'Action.Submit',
	ActionOpenUrl: 'Action.OpenUrl',
	ActionToggleVisibility: 'Action.ToggleVisibility',
	ActionSet: 'ActionSet'
});

export const ThemeElement = Object.freeze({
	Input: "input",
	Button: "button",
	InputDate: "inputDate",
	InputTime: "inputTime",
	RadioButton: "radioButton",
	CheckBox: "checkBox",
	ChoiceSetTitle: "choiceSetTitle",
});
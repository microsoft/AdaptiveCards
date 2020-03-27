[Adaptive Cards Javascript SDK](../README.md) › ["card-elements"](_card_elements_.md)

# Module: "card-elements"

## Index

### Classes

* [Action](../classes/_card_elements_.action.md)
* [ActionSet](../classes/_card_elements_.actionset.md)
* [ActionTypeRegistry](../classes/_card_elements_.actiontyperegistry.md)
* [AdaptiveCard](../classes/_card_elements_.adaptivecard.md)
* [BackgroundImage](../classes/_card_elements_.backgroundimage.md)
* [BaseTextBlock](../classes/_card_elements_.basetextblock.md)
* [CardElement](../classes/_card_elements_.cardelement.md)
* [CardElementContainer](../classes/_card_elements_.cardelementcontainer.md)
* [CardObject](../classes/_card_elements_.cardobject.md)
* [Choice](../classes/_card_elements_.choice.md)
* [ChoiceSetInput](../classes/_card_elements_.choicesetinput.md)
* [Column](../classes/_card_elements_.column.md)
* [ColumnSet](../classes/_card_elements_.columnset.md)
* [Container](../classes/_card_elements_.container.md)
* [ContainerWithActions](../classes/_card_elements_.containerwithactions.md)
* [DateInput](../classes/_card_elements_.dateinput.md)
* [ElementTypeRegistry](../classes/_card_elements_.elementtyperegistry.md)
* [Fact](../classes/_card_elements_.fact.md)
* [FactSet](../classes/_card_elements_.factset.md)
* [HttpAction](../classes/_card_elements_.httpaction.md)
* [HttpHeader](../classes/_card_elements_.httpheader.md)
* [Image](../classes/_card_elements_.image.md)
* [ImageSet](../classes/_card_elements_.imageset.md)
* [Input](../classes/_card_elements_.input.md)
* [InputValidationOptions](../classes/_card_elements_.inputvalidationoptions.md)
* [Media](../classes/_card_elements_.media.md)
* [MediaSource](../classes/_card_elements_.mediasource.md)
* [NumberInput](../classes/_card_elements_.numberinput.md)
* [OpenUrlAction](../classes/_card_elements_.openurlaction.md)
* [RichTextBlock](../classes/_card_elements_.richtextblock.md)
* [SerializableObject](../classes/_card_elements_.serializableobject.md)
* [ShowCardAction](../classes/_card_elements_.showcardaction.md)
* [StylableCardElementContainer](../classes/_card_elements_.stylablecardelementcontainer.md)
* [SubmitAction](../classes/_card_elements_.submitaction.md)
* [TextBlock](../classes/_card_elements_.textblock.md)
* [TextInput](../classes/_card_elements_.textinput.md)
* [TextRun](../classes/_card_elements_.textrun.md)
* [TimeInput](../classes/_card_elements_.timeinput.md)
* [ToggleInput](../classes/_card_elements_.toggleinput.md)
* [ToggleVisibilityAction](../classes/_card_elements_.togglevisibilityaction.md)
* [TypeRegistry](../classes/_card_elements_.typeregistry.md)
* [ValidationFailure](../classes/_card_elements_.validationfailure.md)
* [ValidationResults](../classes/_card_elements_.validationresults.md)

### Interfaces

* [IMarkdownProcessingResult](../interfaces/_card_elements_.imarkdownprocessingresult.md)
* [ITypeRegistration](../interfaces/_card_elements_.ityperegistration.md)

### Type aliases

* [CardElementHeight](_card_elements_.md#cardelementheight)
* [ColumnWidth](_card_elements_.md#columnwidth)

### Functions

* [createActionInstance](_card_elements_.md#createactioninstance)
* [createElementInstance](_card_elements_.md#createelementinstance)

## Type aliases

###  CardElementHeight

Ƭ **CardElementHeight**: *"auto" | "stretch"*

___

###  ColumnWidth

Ƭ **ColumnWidth**: *[SizeAndUnit](../classes/_shared_.sizeandunit.md) | "auto" | "stretch"*

## Functions

###  createActionInstance

▸ **createActionInstance**(`parent`: [CardElement](../classes/_card_elements_.cardelement.md), `json`: any, `forbiddenActionTypes`: string[], `allowFallback`: boolean, `errors`: Array‹[IValidationError](../interfaces/_host_config_.ivalidationerror.md)›): *[Action](../classes/_card_elements_.action.md)*

Instantiates an [`Action`](../classes/_card_elements_.action.md) for a [`CardElement`](../classes/_card_elements_.cardelement.md)

**Parameters:**

Name | Type | Description |
------ | ------ | ------ |
`parent` | [CardElement](../classes/_card_elements_.cardelement.md) | The [`CardElement`](../classes/_card_elements_.cardelement.md) for which to create an [`Action`](../classes/_card_elements_.action.md) |
`json` | any | A json object containing [`Action`](../classes/_card_elements_.action.md) properties |
`forbiddenActionTypes` | string[] | A list of action types that are not allowed to be created |
`allowFallback` | boolean | Whether to allow element fallback to occur |
`errors` | Array‹[IValidationError](../interfaces/_host_config_.ivalidationerror.md)› | A list of validation errors encountered while parsing the action  |

**Returns:** *[Action](../classes/_card_elements_.action.md)*

___

###  createElementInstance

▸ **createElementInstance**(`parent`: [CardElement](../classes/_card_elements_.cardelement.md), `json`: any, `allowFallback`: boolean, `errors`: Array‹[IValidationError](../interfaces/_host_config_.ivalidationerror.md)›): *[CardElement](../classes/_card_elements_.cardelement.md)*

Instantiates a [`CardElement`](../classes/_card_elements_.cardelement.md)

**Parameters:**

Name | Type | Description |
------ | ------ | ------ |
`parent` | [CardElement](../classes/_card_elements_.cardelement.md) | The parent of this [`CardElement`](../classes/_card_elements_.cardelement.md) |
`json` | any | A json object containing [`CardElement`](../classes/_card_elements_.cardelement.md) properties |
`allowFallback` | boolean | Whether to allow element fallback to occur |
`errors` | Array‹[IValidationError](../interfaces/_host_config_.ivalidationerror.md)› | A list of validation errors encountered while parsing the action  |

**Returns:** *[CardElement](../classes/_card_elements_.cardelement.md)*

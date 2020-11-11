[Adaptive Cards Javascript SDK](../README.md) › [IInput](iinput.md)

# Interface: IInput

## Hierarchy

* [ICardElement](icardelement.md)

  ↳ **IInput**

## Implemented by

* [ChoiceSetInput](../classes/choicesetinput.md)
* [DateInput](../classes/dateinput.md)
* [Input](../classes/input.md)
* [NumberInput](../classes/numberinput.md)
* [TextInput](../classes/textinput.md)
* [TimeInput](../classes/timeinput.md)
* [ToggleInput](../classes/toggleinput.md)

## Indexable

* \[ **propName**: *string*\]: any

## Index

### Properties

* [height](iinput.md#optional-height)
* [horizontalAlignment](iinput.md#optional-horizontalalignment)
* [id](iinput.md#optional-id)
* [separator](iinput.md#optional-separator)
* [spacing](iinput.md#optional-spacing)
* [speak](iinput.md#optional-speak)
* [value](iinput.md#optional-value)

### Methods

* [validateValue](iinput.md#validatevalue)

## Properties

### `Optional` height

• **height**? : *"auto" | "stretch"*

*Inherited from [ICardElement](icardelement.md).[height](icardelement.md#optional-height)*

___

### `Optional` horizontalAlignment

• **horizontalAlignment**? : *[HorizontalAlignment](../enums/horizontalalignment.md)*

*Inherited from [ICardElement](icardelement.md).[horizontalAlignment](icardelement.md#optional-horizontalalignment)*

___

### `Optional` id

• **id**? : *string*

*Overrides [ICardElement](icardelement.md).[id](icardelement.md#optional-id)*

___

### `Optional` separator

• **separator**? : *undefined | false | true*

*Inherited from [ICardElement](icardelement.md).[separator](icardelement.md#optional-separator)*

___

### `Optional` spacing

• **spacing**? : *[Spacing](../enums/spacing.md)*

*Inherited from [ICardElement](icardelement.md).[spacing](icardelement.md#optional-spacing)*

___

### `Optional` speak

• **speak**? : *undefined | string*

*Inherited from [ICardElement](icardelement.md).[speak](icardelement.md#optional-speak)*

___

### `Optional` value

• **value**? : *undefined | string*

## Methods

###  validateValue

▸ **validateValue**(): *boolean*

**Returns:** *boolean*

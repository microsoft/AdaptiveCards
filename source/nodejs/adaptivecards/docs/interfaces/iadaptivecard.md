[Adaptive Cards Javascript SDK](../README.md) › [IAdaptiveCard](iadaptivecard.md)

# Interface: IAdaptiveCard

## Hierarchy

* [ICardElement](icardelement.md)

  ↳ **IAdaptiveCard**

## Indexable

* \[ **propName**: *string*\]: any

## Index

### Properties

* [actions](iadaptivecard.md#optional-actions)
* [backgroundImage](iadaptivecard.md#optional-backgroundimage)
* [body](iadaptivecard.md#optional-body)
* [height](iadaptivecard.md#optional-height)
* [horizontalAlignment](iadaptivecard.md#optional-horizontalalignment)
* [id](iadaptivecard.md#optional-id)
* [separator](iadaptivecard.md#optional-separator)
* [spacing](iadaptivecard.md#optional-spacing)
* [speak](iadaptivecard.md#optional-speak)
* [type](iadaptivecard.md#type)
* [version](iadaptivecard.md#optional-version)

## Properties

### `Optional` actions

• **actions**? : *ISubmitAction | IOpenUrlAction | IShowCardAction[]*

___

### `Optional` backgroundImage

• **backgroundImage**? : *IBackgroundImage | string*

___

### `Optional` body

• **body**? : *ITextBlock | IImage | IImageSet | IFactSet | IColumnSet | IContainer[]*

___

### `Optional` height

• **height**? : *"auto" | "stretch"*

*Inherited from [IAdaptiveCard](iadaptivecard.md).[height](iadaptivecard.md#optional-height)*

___

### `Optional` horizontalAlignment

• **horizontalAlignment**? : *[HorizontalAlignment](../enums/horizontalalignment.md)*

*Inherited from [IAdaptiveCard](iadaptivecard.md).[horizontalAlignment](iadaptivecard.md#optional-horizontalalignment)*

___

### `Optional` id

• **id**? : *undefined | string*

*Inherited from [IAdaptiveCard](iadaptivecard.md).[id](iadaptivecard.md#optional-id)*

___

### `Optional` separator

• **separator**? : *undefined | false | true*

*Inherited from [IAdaptiveCard](iadaptivecard.md).[separator](iadaptivecard.md#optional-separator)*

___

### `Optional` spacing

• **spacing**? : *[Spacing](../enums/spacing.md)*

*Inherited from [IAdaptiveCard](iadaptivecard.md).[spacing](iadaptivecard.md#optional-spacing)*

___

### `Optional` speak

• **speak**? : *undefined | string*

*Overrides [ICardElement](icardelement.md).[speak](icardelement.md#optional-speak)*

___

###  type

• **type**: *"AdaptiveCard"*

___

### `Optional` version

• **version**? : *IVersion | string*

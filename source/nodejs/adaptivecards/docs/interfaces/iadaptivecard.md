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

*Defined in [schema.ts:170](https://github.com/microsoft/AdaptiveCards/blob/8588bd5ad/source/nodejs/adaptivecards/src/schema.ts#L170)*

___

### `Optional` backgroundImage

• **backgroundImage**? : *IBackgroundImage | string*

*Defined in [schema.ts:168](https://github.com/microsoft/AdaptiveCards/blob/8588bd5ad/source/nodejs/adaptivecards/src/schema.ts#L168)*

___

### `Optional` body

• **body**? : *ITextBlock | IImage | IImageSet | IFactSet | IColumnSet | IContainer[]*

*Defined in [schema.ts:169](https://github.com/microsoft/AdaptiveCards/blob/8588bd5ad/source/nodejs/adaptivecards/src/schema.ts#L169)*

___

### `Optional` height

• **height**? : *"auto" | "stretch"*

*Inherited from [IAdaptiveCard](iadaptivecard.md).[height](iadaptivecard.md#optional-height)*

*Defined in [schema.ts:39](https://github.com/microsoft/AdaptiveCards/blob/8588bd5ad/source/nodejs/adaptivecards/src/schema.ts#L39)*

___

### `Optional` horizontalAlignment

• **horizontalAlignment**? : *[HorizontalAlignment](../enums/horizontalalignment.md)*

*Inherited from [IAdaptiveCard](iadaptivecard.md).[horizontalAlignment](iadaptivecard.md#optional-horizontalalignment)*

*Defined in [schema.ts:36](https://github.com/microsoft/AdaptiveCards/blob/8588bd5ad/source/nodejs/adaptivecards/src/schema.ts#L36)*

___

### `Optional` id

• **id**? : *undefined | string*

*Inherited from [IAdaptiveCard](iadaptivecard.md).[id](iadaptivecard.md#optional-id)*

*Defined in [schema.ts:34](https://github.com/microsoft/AdaptiveCards/blob/8588bd5ad/source/nodejs/adaptivecards/src/schema.ts#L34)*

___

### `Optional` separator

• **separator**? : *undefined | false | true*

*Inherited from [IAdaptiveCard](iadaptivecard.md).[separator](iadaptivecard.md#optional-separator)*

*Defined in [schema.ts:38](https://github.com/microsoft/AdaptiveCards/blob/8588bd5ad/source/nodejs/adaptivecards/src/schema.ts#L38)*

___

### `Optional` spacing

• **spacing**? : *[Spacing](../enums/spacing.md)*

*Inherited from [IAdaptiveCard](iadaptivecard.md).[spacing](iadaptivecard.md#optional-spacing)*

*Defined in [schema.ts:37](https://github.com/microsoft/AdaptiveCards/blob/8588bd5ad/source/nodejs/adaptivecards/src/schema.ts#L37)*

___

### `Optional` speak

• **speak**? : *undefined | string*

*Overrides [ICardElement](icardelement.md).[speak](icardelement.md#optional-speak)*

*Defined in [schema.ts:171](https://github.com/microsoft/AdaptiveCards/blob/8588bd5ad/source/nodejs/adaptivecards/src/schema.ts#L171)*

___

###  type

• **type**: *"AdaptiveCard"*

*Defined in [schema.ts:166](https://github.com/microsoft/AdaptiveCards/blob/8588bd5ad/source/nodejs/adaptivecards/src/schema.ts#L166)*

___

### `Optional` version

• **version**? : *IVersion | string*

*Defined in [schema.ts:167](https://github.com/microsoft/AdaptiveCards/blob/8588bd5ad/source/nodejs/adaptivecards/src/schema.ts#L167)*

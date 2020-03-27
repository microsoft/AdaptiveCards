[Adaptive Cards Javascript SDK](../README.md) › ["schema"](../modules/_schema_.md) › [IAdaptiveCard](_schema_.iadaptivecard.md)

# Interface: IAdaptiveCard

## Hierarchy

* [ICardElement](_schema_.icardelement.md)

  ↳ **IAdaptiveCard**

## Indexable

* \[ **propName**: *string*\]: any

## Index

### Properties

* [actions](_schema_.iadaptivecard.md#optional-actions)
* [backgroundImage](_schema_.iadaptivecard.md#optional-backgroundimage)
* [body](_schema_.iadaptivecard.md#optional-body)
* [height](_schema_.iadaptivecard.md#optional-height)
* [horizontalAlignment](_schema_.iadaptivecard.md#optional-horizontalalignment)
* [id](_schema_.iadaptivecard.md#optional-id)
* [separator](_schema_.iadaptivecard.md#optional-separator)
* [spacing](_schema_.iadaptivecard.md#optional-spacing)
* [speak](_schema_.iadaptivecard.md#optional-speak)
* [type](_schema_.iadaptivecard.md#type)
* [version](_schema_.iadaptivecard.md#optional-version)

## Properties

### `Optional` actions

• **actions**? : *[ISubmitAction](_schema_.isubmitaction.md) | [IOpenUrlAction](_schema_.iopenurlaction.md) | [IShowCardAction](_schema_.ishowcardaction.md)[]*

___

### `Optional` backgroundImage

• **backgroundImage**? : *[IBackgroundImage](_schema_.ibackgroundimage.md) | string*

___

### `Optional` body

• **body**? : *[IImage](_schema_.iimage.md) | [ITextBlock](_schema_.itextblock.md) | [IImageSet](_schema_.iimageset.md) | [IFactSet](_schema_.ifactset.md) | [IColumnSet](_schema_.icolumnset.md) | [IContainer](_schema_.icontainer.md)[]*

___

### `Optional` height

• **height**? : *"auto" | "stretch"*

*Inherited from [ICardElement](_schema_.icardelement.md).[height](_schema_.icardelement.md#optional-height)*

___

### `Optional` horizontalAlignment

• **horizontalAlignment**? : *[HorizontalAlignment](../modules/_schema_.md#horizontalalignment)*

*Inherited from [ICardElement](_schema_.icardelement.md).[horizontalAlignment](_schema_.icardelement.md#optional-horizontalalignment)*

___

### `Optional` id

• **id**? : *string*

*Inherited from [ICardElement](_schema_.icardelement.md).[id](_schema_.icardelement.md#optional-id)*

___

### `Optional` separator

• **separator**? : *boolean*

*Inherited from [ICardElement](_schema_.icardelement.md).[separator](_schema_.icardelement.md#optional-separator)*

___

### `Optional` spacing

• **spacing**? : *[Spacing](../modules/_schema_.md#spacing)*

*Inherited from [ICardElement](_schema_.icardelement.md).[spacing](_schema_.icardelement.md#optional-spacing)*

___

### `Optional` speak

• **speak**? : *string*

*Overrides [ICardElement](_schema_.icardelement.md).[speak](_schema_.icardelement.md#optional-speak)*

___

###  type

• **type**: *"AdaptiveCard"*

___

### `Optional` version

• **version**? : *[IVersion](_schema_.iversion.md) | string*

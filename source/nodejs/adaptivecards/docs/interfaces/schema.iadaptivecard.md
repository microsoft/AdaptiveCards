[Adaptive Cards Javascript SDK](../README.md) / [schema](../modules/schema.md) / IAdaptiveCard

# Interface: IAdaptiveCard

[schema](../modules/schema.md).IAdaptiveCard

## Hierarchy

* [*ICardElement*](schema.icardelement.md)

  ↳ **IAdaptiveCard**

## Table of contents

### Properties

- [actions](schema.iadaptivecard.md#actions)
- [backgroundImage](schema.iadaptivecard.md#backgroundimage)
- [body](schema.iadaptivecard.md#body)
- [height](schema.iadaptivecard.md#height)
- [horizontalAlignment](schema.iadaptivecard.md#horizontalalignment)
- [id](schema.iadaptivecard.md#id)
- [separator](schema.iadaptivecard.md#separator)
- [spacing](schema.iadaptivecard.md#spacing)
- [speak](schema.iadaptivecard.md#speak)
- [type](schema.iadaptivecard.md#type)
- [version](schema.iadaptivecard.md#version)

## Properties

### actions

• `Optional` **actions**: *undefined* \| ([*ISubmitAction*](schema.isubmitaction.md) \| [*IOpenUrlAction*](schema.iopenurlaction.md) \| [*IShowCardAction*](schema.ishowcardaction.md))[]

Defined in: [schema.ts:170](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/schema.ts#L170)

___

### backgroundImage

• `Optional` **backgroundImage**: *undefined* \| *string* \| [*IBackgroundImage*](schema.ibackgroundimage.md)

Defined in: [schema.ts:168](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/schema.ts#L168)

___

### body

• `Optional` **body**: *undefined* \| ([*ITextBlock*](schema.itextblock.md) \| [*IContainer*](schema.icontainer.md) \| [*IColumnSet*](schema.icolumnset.md) \| [*IFactSet*](schema.ifactset.md) \| [*IImage*](schema.iimage.md) \| [*IImageSet*](schema.iimageset.md))[]

Defined in: [schema.ts:169](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/schema.ts#L169)

___

### height

• `Optional` **height**: *undefined* \| *auto* \| *stretch*

Inherited from: [ICardElement](schema.icardelement.md).[height](schema.icardelement.md#height)

Defined in: [schema.ts:39](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/schema.ts#L39)

___

### horizontalAlignment

• `Optional` **horizontalAlignment**: *undefined* \| *left* \| *center* \| *right*

Inherited from: [ICardElement](schema.icardelement.md).[horizontalAlignment](schema.icardelement.md#horizontalalignment)

Defined in: [schema.ts:36](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/schema.ts#L36)

___

### id

• `Optional` **id**: *undefined* \| *string*

Inherited from: [ICardElement](schema.icardelement.md).[id](schema.icardelement.md#id)

Defined in: [schema.ts:34](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/schema.ts#L34)

___

### separator

• `Optional` **separator**: *undefined* \| *boolean*

Inherited from: [ICardElement](schema.icardelement.md).[separator](schema.icardelement.md#separator)

Defined in: [schema.ts:38](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/schema.ts#L38)

___

### spacing

• `Optional` **spacing**: *undefined* \| *default* \| *none* \| *small* \| *medium* \| *large* \| *extraLarge* \| *padding*

Inherited from: [ICardElement](schema.icardelement.md).[spacing](schema.icardelement.md#spacing)

Defined in: [schema.ts:37](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/schema.ts#L37)

___

### speak

• `Optional` **speak**: *undefined* \| *string*

Overrides: [ICardElement](schema.icardelement.md).[speak](schema.icardelement.md#speak)

Defined in: [schema.ts:171](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/schema.ts#L171)

___

### type

• **type**: *AdaptiveCard*

Defined in: [schema.ts:166](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/schema.ts#L166)

___

### version

• `Optional` **version**: *undefined* \| *string* \| [*IVersion*](schema.iversion.md)

Defined in: [schema.ts:167](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/schema.ts#L167)

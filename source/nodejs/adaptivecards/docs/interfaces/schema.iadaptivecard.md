[Adaptive Cards Javascript SDK](../README.md) / [schema](../modules/schema.md) / IAdaptiveCard

# Interface: IAdaptiveCard

[schema](../modules/schema.md).IAdaptiveCard

## Hierarchy

- [_ICardElement_](schema.icardelement.md)

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

• `Optional` **actions**: _undefined_ \| ([_ISubmitAction_](schema.isubmitaction.md) \| [_IOpenUrlAction_](schema.iopenurlaction.md) \| [_IShowCardAction_](schema.ishowcardaction.md))[]

Defined in: [schema.ts:170](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/schema.ts#L170)

---

### backgroundImage

• `Optional` **backgroundImage**: _undefined_ \| _string_ \| [_IBackgroundImage_](schema.ibackgroundimage.md)

Defined in: [schema.ts:168](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/schema.ts#L168)

---

### body

• `Optional` **body**: _undefined_ \| ([_ITextBlock_](schema.itextblock.md) \| [_IContainer_](schema.icontainer.md) \| [_IColumnSet_](schema.icolumnset.md) \| [_IFactSet_](schema.ifactset.md) \| [_IImage_](schema.iimage.md) \| [_IImageSet_](schema.iimageset.md))[]

Defined in: [schema.ts:169](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/schema.ts#L169)

---

### height

• `Optional` **height**: _undefined_ \| _auto_ \| _stretch_

Inherited from: [ICardElement](schema.icardelement.md).[height](schema.icardelement.md#height)

Defined in: [schema.ts:39](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/schema.ts#L39)

---

### horizontalAlignment

• `Optional` **horizontalAlignment**: _undefined_ \| _left_ \| _center_ \| _right_

Inherited from: [ICardElement](schema.icardelement.md).[horizontalAlignment](schema.icardelement.md#horizontalalignment)

Defined in: [schema.ts:36](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/schema.ts#L36)

---

### id

• `Optional` **id**: _undefined_ \| _string_

Inherited from: [ICardElement](schema.icardelement.md).[id](schema.icardelement.md#id)

Defined in: [schema.ts:34](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/schema.ts#L34)

---

### separator

• `Optional` **separator**: _undefined_ \| _boolean_

Inherited from: [ICardElement](schema.icardelement.md).[separator](schema.icardelement.md#separator)

Defined in: [schema.ts:38](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/schema.ts#L38)

---

### spacing

• `Optional` **spacing**: _undefined_ \| _default_ \| _none_ \| _small_ \| _medium_ \| _large_ \| _extraLarge_ \| _padding_

Inherited from: [ICardElement](schema.icardelement.md).[spacing](schema.icardelement.md#spacing)

Defined in: [schema.ts:37](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/schema.ts#L37)

---

### speak

• `Optional` **speak**: _undefined_ \| _string_

Overrides: [ICardElement](schema.icardelement.md).[speak](schema.icardelement.md#speak)

Defined in: [schema.ts:171](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/schema.ts#L171)

---

### type

• **type**: _AdaptiveCard_

Defined in: [schema.ts:166](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/schema.ts#L166)

---

### version

• `Optional` **version**: _undefined_ \| _string_ \| [_IVersion_](schema.iversion.md)

Defined in: [schema.ts:167](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/schema.ts#L167)

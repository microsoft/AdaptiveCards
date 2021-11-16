[Adaptive Cards Javascript SDK](../README.md) / [adaptivecards](../modules/adaptivecards.md) / SerializationContext

# Class: SerializationContext

[adaptivecards](../modules/adaptivecards.md).SerializationContext

## Hierarchy

- [_BaseSerializationContext_](serialization.baseserializationcontext.md)

  ↳ **SerializationContext**

## Table of contents

### Constructors

- [constructor](adaptivecards.serializationcontext.md#constructor)

### Properties

- [onParseAction](adaptivecards.serializationcontext.md#onparseaction)
- [onParseElement](adaptivecards.serializationcontext.md#onparseelement)
- [targetVersion](adaptivecards.serializationcontext.md#targetversion)
- [toJSONOriginalParam](adaptivecards.serializationcontext.md#tojsonoriginalparam)

### Accessors

- [actionRegistry](adaptivecards.serializationcontext.md#actionregistry)
- [elementRegistry](adaptivecards.serializationcontext.md#elementregistry)
- [eventCount](adaptivecards.serializationcontext.md#eventcount)

### Methods

- [cardObjectParsed](adaptivecards.serializationcontext.md#cardobjectparsed)
- [clearEvents](adaptivecards.serializationcontext.md#clearevents)
- [getEventAt](adaptivecards.serializationcontext.md#geteventat)
- [logEvent](adaptivecards.serializationcontext.md#logevent)
- [logParseEvent](adaptivecards.serializationcontext.md#logparseevent)
- [parseAction](adaptivecards.serializationcontext.md#parseaction)
- [parseCardObject](adaptivecards.serializationcontext.md#parsecardobject)
- [parseElement](adaptivecards.serializationcontext.md#parseelement)
- [serializeArray](adaptivecards.serializationcontext.md#serializearray)
- [serializeBool](adaptivecards.serializationcontext.md#serializebool)
- [serializeEnum](adaptivecards.serializationcontext.md#serializeenum)
- [serializeNumber](adaptivecards.serializationcontext.md#serializenumber)
- [serializeValue](adaptivecards.serializationcontext.md#serializevalue)
- [setActionRegistry](adaptivecards.serializationcontext.md#setactionregistry)
- [setElementRegistry](adaptivecards.serializationcontext.md#setelementregistry)

## Constructors

### constructor

\+ **new SerializationContext**(`targetVersion?`: [_Version_](serialization.version.md)): [_SerializationContext_](card_elements.serializationcontext.md)

#### Parameters:

| Name            | Type                                  |
| :-------------- | :------------------------------------ |
| `targetVersion` | [_Version_](serialization.version.md) |

**Returns:** [_SerializationContext_](card_elements.serializationcontext.md)

Inherited from: [BaseSerializationContext](serialization.baseserializationcontext.md)

Defined in: [serialization.ts:248](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L248)

## Properties

### onParseAction

• `Optional` **onParseAction**: _undefined_ \| (`action`: [_Action_](card_elements.action.md), `source`: _any_, `context`: [_SerializationContext_](card_elements.serializationcontext.md)) => _void_

Defined in: [card-elements.ts:6815](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L6815)

---

### onParseElement

• `Optional` **onParseElement**: _undefined_ \| (`element`: [_CardElement_](card_elements.cardelement.md), `source`: _any_, `context`: [_SerializationContext_](card_elements.serializationcontext.md)) => _void_

Defined in: [card-elements.ts:6816](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L6816)

---

### targetVersion

• **targetVersion**: [_Version_](serialization.version.md)

Inherited from: [BaseSerializationContext](serialization.baseserializationcontext.md).[targetVersion](serialization.baseserializationcontext.md#targetversion)

---

### toJSONOriginalParam

• **toJSONOriginalParam**: _any_

Inherited from: [BaseSerializationContext](serialization.baseserializationcontext.md).[toJSONOriginalParam](serialization.baseserializationcontext.md#tojsonoriginalparam)

Defined in: [serialization.ts:132](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L132)

## Accessors

### actionRegistry

• get **actionRegistry**(): [_CardObjectRegistry_](registry.cardobjectregistry.md)<[_Action_](card_elements.action.md)\>

**Returns:** [_CardObjectRegistry_](registry.cardobjectregistry.md)<[_Action_](card_elements.action.md)\>

Defined in: [card-elements.ts:6904](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L6904)

---

### elementRegistry

• get **elementRegistry**(): [_CardObjectRegistry_](registry.cardobjectregistry.md)<[_CardElement_](card_elements.cardelement.md)\>

**Returns:** [_CardObjectRegistry_](registry.cardobjectregistry.md)<[_CardElement_](card_elements.cardelement.md)\>

Defined in: [card-elements.ts:6894](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L6894)

---

### eventCount

• get **eventCount**(): _number_

**Returns:** _number_

Defined in: [serialization.ts:252](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L252)

## Methods

### cardObjectParsed

▸ `Protected`**cardObjectParsed**(`o`: [_SerializableObject_](serialization.serializableobject.md), `source`: _any_): _void_

#### Parameters:

| Name     | Type                                                        |
| :------- | :---------------------------------------------------------- |
| `o`      | [_SerializableObject_](serialization.serializableobject.md) |
| `source` | _any_                                                       |

**Returns:** _void_

Defined in: [card-elements.ts:6806](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L6806)

---

### clearEvents

▸ **clearEvents**(): _void_

**Returns:** _void_

Inherited from: [BaseSerializationContext](serialization.baseserializationcontext.md)

Defined in: [serialization.ts:223](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L223)

---

### getEventAt

▸ **getEventAt**(`index`: _number_): [_IValidationEvent_](../interfaces/serialization.ivalidationevent.md)

#### Parameters:

| Name    | Type     |
| :------ | :------- |
| `index` | _number_ |

**Returns:** [_IValidationEvent_](../interfaces/serialization.ivalidationevent.md)

Inherited from: [BaseSerializationContext](serialization.baseserializationcontext.md)

Defined in: [serialization.ts:246](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L246)

---

### logEvent

▸ **logEvent**(`source`: _undefined_ \| [_SerializableObject_](serialization.serializableobject.md), `phase`: [_ValidationPhase_](../enums/enums.validationphase.md), `event`: [_ValidationEvent_](../enums/enums.validationevent.md), `message`: _string_): _void_

#### Parameters:

| Name      | Type                                                                       |
| :-------- | :------------------------------------------------------------------------- |
| `source`  | _undefined_ \| [_SerializableObject_](serialization.serializableobject.md) |
| `phase`   | [_ValidationPhase_](../enums/enums.validationphase.md)                     |
| `event`   | [_ValidationEvent_](../enums/enums.validationevent.md)                     |
| `message` | _string_                                                                   |

**Returns:** _void_

Inherited from: [BaseSerializationContext](serialization.baseserializationcontext.md)

Defined in: [serialization.ts:227](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L227)

---

### logParseEvent

▸ **logParseEvent**(`source`: _undefined_ \| [_SerializableObject_](serialization.serializableobject.md), `event`: [_ValidationEvent_](../enums/enums.validationevent.md), `message`: _string_): _void_

#### Parameters:

| Name      | Type                                                                       |
| :-------- | :------------------------------------------------------------------------- |
| `source`  | _undefined_ \| [_SerializableObject_](serialization.serializableobject.md) |
| `event`   | [_ValidationEvent_](../enums/enums.validationevent.md)                     |
| `message` | _string_                                                                   |

**Returns:** _void_

Inherited from: [BaseSerializationContext](serialization.baseserializationcontext.md)

Defined in: [serialization.ts:242](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L242)

---

### parseAction

▸ **parseAction**(`parent`: [_CardElement_](card_elements.cardelement.md), `source`: _any_, `forbiddenActionTypes`: _string_[], `allowFallback`: _boolean_): _undefined_ \| [_Action_](card_elements.action.md)

#### Parameters:

| Name                   | Type                                          |
| :--------------------- | :-------------------------------------------- |
| `parent`               | [_CardElement_](card_elements.cardelement.md) |
| `source`               | _any_                                         |
| `forbiddenActionTypes` | _string_[]                                    |
| `allowFallback`        | _boolean_                                     |

**Returns:** _undefined_ \| [_Action_](card_elements.action.md)

Defined in: [card-elements.ts:6865](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L6865)

---

### parseCardObject

▸ **parseCardObject**<T\>(`parent`: _undefined_ \| [_CardElement_](card_elements.cardelement.md), `source`: _any_, `forbiddenTypeNames`: _string_[], `allowFallback`: _boolean_, `createInstanceCallback`: (`typeName`: _string_) => _undefined_ \| T, `logParseEvent`: (`typeName`: _string_, `errorType`: TypeErrorType) => _void_): _undefined_ \| T

#### Type parameters:

| Name | Type                                          |
| :--- | :-------------------------------------------- |
| `T`  | [_CardObject_](card_object.cardobject.md)<T\> |

#### Parameters:

| Name                     | Type                                                         |
| :----------------------- | :----------------------------------------------------------- |
| `parent`                 | _undefined_ \| [_CardElement_](card_elements.cardelement.md) |
| `source`                 | _any_                                                        |
| `forbiddenTypeNames`     | _string_[]                                                   |
| `allowFallback`          | _boolean_                                                    |
| `createInstanceCallback` | (`typeName`: _string_) => _undefined_ \| T                   |
| `logParseEvent`          | (`typeName`: _string_, `errorType`: TypeErrorType) => _void_ |

**Returns:** _undefined_ \| T

Defined in: [card-elements.ts:6818](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L6818)

---

### parseElement

▸ **parseElement**(`parent`: _undefined_ \| [_CardElement_](card_elements.cardelement.md), `source`: _any_, `allowFallback`: _boolean_): _undefined_ \| [_CardElement_](card_elements.cardelement.md)

#### Parameters:

| Name            | Type                                                         |
| :-------------- | :----------------------------------------------------------- |
| `parent`        | _undefined_ \| [_CardElement_](card_elements.cardelement.md) |
| `source`        | _any_                                                        |
| `allowFallback` | _boolean_                                                    |

**Returns:** _undefined_ \| [_CardElement_](card_elements.cardelement.md)

Defined in: [card-elements.ts:6840](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L6840)

---

### serializeArray

▸ **serializeArray**(`target`: { [key: string]: _any_; }, `propertyName`: _string_, `propertyValue`: _undefined_ \| _any_[]): _void_

#### Parameters:

| Name            | Type                   |
| :-------------- | :--------------------- |
| `target`        | _object_               |
| `propertyName`  | _string_               |
| `propertyValue` | _undefined_ \| _any_[] |

**Returns:** _void_

Inherited from: [BaseSerializationContext](serialization.baseserializationcontext.md)

Defined in: [serialization.ts:190](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L190)

---

### serializeBool

▸ **serializeBool**(`target`: { [key: string]: _any_; }, `propertyName`: _string_, `propertyValue`: _undefined_ \| _boolean_, `defaultValue?`: _undefined_ \| _boolean_): _void_

#### Parameters:

| Name            | Type                     |
| :-------------- | :----------------------- |
| `target`        | _object_                 |
| `propertyName`  | _string_                 |
| `propertyValue` | _undefined_ \| _boolean_ |
| `defaultValue`  | _undefined_ \| _boolean_ |

**Returns:** _void_

Inherited from: [BaseSerializationContext](serialization.baseserializationcontext.md)

Defined in: [serialization.ts:145](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L145)

---

### serializeEnum

▸ **serializeEnum**(`enumType`: { [s: number]: _string_; }, `target`: { [key: string]: _any_; }, `propertyName`: _string_, `propertyValue`: _undefined_ \| _number_, `defaultValue?`: _undefined_ \| _number_): _void_

#### Parameters:

| Name            | Type                    |
| :-------------- | :---------------------- |
| `enumType`      | _object_                |
| `target`        | _object_                |
| `propertyName`  | _string_                |
| `propertyValue` | _undefined_ \| _number_ |
| `defaultValue`  | _undefined_ \| _number_ |

**Returns:** _void_

Inherited from: [BaseSerializationContext](serialization.baseserializationcontext.md)

Defined in: [serialization.ts:163](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L163)

---

### serializeNumber

▸ **serializeNumber**(`target`: { [key: string]: _any_; }, `propertyName`: _string_, `propertyValue`: _undefined_ \| _number_, `defaultValue?`: _undefined_ \| _number_): _void_

#### Parameters:

| Name            | Type                    |
| :-------------- | :---------------------- |
| `target`        | _object_                |
| `propertyName`  | _string_                |
| `propertyValue` | _undefined_ \| _number_ |
| `defaultValue`  | _undefined_ \| _number_ |

**Returns:** _void_

Inherited from: [BaseSerializationContext](serialization.baseserializationcontext.md)

Defined in: [serialization.ts:154](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L154)

---

### serializeValue

▸ **serializeValue**(`target`: { [key: string]: _any_; }, `propertyName`: _string_, `propertyValue`: _any_, `defaultValue?`: _any_): _void_

#### Parameters:

| Name            | Type     |
| :-------------- | :------- |
| `target`        | _object_ |
| `propertyName`  | _string_ |
| `propertyValue` | _any_    |
| `defaultValue`  | _any_    |

**Returns:** _void_

Inherited from: [BaseSerializationContext](serialization.baseserializationcontext.md)

Defined in: [serialization.ts:134](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L134)

---

### setActionRegistry

▸ **setActionRegistry**(`value`: _undefined_ \| [_CardObjectRegistry_](registry.cardobjectregistry.md)<[_Action_](card_elements.action.md)\>): _void_

#### Parameters:

| Name    | Type                                                                                                        |
| :------ | :---------------------------------------------------------------------------------------------------------- |
| `value` | _undefined_ \| [_CardObjectRegistry_](registry.cardobjectregistry.md)<[_Action_](card_elements.action.md)\> |

**Returns:** _void_

Defined in: [card-elements.ts:6910](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L6910)

---

### setElementRegistry

▸ **setElementRegistry**(`value`: _undefined_ \| [_CardObjectRegistry_](registry.cardobjectregistry.md)<[_CardElement_](card_elements.cardelement.md)\>): _void_

#### Parameters:

| Name    | Type                                                                                                                  |
| :------ | :-------------------------------------------------------------------------------------------------------------------- |
| `value` | _undefined_ \| [_CardObjectRegistry_](registry.cardobjectregistry.md)<[_CardElement_](card_elements.cardelement.md)\> |

**Returns:** _void_

Defined in: [card-elements.ts:6900](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L6900)

[Adaptive Cards Javascript SDK](../README.md) / [serialization](../modules/serialization.md) / BaseSerializationContext

# Class: BaseSerializationContext

[serialization](../modules/serialization.md).BaseSerializationContext

## Hierarchy

- **BaseSerializationContext**

  ↳ [_SerializationContext_](card_elements.serializationcontext.md)

  ↳ [_SerializationContext_](adaptivecards.serializationcontext.md)

## Table of contents

### Constructors

- [constructor](serialization.baseserializationcontext.md#constructor)

### Properties

- [targetVersion](serialization.baseserializationcontext.md#targetversion)
- [toJSONOriginalParam](serialization.baseserializationcontext.md#tojsonoriginalparam)

### Accessors

- [eventCount](serialization.baseserializationcontext.md#eventcount)

### Methods

- [clearEvents](serialization.baseserializationcontext.md#clearevents)
- [getEventAt](serialization.baseserializationcontext.md#geteventat)
- [logEvent](serialization.baseserializationcontext.md#logevent)
- [logParseEvent](serialization.baseserializationcontext.md#logparseevent)
- [serializeArray](serialization.baseserializationcontext.md#serializearray)
- [serializeBool](serialization.baseserializationcontext.md#serializebool)
- [serializeEnum](serialization.baseserializationcontext.md#serializeenum)
- [serializeNumber](serialization.baseserializationcontext.md#serializenumber)
- [serializeValue](serialization.baseserializationcontext.md#serializevalue)

## Constructors

### constructor

\+ **new BaseSerializationContext**(`targetVersion?`: [_Version_](serialization.version.md)): [_BaseSerializationContext_](serialization.baseserializationcontext.md)

#### Parameters:

| Name            | Type                                  |
| :-------------- | :------------------------------------ |
| `targetVersion` | [_Version_](serialization.version.md) |

**Returns:** [_BaseSerializationContext_](serialization.baseserializationcontext.md)

Defined in: [serialization.ts:248](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L248)

## Properties

### targetVersion

• **targetVersion**: [_Version_](serialization.version.md)

---

### toJSONOriginalParam

• **toJSONOriginalParam**: _any_

Defined in: [serialization.ts:132](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L132)

## Accessors

### eventCount

• get **eventCount**(): _number_

**Returns:** _number_

Defined in: [serialization.ts:252](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L252)

## Methods

### clearEvents

▸ **clearEvents**(): _void_

**Returns:** _void_

Defined in: [serialization.ts:223](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L223)

---

### getEventAt

▸ **getEventAt**(`index`: _number_): [_IValidationEvent_](../interfaces/serialization.ivalidationevent.md)

#### Parameters:

| Name    | Type     |
| :------ | :------- |
| `index` | _number_ |

**Returns:** [_IValidationEvent_](../interfaces/serialization.ivalidationevent.md)

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

Defined in: [serialization.ts:242](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L242)

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

Defined in: [serialization.ts:134](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L134)

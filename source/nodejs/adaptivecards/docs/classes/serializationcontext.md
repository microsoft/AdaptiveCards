[Adaptive Cards Javascript SDK](../README.md) › [SerializationContext](serializationcontext.md)

# Class: SerializationContext

## Hierarchy

- [BaseSerializationContext](baseserializationcontext.md)

  ↳ **SerializationContext**

## Index

### Constructors

- [constructor](serializationcontext.md#constructor)

### Properties

- [onParseAction](serializationcontext.md#optional-onparseaction)
- [onParseElement](serializationcontext.md#optional-onparseelement)
- [targetVersion](serializationcontext.md#targetversion)
- [toJSONOriginalParam](serializationcontext.md#tojsonoriginalparam)

### Accessors

- [actionRegistry](serializationcontext.md#actionregistry)
- [elementRegistry](serializationcontext.md#elementregistry)
- [eventCount](serializationcontext.md#eventcount)

### Methods

- [cardObjectParsed](serializationcontext.md#protected-cardobjectparsed)
- [clearEvents](serializationcontext.md#clearevents)
- [getEventAt](serializationcontext.md#geteventat)
- [logEvent](serializationcontext.md#logevent)
- [logParseEvent](serializationcontext.md#logparseevent)
- [parseAction](serializationcontext.md#parseaction)
- [parseCardObject](serializationcontext.md#parsecardobject)
- [parseElement](serializationcontext.md#parseelement)
- [serializeArray](serializationcontext.md#serializearray)
- [serializeEnum](serializationcontext.md#serializeenum)
- [serializeNumber](serializationcontext.md#serializenumber)
- [serializeValue](serializationcontext.md#serializevalue)
- [setActionRegistry](serializationcontext.md#setactionregistry)
- [setElementRegistry](serializationcontext.md#setelementregistry)
- [shouldSerialize](serializationcontext.md#shouldserialize)

## Constructors

### constructor

\+ **new SerializationContext**(`targetVersion`: [Version](version.md)): _[SerializationContext](serializationcontext.md)_

_Inherited from [BaseSerializationContext](baseserializationcontext.md).[constructor](baseserializationcontext.md#constructor)_

**Parameters:**

| Name            | Type                  | Default         |
| --------------- | --------------------- | --------------- |
| `targetVersion` | [Version](version.md) | Versions.latest |

**Returns:** _[SerializationContext](serializationcontext.md)_

## Properties

### `Optional` onParseAction

• **onParseAction**? : _undefined | function_

---

### `Optional` onParseElement

• **onParseElement**? : _undefined | function_

---

### targetVersion

• **targetVersion**: _[Version](version.md)_

_Inherited from [BaseSerializationContext](baseserializationcontext.md).[targetVersion](baseserializationcontext.md#targetversion)_

---

### toJSONOriginalParam

• **toJSONOriginalParam**: _any_

_Inherited from [BaseSerializationContext](baseserializationcontext.md).[toJSONOriginalParam](baseserializationcontext.md#tojsonoriginalparam)_

## Accessors

### actionRegistry

• **get actionRegistry**(): _[CardObjectRegistry](cardobjectregistry.md)‹[Action](action.md)›_

**Returns:** _[CardObjectRegistry](cardobjectregistry.md)‹[Action](action.md)›_

---

### elementRegistry

• **get elementRegistry**(): _[CardObjectRegistry](cardobjectregistry.md)‹[CardElement](cardelement.md)›_

**Returns:** _[CardObjectRegistry](cardobjectregistry.md)‹[CardElement](cardelement.md)›_

---

### eventCount

• **get eventCount**(): _number_

_Inherited from [BaseSerializationContext](baseserializationcontext.md).[eventCount](baseserializationcontext.md#eventcount)_

**Returns:** _number_

## Methods

### `Protected` cardObjectParsed

▸ **cardObjectParsed**(`o`: [SerializableObject](serializableobject.md), `source`: any): _void_

**Parameters:**

| Name     | Type                                        |
| -------- | ------------------------------------------- |
| `o`      | [SerializableObject](serializableobject.md) |
| `source` | any                                         |

**Returns:** _void_

---

### clearEvents

▸ **clearEvents**(): _void_

_Inherited from [BaseSerializationContext](baseserializationcontext.md).[clearEvents](baseserializationcontext.md#clearevents)_

**Returns:** _void_

---

### getEventAt

▸ **getEventAt**(`index`: number): _[IValidationEvent](../interfaces/ivalidationevent.md)_

_Inherited from [BaseSerializationContext](baseserializationcontext.md).[getEventAt](baseserializationcontext.md#geteventat)_

**Parameters:**

| Name    | Type   |
| ------- | ------ |
| `index` | number |

**Returns:** _[IValidationEvent](../interfaces/ivalidationevent.md)_

---

### logEvent

▸ **logEvent**(`source`: [SerializableObject](serializableobject.md) | undefined, `phase`: [ValidationPhase](../enums/validationphase.md), `event`: [ValidationEvent](../enums/validationevent.md), `message`: string): _void_

_Inherited from [BaseSerializationContext](baseserializationcontext.md).[logEvent](baseserializationcontext.md#logevent)_

**Parameters:**

| Name      | Type                                                         |
| --------- | ------------------------------------------------------------ |
| `source`  | [SerializableObject](serializableobject.md) &#124; undefined |
| `phase`   | [ValidationPhase](../enums/validationphase.md)               |
| `event`   | [ValidationEvent](../enums/validationevent.md)               |
| `message` | string                                                       |

**Returns:** _void_

---

### logParseEvent

▸ **logParseEvent**(`source`: [SerializableObject](serializableobject.md) | undefined, `event`: [ValidationEvent](../enums/validationevent.md), `message`: string): _void_

_Inherited from [BaseSerializationContext](baseserializationcontext.md).[logParseEvent](baseserializationcontext.md#logparseevent)_

**Parameters:**

| Name      | Type                                                         |
| --------- | ------------------------------------------------------------ |
| `source`  | [SerializableObject](serializableobject.md) &#124; undefined |
| `event`   | [ValidationEvent](../enums/validationevent.md)               |
| `message` | string                                                       |

**Returns:** _void_

---

### parseAction

▸ **parseAction**(`parent`: [CardElement](cardelement.md), `source`: any, `forbiddenActionTypes`: string[], `allowFallback`: boolean): _[Action](action.md) | undefined_

**Parameters:**

| Name                   | Type                          |
| ---------------------- | ----------------------------- |
| `parent`               | [CardElement](cardelement.md) |
| `source`               | any                           |
| `forbiddenActionTypes` | string[]                      |
| `allowFallback`        | boolean                       |

**Returns:** _[Action](action.md) | undefined_

---

### parseCardObject

▸ **parseCardObject**‹**T**›(`parent`: [CardElement](cardelement.md) | undefined, `source`: any, `forbiddenTypeNames`: string[], `allowFallback`: boolean, `createInstanceCallback`: function, `logParseEvent`: function): _T | undefined_

**Type parameters:**

▪ **T**: _[CardObject](cardobject.md)_

**Parameters:**

▪ **parent**: _[CardElement](cardelement.md) | undefined_

▪ **source**: _any_

▪ **forbiddenTypeNames**: _string[]_

▪ **allowFallback**: _boolean_

▪ **createInstanceCallback**: _function_

▸ (`typeName`: string): _T | undefined_

**Parameters:**

| Name       | Type   |
| ---------- | ------ |
| `typeName` | string |

▪ **logParseEvent**: _function_

▸ (`typeName`: string, `errorType`: [TypeErrorType](../enums/typeerrortype.md)): _void_

**Parameters:**

| Name        | Type                                       |
| ----------- | ------------------------------------------ |
| `typeName`  | string                                     |
| `errorType` | [TypeErrorType](../enums/typeerrortype.md) |

**Returns:** _T | undefined_

---

### parseElement

▸ **parseElement**(`parent`: [CardElement](cardelement.md) | undefined, `source`: any, `allowFallback`: boolean): _[CardElement](cardelement.md) | undefined_

**Parameters:**

| Name            | Type                                           |
| --------------- | ---------------------------------------------- |
| `parent`        | [CardElement](cardelement.md) &#124; undefined |
| `source`        | any                                            |
| `allowFallback` | boolean                                        |

**Returns:** _[CardElement](cardelement.md) | undefined_

---

### serializeArray

▸ **serializeArray**(`target`: object, `propertyName`: string, `propertyValue`: any[] | undefined): _void_

_Inherited from [BaseSerializationContext](baseserializationcontext.md).[serializeArray](baseserializationcontext.md#serializearray)_

**Parameters:**

| Name            | Type                   |
| --------------- | ---------------------- |
| `target`        | object                 |
| `propertyName`  | string                 |
| `propertyValue` | any[] &#124; undefined |

**Returns:** _void_

---

### serializeEnum

▸ **serializeEnum**(`enumType`: object, `target`: object, `propertyName`: string, `propertyValue`: number | undefined, `defaultValue`: number | undefined): _void_

_Inherited from [BaseSerializationContext](baseserializationcontext.md).[serializeEnum](baseserializationcontext.md#serializeenum)_

**Parameters:**

| Name            | Type                    | Default   |
| --------------- | ----------------------- | --------- |
| `enumType`      | object                  | -         |
| `target`        | object                  | -         |
| `propertyName`  | string                  | -         |
| `propertyValue` | number &#124; undefined | -         |
| `defaultValue`  | number &#124; undefined | undefined |

**Returns:** _void_

---

### serializeNumber

▸ **serializeNumber**(`target`: object, `propertyName`: string, `propertyValue`: number | undefined, `defaultValue`: number | undefined): _void_

_Inherited from [BaseSerializationContext](baseserializationcontext.md).[serializeNumber](baseserializationcontext.md#serializenumber)_

**Parameters:**

| Name            | Type                    | Default   |
| --------------- | ----------------------- | --------- |
| `target`        | object                  | -         |
| `propertyName`  | string                  | -         |
| `propertyValue` | number &#124; undefined | -         |
| `defaultValue`  | number &#124; undefined | undefined |

**Returns:** _void_

---

### serializeValue

▸ **serializeValue**(`target`: object, `propertyName`: string, `propertyValue`: any, `defaultValue`: any): _void_

_Inherited from [BaseSerializationContext](baseserializationcontext.md).[serializeValue](baseserializationcontext.md#serializevalue)_

**Parameters:**

| Name            | Type   | Default   |
| --------------- | ------ | --------- |
| `target`        | object | -         |
| `propertyName`  | string | -         |
| `propertyValue` | any    | -         |
| `defaultValue`  | any    | undefined |

**Returns:** _void_

---

### setActionRegistry

▸ **setActionRegistry**(`value`: [CardObjectRegistry](cardobjectregistry.md)‹[Action](action.md)› | undefined): _void_

**Parameters:**

| Name    | Type                                                                              |
| ------- | --------------------------------------------------------------------------------- |
| `value` | [CardObjectRegistry](cardobjectregistry.md)‹[Action](action.md)› &#124; undefined |

**Returns:** _void_

---

### setElementRegistry

▸ **setElementRegistry**(`value`: [CardObjectRegistry](cardobjectregistry.md)‹[CardElement](cardelement.md)› | undefined): _void_

**Parameters:**

| Name    | Type                                                                                        |
| ------- | ------------------------------------------------------------------------------------------- |
| `value` | [CardObjectRegistry](cardobjectregistry.md)‹[CardElement](cardelement.md)› &#124; undefined |

**Returns:** _void_

---

### shouldSerialize

▸ **shouldSerialize**(`o`: [SerializableObject](serializableobject.md)): _boolean_

_Overrides [BaseSerializationContext](baseserializationcontext.md).[shouldSerialize](baseserializationcontext.md#shouldserialize)_

**Parameters:**

| Name | Type                                        |
| ---- | ------------------------------------------- |
| `o`  | [SerializableObject](serializableobject.md) |

**Returns:** _boolean_

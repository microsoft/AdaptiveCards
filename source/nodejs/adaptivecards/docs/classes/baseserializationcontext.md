[Adaptive Cards Javascript SDK](../README.md) › [BaseSerializationContext](baseserializationcontext.md)

# Class: BaseSerializationContext

## Hierarchy

- **BaseSerializationContext**

  ↳ [SimpleSerializationContext](simpleserializationcontext.md)

  ↳ [SerializationContext](serializationcontext.md)

## Index

### Constructors

- [constructor](baseserializationcontext.md#constructor)

### Properties

- [targetVersion](baseserializationcontext.md#targetversion)
- [toJSONOriginalParam](baseserializationcontext.md#tojsonoriginalparam)

### Accessors

- [eventCount](baseserializationcontext.md#eventcount)

### Methods

- [clearEvents](baseserializationcontext.md#clearevents)
- [getEventAt](baseserializationcontext.md#geteventat)
- [logEvent](baseserializationcontext.md#logevent)
- [logParseEvent](baseserializationcontext.md#logparseevent)
- [serializeArray](baseserializationcontext.md#serializearray)
- [serializeEnum](baseserializationcontext.md#serializeenum)
- [serializeNumber](baseserializationcontext.md#serializenumber)
- [serializeValue](baseserializationcontext.md#serializevalue)
- [shouldSerialize](baseserializationcontext.md#shouldserialize)

## Constructors

### constructor

\+ **new BaseSerializationContext**(`targetVersion`: [Version](version.md)): _[BaseSerializationContext](baseserializationcontext.md)_

**Parameters:**

| Name            | Type                  | Default         |
| --------------- | --------------------- | --------------- |
| `targetVersion` | [Version](version.md) | Versions.latest |

**Returns:** _[BaseSerializationContext](baseserializationcontext.md)_

## Properties

### targetVersion

• **targetVersion**: _[Version](version.md)_

---

### toJSONOriginalParam

• **toJSONOriginalParam**: _any_

## Accessors

### eventCount

• **get eventCount**(): _number_

**Returns:** _number_

## Methods

### clearEvents

▸ **clearEvents**(): _void_

**Returns:** _void_

---

### getEventAt

▸ **getEventAt**(`index`: number): _[IValidationEvent](../interfaces/ivalidationevent.md)_

**Parameters:**

| Name    | Type   |
| ------- | ------ |
| `index` | number |

**Returns:** _[IValidationEvent](../interfaces/ivalidationevent.md)_

---

### logEvent

▸ **logEvent**(`source`: [SerializableObject](serializableobject.md) | undefined, `phase`: [ValidationPhase](../enums/validationphase.md), `event`: [ValidationEvent](../enums/validationevent.md), `message`: string): _void_

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

**Parameters:**

| Name      | Type                                                         |
| --------- | ------------------------------------------------------------ |
| `source`  | [SerializableObject](serializableobject.md) &#124; undefined |
| `event`   | [ValidationEvent](../enums/validationevent.md)               |
| `message` | string                                                       |

**Returns:** _void_

---

### serializeArray

▸ **serializeArray**(`target`: object, `propertyName`: string, `propertyValue`: any[] | undefined): _void_

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

**Parameters:**

| Name            | Type   | Default   |
| --------------- | ------ | --------- |
| `target`        | object | -         |
| `propertyName`  | string | -         |
| `propertyValue` | any    | -         |
| `defaultValue`  | any    | undefined |

**Returns:** _void_

---

### shouldSerialize

▸ **shouldSerialize**(`o`: [SerializableObject](serializableobject.md)): _boolean_

**Parameters:**

| Name | Type                                        |
| ---- | ------------------------------------------- |
| `o`  | [SerializableObject](serializableobject.md) |

**Returns:** _boolean_

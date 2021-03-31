[Adaptive Cards Javascript SDK](../README.md) › [BaseSerializationContext](baseserializationcontext.md)

# Class: BaseSerializationContext

## Hierarchy

* **BaseSerializationContext**

  ↳ [SerializationContext](serializationcontext.md)

## Index

### Constructors

* [constructor](baseserializationcontext.md#constructor)

### Properties

* [targetVersion](baseserializationcontext.md#targetversion)

### Accessors

* [eventCount](baseserializationcontext.md#eventcount)

### Methods

* [clearEvents](baseserializationcontext.md#clearevents)
* [getEventAt](baseserializationcontext.md#geteventat)
* [logEvent](baseserializationcontext.md#logevent)
* [logParseEvent](baseserializationcontext.md#logparseevent)
* [serializeArray](baseserializationcontext.md#serializearray)
* [serializeEnum](baseserializationcontext.md#serializeenum)
* [serializeNumber](baseserializationcontext.md#serializenumber)
* [serializeValue](baseserializationcontext.md#serializevalue)

## Constructors

###  constructor

\+ **new BaseSerializationContext**(`targetVersion`: [Version](version.md)): *[BaseSerializationContext](baseserializationcontext.md)*

**Parameters:**

Name | Type | Default |
------ | ------ | ------ |
`targetVersion` | [Version](version.md) | Versions.latest |

**Returns:** *[BaseSerializationContext](baseserializationcontext.md)*

## Properties

###  targetVersion

• **targetVersion**: *[Version](version.md)*

## Accessors

###  eventCount

• **get eventCount**(): *number*

**Returns:** *number*

## Methods

###  clearEvents

▸ **clearEvents**(): *void*

**Returns:** *void*

___

###  getEventAt

▸ **getEventAt**(`index`: number): *[IValidationEvent](../interfaces/ivalidationevent.md)*

**Parameters:**

Name | Type |
------ | ------ |
`index` | number |

**Returns:** *[IValidationEvent](../interfaces/ivalidationevent.md)*

___

###  logEvent

▸ **logEvent**(`source`: [SerializableObject](serializableobject.md) | undefined, `phase`: [ValidationPhase](../enums/validationphase.md), `event`: [ValidationEvent](../enums/validationevent.md), `message`: string): *void*

**Parameters:**

Name | Type |
------ | ------ |
`source` | [SerializableObject](serializableobject.md) &#124; undefined |
`phase` | [ValidationPhase](../enums/validationphase.md) |
`event` | [ValidationEvent](../enums/validationevent.md) |
`message` | string |

**Returns:** *void*

___

###  logParseEvent

▸ **logParseEvent**(`source`: [SerializableObject](serializableobject.md) | undefined, `event`: [ValidationEvent](../enums/validationevent.md), `message`: string): *void*

**Parameters:**

Name | Type |
------ | ------ |
`source` | [SerializableObject](serializableobject.md) &#124; undefined |
`event` | [ValidationEvent](../enums/validationevent.md) |
`message` | string |

**Returns:** *void*

___

###  serializeArray

▸ **serializeArray**(`target`: object, `propertyName`: string, `propertyValue`: any[] | undefined): *void*

**Parameters:**

Name | Type |
------ | ------ |
`target` | object |
`propertyName` | string |
`propertyValue` | any[] &#124; undefined |

**Returns:** *void*

___

###  serializeEnum

▸ **serializeEnum**(`enumType`: object, `target`: object, `propertyName`: string, `propertyValue`: number | undefined, `defaultValue`: number | undefined): *void*

**Parameters:**

Name | Type | Default |
------ | ------ | ------ |
`enumType` | object | - |
`target` | object | - |
`propertyName` | string | - |
`propertyValue` | number &#124; undefined | - |
`defaultValue` | number &#124; undefined | undefined |

**Returns:** *void*

___

###  serializeNumber

▸ **serializeNumber**(`target`: object, `propertyName`: string, `propertyValue`: number | undefined, `defaultValue`: number | undefined): *void*

**Parameters:**

Name | Type | Default |
------ | ------ | ------ |
`target` | object | - |
`propertyName` | string | - |
`propertyValue` | number &#124; undefined | - |
`defaultValue` | number &#124; undefined | undefined |

**Returns:** *void*

___

###  serializeValue

▸ **serializeValue**(`target`: object, `propertyName`: string, `propertyValue`: any, `defaultValue`: any): *void*

**Parameters:**

Name | Type | Default |
------ | ------ | ------ |
`target` | object | - |
`propertyName` | string | - |
`propertyValue` | any | - |
`defaultValue` | any | undefined |

**Returns:** *void*

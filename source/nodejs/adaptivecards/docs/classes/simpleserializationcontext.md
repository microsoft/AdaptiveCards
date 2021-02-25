[Adaptive Cards Javascript SDK](../README.md) › [SimpleSerializationContext](simpleserializationcontext.md)

# Class: SimpleSerializationContext

## Hierarchy

* [BaseSerializationContext](baseserializationcontext.md)

  ↳ **SimpleSerializationContext**

## Index

### Constructors

* [constructor](simpleserializationcontext.md#constructor)

### Properties

* [targetVersion](simpleserializationcontext.md#targetversion)
* [toJSONOriginalParam](simpleserializationcontext.md#tojsonoriginalparam)

### Accessors

* [eventCount](simpleserializationcontext.md#eventcount)

### Methods

* [clearEvents](simpleserializationcontext.md#clearevents)
* [getEventAt](simpleserializationcontext.md#geteventat)
* [logEvent](simpleserializationcontext.md#logevent)
* [logParseEvent](simpleserializationcontext.md#logparseevent)
* [serializeArray](simpleserializationcontext.md#serializearray)
* [serializeEnum](simpleserializationcontext.md#serializeenum)
* [serializeNumber](simpleserializationcontext.md#serializenumber)
* [serializeValue](simpleserializationcontext.md#serializevalue)

## Constructors

###  constructor

\+ **new SimpleSerializationContext**(`targetVersion`: [Version](version.md)): *[SimpleSerializationContext](simpleserializationcontext.md)*

*Inherited from [BaseSerializationContext](baseserializationcontext.md).[constructor](baseserializationcontext.md#constructor)*

**Parameters:**

Name | Type | Default |
------ | ------ | ------ |
`targetVersion` | [Version](version.md) | Versions.latest |

**Returns:** *[SimpleSerializationContext](simpleserializationcontext.md)*

## Properties

###  targetVersion

• **targetVersion**: *[Version](version.md)*

*Inherited from [BaseSerializationContext](baseserializationcontext.md).[targetVersion](baseserializationcontext.md#targetversion)*

___

###  toJSONOriginalParam

• **toJSONOriginalParam**: *any*

*Inherited from [BaseSerializationContext](baseserializationcontext.md).[toJSONOriginalParam](baseserializationcontext.md#tojsonoriginalparam)*

## Accessors

###  eventCount

• **get eventCount**(): *number*

*Inherited from [BaseSerializationContext](baseserializationcontext.md).[eventCount](baseserializationcontext.md#eventcount)*

**Returns:** *number*

## Methods

###  clearEvents

▸ **clearEvents**(): *void*

*Inherited from [BaseSerializationContext](baseserializationcontext.md).[clearEvents](baseserializationcontext.md#clearevents)*

**Returns:** *void*

___

###  getEventAt

▸ **getEventAt**(`index`: number): *[IValidationEvent](../interfaces/ivalidationevent.md)*

*Inherited from [BaseSerializationContext](baseserializationcontext.md).[getEventAt](baseserializationcontext.md#geteventat)*

**Parameters:**

Name | Type |
------ | ------ |
`index` | number |

**Returns:** *[IValidationEvent](../interfaces/ivalidationevent.md)*

___

###  logEvent

▸ **logEvent**(`source`: [SerializableObject](serializableobject.md) | undefined, `phase`: [ValidationPhase](../enums/validationphase.md), `event`: [ValidationEvent](../enums/validationevent.md), `message`: string): *void*

*Inherited from [BaseSerializationContext](baseserializationcontext.md).[logEvent](baseserializationcontext.md#logevent)*

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

*Inherited from [BaseSerializationContext](baseserializationcontext.md).[logParseEvent](baseserializationcontext.md#logparseevent)*

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

*Inherited from [BaseSerializationContext](baseserializationcontext.md).[serializeArray](baseserializationcontext.md#serializearray)*

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

*Inherited from [BaseSerializationContext](baseserializationcontext.md).[serializeEnum](baseserializationcontext.md#serializeenum)*

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

*Inherited from [BaseSerializationContext](baseserializationcontext.md).[serializeNumber](baseserializationcontext.md#serializenumber)*

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

*Inherited from [BaseSerializationContext](baseserializationcontext.md).[serializeValue](baseserializationcontext.md#serializevalue)*

**Parameters:**

Name | Type | Default |
------ | ------ | ------ |
`target` | object | - |
`propertyName` | string | - |
`propertyValue` | any | - |
`defaultValue` | any | undefined |

**Returns:** *void*

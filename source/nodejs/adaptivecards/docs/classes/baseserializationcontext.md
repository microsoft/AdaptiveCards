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

*Defined in [serialization.ts:232](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/serialization.ts#L232)*

**Parameters:**

Name | Type | Default |
------ | ------ | ------ |
`targetVersion` | [Version](version.md) | Versions.latest |

**Returns:** *[BaseSerializationContext](baseserializationcontext.md)*

## Properties

###  targetVersion

• **targetVersion**: *[Version](version.md)*

*Defined in [serialization.ts:234](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/serialization.ts#L234)*

## Accessors

###  eventCount

• **get eventCount**(): *number*

*Defined in [serialization.ts:236](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/serialization.ts#L236)*

**Returns:** *number*

## Methods

###  clearEvents

▸ **clearEvents**(): *void*

*Defined in [serialization.ts:208](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/serialization.ts#L208)*

**Returns:** *void*

___

###  getEventAt

▸ **getEventAt**(`index`: number): *[IValidationEvent](../interfaces/ivalidationevent.md)*

*Defined in [serialization.ts:230](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/serialization.ts#L230)*

**Parameters:**

Name | Type |
------ | ------ |
`index` | number |

**Returns:** *[IValidationEvent](../interfaces/ivalidationevent.md)*

___

###  logEvent

▸ **logEvent**(`phase`: [ValidationPhase](../enums/validationphase.md), `event`: [ValidationEvent](../enums/validationevent.md), `message`: string, `source?`: [SerializableObject](serializableobject.md)): *void*

*Defined in [serialization.ts:212](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/serialization.ts#L212)*

**Parameters:**

Name | Type |
------ | ------ |
`phase` | [ValidationPhase](../enums/validationphase.md) |
`event` | [ValidationEvent](../enums/validationevent.md) |
`message` | string |
`source?` | [SerializableObject](serializableobject.md) |

**Returns:** *void*

___

###  logParseEvent

▸ **logParseEvent**(`event`: [ValidationEvent](../enums/validationevent.md), `message`: string, `source?`: [SerializableObject](serializableobject.md)): *void*

*Defined in [serialization.ts:226](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/serialization.ts#L226)*

**Parameters:**

Name | Type |
------ | ------ |
`event` | [ValidationEvent](../enums/validationevent.md) |
`message` | string |
`source?` | [SerializableObject](serializableobject.md) |

**Returns:** *void*

___

###  serializeArray

▸ **serializeArray**(`target`: object, `propertyName`: string, `propertyValue`: any[] | undefined): *void*

*Defined in [serialization.ts:175](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/serialization.ts#L175)*

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

*Defined in [serialization.ts:148](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/serialization.ts#L148)*

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

*Defined in [serialization.ts:139](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/serialization.ts#L139)*

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

*Defined in [serialization.ts:130](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/serialization.ts#L130)*

**Parameters:**

Name | Type | Default |
------ | ------ | ------ |
`target` | object | - |
`propertyName` | string | - |
`propertyValue` | any | - |
`defaultValue` | any | undefined |

**Returns:** *void*

[Adaptive Cards Javascript SDK](../README.md) › [SerializationContext](serializationcontext.md)

# Class: SerializationContext

## Hierarchy

* [BaseSerializationContext](baseserializationcontext.md)

  ↳ **SerializationContext**

## Index

### Constructors

* [constructor](serializationcontext.md#constructor)

### Properties

* [onParseAction](serializationcontext.md#optional-onparseaction)
* [onParseElement](serializationcontext.md#optional-onparseelement)
* [targetVersion](serializationcontext.md#targetversion)

### Accessors

* [actionRegistry](serializationcontext.md#actionregistry)
* [elementRegistry](serializationcontext.md#elementregistry)
* [eventCount](serializationcontext.md#eventcount)

### Methods

* [cardObjectParsed](serializationcontext.md#protected-cardobjectparsed)
* [clearEvents](serializationcontext.md#clearevents)
* [getEventAt](serializationcontext.md#geteventat)
* [logEvent](serializationcontext.md#logevent)
* [logParseEvent](serializationcontext.md#logparseevent)
* [parseAction](serializationcontext.md#parseaction)
* [parseCardObject](serializationcontext.md#parsecardobject)
* [parseElement](serializationcontext.md#parseelement)
* [serializeArray](serializationcontext.md#serializearray)
* [serializeEnum](serializationcontext.md#serializeenum)
* [serializeNumber](serializationcontext.md#serializenumber)
* [serializeValue](serializationcontext.md#serializevalue)
* [setActionRegistry](serializationcontext.md#setactionregistry)
* [setElementRegistry](serializationcontext.md#setelementregistry)

## Constructors

###  constructor

\+ **new SerializationContext**(`targetVersion`: [Version](version.md)): *[SerializationContext](serializationcontext.md)*

*Inherited from [BaseSerializationContext](baseserializationcontext.md).[constructor](baseserializationcontext.md#constructor)*

**Parameters:**

Name | Type | Default |
------ | ------ | ------ |
`targetVersion` | [Version](version.md) | Versions.latest |

**Returns:** *[SerializationContext](serializationcontext.md)*

## Properties

### `Optional` onParseAction

• **onParseAction**? : *undefined | function*

___

### `Optional` onParseElement

• **onParseElement**? : *undefined | function*

___

###  targetVersion

• **targetVersion**: *[Version](version.md)*

*Inherited from [BaseSerializationContext](baseserializationcontext.md).[targetVersion](baseserializationcontext.md#targetversion)*

## Accessors

###  actionRegistry

• **get actionRegistry**(): *[CardObjectRegistry](cardobjectregistry.md)‹[Action](action.md)›*

**Returns:** *[CardObjectRegistry](cardobjectregistry.md)‹[Action](action.md)›*

___

###  elementRegistry

• **get elementRegistry**(): *[CardObjectRegistry](cardobjectregistry.md)‹[CardElement](cardelement.md)›*

**Returns:** *[CardObjectRegistry](cardobjectregistry.md)‹[CardElement](cardelement.md)›*

___

###  eventCount

• **get eventCount**(): *number*

*Inherited from [BaseSerializationContext](baseserializationcontext.md).[eventCount](baseserializationcontext.md#eventcount)*

**Returns:** *number*

## Methods

### `Protected` cardObjectParsed

▸ **cardObjectParsed**(`o`: [SerializableObject](serializableobject.md), `source`: any): *void*

**Parameters:**

Name | Type |
------ | ------ |
`o` | [SerializableObject](serializableobject.md) |
`source` | any |

**Returns:** *void*

___

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

###  parseAction

▸ **parseAction**(`parent`: [CardElement](cardelement.md), `source`: any, `forbiddenActionTypes`: string[], `allowFallback`: boolean): *[Action](action.md) | undefined*

**Parameters:**

Name | Type |
------ | ------ |
`parent` | [CardElement](cardelement.md) |
`source` | any |
`forbiddenActionTypes` | string[] |
`allowFallback` | boolean |

**Returns:** *[Action](action.md) | undefined*

___

###  parseCardObject

▸ **parseCardObject**‹**T**›(`parent`: [CardElement](cardelement.md) | undefined, `source`: any, `forbiddenTypeNames`: string[], `allowFallback`: boolean, `createInstanceCallback`: function, `logParseEvent`: function): *T | undefined*

**Type parameters:**

▪ **T**: *[CardObject](cardobject.md)*

**Parameters:**

▪ **parent**: *[CardElement](cardelement.md) | undefined*

▪ **source**: *any*

▪ **forbiddenTypeNames**: *string[]*

▪ **allowFallback**: *boolean*

▪ **createInstanceCallback**: *function*

▸ (`typeName`: string): *T | undefined*

**Parameters:**

Name | Type |
------ | ------ |
`typeName` | string |

▪ **logParseEvent**: *function*

▸ (`typeName`: string, `errorType`: TypeErrorType): *void*

**Parameters:**

Name | Type |
------ | ------ |
`typeName` | string |
`errorType` | TypeErrorType |

**Returns:** *T | undefined*

___

###  parseElement

▸ **parseElement**(`parent`: [CardElement](cardelement.md) | undefined, `source`: any, `allowFallback`: boolean): *[CardElement](cardelement.md) | undefined*

**Parameters:**

Name | Type |
------ | ------ |
`parent` | [CardElement](cardelement.md) &#124; undefined |
`source` | any |
`allowFallback` | boolean |

**Returns:** *[CardElement](cardelement.md) | undefined*

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

___

###  setActionRegistry

▸ **setActionRegistry**(`value`: [CardObjectRegistry](cardobjectregistry.md)‹[Action](action.md)› | undefined): *void*

**Parameters:**

Name | Type |
------ | ------ |
`value` | [CardObjectRegistry](cardobjectregistry.md)‹[Action](action.md)› &#124; undefined |

**Returns:** *void*

___

###  setElementRegistry

▸ **setElementRegistry**(`value`: [CardObjectRegistry](cardobjectregistry.md)‹[CardElement](cardelement.md)› | undefined): *void*

**Parameters:**

Name | Type |
------ | ------ |
`value` | [CardObjectRegistry](cardobjectregistry.md)‹[CardElement](cardelement.md)› &#124; undefined |

**Returns:** *void*

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

*Defined in [serialization.ts:232](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/serialization.ts#L232)*

**Parameters:**

Name | Type | Default |
------ | ------ | ------ |
`targetVersion` | [Version](version.md) | Versions.latest |

**Returns:** *[SerializationContext](serializationcontext.md)*

## Properties

### `Optional` onParseAction

• **onParseAction**? : *undefined | function*

*Defined in [card-elements.ts:6358](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L6358)*

___

### `Optional` onParseElement

• **onParseElement**? : *undefined | function*

*Defined in [card-elements.ts:6359](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L6359)*

___

###  targetVersion

• **targetVersion**: *[Version](version.md)*

*Inherited from [BaseSerializationContext](baseserializationcontext.md).[targetVersion](baseserializationcontext.md#targetversion)*

*Defined in [serialization.ts:234](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/serialization.ts#L234)*

## Accessors

###  actionRegistry

• **get actionRegistry**(): *[CardObjectRegistry](cardobjectregistry.md)‹[Action](action.md)›*

*Defined in [card-elements.ts:6445](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L6445)*

**Returns:** *[CardObjectRegistry](cardobjectregistry.md)‹[Action](action.md)›*

___

###  elementRegistry

• **get elementRegistry**(): *[CardObjectRegistry](cardobjectregistry.md)‹[CardElement](cardelement.md)›*

*Defined in [card-elements.ts:6435](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L6435)*

**Returns:** *[CardObjectRegistry](cardobjectregistry.md)‹[CardElement](cardelement.md)›*

___

###  eventCount

• **get eventCount**(): *number*

*Inherited from [BaseSerializationContext](baseserializationcontext.md).[eventCount](baseserializationcontext.md#eventcount)*

*Defined in [serialization.ts:236](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/serialization.ts#L236)*

**Returns:** *number*

## Methods

### `Protected` cardObjectParsed

▸ **cardObjectParsed**(`o`: [SerializableObject](serializableobject.md), `source`: any): *void*

*Defined in [card-elements.ts:6349](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L6349)*

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

*Defined in [serialization.ts:208](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/serialization.ts#L208)*

**Returns:** *void*

___

###  getEventAt

▸ **getEventAt**(`index`: number): *[IValidationEvent](../interfaces/ivalidationevent.md)*

*Inherited from [BaseSerializationContext](baseserializationcontext.md).[getEventAt](baseserializationcontext.md#geteventat)*

*Defined in [serialization.ts:230](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/serialization.ts#L230)*

**Parameters:**

Name | Type |
------ | ------ |
`index` | number |

**Returns:** *[IValidationEvent](../interfaces/ivalidationevent.md)*

___

###  logEvent

▸ **logEvent**(`phase`: [ValidationPhase](../enums/validationphase.md), `event`: [ValidationEvent](../enums/validationevent.md), `message`: string, `source?`: [SerializableObject](serializableobject.md)): *void*

*Inherited from [BaseSerializationContext](baseserializationcontext.md).[logEvent](baseserializationcontext.md#logevent)*

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

*Inherited from [BaseSerializationContext](baseserializationcontext.md).[logParseEvent](baseserializationcontext.md#logparseevent)*

*Defined in [serialization.ts:226](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/serialization.ts#L226)*

**Parameters:**

Name | Type |
------ | ------ |
`event` | [ValidationEvent](../enums/validationevent.md) |
`message` | string |
`source?` | [SerializableObject](serializableobject.md) |

**Returns:** *void*

___

###  parseAction

▸ **parseAction**(`parent`: [CardElement](cardelement.md), `source`: any, `forbiddenActionTypes`: string[], `allowFallback`: boolean): *[Action](action.md) | undefined*

*Defined in [card-elements.ts:6406](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L6406)*

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

▸ **parseCardObject**<**T**>(`parent`: [CardElement](cardelement.md) | undefined, `source`: any, `forbiddenTypeNames`: string[], `allowFallback`: boolean, `createInstanceCallback`: function, `logParseEvent`: function): *T | undefined*

*Defined in [card-elements.ts:6361](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L6361)*

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

*Defined in [card-elements.ts:6383](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L6383)*

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

*Inherited from [BaseSerializationContext](baseserializationcontext.md).[serializeEnum](baseserializationcontext.md#serializeenum)*

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

*Inherited from [BaseSerializationContext](baseserializationcontext.md).[serializeNumber](baseserializationcontext.md#serializenumber)*

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

*Inherited from [BaseSerializationContext](baseserializationcontext.md).[serializeValue](baseserializationcontext.md#serializevalue)*

*Defined in [serialization.ts:130](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/serialization.ts#L130)*

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

*Defined in [card-elements.ts:6451](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L6451)*

**Parameters:**

Name | Type |
------ | ------ |
`value` | [CardObjectRegistry](cardobjectregistry.md)‹[Action](action.md)› &#124; undefined |

**Returns:** *void*

___

###  setElementRegistry

▸ **setElementRegistry**(`value`: [CardObjectRegistry](cardobjectregistry.md)‹[CardElement](cardelement.md)› | undefined): *void*

*Defined in [card-elements.ts:6441](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L6441)*

**Parameters:**

Name | Type |
------ | ------ |
`value` | [CardObjectRegistry](cardobjectregistry.md)‹[CardElement](cardelement.md)› &#124; undefined |

**Returns:** *void*

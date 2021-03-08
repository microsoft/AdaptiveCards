[Adaptive Cards Javascript SDK](../README.md) / [adaptivecards](../modules/adaptivecards.md) / SerializationContext

# Class: SerializationContext

[adaptivecards](../modules/adaptivecards.md).SerializationContext

## Hierarchy

* [*BaseSerializationContext*](serialization.baseserializationcontext.md)

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

\+ **new SerializationContext**(`targetVersion?`: [*Version*](serialization.version.md)): [*SerializationContext*](card_elements.serializationcontext.md)

#### Parameters:

Name | Type |
:------ | :------ |
`targetVersion` | [*Version*](serialization.version.md) |

**Returns:** [*SerializationContext*](card_elements.serializationcontext.md)

Inherited from: [BaseSerializationContext](serialization.baseserializationcontext.md)

Defined in: [serialization.ts:248](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L248)

## Properties

### onParseAction

• `Optional` **onParseAction**: *undefined* \| (`action`: [*Action*](card_elements.action.md), `source`: *any*, `context`: [*SerializationContext*](card_elements.serializationcontext.md)) => *void*

Defined in: [card-elements.ts:6815](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L6815)

___

### onParseElement

• `Optional` **onParseElement**: *undefined* \| (`element`: [*CardElement*](card_elements.cardelement.md), `source`: *any*, `context`: [*SerializationContext*](card_elements.serializationcontext.md)) => *void*

Defined in: [card-elements.ts:6816](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L6816)

___

### targetVersion

• **targetVersion**: [*Version*](serialization.version.md)

Inherited from: [BaseSerializationContext](serialization.baseserializationcontext.md).[targetVersion](serialization.baseserializationcontext.md#targetversion)

___

### toJSONOriginalParam

• **toJSONOriginalParam**: *any*

Inherited from: [BaseSerializationContext](serialization.baseserializationcontext.md).[toJSONOriginalParam](serialization.baseserializationcontext.md#tojsonoriginalparam)

Defined in: [serialization.ts:132](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L132)

## Accessors

### actionRegistry

• get **actionRegistry**(): [*CardObjectRegistry*](registry.cardobjectregistry.md)<[*Action*](card_elements.action.md)\>

**Returns:** [*CardObjectRegistry*](registry.cardobjectregistry.md)<[*Action*](card_elements.action.md)\>

Defined in: [card-elements.ts:6904](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L6904)

___

### elementRegistry

• get **elementRegistry**(): [*CardObjectRegistry*](registry.cardobjectregistry.md)<[*CardElement*](card_elements.cardelement.md)\>

**Returns:** [*CardObjectRegistry*](registry.cardobjectregistry.md)<[*CardElement*](card_elements.cardelement.md)\>

Defined in: [card-elements.ts:6894](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L6894)

___

### eventCount

• get **eventCount**(): *number*

**Returns:** *number*

Defined in: [serialization.ts:252](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L252)

## Methods

### cardObjectParsed

▸ `Protected`**cardObjectParsed**(`o`: [*SerializableObject*](serialization.serializableobject.md), `source`: *any*): *void*

#### Parameters:

Name | Type |
:------ | :------ |
`o` | [*SerializableObject*](serialization.serializableobject.md) |
`source` | *any* |

**Returns:** *void*

Defined in: [card-elements.ts:6806](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L6806)

___

### clearEvents

▸ **clearEvents**(): *void*

**Returns:** *void*

Inherited from: [BaseSerializationContext](serialization.baseserializationcontext.md)

Defined in: [serialization.ts:223](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L223)

___

### getEventAt

▸ **getEventAt**(`index`: *number*): [*IValidationEvent*](../interfaces/serialization.ivalidationevent.md)

#### Parameters:

Name | Type |
:------ | :------ |
`index` | *number* |

**Returns:** [*IValidationEvent*](../interfaces/serialization.ivalidationevent.md)

Inherited from: [BaseSerializationContext](serialization.baseserializationcontext.md)

Defined in: [serialization.ts:246](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L246)

___

### logEvent

▸ **logEvent**(`source`: *undefined* \| [*SerializableObject*](serialization.serializableobject.md), `phase`: [*ValidationPhase*](../enums/enums.validationphase.md), `event`: [*ValidationEvent*](../enums/enums.validationevent.md), `message`: *string*): *void*

#### Parameters:

Name | Type |
:------ | :------ |
`source` | *undefined* \| [*SerializableObject*](serialization.serializableobject.md) |
`phase` | [*ValidationPhase*](../enums/enums.validationphase.md) |
`event` | [*ValidationEvent*](../enums/enums.validationevent.md) |
`message` | *string* |

**Returns:** *void*

Inherited from: [BaseSerializationContext](serialization.baseserializationcontext.md)

Defined in: [serialization.ts:227](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L227)

___

### logParseEvent

▸ **logParseEvent**(`source`: *undefined* \| [*SerializableObject*](serialization.serializableobject.md), `event`: [*ValidationEvent*](../enums/enums.validationevent.md), `message`: *string*): *void*

#### Parameters:

Name | Type |
:------ | :------ |
`source` | *undefined* \| [*SerializableObject*](serialization.serializableobject.md) |
`event` | [*ValidationEvent*](../enums/enums.validationevent.md) |
`message` | *string* |

**Returns:** *void*

Inherited from: [BaseSerializationContext](serialization.baseserializationcontext.md)

Defined in: [serialization.ts:242](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L242)

___

### parseAction

▸ **parseAction**(`parent`: [*CardElement*](card_elements.cardelement.md), `source`: *any*, `forbiddenActionTypes`: *string*[], `allowFallback`: *boolean*): *undefined* \| [*Action*](card_elements.action.md)

#### Parameters:

Name | Type |
:------ | :------ |
`parent` | [*CardElement*](card_elements.cardelement.md) |
`source` | *any* |
`forbiddenActionTypes` | *string*[] |
`allowFallback` | *boolean* |

**Returns:** *undefined* \| [*Action*](card_elements.action.md)

Defined in: [card-elements.ts:6865](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L6865)

___

### parseCardObject

▸ **parseCardObject**<T\>(`parent`: *undefined* \| [*CardElement*](card_elements.cardelement.md), `source`: *any*, `forbiddenTypeNames`: *string*[], `allowFallback`: *boolean*, `createInstanceCallback`: (`typeName`: *string*) => *undefined* \| T, `logParseEvent`: (`typeName`: *string*, `errorType`: TypeErrorType) => *void*): *undefined* \| T

#### Type parameters:

Name | Type |
:------ | :------ |
`T` | [*CardObject*](card_object.cardobject.md)<T\> |

#### Parameters:

Name | Type |
:------ | :------ |
`parent` | *undefined* \| [*CardElement*](card_elements.cardelement.md) |
`source` | *any* |
`forbiddenTypeNames` | *string*[] |
`allowFallback` | *boolean* |
`createInstanceCallback` | (`typeName`: *string*) => *undefined* \| T |
`logParseEvent` | (`typeName`: *string*, `errorType`: TypeErrorType) => *void* |

**Returns:** *undefined* \| T

Defined in: [card-elements.ts:6818](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L6818)

___

### parseElement

▸ **parseElement**(`parent`: *undefined* \| [*CardElement*](card_elements.cardelement.md), `source`: *any*, `allowFallback`: *boolean*): *undefined* \| [*CardElement*](card_elements.cardelement.md)

#### Parameters:

Name | Type |
:------ | :------ |
`parent` | *undefined* \| [*CardElement*](card_elements.cardelement.md) |
`source` | *any* |
`allowFallback` | *boolean* |

**Returns:** *undefined* \| [*CardElement*](card_elements.cardelement.md)

Defined in: [card-elements.ts:6840](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L6840)

___

### serializeArray

▸ **serializeArray**(`target`: { [key: string]: *any*;  }, `propertyName`: *string*, `propertyValue`: *undefined* \| *any*[]): *void*

#### Parameters:

Name | Type |
:------ | :------ |
`target` | *object* |
`propertyName` | *string* |
`propertyValue` | *undefined* \| *any*[] |

**Returns:** *void*

Inherited from: [BaseSerializationContext](serialization.baseserializationcontext.md)

Defined in: [serialization.ts:190](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L190)

___

### serializeBool

▸ **serializeBool**(`target`: { [key: string]: *any*;  }, `propertyName`: *string*, `propertyValue`: *undefined* \| *boolean*, `defaultValue?`: *undefined* \| *boolean*): *void*

#### Parameters:

Name | Type |
:------ | :------ |
`target` | *object* |
`propertyName` | *string* |
`propertyValue` | *undefined* \| *boolean* |
`defaultValue` | *undefined* \| *boolean* |

**Returns:** *void*

Inherited from: [BaseSerializationContext](serialization.baseserializationcontext.md)

Defined in: [serialization.ts:145](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L145)

___

### serializeEnum

▸ **serializeEnum**(`enumType`: { [s: number]: *string*;  }, `target`: { [key: string]: *any*;  }, `propertyName`: *string*, `propertyValue`: *undefined* \| *number*, `defaultValue?`: *undefined* \| *number*): *void*

#### Parameters:

Name | Type |
:------ | :------ |
`enumType` | *object* |
`target` | *object* |
`propertyName` | *string* |
`propertyValue` | *undefined* \| *number* |
`defaultValue` | *undefined* \| *number* |

**Returns:** *void*

Inherited from: [BaseSerializationContext](serialization.baseserializationcontext.md)

Defined in: [serialization.ts:163](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L163)

___

### serializeNumber

▸ **serializeNumber**(`target`: { [key: string]: *any*;  }, `propertyName`: *string*, `propertyValue`: *undefined* \| *number*, `defaultValue?`: *undefined* \| *number*): *void*

#### Parameters:

Name | Type |
:------ | :------ |
`target` | *object* |
`propertyName` | *string* |
`propertyValue` | *undefined* \| *number* |
`defaultValue` | *undefined* \| *number* |

**Returns:** *void*

Inherited from: [BaseSerializationContext](serialization.baseserializationcontext.md)

Defined in: [serialization.ts:154](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L154)

___

### serializeValue

▸ **serializeValue**(`target`: { [key: string]: *any*;  }, `propertyName`: *string*, `propertyValue`: *any*, `defaultValue?`: *any*): *void*

#### Parameters:

Name | Type |
:------ | :------ |
`target` | *object* |
`propertyName` | *string* |
`propertyValue` | *any* |
`defaultValue` | *any* |

**Returns:** *void*

Inherited from: [BaseSerializationContext](serialization.baseserializationcontext.md)

Defined in: [serialization.ts:134](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L134)

___

### setActionRegistry

▸ **setActionRegistry**(`value`: *undefined* \| [*CardObjectRegistry*](registry.cardobjectregistry.md)<[*Action*](card_elements.action.md)\>): *void*

#### Parameters:

Name | Type |
:------ | :------ |
`value` | *undefined* \| [*CardObjectRegistry*](registry.cardobjectregistry.md)<[*Action*](card_elements.action.md)\> |

**Returns:** *void*

Defined in: [card-elements.ts:6910](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L6910)

___

### setElementRegistry

▸ **setElementRegistry**(`value`: *undefined* \| [*CardObjectRegistry*](registry.cardobjectregistry.md)<[*CardElement*](card_elements.cardelement.md)\>): *void*

#### Parameters:

Name | Type |
:------ | :------ |
`value` | *undefined* \| [*CardObjectRegistry*](registry.cardobjectregistry.md)<[*CardElement*](card_elements.cardelement.md)\> |

**Returns:** *void*

Defined in: [card-elements.ts:6900](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L6900)

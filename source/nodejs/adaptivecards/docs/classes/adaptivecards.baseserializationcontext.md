[Adaptive Cards Javascript SDK](../README.md) / [adaptivecards](../modules/adaptivecards.md) / BaseSerializationContext

# Class: BaseSerializationContext

[adaptivecards](../modules/adaptivecards.md).BaseSerializationContext

## Table of contents

### Constructors

- [constructor](adaptivecards.baseserializationcontext.md#constructor)

### Properties

- [targetVersion](adaptivecards.baseserializationcontext.md#targetversion)
- [toJSONOriginalParam](adaptivecards.baseserializationcontext.md#tojsonoriginalparam)

### Accessors

- [eventCount](adaptivecards.baseserializationcontext.md#eventcount)

### Methods

- [clearEvents](adaptivecards.baseserializationcontext.md#clearevents)
- [getEventAt](adaptivecards.baseserializationcontext.md#geteventat)
- [logEvent](adaptivecards.baseserializationcontext.md#logevent)
- [logParseEvent](adaptivecards.baseserializationcontext.md#logparseevent)
- [serializeArray](adaptivecards.baseserializationcontext.md#serializearray)
- [serializeBool](adaptivecards.baseserializationcontext.md#serializebool)
- [serializeEnum](adaptivecards.baseserializationcontext.md#serializeenum)
- [serializeNumber](adaptivecards.baseserializationcontext.md#serializenumber)
- [serializeValue](adaptivecards.baseserializationcontext.md#serializevalue)

## Constructors

### constructor

\+ **new BaseSerializationContext**(`targetVersion?`: [*Version*](serialization.version.md)): [*BaseSerializationContext*](serialization.baseserializationcontext.md)

#### Parameters:

Name | Type |
:------ | :------ |
`targetVersion` | [*Version*](serialization.version.md) |

**Returns:** [*BaseSerializationContext*](serialization.baseserializationcontext.md)

Defined in: [serialization.ts:248](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L248)

## Properties

### targetVersion

• **targetVersion**: [*Version*](serialization.version.md)

___

### toJSONOriginalParam

• **toJSONOriginalParam**: *any*

Defined in: [serialization.ts:132](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L132)

## Accessors

### eventCount

• get **eventCount**(): *number*

**Returns:** *number*

Defined in: [serialization.ts:252](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L252)

## Methods

### clearEvents

▸ **clearEvents**(): *void*

**Returns:** *void*

Defined in: [serialization.ts:223](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L223)

___

### getEventAt

▸ **getEventAt**(`index`: *number*): [*IValidationEvent*](../interfaces/serialization.ivalidationevent.md)

#### Parameters:

Name | Type |
:------ | :------ |
`index` | *number* |

**Returns:** [*IValidationEvent*](../interfaces/serialization.ivalidationevent.md)

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

Defined in: [serialization.ts:242](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L242)

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

Defined in: [serialization.ts:134](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L134)

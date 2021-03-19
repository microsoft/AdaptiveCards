[Adaptive Cards Javascript SDK](../README.md) / [adaptivecards](../modules/adaptivecards.md) / TimeProperty

# Class: TimeProperty

[adaptivecards](../modules/adaptivecards.md).TimeProperty

## Hierarchy

* [*CustomProperty*](serialization.customproperty.md)<string \| undefined\>

  ↳ **TimeProperty**

## Table of contents

### Constructors

- [constructor](adaptivecards.timeproperty.md#constructor)

### Properties

- [defaultValue](adaptivecards.timeproperty.md#defaultvalue)
- [isSerializationEnabled](adaptivecards.timeproperty.md#isserializationenabled)
- [name](adaptivecards.timeproperty.md#name)
- [onGetInitialValue](adaptivecards.timeproperty.md#ongetinitialvalue)
- [onParse](adaptivecards.timeproperty.md#onparse)
- [onToJSON](adaptivecards.timeproperty.md#ontojson)
- [sequentialNumber](adaptivecards.timeproperty.md#sequentialnumber)
- [targetVersion](adaptivecards.timeproperty.md#targetversion)

### Methods

- [getInternalName](adaptivecards.timeproperty.md#getinternalname)
- [parse](adaptivecards.timeproperty.md#parse)
- [toJSON](adaptivecards.timeproperty.md#tojson)

## Constructors

### constructor

\+ **new TimeProperty**(`targetVersion`: [*Version*](serialization.version.md), `name`: *string*): [*TimeProperty*](card_elements.timeproperty.md)

#### Parameters:

Name | Type |
:------ | :------ |
`targetVersion` | [*Version*](serialization.version.md) |
`name` | *string* |

**Returns:** [*TimeProperty*](card_elements.timeproperty.md)

Inherited from: [CustomProperty](serialization.customproperty.md)

Defined in: [card-elements.ts:3523](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L3523)

## Properties

### defaultValue

• `Optional` `Readonly` **defaultValue**: *undefined* \| *string*

Inherited from: [CustomProperty](serialization.customproperty.md).[defaultValue](serialization.customproperty.md#defaultvalue)

___

### isSerializationEnabled

• **isSerializationEnabled**: *boolean*= true

Inherited from: [CustomProperty](serialization.customproperty.md).[isSerializationEnabled](serialization.customproperty.md#isserializationenabled)

Defined in: [serialization.ts:276](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L276)

___

### name

• `Readonly` **name**: *string*

Inherited from: [CustomProperty](serialization.customproperty.md).[name](serialization.customproperty.md#name)

___

### onGetInitialValue

• `Optional` `Readonly` **onGetInitialValue**: *undefined* \| (`sender`: [*SerializableObject*](serialization.serializableobject.md)) => *undefined* \| *string*

Inherited from: [CustomProperty](serialization.customproperty.md).[onGetInitialValue](serialization.customproperty.md#ongetinitialvalue)

___

### onParse

• `Readonly` **onParse**: (`sender`: [*SerializableObject*](serialization.serializableobject.md), `property`: [*PropertyDefinition*](serialization.propertydefinition.md), `source`: [*PropertyBag*](../modules/serialization.md#propertybag), `context`: [*BaseSerializationContext*](serialization.baseserializationcontext.md)) => *undefined* \| *string*

#### Type declaration:

▸ (`sender`: [*SerializableObject*](serialization.serializableobject.md), `property`: [*PropertyDefinition*](serialization.propertydefinition.md), `source`: [*PropertyBag*](../modules/serialization.md#propertybag), `context`: [*BaseSerializationContext*](serialization.baseserializationcontext.md)): *undefined* \| *string*

#### Parameters:

Name | Type |
:------ | :------ |
`sender` | [*SerializableObject*](serialization.serializableobject.md) |
`property` | [*PropertyDefinition*](serialization.propertydefinition.md) |
`source` | [*PropertyBag*](../modules/serialization.md#propertybag) |
`context` | [*BaseSerializationContext*](serialization.baseserializationcontext.md) |

**Returns:** *undefined* \| *string*

Defined in: [serialization.ts:695](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L695)

Inherited from: [CustomProperty](serialization.customproperty.md).[onParse](serialization.customproperty.md#onparse)

___

### onToJSON

• `Readonly` **onToJSON**: (`sender`: [*SerializableObject*](serialization.serializableobject.md), `property`: [*PropertyDefinition*](serialization.propertydefinition.md), `target`: [*PropertyBag*](../modules/serialization.md#propertybag), `value`: *undefined* \| *string*, `context`: [*BaseSerializationContext*](serialization.baseserializationcontext.md)) => *void*

#### Type declaration:

▸ (`sender`: [*SerializableObject*](serialization.serializableobject.md), `property`: [*PropertyDefinition*](serialization.propertydefinition.md), `target`: [*PropertyBag*](../modules/serialization.md#propertybag), `value`: *undefined* \| *string*, `context`: [*BaseSerializationContext*](serialization.baseserializationcontext.md)): *void*

#### Parameters:

Name | Type |
:------ | :------ |
`sender` | [*SerializableObject*](serialization.serializableobject.md) |
`property` | [*PropertyDefinition*](serialization.propertydefinition.md) |
`target` | [*PropertyBag*](../modules/serialization.md#propertybag) |
`value` | *undefined* \| *string* |
`context` | [*BaseSerializationContext*](serialization.baseserializationcontext.md) |

**Returns:** *void*

Defined in: [serialization.ts:696](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L696)

Inherited from: [CustomProperty](serialization.customproperty.md).[onToJSON](serialization.customproperty.md#ontojson)

___

### sequentialNumber

• `Readonly` **sequentialNumber**: *number*

Inherited from: [CustomProperty](serialization.customproperty.md).[sequentialNumber](serialization.customproperty.md#sequentialnumber)

Defined in: [serialization.ts:274](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L274)

___

### targetVersion

• `Readonly` **targetVersion**: [*Version*](serialization.version.md)

Inherited from: [CustomProperty](serialization.customproperty.md).[targetVersion](serialization.customproperty.md#targetversion)

## Methods

### getInternalName

▸ **getInternalName**(): *string*

**Returns:** *string*

Inherited from: [CustomProperty](serialization.customproperty.md)

Defined in: [serialization.ts:262](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L262)

___

### parse

▸ **parse**(`sender`: [*SerializableObject*](serialization.serializableobject.md), `source`: [*PropertyBag*](../modules/serialization.md#propertybag), `context`: [*BaseSerializationContext*](serialization.baseserializationcontext.md)): *undefined* \| *string*

#### Parameters:

Name | Type |
:------ | :------ |
`sender` | [*SerializableObject*](serialization.serializableobject.md) |
`source` | [*PropertyBag*](../modules/serialization.md#propertybag) |
`context` | [*BaseSerializationContext*](serialization.baseserializationcontext.md) |

**Returns:** *undefined* \| *string*

Inherited from: [CustomProperty](serialization.customproperty.md)

Defined in: [serialization.ts:684](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L684)

___

### toJSON

▸ **toJSON**(`sender`: [*SerializableObject*](serialization.serializableobject.md), `target`: [*PropertyBag*](../modules/serialization.md#propertybag), `value`: *undefined* \| *string*, `context`: [*BaseSerializationContext*](serialization.baseserializationcontext.md)): *void*

#### Parameters:

Name | Type |
:------ | :------ |
`sender` | [*SerializableObject*](serialization.serializableobject.md) |
`target` | [*PropertyBag*](../modules/serialization.md#propertybag) |
`value` | *undefined* \| *string* |
`context` | [*BaseSerializationContext*](serialization.baseserializationcontext.md) |

**Returns:** *void*

Inherited from: [CustomProperty](serialization.customproperty.md)

Defined in: [serialization.ts:688](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L688)

[Adaptive Cards Javascript SDK](../README.md) / [serialization](../modules/serialization.md) / BoolProperty

# Class: BoolProperty

[serialization](../modules/serialization.md).BoolProperty

## Hierarchy

* [*PropertyDefinition*](serialization.propertydefinition.md)

  ↳ **BoolProperty**

## Table of contents

### Constructors

- [constructor](serialization.boolproperty.md#constructor)

### Properties

- [defaultValue](serialization.boolproperty.md#defaultvalue)
- [isSerializationEnabled](serialization.boolproperty.md#isserializationenabled)
- [name](serialization.boolproperty.md#name)
- [onGetInitialValue](serialization.boolproperty.md#ongetinitialvalue)
- [sequentialNumber](serialization.boolproperty.md#sequentialnumber)
- [targetVersion](serialization.boolproperty.md#targetversion)

### Methods

- [getInternalName](serialization.boolproperty.md#getinternalname)
- [parse](serialization.boolproperty.md#parse)
- [toJSON](serialization.boolproperty.md#tojson)

## Constructors

### constructor

\+ **new BoolProperty**(`targetVersion`: [*Version*](serialization.version.md), `name`: *string*, `defaultValue?`: *any*, `onGetInitialValue?`: (`sender`: [*SerializableObject*](serialization.serializableobject.md)) => *any*): [*BoolProperty*](serialization.boolproperty.md)

#### Parameters:

Name | Type |
:------ | :------ |
`targetVersion` | [*Version*](serialization.version.md) |
`name` | *string* |
`defaultValue?` | *any* |
`onGetInitialValue?` | (`sender`: [*SerializableObject*](serialization.serializableobject.md)) => *any* |

**Returns:** [*BoolProperty*](serialization.boolproperty.md)

Inherited from: [PropertyDefinition](serialization.propertydefinition.md)

Defined in: [serialization.ts:276](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L276)

## Properties

### defaultValue

• `Optional` `Readonly` **defaultValue**: *any*

Inherited from: [PropertyDefinition](serialization.propertydefinition.md).[defaultValue](serialization.propertydefinition.md#defaultvalue)

___

### isSerializationEnabled

• **isSerializationEnabled**: *boolean*= true

Inherited from: [PropertyDefinition](serialization.propertydefinition.md).[isSerializationEnabled](serialization.propertydefinition.md#isserializationenabled)

Defined in: [serialization.ts:276](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L276)

___

### name

• `Readonly` **name**: *string*

Inherited from: [PropertyDefinition](serialization.propertydefinition.md).[name](serialization.propertydefinition.md#name)

___

### onGetInitialValue

• `Optional` `Readonly` **onGetInitialValue**: *undefined* \| (`sender`: [*SerializableObject*](serialization.serializableobject.md)) => *any*

Inherited from: [PropertyDefinition](serialization.propertydefinition.md).[onGetInitialValue](serialization.propertydefinition.md#ongetinitialvalue)

___

### sequentialNumber

• `Readonly` **sequentialNumber**: *number*

Inherited from: [PropertyDefinition](serialization.propertydefinition.md).[sequentialNumber](serialization.propertydefinition.md#sequentialnumber)

Defined in: [serialization.ts:274](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L274)

___

### targetVersion

• `Readonly` **targetVersion**: [*Version*](serialization.version.md)

Inherited from: [PropertyDefinition](serialization.propertydefinition.md).[targetVersion](serialization.propertydefinition.md#targetversion)

## Methods

### getInternalName

▸ **getInternalName**(): *string*

**Returns:** *string*

Inherited from: [PropertyDefinition](serialization.propertydefinition.md)

Defined in: [serialization.ts:262](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L262)

___

### parse

▸ **parse**(`sender`: [*SerializableObject*](serialization.serializableobject.md), `source`: [*PropertyBag*](../modules/serialization.md#propertybag), `context`: [*BaseSerializationContext*](serialization.baseserializationcontext.md)): *undefined* \| *boolean*

#### Parameters:

Name | Type |
:------ | :------ |
`sender` | [*SerializableObject*](serialization.serializableobject.md) |
`source` | [*PropertyBag*](../modules/serialization.md#propertybag) |
`context` | [*BaseSerializationContext*](serialization.baseserializationcontext.md) |

**Returns:** *undefined* \| *boolean*

Overrides: [PropertyDefinition](serialization.propertydefinition.md)

Defined in: [serialization.ts:330](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L330)

___

### toJSON

▸ **toJSON**(`sender`: [*SerializableObject*](serialization.serializableobject.md), `target`: *object*, `value`: *undefined* \| *boolean*, `context`: [*BaseSerializationContext*](serialization.baseserializationcontext.md)): *void*

#### Parameters:

Name | Type |
:------ | :------ |
`sender` | [*SerializableObject*](serialization.serializableobject.md) |
`target` | *object* |
`value` | *undefined* \| *boolean* |
`context` | [*BaseSerializationContext*](serialization.baseserializationcontext.md) |

**Returns:** *void*

Overrides: [PropertyDefinition](serialization.propertydefinition.md)

Defined in: [serialization.ts:334](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L334)

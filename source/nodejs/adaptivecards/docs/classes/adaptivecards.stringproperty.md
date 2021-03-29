[Adaptive Cards Javascript SDK](../README.md) / [adaptivecards](../modules/adaptivecards.md) / StringProperty

# Class: StringProperty

[adaptivecards](../modules/adaptivecards.md).StringProperty

## Hierarchy

* [*PropertyDefinition*](serialization.propertydefinition.md)

  ↳ **StringProperty**

## Table of contents

### Constructors

- [constructor](adaptivecards.stringproperty.md#constructor)

### Properties

- [defaultValue](adaptivecards.stringproperty.md#defaultvalue)
- [isSerializationEnabled](adaptivecards.stringproperty.md#isserializationenabled)
- [name](adaptivecards.stringproperty.md#name)
- [onGetInitialValue](adaptivecards.stringproperty.md#ongetinitialvalue)
- [regEx](adaptivecards.stringproperty.md#regex)
- [sequentialNumber](adaptivecards.stringproperty.md#sequentialnumber)
- [targetVersion](adaptivecards.stringproperty.md#targetversion)
- [treatEmptyAsUndefined](adaptivecards.stringproperty.md#treatemptyasundefined)

### Methods

- [getInternalName](adaptivecards.stringproperty.md#getinternalname)
- [parse](adaptivecards.stringproperty.md#parse)
- [toJSON](adaptivecards.stringproperty.md#tojson)

## Constructors

### constructor

\+ **new StringProperty**(`targetVersion`: [*Version*](serialization.version.md), `name`: *string*, `treatEmptyAsUndefined?`: *boolean*, `regEx?`: *RegExp*, `defaultValue?`: *string*, `onGetInitialValue?`: (`sender`: [*SerializableObject*](serialization.serializableobject.md)) => *string*): [*StringProperty*](serialization.stringproperty.md)

#### Parameters:

Name | Type | Default value |
:------ | :------ | :------ |
`targetVersion` | [*Version*](serialization.version.md) | - |
`name` | *string* | - |
`treatEmptyAsUndefined` | *boolean* | true |
`regEx?` | *RegExp* | - |
`defaultValue?` | *string* | - |
`onGetInitialValue?` | (`sender`: [*SerializableObject*](serialization.serializableobject.md)) => *string* | - |

**Returns:** [*StringProperty*](serialization.stringproperty.md)

Inherited from: [PropertyDefinition](serialization.propertydefinition.md)

Defined in: [serialization.ts:316](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L316)

## Properties

### defaultValue

• `Optional` `Readonly` **defaultValue**: *undefined* \| *string*

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

• `Optional` `Readonly` **onGetInitialValue**: *undefined* \| (`sender`: [*SerializableObject*](serialization.serializableobject.md)) => *string*

Inherited from: [PropertyDefinition](serialization.propertydefinition.md).[onGetInitialValue](serialization.propertydefinition.md#ongetinitialvalue)

___

### regEx

• `Optional` `Readonly` **regEx**: *undefined* \| *RegExp*

___

### sequentialNumber

• `Readonly` **sequentialNumber**: *number*

Inherited from: [PropertyDefinition](serialization.propertydefinition.md).[sequentialNumber](serialization.propertydefinition.md#sequentialnumber)

Defined in: [serialization.ts:274](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L274)

___

### targetVersion

• `Readonly` **targetVersion**: [*Version*](serialization.version.md)

Inherited from: [PropertyDefinition](serialization.propertydefinition.md).[targetVersion](serialization.propertydefinition.md#targetversion)

___

### treatEmptyAsUndefined

• `Readonly` **treatEmptyAsUndefined**: *boolean*= true

## Methods

### getInternalName

▸ **getInternalName**(): *string*

**Returns:** *string*

Inherited from: [PropertyDefinition](serialization.propertydefinition.md)

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

Overrides: [PropertyDefinition](serialization.propertydefinition.md)

Defined in: [serialization.ts:290](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L290)

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

Overrides: [PropertyDefinition](serialization.propertydefinition.md)

Defined in: [serialization.ts:310](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L310)

[Adaptive Cards Javascript SDK](../README.md) / [serialization](../modules/serialization.md) / ValueSetProperty

# Class: ValueSetProperty

[serialization](../modules/serialization.md).ValueSetProperty

## Hierarchy

* [*PropertyDefinition*](serialization.propertydefinition.md)

  ↳ **ValueSetProperty**

## Table of contents

### Constructors

- [constructor](serialization.valuesetproperty.md#constructor)

### Properties

- [defaultValue](serialization.valuesetproperty.md#defaultvalue)
- [isSerializationEnabled](serialization.valuesetproperty.md#isserializationenabled)
- [name](serialization.valuesetproperty.md#name)
- [onGetInitialValue](serialization.valuesetproperty.md#ongetinitialvalue)
- [sequentialNumber](serialization.valuesetproperty.md#sequentialnumber)
- [targetVersion](serialization.valuesetproperty.md#targetversion)
- [values](serialization.valuesetproperty.md#values)

### Methods

- [getInternalName](serialization.valuesetproperty.md#getinternalname)
- [isValidValue](serialization.valuesetproperty.md#isvalidvalue)
- [parse](serialization.valuesetproperty.md#parse)
- [toJSON](serialization.valuesetproperty.md#tojson)

## Constructors

### constructor

\+ **new ValueSetProperty**(`targetVersion`: [*Version*](serialization.version.md), `name`: *string*, `values`: [*IVersionedValue*](../interfaces/serialization.iversionedvalue.md)<string\>[], `defaultValue?`: *string*, `onGetInitialValue?`: (`sender`: [*SerializableObject*](serialization.serializableobject.md)) => *string*): [*ValueSetProperty*](serialization.valuesetproperty.md)

#### Parameters:

Name | Type |
:------ | :------ |
`targetVersion` | [*Version*](serialization.version.md) |
`name` | *string* |
`values` | [*IVersionedValue*](../interfaces/serialization.iversionedvalue.md)<string\>[] |
`defaultValue?` | *string* |
`onGetInitialValue?` | (`sender`: [*SerializableObject*](serialization.serializableobject.md)) => *string* |

**Returns:** [*ValueSetProperty*](serialization.valuesetproperty.md)

Inherited from: [PropertyDefinition](serialization.propertydefinition.md)

Defined in: [serialization.ts:487](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L487)

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

### sequentialNumber

• `Readonly` **sequentialNumber**: *number*

Inherited from: [PropertyDefinition](serialization.propertydefinition.md).[sequentialNumber](serialization.propertydefinition.md#sequentialnumber)

Defined in: [serialization.ts:274](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L274)

___

### targetVersion

• `Readonly` **targetVersion**: [*Version*](serialization.version.md)

Inherited from: [PropertyDefinition](serialization.propertydefinition.md).[targetVersion](serialization.propertydefinition.md#targetversion)

___

### values

• `Readonly` **values**: [*IVersionedValue*](../interfaces/serialization.iversionedvalue.md)<string\>[]

## Methods

### getInternalName

▸ **getInternalName**(): *string*

**Returns:** *string*

Inherited from: [PropertyDefinition](serialization.propertydefinition.md)

Defined in: [serialization.ts:262](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L262)

___

### isValidValue

▸ **isValidValue**(`value`: *string*, `context`: [*BaseSerializationContext*](serialization.baseserializationcontext.md)): *boolean*

#### Parameters:

Name | Type |
:------ | :------ |
`value` | *string* |
`context` | [*BaseSerializationContext*](serialization.baseserializationcontext.md) |

**Returns:** *boolean*

Defined in: [serialization.ts:403](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L403)

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

Defined in: [serialization.ts:415](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L415)

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

Defined in: [serialization.ts:454](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L454)

[Adaptive Cards Javascript SDK](../README.md) / [adaptivecards](../modules/adaptivecards.md) / CustomProperty

# Class: CustomProperty<T\>

[adaptivecards](../modules/adaptivecards.md).CustomProperty

## Type parameters

Name |
:------ |
`T` |

## Hierarchy

* [*PropertyDefinition*](serialization.propertydefinition.md)

  ↳ **CustomProperty**

## Table of contents

### Constructors

- [constructor](adaptivecards.customproperty.md#constructor)

### Properties

- [defaultValue](adaptivecards.customproperty.md#defaultvalue)
- [isSerializationEnabled](adaptivecards.customproperty.md#isserializationenabled)
- [name](adaptivecards.customproperty.md#name)
- [onGetInitialValue](adaptivecards.customproperty.md#ongetinitialvalue)
- [onParse](adaptivecards.customproperty.md#onparse)
- [onToJSON](adaptivecards.customproperty.md#ontojson)
- [sequentialNumber](adaptivecards.customproperty.md#sequentialnumber)
- [targetVersion](adaptivecards.customproperty.md#targetversion)

### Methods

- [getInternalName](adaptivecards.customproperty.md#getinternalname)
- [parse](adaptivecards.customproperty.md#parse)
- [toJSON](adaptivecards.customproperty.md#tojson)

## Constructors

### constructor

\+ **new CustomProperty**<T\>(`targetVersion`: [*Version*](serialization.version.md), `name`: *string*, `onParse`: (`sender`: [*SerializableObject*](serialization.serializableobject.md), `property`: [*PropertyDefinition*](serialization.propertydefinition.md), `source`: [*PropertyBag*](../modules/serialization.md#propertybag), `context`: [*BaseSerializationContext*](serialization.baseserializationcontext.md)) => T, `onToJSON`: (`sender`: [*SerializableObject*](serialization.serializableobject.md), `property`: [*PropertyDefinition*](serialization.propertydefinition.md), `target`: [*PropertyBag*](../modules/serialization.md#propertybag), `value`: T, `context`: [*BaseSerializationContext*](serialization.baseserializationcontext.md)) => *void*, `defaultValue?`: T, `onGetInitialValue?`: (`sender`: [*SerializableObject*](serialization.serializableobject.md)) => T): [*CustomProperty*](serialization.customproperty.md)<T\>

#### Type parameters:

Name |
:------ |
`T` |

#### Parameters:

Name | Type |
:------ | :------ |
`targetVersion` | [*Version*](serialization.version.md) |
`name` | *string* |
`onParse` | (`sender`: [*SerializableObject*](serialization.serializableobject.md), `property`: [*PropertyDefinition*](serialization.propertydefinition.md), `source`: [*PropertyBag*](../modules/serialization.md#propertybag), `context`: [*BaseSerializationContext*](serialization.baseserializationcontext.md)) => T |
`onToJSON` | (`sender`: [*SerializableObject*](serialization.serializableobject.md), `property`: [*PropertyDefinition*](serialization.propertydefinition.md), `target`: [*PropertyBag*](../modules/serialization.md#propertybag), `value`: T, `context`: [*BaseSerializationContext*](serialization.baseserializationcontext.md)) => *void* |
`defaultValue?` | T |
`onGetInitialValue?` | (`sender`: [*SerializableObject*](serialization.serializableobject.md)) => T |

**Returns:** [*CustomProperty*](serialization.customproperty.md)<T\>

Inherited from: [PropertyDefinition](serialization.propertydefinition.md)

Defined in: [serialization.ts:690](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L690)

## Properties

### defaultValue

• `Optional` `Readonly` **defaultValue**: *undefined* \| T

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

• `Optional` `Readonly` **onGetInitialValue**: *undefined* \| (`sender`: [*SerializableObject*](serialization.serializableobject.md)) => T

Inherited from: [PropertyDefinition](serialization.propertydefinition.md).[onGetInitialValue](serialization.propertydefinition.md#ongetinitialvalue)

___

### onParse

• `Readonly` **onParse**: (`sender`: [*SerializableObject*](serialization.serializableobject.md), `property`: [*PropertyDefinition*](serialization.propertydefinition.md), `source`: [*PropertyBag*](../modules/serialization.md#propertybag), `context`: [*BaseSerializationContext*](serialization.baseserializationcontext.md)) => T

#### Type declaration:

▸ (`sender`: [*SerializableObject*](serialization.serializableobject.md), `property`: [*PropertyDefinition*](serialization.propertydefinition.md), `source`: [*PropertyBag*](../modules/serialization.md#propertybag), `context`: [*BaseSerializationContext*](serialization.baseserializationcontext.md)): T

#### Parameters:

Name | Type |
:------ | :------ |
`sender` | [*SerializableObject*](serialization.serializableobject.md) |
`property` | [*PropertyDefinition*](serialization.propertydefinition.md) |
`source` | [*PropertyBag*](../modules/serialization.md#propertybag) |
`context` | [*BaseSerializationContext*](serialization.baseserializationcontext.md) |

**Returns:** T

Defined in: [serialization.ts:695](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L695)

___

### onToJSON

• `Readonly` **onToJSON**: (`sender`: [*SerializableObject*](serialization.serializableobject.md), `property`: [*PropertyDefinition*](serialization.propertydefinition.md), `target`: [*PropertyBag*](../modules/serialization.md#propertybag), `value`: T, `context`: [*BaseSerializationContext*](serialization.baseserializationcontext.md)) => *void*

#### Type declaration:

▸ (`sender`: [*SerializableObject*](serialization.serializableobject.md), `property`: [*PropertyDefinition*](serialization.propertydefinition.md), `target`: [*PropertyBag*](../modules/serialization.md#propertybag), `value`: T, `context`: [*BaseSerializationContext*](serialization.baseserializationcontext.md)): *void*

#### Parameters:

Name | Type |
:------ | :------ |
`sender` | [*SerializableObject*](serialization.serializableobject.md) |
`property` | [*PropertyDefinition*](serialization.propertydefinition.md) |
`target` | [*PropertyBag*](../modules/serialization.md#propertybag) |
`value` | T |
`context` | [*BaseSerializationContext*](serialization.baseserializationcontext.md) |

**Returns:** *void*

Defined in: [serialization.ts:696](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L696)

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

▸ **parse**(`sender`: [*SerializableObject*](serialization.serializableobject.md), `source`: [*PropertyBag*](../modules/serialization.md#propertybag), `context`: [*BaseSerializationContext*](serialization.baseserializationcontext.md)): T

#### Parameters:

Name | Type |
:------ | :------ |
`sender` | [*SerializableObject*](serialization.serializableobject.md) |
`source` | [*PropertyBag*](../modules/serialization.md#propertybag) |
`context` | [*BaseSerializationContext*](serialization.baseserializationcontext.md) |

**Returns:** T

Overrides: [PropertyDefinition](serialization.propertydefinition.md)

Defined in: [serialization.ts:684](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L684)

___

### toJSON

▸ **toJSON**(`sender`: [*SerializableObject*](serialization.serializableobject.md), `target`: [*PropertyBag*](../modules/serialization.md#propertybag), `value`: T, `context`: [*BaseSerializationContext*](serialization.baseserializationcontext.md)): *void*

#### Parameters:

Name | Type |
:------ | :------ |
`sender` | [*SerializableObject*](serialization.serializableobject.md) |
`target` | [*PropertyBag*](../modules/serialization.md#propertybag) |
`value` | T |
`context` | [*BaseSerializationContext*](serialization.baseserializationcontext.md) |

**Returns:** *void*

Overrides: [PropertyDefinition](serialization.propertydefinition.md)

Defined in: [serialization.ts:688](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L688)

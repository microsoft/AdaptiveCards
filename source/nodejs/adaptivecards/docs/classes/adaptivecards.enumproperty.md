[Adaptive Cards Javascript SDK](../README.md) / [adaptivecards](../modules/adaptivecards.md) / EnumProperty

# Class: EnumProperty<TEnum\>

[adaptivecards](../modules/adaptivecards.md).EnumProperty

## Type parameters

Name | Type |
:------ | :------ |
`TEnum` | *object* |

## Hierarchy

* [*PropertyDefinition*](serialization.propertydefinition.md)

  ↳ **EnumProperty**

## Table of contents

### Constructors

- [constructor](adaptivecards.enumproperty.md#constructor)

### Properties

- [defaultValue](adaptivecards.enumproperty.md#defaultvalue)
- [enumType](adaptivecards.enumproperty.md#enumtype)
- [isSerializationEnabled](adaptivecards.enumproperty.md#isserializationenabled)
- [name](adaptivecards.enumproperty.md#name)
- [onGetInitialValue](adaptivecards.enumproperty.md#ongetinitialvalue)
- [sequentialNumber](adaptivecards.enumproperty.md#sequentialnumber)
- [targetVersion](adaptivecards.enumproperty.md#targetversion)

### Accessors

- [values](adaptivecards.enumproperty.md#values)

### Methods

- [getInternalName](adaptivecards.enumproperty.md#getinternalname)
- [parse](adaptivecards.enumproperty.md#parse)
- [toJSON](adaptivecards.enumproperty.md#tojson)

## Constructors

### constructor

\+ **new EnumProperty**<TEnum\>(`targetVersion`: [*Version*](serialization.version.md), `name`: *string*, `enumType`: TEnum, `defaultValue?`: *number*, `values?`: [*IVersionedValue*](../interfaces/serialization.iversionedvalue.md)<number\>[], `onGetInitialValue?`: (`sender`: [*SerializableObject*](serialization.serializableobject.md)) => *number*): [*EnumProperty*](serialization.enumproperty.md)<TEnum\>

#### Type parameters:

Name | Type |
:------ | :------ |
`TEnum` | *object* |

#### Parameters:

Name | Type |
:------ | :------ |
`targetVersion` | [*Version*](serialization.version.md) |
`name` | *string* |
`enumType` | TEnum |
`defaultValue?` | *number* |
`values?` | [*IVersionedValue*](../interfaces/serialization.iversionedvalue.md)<number\>[] |
`onGetInitialValue?` | (`sender`: [*SerializableObject*](serialization.serializableobject.md)) => *number* |

**Returns:** [*EnumProperty*](serialization.enumproperty.md)<TEnum\>

Inherited from: [PropertyDefinition](serialization.propertydefinition.md)

Defined in: [serialization.ts:575](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L575)

## Properties

### defaultValue

• `Optional` `Readonly` **defaultValue**: *undefined* \| *number*

Inherited from: [PropertyDefinition](serialization.propertydefinition.md).[defaultValue](serialization.propertydefinition.md#defaultvalue)

___

### enumType

• `Readonly` **enumType**: TEnum

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

• `Optional` `Readonly` **onGetInitialValue**: *undefined* \| (`sender`: [*SerializableObject*](serialization.serializableobject.md)) => *number*

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

## Accessors

### values

• get **values**(): [*IVersionedValue*](../interfaces/serialization.iversionedvalue.md)<number\>[]

**Returns:** [*IVersionedValue*](../interfaces/serialization.iversionedvalue.md)<number\>[]

Defined in: [serialization.ts:600](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L600)

## Methods

### getInternalName

▸ **getInternalName**(): *string*

**Returns:** *string*

Inherited from: [PropertyDefinition](serialization.propertydefinition.md)

Defined in: [serialization.ts:262](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L262)

___

### parse

▸ **parse**(`sender`: [*SerializableObject*](serialization.serializableobject.md), `source`: [*PropertyBag*](../modules/serialization.md#propertybag), `context`: [*BaseSerializationContext*](serialization.baseserializationcontext.md)): *undefined* \| *number*

#### Parameters:

Name | Type |
:------ | :------ |
`sender` | [*SerializableObject*](serialization.serializableobject.md) |
`source` | [*PropertyBag*](../modules/serialization.md#propertybag) |
`context` | [*BaseSerializationContext*](serialization.baseserializationcontext.md) |

**Returns:** *undefined* \| *number*

Overrides: [PropertyDefinition](serialization.propertydefinition.md)

Defined in: [serialization.ts:502](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L502)

___

### toJSON

▸ **toJSON**(`sender`: [*SerializableObject*](serialization.serializableobject.md), `target`: [*PropertyBag*](../modules/serialization.md#propertybag), `value`: *undefined* \| *number*, `context`: [*BaseSerializationContext*](serialization.baseserializationcontext.md)): *void*

#### Parameters:

Name | Type |
:------ | :------ |
`sender` | [*SerializableObject*](serialization.serializableobject.md) |
`target` | [*PropertyBag*](../modules/serialization.md#propertybag) |
`value` | *undefined* \| *number* |
`context` | [*BaseSerializationContext*](serialization.baseserializationcontext.md) |

**Returns:** *void*

Overrides: [PropertyDefinition](serialization.propertydefinition.md)

Defined in: [serialization.ts:543](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L543)

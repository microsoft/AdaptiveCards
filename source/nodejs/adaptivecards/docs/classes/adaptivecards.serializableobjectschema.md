[Adaptive Cards Javascript SDK](../README.md) / [adaptivecards](../modules/adaptivecards.md) / SerializableObjectSchema

# Class: SerializableObjectSchema

[adaptivecards](../modules/adaptivecards.md).SerializableObjectSchema

## Table of contents

### Constructors

- [constructor](adaptivecards.serializableobjectschema.md#constructor)

### Methods

- [add](adaptivecards.serializableobjectschema.md#add)
- [getCount](adaptivecards.serializableobjectschema.md#getcount)
- [getItemAt](adaptivecards.serializableobjectschema.md#getitemat)
- [indexOf](adaptivecards.serializableobjectschema.md#indexof)
- [remove](adaptivecards.serializableobjectschema.md#remove)

## Constructors

### constructor

\+ **new SerializableObjectSchema**(): [*SerializableObjectSchema*](serialization.serializableobjectschema.md)

**Returns:** [*SerializableObjectSchema*](serialization.serializableobjectschema.md)

## Methods

### add

▸ **add**(...`properties`: [*PropertyDefinition*](serialization.propertydefinition.md)[]): *void*

#### Parameters:

Name | Type |
:------ | :------ |
`...properties` | [*PropertyDefinition*](serialization.propertydefinition.md)[] |

**Returns:** *void*

Defined in: [serialization.ts:724](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L724)

___

### getCount

▸ **getCount**(): *number*

**Returns:** *number*

Defined in: [serialization.ts:751](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L751)

___

### getItemAt

▸ **getItemAt**(`index`: *number*): [*PropertyDefinition*](serialization.propertydefinition.md)

#### Parameters:

Name | Type |
:------ | :------ |
`index` | *number* |

**Returns:** [*PropertyDefinition*](serialization.propertydefinition.md)

Defined in: [serialization.ts:747](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L747)

___

### indexOf

▸ **indexOf**(`property`: [*PropertyDefinition*](serialization.propertydefinition.md)): *number*

#### Parameters:

Name | Type |
:------ | :------ |
`property` | [*PropertyDefinition*](serialization.propertydefinition.md) |

**Returns:** *number*

Defined in: [serialization.ts:714](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L714)

___

### remove

▸ **remove**(...`properties`: [*PropertyDefinition*](serialization.propertydefinition.md)[]): *void*

#### Parameters:

Name | Type |
:------ | :------ |
`...properties` | [*PropertyDefinition*](serialization.propertydefinition.md)[] |

**Returns:** *void*

Defined in: [serialization.ts:732](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L732)

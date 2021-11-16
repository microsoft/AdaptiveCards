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

\+ **new SerializableObjectSchema**(): [_SerializableObjectSchema_](serialization.serializableobjectschema.md)

**Returns:** [_SerializableObjectSchema_](serialization.serializableobjectschema.md)

## Methods

### add

▸ **add**(...`properties`: [_PropertyDefinition_](serialization.propertydefinition.md)[]): _void_

#### Parameters:

| Name            | Type                                                          |
| :-------------- | :------------------------------------------------------------ |
| `...properties` | [_PropertyDefinition_](serialization.propertydefinition.md)[] |

**Returns:** _void_

Defined in: [serialization.ts:724](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L724)

---

### getCount

▸ **getCount**(): _number_

**Returns:** _number_

Defined in: [serialization.ts:751](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L751)

---

### getItemAt

▸ **getItemAt**(`index`: _number_): [_PropertyDefinition_](serialization.propertydefinition.md)

#### Parameters:

| Name    | Type     |
| :------ | :------- |
| `index` | _number_ |

**Returns:** [_PropertyDefinition_](serialization.propertydefinition.md)

Defined in: [serialization.ts:747](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L747)

---

### indexOf

▸ **indexOf**(`property`: [_PropertyDefinition_](serialization.propertydefinition.md)): _number_

#### Parameters:

| Name       | Type                                                        |
| :--------- | :---------------------------------------------------------- |
| `property` | [_PropertyDefinition_](serialization.propertydefinition.md) |

**Returns:** _number_

Defined in: [serialization.ts:714](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L714)

---

### remove

▸ **remove**(...`properties`: [_PropertyDefinition_](serialization.propertydefinition.md)[]): _void_

#### Parameters:

| Name            | Type                                                          |
| :-------------- | :------------------------------------------------------------ |
| `...properties` | [_PropertyDefinition_](serialization.propertydefinition.md)[] |

**Returns:** _void_

Defined in: [serialization.ts:732](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L732)

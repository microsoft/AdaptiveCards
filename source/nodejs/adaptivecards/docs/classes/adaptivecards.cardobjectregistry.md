[Adaptive Cards Javascript SDK](../README.md) / [adaptivecards](../modules/adaptivecards.md) / CardObjectRegistry

# Class: CardObjectRegistry<T\>

[adaptivecards](../modules/adaptivecards.md).CardObjectRegistry

## Type parameters

| Name | Type                                                        |
| :--- | :---------------------------------------------------------- |
| `T`  | [_SerializableObject_](serialization.serializableobject.md) |

## Table of contents

### Constructors

- [constructor](adaptivecards.cardobjectregistry.md#constructor)

### Methods

- [clear](adaptivecards.cardobjectregistry.md#clear)
- [createInstance](adaptivecards.cardobjectregistry.md#createinstance)
- [findByName](adaptivecards.cardobjectregistry.md#findbyname)
- [getItemAt](adaptivecards.cardobjectregistry.md#getitemat)
- [getItemCount](adaptivecards.cardobjectregistry.md#getitemcount)
- [register](adaptivecards.cardobjectregistry.md#register)
- [unregister](adaptivecards.cardobjectregistry.md#unregister)

## Constructors

### constructor

\+ **new CardObjectRegistry**<T\>(): [_CardObjectRegistry_](registry.cardobjectregistry.md)<T\>

#### Type parameters:

| Name | Type                                                            |
| :--- | :-------------------------------------------------------------- |
| `T`  | [_SerializableObject_](serialization.serializableobject.md)<T\> |

**Returns:** [_CardObjectRegistry_](registry.cardobjectregistry.md)<T\>

## Methods

### clear

▸ **clear**(): _void_

**Returns:** _void_

Defined in: [registry.ts:18](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/registry.ts#L18)

---

### createInstance

▸ **createInstance**(`typeName`: _string_, `targetVersion`: [_Version_](serialization.version.md)): _undefined_ \| T

#### Parameters:

| Name            | Type                                  |
| :-------------- | :------------------------------------ |
| `typeName`      | _string_                              |
| `targetVersion` | [_Version_](serialization.version.md) |

**Returns:** _undefined_ \| T

Defined in: [registry.ts:43](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/registry.ts#L43)

---

### findByName

▸ **findByName**(`typeName`: _string_): _undefined_ \| [_ITypeRegistration_](../interfaces/registry.ityperegistration.md)<T\>

#### Parameters:

| Name       | Type     |
| :--------- | :------- |
| `typeName` | _string_ |

**Returns:** _undefined_ \| [_ITypeRegistration_](../interfaces/registry.ityperegistration.md)<T\>

Defined in: [registry.ts:14](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/registry.ts#L14)

---

### getItemAt

▸ **getItemAt**(`index`: _number_): [_ITypeRegistration_](../interfaces/registry.ityperegistration.md)<T\>

#### Parameters:

| Name    | Type     |
| :------ | :------- |
| `index` | _number_ |

**Returns:** [_ITypeRegistration_](../interfaces/registry.ityperegistration.md)<T\>

Defined in: [registry.ts:53](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/registry.ts#L53)

---

### getItemCount

▸ **getItemCount**(): _number_

**Returns:** _number_

Defined in: [registry.ts:49](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/registry.ts#L49)

---

### register

▸ **register**(`typeName`: _string_, `objectType`: () => T, `schemaVersion?`: [_Version_](serialization.version.md)): _void_

#### Parameters:

| Name            | Type                                  |
| :-------------- | :------------------------------------ |
| `typeName`      | _string_                              |
| `objectType`    | () => T                               |
| `schemaVersion` | [_Version_](serialization.version.md) |

**Returns:** _void_

Defined in: [registry.ts:22](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/registry.ts#L22)

---

### unregister

▸ **unregister**(`typeName`: _string_): _void_

#### Parameters:

| Name       | Type     |
| :--------- | :------- |
| `typeName` | _string_ |

**Returns:** _void_

Defined in: [registry.ts:39](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/registry.ts#L39)

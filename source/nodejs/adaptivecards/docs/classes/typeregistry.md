[Adaptive Cards Javascript SDK](../README.md) › [TypeRegistry](typeregistry.md)

# Class: TypeRegistry <**T**>

## Type parameters

▪ **T**

## Hierarchy

* **TypeRegistry**

  ↳ [ElementTypeRegistry](elementtyperegistry.md)

  ↳ [ActionTypeRegistry](actiontyperegistry.md)

## Index

### Constructors

* [constructor](typeregistry.md#constructor)

### Methods

* [clear](typeregistry.md#clear)
* [createInstance](typeregistry.md#createinstance)
* [getItemAt](typeregistry.md#getitemat)
* [getItemCount](typeregistry.md#getitemcount)
* [registerType](typeregistry.md#registertype)
* [reset](typeregistry.md#abstract-reset)
* [unregisterType](typeregistry.md#unregistertype)

## Constructors

###  constructor

\+ **new TypeRegistry**(): *[TypeRegistry](typeregistry.md)*

*Defined in [card-elements.ts:6539](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L6539)*

**Returns:** *[TypeRegistry](typeregistry.md)*

## Methods

###  clear

▸ **clear**(): *void*

*Defined in [card-elements.ts:6545](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L6545)*

**Returns:** *void*

___

###  createInstance

▸ **createInstance**(`typeName`: string): *T*

*Defined in [card-elements.ts:6577](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L6577)*

**Parameters:**

Name | Type |
------ | ------ |
`typeName` | string |

**Returns:** *T*

___

###  getItemAt

▸ **getItemAt**(`index`: number): *[ITypeRegistration](../interfaces/ityperegistration.md)‹T›*

*Defined in [card-elements.ts:6587](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L6587)*

**Parameters:**

Name | Type |
------ | ------ |
`index` | number |

**Returns:** *[ITypeRegistration](../interfaces/ityperegistration.md)‹T›*

___

###  getItemCount

▸ **getItemCount**(): *number*

*Defined in [card-elements.ts:6583](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L6583)*

**Returns:** *number*

___

###  registerType

▸ **registerType**(`typeName`: string, `createInstance`: function): *void*

*Defined in [card-elements.ts:6551](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L6551)*

**Parameters:**

▪ **typeName**: *string*

▪ **createInstance**: *function*

▸ (): *T*

**Returns:** *void*

___

### `Abstract` reset

▸ **reset**(): *any*

*Defined in [card-elements.ts:6549](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L6549)*

**Returns:** *any*

___

###  unregisterType

▸ **unregisterType**(`typeName`: string): *void*

*Defined in [card-elements.ts:6567](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L6567)*

**Parameters:**

Name | Type |
------ | ------ |
`typeName` | string |

**Returns:** *void*

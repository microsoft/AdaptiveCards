[Adaptive Cards Javascript SDK](../README.md) › ["card-elements"](../modules/_card_elements_.md) › [TypeRegistry](_card_elements_.typeregistry.md)

# Class: TypeRegistry <**T**>

## Type parameters

▪ **T**

## Hierarchy

* **TypeRegistry**

  ↳ [ElementTypeRegistry](_card_elements_.elementtyperegistry.md)

  ↳ [ActionTypeRegistry](_card_elements_.actiontyperegistry.md)

## Index

### Constructors

* [constructor](_card_elements_.typeregistry.md#constructor)

### Methods

* [clear](_card_elements_.typeregistry.md#clear)
* [createInstance](_card_elements_.typeregistry.md#createinstance)
* [getItemAt](_card_elements_.typeregistry.md#getitemat)
* [getItemCount](_card_elements_.typeregistry.md#getitemcount)
* [registerType](_card_elements_.typeregistry.md#registertype)
* [reset](_card_elements_.typeregistry.md#abstract-reset)
* [unregisterType](_card_elements_.typeregistry.md#unregistertype)

## Constructors

###  constructor

\+ **new TypeRegistry**(): *[TypeRegistry](_card_elements_.typeregistry.md)*

**Returns:** *[TypeRegistry](_card_elements_.typeregistry.md)*

## Methods

###  clear

▸ **clear**(): *void*

**Returns:** *void*

___

###  createInstance

▸ **createInstance**(`typeName`: string): *T*

**Parameters:**

Name | Type |
------ | ------ |
`typeName` | string |

**Returns:** *T*

___

###  getItemAt

▸ **getItemAt**(`index`: number): *[ITypeRegistration](../interfaces/_card_elements_.ityperegistration.md)‹T›*

**Parameters:**

Name | Type |
------ | ------ |
`index` | number |

**Returns:** *[ITypeRegistration](../interfaces/_card_elements_.ityperegistration.md)‹T›*

___

###  getItemCount

▸ **getItemCount**(): *number*

**Returns:** *number*

___

###  registerType

▸ **registerType**(`typeName`: string, `createInstance`: function): *void*

**Parameters:**

▪ **typeName**: *string*

▪ **createInstance**: *function*

▸ (): *T*

**Returns:** *void*

___

### `Abstract` reset

▸ **reset**(): *any*

**Returns:** *any*

___

###  unregisterType

▸ **unregisterType**(`typeName`: string): *void*

**Parameters:**

Name | Type |
------ | ------ |
`typeName` | string |

**Returns:** *void*

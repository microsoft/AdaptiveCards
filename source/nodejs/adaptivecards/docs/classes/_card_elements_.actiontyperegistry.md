[Adaptive Cards Javascript SDK](../README.md) › ["card-elements"](../modules/_card_elements_.md) › [ActionTypeRegistry](_card_elements_.actiontyperegistry.md)

# Class: ActionTypeRegistry

## Hierarchy

* [TypeRegistry](_card_elements_.typeregistry.md)‹[Action](_card_elements_.action.md)›

  ↳ **ActionTypeRegistry**

## Index

### Constructors

* [constructor](_card_elements_.actiontyperegistry.md#constructor)

### Methods

* [clear](_card_elements_.actiontyperegistry.md#clear)
* [createInstance](_card_elements_.actiontyperegistry.md#createinstance)
* [getItemAt](_card_elements_.actiontyperegistry.md#getitemat)
* [getItemCount](_card_elements_.actiontyperegistry.md#getitemcount)
* [registerType](_card_elements_.actiontyperegistry.md#registertype)
* [reset](_card_elements_.actiontyperegistry.md#reset)
* [unregisterType](_card_elements_.actiontyperegistry.md#unregistertype)

## Constructors

###  constructor

\+ **new ActionTypeRegistry**(): *[ActionTypeRegistry](_card_elements_.actiontyperegistry.md)*

*Inherited from [TypeRegistry](_card_elements_.typeregistry.md).[constructor](_card_elements_.typeregistry.md#constructor)*

**Returns:** *[ActionTypeRegistry](_card_elements_.actiontyperegistry.md)*

## Methods

###  clear

▸ **clear**(): *void*

*Inherited from [TypeRegistry](_card_elements_.typeregistry.md).[clear](_card_elements_.typeregistry.md#clear)*

**Returns:** *void*

___

###  createInstance

▸ **createInstance**(`typeName`: string): *[Action](_card_elements_.action.md)*

*Inherited from [TypeRegistry](_card_elements_.typeregistry.md).[createInstance](_card_elements_.typeregistry.md#createinstance)*

**Parameters:**

Name | Type |
------ | ------ |
`typeName` | string |

**Returns:** *[Action](_card_elements_.action.md)*

___

###  getItemAt

▸ **getItemAt**(`index`: number): *[ITypeRegistration](../interfaces/_card_elements_.ityperegistration.md)‹[Action](_card_elements_.action.md)›*

*Inherited from [TypeRegistry](_card_elements_.typeregistry.md).[getItemAt](_card_elements_.typeregistry.md#getitemat)*

**Parameters:**

Name | Type |
------ | ------ |
`index` | number |

**Returns:** *[ITypeRegistration](../interfaces/_card_elements_.ityperegistration.md)‹[Action](_card_elements_.action.md)›*

___

###  getItemCount

▸ **getItemCount**(): *number*

*Inherited from [TypeRegistry](_card_elements_.typeregistry.md).[getItemCount](_card_elements_.typeregistry.md#getitemcount)*

**Returns:** *number*

___

###  registerType

▸ **registerType**(`typeName`: string, `createInstance`: function): *void*

*Inherited from [TypeRegistry](_card_elements_.typeregistry.md).[registerType](_card_elements_.typeregistry.md#registertype)*

**Parameters:**

▪ **typeName**: *string*

▪ **createInstance**: *function*

▸ (): *[Action](_card_elements_.action.md)*

**Returns:** *void*

___

###  reset

▸ **reset**(): *void*

*Overrides [TypeRegistry](_card_elements_.typeregistry.md).[reset](_card_elements_.typeregistry.md#abstract-reset)*

**Returns:** *void*

___

###  unregisterType

▸ **unregisterType**(`typeName`: string): *void*

*Inherited from [TypeRegistry](_card_elements_.typeregistry.md).[unregisterType](_card_elements_.typeregistry.md#unregistertype)*

**Parameters:**

Name | Type |
------ | ------ |
`typeName` | string |

**Returns:** *void*

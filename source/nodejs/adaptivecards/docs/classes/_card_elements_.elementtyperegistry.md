[Adaptive Cards Javascript SDK](../README.md) › ["card-elements"](../modules/_card_elements_.md) › [ElementTypeRegistry](_card_elements_.elementtyperegistry.md)

# Class: ElementTypeRegistry

## Hierarchy

* [TypeRegistry](_card_elements_.typeregistry.md)‹[CardElement](_card_elements_.cardelement.md)›

  ↳ **ElementTypeRegistry**

## Index

### Constructors

* [constructor](_card_elements_.elementtyperegistry.md#constructor)

### Methods

* [clear](_card_elements_.elementtyperegistry.md#clear)
* [createInstance](_card_elements_.elementtyperegistry.md#createinstance)
* [getItemAt](_card_elements_.elementtyperegistry.md#getitemat)
* [getItemCount](_card_elements_.elementtyperegistry.md#getitemcount)
* [registerType](_card_elements_.elementtyperegistry.md#registertype)
* [reset](_card_elements_.elementtyperegistry.md#reset)
* [unregisterType](_card_elements_.elementtyperegistry.md#unregistertype)

## Constructors

###  constructor

\+ **new ElementTypeRegistry**(): *[ElementTypeRegistry](_card_elements_.elementtyperegistry.md)*

*Inherited from [TypeRegistry](_card_elements_.typeregistry.md).[constructor](_card_elements_.typeregistry.md#constructor)*

**Returns:** *[ElementTypeRegistry](_card_elements_.elementtyperegistry.md)*

## Methods

###  clear

▸ **clear**(): *void*

*Inherited from [TypeRegistry](_card_elements_.typeregistry.md).[clear](_card_elements_.typeregistry.md#clear)*

**Returns:** *void*

___

###  createInstance

▸ **createInstance**(`typeName`: string): *[CardElement](_card_elements_.cardelement.md)*

*Inherited from [TypeRegistry](_card_elements_.typeregistry.md).[createInstance](_card_elements_.typeregistry.md#createinstance)*

**Parameters:**

Name | Type |
------ | ------ |
`typeName` | string |

**Returns:** *[CardElement](_card_elements_.cardelement.md)*

___

###  getItemAt

▸ **getItemAt**(`index`: number): *[ITypeRegistration](../interfaces/_card_elements_.ityperegistration.md)‹[CardElement](_card_elements_.cardelement.md)›*

*Inherited from [TypeRegistry](_card_elements_.typeregistry.md).[getItemAt](_card_elements_.typeregistry.md#getitemat)*

**Parameters:**

Name | Type |
------ | ------ |
`index` | number |

**Returns:** *[ITypeRegistration](../interfaces/_card_elements_.ityperegistration.md)‹[CardElement](_card_elements_.cardelement.md)›*

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

▸ (): *[CardElement](_card_elements_.cardelement.md)*

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

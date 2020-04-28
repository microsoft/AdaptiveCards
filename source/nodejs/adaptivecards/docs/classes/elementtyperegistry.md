[Adaptive Cards Javascript SDK](../README.md) › [ElementTypeRegistry](elementtyperegistry.md)

# Class: ElementTypeRegistry

## Hierarchy

* [TypeRegistry](typeregistry.md)‹[CardElement](cardelement.md)›

  ↳ **ElementTypeRegistry**

## Index

### Constructors

* [constructor](elementtyperegistry.md#constructor)

### Methods

* [clear](elementtyperegistry.md#clear)
* [createInstance](elementtyperegistry.md#createinstance)
* [getItemAt](elementtyperegistry.md#getitemat)
* [getItemCount](elementtyperegistry.md#getitemcount)
* [registerType](elementtyperegistry.md#registertype)
* [reset](elementtyperegistry.md#reset)
* [unregisterType](elementtyperegistry.md#unregistertype)

## Constructors

###  constructor

\+ **new ElementTypeRegistry**(): *[ElementTypeRegistry](elementtyperegistry.md)*

*Inherited from [TypeRegistry](typeregistry.md).[constructor](typeregistry.md#constructor)*

*Defined in [card-elements.ts:6539](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L6539)*

**Returns:** *[ElementTypeRegistry](elementtyperegistry.md)*

## Methods

###  clear

▸ **clear**(): *void*

*Inherited from [TypeRegistry](typeregistry.md).[clear](typeregistry.md#clear)*

*Defined in [card-elements.ts:6545](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L6545)*

**Returns:** *void*

___

###  createInstance

▸ **createInstance**(`typeName`: string): *[CardElement](cardelement.md)*

*Inherited from [TypeRegistry](typeregistry.md).[createInstance](typeregistry.md#createinstance)*

*Defined in [card-elements.ts:6577](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L6577)*

**Parameters:**

Name | Type |
------ | ------ |
`typeName` | string |

**Returns:** *[CardElement](cardelement.md)*

___

###  getItemAt

▸ **getItemAt**(`index`: number): *[ITypeRegistration](../interfaces/ityperegistration.md)‹[CardElement](cardelement.md)›*

*Inherited from [TypeRegistry](typeregistry.md).[getItemAt](typeregistry.md#getitemat)*

*Defined in [card-elements.ts:6587](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L6587)*

**Parameters:**

Name | Type |
------ | ------ |
`index` | number |

**Returns:** *[ITypeRegistration](../interfaces/ityperegistration.md)‹[CardElement](cardelement.md)›*

___

###  getItemCount

▸ **getItemCount**(): *number*

*Inherited from [TypeRegistry](typeregistry.md).[getItemCount](typeregistry.md#getitemcount)*

*Defined in [card-elements.ts:6583](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L6583)*

**Returns:** *number*

___

###  registerType

▸ **registerType**(`typeName`: string, `createInstance`: function): *void*

*Inherited from [TypeRegistry](typeregistry.md).[registerType](typeregistry.md#registertype)*

*Defined in [card-elements.ts:6551](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L6551)*

**Parameters:**

▪ **typeName**: *string*

▪ **createInstance**: *function*

▸ (): *[CardElement](cardelement.md)*

**Returns:** *void*

___

###  reset

▸ **reset**(): *void*

*Overrides [TypeRegistry](typeregistry.md).[reset](typeregistry.md#abstract-reset)*

*Defined in [card-elements.ts:6593](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L6593)*

**Returns:** *void*

___

###  unregisterType

▸ **unregisterType**(`typeName`: string): *void*

*Inherited from [TypeRegistry](typeregistry.md).[unregisterType](typeregistry.md#unregistertype)*

*Defined in [card-elements.ts:6567](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L6567)*

**Parameters:**

Name | Type |
------ | ------ |
`typeName` | string |

**Returns:** *void*

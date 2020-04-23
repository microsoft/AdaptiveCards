[Adaptive Cards Javascript SDK](../README.md) › [Fact](fact.md)

# Class: Fact

## Hierarchy

* [SerializableObject](serializableobject.md)

  ↳ **Fact**

## Index

### Constructors

* [constructor](fact.md#constructor)

### Properties

* [name](fact.md#name)
* [value](fact.md#value)

### Methods

* [getCustomProperty](fact.md#getcustomproperty)
* [parse](fact.md#parse)
* [setCustomProperty](fact.md#setcustomproperty)
* [toJSON](fact.md#tojson)

## Constructors

###  constructor

\+ **new Fact**(`name`: string, `value`: string): *[Fact](fact.md)*

*Defined in [card-elements.ts:1709](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L1709)*

**Parameters:**

Name | Type | Default |
------ | ------ | ------ |
`name` | string | undefined |
`value` | string | undefined |

**Returns:** *[Fact](fact.md)*

## Properties

###  name

• **name**: *string*

*Defined in [card-elements.ts:1708](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L1708)*

___

###  value

• **value**: *string*

*Defined in [card-elements.ts:1709](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L1709)*

## Methods

###  getCustomProperty

▸ **getCustomProperty**(`name`: string): *any*

*Inherited from [SerializableObject](serializableobject.md).[getCustomProperty](serializableobject.md#getcustomproperty)*

*Defined in [card-elements.ts:200](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L200)*

**Parameters:**

Name | Type |
------ | ------ |
`name` | string |

**Returns:** *any*

___

###  parse

▸ **parse**(`json`: any): *void*

*Overrides [SerializableObject](serializableobject.md).[parse](serializableobject.md#parse)*

*Defined in [card-elements.ts:1718](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L1718)*

**Parameters:**

Name | Type |
------ | ------ |
`json` | any |

**Returns:** *void*

___

###  setCustomProperty

▸ **setCustomProperty**(`name`: string, `value`: any): *void*

*Inherited from [SerializableObject](serializableobject.md).[setCustomProperty](serializableobject.md#setcustomproperty)*

*Defined in [card-elements.ts:189](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L189)*

**Parameters:**

Name | Type |
------ | ------ |
`name` | string |
`value` | any |

**Returns:** *void*

___

###  toJSON

▸ **toJSON**(): *any*

*Overrides [SerializableObject](serializableobject.md).[toJSON](serializableobject.md#tojson)*

*Defined in [card-elements.ts:1725](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L1725)*

**Returns:** *any*

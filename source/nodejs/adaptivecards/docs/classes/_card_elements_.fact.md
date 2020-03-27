[Adaptive Cards Javascript SDK](../README.md) › ["card-elements"](../modules/_card_elements_.md) › [Fact](_card_elements_.fact.md)

# Class: Fact

## Hierarchy

* [SerializableObject](_card_elements_.serializableobject.md)

  ↳ **Fact**

## Index

### Constructors

* [constructor](_card_elements_.fact.md#constructor)

### Properties

* [name](_card_elements_.fact.md#name)
* [value](_card_elements_.fact.md#value)

### Methods

* [getCustomProperty](_card_elements_.fact.md#getcustomproperty)
* [parse](_card_elements_.fact.md#parse)
* [setCustomProperty](_card_elements_.fact.md#setcustomproperty)
* [toJSON](_card_elements_.fact.md#tojson)

## Constructors

###  constructor

\+ **new Fact**(`name`: string, `value`: string): *[Fact](_card_elements_.fact.md)*

**Parameters:**

Name | Type | Default |
------ | ------ | ------ |
`name` | string | undefined |
`value` | string | undefined |

**Returns:** *[Fact](_card_elements_.fact.md)*

## Properties

###  name

• **name**: *string*

___

###  value

• **value**: *string*

## Methods

###  getCustomProperty

▸ **getCustomProperty**(`name`: string): *any*

*Inherited from [SerializableObject](_card_elements_.serializableobject.md).[getCustomProperty](_card_elements_.serializableobject.md#getcustomproperty)*

**Parameters:**

Name | Type |
------ | ------ |
`name` | string |

**Returns:** *any*

___

###  parse

▸ **parse**(`json`: any): *void*

*Overrides [SerializableObject](_card_elements_.serializableobject.md).[parse](_card_elements_.serializableobject.md#parse)*

**Parameters:**

Name | Type |
------ | ------ |
`json` | any |

**Returns:** *void*

___

###  setCustomProperty

▸ **setCustomProperty**(`name`: string, `value`: any): *void*

*Inherited from [SerializableObject](_card_elements_.serializableobject.md).[setCustomProperty](_card_elements_.serializableobject.md#setcustomproperty)*

**Parameters:**

Name | Type |
------ | ------ |
`name` | string |
`value` | any |

**Returns:** *void*

___

###  toJSON

▸ **toJSON**(): *any*

*Overrides [SerializableObject](_card_elements_.serializableobject.md).[toJSON](_card_elements_.serializableobject.md#tojson)*

**Returns:** *any*

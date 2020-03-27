[Adaptive Cards Javascript SDK](../README.md) › ["card-elements"](../modules/_card_elements_.md) › [Choice](_card_elements_.choice.md)

# Class: Choice

## Hierarchy

* [SerializableObject](_card_elements_.serializableobject.md)

  ↳ **Choice**

## Index

### Constructors

* [constructor](_card_elements_.choice.md#constructor)

### Properties

* [title](_card_elements_.choice.md#title)
* [value](_card_elements_.choice.md#value)

### Methods

* [getCustomProperty](_card_elements_.choice.md#getcustomproperty)
* [parse](_card_elements_.choice.md#parse)
* [setCustomProperty](_card_elements_.choice.md#setcustomproperty)
* [toJSON](_card_elements_.choice.md#tojson)

## Constructors

###  constructor

\+ **new Choice**(`title`: string, `value`: string): *[Choice](_card_elements_.choice.md)*

**Parameters:**

Name | Type | Default |
------ | ------ | ------ |
`title` | string | undefined |
`value` | string | undefined |

**Returns:** *[Choice](_card_elements_.choice.md)*

## Properties

###  title

• **title**: *string*

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

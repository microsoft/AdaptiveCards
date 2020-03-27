[Adaptive Cards Javascript SDK](../README.md) › ["card-elements"](../modules/_card_elements_.md) › [HttpHeader](_card_elements_.httpheader.md)

# Class: HttpHeader

## Hierarchy

* [SerializableObject](_card_elements_.serializableobject.md)

  ↳ **HttpHeader**

## Index

### Constructors

* [constructor](_card_elements_.httpheader.md#constructor)

### Properties

* [name](_card_elements_.httpheader.md#name)

### Accessors

* [value](_card_elements_.httpheader.md#value)

### Methods

* [getCustomProperty](_card_elements_.httpheader.md#getcustomproperty)
* [getReferencedInputs](_card_elements_.httpheader.md#getreferencedinputs)
* [parse](_card_elements_.httpheader.md#parse)
* [prepareForExecution](_card_elements_.httpheader.md#prepareforexecution)
* [setCustomProperty](_card_elements_.httpheader.md#setcustomproperty)
* [toJSON](_card_elements_.httpheader.md#tojson)

## Constructors

###  constructor

\+ **new HttpHeader**(`name`: string, `value`: string): *[HttpHeader](_card_elements_.httpheader.md)*

**Parameters:**

Name | Type | Default |
------ | ------ | ------ |
`name` | string | "" |
`value` | string | "" |

**Returns:** *[HttpHeader](_card_elements_.httpheader.md)*

## Properties

###  name

• **name**: *string*

## Accessors

###  value

• **get value**(): *string*

**Returns:** *string*

• **set value**(`newValue`: string): *void*

**Parameters:**

Name | Type |
------ | ------ |
`newValue` | string |

**Returns:** *void*

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

###  getReferencedInputs

▸ **getReferencedInputs**(`inputs`: Array‹[Input](_card_elements_.input.md)›, `referencedInputs`: Shared.Dictionary‹[Input](_card_elements_.input.md)›): *void*

**Parameters:**

Name | Type |
------ | ------ |
`inputs` | Array‹[Input](_card_elements_.input.md)› |
`referencedInputs` | Shared.Dictionary‹[Input](_card_elements_.input.md)› |

**Returns:** *void*

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

###  prepareForExecution

▸ **prepareForExecution**(`inputs`: Shared.Dictionary‹[Input](_card_elements_.input.md)›): *void*

**Parameters:**

Name | Type |
------ | ------ |
`inputs` | Shared.Dictionary‹[Input](_card_elements_.input.md)› |

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

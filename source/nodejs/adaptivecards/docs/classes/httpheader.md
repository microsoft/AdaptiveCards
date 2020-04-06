[Adaptive Cards Javascript SDK](../README.md) › [HttpHeader](httpheader.md)

# Class: HttpHeader

## Hierarchy

* [SerializableObject](serializableobject.md)

  ↳ **HttpHeader**

## Index

### Constructors

* [constructor](httpheader.md#constructor)

### Properties

* [name](httpheader.md#name)

### Accessors

* [value](httpheader.md#value)

### Methods

* [getCustomProperty](httpheader.md#getcustomproperty)
* [getReferencedInputs](httpheader.md#getreferencedinputs)
* [parse](httpheader.md#parse)
* [prepareForExecution](httpheader.md#prepareforexecution)
* [setCustomProperty](httpheader.md#setcustomproperty)
* [toJSON](httpheader.md#tojson)

## Constructors

###  constructor

\+ **new HttpHeader**(`name`: string, `value`: string): *[HttpHeader](httpheader.md)*

*Defined in [card-elements.ts:4306](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L4306)*

**Parameters:**

Name | Type | Default |
------ | ------ | ------ |
`name` | string | "" |
`value` | string | "" |

**Returns:** *[HttpHeader](httpheader.md)*

## Properties

###  name

• **name**: *string*

*Defined in [card-elements.ts:4306](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L4306)*

## Accessors

###  value

• **get value**(): *string*

*Defined in [card-elements.ts:4339](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L4339)*

**Returns:** *string*

• **set value**(`newValue`: string): *void*

*Defined in [card-elements.ts:4343](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L4343)*

**Parameters:**

Name | Type |
------ | ------ |
`newValue` | string |

**Returns:** *void*

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

###  getReferencedInputs

▸ **getReferencedInputs**(`inputs`: Array‹[Input](input.md)›, `referencedInputs`: Shared.Dictionary‹[Input](input.md)›): *void*

*Defined in [card-elements.ts:4331](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L4331)*

**Parameters:**

Name | Type |
------ | ------ |
`inputs` | Array‹[Input](input.md)› |
`referencedInputs` | Shared.Dictionary‹[Input](input.md)› |

**Returns:** *void*

___

###  parse

▸ **parse**(`json`: any): *void*

*Overrides [SerializableObject](serializableobject.md).[parse](serializableobject.md#parse)*

*Defined in [card-elements.ts:4315](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L4315)*

**Parameters:**

Name | Type |
------ | ------ |
`json` | any |

**Returns:** *void*

___

###  prepareForExecution

▸ **prepareForExecution**(`inputs`: Shared.Dictionary‹[Input](input.md)›): *void*

*Defined in [card-elements.ts:4335](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L4335)*

**Parameters:**

Name | Type |
------ | ------ |
`inputs` | Shared.Dictionary‹[Input](input.md)› |

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

*Defined in [card-elements.ts:4322](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L4322)*

**Returns:** *any*

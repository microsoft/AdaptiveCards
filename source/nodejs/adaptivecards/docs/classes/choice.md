[Adaptive Cards Javascript SDK](../README.md) › [Choice](choice.md)

# Class: Choice

## Hierarchy

* [SerializableObject](serializableobject.md)

  ↳ **Choice**

## Index

### Constructors

* [constructor](choice.md#constructor)

### Properties

* [title](choice.md#title)
* [value](choice.md#value)

### Methods

* [getCustomProperty](choice.md#getcustomproperty)
* [parse](choice.md#parse)
* [setCustomProperty](choice.md#setcustomproperty)
* [toJSON](choice.md#tojson)

## Constructors

###  constructor

\+ **new Choice**(`title`: string, `value`: string): *[Choice](choice.md)*

*Defined in [card-elements.ts:3248](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L3248)*

**Parameters:**

Name | Type | Default |
------ | ------ | ------ |
`title` | string | undefined |
`value` | string | undefined |

**Returns:** *[Choice](choice.md)*

## Properties

###  title

• **title**: *string*

*Defined in [card-elements.ts:3247](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L3247)*

___

###  value

• **value**: *string*

*Defined in [card-elements.ts:3248](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L3248)*

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

*Defined in [card-elements.ts:3257](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L3257)*

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

*Defined in [card-elements.ts:3264](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L3264)*

**Returns:** *any*

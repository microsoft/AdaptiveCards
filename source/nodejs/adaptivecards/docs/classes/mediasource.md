[Adaptive Cards Javascript SDK](../README.md) › [MediaSource](mediasource.md)

# Class: MediaSource

## Hierarchy

* [SerializableObject](serializableobject.md)

  ↳ **MediaSource**

## Index

### Constructors

* [constructor](mediasource.md#constructor)

### Properties

* [mimeType](mediasource.md#mimetype)
* [url](mediasource.md#url)

### Methods

* [getCustomProperty](mediasource.md#getcustomproperty)
* [parse](mediasource.md#parse)
* [setCustomProperty](mediasource.md#setcustomproperty)
* [toJSON](mediasource.md#tojson)

## Constructors

###  constructor

\+ **new MediaSource**(`url`: string, `mimeType`: string): *[MediaSource](mediasource.md)*

*Defined in [card-elements.ts:2494](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L2494)*

**Parameters:**

Name | Type | Default |
------ | ------ | ------ |
`url` | string | undefined |
`mimeType` | string | undefined |

**Returns:** *[MediaSource](mediasource.md)*

## Properties

###  mimeType

• **mimeType**: *string*

*Defined in [card-elements.ts:2493](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L2493)*

___

###  url

• **url**: *string*

*Defined in [card-elements.ts:2494](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L2494)*

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

▸ **parse**(`json`: any, `errors?`: Array‹[IValidationError](../interfaces/ivalidationerror.md)›): *void*

*Overrides [SerializableObject](serializableobject.md).[parse](serializableobject.md#parse)*

*Defined in [card-elements.ts:2503](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L2503)*

**Parameters:**

Name | Type |
------ | ------ |
`json` | any |
`errors?` | Array‹[IValidationError](../interfaces/ivalidationerror.md)› |

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

*Defined in [card-elements.ts:2510](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L2510)*

**Returns:** *any*

[Adaptive Cards Javascript SDK](../README.md) › ["card-elements"](../modules/_card_elements_.md) › [MediaSource](_card_elements_.mediasource.md)

# Class: MediaSource

## Hierarchy

* [SerializableObject](_card_elements_.serializableobject.md)

  ↳ **MediaSource**

## Index

### Constructors

* [constructor](_card_elements_.mediasource.md#constructor)

### Properties

* [mimeType](_card_elements_.mediasource.md#mimetype)
* [url](_card_elements_.mediasource.md#url)

### Methods

* [getCustomProperty](_card_elements_.mediasource.md#getcustomproperty)
* [parse](_card_elements_.mediasource.md#parse)
* [setCustomProperty](_card_elements_.mediasource.md#setcustomproperty)
* [toJSON](_card_elements_.mediasource.md#tojson)

## Constructors

###  constructor

\+ **new MediaSource**(`url`: string, `mimeType`: string): *[MediaSource](_card_elements_.mediasource.md)*

**Parameters:**

Name | Type | Default |
------ | ------ | ------ |
`url` | string | undefined |
`mimeType` | string | undefined |

**Returns:** *[MediaSource](_card_elements_.mediasource.md)*

## Properties

###  mimeType

• **mimeType**: *string*

___

###  url

• **url**: *string*

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

▸ **parse**(`json`: any, `errors?`: Array‹[IValidationError](../interfaces/_host_config_.ivalidationerror.md)›): *void*

*Overrides [SerializableObject](_card_elements_.serializableobject.md).[parse](_card_elements_.serializableobject.md#parse)*

**Parameters:**

Name | Type |
------ | ------ |
`json` | any |
`errors?` | Array‹[IValidationError](../interfaces/_host_config_.ivalidationerror.md)› |

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

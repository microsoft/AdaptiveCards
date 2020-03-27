[Adaptive Cards Javascript SDK](../README.md) › ["card-elements"](../modules/_card_elements_.md) › [SerializableObject](_card_elements_.serializableobject.md)

# Class: SerializableObject

Represents an object that can be serialized to/from JSON

## Hierarchy

* **SerializableObject**

  ↳ [CardObject](_card_elements_.cardobject.md)

  ↳ [Fact](_card_elements_.fact.md)

  ↳ [MediaSource](_card_elements_.mediasource.md)

  ↳ [InputValidationOptions](_card_elements_.inputvalidationoptions.md)

  ↳ [Choice](_card_elements_.choice.md)

  ↳ [HttpHeader](_card_elements_.httpheader.md)

  ↳ [BackgroundImage](_card_elements_.backgroundimage.md)

## Index

### Methods

* [getCustomProperty](_card_elements_.serializableobject.md#getcustomproperty)
* [parse](_card_elements_.serializableobject.md#parse)
* [setCustomProperty](_card_elements_.serializableobject.md#setcustomproperty)
* [toJSON](_card_elements_.serializableobject.md#tojson)

## Methods

###  getCustomProperty

▸ **getCustomProperty**(`name`: string): *any*

**Parameters:**

Name | Type |
------ | ------ |
`name` | string |

**Returns:** *any*

___

###  parse

▸ **parse**(`json`: any, `errors?`: Array‹[IValidationError](../interfaces/_host_config_.ivalidationerror.md)›): *void*

**Parameters:**

Name | Type |
------ | ------ |
`json` | any |
`errors?` | Array‹[IValidationError](../interfaces/_host_config_.ivalidationerror.md)› |

**Returns:** *void*

___

###  setCustomProperty

▸ **setCustomProperty**(`name`: string, `value`: any): *void*

**Parameters:**

Name | Type |
------ | ------ |
`name` | string |
`value` | any |

**Returns:** *void*

___

###  toJSON

▸ **toJSON**(): *any*

**Returns:** *any*

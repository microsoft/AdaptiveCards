[Adaptive Cards Javascript SDK](../README.md) › ["card-elements"](../modules/_card_elements_.md) › [CardObject](_card_elements_.cardobject.md)

# Class: CardObject

## Hierarchy

* [SerializableObject](_card_elements_.serializableobject.md)

  ↳ **CardObject**

  ↳ [CardElement](_card_elements_.cardelement.md)

  ↳ [Action](_card_elements_.action.md)

## Index

### Properties

* [id](_card_elements_.cardobject.md#id)

### Methods

* [getCustomProperty](_card_elements_.cardobject.md#getcustomproperty)
* [getJsonTypeName](_card_elements_.cardobject.md#abstract-getjsontypename)
* [internalValidateProperties](_card_elements_.cardobject.md#internalvalidateproperties)
* [parse](_card_elements_.cardobject.md#parse)
* [setCustomProperty](_card_elements_.cardobject.md#setcustomproperty)
* [setParent](_card_elements_.cardobject.md#abstract-setparent)
* [shouldFallback](_card_elements_.cardobject.md#abstract-shouldfallback)
* [toJSON](_card_elements_.cardobject.md#tojson)
* [validateProperties](_card_elements_.cardobject.md#validateproperties)

## Properties

###  id

• **id**: *string*

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

### `Abstract` getJsonTypeName

▸ **getJsonTypeName**(): *string*

**Returns:** *string*

___

###  internalValidateProperties

▸ **internalValidateProperties**(`context`: [ValidationResults](_card_elements_.validationresults.md)): *void*

**Parameters:**

Name | Type |
------ | ------ |
`context` | [ValidationResults](_card_elements_.validationresults.md) |

**Returns:** *void*

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

### `Abstract` setParent

▸ **setParent**(`parent`: [CardElement](_card_elements_.cardelement.md)): *any*

**Parameters:**

Name | Type |
------ | ------ |
`parent` | [CardElement](_card_elements_.cardelement.md) |

**Returns:** *any*

___

### `Abstract` shouldFallback

▸ **shouldFallback**(): *boolean*

**Returns:** *boolean*

___

###  toJSON

▸ **toJSON**(): *any*

*Overrides [SerializableObject](_card_elements_.serializableobject.md).[toJSON](_card_elements_.serializableobject.md#tojson)*

**Returns:** *any*

___

###  validateProperties

▸ **validateProperties**(): *[ValidationResults](_card_elements_.validationresults.md)*

**Returns:** *[ValidationResults](_card_elements_.validationresults.md)*

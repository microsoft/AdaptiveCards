[Adaptive Cards Javascript SDK](../README.md) › ["card-elements"](../modules/_card_elements_.md) › [InputValidationOptions](_card_elements_.inputvalidationoptions.md)

# Class: InputValidationOptions

## Hierarchy

* [SerializableObject](_card_elements_.serializableobject.md)

  ↳ **InputValidationOptions**

## Index

### Properties

* [errorMessage](_card_elements_.inputvalidationoptions.md#errormessage)
* [necessity](_card_elements_.inputvalidationoptions.md#necessity)

### Methods

* [getCustomProperty](_card_elements_.inputvalidationoptions.md#getcustomproperty)
* [parse](_card_elements_.inputvalidationoptions.md#parse)
* [setCustomProperty](_card_elements_.inputvalidationoptions.md#setcustomproperty)
* [toJSON](_card_elements_.inputvalidationoptions.md#tojson)

## Properties

###  errorMessage

• **errorMessage**: *string* = undefined

___

###  necessity

• **necessity**: *[InputValidationNecessity](../enums/_enums_.inputvalidationnecessity.md)* = Enums.InputValidationNecessity.Optional

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

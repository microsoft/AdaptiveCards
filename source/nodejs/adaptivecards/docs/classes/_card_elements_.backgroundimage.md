[Adaptive Cards Javascript SDK](../README.md) › ["card-elements"](../modules/_card_elements_.md) › [BackgroundImage](_card_elements_.backgroundimage.md)

# Class: BackgroundImage

## Hierarchy

* [SerializableObject](_card_elements_.serializableobject.md)

  ↳ **BackgroundImage**

## Index

### Properties

* [fillMode](_card_elements_.backgroundimage.md#fillmode)
* [horizontalAlignment](_card_elements_.backgroundimage.md#horizontalalignment)
* [url](_card_elements_.backgroundimage.md#url)
* [verticalAlignment](_card_elements_.backgroundimage.md#verticalalignment)

### Methods

* [apply](_card_elements_.backgroundimage.md#apply)
* [getCustomProperty](_card_elements_.backgroundimage.md#getcustomproperty)
* [isValid](_card_elements_.backgroundimage.md#isvalid)
* [parse](_card_elements_.backgroundimage.md#parse)
* [reset](_card_elements_.backgroundimage.md#reset)
* [setCustomProperty](_card_elements_.backgroundimage.md#setcustomproperty)
* [toJSON](_card_elements_.backgroundimage.md#tojson)

## Properties

###  fillMode

• **fillMode**: *[FillMode](../enums/_enums_.fillmode.md)* = BackgroundImage.defaultFillMode

___

###  horizontalAlignment

• **horizontalAlignment**: *[HorizontalAlignment](../enums/_enums_.horizontalalignment.md)* = BackgroundImage.defaultHorizontalAlignment

___

###  url

• **url**: *string*

___

###  verticalAlignment

• **verticalAlignment**: *[VerticalAlignment](../enums/_enums_.verticalalignment.md)* = BackgroundImage.defaultVerticalAlignment

## Methods

###  apply

▸ **apply**(`element`: HTMLElement): *void*

**Parameters:**

Name | Type |
------ | ------ |
`element` | HTMLElement |

**Returns:** *void*

___

###  getCustomProperty

▸ **getCustomProperty**(`name`: string): *any*

*Inherited from [SerializableObject](_card_elements_.serializableobject.md).[getCustomProperty](_card_elements_.serializableobject.md#getcustomproperty)*

**Parameters:**

Name | Type |
------ | ------ |
`name` | string |

**Returns:** *any*

___

###  isValid

▸ **isValid**(): *boolean*

**Returns:** *boolean*

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

###  reset

▸ **reset**(): *void*

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

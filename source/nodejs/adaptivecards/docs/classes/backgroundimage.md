[Adaptive Cards Javascript SDK](../README.md) › [BackgroundImage](backgroundimage.md)

# Class: BackgroundImage

## Hierarchy

* [SerializableObject](serializableobject.md)

  ↳ **BackgroundImage**

## Index

### Properties

* [fillMode](backgroundimage.md#fillmode)
* [horizontalAlignment](backgroundimage.md#horizontalalignment)
* [url](backgroundimage.md#url)
* [verticalAlignment](backgroundimage.md#verticalalignment)

### Methods

* [apply](backgroundimage.md#apply)
* [getCustomProperty](backgroundimage.md#getcustomproperty)
* [isValid](backgroundimage.md#isvalid)
* [parse](backgroundimage.md#parse)
* [reset](backgroundimage.md#reset)
* [setCustomProperty](backgroundimage.md#setcustomproperty)
* [toJSON](backgroundimage.md#tojson)

## Properties

###  fillMode

• **fillMode**: *[FillMode](../enums/fillmode.md)* = BackgroundImage.defaultFillMode

*Defined in [card-elements.ts:5316](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L5316)*

___

###  horizontalAlignment

• **horizontalAlignment**: *[HorizontalAlignment](../enums/horizontalalignment.md)* = BackgroundImage.defaultHorizontalAlignment

*Defined in [card-elements.ts:5317](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L5317)*

___

###  url

• **url**: *string*

*Defined in [card-elements.ts:5315](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L5315)*

___

###  verticalAlignment

• **verticalAlignment**: *[VerticalAlignment](../enums/verticalalignment.md)* = BackgroundImage.defaultVerticalAlignment

*Defined in [card-elements.ts:5318](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L5318)*

## Methods

###  apply

▸ **apply**(`element`: HTMLElement): *void*

*Defined in [card-elements.ts:5359](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L5359)*

**Parameters:**

Name | Type |
------ | ------ |
`element` | HTMLElement |

**Returns:** *void*

___

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

###  isValid

▸ **isValid**(): *boolean*

*Defined in [card-elements.ts:5400](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L5400)*

**Returns:** *boolean*

___

###  parse

▸ **parse**(`json`: any, `errors?`: Array‹[IValidationError](../interfaces/ivalidationerror.md)›): *void*

*Overrides [SerializableObject](serializableobject.md).[parse](serializableobject.md#parse)*

*Defined in [card-elements.ts:5327](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L5327)*

**Parameters:**

Name | Type |
------ | ------ |
`json` | any |
`errors?` | Array‹[IValidationError](../interfaces/ivalidationerror.md)› |

**Returns:** *void*

___

###  reset

▸ **reset**(): *void*

*Defined in [card-elements.ts:5320](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L5320)*

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

*Defined in [card-elements.ts:5336](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L5336)*

**Returns:** *any*

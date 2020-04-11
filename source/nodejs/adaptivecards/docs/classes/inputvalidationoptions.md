[Adaptive Cards Javascript SDK](../README.md) › [InputValidationOptions](inputvalidationoptions.md)

# Class: InputValidationOptions

## Hierarchy

* [SerializableObject](serializableobject.md)

  ↳ **InputValidationOptions**

## Index

### Properties

* [errorMessage](inputvalidationoptions.md#errormessage)
* [necessity](inputvalidationoptions.md#necessity)

### Methods

* [getCustomProperty](inputvalidationoptions.md#getcustomproperty)
* [parse](inputvalidationoptions.md#parse)
* [setCustomProperty](inputvalidationoptions.md#setcustomproperty)
* [toJSON](inputvalidationoptions.md#tojson)

## Properties

###  errorMessage

• **errorMessage**: *string* = undefined

*Defined in [card-elements.ts:2768](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L2768)*

___

###  necessity

• **necessity**: *[InputValidationNecessity](../enums/inputvalidationnecessity.md)* = Enums.InputValidationNecessity.Optional

*Defined in [card-elements.ts:2767](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L2767)*

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

*Defined in [card-elements.ts:2770](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L2770)*

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

*Defined in [card-elements.ts:2777](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L2777)*

**Returns:** *any*

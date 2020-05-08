[Adaptive Cards Javascript SDK](../README.md) › [SerializableObject](serializableobject.md)

# Class: SerializableObject

Represents an object that can be serialized to/from JSON

## Hierarchy

* **SerializableObject**

  ↳ [CardObject](cardobject.md)

  ↳ [Fact](fact.md)

  ↳ [MediaSource](mediasource.md)

  ↳ [InputValidationOptions](inputvalidationoptions.md)

  ↳ [Choice](choice.md)

  ↳ [HttpHeader](httpheader.md)

  ↳ [BackgroundImage](backgroundimage.md)

## Index

### Methods

* [getCustomProperty](serializableobject.md#getcustomproperty)
* [parse](serializableobject.md#parse)
* [setCustomProperty](serializableobject.md#setcustomproperty)
* [toJSON](serializableobject.md#tojson)

## Methods

###  getCustomProperty

▸ **getCustomProperty**(`name`: string): *any*

*Defined in [card-elements.ts:200](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L200)*

**Parameters:**

Name | Type |
------ | ------ |
`name` | string |

**Returns:** *any*

___

###  parse

▸ **parse**(`json`: any, `errors?`: Array‹[IValidationError](../interfaces/ivalidationerror.md)›): *void*

*Defined in [card-elements.ts:172](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L172)*

**Parameters:**

Name | Type |
------ | ------ |
`json` | any |
`errors?` | Array‹[IValidationError](../interfaces/ivalidationerror.md)› |

**Returns:** *void*

___

###  setCustomProperty

▸ **setCustomProperty**(`name`: string, `value`: any): *void*

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

*Defined in [card-elements.ts:176](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L176)*

**Returns:** *any*

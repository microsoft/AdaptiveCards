[Adaptive Cards Javascript SDK](../README.md) › [CardObject](cardobject.md)

# Class: CardObject

## Hierarchy

* [SerializableObject](serializableobject.md)

  ↳ **CardObject**

  ↳ [CardElement](cardelement.md)

  ↳ [Action](action.md)

## Index

### Properties

* [id](cardobject.md#id)

### Methods

* [getCustomProperty](cardobject.md#getcustomproperty)
* [getJsonTypeName](cardobject.md#abstract-getjsontypename)
* [internalValidateProperties](cardobject.md#internalvalidateproperties)
* [parse](cardobject.md#parse)
* [setCustomProperty](cardobject.md#setcustomproperty)
* [setParent](cardobject.md#abstract-setparent)
* [shouldFallback](cardobject.md#abstract-shouldfallback)
* [toJSON](cardobject.md#tojson)
* [validateProperties](cardobject.md#validateproperties)

## Properties

###  id

• **id**: *string*

*Defined in [card-elements.ts:247](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L247)*

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

### `Abstract` getJsonTypeName

▸ **getJsonTypeName**(): *string*

*Defined in [card-elements.ts:243](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L243)*

**Returns:** *string*

___

###  internalValidateProperties

▸ **internalValidateProperties**(`context`: [ValidationResults](validationresults.md)): *void*

*Defined in [card-elements.ts:249](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L249)*

**Parameters:**

Name | Type |
------ | ------ |
`context` | [ValidationResults](validationresults.md) |

**Returns:** *void*

___

###  parse

▸ **parse**(`json`: any, `errors?`: Array‹[IValidationError](../interfaces/ivalidationerror.md)›): *void*

*Overrides [SerializableObject](serializableobject.md).[parse](serializableobject.md#parse)*

*Defined in [card-elements.ts:269](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L269)*

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

### `Abstract` setParent

▸ **setParent**(`parent`: [CardElement](cardelement.md)): *any*

*Defined in [card-elements.ts:245](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L245)*

**Parameters:**

Name | Type |
------ | ------ |
`parent` | [CardElement](cardelement.md) |

**Returns:** *any*

___

### `Abstract` shouldFallback

▸ **shouldFallback**(): *boolean*

*Defined in [card-elements.ts:244](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L244)*

**Returns:** *boolean*

___

###  toJSON

▸ **toJSON**(): *any*

*Overrides [SerializableObject](serializableobject.md).[toJSON](serializableobject.md#tojson)*

*Defined in [card-elements.ts:275](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L275)*

**Returns:** *any*

___

###  validateProperties

▸ **validateProperties**(): *[ValidationResults](validationresults.md)*

*Defined in [card-elements.ts:284](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L284)*

**Returns:** *[ValidationResults](validationresults.md)*

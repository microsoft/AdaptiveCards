[Adaptive Cards Javascript SDK](../README.md) › [TimeProperty](timeproperty.md)

# Class: TimeProperty

## Hierarchy

  ↳ [CustomProperty](customproperty.md)‹string | undefined›

  ↳ **TimeProperty**

## Index

### Constructors

* [constructor](timeproperty.md#constructor)

### Properties

* [defaultValue](timeproperty.md#optional-defaultvalue)
* [name](timeproperty.md#name)
* [onGetInitialValue](timeproperty.md#optional-ongetinitialvalue)
* [onParse](timeproperty.md#onparse)
* [onToJSON](timeproperty.md#ontojson)
* [targetVersion](timeproperty.md#targetversion)

### Methods

* [getInternalName](timeproperty.md#getinternalname)
* [parse](timeproperty.md#parse)
* [toJSON](timeproperty.md#tojson)

## Constructors

###  constructor

\+ **new TimeProperty**(`targetVersion`: [Version](version.md), `name`: string): *[TimeProperty](timeproperty.md)*

*Overrides [CustomProperty](customproperty.md).[constructor](customproperty.md#constructor)*

*Defined in [card-elements.ts:3148](https://github.com/microsoft/AdaptiveCards/blob/8588bd5ad/source/nodejs/adaptivecards/src/card-elements.ts#L3148)*

**Parameters:**

Name | Type |
------ | ------ |
`targetVersion` | [Version](version.md) |
`name` | string |

**Returns:** *[TimeProperty](timeproperty.md)*

## Properties

### `Optional` defaultValue

• **defaultValue**? : *T*

*Inherited from [CustomProperty](customproperty.md).[defaultValue](customproperty.md#optional-defaultvalue)*

*Overrides [PropertyDefinition](propertydefinition.md).[defaultValue](propertydefinition.md#optional-defaultvalue)*

*Defined in [serialization.ts:644](https://github.com/microsoft/AdaptiveCards/blob/8588bd5ad/source/nodejs/adaptivecards/src/serialization.ts#L644)*

___

###  name

• **name**: *string*

*Overrides [CustomProperty](customproperty.md).[name](customproperty.md#name)*

*Defined in [card-elements.ts:3149](https://github.com/microsoft/AdaptiveCards/blob/8588bd5ad/source/nodejs/adaptivecards/src/card-elements.ts#L3149)*

___

### `Optional` onGetInitialValue

• **onGetInitialValue**? : *undefined | function*

*Inherited from [CustomProperty](customproperty.md).[onGetInitialValue](customproperty.md#optional-ongetinitialvalue)*

*Overrides [PropertyDefinition](propertydefinition.md).[onGetInitialValue](propertydefinition.md#optional-ongetinitialvalue)*

*Defined in [serialization.ts:645](https://github.com/microsoft/AdaptiveCards/blob/8588bd5ad/source/nodejs/adaptivecards/src/serialization.ts#L645)*

___

###  onParse

• **onParse**: *function*

*Inherited from [CustomProperty](customproperty.md).[onParse](customproperty.md#onparse)*

*Defined in [serialization.ts:642](https://github.com/microsoft/AdaptiveCards/blob/8588bd5ad/source/nodejs/adaptivecards/src/serialization.ts#L642)*

#### Type declaration:

▸ (`sender`: [SerializableObject](serializableobject.md), `property`: [PropertyDefinition](propertydefinition.md), `source`: [PropertyBag](../README.md#propertybag), `context`: [BaseSerializationContext](baseserializationcontext.md)): *string | undefined*

**Parameters:**

Name | Type |
------ | ------ |
`sender` | [SerializableObject](serializableobject.md) |
`property` | [PropertyDefinition](propertydefinition.md) |
`source` | [PropertyBag](../README.md#propertybag) |
`context` | [BaseSerializationContext](baseserializationcontext.md) |

___

###  onToJSON

• **onToJSON**: *function*

*Inherited from [CustomProperty](customproperty.md).[onToJSON](customproperty.md#ontojson)*

*Defined in [serialization.ts:643](https://github.com/microsoft/AdaptiveCards/blob/8588bd5ad/source/nodejs/adaptivecards/src/serialization.ts#L643)*

#### Type declaration:

▸ (`sender`: [SerializableObject](serializableobject.md), `property`: [PropertyDefinition](propertydefinition.md), `target`: [PropertyBag](../README.md#propertybag), `value`: string | undefined, `context`: [BaseSerializationContext](baseserializationcontext.md)): *void*

**Parameters:**

Name | Type |
------ | ------ |
`sender` | [SerializableObject](serializableobject.md) |
`property` | [PropertyDefinition](propertydefinition.md) |
`target` | [PropertyBag](../README.md#propertybag) |
`value` | string &#124; undefined |
`context` | [BaseSerializationContext](baseserializationcontext.md) |

___

###  targetVersion

• **targetVersion**: *[Version](version.md)*

*Overrides [CustomProperty](customproperty.md).[targetVersion](customproperty.md#targetversion)*

*Defined in [card-elements.ts:3149](https://github.com/microsoft/AdaptiveCards/blob/8588bd5ad/source/nodejs/adaptivecards/src/card-elements.ts#L3149)*

## Methods

###  getInternalName

▸ **getInternalName**(): *string*

*Inherited from [PropertyDefinition](propertydefinition.md).[getInternalName](propertydefinition.md#getinternalname)*

*Defined in [serialization.ts:244](https://github.com/microsoft/AdaptiveCards/blob/8588bd5ad/source/nodejs/adaptivecards/src/serialization.ts#L244)*

**Returns:** *string*

___

###  parse

▸ **parse**(`sender`: [SerializableObject](serializableobject.md), `source`: [PropertyBag](../README.md#propertybag), `context`: [BaseSerializationContext](baseserializationcontext.md)): *string | undefined*

*Inherited from [CustomProperty](customproperty.md).[parse](customproperty.md#parse)*

*Overrides [PropertyDefinition](propertydefinition.md).[parse](propertydefinition.md#parse)*

*Defined in [serialization.ts:631](https://github.com/microsoft/AdaptiveCards/blob/8588bd5ad/source/nodejs/adaptivecards/src/serialization.ts#L631)*

**Parameters:**

Name | Type |
------ | ------ |
`sender` | [SerializableObject](serializableobject.md) |
`source` | [PropertyBag](../README.md#propertybag) |
`context` | [BaseSerializationContext](baseserializationcontext.md) |

**Returns:** *string | undefined*

___

###  toJSON

▸ **toJSON**(`sender`: [SerializableObject](serializableobject.md), `target`: [PropertyBag](../README.md#propertybag), `value`: string | undefined, `context`: [BaseSerializationContext](baseserializationcontext.md)): *void*

*Inherited from [CustomProperty](customproperty.md).[toJSON](customproperty.md#tojson)*

*Overrides [PropertyDefinition](propertydefinition.md).[toJSON](propertydefinition.md#tojson)*

*Defined in [serialization.ts:635](https://github.com/microsoft/AdaptiveCards/blob/8588bd5ad/source/nodejs/adaptivecards/src/serialization.ts#L635)*

**Parameters:**

Name | Type |
------ | ------ |
`sender` | [SerializableObject](serializableobject.md) |
`target` | [PropertyBag](../README.md#propertybag) |
`value` | string &#124; undefined |
`context` | [BaseSerializationContext](baseserializationcontext.md) |

**Returns:** *void*

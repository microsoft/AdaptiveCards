[Adaptive Cards Javascript SDK](../README.md) › [CustomProperty](customproperty.md)

# Class: CustomProperty <**T**>

## Type parameters

▪ **T**

## Hierarchy

* [PropertyDefinition](propertydefinition.md)

  ↳ **CustomProperty**

  ↳ [TimeProperty](timeproperty.md)

## Index

### Constructors

* [constructor](customproperty.md#constructor)

### Properties

* [defaultValue](customproperty.md#optional-defaultvalue)
* [name](customproperty.md#name)
* [onGetInitialValue](customproperty.md#optional-ongetinitialvalue)
* [onParse](customproperty.md#onparse)
* [onToJSON](customproperty.md#ontojson)
* [targetVersion](customproperty.md#targetversion)

### Methods

* [getInternalName](customproperty.md#getinternalname)
* [parse](customproperty.md#parse)
* [toJSON](customproperty.md#tojson)

## Constructors

###  constructor

\+ **new CustomProperty**(`targetVersion`: [Version](version.md), `name`: string, `onParse`: function, `onToJSON`: function, `defaultValue?`: T, `onGetInitialValue?`: undefined | function): *[CustomProperty](customproperty.md)*

*Overrides [PropertyDefinition](propertydefinition.md).[constructor](propertydefinition.md#constructor)*

*Defined in [serialization.ts:637](https://github.com/microsoft/AdaptiveCards/blob/8588bd5ad/source/nodejs/adaptivecards/src/serialization.ts#L637)*

**Parameters:**

▪ **targetVersion**: *[Version](version.md)*

▪ **name**: *string*

▪ **onParse**: *function*

▸ (`sender`: [SerializableObject](serializableobject.md), `property`: [PropertyDefinition](propertydefinition.md), `source`: [PropertyBag](../README.md#propertybag), `context`: [BaseSerializationContext](baseserializationcontext.md)): *T*

**Parameters:**

Name | Type |
------ | ------ |
`sender` | [SerializableObject](serializableobject.md) |
`property` | [PropertyDefinition](propertydefinition.md) |
`source` | [PropertyBag](../README.md#propertybag) |
`context` | [BaseSerializationContext](baseserializationcontext.md) |

▪ **onToJSON**: *function*

▸ (`sender`: [SerializableObject](serializableobject.md), `property`: [PropertyDefinition](propertydefinition.md), `target`: [PropertyBag](../README.md#propertybag), `value`: T, `context`: [BaseSerializationContext](baseserializationcontext.md)): *void*

**Parameters:**

Name | Type |
------ | ------ |
`sender` | [SerializableObject](serializableobject.md) |
`property` | [PropertyDefinition](propertydefinition.md) |
`target` | [PropertyBag](../README.md#propertybag) |
`value` | T |
`context` | [BaseSerializationContext](baseserializationcontext.md) |

▪`Optional`  **defaultValue**: *T*

▪`Optional`  **onGetInitialValue**: *undefined | function*

**Returns:** *[CustomProperty](customproperty.md)*

## Properties

### `Optional` defaultValue

• **defaultValue**? : *T*

*Overrides [PropertyDefinition](propertydefinition.md).[defaultValue](propertydefinition.md#optional-defaultvalue)*

*Defined in [serialization.ts:644](https://github.com/microsoft/AdaptiveCards/blob/8588bd5ad/source/nodejs/adaptivecards/src/serialization.ts#L644)*

___

###  name

• **name**: *string*

*Overrides [PropertyDefinition](propertydefinition.md).[name](propertydefinition.md#name)*

*Defined in [serialization.ts:641](https://github.com/microsoft/AdaptiveCards/blob/8588bd5ad/source/nodejs/adaptivecards/src/serialization.ts#L641)*

___

### `Optional` onGetInitialValue

• **onGetInitialValue**? : *undefined | function*

*Overrides [PropertyDefinition](propertydefinition.md).[onGetInitialValue](propertydefinition.md#optional-ongetinitialvalue)*

*Defined in [serialization.ts:645](https://github.com/microsoft/AdaptiveCards/blob/8588bd5ad/source/nodejs/adaptivecards/src/serialization.ts#L645)*

___

###  onParse

• **onParse**: *function*

*Defined in [serialization.ts:642](https://github.com/microsoft/AdaptiveCards/blob/8588bd5ad/source/nodejs/adaptivecards/src/serialization.ts#L642)*

#### Type declaration:

▸ (`sender`: [SerializableObject](serializableobject.md), `property`: [PropertyDefinition](propertydefinition.md), `source`: [PropertyBag](../README.md#propertybag), `context`: [BaseSerializationContext](baseserializationcontext.md)): *T*

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

*Defined in [serialization.ts:643](https://github.com/microsoft/AdaptiveCards/blob/8588bd5ad/source/nodejs/adaptivecards/src/serialization.ts#L643)*

#### Type declaration:

▸ (`sender`: [SerializableObject](serializableobject.md), `property`: [PropertyDefinition](propertydefinition.md), `target`: [PropertyBag](../README.md#propertybag), `value`: T, `context`: [BaseSerializationContext](baseserializationcontext.md)): *void*

**Parameters:**

Name | Type |
------ | ------ |
`sender` | [SerializableObject](serializableobject.md) |
`property` | [PropertyDefinition](propertydefinition.md) |
`target` | [PropertyBag](../README.md#propertybag) |
`value` | T |
`context` | [BaseSerializationContext](baseserializationcontext.md) |

___

###  targetVersion

• **targetVersion**: *[Version](version.md)*

*Overrides [PropertyDefinition](propertydefinition.md).[targetVersion](propertydefinition.md#targetversion)*

*Defined in [serialization.ts:640](https://github.com/microsoft/AdaptiveCards/blob/8588bd5ad/source/nodejs/adaptivecards/src/serialization.ts#L640)*

## Methods

###  getInternalName

▸ **getInternalName**(): *string*

*Inherited from [PropertyDefinition](propertydefinition.md).[getInternalName](propertydefinition.md#getinternalname)*

*Defined in [serialization.ts:244](https://github.com/microsoft/AdaptiveCards/blob/8588bd5ad/source/nodejs/adaptivecards/src/serialization.ts#L244)*

**Returns:** *string*

___

###  parse

▸ **parse**(`sender`: [SerializableObject](serializableobject.md), `source`: [PropertyBag](../README.md#propertybag), `context`: [BaseSerializationContext](baseserializationcontext.md)): *T*

*Overrides [PropertyDefinition](propertydefinition.md).[parse](propertydefinition.md#parse)*

*Defined in [serialization.ts:631](https://github.com/microsoft/AdaptiveCards/blob/8588bd5ad/source/nodejs/adaptivecards/src/serialization.ts#L631)*

**Parameters:**

Name | Type |
------ | ------ |
`sender` | [SerializableObject](serializableobject.md) |
`source` | [PropertyBag](../README.md#propertybag) |
`context` | [BaseSerializationContext](baseserializationcontext.md) |

**Returns:** *T*

___

###  toJSON

▸ **toJSON**(`sender`: [SerializableObject](serializableobject.md), `target`: [PropertyBag](../README.md#propertybag), `value`: T, `context`: [BaseSerializationContext](baseserializationcontext.md)): *void*

*Overrides [PropertyDefinition](propertydefinition.md).[toJSON](propertydefinition.md#tojson)*

*Defined in [serialization.ts:635](https://github.com/microsoft/AdaptiveCards/blob/8588bd5ad/source/nodejs/adaptivecards/src/serialization.ts#L635)*

**Parameters:**

Name | Type |
------ | ------ |
`sender` | [SerializableObject](serializableobject.md) |
`target` | [PropertyBag](../README.md#propertybag) |
`value` | T |
`context` | [BaseSerializationContext](baseserializationcontext.md) |

**Returns:** *void*

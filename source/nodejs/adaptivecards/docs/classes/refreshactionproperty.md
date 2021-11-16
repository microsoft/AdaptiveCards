[Adaptive Cards Javascript SDK](../README.md) › [RefreshActionProperty](refreshactionproperty.md)

# Class: RefreshActionProperty

## Hierarchy

* [PropertyDefinition](propertydefinition.md)

  ↳ **RefreshActionProperty**

## Index

### Constructors

* [constructor](refreshactionproperty.md#constructor)

### Properties

* [defaultValue](refreshactionproperty.md#optional-defaultvalue)
* [isSerializationEnabled](refreshactionproperty.md#isserializationenabled)
* [name](refreshactionproperty.md#name)
* [onGetInitialValue](refreshactionproperty.md#optional-ongetinitialvalue)
* [sequentialNumber](refreshactionproperty.md#sequentialnumber)
* [targetVersion](refreshactionproperty.md#targetversion)

### Methods

* [getInternalName](refreshactionproperty.md#getinternalname)
* [parse](refreshactionproperty.md#parse)
* [toJSON](refreshactionproperty.md#tojson)

## Constructors

###  constructor

\+ **new RefreshActionProperty**(`targetVersion`: [Version](version.md), `name`: string): *[RefreshActionProperty](refreshactionproperty.md)*

*Overrides [PropertyDefinition](propertydefinition.md).[constructor](propertydefinition.md#constructor)*

**Parameters:**

Name | Type |
------ | ------ |
`targetVersion` | [Version](version.md) |
`name` | string |

**Returns:** *[RefreshActionProperty](refreshactionproperty.md)*

## Properties

### `Optional` defaultValue

• **defaultValue**? : *any*

*Inherited from [PropertyDefinition](propertydefinition.md).[defaultValue](propertydefinition.md#optional-defaultvalue)*

___

###  isSerializationEnabled

• **isSerializationEnabled**: *boolean* = true

*Inherited from [PropertyDefinition](propertydefinition.md).[isSerializationEnabled](propertydefinition.md#isserializationenabled)*

___

###  name

• **name**: *string*

*Overrides [PropertyDefinition](propertydefinition.md).[name](propertydefinition.md#name)*

___

### `Optional` onGetInitialValue

• **onGetInitialValue**? : *undefined | function*

*Inherited from [PropertyDefinition](propertydefinition.md).[onGetInitialValue](propertydefinition.md#optional-ongetinitialvalue)*

___

###  sequentialNumber

• **sequentialNumber**: *number*

*Inherited from [PropertyDefinition](propertydefinition.md).[sequentialNumber](propertydefinition.md#sequentialnumber)*

___

###  targetVersion

• **targetVersion**: *[Version](version.md)*

*Overrides [PropertyDefinition](propertydefinition.md).[targetVersion](propertydefinition.md#targetversion)*

## Methods

###  getInternalName

▸ **getInternalName**(): *string*

*Inherited from [PropertyDefinition](propertydefinition.md).[getInternalName](propertydefinition.md#getinternalname)*

**Returns:** *string*

___

###  parse

▸ **parse**(`sender`: [RefreshDefinition](refreshdefinition.md), `source`: [PropertyBag](../README.md#propertybag), `context`: [SerializationContext](serializationcontext.md)): *[ExecuteAction](executeaction.md) | undefined*

*Overrides [PropertyDefinition](propertydefinition.md).[parse](propertydefinition.md#parse)*

**Parameters:**

Name | Type |
------ | ------ |
`sender` | [RefreshDefinition](refreshdefinition.md) |
`source` | [PropertyBag](../README.md#propertybag) |
`context` | [SerializationContext](serializationcontext.md) |

**Returns:** *[ExecuteAction](executeaction.md) | undefined*

___

###  toJSON

▸ **toJSON**(`sender`: [SerializableObject](serializableobject.md), `target`: [PropertyBag](../README.md#propertybag), `value`: [ExecuteAction](executeaction.md) | undefined, `context`: [SerializationContext](serializationcontext.md)): *void*

*Overrides [PropertyDefinition](propertydefinition.md).[toJSON](propertydefinition.md#tojson)*

**Parameters:**

Name | Type |
------ | ------ |
`sender` | [SerializableObject](serializableobject.md) |
`target` | [PropertyBag](../README.md#propertybag) |
`value` | [ExecuteAction](executeaction.md) &#124; undefined |
`context` | [SerializationContext](serializationcontext.md) |

**Returns:** *void*

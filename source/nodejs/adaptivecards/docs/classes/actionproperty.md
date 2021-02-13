[Adaptive Cards Javascript SDK](../README.md) › [ActionProperty](actionproperty.md)

# Class: ActionProperty

## Hierarchy

* [PropertyDefinition](propertydefinition.md)

  ↳ **ActionProperty**

## Index

### Constructors

* [constructor](actionproperty.md#constructor)

### Properties

* [defaultValue](actionproperty.md#optional-readonly-defaultvalue)
* [forbiddenActionTypes](actionproperty.md#readonly-forbiddenactiontypes)
* [isSerializationEnabled](actionproperty.md#isserializationenabled)
* [name](actionproperty.md#readonly-name)
* [onGetInitialValue](actionproperty.md#optional-readonly-ongetinitialvalue)
* [sequentialNumber](actionproperty.md#readonly-sequentialnumber)
* [targetVersion](actionproperty.md#readonly-targetversion)

### Methods

* [getInternalName](actionproperty.md#getinternalname)
* [parse](actionproperty.md#parse)
* [toJSON](actionproperty.md#tojson)

## Constructors

###  constructor

\+ **new ActionProperty**(`targetVersion`: [Version](version.md), `name`: string, `forbiddenActionTypes`: string[]): *[ActionProperty](actionproperty.md)*

*Overrides [PropertyDefinition](propertydefinition.md).[constructor](propertydefinition.md#constructor)*

**Parameters:**

Name | Type | Default |
------ | ------ | ------ |
`targetVersion` | [Version](version.md) | - |
`name` | string | - |
`forbiddenActionTypes` | string[] | [] |

**Returns:** *[ActionProperty](actionproperty.md)*

## Properties

### `Optional` `Readonly` defaultValue

• **defaultValue**? : *any*

*Inherited from [PropertyDefinition](propertydefinition.md).[defaultValue](propertydefinition.md#optional-readonly-defaultvalue)*

___

### `Readonly` forbiddenActionTypes

• **forbiddenActionTypes**: *string[]*

___

###  isSerializationEnabled

• **isSerializationEnabled**: *boolean* = true

*Inherited from [PropertyDefinition](propertydefinition.md).[isSerializationEnabled](propertydefinition.md#isserializationenabled)*

___

### `Readonly` name

• **name**: *string*

*Overrides [PropertyDefinition](propertydefinition.md).[name](propertydefinition.md#readonly-name)*

___

### `Optional` `Readonly` onGetInitialValue

• **onGetInitialValue**? : *undefined | function*

*Inherited from [PropertyDefinition](propertydefinition.md).[onGetInitialValue](propertydefinition.md#optional-readonly-ongetinitialvalue)*

___

### `Readonly` sequentialNumber

• **sequentialNumber**: *number*

*Inherited from [PropertyDefinition](propertydefinition.md).[sequentialNumber](propertydefinition.md#readonly-sequentialnumber)*

___

### `Readonly` targetVersion

• **targetVersion**: *[Version](version.md)*

*Overrides [PropertyDefinition](propertydefinition.md).[targetVersion](propertydefinition.md#readonly-targetversion)*

## Methods

###  getInternalName

▸ **getInternalName**(): *string*

*Inherited from [PropertyDefinition](propertydefinition.md).[getInternalName](propertydefinition.md#getinternalname)*

**Returns:** *string*

___

###  parse

▸ **parse**(`sender`: [SerializableObject](serializableobject.md), `source`: [PropertyBag](../README.md#propertybag), `context`: [SerializationContext](serializationcontext.md)): *[Action](action.md) | undefined*

*Overrides [PropertyDefinition](propertydefinition.md).[parse](propertydefinition.md#parse)*

**Parameters:**

Name | Type |
------ | ------ |
`sender` | [SerializableObject](serializableobject.md) |
`source` | [PropertyBag](../README.md#propertybag) |
`context` | [SerializationContext](serializationcontext.md) |

**Returns:** *[Action](action.md) | undefined*

___

###  toJSON

▸ **toJSON**(`sender`: [SerializableObject](serializableobject.md), `target`: [PropertyBag](../README.md#propertybag), `value`: [Action](action.md) | undefined, `context`: [SerializationContext](serializationcontext.md)): *void*

*Overrides [PropertyDefinition](propertydefinition.md).[toJSON](propertydefinition.md#tojson)*

**Parameters:**

Name | Type |
------ | ------ |
`sender` | [SerializableObject](serializableobject.md) |
`target` | [PropertyBag](../README.md#propertybag) |
`value` | [Action](action.md) &#124; undefined |
`context` | [SerializationContext](serializationcontext.md) |

**Returns:** *void*

[Adaptive Cards Javascript SDK](../README.md) › [SerializableObjectSchema](serializableobjectschema.md)

# Class: SerializableObjectSchema

Represents the schema (i.e. list of properties) for any serializable object.

## Hierarchy

* **SerializableObjectSchema**

## Index

### Methods

* [add](serializableobjectschema.md#add)
* [getCount](serializableobjectschema.md#getcount)
* [getItemAt](serializableobjectschema.md#getitemat)
* [indexOf](serializableobjectschema.md#indexof)
* [remove](serializableobjectschema.md#remove)

## Methods

###  add

▸ **add**(...`properties`: [PropertyDefinition](propertydefinition.md)[]): *void*

Adds one or more properties the the schema.

**Parameters:**

Name | Type | Description |
------ | ------ | ------ |
`...properties` | [PropertyDefinition](propertydefinition.md)[] | The properties to add to the schema. Properties that are already part of the schema are not added.  |

**Returns:** *void*

___

###  getCount

▸ **getCount**(): *number*

Gets the number of properties in the schema

**Returns:** *number*

___

###  getItemAt

▸ **getItemAt**(`index`: number): *[PropertyDefinition](propertydefinition.md)*

Gets a property at the specified index.

**Parameters:**

Name | Type | Description |
------ | ------ | ------ |
`index` | number | The index of the property to get. |

**Returns:** *[PropertyDefinition](propertydefinition.md)*

The property at the specified index.

___

###  indexOf

▸ **indexOf**(`property`: [PropertyDefinition](propertydefinition.md)): *number*

Finds the index of a property in the schema.

**Parameters:**

Name | Type | Description |
------ | ------ | ------ |
`property` | [PropertyDefinition](propertydefinition.md) | The property to find the index of. |

**Returns:** *number*

-1 if the property couldn't be found, the zero-based index of the property otherwise.

___

###  remove

▸ **remove**(...`properties`: [PropertyDefinition](propertydefinition.md)[]): *void*

Removes one or more properties from the schema.

**Parameters:**

Name | Type | Description |
------ | ------ | ------ |
`...properties` | [PropertyDefinition](propertydefinition.md)[] | The properties to remove from the schema.  |

**Returns:** *void*

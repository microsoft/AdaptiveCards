[Adaptive Cards Javascript SDK](../README.md) › ["utils"](_utils_.md)

# Module: "utils"

## Index

### Functions

* [appendChild](_utils_.md#appendchild)
* [generateUniqueId](_utils_.md#generateuniqueid)
* [getBoolValue](_utils_.md#getboolvalue)
* [getEnumValue](_utils_.md#getenumvalue)
* [getFitStatus](_utils_.md#getfitstatus)
* [getNumberValue](_utils_.md#getnumbervalue)
* [getStringValue](_utils_.md#getstringvalue)
* [isNullOrEmpty](_utils_.md#isnullorempty)
* [parseHostConfigEnum](_utils_.md#parsehostconfigenum)
* [renderSeparation](_utils_.md#renderseparation)
* [setArrayProperty](_utils_.md#setarrayproperty)
* [setEnumProperty](_utils_.md#setenumproperty)
* [setNumberProperty](_utils_.md#setnumberproperty)
* [setProperty](_utils_.md#setproperty)
* [stringToCssColor](_utils_.md#stringtocsscolor)
* [truncate](_utils_.md#truncate)

## Functions

###  appendChild

▸ **appendChild**(`node`: Node, `child`: Node): *void*

Appends `child` to `node` if `child` is valid

**Parameters:**

Name | Type |
------ | ------ |
`node` | Node |
`child` | Node |

**Returns:** *void*

___

###  generateUniqueId

▸ **generateUniqueId**(): *string*

Generate a UUID prepended with "__ac-"

**Returns:** *string*

___

###  getBoolValue

▸ **getBoolValue**(`value`: any, `defaultValue`: boolean): *boolean*

**Parameters:**

Name | Type |
------ | ------ |
`value` | any |
`defaultValue` | boolean |

**Returns:** *boolean*

`value` if it's a `boolean` or if it's `"true"` or `"false"`. Otherwise returns `defaultValue || undefined`

___

###  getEnumValue

▸ **getEnumValue**(`targetEnum`: object, `name`: string, `defaultValue`: number): *number*

Convert from a `string` to an `enum` value
``` typescript
enum Test {
     Pass,
     Fail,
     Unknown
}
getEnumValue(Test, "Fail", Test.Unknown); // returns 1 (Test.Fail)
getEnumValue(Test, "Not an enum value", Test.Unknown); // returns 2 (Test.Unknown)
```

**Parameters:**

Name | Type | Description |
------ | ------ | ------ |
`targetEnum` | object | `enum` to resolve against |
`name` | string | `string` to look up |
`defaultValue` | number | value to use if lookup fails |

**Returns:** *number*

Numeric `enum` value if lookup succeeded. Otherwise `defaultValue`

___

###  getFitStatus

▸ **getFitStatus**(`element`: HTMLElement, `containerEnd`: number): *[ContainerFitStatus](../enums/_enums_.containerfitstatus.md)*

**Parameters:**

Name | Type |
------ | ------ |
`element` | HTMLElement |
`containerEnd` | number |

**Returns:** *[ContainerFitStatus](../enums/_enums_.containerfitstatus.md)*

___

###  getNumberValue

▸ **getNumberValue**(`obj`: any, `defaultValue`: number): *number*

**Parameters:**

Name | Type | Default |
------ | ------ | ------ |
`obj` | any | - |
`defaultValue` | number | undefined |

**Returns:** *number*

`obj` if `obj` is of type `number`. Otherwise, returns `defaultValue || undefined`

___

###  getStringValue

▸ **getStringValue**(`obj`: any, `defaultValue`: string): *string*

**Parameters:**

Name | Type | Default |
------ | ------ | ------ |
`obj` | any | - |
`defaultValue` | string | undefined |

**Returns:** *string*

`obj.toString()` if `obj` is of type `string`. Otherwise, returns `defaultValue || undefined`

___

###  isNullOrEmpty

▸ **isNullOrEmpty**(`value`: string): *boolean*

**Parameters:**

Name | Type | Description |
------ | ------ | ------ |
`value` | string | string to test |

**Returns:** *boolean*

`true` if `string` is `undefined`, `null`, or `""`

___

###  parseHostConfigEnum

▸ **parseHostConfigEnum**(`targetEnum`: object, `value`: string | number, `defaultValue`: any): *any*

**Parameters:**

Name | Type |
------ | ------ |
`targetEnum` | object |
`value` | string &#124; number |
`defaultValue` | any |

**Returns:** *any*

___

###  renderSeparation

▸ **renderSeparation**(`hostConfig`: [HostConfig](../classes/_host_config_.hostconfig.md), `separationDefinition`: [ISeparationDefinition](../interfaces/_shared_.iseparationdefinition.md), `orientation`: [Orientation](../enums/_enums_.orientation.md)): *HTMLElement*

**Parameters:**

Name | Type |
------ | ------ |
`hostConfig` | [HostConfig](../classes/_host_config_.hostconfig.md) |
`separationDefinition` | [ISeparationDefinition](../interfaces/_shared_.iseparationdefinition.md) |
`orientation` | [Orientation](../enums/_enums_.orientation.md) |

**Returns:** *HTMLElement*

___

###  setArrayProperty

▸ **setArrayProperty**(`target`: object, `propertyName`: string, `propertyValue`: any[]): *void*

**Parameters:**

Name | Type |
------ | ------ |
`target` | object |
`propertyName` | string |
`propertyValue` | any[] |

**Returns:** *void*

___

###  setEnumProperty

▸ **setEnumProperty**(`enumType`: object, `target`: object, `propertyName`: string, `propertyValue`: number, `defaultValue`: number): *void*

**Parameters:**

Name | Type | Default |
------ | ------ | ------ |
`enumType` | object | - |
`target` | object | - |
`propertyName` | string | - |
`propertyValue` | number | - |
`defaultValue` | number | undefined |

**Returns:** *void*

___

###  setNumberProperty

▸ **setNumberProperty**(`target`: object, `propertyName`: string, `propertyValue`: number, `defaultValue`: number): *void*

**Parameters:**

Name | Type | Default | Description |
------ | ------ | ------ | ------ |
`target` | object | - | `object` to set property on |
`propertyName` | string | - | Name of property to set |
`propertyValue` | number | - | Value to set property to |
`defaultValue` | number | undefined | Value to use if `propertyValue` isn't valid  |

**Returns:** *void*

___

###  setProperty

▸ **setProperty**(`target`: object, `propertyName`: string, `propertyValue`: any, `defaultValue`: any): *void*

**Parameters:**

Name | Type | Default | Description |
------ | ------ | ------ | ------ |
`target` | object | - | `object` to set property on |
`propertyName` | string | - | Name of property to set |
`propertyValue` | any | - | Value to set property to |
`defaultValue` | any | undefined | Value to use if `propertyValue` isn't valid  |

**Returns:** *void*

___

###  stringToCssColor

▸ **stringToCssColor**(`color`: string): *string*

**Parameters:**

Name | Type |
------ | ------ |
`color` | string |

**Returns:** *string*

___

###  truncate

▸ **truncate**(`element`: HTMLElement, `maxHeight`: number, `lineHeight?`: number): *void*

**Parameters:**

Name | Type |
------ | ------ |
`element` | HTMLElement |
`maxHeight` | number |
`lineHeight?` | number |

**Returns:** *void*

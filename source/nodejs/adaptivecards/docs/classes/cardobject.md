[Adaptive Cards Javascript SDK](../README.md) › [CardObject](cardobject.md)

# Class: CardObject

## Hierarchy

* [SerializableObject](serializableobject.md)

  ↳ **CardObject**

  ↳ [CardElement](cardelement.md)

  ↳ [Action](action.md)

## Index

### Constructors

* [constructor](cardobject.md#constructor)

### Properties

* [_parent](cardobject.md#protected-optional-_parent)
* [_renderedElement](cardobject.md#protected-optional-_renderedelement)
* [id](cardobject.md#optional-id)
* [maxVersion](cardobject.md#maxversion)
* [onPreProcessPropertyValue](cardobject.md#optional-onpreprocesspropertyvalue)
* [idProperty](cardobject.md#static-readonly-idproperty)
* [onRegisterCustomProperties](cardobject.md#static-optional-onregistercustomproperties)
* [requiresProperty](cardobject.md#static-readonly-requiresproperty)
* [typeNameProperty](cardobject.md#static-readonly-typenameproperty)

### Accessors

* [hostConfig](cardobject.md#hostconfig)
* [parent](cardobject.md#parent)
* [renderedElement](cardobject.md#renderedelement)
* [requires](cardobject.md#requires)

### Methods

* [getCustomProperty](cardobject.md#getcustomproperty)
* [getDefaultSerializationContext](cardobject.md#protected-getdefaultserializationcontext)
* [getJsonTypeName](cardobject.md#abstract-getjsontypename)
* [getRootObject](cardobject.md#getrootobject)
* [getSchema](cardobject.md#getschema)
* [getSchemaKey](cardobject.md#protected-getschemakey)
* [getValue](cardobject.md#protected-getvalue)
* [hasAllDefaultValues](cardobject.md#hasalldefaultvalues)
* [hasDefaultValue](cardobject.md#hasdefaultvalue)
* [internalParse](cardobject.md#protected-internalparse)
* [internalToJSON](cardobject.md#protected-internaltojson)
* [internalValidateProperties](cardobject.md#internalvalidateproperties)
* [parse](cardobject.md#parse)
* [populateSchema](cardobject.md#protected-populateschema)
* [preProcessPropertyValue](cardobject.md#preprocesspropertyvalue)
* [resetDefaultValues](cardobject.md#resetdefaultvalues)
* [setCustomProperty](cardobject.md#setcustomproperty)
* [setParent](cardobject.md#setparent)
* [setShouldFallback](cardobject.md#setshouldfallback)
* [setValue](cardobject.md#protected-setvalue)
* [shouldFallback](cardobject.md#shouldfallback)
* [shouldSerialize](cardobject.md#protected-shouldserialize)
* [toJSON](cardobject.md#tojson)
* [validateProperties](cardobject.md#validateproperties)

## Constructors

###  constructor

\+ **new CardObject**(): *[CardObject](cardobject.md)*

*Inherited from [HostCapabilities](hostcapabilities.md).[constructor](hostcapabilities.md#constructor)*

**Returns:** *[CardObject](cardobject.md)*

## Properties

### `Protected` `Optional` _parent

• **_parent**? : *[CardObject](cardobject.md)*

___

### `Protected` `Optional` _renderedElement

• **_renderedElement**? : *HTMLElement*

___

### `Optional` id

• **id**? : *undefined | string*

___

###  maxVersion

• **maxVersion**: *[Version](version.md)* = Versions.v1_3

*Inherited from [HostCapabilities](hostcapabilities.md).[maxVersion](hostcapabilities.md#maxversion)*

___

### `Optional` onPreProcessPropertyValue

• **onPreProcessPropertyValue**? : *undefined | function*

___

### `Static` `Readonly` idProperty

▪ **idProperty**: *[StringProperty](stringproperty.md)‹›* = new StringProperty(Versions.v1_0, "id")

___

### `Static` `Optional` onRegisterCustomProperties

▪ **onRegisterCustomProperties**? : *undefined | function*

*Inherited from [HostCapabilities](hostcapabilities.md).[onRegisterCustomProperties](hostcapabilities.md#static-optional-onregistercustomproperties)*

___

### `Static` `Readonly` requiresProperty

▪ **requiresProperty**: *[SerializableObjectProperty](serializableobjectproperty.md)‹›* = new SerializableObjectProperty(
        Versions.v1_2,
        "requires",
        HostCapabilities,
        new HostCapabilities())

___

### `Static` `Readonly` typeNameProperty

▪ **typeNameProperty**: *[StringProperty](stringproperty.md)‹›* = new StringProperty(
        Versions.v1_0,
        "type",
        undefined,
        undefined,
        undefined,
        (sender: object) => {
            return (<CardObject>sender).getJsonTypeName()
        })

## Accessors

###  hostConfig

• **get hostConfig**(): *[HostConfig](hostconfig.md)*

**Returns:** *[HostConfig](hostconfig.md)*

___

###  parent

• **get parent**(): *[CardObject](cardobject.md) | undefined*

**Returns:** *[CardObject](cardobject.md) | undefined*

___

###  renderedElement

• **get renderedElement**(): *HTMLElement | undefined*

**Returns:** *HTMLElement | undefined*

___

###  requires

• **get requires**(): *[HostCapabilities](hostcapabilities.md)*

**Returns:** *[HostCapabilities](hostcapabilities.md)*

## Methods

###  getCustomProperty

▸ **getCustomProperty**(`name`: string): *any*

*Inherited from [HostCapabilities](hostcapabilities.md).[getCustomProperty](hostcapabilities.md#getcustomproperty)*

**Parameters:**

Name | Type |
------ | ------ |
`name` | string |

**Returns:** *any*

___

### `Protected` getDefaultSerializationContext

▸ **getDefaultSerializationContext**(): *[BaseSerializationContext](baseserializationcontext.md)*

*Inherited from [HostCapabilities](hostcapabilities.md).[getDefaultSerializationContext](hostcapabilities.md#protected-getdefaultserializationcontext)*

**Returns:** *[BaseSerializationContext](baseserializationcontext.md)*

___

### `Abstract` getJsonTypeName

▸ **getJsonTypeName**(): *string*

**Returns:** *string*

___

###  getRootObject

▸ **getRootObject**(): *[CardObject](cardobject.md)*

**Returns:** *[CardObject](cardobject.md)*

___

###  getSchema

▸ **getSchema**(): *[SerializableObjectSchema](serializableobjectschema.md)*

*Inherited from [HostCapabilities](hostcapabilities.md).[getSchema](hostcapabilities.md#getschema)*

**Returns:** *[SerializableObjectSchema](serializableobjectschema.md)*

___

### `Protected` getSchemaKey

▸ **getSchemaKey**(): *string*

*Overrides [SerializableObject](serializableobject.md).[getSchemaKey](serializableobject.md#protected-abstract-getschemakey)*

**Returns:** *string*

___

### `Protected` getValue

▸ **getValue**(`property`: [PropertyDefinition](propertydefinition.md)): *any*

*Inherited from [HostCapabilities](hostcapabilities.md).[getValue](hostcapabilities.md#protected-getvalue)*

**Parameters:**

Name | Type |
------ | ------ |
`property` | [PropertyDefinition](propertydefinition.md) |

**Returns:** *any*

___

###  hasAllDefaultValues

▸ **hasAllDefaultValues**(): *boolean*

*Inherited from [HostCapabilities](hostcapabilities.md).[hasAllDefaultValues](hostcapabilities.md#hasalldefaultvalues)*

**Returns:** *boolean*

___

###  hasDefaultValue

▸ **hasDefaultValue**(`property`: [PropertyDefinition](propertydefinition.md)): *boolean*

*Inherited from [HostCapabilities](hostcapabilities.md).[hasDefaultValue](hostcapabilities.md#hasdefaultvalue)*

**Parameters:**

Name | Type |
------ | ------ |
`property` | [PropertyDefinition](propertydefinition.md) |

**Returns:** *boolean*

___

### `Protected` internalParse

▸ **internalParse**(`source`: [PropertyBag](../README.md#propertybag), `context`: [BaseSerializationContext](baseserializationcontext.md)): *void*

*Inherited from [SerializableObject](serializableobject.md).[internalParse](serializableobject.md#protected-internalparse)*

**Parameters:**

Name | Type |
------ | ------ |
`source` | [PropertyBag](../README.md#propertybag) |
`context` | [BaseSerializationContext](baseserializationcontext.md) |

**Returns:** *void*

___

### `Protected` internalToJSON

▸ **internalToJSON**(`target`: [PropertyBag](../README.md#propertybag), `context`: [BaseSerializationContext](baseserializationcontext.md)): *void*

*Inherited from [SerializableObject](serializableobject.md).[internalToJSON](serializableobject.md#protected-internaltojson)*

**Parameters:**

Name | Type |
------ | ------ |
`target` | [PropertyBag](../README.md#propertybag) |
`context` | [BaseSerializationContext](baseserializationcontext.md) |

**Returns:** *void*

___

###  internalValidateProperties

▸ **internalValidateProperties**(`context`: [ValidationResults](validationresults.md)): *void*

**Parameters:**

Name | Type |
------ | ------ |
`context` | [ValidationResults](validationresults.md) |

**Returns:** *void*

___

###  parse

▸ **parse**(`source`: [PropertyBag](../README.md#propertybag), `context?`: [BaseSerializationContext](baseserializationcontext.md)): *void*

*Inherited from [HostCapabilities](hostcapabilities.md).[parse](hostcapabilities.md#parse)*

**Parameters:**

Name | Type |
------ | ------ |
`source` | [PropertyBag](../README.md#propertybag) |
`context?` | [BaseSerializationContext](baseserializationcontext.md) |

**Returns:** *void*

___

### `Protected` populateSchema

▸ **populateSchema**(`schema`: [SerializableObjectSchema](serializableobjectschema.md)): *void*

*Inherited from [HostCapabilities](hostcapabilities.md).[populateSchema](hostcapabilities.md#protected-populateschema)*

**Parameters:**

Name | Type |
------ | ------ |
`schema` | [SerializableObjectSchema](serializableobjectschema.md) |

**Returns:** *void*

___

###  preProcessPropertyValue

▸ **preProcessPropertyValue**(`property`: [PropertyDefinition](propertydefinition.md), `propertyValue?`: any): *any*

**Parameters:**

Name | Type |
------ | ------ |
`property` | [PropertyDefinition](propertydefinition.md) |
`propertyValue?` | any |

**Returns:** *any*

___

###  resetDefaultValues

▸ **resetDefaultValues**(): *void*

*Inherited from [HostCapabilities](hostcapabilities.md).[resetDefaultValues](hostcapabilities.md#resetdefaultvalues)*

**Returns:** *void*

___

###  setCustomProperty

▸ **setCustomProperty**(`name`: string, `value`: any): *void*

*Inherited from [HostCapabilities](hostcapabilities.md).[setCustomProperty](hostcapabilities.md#setcustomproperty)*

**Parameters:**

Name | Type |
------ | ------ |
`name` | string |
`value` | any |

**Returns:** *void*

___

###  setParent

▸ **setParent**(`value`: [CardObject](cardobject.md) | undefined): *void*

**Parameters:**

Name | Type |
------ | ------ |
`value` | [CardObject](cardobject.md) &#124; undefined |

**Returns:** *void*

___

###  setShouldFallback

▸ **setShouldFallback**(`value`: boolean): *void*

**Parameters:**

Name | Type |
------ | ------ |
`value` | boolean |

**Returns:** *void*

___

### `Protected` setValue

▸ **setValue**(`property`: [PropertyDefinition](propertydefinition.md), `value`: any): *void*

*Inherited from [HostCapabilities](hostcapabilities.md).[setValue](hostcapabilities.md#protected-setvalue)*

**Parameters:**

Name | Type |
------ | ------ |
`property` | [PropertyDefinition](propertydefinition.md) |
`value` | any |

**Returns:** *void*

___

###  shouldFallback

▸ **shouldFallback**(): *boolean*

**Returns:** *boolean*

___

### `Protected` shouldSerialize

▸ **shouldSerialize**(`context`: [BaseSerializationContext](baseserializationcontext.md)): *boolean*

*Inherited from [HostCapabilities](hostcapabilities.md).[shouldSerialize](hostcapabilities.md#protected-shouldserialize)*

**Parameters:**

Name | Type |
------ | ------ |
`context` | [BaseSerializationContext](baseserializationcontext.md) |

**Returns:** *boolean*

___

###  toJSON

▸ **toJSON**(`context?`: [BaseSerializationContext](baseserializationcontext.md)): *[PropertyBag](../README.md#propertybag) | undefined*

*Inherited from [HostCapabilities](hostcapabilities.md).[toJSON](hostcapabilities.md#tojson)*

**Parameters:**

Name | Type |
------ | ------ |
`context?` | [BaseSerializationContext](baseserializationcontext.md) |

**Returns:** *[PropertyBag](../README.md#propertybag) | undefined*

___

###  validateProperties

▸ **validateProperties**(): *[ValidationResults](validationresults.md)*

**Returns:** *[ValidationResults](validationresults.md)*

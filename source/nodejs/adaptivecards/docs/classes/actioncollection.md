[Adaptive Cards Javascript SDK](../README.md) › [ActionCollection](actioncollection.md)

# Class: ActionCollection

## Hierarchy

* **ActionCollection**

## Index

### Constructors

* [constructor](actioncollection.md#constructor)

### Properties

* [buttons](actioncollection.md#buttons)
* [items](actioncollection.md#items)

### Accessors

* [expandedAction](actioncollection.md#expandedaction)
* [renderedActionCount](actioncollection.md#renderedactioncount)

### Methods

* [actionExecuted](actioncollection.md#actionexecuted)
* [addAction](actioncollection.md#addaction)
* [clear](actioncollection.md#clear)
* [getActionById](actioncollection.md#getactionbyid)
* [getAllInputs](actioncollection.md#getallinputs)
* [getResourceInformation](actioncollection.md#getresourceinformation)
* [parse](actioncollection.md#parse)
* [removeAction](actioncollection.md#removeaction)
* [render](actioncollection.md#render)
* [toJSON](actioncollection.md#tojson)
* [validateProperties](actioncollection.md#validateproperties)

## Constructors

###  constructor

\+ **new ActionCollection**(`owner`: [CardElement](cardelement.md)): *[ActionCollection](actioncollection.md)*

**Parameters:**

Name | Type |
------ | ------ |
`owner` | [CardElement](cardelement.md) |

**Returns:** *[ActionCollection](actioncollection.md)*

## Properties

###  buttons

• **buttons**: *[ActionButton](actionbutton.md)[]* = []

___

###  items

• **items**: *[Action](action.md)[]* = []

## Accessors

###  expandedAction

• **get expandedAction**(): *[ShowCardAction](showcardaction.md) | undefined*

**Returns:** *[ShowCardAction](showcardaction.md) | undefined*

___

###  renderedActionCount

• **get renderedActionCount**(): *number*

**Returns:** *number*

## Methods

###  actionExecuted

▸ **actionExecuted**(`action`: [Action](action.md)): *void*

**Parameters:**

Name | Type |
------ | ------ |
`action` | [Action](action.md) |

**Returns:** *void*

___

###  addAction

▸ **addAction**(`action`: [Action](action.md)): *void*

**Parameters:**

Name | Type |
------ | ------ |
`action` | [Action](action.md) |

**Returns:** *void*

___

###  clear

▸ **clear**(): *void*

**Returns:** *void*

___

###  getActionById

▸ **getActionById**(`id`: string): *[Action](action.md) | undefined*

**Parameters:**

Name | Type |
------ | ------ |
`id` | string |

**Returns:** *[Action](action.md) | undefined*

___

###  getAllInputs

▸ **getAllInputs**(`processActions`: boolean): *[Input](input.md)[]*

**Parameters:**

Name | Type | Default |
------ | ------ | ------ |
`processActions` | boolean | true |

**Returns:** *[Input](input.md)[]*

___

###  getResourceInformation

▸ **getResourceInformation**(): *[IResourceInformation](../interfaces/iresourceinformation.md)[]*

**Returns:** *[IResourceInformation](../interfaces/iresourceinformation.md)[]*

___

###  parse

▸ **parse**(`source`: any, `context`: [SerializationContext](serializationcontext.md)): *void*

**Parameters:**

Name | Type |
------ | ------ |
`source` | any |
`context` | [SerializationContext](serializationcontext.md) |

**Returns:** *void*

___

###  removeAction

▸ **removeAction**(`action`: [Action](action.md)): *boolean*

**Parameters:**

Name | Type |
------ | ------ |
`action` | [Action](action.md) |

**Returns:** *boolean*

___

###  render

▸ **render**(`orientation`: [Orientation](../enums/orientation.md), `isDesignMode`: boolean): *HTMLElement | undefined*

**Parameters:**

Name | Type |
------ | ------ |
`orientation` | [Orientation](../enums/orientation.md) |
`isDesignMode` | boolean |

**Returns:** *HTMLElement | undefined*

___

###  toJSON

▸ **toJSON**(`target`: [PropertyBag](../README.md#propertybag), `propertyName`: string, `context`: [SerializationContext](serializationcontext.md)): *any*

**Parameters:**

Name | Type |
------ | ------ |
`target` | [PropertyBag](../README.md#propertybag) |
`propertyName` | string |
`context` | [SerializationContext](serializationcontext.md) |

**Returns:** *any*

___

###  validateProperties

▸ **validateProperties**(`context`: [ValidationResults](validationresults.md)): *void*

**Parameters:**

Name | Type |
------ | ------ |
`context` | [ValidationResults](validationresults.md) |

**Returns:** *void*

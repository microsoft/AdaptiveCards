[Adaptive Cards Javascript SDK](../README.md) › [ToggleVisibilityAction](togglevisibilityaction.md)

# Class: ToggleVisibilityAction

## Hierarchy

↳ [Action](action.md)

↳ **ToggleVisibilityAction**

## Index

### Constructors

- [constructor](togglevisibilityaction.md#constructor)

### Properties

- [\_parent](togglevisibilityaction.md#protected-optional-_parent)
- [\_renderedElement](togglevisibilityaction.md#protected-optional-_renderedelement)
- [iconUrl](togglevisibilityaction.md#optional-iconurl)
- [id](togglevisibilityaction.md#optional-id)
- [maxVersion](togglevisibilityaction.md#maxversion)
- [onExecute](togglevisibilityaction.md#onexecute)
- [onPreProcessPropertyValue](togglevisibilityaction.md#optional-onpreprocesspropertyvalue)
- [style](togglevisibilityaction.md#style)
- [targetElements](togglevisibilityaction.md#targetelements)
- [title](togglevisibilityaction.md#optional-title)
- [JsonTypeName](togglevisibilityaction.md#static-readonly-jsontypename)
- [iconUrlProperty](togglevisibilityaction.md#static-readonly-iconurlproperty)
- [idProperty](togglevisibilityaction.md#static-readonly-idproperty)
- [onRegisterCustomProperties](togglevisibilityaction.md#static-optional-onregistercustomproperties)
- [requiresProperty](togglevisibilityaction.md#static-readonly-requiresproperty)
- [styleProperty](togglevisibilityaction.md#static-readonly-styleproperty)
- [targetElementsProperty](togglevisibilityaction.md#static-readonly-targetelementsproperty)
- [titleProperty](togglevisibilityaction.md#static-readonly-titleproperty)
- [typeNameProperty](togglevisibilityaction.md#static-readonly-typenameproperty)

### Accessors

- [hostConfig](togglevisibilityaction.md#hostconfig)
- [isPrimary](togglevisibilityaction.md#isprimary)
- [parent](togglevisibilityaction.md#parent)
- [renderedElement](togglevisibilityaction.md#renderedelement)
- [requires](togglevisibilityaction.md#requires)

### Methods

- [addCssClasses](togglevisibilityaction.md#protected-addcssclasses)
- [addTargetElement](togglevisibilityaction.md#addtargetelement)
- [execute](togglevisibilityaction.md#execute)
- [getActionById](togglevisibilityaction.md#getactionbyid)
- [getAllInputs](togglevisibilityaction.md#getallinputs)
- [getAriaRole](togglevisibilityaction.md#getariarole)
- [getCustomProperty](togglevisibilityaction.md#getcustomproperty)
- [getDefaultSerializationContext](togglevisibilityaction.md#protected-getdefaultserializationcontext)
- [getHref](togglevisibilityaction.md#gethref)
- [getJsonTypeName](togglevisibilityaction.md#getjsontypename)
- [getReferencedInputs](togglevisibilityaction.md#getreferencedinputs)
- [getResourceInformation](togglevisibilityaction.md#getresourceinformation)
- [getRootObject](togglevisibilityaction.md#getrootobject)
- [getSchema](togglevisibilityaction.md#getschema)
- [getSchemaKey](togglevisibilityaction.md#protected-getschemakey)
- [getValue](togglevisibilityaction.md#protected-getvalue)
- [hasAllDefaultValues](togglevisibilityaction.md#hasalldefaultvalues)
- [hasDefaultValue](togglevisibilityaction.md#hasdefaultvalue)
- [internalGetReferencedInputs](togglevisibilityaction.md#protected-internalgetreferencedinputs)
- [internalParse](togglevisibilityaction.md#protected-internalparse)
- [internalPrepareForExecution](togglevisibilityaction.md#protected-internalprepareforexecution)
- [internalToJSON](togglevisibilityaction.md#protected-internaltojson)
- [internalValidateInputs](togglevisibilityaction.md#protected-internalvalidateinputs)
- [internalValidateProperties](togglevisibilityaction.md#internalvalidateproperties)
- [parse](togglevisibilityaction.md#parse)
- [populateSchema](togglevisibilityaction.md#protected-populateschema)
- [preProcessPropertyValue](togglevisibilityaction.md#preprocesspropertyvalue)
- [prepareForExecution](togglevisibilityaction.md#prepareforexecution)
- [raiseExecuteActionEvent](togglevisibilityaction.md#protected-raiseexecuteactionevent)
- [remove](togglevisibilityaction.md#remove)
- [removeTargetElement](togglevisibilityaction.md#removetargetelement)
- [render](togglevisibilityaction.md#render)
- [resetDefaultValues](togglevisibilityaction.md#resetdefaultvalues)
- [setCustomProperty](togglevisibilityaction.md#setcustomproperty)
- [setParent](togglevisibilityaction.md#setparent)
- [setShouldFallback](togglevisibilityaction.md#setshouldfallback)
- [setValue](togglevisibilityaction.md#protected-setvalue)
- [shouldFallback](togglevisibilityaction.md#shouldfallback)
- [shouldSerialize](togglevisibilityaction.md#protected-shouldserialize)
- [toJSON](togglevisibilityaction.md#tojson)
- [updateActionButtonCssStyle](togglevisibilityaction.md#updateactionbuttoncssstyle)
- [validateInputs](togglevisibilityaction.md#validateinputs)
- [validateProperties](togglevisibilityaction.md#validateproperties)

## Constructors

### constructor

\+ **new ToggleVisibilityAction**(): _[ToggleVisibilityAction](togglevisibilityaction.md)_

_Inherited from [SerializableObject](serializableobject.md).[constructor](serializableobject.md#constructor)_

**Returns:** _[ToggleVisibilityAction](togglevisibilityaction.md)_

## Properties

### `Protected` `Optional` \_parent

• **\_parent**? : _[CardObject](cardobject.md)_

_Inherited from [CardObject](cardobject.md).[\_parent](cardobject.md#protected-optional-_parent)_

---

### `Protected` `Optional` \_renderedElement

• **\_renderedElement**? : _HTMLElement_

_Inherited from [CardObject](cardobject.md).[\_renderedElement](cardobject.md#protected-optional-_renderedelement)_

---

### `Optional` iconUrl

• **iconUrl**? : _undefined | string_

_Inherited from [Action](action.md).[iconUrl](action.md#optional-iconurl)_

---

### `Optional` id

• **id**? : _undefined | string_

_Inherited from [CardObject](cardobject.md).[id](cardobject.md#optional-id)_

---

### maxVersion

• **maxVersion**: _[Version](version.md)_ = Versions.v1_3

_Inherited from [SerializableObject](serializableobject.md).[maxVersion](serializableobject.md#maxversion)_

---

### onExecute

• **onExecute**: _function_

_Inherited from [Action](action.md).[onExecute](action.md#onexecute)_

#### Type declaration:

▸ (`sender`: [Action](action.md)): _void_

**Parameters:**

| Name     | Type                |
| -------- | ------------------- |
| `sender` | [Action](action.md) |

---

### `Optional` onPreProcessPropertyValue

• **onPreProcessPropertyValue**? : _undefined | function_

_Inherited from [CardObject](cardobject.md).[onPreProcessPropertyValue](cardobject.md#optional-onpreprocesspropertyvalue)_

---

### style

• **style**: _string_ = Enums.ActionStyle.Default

_Inherited from [Action](action.md).[style](action.md#style)_

---

### targetElements

• **targetElements**: _object_

#### Type declaration:

- \[ **key**: _string_\]: any

---

### `Optional` title

• **title**? : _undefined | string_

_Inherited from [Action](action.md).[title](action.md#optional-title)_

---

### `Static` `Readonly` JsonTypeName

▪ **JsonTypeName**: _"Action.ToggleVisibility"_ = "Action.ToggleVisibility"

---

### `Static` `Readonly` iconUrlProperty

▪ **iconUrlProperty**: _[StringProperty](stringproperty.md)‹›_ = new StringProperty(Versions.v1_1, "iconUrl")

_Inherited from [Action](action.md).[iconUrlProperty](action.md#static-readonly-iconurlproperty)_

---

### `Static` `Readonly` idProperty

▪ **idProperty**: _[StringProperty](stringproperty.md)‹›_ = new StringProperty(Versions.v1_0, "id")

_Inherited from [CardObject](cardobject.md).[idProperty](cardobject.md#static-readonly-idproperty)_

---

### `Static` `Optional` onRegisterCustomProperties

▪ **onRegisterCustomProperties**? : _undefined | function_

_Inherited from [SerializableObject](serializableobject.md).[onRegisterCustomProperties](serializableobject.md#static-optional-onregistercustomproperties)_

---

### `Static` `Readonly` requiresProperty

▪ **requiresProperty**: _[SerializableObjectProperty](serializableobjectproperty.md)‹›_ = new SerializableObjectProperty(
Versions.v1_2,
"requires",
HostCapabilities,
false,
new HostCapabilities())

_Inherited from [CardObject](cardobject.md).[requiresProperty](cardobject.md#static-readonly-requiresproperty)_

---

### `Static` `Readonly` styleProperty

▪ **styleProperty**: _[ValueSetProperty](valuesetproperty.md)‹›_ = new ValueSetProperty(
Versions.v1_2,
"style",
[
{ value: Enums.ActionStyle.Default },
{ value: Enums.ActionStyle.Positive },
{ value: Enums.ActionStyle.Destructive }
],
Enums.ActionStyle.Default)

_Inherited from [Action](action.md).[styleProperty](action.md#static-readonly-styleproperty)_

---

### `Static` `Readonly` targetElementsProperty

▪ **targetElementsProperty**: _[CustomProperty](customproperty.md)‹[PropertyBag](../README.md#propertybag)›_ = new CustomProperty<PropertyBag>(
Versions.v1_2,
"targetElements",
(sender: SerializableObject, property: PropertyDefinition, source: PropertyBag, context: BaseSerializationContext) => {
let result: PropertyBag = {}

            if (Array.isArray(source[property.name])) {
                for (let item of source[property.name]) {
                    if (typeof item === "string") {
                        result[item] = undefined;
                    }
                    else if (typeof item === "object") {
                        let elementId = item["elementId"];

                        if (typeof elementId === "string") {
                            result[elementId] = Utils.parseBool(item["isVisible"]);
                        }
                    }
                }
            }

            return result;
        },
        (sender: SerializableObject, property: PropertyDefinition, target: PropertyBag, value: PropertyBag, context: BaseSerializationContext) => {
            let targetElements: any[] = [];

            for (let id of Object.keys(value)) {
                if (typeof value[id] === "boolean") {
                    targetElements.push(
                        {
                            elementId: id,
                            isVisible: value[id]
                        }
                    );
                }
                else {
                    targetElements.push(id);
                }
            }

            context.serializeArray(target, property.name, targetElements);
        },
        {},
        (sender: SerializableObject) => { return {}; })

---

### `Static` `Readonly` titleProperty

▪ **titleProperty**: _[StringProperty](stringproperty.md)‹›_ = new StringProperty(Versions.v1_0, "title")

_Inherited from [Action](action.md).[titleProperty](action.md#static-readonly-titleproperty)_

---

### `Static` `Readonly` typeNameProperty

▪ **typeNameProperty**: _[StringProperty](stringproperty.md)‹›_ = new StringProperty(
Versions.v1_0,
"type",
undefined,
undefined,
undefined,
(sender: object) => {
return (<CardObject>sender).getJsonTypeName()
})

_Inherited from [CardObject](cardobject.md).[typeNameProperty](cardobject.md#static-readonly-typenameproperty)_

## Accessors

### hostConfig

• **get hostConfig**(): _[HostConfig](hostconfig.md)_

_Inherited from [Action](action.md).[hostConfig](action.md#hostconfig)_

_Overrides [CardObject](cardobject.md).[hostConfig](cardobject.md#hostconfig)_

**Returns:** _[HostConfig](hostconfig.md)_

---

### isPrimary

• **get isPrimary**(): _boolean_

_Inherited from [Action](action.md).[isPrimary](action.md#isprimary)_

**Returns:** _boolean_

• **set isPrimary**(`value`: boolean): _void_

_Inherited from [Action](action.md).[isPrimary](action.md#isprimary)_

**Parameters:**

| Name    | Type    |
| ------- | ------- |
| `value` | boolean |

**Returns:** _void_

---

### parent

• **get parent**(): _[CardElement](cardelement.md) | undefined_

_Inherited from [Action](action.md).[parent](action.md#parent)_

_Overrides [CardObject](cardobject.md).[parent](cardobject.md#parent)_

**Returns:** _[CardElement](cardelement.md) | undefined_

---

### renderedElement

• **get renderedElement**(): _HTMLElement | undefined_

_Inherited from [CardObject](cardobject.md).[renderedElement](cardobject.md#renderedelement)_

**Returns:** _HTMLElement | undefined_

---

### requires

• **get requires**(): _[HostCapabilities](hostcapabilities.md)_

_Inherited from [CardObject](cardobject.md).[requires](cardobject.md#requires)_

**Returns:** _[HostCapabilities](hostcapabilities.md)_

## Methods

### `Protected` addCssClasses

▸ **addCssClasses**(`element`: HTMLElement): _void_

_Inherited from [Action](action.md).[addCssClasses](action.md#protected-addcssclasses)_

**Parameters:**

| Name      | Type        |
| --------- | ----------- |
| `element` | HTMLElement |

**Returns:** _void_

---

### addTargetElement

▸ **addTargetElement**(`elementId`: string, `isVisible`: boolean | undefined): _void_

**Parameters:**

| Name        | Type                     | Default   |
| ----------- | ------------------------ | --------- |
| `elementId` | string                   | -         |
| `isVisible` | boolean &#124; undefined | undefined |

**Returns:** _void_

---

### execute

▸ **execute**(): _void_

_Overrides [Action](action.md).[execute](action.md#execute)_

**Returns:** _void_

---

### getActionById

▸ **getActionById**(`id`: string): _[Action](action.md) | undefined_

_Inherited from [Action](action.md).[getActionById](action.md#getactionbyid)_

**Parameters:**

| Name | Type   |
| ---- | ------ |
| `id` | string |

**Returns:** _[Action](action.md) | undefined_

---

### getAllInputs

▸ **getAllInputs**(`processActions`: boolean): _[Input](input.md)[]_

_Inherited from [Action](action.md).[getAllInputs](action.md#getallinputs)_

**Parameters:**

| Name             | Type    | Default |
| ---------------- | ------- | ------- |
| `processActions` | boolean | true    |

**Returns:** _[Input](input.md)[]_

---

### getAriaRole

▸ **getAriaRole**(): _string_

_Inherited from [Action](action.md).[getAriaRole](action.md#getariarole)_

**Returns:** _string_

---

### getCustomProperty

▸ **getCustomProperty**(`name`: string): _any_

_Inherited from [SerializableObject](serializableobject.md).[getCustomProperty](serializableobject.md#getcustomproperty)_

**Parameters:**

| Name   | Type   |
| ------ | ------ |
| `name` | string |

**Returns:** _any_

---

### `Protected` getDefaultSerializationContext

▸ **getDefaultSerializationContext**(): _[BaseSerializationContext](baseserializationcontext.md)_

_Inherited from [Action](action.md).[getDefaultSerializationContext](action.md#protected-getdefaultserializationcontext)_

_Overrides [SerializableObject](serializableobject.md).[getDefaultSerializationContext](serializableobject.md#protected-getdefaultserializationcontext)_

**Returns:** _[BaseSerializationContext](baseserializationcontext.md)_

---

### getHref

▸ **getHref**(): _string | undefined_

_Inherited from [Action](action.md).[getHref](action.md#gethref)_

**Returns:** _string | undefined_

---

### getJsonTypeName

▸ **getJsonTypeName**(): _string_

_Overrides [CardObject](cardobject.md).[getJsonTypeName](cardobject.md#abstract-getjsontypename)_

**Returns:** _string_

---

### getReferencedInputs

▸ **getReferencedInputs**(): _[Dictionary](../README.md#dictionary)‹[Input](input.md)› | undefined_

_Inherited from [Action](action.md).[getReferencedInputs](action.md#getreferencedinputs)_

**Returns:** _[Dictionary](../README.md#dictionary)‹[Input](input.md)› | undefined_

---

### getResourceInformation

▸ **getResourceInformation**(): _[IResourceInformation](../interfaces/iresourceinformation.md)[]_

_Inherited from [Action](action.md).[getResourceInformation](action.md#getresourceinformation)_

**Returns:** _[IResourceInformation](../interfaces/iresourceinformation.md)[]_

---

### getRootObject

▸ **getRootObject**(): _[CardObject](cardobject.md)_

_Inherited from [CardObject](cardobject.md).[getRootObject](cardobject.md#getrootobject)_

**Returns:** _[CardObject](cardobject.md)_

---

### getSchema

▸ **getSchema**(): _[SerializableObjectSchema](serializableobjectschema.md)_

_Inherited from [SerializableObject](serializableobject.md).[getSchema](serializableobject.md#getschema)_

**Returns:** _[SerializableObjectSchema](serializableobjectschema.md)_

---

### `Protected` getSchemaKey

▸ **getSchemaKey**(): _string_

_Inherited from [CardObject](cardobject.md).[getSchemaKey](cardobject.md#protected-getschemakey)_

_Overrides [SerializableObject](serializableobject.md).[getSchemaKey](serializableobject.md#protected-abstract-getschemakey)_

**Returns:** _string_

---

### `Protected` getValue

▸ **getValue**(`property`: [PropertyDefinition](propertydefinition.md)): _any_

_Inherited from [SerializableObject](serializableobject.md).[getValue](serializableobject.md#protected-getvalue)_

**Parameters:**

| Name       | Type                                        |
| ---------- | ------------------------------------------- |
| `property` | [PropertyDefinition](propertydefinition.md) |

**Returns:** _any_

---

### hasAllDefaultValues

▸ **hasAllDefaultValues**(): _boolean_

_Inherited from [SerializableObject](serializableobject.md).[hasAllDefaultValues](serializableobject.md#hasalldefaultvalues)_

**Returns:** _boolean_

---

### hasDefaultValue

▸ **hasDefaultValue**(`property`: [PropertyDefinition](propertydefinition.md)): _boolean_

_Inherited from [SerializableObject](serializableobject.md).[hasDefaultValue](serializableobject.md#hasdefaultvalue)_

**Parameters:**

| Name       | Type                                        |
| ---------- | ------------------------------------------- |
| `property` | [PropertyDefinition](propertydefinition.md) |

**Returns:** _boolean_

---

### `Protected` internalGetReferencedInputs

▸ **internalGetReferencedInputs**(): _[Dictionary](../README.md#dictionary)‹[Input](input.md)›_

_Inherited from [Action](action.md).[internalGetReferencedInputs](action.md#protected-internalgetreferencedinputs)_

**Returns:** _[Dictionary](../README.md#dictionary)‹[Input](input.md)›_

---

### `Protected` internalParse

▸ **internalParse**(`source`: [PropertyBag](../README.md#propertybag), `context`: [BaseSerializationContext](baseserializationcontext.md)): _void_

_Inherited from [SerializableObject](serializableobject.md).[internalParse](serializableobject.md#protected-internalparse)_

**Parameters:**

| Name      | Type                                                    |
| --------- | ------------------------------------------------------- |
| `source`  | [PropertyBag](../README.md#propertybag)                 |
| `context` | [BaseSerializationContext](baseserializationcontext.md) |

**Returns:** _void_

---

### `Protected` internalPrepareForExecution

▸ **internalPrepareForExecution**(`inputs`: [Dictionary](../README.md#dictionary)‹[Input](input.md)› | undefined): _void_

_Inherited from [Action](action.md).[internalPrepareForExecution](action.md#protected-internalprepareforexecution)_

**Parameters:**

| Name     | Type                                                                      |
| -------- | ------------------------------------------------------------------------- |
| `inputs` | [Dictionary](../README.md#dictionary)‹[Input](input.md)› &#124; undefined |

**Returns:** _void_

---

### `Protected` internalToJSON

▸ **internalToJSON**(`target`: [PropertyBag](../README.md#propertybag), `context`: [BaseSerializationContext](baseserializationcontext.md)): _void_

_Inherited from [SerializableObject](serializableobject.md).[internalToJSON](serializableobject.md#protected-internaltojson)_

**Parameters:**

| Name      | Type                                                    |
| --------- | ------------------------------------------------------- |
| `target`  | [PropertyBag](../README.md#propertybag)                 |
| `context` | [BaseSerializationContext](baseserializationcontext.md) |

**Returns:** _void_

---

### `Protected` internalValidateInputs

▸ **internalValidateInputs**(`referencedInputs`: [Dictionary](../README.md#dictionary)‹[Input](input.md)› | undefined): _[Input](input.md)[]_

_Inherited from [Action](action.md).[internalValidateInputs](action.md#protected-internalvalidateinputs)_

**Parameters:**

| Name               | Type                                                                      |
| ------------------ | ------------------------------------------------------------------------- |
| `referencedInputs` | [Dictionary](../README.md#dictionary)‹[Input](input.md)› &#124; undefined |

**Returns:** _[Input](input.md)[]_

---

### internalValidateProperties

▸ **internalValidateProperties**(`context`: [ValidationResults](validationresults.md)): _void_

_Inherited from [CardObject](cardobject.md).[internalValidateProperties](cardobject.md#internalvalidateproperties)_

**Parameters:**

| Name      | Type                                      |
| --------- | ----------------------------------------- |
| `context` | [ValidationResults](validationresults.md) |

**Returns:** _void_

---

### parse

▸ **parse**(`source`: any, `context?`: [SerializationContext](serializationcontext.md)): _void_

_Inherited from [Action](action.md).[parse](action.md#parse)_

_Overrides [SerializableObject](serializableobject.md).[parse](serializableobject.md#parse)_

**Parameters:**

| Name       | Type                                            |
| ---------- | ----------------------------------------------- |
| `source`   | any                                             |
| `context?` | [SerializationContext](serializationcontext.md) |

**Returns:** _void_

---

### `Protected` populateSchema

▸ **populateSchema**(`schema`: [SerializableObjectSchema](serializableobjectschema.md)): _void_

_Inherited from [SerializableObject](serializableobject.md).[populateSchema](serializableobject.md#protected-populateschema)_

**Parameters:**

| Name     | Type                                                    |
| -------- | ------------------------------------------------------- |
| `schema` | [SerializableObjectSchema](serializableobjectschema.md) |

**Returns:** _void_

---

### preProcessPropertyValue

▸ **preProcessPropertyValue**(`property`: [PropertyDefinition](propertydefinition.md), `propertyValue?`: any): _any_

_Inherited from [CardObject](cardobject.md).[preProcessPropertyValue](cardobject.md#preprocesspropertyvalue)_

**Parameters:**

| Name             | Type                                        |
| ---------------- | ------------------------------------------- |
| `property`       | [PropertyDefinition](propertydefinition.md) |
| `propertyValue?` | any                                         |

**Returns:** _any_

---

### prepareForExecution

▸ **prepareForExecution**(): _boolean_

_Inherited from [Action](action.md).[prepareForExecution](action.md#prepareforexecution)_

**Returns:** _boolean_

---

### `Protected` raiseExecuteActionEvent

▸ **raiseExecuteActionEvent**(): _void_

_Inherited from [Action](action.md).[raiseExecuteActionEvent](action.md#protected-raiseexecuteactionevent)_

**Returns:** _void_

---

### remove

▸ **remove**(): _boolean_

_Inherited from [Action](action.md).[remove](action.md#remove)_

**Returns:** _boolean_

---

### removeTargetElement

▸ **removeTargetElement**(`elementId`: string): _void_

**Parameters:**

| Name        | Type   |
| ----------- | ------ |
| `elementId` | string |

**Returns:** _void_

---

### render

▸ **render**(`baseCssClass`: string): _void_

_Overrides [Action](action.md).[render](action.md#render)_

**Parameters:**

| Name           | Type   | Default         |
| -------------- | ------ | --------------- |
| `baseCssClass` | string | "ac-pushButton" |

**Returns:** _void_

---

### resetDefaultValues

▸ **resetDefaultValues**(): _void_

_Inherited from [SerializableObject](serializableobject.md).[resetDefaultValues](serializableobject.md#resetdefaultvalues)_

**Returns:** _void_

---

### setCustomProperty

▸ **setCustomProperty**(`name`: string, `value`: any): _void_

_Inherited from [SerializableObject](serializableobject.md).[setCustomProperty](serializableobject.md#setcustomproperty)_

**Parameters:**

| Name    | Type   |
| ------- | ------ |
| `name`  | string |
| `value` | any    |

**Returns:** _void_

---

### setParent

▸ **setParent**(`value`: [CardObject](cardobject.md) | undefined): _void_

_Inherited from [CardObject](cardobject.md).[setParent](cardobject.md#setparent)_

**Parameters:**

| Name    | Type                                         |
| ------- | -------------------------------------------- |
| `value` | [CardObject](cardobject.md) &#124; undefined |

**Returns:** _void_

---

### setShouldFallback

▸ **setShouldFallback**(`value`: boolean): _void_

_Inherited from [CardObject](cardobject.md).[setShouldFallback](cardobject.md#setshouldfallback)_

**Parameters:**

| Name    | Type    |
| ------- | ------- |
| `value` | boolean |

**Returns:** _void_

---

### `Protected` setValue

▸ **setValue**(`property`: [PropertyDefinition](propertydefinition.md), `value`: any): _void_

_Inherited from [SerializableObject](serializableobject.md).[setValue](serializableobject.md#protected-setvalue)_

**Parameters:**

| Name       | Type                                        |
| ---------- | ------------------------------------------- |
| `property` | [PropertyDefinition](propertydefinition.md) |
| `value`    | any                                         |

**Returns:** _void_

---

### shouldFallback

▸ **shouldFallback**(): _boolean_

_Inherited from [CardObject](cardobject.md).[shouldFallback](cardobject.md#shouldfallback)_

**Returns:** _boolean_

---

### `Protected` shouldSerialize

▸ **shouldSerialize**(`context`: [BaseSerializationContext](baseserializationcontext.md)): _boolean_

_Inherited from [SerializableObject](serializableobject.md).[shouldSerialize](serializableobject.md#protected-shouldserialize)_

**Parameters:**

| Name      | Type                                                    |
| --------- | ------------------------------------------------------- |
| `context` | [BaseSerializationContext](baseserializationcontext.md) |

**Returns:** _boolean_

---

### toJSON

▸ **toJSON**(`context?`: [BaseSerializationContext](baseserializationcontext.md)): _[PropertyBag](../README.md#propertybag) | undefined_

_Inherited from [SerializableObject](serializableobject.md).[toJSON](serializableobject.md#tojson)_

**Parameters:**

| Name       | Type                                                    |
| ---------- | ------------------------------------------------------- |
| `context?` | [BaseSerializationContext](baseserializationcontext.md) |

**Returns:** _[PropertyBag](../README.md#propertybag) | undefined_

---

### updateActionButtonCssStyle

▸ **updateActionButtonCssStyle**(`actionButtonElement`: HTMLElement, `buttonState`: [ActionButtonState](../enums/actionbuttonstate.md)): _void_

_Inherited from [Action](action.md).[updateActionButtonCssStyle](action.md#updateactionbuttoncssstyle)_

**Parameters:**

| Name                  | Type                                               | Default                  |
| --------------------- | -------------------------------------------------- | ------------------------ |
| `actionButtonElement` | HTMLElement                                        | -                        |
| `buttonState`         | [ActionButtonState](../enums/actionbuttonstate.md) | ActionButtonState.Normal |

**Returns:** _void_

---

### validateInputs

▸ **validateInputs**(): _[Input](input.md)[]_

_Inherited from [Action](action.md).[validateInputs](action.md#validateinputs)_

Validates the inputs associated with this action.

**Returns:** _[Input](input.md)[]_

A list of inputs that failed validation, or an empty array if no input failed validation.

---

### validateProperties

▸ **validateProperties**(): _[ValidationResults](validationresults.md)_

_Inherited from [CardObject](cardobject.md).[validateProperties](cardobject.md#validateproperties)_

**Returns:** _[ValidationResults](validationresults.md)_

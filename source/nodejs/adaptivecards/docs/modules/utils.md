[Adaptive Cards Javascript SDK](../README.md) / utils

# Module: utils

## Table of contents

### Functions

- [appendChild](utils.md#appendchild)
- [generateUniqueId](utils.md#generateuniqueid)
- [getEnumValueByName](utils.md#getenumvaluebyname)
- [getFitStatus](utils.md#getfitstatus)
- [isInternetExplorer](utils.md#isinternetexplorer)
- [isMobileOS](utils.md#ismobileos)
- [parseBool](utils.md#parsebool)
- [parseEnum](utils.md#parseenum)
- [parseNumber](utils.md#parsenumber)
- [parseString](utils.md#parsestring)
- [renderSeparation](utils.md#renderseparation)
- [stringToCssColor](utils.md#stringtocsscolor)
- [truncate](utils.md#truncate)

## Functions

### appendChild

▸ **appendChild**(`node`: Node, `child`: Node \| _undefined_): _void_

#### Parameters:

| Name    | Type                |
| :------ | :------------------ |
| `node`  | Node                |
| `child` | Node \| _undefined_ |

**Returns:** _void_

Defined in: [utils.ts:33](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/utils.ts#L33)

---

### generateUniqueId

▸ **generateUniqueId**(): _string_

Generate a UUID prepended with "\_\_ac-"

**Returns:** _string_

Defined in: [utils.ts:29](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/utils.ts#L29)

---

### getEnumValueByName

▸ **getEnumValueByName**(`enumType`: { [s: number]: _string_; }, `name`: _string_): _number_ \| _undefined_

#### Parameters:

| Name       | Type     |
| :--------- | :------- |
| `enumType` | _object_ |
| `name`     | _string_ |

**Returns:** _number_ \| _undefined_

Defined in: [utils.ts:65](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/utils.ts#L65)

---

### getFitStatus

▸ **getFitStatus**(`element`: HTMLElement, `containerEnd`: _number_): [_ContainerFitStatus_](../enums/enums.containerfitstatus.md)

#### Parameters:

| Name           | Type        |
| :------------- | :---------- |
| `element`      | HTMLElement |
| `containerEnd` | _number_    |

**Returns:** [_ContainerFitStatus_](../enums/enums.containerfitstatus.md)

Defined in: [utils.ts:233](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/utils.ts#L233)

---

### isInternetExplorer

▸ **isInternetExplorer**(): _boolean_

**Returns:** _boolean_

Defined in: [utils.ts:15](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/utils.ts#L15)

---

### isMobileOS

▸ **isMobileOS**(): _boolean_

**Returns:** _boolean_

Defined in: [utils.ts:20](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/utils.ts#L20)

---

### parseBool

▸ **parseBool**(`value`: _any_, `defaultValue?`: _boolean_): _boolean_ \| _undefined_

#### Parameters:

| Name            | Type      |
| :-------------- | :-------- |
| `value`         | _any_     |
| `defaultValue?` | _boolean_ |

**Returns:** _boolean_ \| _undefined_

Defined in: [utils.ts:47](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/utils.ts#L47)

---

### parseEnum

▸ **parseEnum**(`enumType`: { [s: number]: _string_; }, `name`: _string_, `defaultValue?`: _number_): _number_ \| _undefined_

#### Parameters:

| Name            | Type     |
| :-------------- | :------- |
| `enumType`      | _object_ |
| `name`          | _string_ |
| `defaultValue?` | _number_ |

**Returns:** _number_ \| _undefined_

Defined in: [utils.ts:81](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/utils.ts#L81)

---

### parseNumber

▸ **parseNumber**(`obj`: _any_, `defaultValue?`: _number_): _number_ \| _undefined_

#### Parameters:

| Name            | Type     |
| :-------------- | :------- |
| `obj`           | _any_    |
| `defaultValue?` | _number_ |

**Returns:** _number_ \| _undefined_

Defined in: [utils.ts:43](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/utils.ts#L43)

---

### parseString

▸ **parseString**(`obj`: _any_, `defaultValue?`: _string_): _string_ \| _undefined_

#### Parameters:

| Name            | Type     |
| :-------------- | :------- |
| `obj`           | _any_    |
| `defaultValue?` | _string_ |

**Returns:** _string_ \| _undefined_

Defined in: [utils.ts:39](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/utils.ts#L39)

---

### renderSeparation

▸ **renderSeparation**(`hostConfig`: [_HostConfig_](../classes/host_config.hostconfig.md), `separationDefinition`: [_ISeparationDefinition_](../interfaces/shared.iseparationdefinition.md), `orientation`: [_Orientation_](../enums/enums.orientation.md)): HTMLElement \| _undefined_

#### Parameters:

| Name                   | Type                                                                     |
| :--------------------- | :----------------------------------------------------------------------- |
| `hostConfig`           | [_HostConfig_](../classes/host_config.hostconfig.md)                     |
| `separationDefinition` | [_ISeparationDefinition_](../interfaces/shared.iseparationdefinition.md) |
| `orientation`          | [_Orientation_](../enums/enums.orientation.md)                           |

**Returns:** HTMLElement \| _undefined_

Defined in: [utils.ts:91](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/utils.ts#L91)

---

### stringToCssColor

▸ **stringToCssColor**(`color`: _string_ \| _undefined_): _string_ \| _undefined_

#### Parameters:

| Name    | Type                    |
| :------ | :---------------------- |
| `color` | _string_ \| _undefined_ |

**Returns:** _string_ \| _undefined_

Defined in: [utils.ts:130](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/utils.ts#L130)

---

### truncate

▸ **truncate**(`element`: HTMLElement, `maxHeight`: _number_, `lineHeight?`: _number_): _void_

#### Parameters:

| Name          | Type        |
| :------------ | :---------- |
| `element`     | HTMLElement |
| `maxHeight`   | _number_    |
| `lineHeight?` | _number_    |

**Returns:** _void_

Defined in: [utils.ts:148](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/utils.ts#L148)

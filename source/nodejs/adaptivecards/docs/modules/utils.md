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

▸ **appendChild**(`node`: Node, `child`: Node \| *undefined*): *void*

#### Parameters:

Name | Type |
:------ | :------ |
`node` | Node |
`child` | Node \| *undefined* |

**Returns:** *void*

Defined in: [utils.ts:33](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/utils.ts#L33)

___

### generateUniqueId

▸ **generateUniqueId**(): *string*

Generate a UUID prepended with "__ac-"

**Returns:** *string*

Defined in: [utils.ts:29](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/utils.ts#L29)

___

### getEnumValueByName

▸ **getEnumValueByName**(`enumType`: { [s: number]: *string*;  }, `name`: *string*): *number* \| *undefined*

#### Parameters:

Name | Type |
:------ | :------ |
`enumType` | *object* |
`name` | *string* |

**Returns:** *number* \| *undefined*

Defined in: [utils.ts:65](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/utils.ts#L65)

___

### getFitStatus

▸ **getFitStatus**(`element`: HTMLElement, `containerEnd`: *number*): [*ContainerFitStatus*](../enums/enums.containerfitstatus.md)

#### Parameters:

Name | Type |
:------ | :------ |
`element` | HTMLElement |
`containerEnd` | *number* |

**Returns:** [*ContainerFitStatus*](../enums/enums.containerfitstatus.md)

Defined in: [utils.ts:233](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/utils.ts#L233)

___

### isInternetExplorer

▸ **isInternetExplorer**(): *boolean*

**Returns:** *boolean*

Defined in: [utils.ts:15](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/utils.ts#L15)

___

### isMobileOS

▸ **isMobileOS**(): *boolean*

**Returns:** *boolean*

Defined in: [utils.ts:20](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/utils.ts#L20)

___

### parseBool

▸ **parseBool**(`value`: *any*, `defaultValue?`: *boolean*): *boolean* \| *undefined*

#### Parameters:

Name | Type |
:------ | :------ |
`value` | *any* |
`defaultValue?` | *boolean* |

**Returns:** *boolean* \| *undefined*

Defined in: [utils.ts:47](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/utils.ts#L47)

___

### parseEnum

▸ **parseEnum**(`enumType`: { [s: number]: *string*;  }, `name`: *string*, `defaultValue?`: *number*): *number* \| *undefined*

#### Parameters:

Name | Type |
:------ | :------ |
`enumType` | *object* |
`name` | *string* |
`defaultValue?` | *number* |

**Returns:** *number* \| *undefined*

Defined in: [utils.ts:81](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/utils.ts#L81)

___

### parseNumber

▸ **parseNumber**(`obj`: *any*, `defaultValue?`: *number*): *number* \| *undefined*

#### Parameters:

Name | Type |
:------ | :------ |
`obj` | *any* |
`defaultValue?` | *number* |

**Returns:** *number* \| *undefined*

Defined in: [utils.ts:43](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/utils.ts#L43)

___

### parseString

▸ **parseString**(`obj`: *any*, `defaultValue?`: *string*): *string* \| *undefined*

#### Parameters:

Name | Type |
:------ | :------ |
`obj` | *any* |
`defaultValue?` | *string* |

**Returns:** *string* \| *undefined*

Defined in: [utils.ts:39](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/utils.ts#L39)

___

### renderSeparation

▸ **renderSeparation**(`hostConfig`: [*HostConfig*](../classes/host_config.hostconfig.md), `separationDefinition`: [*ISeparationDefinition*](../interfaces/shared.iseparationdefinition.md), `orientation`: [*Orientation*](../enums/enums.orientation.md)): HTMLElement \| *undefined*

#### Parameters:

Name | Type |
:------ | :------ |
`hostConfig` | [*HostConfig*](../classes/host_config.hostconfig.md) |
`separationDefinition` | [*ISeparationDefinition*](../interfaces/shared.iseparationdefinition.md) |
`orientation` | [*Orientation*](../enums/enums.orientation.md) |

**Returns:** HTMLElement \| *undefined*

Defined in: [utils.ts:91](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/utils.ts#L91)

___

### stringToCssColor

▸ **stringToCssColor**(`color`: *string* \| *undefined*): *string* \| *undefined*

#### Parameters:

Name | Type |
:------ | :------ |
`color` | *string* \| *undefined* |

**Returns:** *string* \| *undefined*

Defined in: [utils.ts:130](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/utils.ts#L130)

___

### truncate

▸ **truncate**(`element`: HTMLElement, `maxHeight`: *number*, `lineHeight?`: *number*): *void*

#### Parameters:

Name | Type |
:------ | :------ |
`element` | HTMLElement |
`maxHeight` | *number* |
`lineHeight?` | *number* |

**Returns:** *void*

Defined in: [utils.ts:148](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/utils.ts#L148)

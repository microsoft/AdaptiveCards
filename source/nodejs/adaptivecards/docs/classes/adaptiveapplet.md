[Adaptive Cards Javascript SDK](../README.md) › [AdaptiveApplet](adaptiveapplet.md)

# Class: AdaptiveApplet

## Hierarchy

* **AdaptiveApplet**

## Index

### Constructors

* [constructor](adaptiveapplet.md#constructor)

### Properties

* [channelAdapter](adaptiveapplet.md#channeladapter)
* [onActivityRequestFailed](adaptiveapplet.md#optional-onactivityrequestfailed)
* [onActivityRequestSucceeded](adaptiveapplet.md#optional-onactivityrequestsucceeded)
* [onCardChanged](adaptiveapplet.md#optional-oncardchanged)
* [onCardChanging](adaptiveapplet.md#optional-oncardchanging)
* [onCreateProgressOverlay](adaptiveapplet.md#optional-oncreateprogressoverlay)
* [onPrepareActivityRequest](adaptiveapplet.md#optional-onprepareactivityrequest)
* [onRenderRefreshButton](adaptiveapplet.md#optional-onrenderrefreshbutton)
* [renderedElement](adaptiveapplet.md#renderedelement)
* [userId](adaptiveapplet.md#optional-userid)

### Accessors

* [card](adaptiveapplet.md#card)

### Methods

* [refreshCard](adaptiveapplet.md#refreshcard)
* [setCard](adaptiveapplet.md#setcard)
* [initialize](adaptiveapplet.md#static-initialize)

## Constructors

###  constructor

\+ **new AdaptiveApplet**(): *[AdaptiveApplet](adaptiveapplet.md)*

**Returns:** *[AdaptiveApplet](adaptiveapplet.md)*

## Properties

###  channelAdapter

• **channelAdapter**: *[ChannelAdapter](channeladapter.md) | undefined* = undefined

___

### `Optional` onActivityRequestFailed

• **onActivityRequestFailed**? : *undefined | function*

___

### `Optional` onActivityRequestSucceeded

• **onActivityRequestSucceeded**? : *undefined | function*

___

### `Optional` onCardChanged

• **onCardChanged**? : *undefined | function*

___

### `Optional` onCardChanging

• **onCardChanging**? : *undefined | function*

___

### `Optional` onCreateProgressOverlay

• **onCreateProgressOverlay**? : *undefined | function*

___

### `Optional` onPrepareActivityRequest

• **onPrepareActivityRequest**? : *undefined | function*

___

### `Optional` onRenderRefreshButton

• **onRenderRefreshButton**? : *undefined | function*

___

###  renderedElement

• **renderedElement**: *HTMLElement*

___

### `Optional` userId

• **userId**? : *undefined | string*

## Accessors

###  card

• **get card**(): *[AdaptiveAppletCard](adaptiveappletcard.md) | undefined*

**Returns:** *[AdaptiveAppletCard](adaptiveappletcard.md) | undefined*

## Methods

###  refreshCard

▸ **refreshCard**(): *void*

**Returns:** *void*

___

###  setCard

▸ **setCard**(`payload`: any): *void*

**Parameters:**

Name | Type |
------ | ------ |
`payload` | any |

**Returns:** *void*

___

### `Static` initialize

▸ **initialize**(): *void*

**Returns:** *void*

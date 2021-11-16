[Adaptive Cards Javascript SDK](../README.md) › [AdaptiveApplet](adaptiveapplet.md)

# Class: AdaptiveApplet

## Hierarchy

- **AdaptiveApplet**

## Index

### Constructors

- [constructor](adaptiveapplet.md#constructor)

### Properties

- [channelAdapter](adaptiveapplet.md#channeladapter)
- [onActivityRequestFailed](adaptiveapplet.md#optional-onactivityrequestfailed)
- [onActivityRequestSucceeded](adaptiveapplet.md#optional-onactivityrequestsucceeded)
- [onCardChanged](adaptiveapplet.md#optional-oncardchanged)
- [onCardChanging](adaptiveapplet.md#optional-oncardchanging)
- [onCreateProgressOverlay](adaptiveapplet.md#optional-oncreateprogressoverlay)
- [onPrepareActivityRequest](adaptiveapplet.md#optional-onprepareactivityrequest)
- [onRenderRefreshButton](adaptiveapplet.md#optional-onrenderrefreshbutton)
- [renderedElement](adaptiveapplet.md#renderedelement)
- [userId](adaptiveapplet.md#optional-userid)

### Accessors

- [card](adaptiveapplet.md#card)

### Methods

- [refreshCard](adaptiveapplet.md#refreshcard)
- [setCard](adaptiveapplet.md#setcard)
- [initialize](adaptiveapplet.md#static-initialize)

## Constructors

### constructor

\+ **new AdaptiveApplet**(): _[AdaptiveApplet](adaptiveapplet.md)_

**Returns:** _[AdaptiveApplet](adaptiveapplet.md)_

## Properties

### channelAdapter

• **channelAdapter**: _[ChannelAdapter](channeladapter.md) | undefined_ = undefined

---

### `Optional` onActivityRequestFailed

• **onActivityRequestFailed**? : _undefined | function_

---

### `Optional` onActivityRequestSucceeded

• **onActivityRequestSucceeded**? : _undefined | function_

---

### `Optional` onCardChanged

• **onCardChanged**? : _undefined | function_

---

### `Optional` onCardChanging

• **onCardChanging**? : _undefined | function_

---

### `Optional` onCreateProgressOverlay

• **onCreateProgressOverlay**? : _undefined | function_

---

### `Optional` onPrepareActivityRequest

• **onPrepareActivityRequest**? : _undefined | function_

---

### `Optional` onRenderRefreshButton

• **onRenderRefreshButton**? : _undefined | function_

---

### renderedElement

• **renderedElement**: _HTMLElement_

---

### `Optional` userId

• **userId**? : _undefined | string_

## Accessors

### card

• **get card**(): _[AdaptiveAppletCard](adaptiveappletcard.md) | undefined_

**Returns:** _[AdaptiveAppletCard](adaptiveappletcard.md) | undefined_

## Methods

### refreshCard

▸ **refreshCard**(): _void_

**Returns:** _void_

---

### setCard

▸ **setCard**(`payload`: any): _void_

**Parameters:**

| Name      | Type |
| --------- | ---- |
| `payload` | any  |

**Returns:** _void_

---

### `Static` initialize

▸ **initialize**(): _void_

**Returns:** _void_

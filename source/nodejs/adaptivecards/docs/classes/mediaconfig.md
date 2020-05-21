[Adaptive Cards Javascript SDK](../README.md) › [MediaConfig](mediaconfig.md)

# Class: MediaConfig

## Hierarchy

* **MediaConfig**

## Index

### Constructors

* [constructor](mediaconfig.md#constructor)

### Properties

* [allowInlinePlayback](mediaconfig.md#allowinlineplayback)
* [defaultPoster](mediaconfig.md#optional-defaultposter)

### Methods

* [toJSON](mediaconfig.md#tojson)

## Constructors

###  constructor

\+ **new MediaConfig**(`obj?`: any): *[MediaConfig](mediaconfig.md)*

*Defined in [host-config.ts:87](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/host-config.ts#L87)*

**Parameters:**

Name | Type |
------ | ------ |
`obj?` | any |

**Returns:** *[MediaConfig](mediaconfig.md)*

## Properties

###  allowInlinePlayback

• **allowInlinePlayback**: *boolean* = true

*Defined in [host-config.ts:87](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/host-config.ts#L87)*

___

### `Optional` defaultPoster

• **defaultPoster**? : *undefined | string*

*Defined in [host-config.ts:86](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/host-config.ts#L86)*

## Methods

###  toJSON

▸ **toJSON**(): *object*

*Defined in [host-config.ts:96](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/host-config.ts#L96)*

**Returns:** *object*

* **allowInlinePlayback**: *boolean* = this.allowInlinePlayback

* **defaultPoster**: *undefined | string* = this.defaultPoster

[Adaptive Cards Javascript SDK](../README.md) › [ImageSetConfig](imagesetconfig.md)

# Class: ImageSetConfig

## Hierarchy

* **ImageSetConfig**

## Index

### Constructors

* [constructor](imagesetconfig.md#constructor)

### Properties

* [imageSize](imagesetconfig.md#imagesize)
* [maxImageHeight](imagesetconfig.md#maximageheight)

### Methods

* [toJSON](imagesetconfig.md#tojson)

## Constructors

###  constructor

\+ **new ImageSetConfig**(`obj?`: any): *[ImageSetConfig](imagesetconfig.md)*

*Defined in [host-config.ts:58](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/host-config.ts#L58)*

**Parameters:**

Name | Type |
------ | ------ |
`obj?` | any |

**Returns:** *[ImageSetConfig](imagesetconfig.md)*

## Properties

###  imageSize

• **imageSize**: *[Size](../enums/size.md)* = Enums.Size.Medium

*Defined in [host-config.ts:57](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/host-config.ts#L57)*

___

###  maxImageHeight

• **maxImageHeight**: *number* = 100

*Defined in [host-config.ts:58](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/host-config.ts#L58)*

## Methods

###  toJSON

▸ **toJSON**(): *object*

*Defined in [host-config.ts:67](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/host-config.ts#L67)*

**Returns:** *object*

* **imageSize**: *string* = Enums.Size[this.imageSize]

* **maxImageHeight**: *number* = this.maxImageHeight

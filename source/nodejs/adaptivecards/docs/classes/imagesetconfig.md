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

*Defined in [host-config.ts:68](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/host-config.ts#L68)*

**Parameters:**

Name | Type |
------ | ------ |
`obj?` | any |

**Returns:** *[ImageSetConfig](imagesetconfig.md)*

## Properties

###  imageSize

• **imageSize**: *[Size](../enums/size.md)* = Enums.Size.Medium

*Defined in [host-config.ts:67](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/host-config.ts#L67)*

___

###  maxImageHeight

• **maxImageHeight**: *number* = 100

*Defined in [host-config.ts:68](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/host-config.ts#L68)*

## Methods

###  toJSON

▸ **toJSON**(): *object*

*Defined in [host-config.ts:77](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/host-config.ts#L77)*

**Returns:** *object*

* **imageSize**: *string* = Enums.Size[this.imageSize]

* **maxImageHeight**: *number* = this.maxImageHeight

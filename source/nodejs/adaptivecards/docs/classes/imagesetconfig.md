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

**Parameters:**

Name | Type |
------ | ------ |
`obj?` | any |

**Returns:** *[ImageSetConfig](imagesetconfig.md)*

## Properties

###  imageSize

• **imageSize**: *[Size](../enums/size.md)* = Enums.Size.Medium

___

###  maxImageHeight

• **maxImageHeight**: *number* = 100

## Methods

###  toJSON

▸ **toJSON**(): *object*

**Returns:** *object*

* **imageSize**: *string* = Enums.Size[this.imageSize]

* **maxImageHeight**: *number* = this.maxImageHeight

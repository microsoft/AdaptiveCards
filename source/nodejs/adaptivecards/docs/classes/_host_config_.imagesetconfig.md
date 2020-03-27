[Adaptive Cards Javascript SDK](../README.md) › ["host-config"](../modules/_host_config_.md) › [ImageSetConfig](_host_config_.imagesetconfig.md)

# Class: ImageSetConfig

## Hierarchy

* **ImageSetConfig**

## Index

### Constructors

* [constructor](_host_config_.imagesetconfig.md#constructor)

### Properties

* [imageSize](_host_config_.imagesetconfig.md#imagesize)
* [maxImageHeight](_host_config_.imagesetconfig.md#maximageheight)

### Methods

* [toJSON](_host_config_.imagesetconfig.md#tojson)

## Constructors

###  constructor

\+ **new ImageSetConfig**(`obj?`: any): *[ImageSetConfig](_host_config_.imagesetconfig.md)*

**Parameters:**

Name | Type |
------ | ------ |
`obj?` | any |

**Returns:** *[ImageSetConfig](_host_config_.imagesetconfig.md)*

## Properties

###  imageSize

• **imageSize**: *[Size](../enums/_enums_.size.md)* = Enums.Size.Medium

___

###  maxImageHeight

• **maxImageHeight**: *number* = 100

## Methods

###  toJSON

▸ **toJSON**(): *object*

**Returns:** *object*

* **imageSize**: *string* = Enums.Size[this.imageSize]

* **maxImageHeight**: *number* = this.maxImageHeight

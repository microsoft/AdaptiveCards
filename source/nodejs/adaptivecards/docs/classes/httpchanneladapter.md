[Adaptive Cards Javascript SDK](../README.md) › [HttpChannelAdapter](httpchanneladapter.md)

# Class: HttpChannelAdapter

## Hierarchy

* [ChannelAdapter](channeladapter.md)

  ↳ **HttpChannelAdapter**

## Index

### Constructors

* [constructor](httpchanneladapter.md#constructor)

### Properties

* [url](httpchanneladapter.md#url)

### Methods

* [sendRequestAsync](httpchanneladapter.md#sendrequestasync)

## Constructors

###  constructor

\+ **new HttpChannelAdapter**(`url`: string): *[HttpChannelAdapter](httpchanneladapter.md)*

**Parameters:**

Name | Type |
------ | ------ |
`url` | string |

**Returns:** *[HttpChannelAdapter](httpchanneladapter.md)*

## Properties

###  url

• **url**: *string*

## Methods

###  sendRequestAsync

▸ **sendRequestAsync**(`request`: [ActivityRequest](../interfaces/activityrequest.md)): *Promise‹[ActivityResponse](../interfaces/activityresponse.md)›*

*Overrides [ChannelAdapter](channeladapter.md).[sendRequestAsync](channeladapter.md#abstract-sendrequestasync)*

**Parameters:**

Name | Type |
------ | ------ |
`request` | [ActivityRequest](../interfaces/activityrequest.md) |

**Returns:** *Promise‹[ActivityResponse](../interfaces/activityresponse.md)›*

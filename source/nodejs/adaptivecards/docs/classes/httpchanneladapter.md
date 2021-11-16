[Adaptive Cards Javascript SDK](../README.md) › [HttpChannelAdapter](httpchanneladapter.md)

# Class: HttpChannelAdapter

## Hierarchy

- [ChannelAdapter](channeladapter.md)

  ↳ **HttpChannelAdapter**

## Index

### Constructors

- [constructor](httpchanneladapter.md#constructor)

### Properties

- [url](httpchanneladapter.md#url)

### Methods

- [sendRequestAsync](httpchanneladapter.md#sendrequestasync)

## Constructors

### constructor

\+ **new HttpChannelAdapter**(`url`: string): _[HttpChannelAdapter](httpchanneladapter.md)_

**Parameters:**

| Name  | Type   |
| ----- | ------ |
| `url` | string |

**Returns:** _[HttpChannelAdapter](httpchanneladapter.md)_

## Properties

### url

• **url**: _string_

## Methods

### sendRequestAsync

▸ **sendRequestAsync**(`request`: [ActivityRequest](../interfaces/activityrequest.md)): _Promise‹[ActivityResponse](../interfaces/activityresponse.md)›_

_Overrides [ChannelAdapter](channeladapter.md).[sendRequestAsync](channeladapter.md#abstract-sendrequestasync)_

**Parameters:**

| Name      | Type                                                |
| --------- | --------------------------------------------------- |
| `request` | [ActivityRequest](../interfaces/activityrequest.md) |

**Returns:** _Promise‹[ActivityResponse](../interfaces/activityresponse.md)›_

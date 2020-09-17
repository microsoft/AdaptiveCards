[Adaptive Cards Javascript SDK](../README.md) › [InvokeActivity](invokeactivity.md)

# Interface: InvokeActivity

## Hierarchy

* **InvokeActivity**

## Index

### Properties

* [channelData](invokeactivity.md#optional-channeldata)
* [channelId](invokeactivity.md#optional-channelid)
* [conversation](invokeactivity.md#optional-conversation)
* [entities](invokeactivity.md#optional-entities)
* [from](invokeactivity.md#optional-from)
* [localTimestamp](invokeactivity.md#localtimestamp)
* [localTimezone](invokeactivity.md#localtimezone)
* [name](invokeactivity.md#name)
* [relatesTo](invokeactivity.md#optional-relatesto)
* [replyToId](invokeactivity.md#optional-replytoid)
* [serviceUrl](invokeactivity.md#optional-serviceurl)
* [type](invokeactivity.md#type)
* [value](invokeactivity.md#value)

## Properties

### `Optional` channelData

• **channelData**? : *undefined | object*

___

### `Optional` channelId

• **channelId**? : *undefined | string*

___

### `Optional` conversation

• **conversation**? : *undefined | object*

___

### `Optional` entities

• **entities**? : *object[]*

___

### `Optional` from

• **from**? : *undefined | object*

___

###  localTimestamp

• **localTimestamp**: *string*

___

###  localTimezone

• **localTimezone**: *string*

___

###  name

• **name**: *"adaptiveCard/action"*

___

### `Optional` relatesTo

• **relatesTo**? : *undefined | string*

___

### `Optional` replyToId

• **replyToId**? : *undefined | string*

___

### `Optional` serviceUrl

• **serviceUrl**? : *undefined | string*

___

###  type

• **type**: *"invoke"*

___

###  value

• **value**: *object*

#### Type declaration:

* **action**(): *object*

  * **data**? : *undefined | object*

  * **id**? : *undefined | string*

  * **type**: *"Action.Execute"*

  * **verb**: *string*

* **magicCode**? : *undefined | string*

* **trigger**: *[ActivityInvocationTrigger](../enums/activityinvocationtrigger.md)*

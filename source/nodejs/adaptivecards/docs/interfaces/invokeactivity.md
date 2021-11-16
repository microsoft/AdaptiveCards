[Adaptive Cards Javascript SDK](../README.md) › [InvokeActivity](invokeactivity.md)

# Interface: InvokeActivity

## Hierarchy

- **InvokeActivity**

## Index

### Properties

- [channelData](invokeactivity.md#optional-channeldata)
- [channelId](invokeactivity.md#optional-channelid)
- [conversation](invokeactivity.md#optional-conversation)
- [entities](invokeactivity.md#optional-entities)
- [from](invokeactivity.md#optional-from)
- [localTimestamp](invokeactivity.md#localtimestamp)
- [localTimezone](invokeactivity.md#localtimezone)
- [name](invokeactivity.md#name)
- [relatesTo](invokeactivity.md#optional-relatesto)
- [replyToId](invokeactivity.md#optional-replytoid)
- [serviceUrl](invokeactivity.md#optional-serviceurl)
- [type](invokeactivity.md#type)
- [value](invokeactivity.md#value)

## Properties

### `Optional` channelData

• **channelData**? : _undefined | object_

---

### `Optional` channelId

• **channelId**? : _undefined | string_

---

### `Optional` conversation

• **conversation**? : _undefined | object_

---

### `Optional` entities

• **entities**? : _object[]_

---

### `Optional` from

• **from**? : _undefined | object_

---

### localTimestamp

• **localTimestamp**: _string_

---

### localTimezone

• **localTimezone**: _string_

---

### name

• **name**: _"adaptiveCard/action"_

---

### `Optional` relatesTo

• **relatesTo**? : _undefined | string_

---

### `Optional` replyToId

• **replyToId**? : _undefined | string_

---

### `Optional` serviceUrl

• **serviceUrl**? : _undefined | string_

---

### type

• **type**: _"invoke"_

---

### value

• **value**: _object_

#### Type declaration:

- **action**(): _object_

  - **data**? : _undefined | object_

  - **id**? : _undefined | string_

  - **type**: _"Action.Execute"_

  - **verb**: _string_

- **magicCode**? : _undefined | string_

- **trigger**: _[ActivityInvocationTrigger](../enums/activityinvocationtrigger.md)_

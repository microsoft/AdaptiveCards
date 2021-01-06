[Adaptive Cards Javascript SDK](../README.md) › [AbstractTextFormatter](abstracttextformatter.md)

# Class: AbstractTextFormatter

## Hierarchy

* **AbstractTextFormatter**

  ↳ [DateFormatter](dateformatter.md)

  ↳ [TimeFormatter](timeformatter.md)

## Index

### Constructors

* [constructor](abstracttextformatter.md#constructor)

### Methods

* [format](abstracttextformatter.md#format)
* [internalFormat](abstracttextformatter.md#protected-abstract-internalformat)

## Constructors

###  constructor

\+ **new AbstractTextFormatter**(`regularExpression`: RegExp): *[AbstractTextFormatter](abstracttextformatter.md)*

**Parameters:**

Name | Type |
------ | ------ |
`regularExpression` | RegExp |

**Returns:** *[AbstractTextFormatter](abstracttextformatter.md)*

## Methods

###  format

▸ **format**(`lang`: string | undefined, `input`: string | undefined): *string | undefined*

**Parameters:**

Name | Type |
------ | ------ |
`lang` | string &#124; undefined |
`input` | string &#124; undefined |

**Returns:** *string | undefined*

___

### `Protected` `Abstract` internalFormat

▸ **internalFormat**(`lang`: string | undefined, `matches`: RegExpExecArray): *string*

**Parameters:**

Name | Type |
------ | ------ |
`lang` | string &#124; undefined |
`matches` | RegExpExecArray |

**Returns:** *string*

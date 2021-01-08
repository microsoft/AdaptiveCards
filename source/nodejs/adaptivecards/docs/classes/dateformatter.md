[Adaptive Cards Javascript SDK](../README.md) › [DateFormatter](dateformatter.md)

# Class: DateFormatter

## Hierarchy

* [AbstractTextFormatter](abstracttextformatter.md)

  ↳ **DateFormatter**

## Index

### Constructors

* [constructor](dateformatter.md#constructor)

### Methods

* [format](dateformatter.md#format)
* [internalFormat](dateformatter.md#protected-internalformat)

## Constructors

###  constructor

\+ **new DateFormatter**(`regularExpression`: RegExp): *[DateFormatter](dateformatter.md)*

*Inherited from [AbstractTextFormatter](abstracttextformatter.md).[constructor](abstracttextformatter.md#constructor)*

**Parameters:**

Name | Type |
------ | ------ |
`regularExpression` | RegExp |

**Returns:** *[DateFormatter](dateformatter.md)*

## Methods

###  format

▸ **format**(`lang`: string | undefined, `input`: string | undefined): *string | undefined*

*Inherited from [AbstractTextFormatter](abstracttextformatter.md).[format](abstracttextformatter.md#format)*

**Parameters:**

Name | Type |
------ | ------ |
`lang` | string &#124; undefined |
`input` | string &#124; undefined |

**Returns:** *string | undefined*

___

### `Protected` internalFormat

▸ **internalFormat**(`lang`: string | undefined, `matches`: RegExpExecArray): *string*

*Overrides [AbstractTextFormatter](abstracttextformatter.md).[internalFormat](abstracttextformatter.md#protected-abstract-internalformat)*

**Parameters:**

Name | Type |
------ | ------ |
`lang` | string &#124; undefined |
`matches` | RegExpExecArray |

**Returns:** *string*

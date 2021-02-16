[Adaptive Cards Javascript SDK](../README.md) › [TimeFormatter](timeformatter.md)

# Class: TimeFormatter

## Hierarchy

* [AbstractTextFormatter](abstracttextformatter.md)

  ↳ **TimeFormatter**

## Index

### Constructors

* [constructor](timeformatter.md#constructor)

### Methods

* [format](timeformatter.md#format)
* [internalFormat](timeformatter.md#protected-internalformat)

## Constructors

###  constructor

\+ **new TimeFormatter**(`regularExpression`: RegExp): *[TimeFormatter](timeformatter.md)*

*Inherited from [AbstractTextFormatter](abstracttextformatter.md).[constructor](abstracttextformatter.md#constructor)*

**Parameters:**

Name | Type |
------ | ------ |
`regularExpression` | RegExp |

**Returns:** *[TimeFormatter](timeformatter.md)*

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

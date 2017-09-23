# Change Log
All notable changes will be documented in this file.
JSON Schema $Ref Parser adheres to [Semantic Versioning](http://semver.org/).


## [v3.3.0](https://github.com/BigstickCarpet/json-schema-ref-parser/tree/v3.3.0) (2017-08-09)

- Updated dependencies

- [PR #30](https://github.com/BigstickCarpet/json-schema-ref-parser/pull/30) - Added a `browser` field to the `package.json` file to support bundlers such as Browserify, Rollup, and Webpack

- [PR #45](https://github.com/BigstickCarpet/json-schema-ref-parser/pull/45) - Implemented a temporary workaround for [issue #42](https://github.com/BigstickCarpet/json-schema-ref-parser/issues/42). JSON Schema $Ref Parser does _not_ currently support [named internal references](http://json-schema.org/latest/json-schema-core.html#id-keyword), but support will be added in the next major release.

[Full Changelog](https://github.com/BigstickCarpet/json-schema-ref-parser/compare/v3.0.0...v3.3.0)


## [v3.0.0](https://github.com/BigstickCarpet/json-schema-ref-parser/tree/v3.0.0) (2016-04-03)

#### Plug-ins !!!
That's the major new feature in this version. Originally requested in [PR #8](https://github.com/BigstickCarpet/json-schema-ref-parser/pull/8), and refined a few times over the past few months, the plug-in API is now finalized and ready to use. You can now define your own [resolvers](https://github.com/BigstickCarpet/json-schema-ref-parser/blob/v3.0.0/docs/plugins/resolvers.md) and [parsers](https://github.com/BigstickCarpet/json-schema-ref-parser/blob/v3.0.0/docs/plugins/parsers.md).

#### Breaking Changes
The available [options have changed](https://github.com/BigstickCarpet/json-schema-ref-parser/blob/v3.0.0/docs/options.md), mostly due to the new plug-in API.  There's not a one-to-one mapping of old options to new options, so you'll have to read the docs and determine which options you need to set. If any. The out-of-the-box configuration works for most people.

All of the [caching options have been removed](https://github.com/BigstickCarpet/json-schema-ref-parser/commit/1f4260184bfd370e9cd385b523fb08c098fac6db). Instead, all files are now cached, and the entire cache is reset for each new parse operation. Caching options may come back in a future release, if there is enough demand for it. If you used the old caching options, please open an issue and explain your use-case and requirements.  I need a better understanding of what caching functionality is actually needed by users.

#### Bug Fixes
Lots of little bug fixes.  The only major bug fix is to [support root-level `$ref`s](https://github.com/BigstickCarpet/json-schema-ref-parser/issues/16)


[Full Changelog](https://github.com/BigstickCarpet/json-schema-ref-parser/compare/v2.2.0...v3.0.0)


## [v2.2.0](https://github.com/BigstickCarpet/json-schema-ref-parser/tree/v2.2.0) (2016-01-03)

This version includes a **complete rewrite** of the [`bundle` method](https://github.com/BigstickCarpet/json-schema-ref-parser/blob/master/docs/ref-parser.md#bundleschema-options-callback) method, mostly to fix [this bug](https://github.com/BigstickCarpet/swagger-parser/issues/16), but also to address a few [edge-cases](https://github.com/BigstickCarpet/json-schema-ref-parser/commit/ca9b322879519e4bcb2dcf6e63f08ac254b90868) that weren't handled before.  As a side-effect of this rewrite, there was also some pretty significant refactoring and code-cleanup done throughout the codebase.

Despite the significant code changes, there were no changes to any public-facing APIs, and [all tests are passing](http://bigstickcarpet.com/json-schema-ref-parser/test/index.html) as expected.

[Full Changelog](https://github.com/BigstickCarpet/json-schema-ref-parser/compare/v2.1.0...v2.2.0)


## [v2.1.0](https://github.com/BigstickCarpet/json-schema-ref-parser/tree/v2.1.0) (2015-12-31)

JSON Schema $Ref Parser now automatically follows HTTP redirects. This is especially great for servers that automatically "ugrade" your connection from HTTP to HTTPS via a 301 redirect. Now that won't break your code.

There are a few [new options](https://github.com/BigstickCarpet/json-schema-ref-parser/blob/master/docs/options.md) that allow you to set the number of redirects (default is 5) and a few other HTTP request properties.

[Full Changelog](https://github.com/BigstickCarpet/json-schema-ref-parser/compare/v2.0.0...v2.1.0)


## [v2.0.0](https://github.com/BigstickCarpet/json-schema-ref-parser/tree/v2.0.0) (2015-12-31)

Bumping the major version number because [this change](https://github.com/BigstickCarpet/json-schema-ref-parser/pull/5) technically breaks backward-compatibility &mdash; although I doubt it will actually affect many people.  Basically, if you're using JSON Schema $Ref Parser to download files from a CORS-enabled server that requires authentication, then you'll need to set the `http.withCredentials` option to `true`.

```javascript
$RefParser.dereference('http://some.server.com/file.json', {
    http: { withCredentials: true }
});
```

[Full Changelog](https://github.com/BigstickCarpet/json-schema-ref-parser/compare/v1.4.1...v2.0.0)

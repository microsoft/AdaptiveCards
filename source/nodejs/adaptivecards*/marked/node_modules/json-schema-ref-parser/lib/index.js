'use strict';

var Promise         = require('./util/promise'),
    Options         = require('./options'),
    $Refs           = require('./refs'),
    parse           = require('./parse'),
    resolveExternal = require('./resolve-external'),
    bundle          = require('./bundle'),
    dereference     = require('./dereference'),
    url             = require('./util/url'),
    maybe           = require('call-me-maybe'),
    ono             = require('ono');

module.exports = $RefParser;
module.exports.YAML = require('./util/yaml');

/**
 * This class parses a JSON schema, builds a map of its JSON references and their resolved values,
 * and provides methods for traversing, manipulating, and dereferencing those references.
 *
 * @constructor
 */
function $RefParser() {
  /**
   * The parsed (and possibly dereferenced) JSON schema object
   *
   * @type {object}
   * @readonly
   */
  this.schema = null;

  /**
   * The resolved JSON references
   *
   * @type {$Refs}
   * @readonly
   */
  this.$refs = new $Refs();
}

/**
 * Parses the given JSON schema.
 * This method does not resolve any JSON references.
 * It just reads a single file in JSON or YAML format, and parse it as a JavaScript object.
 *
 * @param {string|object} schema - The file path or URL of the JSON schema. Or a JSON schema object.
 * @param {$RefParserOptions} [options] - Options that determine how the schema is parsed
 * @param {function} [callback] - An error-first callback. The second parameter is the parsed JSON schema object.
 * @returns {Promise} - The returned promise resolves with the parsed JSON schema object.
 */
$RefParser.parse = function(schema, options, callback) {
  var Class = this; // eslint-disable-line consistent-this
  var instance = new Class();
  return instance.parse.apply(instance, arguments);
};

/**
 * Parses the given JSON schema.
 * This method does not resolve any JSON references.
 * It just reads a single file in JSON or YAML format, and parse it as a JavaScript object.
 *
 * @param {string|object} schema - The file path or URL of the JSON schema. Or a JSON schema object.
 * @param {$RefParserOptions} [options] - Options that determine how the schema is parsed
 * @param {function} [callback] - An error-first callback. The second parameter is the parsed JSON schema object.
 * @returns {Promise} - The returned promise resolves with the parsed JSON schema object.
 */
$RefParser.prototype.parse = function(schema, options, callback) {
  var args = normalizeArgs(arguments);
  var promise;

  if (!args.path && !args.schema) {
    var err = ono('Expected a file path, URL, or object. Got %s', args.path || args.schema);
    return maybe(args.callback, Promise.reject(err));
  }

  // Reset everything
  this.schema = null;
  this.$refs = new $Refs();

  // If the path is a filesystem path, then convert it to a URL.
  // NOTE: According to the JSON Reference spec, these should already be URLs,
  // but, in practice, many people use local filesystem paths instead.
  // So we're being generous here and doing the conversion automatically.
  // This is not intended to be a 100% bulletproof solution.
  // If it doesn't work for your use-case, then use a URL instead.
  if (url.isFileSystemPath(args.path)) {
    args.path = url.fromFileSystemPath(args.path);
  }

  // Resolve the absolute path of the schema
  args.path = url.resolve(url.cwd(), args.path);

  if (args.schema && typeof args.schema === 'object') {
    // A schema object was passed-in.
    // So immediately add a new $Ref with the schema object as its value
    this.$refs._add(args.path, args.schema);
    promise = Promise.resolve(args.schema);
  }
  else {
    // Parse the schema file/url
    promise = parse(args.path, this.$refs, args.options);
  }

  var me = this;
  return promise
    .then(function(result) {
      if (!result || typeof result !== 'object' || Buffer.isBuffer(result)) {
        throw ono.syntax('"%s" is not a valid JSON Schema', me.$refs._root$Ref.path || result);
      }
      else {
        me.schema = result;
        return maybe(args.callback, Promise.resolve(me.schema));
      }
    })
    .catch(function(e) {
      return maybe(args.callback, Promise.reject(e));
    });
};

/**
 * Parses the given JSON schema and resolves any JSON references, including references in
 * externally-referenced files.
 *
 * @param {string|object} schema - The file path or URL of the JSON schema. Or a JSON schema object.
 * @param {$RefParserOptions} [options] - Options that determine how the schema is parsed and resolved
 * @param {function} [callback]
 * - An error-first callback. The second parameter is a {@link $Refs} object containing the resolved JSON references
 *
 * @returns {Promise}
 * The returned promise resolves with a {@link $Refs} object containing the resolved JSON references
 */
$RefParser.resolve = function(schema, options, callback) {
  var Class = this; // eslint-disable-line consistent-this
  var instance = new Class();
  return instance.resolve.apply(instance, arguments);
};

/**
 * Parses the given JSON schema and resolves any JSON references, including references in
 * externally-referenced files.
 *
 * @param {string|object} schema - The file path or URL of the JSON schema. Or a JSON schema object.
 * @param {$RefParserOptions} [options] - Options that determine how the schema is parsed and resolved
 * @param {function} [callback]
 * - An error-first callback. The second parameter is a {@link $Refs} object containing the resolved JSON references
 *
 * @returns {Promise}
 * The returned promise resolves with a {@link $Refs} object containing the resolved JSON references
 */
$RefParser.prototype.resolve = function(schema, options, callback) {
  var me = this;
  var args = normalizeArgs(arguments);

  return this.parse(args.path, args.schema, args.options)
    .then(function() {
      return resolveExternal(me, args.options);
    })
    .then(function() {
      return maybe(args.callback, Promise.resolve(me.$refs));
    })
    .catch(function(err) {
      return maybe(args.callback, Promise.reject(err));
    });
};

/**
 * Parses the given JSON schema, resolves any JSON references, and bundles all external references
 * into the main JSON schema. This produces a JSON schema that only has *internal* references,
 * not any *external* references.
 *
 * @param {string|object} schema - The file path or URL of the JSON schema. Or a JSON schema object.
 * @param {$RefParserOptions} [options] - Options that determine how the schema is parsed, resolved, and dereferenced
 * @param {function} [callback] - An error-first callback. The second parameter is the bundled JSON schema object
 * @returns {Promise} - The returned promise resolves with the bundled JSON schema object.
 */
$RefParser.bundle = function(schema, options, callback) {
  var Class = this; // eslint-disable-line consistent-this
  var instance = new Class();
  return instance.bundle.apply(instance, arguments);
};

/**
 * Parses the given JSON schema, resolves any JSON references, and bundles all external references
 * into the main JSON schema. This produces a JSON schema that only has *internal* references,
 * not any *external* references.
 *
 * @param {string|object} schema - The file path or URL of the JSON schema. Or a JSON schema object.
 * @param {$RefParserOptions} [options] - Options that determine how the schema is parsed, resolved, and dereferenced
 * @param {function} [callback] - An error-first callback. The second parameter is the bundled JSON schema object
 * @returns {Promise} - The returned promise resolves with the bundled JSON schema object.
 */
$RefParser.prototype.bundle = function(schema, options, callback) {
  var me = this;
  var args = normalizeArgs(arguments);

  return this.resolve(args.path, args.schema, args.options)
    .then(function() {
      bundle(me, args.options);
      return maybe(args.callback, Promise.resolve(me.schema));
    })
    .catch(function(err) {
      return maybe(args.callback, Promise.reject(err));
    });
};

/**
 * Parses the given JSON schema, resolves any JSON references, and dereferences the JSON schema.
 * That is, all JSON references are replaced with their resolved values.
 *
 * @param {string|object} schema - The file path or URL of the JSON schema. Or a JSON schema object.
 * @param {$RefParserOptions} [options] - Options that determine how the schema is parsed, resolved, and dereferenced
 * @param {function} [callback] - An error-first callback. The second parameter is the dereferenced JSON schema object
 * @returns {Promise} - The returned promise resolves with the dereferenced JSON schema object.
 */
$RefParser.dereference = function(schema, options, callback) {
  var Class = this; // eslint-disable-line consistent-this
  var instance = new Class();
  return instance.dereference.apply(instance, arguments);
};

/**
 * Parses the given JSON schema, resolves any JSON references, and dereferences the JSON schema.
 * That is, all JSON references are replaced with their resolved values.
 *
 * @param {string|object} schema - The file path or URL of the JSON schema. Or a JSON schema object.
 * @param {$RefParserOptions} [options] - Options that determine how the schema is parsed, resolved, and dereferenced
 * @param {function} [callback] - An error-first callback. The second parameter is the dereferenced JSON schema object
 * @returns {Promise} - The returned promise resolves with the dereferenced JSON schema object.
 */
$RefParser.prototype.dereference = function(schema, options, callback) {
  var me = this;
  var args = normalizeArgs(arguments);

  return this.resolve(args.path, args.schema, args.options)
    .then(function() {
      dereference(me, args.options);
      return maybe(args.callback, Promise.resolve(me.schema));
    })
    .catch(function(err) {
      return maybe(args.callback, Promise.reject(err));
    });
};

/**
 * Normalizes the given arguments, accounting for optional args.
 *
 * @param {Arguments} args
 * @returns {object}
 */
function normalizeArgs(args) {
  var path, schema, options, callback;
  args = Array.prototype.slice.call(args);

  if (typeof args[args.length - 1] === 'function') {
    // The last parameter is a callback function
    callback = args.pop();
  }

  if (typeof args[0] === 'string') {
    // The first parameter is the path
    path = args[0];
    if (typeof args[2] === 'object') {
      // The second parameter is the schema, and the third parameter is the options
      schema = args[1];
      options = args[2];
    }
    else {
      // The second parameter is the options
      schema = undefined;
      options = args[1];
    }
  }
  else {
    // The first parameter is the schema
    path = '';
    schema = args[0];
    options = args[1];
  }

  if (!(options instanceof Options)) {
    options = new Options(options);
  }

  return {
    path: path,
    schema: schema,
    options: options,
    callback: callback
  };
}

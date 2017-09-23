'use strict';

module.exports = {
  /**
   * The order that this validator will run, in relation to other validators.
   *
   * @type {number}
   */
  order: 100,

  /**
   * Determines whether this validator can parse a given schema file.
   *
   * There are three opportunities at which a validator may choose to validate a schema:
   *
   *  1 - After the JSON Schema is parsed, but before any of its JSON References are resolved
   *
   *  2 - After all JSON References have been resolved (and the $Refs object has been populated),
   *      but before any references have been dereferenced
   *
   *  3 - After all JSON References have been dereferenced
   *
   * JSON Schema $Ref Parser's {@link $RefParser.validate} method will only perform as much processing
   * as is necessary to satisfy all validators. So, if all validators are able to process the
   * schema after step 1 above, then steps 2 and 3 will not be performed.  If some validators aren't
   * able to process the schema after step 1, then step 2 will be performed and the remaining validators
   * will be given a second chance to process the schema. If they all do, then step 3 will not be performed.
   * If there are still remaining validators, then step 3 will be performed and the remaining validators
   * will be given a third chance.
   *
   * @param {object} file               - An object containing information about the JSON Schema
   * @param {string} file.url           - The full URL of the schema file
   * @param {string} file.extension     - The lowercased scheam file extension (e.g. ".json", ".yaml", etc.)
   * @param {*}      file.data          - The raw file contents. This will be whatever data type was returned by the resolver
   * @param {object} file.parsed        - The parsed JSON Schema (available in steps 1, 2, and 3)
   * @param {$Refs}  file.resolved      - The resolved JSON References (available in steps 2 and 3)
   * @param {object} file.dereferenced  - The dereferenced JSON Schema (only available in step 3)
   * @returns {boolean}
   */
  canValidate: function canValidate(file) {
    // Z-Schema requires JSON References to already be resolved (but not dereferenced)
    return !!file.resolved;
  },

  /**
   * Validates the given JSON Schema
   *
   * @param {object} file           - An object containing information about the referenced file
   * @param {string} file.url       - The full URL of the referenced file
   * @param {string} file.extension - The lowercased file extension (e.g. ".txt", ".html", etc.)
   * @param {*}      file.data      - The file contents. This will be whatever data type was returned by the resolver
   * @returns {Promise<Buffer>}
   */
  validate: function validate(file) {
    // TODO
  }
};

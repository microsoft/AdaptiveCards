module.exports = {
    root: true,
    extends: [
        "plugin:@typescript-eslint/eslint-recommended",
        "plugin:@typescript-eslint/recommended",
        "plugin:@typescript-eslint/recommended-requiring-type-checking",
        "prettier"
    ],
    env: {
        browser: true,
        node: true
    },
    parser: "@typescript-eslint/parser",
    parserOptions: {
        project: ["tsconfig.json"],
        tsconfigRootDir: __dirname,
        sourceType: "module"
    },
    plugins: ["@typescript-eslint"],
    ignorePatterns: ["node_modules", "__tests__", "__mocks__", "lib", "dist", ".eslintrc.js"],
    rules: {
        "@typescript-eslint/naming-convention": [
            "error",
            {
                selector: "default",
                format: ["camelCase"]
            },
            {
                selector: "variable",
                modifiers: ["exported", "global"],
                format: ["PascalCase"]
            },
            {
                selector: "parameter",
                format: ["camelCase"],
                modifiers: ["unused"],
                prefix: ["_"]
            },
            {
                // a special rule just for the pre-existing (and unchangable)
                // `JsonTypeName` property
                selector: "property",
                format: ["PascalCase"],
                modifiers: ["public"],
                filter: {
                    regex: "JsonTypeName",
                    match: true
                }
            },
            {
                selector: "property",
                format: ["camelCase"],
                modifiers: ["public"],
                leadingUnderscore: "forbid"
            },
            {
                selector: "property",
                modifiers: ["private"],
                format: ["camelCase"],
                leadingUnderscore: "require"
            },
            {
                selector: "property",
                modifiers: ["protected"],
                format: ["camelCase"],
                leadingUnderscore: "require"
            },
            {
                selector: ["enum", "enumMember", "class", "typeLike"],
                format: ["PascalCase"]
            },
            {
                selector: "interface",
                format: ["PascalCase"],
                prefix: ["I"]
            }
        ],

        // let prettier handle quotes
        "@typescript-eslint/quotes": "off",

        // disallow empty functions
        "@typescript-eslint/no-empty-function": "error",

        // prevent errors/warnings on `let someVar: boolean = false;` (rule
        // complains that you shouldn't supply a type when it can be inferred)
        "@typescript-eslint/no-inferrable-types": "off",

        // currently turned off due to false positives
        "@typescript-eslint/no-use-before-define": "off",

        // disallow (someVar == true)
        "@typescript-eslint/no-unnecessary-boolean-literal-compare": "error",

        // in general, we prefer interfaces to type aliases, but still use aliases in some cases
        "@typescript-eslint/no-type-alias": [
            "error",
            {
                allowLiterals: "always", // e.g. `type SmallObject = { name: string; value: string; };`
                allowAliases: "in-unions" // e.g. `type MetaVariable = 'foo' | 'bar' | 'baz';`
            }
        ],

        // disallow `throw 'some string';`
        "@typescript-eslint/no-throw-literal": "error",

        // disallow use of `require` (use `import` instead)
        "@typescript-eslint/no-require-imports": "error",

        // disallow implicit class property declaration via constructor
        "@typescript-eslint/no-parameter-properties": [
            "error",
            {
                allows: ["readonly"]
            }
        ],

        // disallow `foo?.bar!`
        "@typescript-eslint/no-non-null-asserted-optional-chain": "error",

        // disallow functions that may invoke `eval`
        "@typescript-eslint/no-implied-eval": "error",

        // require correct error handling with promises
        "@typescript-eslint/no-floating-promises": [
            "error",
            {
                ignoreVoid: true // allow disabling this check using the `void` keyword
            }
        ],

        // disallow unnecessary classes
        "@typescript-eslint/no-extraneous-class": "error",

        // disallow unnecessary null checks
        "@typescript-eslint/no-extra-non-null-assertion": "error",

        // allow the non-null assertion operator, as it is sometimes needed (see e.g. `MediaSource.render()`)
        "@typescript-eslint/no-non-null-assertion": "off",

        "@typescript-eslint/no-unnecessary-type-assertion": [
            "error",
            {
                "typesToIgnore": [ 'string?' ]
            }
        ],

        // disallow `toString()` calls that would invoke `Object.toString()`
        // (prevents `[Object object]`)
        "@typescript-eslint/no-base-to-string": "error",

        // ban comments that disable typescript checks
        "@typescript-eslint/ban-ts-comment": [
            "error",
            {
                "ts-ignore": true,
                "ts-nocheck": true,
                "ts-check": false // (except comments that improve checking)
            }
        ],

        // TODO: revisit -- we currently don't mark functions as `void` when we probably should
        // require functions to declare return type
        "@typescript-eslint/explicit-function-return-type": "off",

        // TODO: enable at some point
        "@typescript-eslint/restrict-plus-operands": "off",
        "@typescript-eslint/restrict-template-expressions": "off",
        "@typescript-eslint/no-unsafe-call": "off",
        // "@typescript-eslint/prefer-optional-chain": "error",
        // "@typescript-eslint/prefer-readonly": "error",
        // "@typescript-eslint/prefer-readonly-parameter-types": "error",

        // when using Array.sort, require caller to supply a comparison function
        // (otherwise, likely get incorrect sort ordering)
        "@typescript-eslint/require-array-sort-compare": "error",

        // require promise-returning functions to be marked `async`
        "@typescript-eslint/promise-function-async": "error",

        // when iterating over an array in a for loop, prefer `for (item of
        // array) {}` to traditional loop if index is only used to access array
        // members. this can prevent correctness issues and yields
        // cleaner-reading code.
        "@typescript-eslint/prefer-for-of": "error",

        // prefer the "nullish coalescing operator" to "logical or" assignments due to potential gotchas in the "logical or" case
        // let foo = somethingPossiblyNull ?? "default value"; <-- clean and safe
        // let uhoh = ""; <-- logically nullish
        // let bar = uhoh || "this is a problem";
        "@typescript-eslint/prefer-nullish-coalescing": "error",

        // prefer type overloads to distinct function overloads e.g.
        // function foo(param: string) { /**/ };
        // function foo(param: number) { /**/ };
        //    ^-- missed opportunity to share code
        //
        // function foo (param: string | number) { /**/ }; <-- nice
        "@typescript-eslint/unified-signatures": "error",

        // when using switch on an enum value, ensure that every member of the enum has a case statement only warn because
        // we have places where we're safely being non-exhaustive.
        "@typescript-eslint/switch-exhaustiveness-check": "warn",

        "@typescript-eslint/no-unsafe-member-access": "off",
        "@typescript-eslint/no-explicit-any": "off",
        "@typescript-eslint/no-unsafe-argument": "off",
        "@typescript-eslint/no-unsafe-assignment": "off",
        "@typescript-eslint/no-unsafe-return": "off",

        // prevent class members with duplicate names
        "no-dupe-class-members": "off",
        "@typescript-eslint/no-dupe-class-members": "error",

        // disallow unnecessary namespace or enum qualifier use e.g.
        // namespace A {
        // class B { /**/ }
        // function C() { let a: A.B; /*...*/ };
        // already in NS A ------^
        "@typescript-eslint/no-unnecessary-qualifier": "error",

        // disallow empty default constructors
        "@typescript-eslint/no-useless-constructor": "error",

        //--------------------------------------------------------------------------------

        // disallow expressions that have no effect (as they may indicate a typo or mistake) e.g.
        // let a = 5;
        // a + 2; <-- this does nothing
        "@typescript-eslint/no-unused-expressions": "error",

        // turn off no-unused-vars -- there doesn't appear to be a way to
        // configure it to ignore unread parameters on methods that get
        // overridden elsewhere
        "@typescript-eslint/no-unused-vars": "off",

        // require parameters with defaults to be placed at the end of a function signature
        "@typescript-eslint/default-param-last": "error",

        // require curly braces
        curly: "error",

        // don't require using `.` to access properties (e.g. `foo.property`).
        // `.` can only be used to access properties with a "valid identifier",
        // which precludes certain names (e.g. `123`). we don't want to preclude
        // names since we need to be able to roundtrip arbitrary JSON.
        "dot-notation": "off",

        // require use of === (as well as >==, etc.)
        eqeqeq: ["error", "smart"],

        // best explained in the docs:
        // https://github.com/eslint/eslint/blob/master/docs/rules/guard-for-in.md
        "guard-for-in": "error",

        // don't ban variable names
        "id-blacklist": "off",
        "id-match": "off",

        // don't allow bitwise operators (reenable explicitly as needed)
        "no-bitwise": "error",

        // disallow use of `arguments.caller`
        "no-caller": "error",

        // disallow use of console logging (except for console.warn, which we use to warn site owners about lack of
        // markdown processing)
        "no-console": "error",

        // disallow invoking the debugger in code
        "no-debugger": "error",

        // disallow empty blocks
        "no-empty": "error",

        // disallow use of eval
        "no-eval": "error",

        // disallow switch case fallthrough
        "no-fallthrough": "error",

        // disallow using new on wrapper classes (e.g. String)
        "no-new-wrappers": "error",

        // disallow shadow declarations of variables (e.g. let a = 2; let a = 5;)
        "no-redeclare": "error", // same scope
        "no-shadow": "off",
        "@typescript-eslint/no-shadow": "error",

        // disallow underscores at the end of names
        "no-underscore-dangle": "off",

        // don't allow labels that aren't used
        "no-unused-labels": "error",

        // disallow use of `var`
        "no-var": "error"
    }
};

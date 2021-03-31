module.exports = {
    "root": true,
    "extends": [
      "plugin:@typescript-eslint/eslint-recommended",
      "plugin:@typescript-eslint/recommended",
      "plugin:@typescript-eslint/recommended-requiring-type-checking"
    ],
    "env": {
        "browser": true,
        "node": true
    },
    "parser": "@typescript-eslint/parser",
    "parserOptions": {
        "project": "tsconfig.json",
        "sourceType": "module"
    },
    "plugins": [
        "@typescript-eslint",
    ],
    "rules": {
      //--------------------------------------------------------------------------------
      // Syntax/naming conventions

      "camelcase": "off", // disable eslint version
      "@typescript-eslint/naming-convention": [
        "error",
        {                                // let someGlobal : number = 42;
          "selector": "default",         //
          "format": ["camelCase"]        // function someFunction(someParameter: number): number {
        },                               //   let someVariable : number = someParameter*someParameter;
        {                                //   return someVariable;
          "selector": "property",        // }
          "format": ["camelCase"],       //
          "leadingUnderscore": "forbid"  // class SomeClass {
        },                               //   publicProperty : number;
        {                                //   protected _protectedProperty : number;
          "selector": "property",        //   private _privateProperty : number;
          "modifiers": ["private"],      //   publicMemberFunction() : void { /* ... */ }
          "format": ["camelCase"],       //   protected _protectedMemberFunction() : void { /* ... */ }
          "leadingUnderscore": "require" //   private _privateMemberFunction() : void { /* ... */ }
        },                               // }
        {                                //
          "selector": "property",        // enum SomeEnum {
          "modifiers": ["protected"],    //   FirstValue,
          "format": ["camelCase"],       //   SecondValue
          "leadingUnderscore": "require" // }
        },
        {
          "selector": "enum",
          "format": ["PascalCase"]
        },
        {
          "selector": "enumMember",
          "format": ["PascalCase"]
        },
        {
          "selector": "class",
          "format": ["PascalCase"]
        },
        {
          "selector": "typeLike",
          "format": ["PascalCase"]
        }
      ],

      "quotes": "off", // disable eslint's version
      "@typescript-eslint/quotes": [
        "error",
        "double", // use double quotes
        {
          "avoidEscape": true // unless using and alternative to avoid escaping (e.g. 'some "text" here')
        }
      ],

      "semi": "off",// disable eslint's version
      "@typescript-eslint/semi": [ "error", "always" ], // require semicolons

      "@typescript-eslint/type-annotation-spacing": "error", // enforce spacing around `:` in type declarations

      "space-before-function-paren": "off", // disable eslint's version
      // enforce no space between function name and opening paren (e.g. `function foo()`, not `function foo ()`)
      "@typescript-eslint/space-before-function-paren": [ "error", "never" ],

      // same as space-before-function-paren, but for function calls
      "func-call-spacing": "off",
      "@typescript-eslint/func-call-spacing": "error",

      // disallow multiple semicolons (e.g. `let foo = 5;;`)
      "no-extra-semi": "off",
      "@typescript-eslint/no-extra-semi": "error",

      // disallow empty functions
      "no-empty-function": "off", // disable eslint's version
      "@typescript-eslint/no-empty-function": "error",

      // enforce 4 spaces as default indent
      "indent": "off", // disable eslint's version
      "@typescript-eslint/indent": "error",

      // enforce brace placement
      "brace-style": "off", // disable eslint's version
      "@typescript-eslint/brace-style": [
        "error", "stroustrup",
        {
          "allowSingleLine": true
        }
      ],

      // enforce spacing around commas
      "comma-spacing": "off", // disable eslint's version
      "@typescript-eslint/comma-spacing": [
        "error",
        {
          "before": false,
          "after": true
        }
      ],

      // enforce consistent delimiters for class/itf members
      "@typescript-eslint/member-delimiter-style": [
        "error",
        {
          "multiline": {
            "delimiter": "semi",
            "requireLast": true
          },
          "singleline": {
            "delimiter": "semi",
            "requireLast": false
          }
        }
      ],

      // enforce consistent itf naming (require `I` prefix)
      "@typescript-eslint/interface-name-prefix": [
        "error",
        {
          "prefixWithI": "always"
        }
      ],

      // TODO: need to come up with preferred order
      // https://github.com/typescript-eslint/typescript-eslint/blob/master/packages/eslint-plugin/docs/rules/member-ordering.md
      // "@typescript-eslint/member-ordering": [
      //   "error",
      //   {
      //     "default": [
      //       'private-abstract-field',
      //       'private-instance-field',
      //       'private-static-field',
      //       'private-abstract-method',
      //       'private-static-method',
      //       'private-instance-method',
      //       'private-constructor',
      //       'protected-abstract-field',
      //       'protected-instance-field',
      //       'protected-static-field',
      //       'protected-abstract-method',
      //       'protected-static-method',
      //       'protected-instance-method',
      //       'protected-constructor',
      //       'public-abstract-field',
      //       'public-static-field',
      //       'public-instance-field',
      //       'public-abstract-method',
      //       'public-static-method',
      //       'public-instance-method',
      //       'public-constructor',
      //       'signature',
      //     ]
      //   }
      // ],

      //--------------------------------------------------------------------------------


      //--------------------------------------------------------------------------------
      // Safety/correctness

      // prevent errors/warnings on `let someVar: boolean = false;` (rule complains that you shouldn't supply a type
      // when it can be inferred)
      "@typescript-eslint/no-inferrable-types": "off",

      // currently turned off due to false positives
      "@typescript-eslint/no-use-before-define": "off",

      // disallow (someVar == true)
      "@typescript-eslint/no-unnecessary-boolean-literal-compare": "error",

      // in general, we prefer interfaces to type aliases, but still use aliases in some cases
      "@typescript-eslint/no-type-alias": [
        "error",
        {
          "allowLiterals": "always", // e.g. `type SmallObject = { name: string; value: string; };`
          "allowAliases": "in-unions" // e.g. `type MetaVariable = 'foo' | 'bar' | 'baz';`
        }
      ],

      // disallow `throw 'some string';`
      "@typescript-eslint/no-throw-literal": "error",

      // disallow use of `require` (use `import` instead)
      "@typescript-eslint/no-require-imports": "error",

      // disallow implicit class property declaration via constructor
      "@typescript-eslint/no-parameter-properties": "error",

      // disallow `foo?.bar!`
      "@typescript-eslint/no-non-null-asserted-optional-chain": "error",

      // disallow functions that may invoke `eval`
      "@typescript-eslint/no-implied-eval": "error",

      // require correct error handling with promises
      "@typescript-eslint/no-floating-promises": [
        "error",
        {
          "ignoreVoid": true // allow disabling this check using the `void` keyword
        }
      ],

      // disallow unnecessary classes
      "@typescript-eslint/no-extraneous-class": "error",

      // disallow unnecessary null checks
      "@typescript-eslint/no-extra-non-null-assertion": "error",

      // disallow `toString()` calls that would invoke `Object.toString()` (prevents `[Object object]`)
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
      // "@typescript-eslint/explicit-module-boundary-types": "error",

      // TODO: enable at some point
      // "@typescript-eslint/restrict-plus-operands": [
      //   "error",
      //   {
      //     "checkCompoundAssignments": true
      //   }
      // ],

      // when using Array.sort, require caller to supply a comparison function (otherwise, likely get incorrect sort ordering)
      "@typescript-eslint/require-array-sort-compare": "error",

      // require promise-returning functions to be marked `async`
      "@typescript-eslint/promise-function-async": "error",

      // when iterating over an array in a for loop, prefer `for (item of array) {}` to traditional loop if index is
      // only used to access array members. this can prevent correctness issues and yields cleaner-reading code.
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
      // function foo param: string | number) { /**/ }; <-- nice
      "@typescript-eslint/unified-signatures": "error",

      // when using switch on an enum value, ensure that every member of the enum has a case statement only warn because
      // we have places where we're safely being non-exhaustive.
      "@typescript-eslint/switch-exhaustiveness-check": "warn",

      // TODO: reenable -- currently the fixers for these create some questionable code
      // "@typescript-eslint/prefer-optional-chain": "error",
      // "@typescript-eslint/prefer-readonly": "error",
      // "@typescript-eslint/prefer-readonly-parameter-types": "error",

      // TODO: investigate these (revisit use of any)
      // "@typescript-eslint/no-unsafe-call": "error",
      // "@typescript-eslint/no-unsafe-member-access": "error",
      // "@typescript-eslint/no-unsafe-return": "error",
      "@typescript-eslint/no-explicit-any": "off",

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
      "no-unused-expressions": "off",
      "@typescript-eslint/no-unused-expressions": "error",

      // require parameters with defaults to be placed at the end of a function signature
      "@typescript-eslint/default-param-last": "error",

      // don't allow dangling commas in declarations e.g.
      // let a = [ 0,
      //           1,
      // ];         ^--- unnecessary comma
      "comma-dangle": ["error", "never" ],

      // require curly braces
      "curly": "error",

      // prefer the use of dot notation to access properties. e.g.
      // class Foo { public Bar: number; /*...*/ }
      // let foo: Foo = /*...*/;
      // foo.Bar = 7; <-- nice
      // foo["Bar"] = 7; <-- legal but weird
      "dot-notation": "error",

      // require files to end in a single EOL
      "eol-last": "error",

      // require use of === (as well as >==, etc.)
      "eqeqeq": [
        "error",
        "smart"
      ],

      // best explained in the docs: https://github.com/eslint/eslint/blob/master/docs/rules/guard-for-in.md
      "guard-for-in": "error",

      // don't ban variable names
      "id-blacklist": "off",
      "id-match": "off",

      // enforce line length
      "max-len": [
        "error",
        {
          "code": 140
        }
      ],

      // don't allow bitwise operators (reenable explicitly as needed)
      "no-bitwise": "error",

      // disallow use of `arguments.caller`
      "no-caller": "error",

      // disallow use of console logging (except for console.warn, which we use to warn site owners about lack of
      // markdown processing)
      "no-console": [
        "error",
        {
          "allow": [
            "warn"
          ]
        }
      ],

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
      "no-shadow": [ // differing scopes
        "error",
        {
          "hoist": "all"
        }
      ],

      // disallow trailing spaces
      "no-trailing-spaces": "error",

      // disallow underscores at the end of names
      "no-underscore-dangle": "off",

      // don't allow labels that aren't used
      "no-unused-labels": "error",

      // disallow use of `var`
      "no-var": "error"
    }
};

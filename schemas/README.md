# Schema files

## AdaptiveCard schema

### Referenceable versions

Here's a list of the schema URLs you can reference

* https://adaptivecards.io/schemas/1.2.1/adaptive-card.json
* https://adaptivecards.io/schemas/1.2.0/adaptive-card.json
* https://adaptivecards.io/schemas/1.1.0/adaptive-card.json

### Generating the schema

The Adaptive Card schema is generated from "typed schema" files located in the `src` folder. These typed schema files are much easier to author. The schema is then **compiled** into the standard JSON schema file using the nodejs `ac-typed-schema` project in Adaptive Cards. The fact that it's compiled means we can support case-insensitive enums (via lengthy regex expressions) and it also means it's way easier to update the schema and produce a reliable and correct schema without having to worry about `#/definitions` and everything!

Our schema explorer on the website is also generated from the typed schema files in the `src` folder.

To generate the schema, see `../source/nodejs/ac-typed-schema`.

### Non-extensible schema

The schema is **strict**. It doesn't allow unknown types or unknown properties. There's a good reason for that - if we DID allow unknown types/properties, then you wouldn't even know if you're accidently using an unknown property or type... and at that point, why even validate at all!

If you want to run automated tests using the schema in your CI but have to use host-specific properties, you can always add exemptions in your tests when your test fails because of unknown "Action.InvokeAddIn". Then you still get the value of knowing when you're using incorrect properties, and you have to specifically add the known extension properties to a test allowlist of your own.

### Versioned schema

We keep a version history of the schema, and we only support referencing a specific version of the schema. That's because you really don't want the schema randomly changing on you! Updating the schema must be a conscious decision.
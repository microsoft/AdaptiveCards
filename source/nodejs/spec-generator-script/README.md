# Spec Generator Script

This generates a single JavaScript file that can be ran using `node precompiled\spec-generator-script.js` in order to update the specs from the schema.

The precompiled file **IS** included in the git repository even though it's compiled code. The reason for that is we want people to be able to run this code without having to compile all the dependencies. All they need is Node as a pre-requisite.

If you install the [Run On Save extension by emeraldwalk](https://marketplace.visualstudio.com/items?itemName=emeraldwalk.RunOnSave), when you save any changes to the schema file, the script will automatically be ran and the spec tables will be updated.
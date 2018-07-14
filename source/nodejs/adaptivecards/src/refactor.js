"use strict";
exports.__esModule = true;
var fs = require("fs");
var ts = require("typescript");
var prepend = require("prepend-file");
var fileName = 'card-elements.ts';
var sourceFile = ts.createSourceFile(fileName, fs.readFileSync(fileName).toString(), ts.ScriptTarget.ES2015, /*setParentNodes */ true);
var prolog = "";
var declared_in_utility = [];
var preserve_for_prolog = function (node) {
    prolog += node.getFullText();
};
var create_prolog = function (exclude_file) {
    var rex = new RegExp("^.*'\\.\\/" + exclude_file.substr(0, exclude_file.length - 3) + "'.*$", "gm");
    var result = prolog +
        "\nimport {" +
        declared_in_utility.join(",") +
        "} from './utility'\n\n";
    return result.replace(rex, "");
};
var files_created = ["utility.ts"];
var modules_created = {};
var move_to_its_own_file = function (cl) {
    var declaration_node = cl;
    var declared_name = declaration_node.name.getFullText().trim();
    // TODO: make sure the declaration is exported
    var is_export = (cl.modifiers && cl.modifiers[0].kind == ts.SyntaxKind.ExportKeyword);
    var module_name = declared_name.toLowerCase();
    var file_name = module_name + ".ts";
    fs.writeFileSync(file_name, (is_export ? "" : "\n\nexport ") + cl.getFullText().trim());
    files_created.push(file_name);
    modules_created[declared_name] = file_name;
    prolog += "import {" + declared_name + "} from './" + module_name + "'\n";
};
var move_to_utility_file = function (cl) {
    if (ts.isVariableStatement(cl)) {
        var stmt = cl;
        declared_in_utility = declared_in_utility.concat(stmt.declarationList.declarations.map(function (vd) {
            return vd.name.getFullText().trim();
        }));
    }
    else {
        var declaration_node = cl;
        if (declaration_node.name) {
            var declared_name = declaration_node.name.getFullText().trim();
            declared_in_utility.push(declared_name);
        }
        else {
            console.log(declaration_node.getFullText());
        }
    }
    var is_export = (cl.modifiers && cl.modifiers[0].kind == ts.SyntaxKind.ExportKeyword);
    fs.appendFileSync("utility.ts", (is_export ? "" : "\n\nexport ") + cl.getFullText().trim());
};
var ignore = function () { return null; };
var kill_this = function (text) { return function (node) {
    console.log("Found the following node:\n\t" + node.getFullText().trim().substr(0, 50));
    console.log("So I have to abort: " + text + ".\n");
    process.abort();
}; };
var show_error = kill_this("I have no rule for it");
// 229 - ClassDeclaration - move to its own file
// 238 - ImportDeclaration - preserve then copy on every file
// 243 - ExportAssignment - preserve then copy on every file
// 228 - FunctionDeclaration - move to Utilty file
// 231 - TypeAliasDeclaration - move to utilty
// 208 - VariableStatement - move to Utilty file
// 230 - InterfaceDeclaration - move to its own file?
// 232 - EnumDeclaration - move to its own file?
// 1 - EndOfFileToken - do nothing
// 244 - ExportDeclaration - stop (an export declaration -export another module- means it's refactored)
var kind_to_strategy = {
    229: move_to_its_own_file,
    230: move_to_its_own_file,
    232: move_to_its_own_file,
    1: ignore,
    228: move_to_utility_file,
    208: move_to_utility_file,
    231: move_to_utility_file,
    238: preserve_for_prolog,
    243: preserve_for_prolog,
    244: kill_this("This means the refactoring is probably done already")
};
// first pass - process all
sourceFile.forEachChild(function (node) {
    var strategy = kind_to_strategy[node.kind] || show_error;
    strategy(node);
});
// second pass - prolog
files_created.forEach(function (fname) {
    prepend.sync(fname, create_prolog(fname));
});
// third pass - rewrite imports
var contents = files_created.map(function (f) { return "export * from \"./" + f.substr(0, f.length - 3) + "\";"; }).join("\n") +
    "\
export * from \"./enums\";\n\
export * from \"./host-config\";\n\
export { getEnumValueOrDefault } from \"./utils\";\n\
export { IAdaptiveCard, ICardElement } from \"./schema\";";
fs.writeFileSync("adaptivecards.ts", contents);
fs.writeFileSync("card-elements.ts", contents);

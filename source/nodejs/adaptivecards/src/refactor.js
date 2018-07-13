"use strict";
exports.__esModule = true;
var fs = require("fs");
var ts = require("typescript");
var fileName = 'card-elements.ts';
var sourceFile = ts.createSourceFile(fileName, fs.readFileSync(fileName).toString(), ts.ScriptTarget.ES2015, /*setParentNodes */ true);
var prolog = "";
var declared_in_utility = [];
var preserve_for_prolog = function (node) {
    prolog += node.getFullText();
};
var create_prolog = function () {
    return prolog +
        "\nimport {" +
        declared_in_utility.join(",") +
        "} from './utility'\n\n";
};
var modules_created = {};
var move_to_its_own_file = function (cl) {
    var declaration_node = cl;
    var declared_name = declaration_node.name.getFullText().trim();
    // TODO: make sure the declaration is exported
    var is_export = (cl.modifiers && cl.modifiers[0].kind == ts.SyntaxKind.ExportKeyword);
    var module_name = declared_name.toLowerCase();
    var file_name = module_name + ".ts";
    fs.writeFileSync(file_name, create_prolog() + (is_export ? "" : "export ") + cl.getFullText());
    modules_created[declared_name] = file_name;
    prolog += "import {" + declared_name + "} from './" + module_name + "'\n";
};
var prologued_utilty = false;
var move_to_utility_file = function (cl) {
    if (!prologued_utilty) {
        fs.writeFileSync("utility.ts", prolog + "\n\n");
        prologued_utilty = true;
    }
    if (ts.isVariableStatement(cl)) {
        var stmt = cl;
        declared_in_utility.concat(stmt.declarationList.declarations.map(function (vd) { return vd.name.getFullText().trim(); }));
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
    fs.appendFileSync("utility.ts", cl.getFullText());
};
var ignore = function () { return null; };
var show_error = function (node) { return console.log("I have no rule for " + node.kind); };
// 229 - ClassDeclaration - move to its own file
// 238 - ImportDeclaration - preserve then copy on every file
// 228 - FunctionDeclaration - move to Utilty file
// 231 - TypeAliasDeclaration - move to utilty
// 208 - VariableStatement - move to Utilty file
// 230 - InterfaceDeclaration - move to its own file?
// 232 - EnumDeclaration - move to its own file?
// 1 - EndOfFileToken - do nothing
var kind_to_strategy = {
    229: move_to_its_own_file,
    230: move_to_its_own_file,
    232: move_to_its_own_file,
    1: ignore,
    228: move_to_utility_file,
    208: move_to_utility_file,
    231: move_to_utility_file,
    238: preserve_for_prolog
};
// first pass - process all
sourceFile.forEachChild(function (node) {
    var strategy = kind_to_strategy[node.kind] || show_error;
    strategy(node);
});

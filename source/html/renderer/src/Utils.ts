import markdownIt = require("markdown-it");
let markdownProcessor = new markdownIt();

export function processMarkdown(text: string): any {
    return markdownProcessor.render(text);
}

export function isNullOrEmpty(value: string): boolean {
    return value === undefined || value === null || value === "";
}

export function appendChild(node: Node, child: Node) {
    if (child != null && child != undefined) {
        node.appendChild(child);
    }
}

export function getClassNameFromInstance(object: any) {
    return getClassNameFromConstructor(object.constructor);
}

export function getClassNameFromConstructor(constructor: any) {
    // There is a cleaner way to do this in ES6, but in order to support
    // IE11 we need to stick to ES5.
    var constructorString: string = constructor.toString();

    return constructorString.match(/\w+/g)[1];
}
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
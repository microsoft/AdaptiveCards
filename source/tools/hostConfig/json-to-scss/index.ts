function stringToCssColor(color: string): string {
    var regEx = /#([0-9A-F]{2})([0-9A-F]{2})([0-9A-F]{2})([0-9A-F]{2})?/gi;

    var matches = regEx.exec(color);

    if (matches && matches[4]) {
        var a = parseInt(matches[1], 16) / 255;
        var r = parseInt(matches[2], 16);
        var g = parseInt(matches[3], 16);
        var b = parseInt(matches[4], 16);

        return "rgba(" + r + "," + g + "," + b + "," + a + ")";
    }
    else {
        return color;
    }
}

function convertToCssValue(value: any) {
    if (typeof value === 'number') {
        return value + 'px';
    }
    if (typeof value === 'string' && value[0] === '#') {
        return stringToCssColor(value);
    }
    return JSON.stringify(value);
}

function indent(level: number) {
    return new Array(level + 1).join('  ');
}

function appendToLast(output: string[], append: string) {
    output[output.length - 1] += append;
}

function convertToSCSS(x: any, varName = '$hostConfig') {
    var output: string[] = [];

    function walk(prefix: string, node: any, indentLevel: number) {
        output.push(indent(indentLevel) + prefix + ': (');

        var first = true;
        for (var key in node) {

            if (!first) {
                appendToLast(output, ',');
            }

            var value = node[key];

            if (typeof value === 'object') {
                walk(key, value, indentLevel + 1);
            } else {
                output.push(indent(indentLevel + 1) + key + ': ' + convertToCssValue(value));
            }

            first = false;
        }

        output.push(indent(indentLevel) + ')');
    }

    walk(varName, x, 0);

    appendToLast(output, ';');

    return output.join('\n');
}

export = convertToSCSS;

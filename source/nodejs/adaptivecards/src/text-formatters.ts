// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
abstract class AbstractTextFormatter {
    private _regularExpression: RegExp;

    protected abstract internalFormat(lang: string, matches: RegExpExecArray): string;

    constructor(regularExpression: RegExp) {
        this._regularExpression = regularExpression;
    }

    format(lang: string, input: string): string {
        var matches;
        var result = input;

        while ((matches = this._regularExpression.exec(input)) != null) {
            result = result.replace(matches[0], this.internalFormat(lang, matches));
        };

        return result;
    }
}

class DateFormatter extends AbstractTextFormatter {
    protected internalFormat(lang: string, matches: RegExpExecArray): string {
        var date = new Date(Date.parse(matches[1]));
        var format = matches[2] != undefined ? matches[2].toLowerCase() : "compact";

        if (format != "compact") {
            return date.toLocaleDateString(lang, { day: "numeric", weekday: format, month: format, year: "numeric" });
        }
        else {
            return date.toLocaleDateString();
        }
    }
}

class TimeFormatter extends AbstractTextFormatter {
    protected internalFormat(lang: string, matches: RegExpExecArray): string {
        var date = new Date(Date.parse(matches[1]));

        return date.toLocaleTimeString(lang, { hour: 'numeric', minute: '2-digit' });
    }
}

export function formatText(lang: string, text: string): string {
    const formatters: Array<AbstractTextFormatter> = [
        new DateFormatter(/\{{2}DATE\((\d{4}-\d{2}-\d{2}T\d{2}:\d{2}:\d{2}(?:Z|(?:(?:-|\+)\d{2}:\d{2})))(?:, ?(COMPACT|LONG|SHORT))?\)\}{2}/g),
        new TimeFormatter(/\{{2}TIME\((\d{4}-\d{2}-\d{2}T\d{2}:\d{2}:\d{2}(?:Z|(?:(?:-|\+)\d{2}:\d{2})))\)\}{2}/g)
    ];

    var result = text;

    for (var i = 0; i < formatters.length; i++) {
        result = formatters[i].format(lang, result);
    }

    return result;
}

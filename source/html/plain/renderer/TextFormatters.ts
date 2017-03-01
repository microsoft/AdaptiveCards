abstract class AbstractTextFormatter {
    private _regularExpression: RegExp;

    protected abstract internalFormat(matches: RegExpExecArray): string;

    constructor(regularExpression: RegExp) {
        this._regularExpression = regularExpression;
    }

    format(input: string): string {
        var matches;
        var result = input;

        while ((matches = this._regularExpression.exec(input)) != null) {
            result = result.replace(matches[0], this.internalFormat(matches));
        };

        return result;
    }
}

class DateFormatter extends AbstractTextFormatter {
    protected internalFormat(matches: RegExpExecArray): string {
        var date = new Date(Date.parse(matches[1]));

        if (matches[2] != undefined) {
            var longOrShort = matches[2].toLowerCase();

            return date.toLocaleDateString(undefined, { day: "numeric", weekday: longOrShort, month: longOrShort, year: "numeric" });
        }
        else {
            return date.toLocaleDateString();
        }
    }
}

class TimeFormatter extends AbstractTextFormatter {
    protected internalFormat(matches: RegExpExecArray): string {
        var date = new Date(Date.parse(matches[1]));

        return date.toLocaleTimeString();
    }
}

export function formatText(text: string): string {
    const formatters: Array<AbstractTextFormatter> = [
        new DateFormatter(/\{{2}date\((\d{4}-\d{2}-\d{2}T\d{2}:\d{2}:\d{2}(?:z|Z|-\d{1,2}))(?:,(long|short))?\)\}{2}/gi),
        new TimeFormatter(/\{{2}time\((\d{4}-\d{2}-\d{2}T\d{2}:\d{2}:\d{2}(?:z|Z|-\d{1,2}))\)\}{2}/gi)
    ];

    var result = text;

    for (var i = 0; i < formatters.length; i++) {
        result = formatters[i].format(result);
    }

    return result;
}
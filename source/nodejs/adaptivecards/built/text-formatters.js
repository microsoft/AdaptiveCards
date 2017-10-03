"use strict";
var __extends = (this && this.__extends) || (function () {
    var extendStatics = Object.setPrototypeOf ||
        ({ __proto__: [] } instanceof Array && function (d, b) { d.__proto__ = b; }) ||
        function (d, b) { for (var p in b) if (b.hasOwnProperty(p)) d[p] = b[p]; };
    return function (d, b) {
        extendStatics(d, b);
        function __() { this.constructor = d; }
        d.prototype = b === null ? Object.create(b) : (__.prototype = b.prototype, new __());
    };
})();
Object.defineProperty(exports, "__esModule", { value: true });
var AbstractTextFormatter = /** @class */ (function () {
    function AbstractTextFormatter(regularExpression) {
        this._regularExpression = regularExpression;
    }
    AbstractTextFormatter.prototype.format = function (input) {
        var matches;
        var result = input;
        while ((matches = this._regularExpression.exec(input)) != null) {
            result = result.replace(matches[0], this.internalFormat(matches));
        }
        ;
        return result;
    };
    return AbstractTextFormatter;
}());
var DateFormatter = /** @class */ (function (_super) {
    __extends(DateFormatter, _super);
    function DateFormatter() {
        return _super !== null && _super.apply(this, arguments) || this;
    }
    DateFormatter.prototype.internalFormat = function (matches) {
        var date = new Date(Date.parse(matches[1]));
        if (matches[2] != undefined) {
            var longOrShort = matches[2].toLowerCase();
            return date.toLocaleDateString(undefined, { day: "numeric", weekday: longOrShort, month: longOrShort, year: "numeric" });
        }
        else {
            return date.toLocaleDateString();
        }
    };
    return DateFormatter;
}(AbstractTextFormatter));
var TimeFormatter = /** @class */ (function (_super) {
    __extends(TimeFormatter, _super);
    function TimeFormatter() {
        return _super !== null && _super.apply(this, arguments) || this;
    }
    TimeFormatter.prototype.internalFormat = function (matches) {
        var date = new Date(Date.parse(matches[1]));
        return date.toLocaleTimeString();
    };
    return TimeFormatter;
}(AbstractTextFormatter));
function formatText(text) {
    var formatters = [
        new DateFormatter(/\{{2}date\((\d{4}-\d{2}-\d{2}T\d{2}:\d{2}:\d{2}(?:z|Z|-\d{1,2}))(?:,(long|short))?\)\}{2}/gi),
        new TimeFormatter(/\{{2}time\((\d{4}-\d{2}-\d{2}T\d{2}:\d{2}:\d{2}(?:z|Z|-\d{1,2}))\)\}{2}/gi)
    ];
    var result = text;
    for (var i = 0; i < formatters.length; i++) {
        result = formatters[i].format(result);
    }
    return result;
}
exports.formatText = formatText;
//# sourceMappingURL=text-formatters.js.map
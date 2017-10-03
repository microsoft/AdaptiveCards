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
var TypedElement = /** @class */ (function () {
    function TypedElement(type) {
        this.type = type;
    }
    return TypedElement;
}());
exports.TypedElement = TypedElement;
var Card = /** @class */ (function (_super) {
    __extends(Card, _super);
    function Card(init) {
        var _this = _super.call(this, "AdaptiveCard") || this;
        Object.assign(_this, init);
        if (!_this.actions)
            _this.actions = [];
        if (!_this.body)
            _this.body = [];
        return _this;
    }
    return Card;
}(TypedElement));
exports.Card = Card;
var ActionBase = /** @class */ (function (_super) {
    __extends(ActionBase, _super);
    function ActionBase(type, init) {
        var _this = _super.call(this, type) || this;
        Object.assign(_this, init);
        return _this;
    }
    return ActionBase;
}(TypedElement));
exports.ActionBase = ActionBase;
var ActionHttp = /** @class */ (function (_super) {
    __extends(ActionHttp, _super);
    function ActionHttp(init) {
        var _this = _super.call(this, "Action.Http", init) || this;
        Object.assign(_this, init);
        return _this;
    }
    return ActionHttp;
}(ActionBase));
exports.ActionHttp = ActionHttp;
var ActionOpenUrl = /** @class */ (function (_super) {
    __extends(ActionOpenUrl, _super);
    function ActionOpenUrl(init) {
        var _this = _super.call(this, "Action.OpenUrl", init) || this;
        Object.assign(_this, init);
        return _this;
    }
    return ActionOpenUrl;
}(ActionBase));
exports.ActionOpenUrl = ActionOpenUrl;
var ActionShowCard = /** @class */ (function (_super) {
    __extends(ActionShowCard, _super);
    function ActionShowCard(init) {
        var _this = _super.call(this, "Action.ShowCard", init) || this;
        Object.assign(_this, init);
        if (!_this.card)
            _this.card = new Card(null);
        return _this;
    }
    return ActionShowCard;
}(ActionBase));
exports.ActionShowCard = ActionShowCard;
var ActionSubmit = /** @class */ (function (_super) {
    __extends(ActionSubmit, _super);
    function ActionSubmit(init) {
        var _this = _super.call(this, "Action.ShowCard", init) || this;
        Object.assign(_this, init);
        return _this;
    }
    return ActionSubmit;
}(ActionBase));
exports.ActionSubmit = ActionSubmit;
var CardElement = /** @class */ (function (_super) {
    __extends(CardElement, _super);
    function CardElement(type, init) {
        var _this = _super.call(this, type) || this;
        Object.assign(_this, init);
        return _this;
    }
    return CardElement;
}(TypedElement));
exports.CardElement = CardElement;
var ColumnSet = /** @class */ (function (_super) {
    __extends(ColumnSet, _super);
    function ColumnSet(init) {
        var _this = _super.call(this, "ColumnSet", init) || this;
        Object.assign(_this, init);
        if (!_this.columns)
            _this.columns = [];
        return _this;
    }
    return ColumnSet;
}(CardElement));
exports.ColumnSet = ColumnSet;
var ContainerBase = /** @class */ (function (_super) {
    __extends(ContainerBase, _super);
    function ContainerBase(type, init) {
        var _this = _super.call(this, type, init) || this;
        Object.assign(_this, init);
        if (!_this.items)
            _this.items = [];
        if (!_this.actions)
            _this.actions = [];
        return _this;
    }
    ;
    return ContainerBase;
}(CardElement));
exports.ContainerBase = ContainerBase;
var Container = /** @class */ (function (_super) {
    __extends(Container, _super);
    function Container(init) {
        var _this = _super.call(this, "Container", init) || this;
        Object.assign(_this, init);
        return _this;
    }
    return Container;
}(ContainerBase));
exports.Container = Container;
var Column = /** @class */ (function (_super) {
    __extends(Column, _super);
    function Column(init) {
        var _this = _super.call(this, "Column", init) || this;
        Object.assign(_this, init);
        return _this;
    }
    return Column;
}(ContainerBase));
exports.Column = Column;
var Fact = /** @class */ (function () {
    function Fact(init) {
        Object.assign(this, init);
    }
    return Fact;
}());
exports.Fact = Fact;
var FactSet = /** @class */ (function (_super) {
    __extends(FactSet, _super);
    function FactSet(init) {
        var _this = _super.call(this, "FactSet", init) || this;
        Object.assign(_this, init);
        if (!_this.facts)
            _this.facts = [];
        return _this;
    }
    return FactSet;
}(CardElement));
exports.FactSet = FactSet;
var Image = /** @class */ (function (_super) {
    __extends(Image, _super);
    function Image(init) {
        var _this = _super.call(this, "Image", init) || this;
        Object.assign(_this, init);
        return _this;
    }
    return Image;
}(CardElement));
exports.Image = Image;
var ImageSet = /** @class */ (function (_super) {
    __extends(ImageSet, _super);
    function ImageSet(init) {
        var _this = _super.call(this, "ImageSet") || this;
        Object.assign(_this, init);
        if (!_this.images)
            _this.images = [];
        return _this;
    }
    return ImageSet;
}(CardElement));
exports.ImageSet = ImageSet;
var Input = /** @class */ (function (_super) {
    __extends(Input, _super);
    function Input(type, init) {
        var _this = _super.call(this, type) || this;
        Object.assign(_this, init);
        return _this;
    }
    return Input;
}(CardElement));
exports.Input = Input;
var InputDate = /** @class */ (function (_super) {
    __extends(InputDate, _super);
    function InputDate(init) {
        var _this = _super.call(this, "Input.Date", init) || this;
        Object.assign(_this, init);
        return _this;
    }
    return InputDate;
}(Input));
exports.InputDate = InputDate;
var InputNumber = /** @class */ (function (_super) {
    __extends(InputNumber, _super);
    function InputNumber(init) {
        var _this = _super.call(this, "Input.Number", init) || this;
        Object.assign(_this, init);
        return _this;
    }
    return InputNumber;
}(Input));
exports.InputNumber = InputNumber;
var InputText = /** @class */ (function (_super) {
    __extends(InputText, _super);
    function InputText(init) {
        var _this = _super.call(this, "Input.Text", init) || this;
        Object.assign(_this, init);
        return _this;
    }
    return InputText;
}(Input));
exports.InputText = InputText;
var InputTime = /** @class */ (function (_super) {
    __extends(InputTime, _super);
    function InputTime(init) {
        var _this = _super.call(this, "Input.Time", init) || this;
        Object.assign(_this, init);
        return _this;
    }
    return InputTime;
}(Input));
exports.InputTime = InputTime;
var InputToggle = /** @class */ (function (_super) {
    __extends(InputToggle, _super);
    function InputToggle(init) {
        var _this = _super.call(this, "Input.Toggle", init) || this;
        Object.assign(_this, init);
        return _this;
    }
    return InputToggle;
}(Input));
exports.InputToggle = InputToggle;
var TextBlock = /** @class */ (function (_super) {
    __extends(TextBlock, _super);
    function TextBlock(init) {
        var _this = _super.call(this, "TextBlock") || this;
        Object.assign(_this, init);
        return _this;
    }
    return TextBlock;
}(TypedElement));
exports.TextBlock = TextBlock;
//# sourceMappingURL=schema.js.map
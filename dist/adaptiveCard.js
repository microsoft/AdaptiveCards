"use strict";
var __extends = (this && this.__extends) || function (d, b) {
    for (var p in b) if (b.hasOwnProperty(p)) d[p] = b[p];
    function __() { this.constructor = d; }
    d.prototype = b === null ? Object.create(b) : (__.prototype = b.prototype, new __());
};
var markdownIt = require("markdown-it");
var markdownProcessor = new markdownIt();
function processMarkdown(text) {
    return markdownProcessor.render(text);
}
exports.processMarkdown = processMarkdown;
/*
Strongly typed events from https://keestalkstech.com/2016/03/strongly-typed-event-handlers-in-typescript-part-1/
*/
(function (Size) {
    Size[Size["Auto"] = 0] = "Auto";
    Size[Size["Stretch"] = 1] = "Stretch";
    Size[Size["Small"] = 2] = "Small";
    Size[Size["Medium"] = 3] = "Medium";
    Size[Size["Large"] = 4] = "Large";
})(exports.Size || (exports.Size = {}));
var Size = exports.Size;
(function (TextSize) {
    TextSize[TextSize["Small"] = 0] = "Small";
    TextSize[TextSize["Normal"] = 1] = "Normal";
    TextSize[TextSize["Medium"] = 2] = "Medium";
    TextSize[TextSize["Large"] = 3] = "Large";
    TextSize[TextSize["ExtraLarge"] = 4] = "ExtraLarge";
})(exports.TextSize || (exports.TextSize = {}));
var TextSize = exports.TextSize;
(function (TextWeight) {
    TextWeight[TextWeight["Lighter"] = 0] = "Lighter";
    TextWeight[TextWeight["Normal"] = 1] = "Normal";
    TextWeight[TextWeight["Bolder"] = 2] = "Bolder";
})(exports.TextWeight || (exports.TextWeight = {}));
var TextWeight = exports.TextWeight;
(function (TextColor) {
    TextColor[TextColor["Default"] = 0] = "Default";
    TextColor[TextColor["Dark"] = 1] = "Dark";
    TextColor[TextColor["Light"] = 2] = "Light";
    TextColor[TextColor["Accent"] = 3] = "Accent";
    TextColor[TextColor["Good"] = 4] = "Good";
    TextColor[TextColor["Warning"] = 5] = "Warning";
    TextColor[TextColor["Attention"] = 6] = "Attention";
})(exports.TextColor || (exports.TextColor = {}));
var TextColor = exports.TextColor;
(function (HorizontalAlignment) {
    HorizontalAlignment[HorizontalAlignment["Left"] = 0] = "Left";
    HorizontalAlignment[HorizontalAlignment["Center"] = 1] = "Center";
    HorizontalAlignment[HorizontalAlignment["Right"] = 2] = "Right";
})(exports.HorizontalAlignment || (exports.HorizontalAlignment = {}));
var HorizontalAlignment = exports.HorizontalAlignment;
(function (ImageStyle) {
    ImageStyle[ImageStyle["Normal"] = 0] = "Normal";
    ImageStyle[ImageStyle["Person"] = 1] = "Person";
})(exports.ImageStyle || (exports.ImageStyle = {}));
var ImageStyle = exports.ImageStyle;
function stringToSize(value, defaultValue) {
    switch (value) {
        case "auto":
            return Size.Auto;
        case "stretch":
            return Size.Stretch;
        case "small":
            return Size.Small;
        case "medium":
            return Size.Medium;
        case "large":
            return Size.Large;
        default:
            return defaultValue;
    }
}
exports.stringToSize = stringToSize;
function stringToTextSize(value, defaultValue) {
    switch (value) {
        case "small":
            return TextSize.Small;
        case "normal":
            return TextSize.Normal;
        case "medium":
            return TextSize.Medium;
        case "large":
            return TextSize.Large;
        case "extraLarge":
            return TextSize.ExtraLarge;
        default:
            return defaultValue;
    }
}
exports.stringToTextSize = stringToTextSize;
function stringToTextWeight(value, defaultValue) {
    switch (value) {
        case "lighter":
            return TextWeight.Lighter;
        case "normal":
            return TextWeight.Normal;
        case "bolder":
            return TextWeight.Bolder;
        default:
            return defaultValue;
    }
}
exports.stringToTextWeight = stringToTextWeight;
function stringToTextColor(value, defaultValue) {
    switch (value) {
        case "default":
            return TextColor.Default;
        case "dark":
            return TextColor.Dark;
        case "light":
            return TextColor.Light;
        case "accent":
            return TextColor.Accent;
        case "good":
            return TextColor.Good;
        case "warning":
            return TextColor.Warning;
        case "attention":
            return TextColor.Attention;
        default:
            return defaultValue;
    }
}
exports.stringToTextColor = stringToTextColor;
function stringToHorizontalAlignment(value, defaultValue) {
    switch (value) {
        case "left":
            return HorizontalAlignment.Left;
        case "center":
            return HorizontalAlignment.Center;
        case "right":
            return HorizontalAlignment.Right;
        default:
            return defaultValue;
    }
}
exports.stringToHorizontalAlignment = stringToHorizontalAlignment;
function stringToImageStyle(value, defaultValue) {
    switch (value) {
        case "person":
            return ImageStyle.Person;
        case "normal":
            return ImageStyle.Normal;
        default:
            return defaultValue;
    }
}
exports.stringToImageStyle = stringToImageStyle;
var EventDispatcher = (function () {
    function EventDispatcher() {
        this._subscriptions = new Array();
    }
    EventDispatcher.prototype.subscribe = function (fn) {
        if (fn) {
            this._subscriptions.push(fn);
        }
    };
    EventDispatcher.prototype.unsubscribe = function (fn) {
        var i = this._subscriptions.indexOf(fn);
        if (i > -1) {
            this._subscriptions.splice(i, 1);
        }
    };
    EventDispatcher.prototype.dispatch = function (sender, args) {
        for (var _i = 0, _a = this._subscriptions; _i < _a.length; _i++) {
            var handler = _a[_i];
            handler(sender, args);
        }
    };
    return EventDispatcher;
}());
function isNullOrEmpty(value) {
    return value === undefined || value === null || value === "";
}
exports.isNullOrEmpty = isNullOrEmpty;
function appendChild(node, child) {
    if (child != null && child != undefined) {
        node.appendChild(child);
    }
}
exports.appendChild = appendChild;
var CardElement = (function () {
    function CardElement(container) {
        this.size = Size.Auto;
        this.horizontalAlignment = HorizontalAlignment.Left;
        this._container = container;
    }
    CardElement.createElement = function (container, typeName) {
        switch (typeName) {
            case "TextBlock":
                return new TextBlock(container);
            case "Image":
                return new Image(container);
            case "ImageGallery":
                return new ImageGallery(container);
            case "ActionGroup":
                return new ActionGroup(container);
            case "FactGroup":
                return new FactGroup(container);
            case "Separator":
                return new Separator(container);
            case "ColumnGroup":
                return new ColumnGroup(container);
            case "TextInput":
                return new TextInput(container);
            case "DateInput":
                return new DateInput(container);
            case "MultichoiceInput":
                return new MultichoiceInput(container);
            default:
                throw new Error("Unknown element type: " + typeName);
        }
    };
    Object.defineProperty(CardElement.prototype, "container", {
        get: function () {
            return this._container;
        },
        enumerable: true,
        configurable: true
    });
    Object.defineProperty(CardElement.prototype, "hideOverflow", {
        get: function () {
            return true;
        },
        enumerable: true,
        configurable: true
    });
    Object.defineProperty(CardElement.prototype, "useDefaultSizing", {
        get: function () {
            return true;
        },
        enumerable: true,
        configurable: true
    });
    CardElement.prototype.removeTopSpacing = function (element) {
        element.style.marginTop = "0px";
    };
    CardElement.prototype.adjustLayout = function (element) {
        if (this.useDefaultSizing) {
            switch (this.size) {
                case Size.Stretch:
                    element.className += " stretch";
                    break;
                case Size.Small:
                    element.className += " smallSize";
                    break;
                case Size.Medium:
                    element.className += " mediumSize";
                    break;
                case Size.Large:
                    element.className += " largeSize";
                    break;
            }
        }
        switch (this.horizontalAlignment) {
            case HorizontalAlignment.Center:
                element.style.textAlign = "center";
                break;
            case HorizontalAlignment.Right:
                element.style.textAlign = "right";
                break;
        }
        if (this.hideOverflow) {
            element.style.overflow = "hidden";
        }
    };
    CardElement.prototype.internalRender = function () {
        var renderedElement = this.render();
        if (renderedElement != null) {
            this.adjustLayout(renderedElement);
        }
        return renderedElement;
    };
    CardElement.prototype.parse = function (json) {
        this.size = stringToSize(json["size"], this.size);
        this.horizontalAlignment = stringToHorizontalAlignment(json["horizontalAlignment"], this.horizontalAlignment);
    };
    return CardElement;
}());
exports.CardElement = CardElement;
var TextBlock = (function (_super) {
    __extends(TextBlock, _super);
    function TextBlock() {
        _super.apply(this, arguments);
        this.textSize = TextSize.Normal;
        this.textWeight = TextWeight.Normal;
        this.textColor = TextColor.Default;
        this.isSubtle = false;
        this.wrap = true;
    }
    TextBlock.prototype.parse = function (json) {
        _super.prototype.parse.call(this, json);
        this.text = json["text"];
        this.textSize = stringToTextSize(json["textSize"], TextSize.Normal);
        this.textWeight = stringToTextWeight(json["textWeight"], TextWeight.Normal);
        this.textColor = stringToTextColor(json["textColor"], TextColor.Default);
        this.isSubtle = json["isSubtle"];
        this.wrap = json["wrap"];
    };
    TextBlock.prototype.render = function () {
        if (!isNullOrEmpty(this.text)) {
            var element = document.createElement("div");
            var cssStyle = "text ";
            switch (this.textSize) {
                case TextSize.Small:
                    cssStyle += "small ";
                    break;
                case TextSize.Medium:
                    cssStyle += "medium ";
                    break;
                case TextSize.Large:
                    cssStyle += "large ";
                    break;
                case TextSize.ExtraLarge:
                    cssStyle += "extraLarge ";
                    break;
                default:
                    cssStyle += "defaultSize ";
                    break;
            }
            var actualTextColor = this.textColor == TextColor.Default ? this.container.textColor : this.textColor;
            switch (actualTextColor) {
                case TextColor.Dark:
                    cssStyle += "darkColor ";
                    break;
                case TextColor.Light:
                    cssStyle += "lightColor ";
                    break;
                case TextColor.Accent:
                    cssStyle += "accentColor ";
                    break;
                case TextColor.Good:
                    cssStyle += "goodColor ";
                    break;
                case TextColor.Warning:
                    cssStyle += "warningColor ";
                    break;
                case TextColor.Attention:
                    cssStyle += "attentionColor ";
                    break;
                default:
                    cssStyle += "defaultColor ";
                    break;
            }
            if (this.isSubtle) {
                cssStyle += "subtle ";
            }
            switch (this.textWeight) {
                case TextWeight.Lighter:
                    cssStyle += "lighter ";
                    break;
                case TextWeight.Bolder:
                    cssStyle += "bolder ";
                    break;
                default:
                    cssStyle += "defaultWeight ";
                    break;
            }
            element.innerHTML = processMarkdown(this.text);
            element.className = cssStyle;
            if (element.firstElementChild instanceof (HTMLElement)) {
                element.firstElementChild.style.marginTop = "0px";
            }
            if (element.lastElementChild instanceof (HTMLElement)) {
                element.lastElementChild.style.marginBottom = "0px";
            }
            var anchors = element.getElementsByTagName("a");
            for (var i = 0; i < anchors.length; i++) {
                anchors[i].target = "_blank";
            }
            if (!this.wrap) {
                element.style.whiteSpace = "nowrap";
                element.style.textOverflow = "ellipsis";
            }
            return element;
        }
        else {
            return null;
        }
    };
    TextBlock.prototype.removeTopSpacing = function (element) {
        element.style.paddingTop = "0px";
    };
    return TextBlock;
}(CardElement));
exports.TextBlock = TextBlock;
var Fact = (function () {
    function Fact() {
    }
    Fact.prototype.parse = function (json) {
        this.name = json["name"];
        this.value = json["value"];
    };
    return Fact;
}());
exports.Fact = Fact;
var FactGroup = (function (_super) {
    __extends(FactGroup, _super);
    function FactGroup() {
        _super.apply(this, arguments);
        this._items = [];
    }
    Object.defineProperty(FactGroup.prototype, "items", {
        get: function () {
            return this._items;
        },
        enumerable: true,
        configurable: true
    });
    FactGroup.prototype.parse = function (json) {
        _super.prototype.parse.call(this, json);
        if (json["items"] != null) {
            var factArray = json["items"];
            for (var i = 0; i < factArray.length; i++) {
                var fact = new Fact();
                fact.parse(factArray[i]);
                this._items.push(fact);
            }
        }
    };
    FactGroup.prototype.render = function () {
        var element = null;
        if (this._items.length > 0) {
            element = document.createElement("table");
            element.className = "factGroup";
            var html = '';
            for (var i = 0; i < this._items.length; i++) {
                html += '<tr>';
                html += '    <td class="factName">';
                var textBlock = new TextBlock(this.container);
                textBlock.text = this._items[i].name;
                textBlock.textWeight = TextWeight.Bolder;
                var renderedText = textBlock.internalRender();
                if (renderedText != null) {
                    html += renderedText.outerHTML;
                }
                html += '    </td>';
                html += '    <td class="factValue">';
                textBlock = new TextBlock(this.container);
                textBlock.text = this._items[i].value;
                textBlock.textWeight = TextWeight.Lighter;
                renderedText = textBlock.internalRender();
                if (renderedText != null) {
                    html += renderedText.outerHTML;
                }
                html += '    </td>';
                html += '</tr>';
            }
            element.innerHTML = html;
        }
        return element;
    };
    return FactGroup;
}(CardElement));
exports.FactGroup = FactGroup;
var Image = (function (_super) {
    __extends(Image, _super);
    function Image() {
        _super.apply(this, arguments);
        this.style = ImageStyle.Normal;
    }
    Object.defineProperty(Image.prototype, "useDefaultSizing", {
        get: function () {
            return false;
        },
        enumerable: true,
        configurable: true
    });
    Image.prototype.parse = function (json) {
        _super.prototype.parse.call(this, json);
        this.url = json["url"];
        this.style = stringToImageStyle(json["style"], ImageStyle.Normal);
    };
    Image.prototype.render = function () {
        var imageElement = null;
        if (!isNullOrEmpty(this.url)) {
            imageElement = document.createElement("img");
            var cssStyle = "image";
            switch (this.size) {
                case Size.Auto:
                    cssStyle += " autoSize";
                    break;
                case Size.Stretch:
                    cssStyle += " stretch";
                    break;
                case Size.Small:
                    cssStyle += " small";
                    break;
                case Size.Large:
                    cssStyle += " large";
                    break;
                default:
                    cssStyle += " medium";
                    break;
            }
            if (this.style == ImageStyle.Person) {
                cssStyle += " person";
            }
            imageElement.className = cssStyle;
            imageElement.src = this.url;
        }
        return imageElement;
    };
    return Image;
}(CardElement));
exports.Image = Image;
var ImageGallery = (function (_super) {
    __extends(ImageGallery, _super);
    function ImageGallery() {
        _super.apply(this, arguments);
        this._items = [];
        this.imageSize = Size.Medium;
    }
    Object.defineProperty(ImageGallery.prototype, "items", {
        get: function () {
            return this._items;
        },
        enumerable: true,
        configurable: true
    });
    ImageGallery.prototype.parse = function (json) {
        _super.prototype.parse.call(this, json);
        this.imageSize = stringToSize(json["imageSize"], Size.Medium);
        if (json["items"] != null) {
            var imageArray = json["items"];
            for (var i = 0; i < imageArray.length; i++) {
                var image = new Image(this.container);
                image.size = this.imageSize;
                image.url = imageArray[i];
                this._items.push(image);
            }
        }
    };
    ImageGallery.prototype.render = function () {
        var element = null;
        if (this._items.length > 0) {
            element = document.createElement("div");
            element.className = "imageGallery";
            for (var i = 0; i < this._items.length; i++) {
                var renderedImage = this._items[i].internalRender();
                renderedImage.style.margin = "0px";
                renderedImage.style.marginRight = "10px";
                appendChild(element, renderedImage);
            }
        }
        return element;
    };
    return ImageGallery;
}(CardElement));
exports.ImageGallery = ImageGallery;
var Action = (function () {
    function Action(owner) {
        this._owner = owner;
    }
    Action.create = function (owner, typeName) {
        switch (typeName) {
            case "OpenUri":
            case "ViewAction":
                return new OpenUri(owner);
            case "HttpPOST":
                return new HttpPOST(owner);
            case "ActionCard":
                return new ActionCard(owner);
            default:
                throw new Error("Unknown action type: " + typeName);
        }
    };
    Object.defineProperty(Action.prototype, "owner", {
        get: function () {
            return this._owner;
        },
        enumerable: true,
        configurable: true
    });
    Action.prototype.parse = function (json) {
        this.name = json["name"];
    };
    Action.prototype.renderUi = function (container, requiresTopSpacer) {
        if (requiresTopSpacer === void 0) { requiresTopSpacer = false; }
        return null;
    };
    Object.defineProperty(Action.prototype, "hasUi", {
        get: function () {
            return false;
        },
        enumerable: true,
        configurable: true
    });
    return Action;
}());
exports.Action = Action;
var ExternalAction = (function (_super) {
    __extends(ExternalAction, _super);
    function ExternalAction() {
        _super.apply(this, arguments);
    }
    return ExternalAction;
}(Action));
exports.ExternalAction = ExternalAction;
var TargetUri = (function () {
    function TargetUri() {
    }
    TargetUri.prototype.parse = function (json) {
        this.os = json["os"];
        this.uri = json["uri"];
    };
    return TargetUri;
}());
exports.TargetUri = TargetUri;
var OpenUri = (function (_super) {
    __extends(OpenUri, _super);
    function OpenUri() {
        _super.apply(this, arguments);
        this._targets = [];
    }
    OpenUri.prototype.addTarget = function () {
        var targetUri = new TargetUri();
        this._targets.push(targetUri);
        return targetUri;
    };
    OpenUri.prototype.parse = function (json) {
        _super.prototype.parse.call(this, json);
        if (json["@type"] == "ViewAction") {
            var target = new TargetUri();
            target.uri = json["target"][0];
        }
        else {
            if (json["targets"] != undefined) {
                var targetArray = json["targets"];
                for (var i = 0; i < targetArray.length; i++) {
                    var target = this.addTarget();
                    target.parse(targetArray[i]);
                }
            }
        }
    };
    return OpenUri;
}(ExternalAction));
exports.OpenUri = OpenUri;
var HttpPOST = (function (_super) {
    __extends(HttpPOST, _super);
    function HttpPOST() {
        _super.apply(this, arguments);
    }
    HttpPOST.prototype.parse = function (json) {
        _super.prototype.parse.call(this, json);
        this.target = json["target"];
        this.body = json["body"];
        this.bodyContentType = json["bodyContentType"];
        this.successMessage = json["successMessage"];
        this.errorMessage = json["errorMessage"];
    };
    return HttpPOST;
}(ExternalAction));
exports.HttpPOST = HttpPOST;
var Input = (function (_super) {
    __extends(Input, _super);
    function Input() {
        _super.apply(this, arguments);
    }
    Input.createInput = function (container, typeName) {
        switch (typeName) {
            case "TextInput":
                return new TextInput(container);
            case "MultichoiceInput":
                return new MultichoiceInput(container);
            case "DateInput":
                return new DateInput(container);
            default:
                throw new Error("Unknown input type: " + typeName);
        }
    };
    Input.prototype.parse = function (json) {
        _super.prototype.parse.call(this, json);
        this.id = json["id"];
        this.title = json["title"];
        this.value = json["value"];
    };
    return Input;
}(CardElement));
exports.Input = Input;
var TextInput = (function (_super) {
    __extends(TextInput, _super);
    function TextInput(container) {
        _super.call(this, container);
        this.size = Size.Stretch;
    }
    TextInput.prototype.parse = function (json) {
        _super.prototype.parse.call(this, json);
        this.maxLength = json["maxLength"];
        this.isMultiline = json["isMultiline"];
    };
    TextInput.prototype.render = function () {
        var element = document.createElement("textarea");
        element.className = "textInput";
        element.placeholder = this.title;
        return element;
    };
    return TextInput;
}(Input));
exports.TextInput = TextInput;
var Choice = (function () {
    function Choice() {
    }
    Choice.prototype.parse = function (json) {
        this.display = json["display"];
        this.value = json["value"];
    };
    return Choice;
}());
exports.Choice = Choice;
var MultichoiceInput = (function (_super) {
    __extends(MultichoiceInput, _super);
    function MultichoiceInput(container) {
        _super.call(this, container);
        this._choices = [];
        this.size = Size.Medium;
    }
    MultichoiceInput.prototype.parse = function (json) {
        _super.prototype.parse.call(this, json);
        if (json["choices"] != undefined) {
            var choiceArray = json["choices"];
            for (var i = 0; i < choiceArray.length; i++) {
                var choice = new Choice();
                choice.parse(choiceArray[i]);
                this._choices.push(choice);
            }
        }
    };
    MultichoiceInput.prototype.render = function () {
        var selectElement = document.createElement("select");
        selectElement.className = "multichoiceInput";
        for (var i = 0; i < this._choices.length; i++) {
            var option = document.createElement("option");
            option.value = this._choices[i].value;
            option.text = this._choices[i].display;
            appendChild(selectElement, option);
        }
        return selectElement;
    };
    return MultichoiceInput;
}(Input));
exports.MultichoiceInput = MultichoiceInput;
var DateInput = (function (_super) {
    __extends(DateInput, _super);
    function DateInput(container) {
        _super.call(this, container);
        this.size = Size.Medium;
    }
    DateInput.prototype.parse = function (json) {
        _super.prototype.parse.call(this, json);
        this.includeTime = json["includeTime"];
    };
    DateInput.prototype.render = function () {
        var container = document.createElement("div");
        container.style.display = "flex";
        var datePicker = document.createElement("input");
        datePicker.type = "date";
        datePicker.className = "dateInput";
        appendChild(container, datePicker);
        if (this.includeTime) {
            datePicker.style.flex = "1 1 67%";
            var timePicker = document.createElement("input");
            timePicker.type = "time";
            timePicker.className = "timeInput";
            timePicker.style.flex = "1 1 33%";
            appendChild(container, timePicker);
        }
        else {
            datePicker.style.flex = "1 1 100%";
        }
        return container;
    };
    return DateInput;
}(Input));
exports.DateInput = DateInput;
var ActionCard = (function (_super) {
    __extends(ActionCard, _super);
    function ActionCard() {
        _super.apply(this, arguments);
        this._allowedActionTypes = ["OpenUri", "HttpPOST"];
        this._inputs = [];
        this._actions = [];
    }
    Object.defineProperty(ActionCard.prototype, "hasUi", {
        get: function () {
            return true;
        },
        enumerable: true,
        configurable: true
    });
    Object.defineProperty(ActionCard.prototype, "inputs", {
        get: function () {
            return this._inputs;
        },
        enumerable: true,
        configurable: true
    });
    Object.defineProperty(ActionCard.prototype, "actions", {
        get: function () {
            return this._actions;
        },
        enumerable: true,
        configurable: true
    });
    ActionCard.prototype.parse = function (json) {
        _super.prototype.parse.call(this, json);
        if (json["card"] != undefined) {
            this._card = new Container(this.owner.container, ["ActionGroup"]);
            this._card.parse(json["card"]);
        }
        if (json["inputs"] != undefined) {
            var inputArray = json["inputs"];
            for (var i = 0; i < inputArray.length; i++) {
                var input = Input.createInput(this.owner.container, inputArray[i]["@type"]);
                input.parse(inputArray[i]);
                this._inputs.push(input);
            }
        }
        if (json["actions"] != undefined) {
            var actionArray = json["actions"];
            for (var i = 0; i < actionArray.length; i++) {
                var actionJson = actionArray[i];
                var typeIsAllowed = false;
                for (var j = 0; j < this._allowedActionTypes.length; j++) {
                    if (actionJson["@type"] === this._allowedActionTypes[j]) {
                        typeIsAllowed = true;
                        break;
                    }
                }
                if (typeIsAllowed) {
                    var action = Action.create(this.owner, actionJson["@type"]);
                    action.parse(actionJson);
                    this._actions.push(action);
                }
            }
        }
    };
    ActionCard.prototype.actionClicked = function (actionButton) {
        alert('Now executing "' + actionButton.text + '"');
    };
    ActionCard.prototype.renderUi = function (container, needsTopSpacer) {
        var _this = this;
        if (needsTopSpacer === void 0) { needsTopSpacer = false; }
        var actionCardElement = document.createElement("div");
        if (this._card != null) {
            appendChild(actionCardElement, this._card.internalRender());
        }
        else {
            for (var i = 0; i < this._inputs.length; i++) {
                var inputElement = this._inputs[i].internalRender();
                appendChild(actionCardElement, inputElement);
            }
        }
        var buttonsContainer = document.createElement("div");
        buttonsContainer.style.display = "flex";
        buttonsContainer.style.marginTop = "16px";
        for (var i = 0; i < this._actions.length; i++) {
            var actionButton = new ActionButton(this._actions[i], ActionButtonStyle.Push);
            actionButton.text = this._actions[i].name;
            actionButton.onClick.subscribe(function (ab, args) {
                _this.actionClicked(ab);
            });
            if (this._actions.length > 1 && i < this._actions.length - 1) {
                actionButton.element.style.marginRight = "16px";
            }
            appendChild(buttonsContainer, actionButton.element);
        }
        appendChild(actionCardElement, buttonsContainer);
        return actionCardElement;
    };
    return ActionCard;
}(Action));
exports.ActionCard = ActionCard;
(function (ActionButtonStyle) {
    ActionButtonStyle[ActionButtonStyle["Link"] = 0] = "Link";
    ActionButtonStyle[ActionButtonStyle["Push"] = 1] = "Push";
})(exports.ActionButtonStyle || (exports.ActionButtonStyle = {}));
var ActionButtonStyle = exports.ActionButtonStyle;
(function (ActionButtonState) {
    ActionButtonState[ActionButtonState["Normal"] = 0] = "Normal";
    ActionButtonState[ActionButtonState["Expanded"] = 1] = "Expanded";
    ActionButtonState[ActionButtonState["Subdued"] = 2] = "Subdued";
})(exports.ActionButtonState || (exports.ActionButtonState = {}));
var ActionButtonState = exports.ActionButtonState;
var ActionButton = (function () {
    function ActionButton(action, style) {
        var _this = this;
        this._onClick = new EventDispatcher();
        this._element = null;
        this._state = ActionButtonState.Normal;
        this._action = action;
        this._style = style;
        this._element = document.createElement("div");
        this._element.onclick = function (e) { _this.click(); };
        this.updateCssStyle();
    }
    ActionButton.prototype.click = function () {
        this._onClick.dispatch(this, null);
    };
    ActionButton.prototype.updateCssStyle = function () {
        var cssStyle = this._style == ActionButtonStyle.Link ? "linkButton " : "pushButton ";
        switch (this._state) {
            case ActionButtonState.Expanded:
                cssStyle += " expanded";
                break;
            case ActionButtonState.Subdued:
                cssStyle += " subdued";
                break;
        }
        this._element.className = cssStyle;
    };
    Object.defineProperty(ActionButton.prototype, "action", {
        get: function () {
            return this._action;
        },
        enumerable: true,
        configurable: true
    });
    Object.defineProperty(ActionButton.prototype, "onClick", {
        get: function () {
            return this._onClick;
        },
        enumerable: true,
        configurable: true
    });
    Object.defineProperty(ActionButton.prototype, "text", {
        get: function () {
            return this._text;
        },
        set: function (value) {
            this._text = value;
            this._element.innerText = this._text;
        },
        enumerable: true,
        configurable: true
    });
    Object.defineProperty(ActionButton.prototype, "element", {
        get: function () {
            return this._element;
        },
        enumerable: true,
        configurable: true
    });
    Object.defineProperty(ActionButton.prototype, "state", {
        get: function () {
            return this._state;
        },
        set: function (value) {
            this._state = value;
            this.updateCssStyle();
        },
        enumerable: true,
        configurable: true
    });
    return ActionButton;
}());
exports.ActionButton = ActionButton;
var ActionGroup = (function (_super) {
    __extends(ActionGroup, _super);
    function ActionGroup() {
        _super.apply(this, arguments);
        this._actionButtons = [];
        this._actions = [];
        this._expandedAction = null;
    }
    ActionGroup.prototype.hideActionCardPane = function () {
        this._actionCardContainer.innerHTML = '';
        this._actionCardContainer.style.padding = "0px";
        this._actionCardContainer.style.marginTop = "0px";
        this.container.showBottomSpacer(this);
    };
    ActionGroup.prototype.showActionCardPane = function (action) {
        this.container.hideBottomSpacer(this);
        this._actionCardContainer.innerHTML = '';
        this._actionCardContainer.style.padding = null;
        this._actionCardContainer.style.marginTop = null;
        appendChild(this._actionCardContainer, action.renderUi(this.container, this._actions.length > 1));
    };
    ActionGroup.prototype.actionClicked = function (actionButton) {
        if (!actionButton.action.hasUi) {
            for (var i = 0; i < this._actionButtons.length; i++) {
                this._actionButtons[i].state = ActionButtonState.Normal;
            }
            this.hideActionCardPane();
            alert("Executing action " + actionButton.text);
        }
        else {
            if (actionButton.action === this._expandedAction) {
                for (var i = 0; i < this._actionButtons.length; i++) {
                    this._actionButtons[i].state = ActionButtonState.Normal;
                }
                this._expandedAction = null;
                this.hideActionCardPane();
            }
            else {
                for (var i = 0; i < this._actionButtons.length; i++) {
                    if (this._actionButtons[i] !== actionButton) {
                        this._actionButtons[i].state = ActionButtonState.Subdued;
                    }
                }
                actionButton.state = ActionButtonState.Expanded;
                this._expandedAction = actionButton.action;
                this.showActionCardPane(actionButton.action);
            }
        }
    };
    Object.defineProperty(ActionGroup.prototype, "actions", {
        get: function () {
            return this._actions;
        },
        enumerable: true,
        configurable: true
    });
    Object.defineProperty(ActionGroup.prototype, "hideOverflow", {
        get: function () {
            return false;
        },
        enumerable: true,
        configurable: true
    });
    ActionGroup.prototype.parse = function (json) {
        _super.prototype.parse.call(this, json);
        if (json["items"] != null) {
            var actionArray = json["items"];
            for (var i = 0; i < actionArray.length; i++) {
                var action = Action.create(this, actionArray[i]["@type"]);
                action.parse(actionArray[i]);
                this._actions.push(action);
            }
        }
    };
    ActionGroup.prototype.render = function () {
        var _this = this;
        var element = document.createElement("div");
        element.className = "actionGroup";
        var buttonStrip = document.createElement("div");
        buttonStrip.className = "buttonStrip";
        if (this._actions.length == 1 && this._actions[0] instanceof ActionCard) {
            this.showActionCardPane(this._actions[0]);
        }
        else {
            for (var i = 0; i < this._actions.length; i++) {
                var buttonStripItem = document.createElement("div");
                buttonStripItem.className = "buttonStripItem";
                var actionButton = new ActionButton(this._actions[i], ActionGroup.buttonStyle);
                actionButton.text = this._actions[i].name;
                actionButton.onClick.subscribe(function (ab, args) {
                    _this.actionClicked(ab);
                });
                this._actionButtons.push(actionButton);
                if (i < this._actions.length - 1) {
                    buttonStripItem.className += " buttonStripItemSpacer";
                }
                appendChild(buttonStripItem, actionButton.element);
                appendChild(buttonStrip, buttonStripItem);
            }
        }
        appendChild(element, buttonStrip);
        this._actionCardContainer = document.createElement("div");
        this._actionCardContainer.className = "actionCardContainer";
        this._actionCardContainer.style.padding = "0px";
        this._actionCardContainer.style.marginTop = "0px";
        appendChild(element, this._actionCardContainer);
        return element;
    };
    ActionGroup.buttonStyle = ActionButtonStyle.Push;
    return ActionGroup;
}(CardElement));
exports.ActionGroup = ActionGroup;
var Separator = (function (_super) {
    __extends(Separator, _super);
    function Separator() {
        _super.apply(this, arguments);
    }
    Separator.prototype.parse = function (json) {
        _super.prototype.parse.call(this, json);
        // Nothing else to parse
    };
    Separator.prototype.render = function () {
        var element = document.createElement("div");
        element.className = "separator";
        return element;
    };
    return Separator;
}(CardElement));
exports.Separator = Separator;
var Container = (function (_super) {
    __extends(Container, _super);
    function Container(container, forbiddenItemTypes) {
        if (forbiddenItemTypes === void 0) { forbiddenItemTypes = null; }
        _super.call(this, container);
        this._items = [];
        this._textColor = TextColor.Default;
        this._forbiddenItemTypes = forbiddenItemTypes;
    }
    Container.prototype.isAllowedItemType = function (elementType) {
        if (this._forbiddenItemTypes == null) {
            return true;
        }
        for (var i = 0; i < this._forbiddenItemTypes.length; i++) {
            if (elementType == this._forbiddenItemTypes[i]) {
                return false;
            }
        }
        if (this.container != null) {
            return this.container.isAllowedItemType(elementType);
        }
        else {
            return true;
        }
    };
    Object.defineProperty(Container.prototype, "cssClassName", {
        get: function () {
            return "container";
        },
        enumerable: true,
        configurable: true
    });
    Object.defineProperty(Container.prototype, "items", {
        get: function () {
            return this._items;
        },
        enumerable: true,
        configurable: true
    });
    Object.defineProperty(Container.prototype, "elementCount", {
        get: function () {
            return this._items.length;
        },
        enumerable: true,
        configurable: true
    });
    Object.defineProperty(Container.prototype, "hideOverflow", {
        get: function () {
            return false;
        },
        enumerable: true,
        configurable: true
    });
    Object.defineProperty(Container.prototype, "textColor", {
        get: function () {
            if (this.container == null) {
                return this._textColor == TextColor.Default ? TextColor.Dark : this._textColor;
            }
            if (this._textColor == TextColor.Default) {
                return this.container.textColor;
            }
            return this._textColor;
        },
        set: function (value) {
            this._textColor = value;
        },
        enumerable: true,
        configurable: true
    });
    Container.prototype.addElement = function (element) {
        if (element != null) {
            this._items.push(element);
        }
    };
    Container.prototype.isLastElement = function (element) {
        return this._items.indexOf(element) == this.elementCount - 1;
    };
    Container.prototype.getElement = function (index) {
        return this._items[index];
    };
    Container.prototype.showBottomSpacer = function (requestingElement) {
        if (this.isLastElement(requestingElement)) {
            this._element.style.paddingBottom = null;
            if (this.container != null) {
                this.container.showBottomSpacer(this);
            }
        }
    };
    Container.prototype.hideBottomSpacer = function (requestingElement) {
        if (this.isLastElement(requestingElement)) {
            this._element.style.paddingBottom = "0px";
            if (this.container != null) {
                this.container.hideBottomSpacer(this);
            }
        }
    };
    Container.prototype.parse = function (json) {
        _super.prototype.parse.call(this, json);
        this.backgroundImageUrl = json["backgroundImage"];
        this.backgroundColor = json["backgroundColor"];
        this._textColor = stringToTextColor(json["textColor"], TextColor.Default);
        if (json["items"] != null) {
            var items = json["items"];
            for (var i = 0; i < items.length; i++) {
                var elementType = items[i]["@type"];
                if (this.isAllowedItemType(elementType)) {
                    var element = CardElement.createElement(this, elementType);
                    element.parse(items[i]);
                    this.addElement(element);
                }
                else {
                    throw new Error("Elements of type " + elementType + " are not allowed in this container.");
                }
            }
        }
    };
    Container.prototype.render = function () {
        if (this.elementCount > 0) {
            this._element = document.createElement("div");
            this._element.className = this.cssClassName;
            if (!isNullOrEmpty(this.backgroundColor)) {
                this._element.style.backgroundColor = this.backgroundColor;
            }
            var html = '';
            var previousElement = null;
            for (var i = 0; i < this.elementCount; i++) {
                var renderedElement = this.getElement(i).internalRender();
                if (renderedElement != null) {
                    if (previousElement == null) {
                        this.getElement(i).removeTopSpacing(renderedElement);
                    }
                    appendChild(this._element, renderedElement);
                }
                previousElement = this.getElement(i);
            }
            if (!isNullOrEmpty(this.backgroundImageUrl)) {
                this._element.style.backgroundImage = 'url("' + this.backgroundImageUrl + '")';
                this._element.style.backgroundRepeat = "no-repeat";
                this._element.style.backgroundSize = "cover";
            }
        }
        return this._element;
    };
    Container.prototype.getRootContainer = function () {
        var currentContainer = this;
        while (currentContainer.container != null) {
            currentContainer = currentContainer.container;
        }
        return currentContainer;
    };
    return Container;
}(CardElement));
exports.Container = Container;
var Column = (function (_super) {
    __extends(Column, _super);
    function Column() {
        _super.apply(this, arguments);
        this._useWeight = false;
        this._weight = 100;
    }
    Object.defineProperty(Column.prototype, "cssClassName", {
        get: function () {
            return "column";
        },
        enumerable: true,
        configurable: true
    });
    Column.prototype.parse = function (json) {
        _super.prototype.parse.call(this, json);
        this.size = stringToSize(json["size"], undefined);
        if (this.size === undefined) {
            this._useWeight = true;
            this._weight = Number(json["size"]);
        }
    };
    Column.prototype.adjustLayout = function (element) {
        if (this._useWeight) {
            element.style.flex = "1 1 " + this._weight + "%";
        }
        else {
            switch (this.size) {
                case Size.Stretch:
                    element.style.flex = "1 1 auto";
                    break;
                default:
                    element.style.flex = "0 0 auto";
                    break;
            }
        }
    };
    return Column;
}(Container));
exports.Column = Column;
var ColumnGroup = (function (_super) {
    __extends(ColumnGroup, _super);
    function ColumnGroup() {
        _super.apply(this, arguments);
        this._items = [];
    }
    ColumnGroup.prototype.addColumn = function () {
        var column = new Column(this.container, ["ColumnGroup", "ActionGroup"]);
        this._items.push(column);
        return column;
    };
    ColumnGroup.prototype.parse = function (json) {
        _super.prototype.parse.call(this, json);
        if (json["items"] != null) {
            var itemArray = json["items"];
            for (var i = 0; i < itemArray.length; i++) {
                var column = this.addColumn();
                column.parse(itemArray[i]);
            }
        }
    };
    ColumnGroup.prototype.render = function () {
        if (this._items.length > 0) {
            var element = document.createElement("div");
            element.className = "columnGroup";
            element.style.display = "flex";
            for (var i = 0; i < this._items.length; i++) {
                var renderedColumn = this._items[i].internalRender();
                appendChild(element, renderedColumn);
                if (this._items.length > 1 && i < this._items.length - 1) {
                    var spacer = document.createElement("div");
                    spacer.className = "columnSpacer";
                    spacer.style.flex = "0 0 auto";
                    appendChild(element, spacer);
                }
            }
            return element;
        }
        else {
            return null;
        }
    };
    return ColumnGroup;
}(CardElement));
exports.ColumnGroup = ColumnGroup;
var AdaptiveCard = (function () {
    function AdaptiveCard() {
        this._rootContainer = new Container(null);
        this.textColor = TextColor.Dark;
    }
    AdaptiveCard.prototype.parse = function (json) {
        this._rootContainer.backgroundImageUrl = json["backgroundImage"];
        if (json["sections"] != undefined) {
            var sectionArray = json["sections"];
            for (var i = 0; i < sectionArray.length; i++) {
                var section = new Container(this._rootContainer, ["Section"]);
                section.parse(sectionArray[i]);
                this._rootContainer.addElement(section);
            }
        }
    };
    AdaptiveCard.prototype.render = function () {
        this._rootContainer.textColor = this.textColor;
        var renderedContainer = this._rootContainer.internalRender();
        renderedContainer.className = "rootContainer";
        return renderedContainer;
    };
    return AdaptiveCard;
}());
exports.AdaptiveCard = AdaptiveCard;
//# sourceMappingURL=adaptiveCard.js.map
var __extends = (this && this.__extends) || function (d, b) {
    for (var p in b) if (b.hasOwnProperty(p)) d[p] = b[p];
    function __() { this.constructor = d; }
    d.prototype = b === null ? Object.create(b) : (__.prototype = b.prototype, new __());
};
/*
Strongly typed events from https://keestalkstech.com/2016/03/strongly-typed-event-handlers-in-typescript-part-1/
*/
var Size = (function () {
    function Size(name, physicalSize, physicalPictureSize) {
        if (physicalSize === void 0) { physicalSize = undefined; }
        if (physicalPictureSize === void 0) { physicalPictureSize = undefined; }
        this.name = name;
        this.physicalSize = physicalSize;
        this.physicalPictureSize = physicalPictureSize;
    }
    Size.parse = function (name, defaultValue) {
        for (var key in Size) {
            if (!isNullOrEmpty(Size[key].name) && Size[key].name == name) {
                return Size[key];
            }
        }
        return defaultValue;
    };
    Size.Auto = new Size("auto");
    Size.Stretch = new Size("stretch");
    Size.Small = new Size("small", 100, 40);
    Size.Medium = new Size("medium", 200, 80);
    Size.Large = new Size("large", 300, 160);
    return Size;
}());
var Spacing;
(function (Spacing) {
    Spacing[Spacing["None"] = 0] = "None";
    Spacing[Spacing["Default"] = 1] = "Default";
})(Spacing || (Spacing = {}));
var TextSize;
(function (TextSize) {
    TextSize[TextSize["Small"] = 0] = "Small";
    TextSize[TextSize["Normal"] = 1] = "Normal";
    TextSize[TextSize["Medium"] = 2] = "Medium";
    TextSize[TextSize["Large"] = 3] = "Large";
    TextSize[TextSize["ExtraLarge"] = 4] = "ExtraLarge";
})(TextSize || (TextSize = {}));
var TextWeight;
(function (TextWeight) {
    TextWeight[TextWeight["Lighter"] = 0] = "Lighter";
    TextWeight[TextWeight["Normal"] = 1] = "Normal";
    TextWeight[TextWeight["Bolder"] = 2] = "Bolder";
})(TextWeight || (TextWeight = {}));
var TextColor;
(function (TextColor) {
    TextColor[TextColor["Default"] = 0] = "Default";
    TextColor[TextColor["Dark"] = 1] = "Dark";
    TextColor[TextColor["Light"] = 2] = "Light";
    TextColor[TextColor["Accent"] = 3] = "Accent";
})(TextColor || (TextColor = {}));
var HorizontalAlignment;
(function (HorizontalAlignment) {
    HorizontalAlignment[HorizontalAlignment["Left"] = 0] = "Left";
    HorizontalAlignment[HorizontalAlignment["Center"] = 1] = "Center";
    HorizontalAlignment[HorizontalAlignment["Right"] = 2] = "Right";
})(HorizontalAlignment || (HorizontalAlignment = {}));
var PictureStyle;
(function (PictureStyle) {
    PictureStyle[PictureStyle["Normal"] = 0] = "Normal";
    PictureStyle[PictureStyle["Person"] = 1] = "Person";
})(PictureStyle || (PictureStyle = {}));
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
        default:
            return defaultValue;
    }
}
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
function stringToPictureStyle(value, defaultValue) {
    switch (value) {
        case "person":
            return PictureStyle.Person;
        case "normal":
            return PictureStyle.Normal;
        default:
            return defaultValue;
    }
}
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
function appendChild(node, child) {
    if (child != null && child != undefined) {
        node.appendChild(child);
    }
}
var CardElement = (function () {
    function CardElement(container) {
        this.size = Size.Auto;
        this.horizontalAlignment = HorizontalAlignment.Left;
        this.topSpacing = Spacing.Default;
        this._container = container;
    }
    CardElement.createElement = function (container, typeName) {
        switch (typeName) {
            case "TextBlock":
                return new TextBlock(container);
            case "Picture":
                return new Picture(container);
            case "PictureGallery":
                return new PictureGallery(container);
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
    CardElement.prototype.removeTopSpacing = function (element) {
        element.style.marginTop = "0px";
    };
    CardElement.prototype.adjustLayout = function (element) {
        if (this.size == Size.Stretch) {
            element.style.width = "100%";
        }
        else if (this.size != Size.Auto) {
            element.style.width = this.size.physicalSize.toString() + "px";
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
        if (this.topSpacing == Spacing.None) {
            this.removeTopSpacing(renderedElement);
        }
        return renderedElement;
    };
    CardElement.prototype.parse = function (json) {
        this.size = Size.parse(json["size"], this.size);
        this.horizontalAlignment = stringToHorizontalAlignment(json["horizontalAlignment"], this.horizontalAlignment);
        if (json["topSpacing"] === "none") {
            this.topSpacing = Spacing.None;
        }
    };
    return CardElement;
}());
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
            var firstChild = element.firstChild;
            firstChild.className = cssStyle;
            var anchors = firstChild.getElementsByTagName("a");
            for (var i = 0; i < anchors.length; i++) {
                anchors[i].target = "_blank";
            }
            if (!this.wrap) {
                firstChild.style.whiteSpace = "nowrap";
                firstChild.style.textOverflow = "ellipsis";
            }
            return firstChild;
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
var Fact = (function () {
    function Fact() {
    }
    Fact.prototype.parse = function (json) {
        this.name = json["name"];
        this.value = json["value"];
    };
    return Fact;
}());
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
                html += '    <td style="border-width: 0px; padding: 0px; border-style: none; min-width: 100px; vertical-align: top">';
                var textBlock = new TextBlock(this.container);
                textBlock.text = this._items[i].name;
                textBlock.textWeight = TextWeight.Bolder;
                textBlock.topSpacing = Spacing.None;
                html += textBlock.internalRender().outerHTML;
                html += '    </td>';
                html += '    <td style="border-width: 0px; padding: 0px; border-style: none; vertical-align: top; padding: 0px 0px 0px 10px">';
                textBlock = new TextBlock(this.container);
                textBlock.text = this._items[i].value;
                textBlock.textWeight = TextWeight.Lighter;
                textBlock.topSpacing = Spacing.None;
                html += textBlock.internalRender().outerHTML;
                html += '    </td>';
                html += '</tr>';
            }
            element.innerHTML = html;
        }
        return element;
    };
    return FactGroup;
}(CardElement));
var Picture = (function (_super) {
    __extends(Picture, _super);
    function Picture() {
        _super.apply(this, arguments);
        this.style = PictureStyle.Normal;
    }
    Picture.prototype.parse = function (json) {
        _super.prototype.parse.call(this, json);
        this.url = json["url"];
        this.style = stringToPictureStyle(json["style"], PictureStyle.Normal);
    };
    Picture.prototype.render = function () {
        var image = null;
        if (!isNullOrEmpty(this.url)) {
            image = document.createElement("img");
            image.className = "picture";
            if (this.size == Size.Auto) {
                image.style.maxWidth = "100%";
            }
            else {
                image.style.maxWidth = this.size.physicalPictureSize.toString() + "px";
                image.style.maxHeight = this.size.physicalPictureSize.toString() + "px";
                if (this.style == PictureStyle.Person) {
                    image.className = "inCircle";
                    image.style.borderRadius = (this.size.physicalPictureSize / 2).toString() + "px";
                    image.style.backgroundPosition = "50% 50%";
                    image.style.backgroundRepeat = "no-repeat";
                }
            }
            image.src = this.url;
        }
        return image;
    };
    return Picture;
}(CardElement));
var PictureGallery = (function (_super) {
    __extends(PictureGallery, _super);
    function PictureGallery() {
        _super.apply(this, arguments);
        this._items = [];
        this.pictureSize = Size.Medium;
    }
    Object.defineProperty(PictureGallery.prototype, "items", {
        get: function () {
            return this._items;
        },
        enumerable: true,
        configurable: true
    });
    PictureGallery.prototype.parse = function (json) {
        _super.prototype.parse.call(this, json);
        this.pictureSize = Size.parse(json["imageSize"], Size.Medium);
        if (json["items"] != null) {
            var pictureArray = json["items"];
            for (var i = 0; i < pictureArray.length; i++) {
                var picture = new Picture(this.container);
                picture.size = this.pictureSize;
                picture.url = pictureArray[i];
                this._items.push(picture);
            }
        }
    };
    PictureGallery.prototype.render = function () {
        var element = null;
        if (this._items.length > 0) {
            element = document.createElement("div");
            element.className = "pictureGallery";
            for (var i = 0; i < this._items.length; i++) {
                var renderedPicture = this._items[i].render();
                renderedPicture.style.margin = "0px";
                renderedPicture.style.marginRight = "10px";
                appendChild(element, renderedPicture);
            }
        }
        return element;
    };
    return PictureGallery;
}(CardElement));
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
var ExternalAction = (function (_super) {
    __extends(ExternalAction, _super);
    function ExternalAction() {
        _super.apply(this, arguments);
    }
    return ExternalAction;
}(Action));
var TargetUri = (function () {
    function TargetUri() {
    }
    TargetUri.prototype.parse = function (json) {
        this.os = json["os"];
        this.uri = json["uri"];
    };
    return TargetUri;
}());
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
        element.className = "input textInput";
        element.placeholder = this.title;
        return element;
    };
    return TextInput;
}(Input));
var Choice = (function () {
    function Choice() {
    }
    Choice.prototype.parse = function (json) {
        this.display = json["display"];
        this.value = json["value"];
    };
    return Choice;
}());
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
        selectElement.className = "input multichoiceInput";
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
        container.className = "input";
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
            this._card.topSpacing = Spacing.None;
            this._card.parse(json["card"]);
        }
        if (json["inputs"] != undefined) {
            var inputArray = json["inputs"];
            for (var i = 0; i < inputArray.length; i++) {
                var input = Input.createInput(this.owner.container, inputArray[i]["@type"]);
                if (i == 0) {
                    input.topSpacing = Spacing.None;
                }
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
                if (i > 0) {
                    inputElement.style.marginTop = "10px";
                }
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
var ActionButtonStyle;
(function (ActionButtonStyle) {
    ActionButtonStyle[ActionButtonStyle["Link"] = 0] = "Link";
    ActionButtonStyle[ActionButtonStyle["Push"] = 1] = "Push";
})(ActionButtonStyle || (ActionButtonStyle = {}));
var ActionButtonState;
(function (ActionButtonState) {
    ActionButtonState[ActionButtonState["Normal"] = 0] = "Normal";
    ActionButtonState[ActionButtonState["Expanded"] = 1] = "Expanded";
    ActionButtonState[ActionButtonState["Subdued"] = 2] = "Subdued";
})(ActionButtonState || (ActionButtonState = {}));
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
                if (i < this._actions.length - 1) {
                    buttonStripItem.style.marginRight = "20px";
                }
                var actionButton = new ActionButton(this._actions[i], ActionButtonStyle.Link);
                actionButton.text = this._actions[i].name;
                actionButton.onClick.subscribe(function (ab, args) {
                    _this.actionClicked(ab);
                });
                this._actionButtons.push(actionButton);
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
    return ActionGroup;
}(CardElement));
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
            this._element.className = "container";
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
var Column = (function (_super) {
    __extends(Column, _super);
    function Column() {
        _super.apply(this, arguments);
        this._useWeight = false;
        this._weight = 100;
    }
    Column.prototype.parse = function (json) {
        _super.prototype.parse.call(this, json);
        this.size = Size.parse(json["size"], undefined);
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
                case Size.Auto:
                    element.style.flex = "0 0 auto";
                    break;
                case Size.Stretch:
                    element.style.flex = "1 1 auto";
                    break;
                default:
                    element.style.flex = "0 0 " + this.size.physicalSize + "px";
                    break;
            }
        }
    };
    return Column;
}(Container));
var ColumnGroup = (function (_super) {
    __extends(ColumnGroup, _super);
    function ColumnGroup() {
        _super.apply(this, arguments);
        this._items = [];
    }
    ColumnGroup.prototype.addColumn = function () {
        var column = new Column(this.container, ["ColumnGroup", "ActionGroup"]);
        column.topSpacing = Spacing.None;
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
//# sourceMappingURL=adaptiveCard.js.map
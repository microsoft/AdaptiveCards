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
var Enums = require("./enums");
var Utils = require("./utils");
var HostConfig = require("./host-config");
var TextFormatters = require("./text-formatters");
function invokeSetParent(obj, parent) {
    if (obj) {
        // Closest emulation of "internal" in TypeScript.
        obj["setParent"](parent);
    }
}
function invokeSetCollection(action, collection) {
    if (action) {
        // Closest emulation of "internal" in TypeScript.
        action["setCollection"](collection);
    }
}
function isActionAllowed(action, forbiddenActionTypes) {
    if (forbiddenActionTypes) {
        for (var i = 0; i < forbiddenActionTypes.length; i++) {
            if (action.getJsonTypeName() === forbiddenActionTypes[i]) {
                return false;
            }
        }
    }
    return true;
}
function createActionInstance(json) {
    var actionType = json["type"];
    var result = AdaptiveCard.actionTypeRegistry.createInstance(actionType);
    if (result) {
        result.parse(json);
    }
    else {
        raiseParseError({
            error: Enums.ValidationError.UnknownActionType,
            message: "Unknown action type: " + actionType
        });
    }
    return result;
}
var CardElement = /** @class */ (function () {
    function CardElement() {
        this._internalPadding = null;
        this._parent = null;
        this._isVisibile = true;
        this._renderedElement = null;
        this._separatorElement = null;
        this.horizontalAlignment = null;
        this.spacing = Enums.Spacing.Default;
        this.separator = false;
        this.height = "auto";
    }
    CardElement.prototype.internalRenderSeparator = function () {
        return Utils.renderSeparation({
            spacing: this.hostConfig.getEffectiveSpacing(this.spacing),
            lineThickness: this.separator ? this.hostConfig.separator.lineThickness : null,
            lineColor: this.separator ? this.hostConfig.separator.lineColor : null
        }, this.separatorOrientation);
    };
    CardElement.prototype.updateRenderedElementVisibility = function () {
        if (this._renderedElement) {
            this._renderedElement.style.visibility = this._isVisibile ? null : "collapse";
        }
        if (this._separatorElement) {
            this._separatorElement.style.visibility = this._isVisibile ? null : "collapse";
        }
    };
    CardElement.prototype.internalGetNonZeroPadding = function (padding) {
        if (padding.top == Enums.Padding.None) {
            padding.top = this.internalPadding.top;
        }
        if (padding.right == Enums.Padding.None) {
            padding.right = this.internalPadding.right;
        }
        if (padding.bottom == Enums.Padding.None) {
            padding.bottom = this.internalPadding.bottom;
        }
        if (padding.left == Enums.Padding.None) {
            padding.left = this.internalPadding.left;
        }
        if (this.parent) {
            this.parent.internalGetNonZeroPadding(padding);
        }
    };
    CardElement.prototype.adjustRenderedElementSize = function (renderedElement) {
        if (this.height === "auto") {
            renderedElement.style.flex = "0 0 auto";
        }
        else {
            renderedElement.style.flex = "1 1 100%";
        }
    };
    CardElement.prototype.showBottomSpacer = function (requestingElement) {
        if (this.parent) {
            this.parent.showBottomSpacer(requestingElement);
        }
    };
    CardElement.prototype.hideBottomSpacer = function (requestingElement) {
        if (this.parent) {
            this.parent.hideBottomSpacer(requestingElement);
        }
    };
    CardElement.prototype.setParent = function (value) {
        this._parent = value;
    };
    Object.defineProperty(CardElement.prototype, "useDefaultSizing", {
        get: function () {
            return true;
        },
        enumerable: true,
        configurable: true
    });
    Object.defineProperty(CardElement.prototype, "allowCustomPadding", {
        get: function () {
            return true;
        },
        enumerable: true,
        configurable: true
    });
    Object.defineProperty(CardElement.prototype, "defaultPadding", {
        get: function () {
            return new HostConfig.PaddingDefinition({
                top: Enums.Padding.None,
                right: Enums.Padding.None,
                bottom: Enums.Padding.None,
                left: Enums.Padding.None
            });
        },
        enumerable: true,
        configurable: true
    });
    Object.defineProperty(CardElement.prototype, "internalPadding", {
        get: function () {
            return (this._internalPadding && this.allowCustomPadding) ? this._internalPadding : this.defaultPadding;
        },
        set: function (value) {
            this._internalPadding = value;
        },
        enumerable: true,
        configurable: true
    });
    Object.defineProperty(CardElement.prototype, "separatorOrientation", {
        get: function () {
            return Enums.Orientation.Horizontal;
        },
        enumerable: true,
        configurable: true
    });
    CardElement.prototype.getNonZeroPadding = function () {
        var padding = new HostConfig.PaddingDefinition({
            top: Enums.Padding.None,
            right: Enums.Padding.None,
            bottom: Enums.Padding.None,
            left: Enums.Padding.None
        });
        this.internalGetNonZeroPadding(padding);
        return padding;
    };
    CardElement.prototype.getForbiddenElementTypes = function () {
        return null;
    };
    CardElement.prototype.getForbiddenActionTypes = function () {
        return null;
    };
    CardElement.prototype.parse = function (json) {
        raiseParseElementEvent(this, json);
        this.id = json["id"];
        this.speak = json["speak"];
        this.horizontalAlignment = Utils.getEnumValueOrDefault(Enums.HorizontalAlignment, json["horizontalAlignment"], null);
        this.spacing = Utils.getEnumValueOrDefault(Enums.Spacing, json["spacing"], Enums.Spacing.Default);
        this.separator = json["separator"];
        var jsonSeparation = json["separation"];
        if (jsonSeparation !== undefined) {
            if (jsonSeparation === "none") {
                this.spacing = Enums.Spacing.None;
                this.separator = false;
            }
            else if (jsonSeparation === "strong") {
                this.spacing = Enums.Spacing.Large;
                this.separator = true;
            }
            else if (jsonSeparation === "default") {
                this.spacing = Enums.Spacing.Default;
                this.separator = false;
            }
            raiseParseError({
                error: Enums.ValidationError.Deprecated,
                message: "The \"separation\" property is deprecated and will be removed. Use the \"spacing\" and \"separator\" properties instead."
            });
        }
        var jsonHeight = json["height"];
        if (jsonHeight === "auto" || jsonHeight === "stretch") {
            this.height = jsonHeight;
        }
    };
    CardElement.prototype.validate = function () {
        return [];
    };
    CardElement.prototype.render = function () {
        this._renderedElement = this.internalRender();
        this._separatorElement = this.internalRenderSeparator();
        if (this._renderedElement) {
            this._renderedElement.style.boxSizing = "border-box";
            this.adjustRenderedElementSize(this._renderedElement);
            this.updateLayout(false);
            this.updateRenderedElementVisibility();
        }
        return this._renderedElement;
    };
    CardElement.prototype.updateLayout = function (processChildren) {
        if (processChildren === void 0) { processChildren = true; }
        // Does nothing in base implementation
    };
    CardElement.prototype.isAtTheVeryTop = function () {
        return this.parent ? this.parent.isFirstElement(this) && this.parent.isAtTheVeryTop() : true;
    };
    CardElement.prototype.isFirstElement = function (element) {
        return true;
    };
    CardElement.prototype.isAtTheVeryBottom = function () {
        return this.parent ? this.parent.isLastElement(this) && this.parent.isAtTheVeryBottom() : true;
    };
    CardElement.prototype.isLastElement = function (element) {
        return true;
    };
    CardElement.prototype.isAtTheVeryLeft = function () {
        return this.parent ? this.parent.isLeftMostElement(this) && this.parent.isAtTheVeryLeft() : true;
    };
    CardElement.prototype.isLeftMostElement = function (element) {
        return true;
    };
    CardElement.prototype.isAtTheVeryRight = function () {
        return this.parent ? this.parent.isRightMostElement(this) && this.parent.isAtTheVeryRight() : true;
    };
    CardElement.prototype.isRightMostElement = function (element) {
        return true;
    };
    CardElement.prototype.canContentBleed = function () {
        return this.parent ? this.parent.canContentBleed() : true;
    };
    CardElement.prototype.getRootElement = function () {
        var rootElement = this;
        while (rootElement.parent) {
            rootElement = rootElement.parent;
        }
        return rootElement;
    };
    CardElement.prototype.getParentContainer = function () {
        var currentElement = this.parent;
        while (currentElement) {
            if (currentElement instanceof Container) {
                return currentElement;
            }
            currentElement = currentElement.parent;
        }
        return null;
    };
    CardElement.prototype.getAllInputs = function () {
        return [];
    };
    CardElement.prototype.getElementById = function (id) {
        return this.id === id ? this : null;
    };
    CardElement.prototype.getActionById = function (id) {
        return null;
    };
    Object.defineProperty(CardElement.prototype, "hostConfig", {
        get: function () {
            if (!this._hostConfig) {
                var result = this.parent.hostConfig;
                this._hostConfig = result ? result : defaultHostConfig;
            }
            return this._hostConfig;
        },
        set: function (value) {
            this._hostConfig = value;
        },
        enumerable: true,
        configurable: true
    });
    Object.defineProperty(CardElement.prototype, "isInteractive", {
        get: function () {
            return false;
        },
        enumerable: true,
        configurable: true
    });
    Object.defineProperty(CardElement.prototype, "isStandalone", {
        get: function () {
            return true;
        },
        enumerable: true,
        configurable: true
    });
    Object.defineProperty(CardElement.prototype, "parent", {
        get: function () {
            return this._parent;
        },
        enumerable: true,
        configurable: true
    });
    Object.defineProperty(CardElement.prototype, "isVisible", {
        get: function () {
            return this._isVisibile;
        },
        set: function (value) {
            if (this._isVisibile != value) {
                this._isVisibile = value;
                this.updateRenderedElementVisibility();
                if (this._renderedElement) {
                    raiseElementVisibilityChangedEvent(this);
                }
            }
        },
        enumerable: true,
        configurable: true
    });
    Object.defineProperty(CardElement.prototype, "renderedElement", {
        get: function () {
            return this._renderedElement;
        },
        enumerable: true,
        configurable: true
    });
    Object.defineProperty(CardElement.prototype, "separatorElement", {
        get: function () {
            return this._separatorElement;
        },
        enumerable: true,
        configurable: true
    });
    return CardElement;
}());
exports.CardElement = CardElement;
var TextBlock = /** @class */ (function (_super) {
    __extends(TextBlock, _super);
    function TextBlock() {
        var _this = _super !== null && _super.apply(this, arguments) || this;
        _this.size = Enums.TextSize.Default;
        _this.weight = Enums.TextWeight.Default;
        _this.color = Enums.TextColor.Default;
        _this.isSubtle = false;
        _this.wrap = false;
        return _this;
    }
    TextBlock.prototype.internalRender = function () {
        if (!Utils.isNullOrEmpty(this.text)) {
            var element = document.createElement("div");
            element.style.overflow = "hidden";
            if (this.hostConfig.fontFamily) {
                element.style.fontFamily = this.hostConfig.fontFamily;
            }
            switch (this.horizontalAlignment) {
                case Enums.HorizontalAlignment.Center:
                    element.style.textAlign = "center";
                    break;
                case Enums.HorizontalAlignment.Right:
                    element.style.textAlign = "right";
                    break;
                default:
                    element.style.textAlign = "left";
                    break;
            }
            var cssStyle = "text ";
            var fontSize;
            switch (this.size) {
                case Enums.TextSize.Small:
                    fontSize = this.hostConfig.fontSizes.small;
                    break;
                case Enums.TextSize.Medium:
                    fontSize = this.hostConfig.fontSizes.medium;
                    break;
                case Enums.TextSize.Large:
                    fontSize = this.hostConfig.fontSizes.large;
                    break;
                case Enums.TextSize.ExtraLarge:
                    fontSize = this.hostConfig.fontSizes.extraLarge;
                    break;
                default:
                    fontSize = this.hostConfig.fontSizes.default;
                    break;
            }
            // Looks like 1.33 is the magic number to compute line-height
            // from font size.
            var computedLineHeight = fontSize * 1.33;
            element.style.fontSize = fontSize + "px";
            element.style.lineHeight = computedLineHeight + "px";
            var parentContainer = this.getParentContainer();
            var styleDefinition = this.hostConfig.getContainerStyleDefinition(parentContainer ? parentContainer.style : Enums.ContainerStyle.Default);
            var actualTextColor = this.color ? this.color : Enums.TextColor.Default;
            var colorDefinition;
            switch (actualTextColor) {
                case Enums.TextColor.Accent:
                    colorDefinition = styleDefinition.fontColors.accent;
                    break;
                case Enums.TextColor.Good:
                    colorDefinition = styleDefinition.fontColors.good;
                    break;
                case Enums.TextColor.Warning:
                    colorDefinition = styleDefinition.fontColors.warning;
                    break;
                case Enums.TextColor.Attention:
                    colorDefinition = styleDefinition.fontColors.attention;
                    break;
                default:
                    colorDefinition = styleDefinition.fontColors.default;
                    break;
            }
            element.style.color = Utils.stringToCssColor(this.isSubtle ? colorDefinition.subtle : colorDefinition.normal);
            var fontWeight;
            switch (this.weight) {
                case Enums.TextWeight.Lighter:
                    fontWeight = this.hostConfig.fontWeights.lighter;
                    break;
                case Enums.TextWeight.Bolder:
                    fontWeight = this.hostConfig.fontWeights.bolder;
                    break;
                default:
                    fontWeight = this.hostConfig.fontWeights.default;
                    break;
            }
            element.style.fontWeight = fontWeight.toString();
            var formattedText = TextFormatters.formatText(this.text);
            element.innerHTML = Utils.processMarkdown(formattedText);
            if (element.firstElementChild instanceof HTMLElement) {
                var firstElementChild = element.firstElementChild;
                firstElementChild.style.marginTop = "0px";
                firstElementChild.style.width = "100%";
                if (!this.wrap) {
                    firstElementChild.style.overflow = "hidden";
                    firstElementChild.style.textOverflow = "ellipsis";
                }
            }
            if (element.lastElementChild instanceof HTMLElement) {
                element.lastElementChild.style.marginBottom = "0px";
            }
            var anchors = element.getElementsByTagName("a");
            for (var i = 0; i < anchors.length; i++) {
                var anchor = anchors[i];
                anchor.classList.add("ac-anchor");
                anchor.target = "_blank";
                anchor.onclick = function (e) {
                    if (raiseAnchorClickedEvent(anchor)) {
                        e.preventDefault();
                    }
                };
            }
            if (this.wrap) {
                element.style.wordWrap = "break-word";
                if (this.maxLines > 0) {
                    element.style.maxHeight = (computedLineHeight * this.maxLines) + "px";
                    element.style.overflow = "hidden";
                }
            }
            else {
                element.style.whiteSpace = "nowrap";
            }
            return element;
        }
        else {
            return null;
        }
    };
    TextBlock.prototype.parse = function (json) {
        _super.prototype.parse.call(this, json);
        this.text = json["text"];
        var sizeString = json["size"];
        if (sizeString && typeof sizeString === "string" && sizeString.toLowerCase() === "normal") {
            this.size = Enums.TextSize.Default;
            raiseParseError({
                error: Enums.ValidationError.Deprecated,
                message: "The TextBlock.size value \"normal\" is deprecated and will be removed. Use \"default\" instead."
            });
        }
        else {
            this.size = Utils.getEnumValueOrDefault(Enums.TextSize, sizeString, this.size);
        }
        var weightString = json["weight"];
        if (weightString && typeof weightString === "string" && weightString.toLowerCase() === "normal") {
            this.weight = Enums.TextWeight.Default;
            raiseParseError({
                error: Enums.ValidationError.Deprecated,
                message: "The TextBlock.weight value \"normal\" is deprecated and will be removed. Use \"default\" instead."
            });
        }
        else {
            this.weight = Utils.getEnumValueOrDefault(Enums.TextWeight, weightString, this.weight);
        }
        this.color = Utils.getEnumValueOrDefault(Enums.TextColor, json["color"], this.color);
        this.isSubtle = json["isSubtle"];
        this.wrap = json["wrap"] === undefined ? false : json["wrap"];
        this.maxLines = json["maxLines"];
    };
    TextBlock.prototype.getJsonTypeName = function () {
        return "TextBlock";
    };
    TextBlock.prototype.renderSpeech = function () {
        if (this.speak != null)
            return this.speak + '\n';
        if (this.text)
            return '<s>' + this.text + '</s>\n';
        return null;
    };
    return TextBlock;
}(CardElement));
exports.TextBlock = TextBlock;
var Fact = /** @class */ (function () {
    function Fact() {
    }
    Fact.prototype.renderSpeech = function () {
        if (this.speak != null) {
            return this.speak + '\n';
        }
        return '<s>' + this.name + ' ' + this.value + '</s>\n';
    };
    return Fact;
}());
exports.Fact = Fact;
var FactSet = /** @class */ (function (_super) {
    __extends(FactSet, _super);
    function FactSet() {
        var _this = _super !== null && _super.apply(this, arguments) || this;
        _this.facts = [];
        return _this;
    }
    Object.defineProperty(FactSet.prototype, "useDefaultSizing", {
        get: function () {
            return false;
        },
        enumerable: true,
        configurable: true
    });
    FactSet.prototype.internalRender = function () {
        var element = null;
        if (this.facts.length > 0) {
            element = document.createElement("table");
            element.style.borderWidth = "0px";
            element.style.borderSpacing = "0px";
            element.style.borderStyle = "none";
            element.style.borderCollapse = "collapse";
            element.style.display = "block";
            element.style.overflow = "hidden";
            for (var i = 0; i < this.facts.length; i++) {
                var trElement = document.createElement("tr");
                if (i > 0) {
                    trElement.style.marginTop = this.hostConfig.factSet.spacing + "px";
                }
                var tdElement = document.createElement("td");
                tdElement.style.padding = "0";
                if (this.hostConfig.factSet.title.maxWidth) {
                    tdElement.style.maxWidth = this.hostConfig.factSet.title.maxWidth + "px";
                }
                tdElement.style.verticalAlign = "top";
                var textBlock = new TextBlock();
                textBlock.hostConfig = this.hostConfig;
                textBlock.text = this.facts[i].name;
                textBlock.size = this.hostConfig.factSet.title.size;
                textBlock.color = this.hostConfig.factSet.title.color;
                textBlock.isSubtle = this.hostConfig.factSet.title.isSubtle;
                textBlock.weight = this.hostConfig.factSet.title.weight;
                textBlock.wrap = this.hostConfig.factSet.title.wrap;
                textBlock.spacing = Enums.Spacing.None;
                Utils.appendChild(tdElement, textBlock.render());
                Utils.appendChild(trElement, tdElement);
                tdElement = document.createElement("td");
                tdElement.style.padding = "0px 0px 0px 10px";
                tdElement.style.verticalAlign = "top";
                textBlock = new TextBlock();
                textBlock.hostConfig = this.hostConfig;
                textBlock.text = this.facts[i].value;
                textBlock.size = this.hostConfig.factSet.value.size;
                textBlock.color = this.hostConfig.factSet.value.color;
                textBlock.isSubtle = this.hostConfig.factSet.value.isSubtle;
                textBlock.weight = this.hostConfig.factSet.value.weight;
                textBlock.wrap = this.hostConfig.factSet.value.wrap;
                textBlock.spacing = Enums.Spacing.None;
                Utils.appendChild(tdElement, textBlock.render());
                Utils.appendChild(trElement, tdElement);
                Utils.appendChild(element, trElement);
            }
        }
        return element;
    };
    FactSet.prototype.getJsonTypeName = function () {
        return "FactSet";
    };
    FactSet.prototype.parse = function (json) {
        _super.prototype.parse.call(this, json);
        if (json["facts"] != null) {
            var jsonFacts = json["facts"];
            for (var i = 0; i < jsonFacts.length; i++) {
                var fact = new Fact();
                fact.name = jsonFacts[i]["title"];
                fact.value = jsonFacts[i]["value"];
                fact.speak = jsonFacts[i]["speak"];
                this.facts.push(fact);
            }
        }
    };
    FactSet.prototype.renderSpeech = function () {
        if (this.speak != null) {
            return this.speak + '\n';
        }
        // render each fact
        var speak = null;
        if (this.facts.length > 0) {
            speak = '';
            for (var i = 0; i < this.facts.length; i++) {
                var speech = this.facts[i].renderSpeech();
                if (speech) {
                    speak += speech;
                }
            }
        }
        return '<p>' + speak + '\n</p>\n';
    };
    return FactSet;
}(CardElement));
exports.FactSet = FactSet;
var Image = /** @class */ (function (_super) {
    __extends(Image, _super);
    function Image() {
        var _this = _super !== null && _super.apply(this, arguments) || this;
        _this.style = Enums.ImageStyle.Default;
        _this.size = Enums.Size.Auto;
        _this.pixelWidth = null;
        _this.pixelHeight = null;
        _this.altText = "";
        return _this;
    }
    Object.defineProperty(Image.prototype, "useDefaultSizing", {
        get: function () {
            return false;
        },
        enumerable: true,
        configurable: true
    });
    Image.prototype.internalRender = function () {
        var _this = this;
        var element = null;
        if (!Utils.isNullOrEmpty(this.url)) {
            element = document.createElement("div");
            element.classList.add("ac-image");
            element.style.display = "flex";
            element.style.alignItems = "flex-start";
            if (this.selectAction != null) {
                element.tabIndex = 0;
                element.setAttribute("role", "button");
                element.setAttribute("aria-label", this.selectAction.title);
                element.classList.add("ac-selectable");
            }
            element.onkeypress = function (e) {
                if (_this.selectAction) {
                    if (e.keyCode == 13 || e.keyCode == 32) {
                        _this.selectAction.execute();
                    }
                }
            };
            element.onclick = function (e) {
                if (_this.selectAction) {
                    _this.selectAction.execute();
                    e.cancelBubble = true;
                }
            };
            switch (this.horizontalAlignment) {
                case Enums.HorizontalAlignment.Center:
                    element.style.justifyContent = "center";
                    break;
                case Enums.HorizontalAlignment.Right:
                    element.style.justifyContent = "flex-end";
                    break;
                default:
                    element.style.justifyContent = "flex-start";
                    break;
            }
            var imageElement = document.createElement("img");
            imageElement.style.maxHeight = "100%";
            imageElement.style.minWidth = "0";
            if (this.pixelWidth || this.pixelHeight) {
                if (this.pixelWidth) {
                    imageElement.style.width = this.pixelWidth + "px";
                }
                if (this.pixelHeight) {
                    imageElement.style.height = this.pixelHeight + "px";
                }
            }
            else {
                switch (this.size) {
                    case Enums.Size.Stretch:
                        imageElement.style.width = "100%";
                        break;
                    case Enums.Size.Auto:
                        imageElement.style.maxWidth = "100%";
                        break;
                    case Enums.Size.Small:
                        imageElement.style.width = this.hostConfig.imageSizes.small + "px";
                        break;
                    case Enums.Size.Large:
                        imageElement.style.width = this.hostConfig.imageSizes.large + "px";
                        break;
                    case Enums.Size.Medium:
                        imageElement.style.width = this.hostConfig.imageSizes.medium + "px";
                        break;
                }
            }
            if (this.style === Enums.ImageStyle.Person) {
                imageElement.style.borderRadius = "50%";
                imageElement.style.backgroundPosition = "50% 50%";
                imageElement.style.backgroundRepeat = "no-repeat";
            }
            imageElement.src = this.url;
            imageElement.alt = this.altText;
            element.appendChild(imageElement);
        }
        return element;
    };
    Image.prototype.getJsonTypeName = function () {
        return "Image";
    };
    Image.prototype.getActionById = function (id) {
        var result = _super.prototype.getActionById.call(this, id);
        if (!result && this.selectAction) {
            result = this.selectAction.getActionById(id);
        }
        return result;
    };
    Image.prototype.parse = function (json) {
        _super.prototype.parse.call(this, json);
        this.url = json["url"];
        var styleString = json["style"];
        if (styleString && typeof styleString === "string" && styleString.toLowerCase() === "normal") {
            this.style = Enums.ImageStyle.Default;
            raiseParseError({
                error: Enums.ValidationError.Deprecated,
                message: "The Image.style value \"normal\" is deprecated and will be removed. Use \"default\" instead."
            });
        }
        else {
            this.style = Utils.getEnumValueOrDefault(Enums.ImageStyle, styleString, this.style);
        }
        this.size = Utils.getEnumValueOrDefault(Enums.Size, json["size"], this.size);
        this.altText = json["altText"];
        var selectActionJson = json["selectAction"];
        if (selectActionJson != undefined) {
            this.selectAction = createActionInstance(selectActionJson);
        }
        if (json["pixelWidth"] && typeof json["pixelWidth"] === "number") {
            this.pixelWidth = json["pixelWidth"];
        }
        if (json["pixelHeight"] && typeof json["pixelHeight"] === "number") {
            this.pixelHeight = json["pixelHeight"];
        }
    };
    Image.prototype.renderSpeech = function () {
        if (this.speak != null) {
            return this.speak + '\n';
        }
        return null;
    };
    Object.defineProperty(Image.prototype, "selectAction", {
        get: function () {
            return this._selectAction;
        },
        set: function (value) {
            this._selectAction = value;
            if (this._selectAction) {
                invokeSetParent(this._selectAction, this);
            }
        },
        enumerable: true,
        configurable: true
    });
    return Image;
}(CardElement));
exports.Image = Image;
var ImageSet = /** @class */ (function (_super) {
    __extends(ImageSet, _super);
    function ImageSet() {
        var _this = _super !== null && _super.apply(this, arguments) || this;
        _this._images = [];
        _this.imageSize = Enums.Size.Medium;
        return _this;
    }
    ImageSet.prototype.internalRender = function () {
        var element = null;
        if (this._images.length > 0) {
            element = document.createElement("div");
            element.style.display = "flex";
            element.style.flexWrap = "wrap";
            for (var i = 0; i < this._images.length; i++) {
                var renderedImage = this._images[i].render();
                renderedImage.style.display = "inline-flex";
                renderedImage.style.margin = "0px";
                renderedImage.style.marginRight = "10px";
                renderedImage.style.maxHeight = this.hostConfig.imageSet.maxImageHeight + "px";
                Utils.appendChild(element, renderedImage);
            }
        }
        return element;
    };
    ImageSet.prototype.getJsonTypeName = function () {
        return "ImageSet";
    };
    ImageSet.prototype.parse = function (json) {
        _super.prototype.parse.call(this, json);
        //this.imageSize = Utils.getValueOrDefault<Enums.Size>(json["imageSize"], Enums.Size.medium);
        this.imageSize = Utils.getEnumValueOrDefault(Enums.Size, json["imageSize"], Enums.Size.Medium);
        if (json["images"] != null) {
            var jsonImages = json["images"];
            for (var i = 0; i < jsonImages.length; i++) {
                var image = new Image();
                image.parse(jsonImages[i]);
                image.size = this.imageSize;
                this.addImage(image);
            }
        }
    };
    ImageSet.prototype.addImage = function (image) {
        if (!image.parent) {
            this._images.push(image);
            invokeSetParent(image, this);
        }
        else {
            throw new Error("This image already belongs to another ImageSet");
        }
    };
    ImageSet.prototype.renderSpeech = function () {
        if (this.speak != null) {
            return this.speak;
        }
        var speak = null;
        if (this._images.length > 0) {
            speak = '';
            for (var i = 0; i < this._images.length; i++) {
                speak += this._images[i].renderSpeech();
            }
        }
        return speak;
    };
    return ImageSet;
}(CardElement));
exports.ImageSet = ImageSet;
var Input = /** @class */ (function (_super) {
    __extends(Input, _super);
    function Input() {
        return _super !== null && _super.apply(this, arguments) || this;
    }
    Input.prototype.validate = function () {
        if (!this.id) {
            return [{ error: Enums.ValidationError.PropertyCantBeNull, message: "All inputs must have a unique Id" }];
        }
        else {
            return [];
        }
    };
    Input.prototype.parse = function (json) {
        _super.prototype.parse.call(this, json);
        this.id = json["id"];
        this.defaultValue = json["value"];
    };
    Input.prototype.renderSpeech = function () {
        if (this.speak != null) {
            return this.speak;
        }
        if (this.title) {
            return '<s>' + this.title + '</s>\n';
        }
        return null;
    };
    Input.prototype.getAllInputs = function () {
        return [this];
    };
    Object.defineProperty(Input.prototype, "isInteractive", {
        get: function () {
            return true;
        },
        enumerable: true,
        configurable: true
    });
    return Input;
}(CardElement));
exports.Input = Input;
var TextInput = /** @class */ (function (_super) {
    __extends(TextInput, _super);
    function TextInput() {
        return _super !== null && _super.apply(this, arguments) || this;
    }
    TextInput.prototype.internalRender = function () {
        if (this.isMultiline) {
            this._textareaElement = document.createElement("textarea");
            this._textareaElement.className = "ac-input ac-textInput ac-multiline";
            this._textareaElement.style.width = "100%";
            this._textareaElement.tabIndex = 0;
            if (!Utils.isNullOrEmpty(this.placeholder)) {
                this._textareaElement.placeholder = this.placeholder;
                this._textareaElement.setAttribute("aria-label", this.placeholder);
            }
            if (!Utils.isNullOrEmpty(this.defaultValue)) {
                this._textareaElement.value = this.defaultValue;
            }
            if (this.maxLength > 0) {
                this._textareaElement.maxLength = this.maxLength;
            }
            return this._textareaElement;
        }
        else {
            this._inputElement = document.createElement("input");
            this._inputElement.type = "text";
            this._inputElement.className = "ac-input ac-textInput";
            this._inputElement.style.width = "100%";
            this._inputElement.tabIndex = 0;
            if (!Utils.isNullOrEmpty(this.placeholder)) {
                this._inputElement.placeholder = this.placeholder;
                this._inputElement.setAttribute("aria-label", this.placeholder);
            }
            if (!Utils.isNullOrEmpty(this.defaultValue)) {
                this._inputElement.value = this.defaultValue;
            }
            if (this.maxLength > 0) {
                this._inputElement.maxLength = this.maxLength;
            }
            return this._inputElement;
        }
    };
    TextInput.prototype.getJsonTypeName = function () {
        return "Input.Text";
    };
    TextInput.prototype.parse = function (json) {
        _super.prototype.parse.call(this, json);
        this.maxLength = json["maxLength"];
        this.isMultiline = json["isMultiline"];
        this.placeholder = json["placeholder"];
    };
    Object.defineProperty(TextInput.prototype, "value", {
        get: function () {
            if (this.isMultiline) {
                return this._textareaElement ? this._textareaElement.value : null;
            }
            else {
                return this._inputElement ? this._inputElement.value : null;
            }
        },
        enumerable: true,
        configurable: true
    });
    return TextInput;
}(Input));
exports.TextInput = TextInput;
var ToggleInput = /** @class */ (function (_super) {
    __extends(ToggleInput, _super);
    function ToggleInput() {
        var _this = _super !== null && _super.apply(this, arguments) || this;
        _this.valueOn = "true";
        _this.valueOff = "false";
        return _this;
    }
    ToggleInput.prototype.internalRender = function () {
        var element = document.createElement("div");
        element.className = "ac-input";
        element.style.width = "100%";
        element.style.display = "flex";
        this._checkboxInputElement = document.createElement("input");
        this._checkboxInputElement.type = "checkbox";
        this._checkboxInputElement.style.display = "inline-block";
        this._checkboxInputElement.style.verticalAlign = "middle";
        this._checkboxInputElement.style.margin = "0";
        this._checkboxInputElement.style.flex = "0 0 auto";
        this._checkboxInputElement.setAttribute("aria-label", this.title);
        this._checkboxInputElement.tabIndex = 0;
        if (this.defaultValue == this.valueOn) {
            this._checkboxInputElement.checked = true;
        }
        var label = new TextBlock();
        label.hostConfig = this.hostConfig;
        label.text = this.title;
        var labelElement = label.render();
        labelElement.style.display = "inline-block";
        labelElement.style.marginLeft = "6px";
        labelElement.style.verticalAlign = "middle";
        var compoundInput = document.createElement("div");
        Utils.appendChild(element, this._checkboxInputElement);
        Utils.appendChild(element, labelElement);
        return element;
    };
    ToggleInput.prototype.getJsonTypeName = function () {
        return "Input.Toggle";
    };
    ToggleInput.prototype.parse = function (json) {
        _super.prototype.parse.call(this, json);
        this.title = json["title"];
        this.valueOn = Utils.getValueOrDefault(json["valueOn"], this.valueOn);
        this.valueOff = Utils.getValueOrDefault(json["valueOff"], this.valueOff);
    };
    Object.defineProperty(ToggleInput.prototype, "value", {
        get: function () {
            if (this._checkboxInputElement) {
                return this._checkboxInputElement.checked ? this.valueOn : this.valueOff;
            }
            else {
                return null;
            }
        },
        enumerable: true,
        configurable: true
    });
    return ToggleInput;
}(Input));
exports.ToggleInput = ToggleInput;
var Choice = /** @class */ (function () {
    function Choice() {
    }
    return Choice;
}());
exports.Choice = Choice;
var ChoiceSetInput = /** @class */ (function (_super) {
    __extends(ChoiceSetInput, _super);
    function ChoiceSetInput() {
        var _this = _super !== null && _super.apply(this, arguments) || this;
        _this.choices = [];
        return _this;
    }
    ChoiceSetInput.prototype.internalRender = function () {
        if (!this.isMultiSelect) {
            if (this.isCompact) {
                // Render as a combo box
                this._selectElement = document.createElement("select");
                this._selectElement.className = "ac-input ac-multichoiceInput";
                this._selectElement.style.width = "100%";
                var option = document.createElement("option");
                option.selected = true;
                option.disabled = true;
                option.hidden = true;
                if (this.placeholder) {
                    option.text = this.placeholder;
                }
                Utils.appendChild(this._selectElement, option);
                for (var i = 0; i < this.choices.length; i++) {
                    var option = document.createElement("option");
                    option.value = this.choices[i].value;
                    option.text = this.choices[i].title;
                    option.setAttribute("aria-label", this.choices[i].title);
                    if (this.choices[i].value == this.defaultValue) {
                        option.selected = true;
                    }
                    Utils.appendChild(this._selectElement, option);
                }
                return this._selectElement;
            }
            else {
                // Render as a series of radio buttons
                var element = document.createElement("div");
                element.className = "ac-input";
                element.style.width = "100%";
                this._toggleInputs = [];
                for (var i = 0; i < this.choices.length; i++) {
                    var radioInput = document.createElement("input");
                    radioInput.type = "radio";
                    radioInput.style.margin = "0";
                    radioInput.style.display = "inline-block";
                    radioInput.style.verticalAlign = "middle";
                    radioInput.name = this.id;
                    radioInput.value = this.choices[i].value;
                    radioInput.style.flex = "0 0 auto";
                    radioInput.setAttribute("aria-label", this.choices[i].title);
                    if (this.choices[i].value == this.defaultValue) {
                        radioInput.checked = true;
                    }
                    this._toggleInputs.push(radioInput);
                    var label = new TextBlock();
                    label.hostConfig = this.hostConfig;
                    label.text = this.choices[i].title;
                    var labelElement = label.render();
                    labelElement.style.display = "inline-block";
                    labelElement.style.marginLeft = "6px";
                    labelElement.style.verticalAlign = "middle";
                    var compoundInput = document.createElement("div");
                    compoundInput.style.display = "flex";
                    Utils.appendChild(compoundInput, radioInput);
                    Utils.appendChild(compoundInput, labelElement);
                    Utils.appendChild(element, compoundInput);
                }
                return element;
            }
        }
        else {
            // Render as a list of toggle inputs
            var defaultValues = this.defaultValue ? this.defaultValue.split(",") : null;
            var element = document.createElement("div");
            element.className = "ac-input";
            element.style.width = "100%";
            this._toggleInputs = [];
            for (var i = 0; i < this.choices.length; i++) {
                var checkboxInput = document.createElement("input");
                checkboxInput.type = "checkbox";
                checkboxInput.style.margin = "0";
                checkboxInput.style.display = "inline-block";
                checkboxInput.style.verticalAlign = "middle";
                checkboxInput.value = this.choices[i].value;
                checkboxInput.style.flex = "0 0 auto";
                checkboxInput.setAttribute("aria-label", this.choices[i].title);
                if (defaultValues) {
                    if (defaultValues.indexOf(this.choices[i].value) >= 0) {
                        checkboxInput.checked = true;
                    }
                }
                this._toggleInputs.push(checkboxInput);
                var label = new TextBlock();
                label.hostConfig = this.hostConfig;
                label.text = this.choices[i].title;
                var labelElement = label.render();
                labelElement.style.display = "inline-block";
                labelElement.style.marginLeft = "6px";
                labelElement.style.verticalAlign = "middle";
                var compoundInput = document.createElement("div");
                compoundInput.style.display = "flex";
                Utils.appendChild(compoundInput, checkboxInput);
                Utils.appendChild(compoundInput, labelElement);
                Utils.appendChild(element, compoundInput);
            }
            return element;
        }
    };
    ChoiceSetInput.prototype.getJsonTypeName = function () {
        return "Input.ChoiceSet";
    };
    ChoiceSetInput.prototype.validate = function () {
        var result = [];
        if (this.choices.length == 0) {
            result = [{ error: Enums.ValidationError.CollectionCantBeEmpty, message: "An Input.ChoiceSet must have at least one choice defined." }];
        }
        for (var i = 0; i < this.choices.length; i++) {
            if (!this.choices[i].title || !this.choices[i].value) {
                result = result.concat([{ error: Enums.ValidationError.PropertyCantBeNull, message: "All choices in an Input.ChoiceSet must have their title and value properties set." }]);
                break;
            }
        }
        return result;
    };
    ChoiceSetInput.prototype.parse = function (json) {
        _super.prototype.parse.call(this, json);
        this.isCompact = !(json["style"] === "expanded");
        this.isMultiSelect = json["isMultiSelect"];
        this.placeholder = json["placeholder"];
        if (json["choices"] != undefined) {
            var choiceArray = json["choices"];
            for (var i = 0; i < choiceArray.length; i++) {
                var choice = new Choice();
                choice.title = choiceArray[i]["title"];
                choice.value = choiceArray[i]["value"];
                this.choices.push(choice);
            }
        }
    };
    Object.defineProperty(ChoiceSetInput.prototype, "value", {
        get: function () {
            if (!this.isMultiSelect) {
                if (this.isCompact) {
                    return this._selectElement ? this._selectElement.value : null;
                }
                else {
                    if (!this._toggleInputs || this._toggleInputs.length == 0) {
                        return null;
                    }
                    for (var i = 0; i < this._toggleInputs.length; i++) {
                        if (this._toggleInputs[i].checked) {
                            return this._toggleInputs[i].value;
                        }
                    }
                    return null;
                }
            }
            else {
                if (!this._toggleInputs || this._toggleInputs.length == 0) {
                    return null;
                }
                var result = "";
                for (var i = 0; i < this._toggleInputs.length; i++) {
                    if (this._toggleInputs[i].checked) {
                        if (result != "") {
                            result += ";";
                        }
                        result += this._toggleInputs[i].value;
                    }
                }
                return result == "" ? null : result;
            }
        },
        enumerable: true,
        configurable: true
    });
    return ChoiceSetInput;
}(Input));
exports.ChoiceSetInput = ChoiceSetInput;
var NumberInput = /** @class */ (function (_super) {
    __extends(NumberInput, _super);
    function NumberInput() {
        return _super !== null && _super.apply(this, arguments) || this;
    }
    NumberInput.prototype.internalRender = function () {
        this._numberInputElement = document.createElement("input");
        this._numberInputElement.type = "number";
        this._numberInputElement.className = "ac-input ac-numberInput";
        this._numberInputElement.min = this.min;
        this._numberInputElement.max = this.max;
        this._numberInputElement.style.width = "100%";
        this._numberInputElement.tabIndex = 0;
        if (!Utils.isNullOrEmpty(this.defaultValue)) {
            this._numberInputElement.value = this.defaultValue;
        }
        if (!Utils.isNullOrEmpty(this.placeholder)) {
            this._numberInputElement.placeholder = this.placeholder;
            this._numberInputElement.setAttribute("aria-label", this.placeholder);
        }
        return this._numberInputElement;
    };
    NumberInput.prototype.getJsonTypeName = function () {
        return "Input.Number";
    };
    NumberInput.prototype.parse = function (json) {
        _super.prototype.parse.call(this, json);
        this.placeholder = json["placeholder"];
        this.min = json["min"];
        this.max = json["max"];
    };
    Object.defineProperty(NumberInput.prototype, "value", {
        get: function () {
            return this._numberInputElement ? this._numberInputElement.value : null;
        },
        enumerable: true,
        configurable: true
    });
    return NumberInput;
}(Input));
exports.NumberInput = NumberInput;
var DateInput = /** @class */ (function (_super) {
    __extends(DateInput, _super);
    function DateInput() {
        return _super !== null && _super.apply(this, arguments) || this;
    }
    DateInput.prototype.internalRender = function () {
        this._dateInputElement = document.createElement("input");
        this._dateInputElement.type = "date";
        this._dateInputElement.className = "ac-input ac-dateInput";
        this._dateInputElement.style.width = "100%";
        if (!Utils.isNullOrEmpty(this.defaultValue)) {
            this._dateInputElement.value = this.defaultValue;
        }
        return this._dateInputElement;
    };
    DateInput.prototype.getJsonTypeName = function () {
        return "Input.Date";
    };
    Object.defineProperty(DateInput.prototype, "value", {
        get: function () {
            return this._dateInputElement ? this._dateInputElement.value : null;
        },
        enumerable: true,
        configurable: true
    });
    return DateInput;
}(Input));
exports.DateInput = DateInput;
var TimeInput = /** @class */ (function (_super) {
    __extends(TimeInput, _super);
    function TimeInput() {
        return _super !== null && _super.apply(this, arguments) || this;
    }
    TimeInput.prototype.internalRender = function () {
        this._timeInputElement = document.createElement("input");
        this._timeInputElement.type = "time";
        this._timeInputElement.className = "ac-input ac-timeInput";
        this._timeInputElement.style.width = "100%";
        if (!Utils.isNullOrEmpty(this.defaultValue)) {
            this._timeInputElement.value = this.defaultValue;
        }
        return this._timeInputElement;
    };
    TimeInput.prototype.getJsonTypeName = function () {
        return "Input.Time";
    };
    Object.defineProperty(TimeInput.prototype, "value", {
        get: function () {
            return this._timeInputElement ? this._timeInputElement.value : null;
        },
        enumerable: true,
        configurable: true
    });
    return TimeInput;
}(Input));
exports.TimeInput = TimeInput;
var ActionButtonState;
(function (ActionButtonState) {
    ActionButtonState[ActionButtonState["Normal"] = 0] = "Normal";
    ActionButtonState[ActionButtonState["Expanded"] = 1] = "Expanded";
    ActionButtonState[ActionButtonState["Subdued"] = 2] = "Subdued";
})(ActionButtonState || (ActionButtonState = {}));
var ActionButton = /** @class */ (function () {
    function ActionButton(action) {
        var _this = this;
        this._element = null;
        this._state = ActionButtonState.Normal;
        this.onClick = null;
        this._action = action;
        this._element = document.createElement("button");
        this._element.type = "button";
        this._element.style.overflow = "hidden";
        this._element.style.whiteSpace = "nowrap";
        this._element.style.textOverflow = "ellipsis";
        this._element.onclick = function (e) { _this.click(); };
        this.updateCssStyle();
    }
    ActionButton.prototype.click = function () {
        if (this.onClick != null) {
            this.onClick(this);
        }
    };
    ActionButton.prototype.updateCssStyle = function () {
        this._element.className = "ac-pushButton";
        if (this._action instanceof ShowCardAction) {
            this._element.classList.add("expandable");
        }
        switch (this._state) {
            case ActionButtonState.Expanded:
                this._element.classList.add("expanded");
                break;
            case ActionButtonState.Subdued:
                this._element.classList.add("subdued");
                break;
        }
    };
    Object.defineProperty(ActionButton.prototype, "action", {
        get: function () {
            return this._action;
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
            this._element.setAttribute("aria-label", this._text);
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
var Action = /** @class */ (function () {
    function Action() {
        this._parent = null;
        this._actionCollection = null; // hold the reference to its action collection
    }
    Action.prototype.setParent = function (value) {
        this._parent = value;
    };
    Action.prototype.execute = function () {
        raiseExecuteActionEvent(this);
    };
    Action.prototype.setCollection = function (actionCollection) {
        this._actionCollection = actionCollection;
    };
    // Expand the action card pane with a inline status card
    // Null status will clear the status bar
    Action.prototype.setStatus = function (status) {
        if (this._actionCollection == null) {
            return;
        }
        if (status) {
            var statusCard = new InlineAdaptiveCard();
            statusCard.parse(status);
            this._actionCollection.showStatusCard(statusCard);
        }
        else {
            this._actionCollection.hideStatusCard();
        }
    };
    Action.prototype.validate = function () {
        return [];
    };
    Action.prototype.prepare = function (inputs) {
        // Do nothing in base implementation
    };
    ;
    Action.prototype.parse = function (json) {
        this.id = json["id"];
        this.title = json["title"];
    };
    Action.prototype.getAllInputs = function () {
        return [];
    };
    Action.prototype.getActionById = function (id) {
        if (this.id == id) {
            return this;
        }
    };
    Object.defineProperty(Action.prototype, "parent", {
        get: function () {
            return this._parent;
        },
        enumerable: true,
        configurable: true
    });
    return Action;
}());
exports.Action = Action;
var SubmitAction = /** @class */ (function (_super) {
    __extends(SubmitAction, _super);
    function SubmitAction() {
        var _this = _super !== null && _super.apply(this, arguments) || this;
        _this._isPrepared = false;
        return _this;
    }
    SubmitAction.prototype.getJsonTypeName = function () {
        return "Action.Submit";
    };
    SubmitAction.prototype.prepare = function (inputs) {
        if (this._originalData) {
            this._processedData = JSON.parse(JSON.stringify(this._originalData));
        }
        else {
            this._processedData = {};
        }
        for (var i = 0; i < inputs.length; i++) {
            var inputValue = inputs[i].value;
            if (inputValue != null) {
                this._processedData[inputs[i].id] = inputs[i].value;
            }
        }
        this._isPrepared = true;
    };
    SubmitAction.prototype.parse = function (json) {
        _super.prototype.parse.call(this, json);
        this.data = json["data"];
    };
    Object.defineProperty(SubmitAction.prototype, "data", {
        get: function () {
            return this._isPrepared ? this._processedData : this._originalData;
        },
        set: function (value) {
            this._originalData = value;
            this._isPrepared = false;
        },
        enumerable: true,
        configurable: true
    });
    return SubmitAction;
}(Action));
exports.SubmitAction = SubmitAction;
var OpenUrlAction = /** @class */ (function (_super) {
    __extends(OpenUrlAction, _super);
    function OpenUrlAction() {
        return _super !== null && _super.apply(this, arguments) || this;
    }
    OpenUrlAction.prototype.getJsonTypeName = function () {
        return "Action.OpenUrl";
    };
    OpenUrlAction.prototype.validate = function () {
        if (!this.url) {
            return [{ error: Enums.ValidationError.PropertyCantBeNull, message: "An Action.OpenUrl must have its url property set." }];
        }
        else {
            return [];
        }
    };
    OpenUrlAction.prototype.parse = function (json) {
        _super.prototype.parse.call(this, json);
        this.url = json["url"];
    };
    return OpenUrlAction;
}(Action));
exports.OpenUrlAction = OpenUrlAction;
var HttpHeader = /** @class */ (function () {
    function HttpHeader() {
        this._value = new Utils.StringWithSubstitutions();
    }
    HttpHeader.prototype.prepare = function (inputs) {
        this._value.substituteInputValues(inputs);
    };
    Object.defineProperty(HttpHeader.prototype, "value", {
        get: function () {
            return this._value.get();
        },
        set: function (newValue) {
            this._value.set(newValue);
        },
        enumerable: true,
        configurable: true
    });
    return HttpHeader;
}());
exports.HttpHeader = HttpHeader;
var HttpAction = /** @class */ (function (_super) {
    __extends(HttpAction, _super);
    function HttpAction() {
        var _this = _super !== null && _super.apply(this, arguments) || this;
        _this._url = new Utils.StringWithSubstitutions();
        _this._body = new Utils.StringWithSubstitutions();
        _this._headers = [];
        return _this;
    }
    HttpAction.prototype.getJsonTypeName = function () {
        return "Action.Http";
    };
    HttpAction.prototype.validate = function () {
        var result = [];
        if (!this.url) {
            result = [{ error: Enums.ValidationError.PropertyCantBeNull, message: "An Action.Http must have its url property set." }];
        }
        if (this.headers.length > 0) {
            for (var i = 0; i < this.headers.length; i++) {
                if (!this.headers[i].name || !this.headers[i].value) {
                    result = result.concat([{ error: Enums.ValidationError.PropertyCantBeNull, message: "All headers of an Action.Http must have their name and value properties set." }]);
                    break;
                }
            }
        }
        return result;
    };
    HttpAction.prototype.prepare = function (inputs) {
        this._url.substituteInputValues(inputs);
        this._body.substituteInputValues(inputs);
        for (var i = 0; i < this._headers.length; i++) {
            this._headers[i].prepare(inputs);
        }
    };
    ;
    HttpAction.prototype.parse = function (json) {
        _super.prototype.parse.call(this, json);
        this.url = json["url"];
        this.method = json["method"];
        this.body = json["body"];
        if (json["headers"] != null) {
            var jsonHeaders = json["headers"];
            for (var i = 0; i < jsonHeaders.length; i++) {
                var httpHeader = new HttpHeader();
                httpHeader.name = jsonHeaders[i]["name"];
                httpHeader.value = jsonHeaders[i]["value"];
                this.headers.push(httpHeader);
            }
        }
    };
    Object.defineProperty(HttpAction.prototype, "url", {
        get: function () {
            return this._url.get();
        },
        set: function (value) {
            this._url.set(value);
        },
        enumerable: true,
        configurable: true
    });
    Object.defineProperty(HttpAction.prototype, "body", {
        get: function () {
            return this._body.get();
        },
        set: function (value) {
            this._body.set(value);
        },
        enumerable: true,
        configurable: true
    });
    Object.defineProperty(HttpAction.prototype, "headers", {
        get: function () {
            return this._headers;
        },
        enumerable: true,
        configurable: true
    });
    return HttpAction;
}(Action));
exports.HttpAction = HttpAction;
var ShowCardAction = /** @class */ (function (_super) {
    __extends(ShowCardAction, _super);
    function ShowCardAction() {
        var _this = _super !== null && _super.apply(this, arguments) || this;
        _this.card = new InlineAdaptiveCard();
        return _this;
    }
    ShowCardAction.prototype.setParent = function (value) {
        _super.prototype.setParent.call(this, value);
        invokeSetParent(this.card, value);
    };
    ShowCardAction.prototype.getJsonTypeName = function () {
        return "Action.ShowCard";
    };
    ShowCardAction.prototype.validate = function () {
        return this.card.validate();
    };
    ShowCardAction.prototype.parse = function (json) {
        _super.prototype.parse.call(this, json);
        this.card.parse(json["card"]);
    };
    ShowCardAction.prototype.getAllInputs = function () {
        return this.card.getAllInputs();
    };
    ShowCardAction.prototype.getActionById = function (id) {
        var result = _super.prototype.getActionById.call(this, id);
        if (!result) {
            result = this.card.getActionById(id);
        }
        return result;
    };
    return ShowCardAction;
}(Action));
exports.ShowCardAction = ShowCardAction;
var ActionCollection = /** @class */ (function () {
    function ActionCollection(owner) {
        this._actionButtons = [];
        this._expandedAction = null;
        this._renderedActionCount = 0;
        this._statusCard = null;
        this._actionCard = null;
        this.items = [];
        this.onHideActionCardPane = null;
        this.onShowActionCardPane = null;
        this._owner = owner;
    }
    ActionCollection.prototype.showStatusCard = function (status) {
        invokeSetParent(status, this._owner);
        this._statusCard = status.render();
        this.refreshContainer();
    };
    ActionCollection.prototype.hideStatusCard = function () {
        this._statusCard = null;
        this.refreshContainer();
    };
    ActionCollection.prototype.refreshContainer = function () {
        this._actionCardContainer.innerHTML = "";
        if (this._actionCard === null && this._statusCard === null) {
            this._actionCardContainer.style.padding = "0px";
            this._actionCardContainer.style.marginTop = "0px";
            if (this.onHideActionCardPane) {
                this.onHideActionCardPane();
            }
            return;
        }
        if (this.onShowActionCardPane) {
            this.onShowActionCardPane(null);
        }
        this._actionCardContainer.style.marginTop = this._renderedActionCount > 0 ? this._owner.hostConfig.actions.showCard.inlineTopMargin + "px" : "0px";
        var padding = this._owner.hostConfig.paddingToSpacingDefinition(this._owner.getNonZeroPadding());
        if (this._actionCard !== null) {
            this._actionCard.style.paddingLeft = padding.left + "px";
            this._actionCard.style.paddingRight = padding.right + "px";
            this._actionCard.style.marginLeft = "-" + padding.left + "px";
            this._actionCard.style.marginRight = "-" + padding.right + "px";
            Utils.appendChild(this._actionCardContainer, this._actionCard);
        }
        if (this._statusCard !== null) {
            this._statusCard.style.paddingLeft = padding.left + "px";
            this._statusCard.style.paddingRight = padding.right + "px";
            this._statusCard.style.marginLeft = "-" + padding.left + "px";
            this._statusCard.style.marginRight = "-" + padding.right + "px";
            Utils.appendChild(this._actionCardContainer, this._statusCard);
        }
    };
    ActionCollection.prototype.hideActionCard = function () {
        if (this._expandedAction) {
            raiseInlineCardExpandedEvent(this._expandedAction, false);
        }
        this._expandedAction = null;
        this._actionCard = null;
        this.refreshContainer();
    };
    ActionCollection.prototype.showActionCard = function (action) {
        if (action.card == null)
            return;
        var renderedCard = action.card.render();
        this._actionCard = renderedCard;
        this._expandedAction = action;
        this.refreshContainer();
        raiseInlineCardExpandedEvent(action, true);
    };
    ActionCollection.prototype.actionClicked = function (actionButton) {
        if (!(actionButton.action instanceof ShowCardAction)) {
            for (var i = 0; i < this._actionButtons.length; i++) {
                this._actionButtons[i].state = ActionButtonState.Normal;
            }
            this.hideActionCard();
            actionButton.action.execute();
        }
        else {
            this.hideStatusCard();
            if (this._owner.hostConfig.actions.showCard.actionMode === Enums.ShowCardActionMode.Popup) {
                actionButton.action.execute();
            }
            else if (actionButton.action === this._expandedAction) {
                for (var i = 0; i < this._actionButtons.length; i++) {
                    this._actionButtons[i].state = ActionButtonState.Normal;
                }
                this.hideActionCard();
            }
            else {
                for (var i = 0; i < this._actionButtons.length; i++) {
                    if (this._actionButtons[i] !== actionButton) {
                        this._actionButtons[i].state = ActionButtonState.Subdued;
                    }
                }
                actionButton.state = ActionButtonState.Expanded;
                this.showActionCard(actionButton.action);
            }
        }
    };
    ActionCollection.prototype.getActionById = function (id) {
        var result = null;
        for (var i = 0; i < this.items.length; i++) {
            result = this.items[i].getActionById(id);
            if (result) {
                break;
            }
        }
        return result;
    };
    ActionCollection.prototype.validate = function () {
        var result = [];
        if (this._owner.hostConfig.actions.maxActions && this.items.length > this._owner.hostConfig.actions.maxActions) {
            result.push({
                error: Enums.ValidationError.TooManyActions,
                message: "A maximum of " + this._owner.hostConfig.actions.maxActions + " actions are allowed."
            });
        }
        if (this.items.length > 0 && !this._owner.hostConfig.supportsInteractivity) {
            result.push({
                error: Enums.ValidationError.InteractivityNotAllowed,
                message: "Interactivity is not allowed."
            });
        }
        for (var i = 0; i < this.items.length; i++) {
            if (!isActionAllowed(this.items[i], this._owner.getForbiddenActionTypes())) {
                result.push({
                    error: Enums.ValidationError.ActionTypeNotAllowed,
                    message: "Actions of type " + this.items[i].getJsonTypeName() + " are not allowe."
                });
            }
        }
        for (var i = 0; i < this.items.length; i++) {
            result = result.concat(this.items[i].validate());
        }
        return result;
    };
    ActionCollection.prototype.render = function () {
        var _this = this;
        if (!this._owner.hostConfig.supportsInteractivity) {
            return null;
        }
        var element = document.createElement("div");
        this._actionCardContainer = document.createElement("div");
        this._renderedActionCount = 0;
        var maxActions = this._owner.hostConfig.actions.maxActions ? Math.min(this._owner.hostConfig.actions.maxActions, this.items.length) : this.items.length;
        var forbiddenActionTypes = this._owner.getForbiddenActionTypes();
        if (AdaptiveCard.preExpandSingleShowCardAction && maxActions == 1 && this.items[0] instanceof ShowCardAction && isActionAllowed(this.items[i], forbiddenActionTypes)) {
            this.showActionCard(this.items[0]);
            this._renderedActionCount = 1;
        }
        else {
            var buttonStrip = document.createElement("div");
            buttonStrip.style.display = "flex";
            if (this._owner.hostConfig.actions.actionsOrientation == Enums.Orientation.Horizontal) {
                buttonStrip.style.flexDirection = "row";
                if (this._owner.horizontalAlignment && this._owner.hostConfig.actions.actionAlignment != Enums.ActionAlignment.Stretch) {
                    switch (this._owner.horizontalAlignment) {
                        case Enums.HorizontalAlignment.Center:
                            buttonStrip.style.justifyContent = "center";
                            break;
                        case Enums.HorizontalAlignment.Right:
                            buttonStrip.style.justifyContent = "flex-end";
                            break;
                        default:
                            buttonStrip.style.justifyContent = "flex-start";
                            break;
                    }
                }
                else {
                    switch (this._owner.hostConfig.actions.actionAlignment) {
                        case Enums.ActionAlignment.Center:
                            buttonStrip.style.justifyContent = "center";
                            break;
                        case Enums.ActionAlignment.Right:
                            buttonStrip.style.justifyContent = "flex-end";
                            break;
                        default:
                            buttonStrip.style.justifyContent = "flex-start";
                            break;
                    }
                }
            }
            else {
                buttonStrip.style.flexDirection = "column";
                if (this._owner.horizontalAlignment && this._owner.hostConfig.actions.actionAlignment != Enums.ActionAlignment.Stretch) {
                    switch (this._owner.horizontalAlignment) {
                        case Enums.HorizontalAlignment.Center:
                            buttonStrip.style.alignItems = "center";
                            break;
                        case Enums.HorizontalAlignment.Right:
                            buttonStrip.style.alignItems = "flex-end";
                            break;
                        default:
                            buttonStrip.style.alignItems = "flex-start";
                            break;
                    }
                }
                else {
                    switch (this._owner.hostConfig.actions.actionAlignment) {
                        case Enums.ActionAlignment.Center:
                            buttonStrip.style.alignItems = "center";
                            break;
                        case Enums.ActionAlignment.Right:
                            buttonStrip.style.alignItems = "flex-end";
                            break;
                        case Enums.ActionAlignment.Stretch:
                            buttonStrip.style.alignItems = "stretch";
                            break;
                        default:
                            buttonStrip.style.alignItems = "flex-start";
                            break;
                    }
                }
            }
            for (var i = 0; i < this.items.length; i++) {
                if (isActionAllowed(this.items[i], forbiddenActionTypes)) {
                    var actionButton = new ActionButton(this.items[i]);
                    actionButton.element.style.overflow = "hidden";
                    actionButton.element.style.overflow = "table-cell";
                    actionButton.element.style.flex = this._owner.hostConfig.actions.actionAlignment === Enums.ActionAlignment.Stretch ? "0 1 100%" : "0 1 auto";
                    actionButton.text = this.items[i].title;
                    actionButton.onClick = function (ab) { _this.actionClicked(ab); };
                    this._actionButtons.push(actionButton);
                    buttonStrip.appendChild(actionButton.element);
                    this._renderedActionCount++;
                    if (this._renderedActionCount >= this._owner.hostConfig.actions.maxActions || i == this.items.length - 1) {
                        break;
                    }
                    else if (this._owner.hostConfig.actions.buttonSpacing > 0) {
                        var spacer = document.createElement("div");
                        if (this._owner.hostConfig.actions.actionsOrientation === Enums.Orientation.Horizontal) {
                            spacer.style.flex = "0 0 auto";
                            spacer.style.width = this._owner.hostConfig.actions.buttonSpacing + "px";
                        }
                        else {
                            spacer.style.height = this._owner.hostConfig.actions.buttonSpacing + "px";
                        }
                        Utils.appendChild(buttonStrip, spacer);
                    }
                }
            }
            var buttonStripContainer = document.createElement("div");
            buttonStripContainer.style.overflow = "hidden";
            buttonStripContainer.appendChild(buttonStrip);
            Utils.appendChild(element, buttonStripContainer);
        }
        Utils.appendChild(element, this._actionCardContainer);
        return this._renderedActionCount > 0 ? element : null;
    };
    ActionCollection.prototype.addAction = function (action) {
        if (!action.parent) {
            this.items.push(action);
            invokeSetParent(action, this._owner);
            invokeSetCollection(action, this);
        }
        else {
            throw new Error("The action already belongs to another element.");
        }
    };
    ActionCollection.prototype.clear = function () {
        this.items = [];
    };
    ActionCollection.prototype.getAllInputs = function () {
        var result = [];
        for (var i = 0; i < this.items.length; i++) {
            var action = this.items[i];
            result = result.concat(action.getAllInputs());
        }
        return result;
    };
    return ActionCollection;
}());
var ActionSet = /** @class */ (function (_super) {
    __extends(ActionSet, _super);
    function ActionSet() {
        var _this = _super.call(this) || this;
        _this._actionCollection = new ActionCollection(_this);
        _this._actionCollection.onHideActionCardPane = function () { _this.showBottomSpacer(_this); };
        _this._actionCollection.onShowActionCardPane = function (action) { _this.hideBottomSpacer(_this); };
        return _this;
    }
    ActionSet.prototype.internalRender = function () {
        return this._actionCollection.render();
    };
    ActionSet.prototype.getJsonTypeName = function () {
        return "ActionSet";
    };
    ActionSet.prototype.validate = function () {
        return this._actionCollection.validate();
    };
    ActionSet.prototype.parse = function (json, itemsCollectionPropertyName) {
        if (itemsCollectionPropertyName === void 0) { itemsCollectionPropertyName = "items"; }
        _super.prototype.parse.call(this, json);
        if (json["actions"] != undefined) {
            var jsonActions = json["actions"];
            for (var i = 0; i < jsonActions.length; i++) {
                this.addAction(createActionInstance(jsonActions[i]));
            }
        }
    };
    ActionSet.prototype.addAction = function (action) {
        if (action != null) {
            this._actionCollection.addAction(action);
        }
    };
    ActionSet.prototype.getAllInputs = function () {
        return this._actionCollection.getAllInputs();
    };
    ActionSet.prototype.renderSpeech = function () {
        // TODO: What's the right thing to do here?
        return "";
    };
    Object.defineProperty(ActionSet.prototype, "isInteractive", {
        get: function () {
            return true;
        },
        enumerable: true,
        configurable: true
    });
    return ActionSet;
}(CardElement));
exports.ActionSet = ActionSet;
var BackgroundImage = /** @class */ (function () {
    function BackgroundImage() {
        this.mode = Enums.BackgroundImageMode.Stretch;
        this.horizontalAlignment = Enums.HorizontalAlignment.Left;
        this.verticalAlignment = Enums.VerticalAlignment.Top;
    }
    BackgroundImage.prototype.parse = function (json) {
        this.url = json["url"];
        this.mode = Utils.getEnumValueOrDefault(Enums.BackgroundImageMode, json["mode"], this.mode);
        this.horizontalAlignment = Utils.getEnumValueOrDefault(Enums.HorizontalAlignment, json["horizontalAlignment"], this.horizontalAlignment);
        this.verticalAlignment = Utils.getEnumValueOrDefault(Enums.VerticalAlignment, json["verticalAlignment"], this.verticalAlignment);
    };
    BackgroundImage.prototype.apply = function (element) {
        if (this.url) {
            element.style.backgroundImage = "url('" + this.url + "')";
            switch (this.mode) {
                case Enums.BackgroundImageMode.Repeat:
                    element.style.backgroundRepeat = "repeat";
                    break;
                case Enums.BackgroundImageMode.RepeatHorizontally:
                    element.style.backgroundRepeat = "repeat-x";
                    break;
                case Enums.BackgroundImageMode.RepeatVertically:
                    element.style.backgroundRepeat = "repeat-y";
                    break;
                case Enums.BackgroundImageMode.Stretch:
                default:
                    element.style.backgroundRepeat = "no-repeat";
                    element.style.backgroundSize = "cover";
                    break;
            }
            switch (this.horizontalAlignment) {
                case Enums.HorizontalAlignment.Center:
                    element.style.backgroundPositionX = "center";
                    break;
                case Enums.HorizontalAlignment.Right:
                    element.style.backgroundPositionX = "right";
                    break;
            }
            switch (this.verticalAlignment) {
                case Enums.VerticalAlignment.Center:
                    element.style.backgroundPositionY = "center";
                    break;
                case Enums.VerticalAlignment.Bottom:
                    element.style.backgroundPositionY = "bottom";
                    break;
            }
        }
    };
    return BackgroundImage;
}());
exports.BackgroundImage = BackgroundImage;
var Container = /** @class */ (function (_super) {
    __extends(Container, _super);
    function Container() {
        var _this = _super !== null && _super.apply(this, arguments) || this;
        _this._items = [];
        _this._style = null;
        return _this;
    }
    Container.prototype.isElementAllowed = function (element, forbiddenElementTypes) {
        if (!this.hostConfig.supportsInteractivity && element.isInteractive) {
            return false;
        }
        if (forbiddenElementTypes) {
            for (var i = 0; i < forbiddenElementTypes.length; i++) {
                if (element.getJsonTypeName() === forbiddenElementTypes[i]) {
                    return false;
                }
            }
        }
        return true;
    };
    Object.defineProperty(Container.prototype, "hasExplicitStyle", {
        get: function () {
            return this._style != null;
        },
        enumerable: true,
        configurable: true
    });
    Container.prototype.showBottomSpacer = function (requestingElement) {
        if ((!requestingElement || this.isLastElement(requestingElement))) {
            this.applyPadding();
            _super.prototype.showBottomSpacer.call(this, requestingElement);
        }
    };
    Container.prototype.hideBottomSpacer = function (requestingElement) {
        if ((!requestingElement || this.isLastElement(requestingElement))) {
            this.renderedElement.style.paddingBottom = "0px";
            _super.prototype.hideBottomSpacer.call(this, requestingElement);
        }
    };
    Container.prototype.applyPadding = function () {
        if (this.hasBackground) {
            var physicalMargin = new HostConfig.SpacingDefinition();
            var physicalPadding = new HostConfig.SpacingDefinition();
            var useAutoPadding = AdaptiveCard.useAutoPadding && (this.parent ? this.parent.canContentBleed() : false);
            if (useAutoPadding) {
                var effectivePadding = this.getNonZeroPadding();
                var effectiveMargin = new HostConfig.PaddingDefinition({
                    top: effectivePadding.top,
                    right: effectivePadding.right,
                    bottom: effectivePadding.bottom,
                    left: effectivePadding.left,
                });
                if (!this.isAtTheVeryTop()) {
                    effectivePadding.top = Enums.Padding.None;
                    effectiveMargin.top = Enums.Padding.None;
                }
                if (!this.isAtTheVeryBottom()) {
                    effectivePadding.bottom = Enums.Padding.None;
                    effectiveMargin.bottom = Enums.Padding.None;
                }
                if (!this.isAtTheVeryLeft()) {
                    effectivePadding.left = Enums.Padding.None;
                    effectiveMargin.left = Enums.Padding.None;
                }
                if (!this.isAtTheVeryRight()) {
                    effectivePadding.right = Enums.Padding.None;
                    effectiveMargin.right = Enums.Padding.None;
                }
                if (effectivePadding.left != Enums.Padding.None || effectivePadding.right != Enums.Padding.None) {
                    if (effectivePadding.left == Enums.Padding.None) {
                        effectivePadding.left = effectivePadding.right;
                    }
                    if (effectivePadding.right == Enums.Padding.None) {
                        effectivePadding.right = effectivePadding.left;
                    }
                }
                if (effectivePadding.top != Enums.Padding.None || effectivePadding.bottom != Enums.Padding.None) {
                    if (effectivePadding.top == Enums.Padding.None) {
                        effectivePadding.top = effectivePadding.bottom;
                    }
                    if (effectivePadding.bottom == Enums.Padding.None) {
                        effectivePadding.bottom = effectivePadding.top;
                    }
                }
                if (effectivePadding.top != Enums.Padding.None
                    || effectivePadding.right != Enums.Padding.None
                    || effectivePadding.bottom != Enums.Padding.None
                    || effectivePadding.left != Enums.Padding.None) {
                    if (effectivePadding.top == Enums.Padding.None) {
                        effectivePadding.top = Enums.Padding.Default;
                    }
                    if (effectivePadding.right == Enums.Padding.None) {
                        effectivePadding.right = Enums.Padding.Default;
                    }
                    if (effectivePadding.bottom == Enums.Padding.None) {
                        effectivePadding = Object.assign({}, effectivePadding, {
                            bottom: Enums.Padding.Default
                        });
                    }
                    if (effectivePadding.left == Enums.Padding.None) {
                        effectivePadding = Object.assign({}, effectivePadding, {
                            left: Enums.Padding.Default
                        });
                    }
                }
                if (effectivePadding.top == Enums.Padding.None &&
                    effectivePadding.right == Enums.Padding.None &&
                    effectivePadding.bottom == Enums.Padding.None &&
                    effectivePadding.left == Enums.Padding.None) {
                    effectivePadding = new HostConfig.PaddingDefinition({
                        top: Enums.Padding.Default,
                        right: Enums.Padding.Default,
                        bottom: Enums.Padding.Default,
                        left: Enums.Padding.Default,
                    });
                }
                physicalMargin = this.hostConfig.paddingToSpacingDefinition(effectiveMargin);
                physicalPadding = this.hostConfig.paddingToSpacingDefinition(effectivePadding);
            }
            else {
                physicalPadding = this.hostConfig.paddingToSpacingDefinition(new HostConfig.PaddingDefinition({
                    top: Enums.Padding.Default,
                    right: Enums.Padding.Default,
                    bottom: Enums.Padding.Default,
                    left: Enums.Padding.Default
                }));
            }
            if (this.renderedElement) {
                this.renderedElement.style.marginTop = "-" + physicalMargin.top + "px";
                this.renderedElement.style.marginRight = "-" + physicalMargin.right + "px";
                this.renderedElement.style.marginBottom = "-" + physicalMargin.bottom + "px";
                this.renderedElement.style.marginLeft = "-" + physicalMargin.left + "px";
                this.renderedElement.style.paddingTop = physicalPadding.top + "px";
                this.renderedElement.style.paddingRight = physicalPadding.right + "px";
                this.renderedElement.style.paddingBottom = physicalPadding.bottom + "px";
                this.renderedElement.style.paddingLeft = physicalPadding.left + "px";
            }
            if (this.separatorElement) {
                if (this.separatorOrientation == Enums.Orientation.Horizontal) {
                    this.separatorElement.style.marginLeft = "-" + physicalMargin.left + "px";
                    this.separatorElement.style.marginRight = "-" + physicalMargin.right + "px";
                }
                else {
                    this.separatorElement.style.marginTop = "-" + physicalMargin.top + "px";
                    this.separatorElement.style.marginBottom = "-" + physicalMargin.bottom + "px";
                }
            }
        }
    };
    Container.prototype.internalRender = function () {
        var _this = this;
        var element = document.createElement("div");
        element.className = "ac-container";
        element.style.display = "flex";
        element.style.flexDirection = "column";
        if (this.hasBackground) {
            if (this.backgroundImage) {
                this.backgroundImage.apply(element);
            }
            var styleDefinition = this.hostConfig.getContainerStyleDefinition(this.style);
            if (!Utils.isNullOrEmpty(styleDefinition.backgroundColor)) {
                element.style.backgroundColor = Utils.stringToCssColor(styleDefinition.backgroundColor);
            }
        }
        if (this.selectAction) {
            element.classList.add("ac-selectable");
            element.tabIndex = 0;
            element.setAttribute("role", "button");
            element.setAttribute("aria-label", this.selectAction.title);
            element.onclick = function (e) {
                if (_this.selectAction != null) {
                    _this.selectAction.execute();
                    e.cancelBubble = true;
                }
            };
            element.onkeypress = function (e) {
                if (_this.selectAction != null) {
                    // Enter or space pressed
                    if (e.keyCode == 13 || e.keyCode == 32) {
                        _this.selectAction.execute();
                    }
                }
            };
        }
        if (this._items.length > 0) {
            var renderedElementCount = 0;
            for (var i = 0; i < this._items.length; i++) {
                var renderedElement = this.isElementAllowed(this._items[i], this.getForbiddenElementTypes()) ? this._items[i].render() : null;
                if (renderedElement) {
                    if (renderedElementCount > 0 && this._items[i].separatorElement) {
                        this._items[i].separatorElement.style.flex = "0 0 auto";
                        Utils.appendChild(element, this._items[i].separatorElement);
                    }
                    Utils.appendChild(element, renderedElement);
                    renderedElementCount++;
                }
            }
        }
        return element;
    };
    Object.defineProperty(Container.prototype, "hasBackground", {
        get: function () {
            var parentContainer = this.getParentContainer();
            return this.backgroundImage != undefined || (this.hasExplicitStyle && (parentContainer ? parentContainer.style != this.style : false));
        },
        enumerable: true,
        configurable: true
    });
    Object.defineProperty(Container.prototype, "defaultStyle", {
        get: function () {
            return Enums.ContainerStyle.Default;
        },
        enumerable: true,
        configurable: true
    });
    Object.defineProperty(Container.prototype, "allowCustomStyle", {
        get: function () {
            return true;
        },
        enumerable: true,
        configurable: true
    });
    Object.defineProperty(Container.prototype, "style", {
        get: function () {
            if (this.allowCustomStyle) {
                return this._style ? this._style : this.defaultStyle;
            }
            else {
                return this.defaultStyle;
            }
        },
        enumerable: true,
        configurable: true
    });
    Container.prototype.getJsonTypeName = function () {
        return "Container";
    };
    Container.prototype.isFirstElement = function (element) {
        for (var i = 0; i < this._items.length; i++) {
            if (this._items[i].isVisible) {
                return this._items[i] == element;
            }
        }
        return false;
    };
    Container.prototype.isLastElement = function (element) {
        for (var i = this._items.length - 1; i >= 0; i--) {
            if (this._items[i].isVisible) {
                return this._items[i] == element;
            }
        }
        return false;
    };
    Container.prototype.validate = function () {
        var result = [];
        for (var i = 0; i < this._items.length; i++) {
            if (!this.hostConfig.supportsInteractivity && this._items[i].isInteractive) {
                result.push({
                    error: Enums.ValidationError.InteractivityNotAllowed,
                    message: "Interactivity is not allowed."
                });
            }
            if (!this.isElementAllowed(this._items[i], this.getForbiddenElementTypes())) {
                result.push({
                    error: Enums.ValidationError.InteractivityNotAllowed,
                    message: "Elements of type " + this._items[i].getJsonTypeName() + " are not allowed in this container."
                });
            }
            result = result.concat(this._items[i].validate());
        }
        return result;
    };
    Container.prototype.parse = function (json, itemsCollectionPropertyName) {
        if (itemsCollectionPropertyName === void 0) { itemsCollectionPropertyName = "items"; }
        _super.prototype.parse.call(this, json);
        var jsonBackgroundImage = json["backgroundImage"];
        if (jsonBackgroundImage) {
            this.backgroundImage = new BackgroundImage();
            if (typeof jsonBackgroundImage === "string") {
                this.backgroundImage.url = jsonBackgroundImage;
                this.backgroundImage.mode = Enums.BackgroundImageMode.Stretch;
            }
            else if (typeof jsonBackgroundImage === "object") {
                this.backgroundImage = new BackgroundImage();
                this.backgroundImage.parse(json["backgroundImage"]);
            }
        }
        this._style = Utils.getEnumValueOrDefault(Enums.ContainerStyle, json["style"], null);
        if (json[itemsCollectionPropertyName] != null) {
            var items = json[itemsCollectionPropertyName];
            for (var i = 0; i < items.length; i++) {
                var elementType = items[i]["type"];
                var element = AdaptiveCard.elementTypeRegistry.createInstance(elementType);
                if (!element) {
                    raiseParseError({
                        error: Enums.ValidationError.UnknownElementType,
                        message: "Unknown element type: " + elementType
                    });
                }
                else {
                    this.addItem(element);
                    element.parse(items[i]);
                }
            }
        }
        var selectActionJson = json["selectAction"];
        if (selectActionJson != undefined) {
            this.selectAction = createActionInstance(selectActionJson);
        }
    };
    Container.prototype.addItem = function (item) {
        if (!item.parent) {
            if (item.isStandalone) {
                this._items.push(item);
                invokeSetParent(item, this);
            }
            else {
                throw new Error("Elements of type " + item.getJsonTypeName() + " cannot be used as standalone elements.");
            }
        }
        else {
            throw new Error("The element already belongs to another container.");
        }
    };
    Container.prototype.clear = function () {
        this._items = [];
    };
    Container.prototype.canContentBleed = function () {
        return this.hasBackground ? false : _super.prototype.canContentBleed.call(this);
    };
    Container.prototype.getAllInputs = function () {
        var result = [];
        for (var i = 0; i < this._items.length; i++) {
            var item = this._items[i];
            result = result.concat(item.getAllInputs());
        }
        return result;
    };
    Container.prototype.getElementById = function (id) {
        var result = _super.prototype.getElementById.call(this, id);
        if (!result) {
            for (var i = 0; i < this._items.length; i++) {
                result = this._items[i].getElementById(id);
                if (result) {
                    break;
                }
            }
        }
        return result;
    };
    Container.prototype.getActionById = function (id) {
        var result = _super.prototype.getActionById.call(this, id);
        if (!result) {
            if (this.selectAction) {
                result = this.selectAction.getActionById(id);
            }
            if (!result) {
                for (var i = 0; i < this._items.length; i++) {
                    result = this._items[i].getActionById(id);
                    if (result) {
                        break;
                    }
                }
            }
        }
        return result;
    };
    Container.prototype.renderSpeech = function () {
        if (this.speak != null) {
            return this.speak;
        }
        // render each item
        var speak = null;
        if (this._items.length > 0) {
            speak = '';
            for (var i = 0; i < this._items.length; i++) {
                var result = this._items[i].renderSpeech();
                if (result) {
                    speak += result;
                }
            }
        }
        return speak;
    };
    Container.prototype.updateLayout = function (processChildren) {
        if (processChildren === void 0) { processChildren = true; }
        this.applyPadding();
        if (processChildren) {
            for (var i = 0; i < this._items.length; i++) {
                this._items[i].updateLayout();
            }
        }
    };
    Object.defineProperty(Container.prototype, "selectAction", {
        get: function () {
            return this._selectAction;
        },
        set: function (value) {
            this._selectAction = value;
            if (this._selectAction) {
                invokeSetParent(this._selectAction, this);
            }
        },
        enumerable: true,
        configurable: true
    });
    return Container;
}(CardElement));
exports.Container = Container;
var Column = /** @class */ (function (_super) {
    __extends(Column, _super);
    function Column() {
        var _this = _super !== null && _super.apply(this, arguments) || this;
        _this._computedWeight = 0;
        _this.width = "auto";
        return _this;
    }
    Column.prototype.adjustRenderedElementSize = function (renderedElement) {
        renderedElement.style.minWidth = "0";
        if (typeof this.width === "number") {
            renderedElement.style.flex = "1 1 " + (this._computedWeight > 0 ? this._computedWeight : this.width) + "%";
        }
        else if (this.width === "auto") {
            renderedElement.style.flex = "0 1 auto";
        }
        else {
            renderedElement.style.flex = "1 1 50px";
        }
    };
    Object.defineProperty(Column.prototype, "separatorOrientation", {
        get: function () {
            return Enums.Orientation.Vertical;
        },
        enumerable: true,
        configurable: true
    });
    Column.prototype.getJsonTypeName = function () {
        return "Column";
    };
    Column.prototype.parse = function (json) {
        _super.prototype.parse.call(this, json);
        var jsonWidth = json["width"];
        if (jsonWidth === undefined) {
            jsonWidth = json["size"];
            if (jsonWidth !== undefined) {
                raiseParseError({
                    error: Enums.ValidationError.Deprecated,
                    message: "The \"Column.size\" property is deprecated and will be removed. Use the \"Column.width\" property instead."
                });
            }
        }
        var invalidWidth = false;
        if (typeof jsonWidth === "number") {
            if (jsonWidth <= 0) {
                invalidWidth = true;
            }
        }
        else if (typeof jsonWidth === "string") {
            if (jsonWidth != "auto" && jsonWidth != "stretch") {
                var sizeAsNumber = parseInt(jsonWidth);
                if (!isNaN(sizeAsNumber)) {
                    jsonWidth = sizeAsNumber;
                }
                else {
                    invalidWidth = true;
                }
            }
        }
        else if (jsonWidth) {
            invalidWidth = true;
        }
        if (invalidWidth) {
            raiseParseError({
                error: Enums.ValidationError.InvalidPropertyValue,
                message: "Invalid column width: " + jsonWidth
            });
        }
        else {
            this.width = jsonWidth;
        }
    };
    Object.defineProperty(Column.prototype, "isStandalone", {
        get: function () {
            return false;
        },
        enumerable: true,
        configurable: true
    });
    return Column;
}(Container));
exports.Column = Column;
var ColumnSet = /** @class */ (function (_super) {
    __extends(ColumnSet, _super);
    function ColumnSet() {
        var _this = _super !== null && _super.apply(this, arguments) || this;
        _this._columns = [];
        return _this;
    }
    ColumnSet.prototype.internalRender = function () {
        var _this = this;
        if (this._columns.length > 0) {
            var element = document.createElement("div");
            element.className = "ac-columnSet";
            element.style.display = "flex";
            if (this.selectAction) {
                element.classList.add("ac-selectable");
                element.onclick = function (e) {
                    _this.selectAction.execute();
                    e.cancelBubble = true;
                };
            }
            switch (this.horizontalAlignment) {
                case Enums.HorizontalAlignment.Center:
                    element.style.justifyContent = "center";
                    break;
                case Enums.HorizontalAlignment.Right:
                    element.style.justifyContent = "flex-end";
                    break;
                default:
                    element.style.justifyContent = "flex-start";
                    break;
            }
            var totalWeight = 0;
            for (var i = 0; i < this._columns.length; i++) {
                if (typeof this._columns[i].width === "number") {
                    totalWeight += this._columns[i].width;
                }
            }
            var renderedColumnCount = 0;
            for (var i = 0; i < this._columns.length; i++) {
                if (typeof this._columns[i].width === "number" && totalWeight > 0) {
                    var computedWeight = 100 / totalWeight * this._columns[i].width;
                    // Best way to emulate "internal" access I know of
                    this._columns[i]["_computedWeight"] = computedWeight;
                }
                var renderedColumn = this._columns[i].render();
                if (renderedColumn) {
                    if (renderedColumnCount > 0 && this._columns[i].separatorElement) {
                        this._columns[i].separatorElement.style.flex = "0 0 auto";
                        Utils.appendChild(element, this._columns[i].separatorElement);
                    }
                    Utils.appendChild(element, renderedColumn);
                    renderedColumnCount++;
                }
            }
            return renderedColumnCount > 0 ? element : null;
        }
        else {
            return null;
        }
    };
    ColumnSet.prototype.getJsonTypeName = function () {
        return "ColumnSet";
    };
    ColumnSet.prototype.parse = function (json) {
        _super.prototype.parse.call(this, json);
        var selectActionJson = json["selectAction"];
        if (selectActionJson != undefined) {
            this.selectAction = createActionInstance(selectActionJson);
        }
        if (json["columns"] != null) {
            var jsonColumns = json["columns"];
            for (var i = 0; i < jsonColumns.length; i++) {
                var column = new Column();
                column.parse(jsonColumns[i]);
                this.addColumn(column);
            }
        }
    };
    ColumnSet.prototype.validate = function () {
        var result = [];
        var weightedColumns = 0;
        var stretchedColumns = 0;
        for (var i = 0; i < this._columns.length; i++) {
            if (typeof this._columns[i].width === "number") {
                weightedColumns++;
            }
            else if (this._columns[i].width === "stretch") {
                stretchedColumns++;
            }
            result = result.concat(this._columns[i].validate());
        }
        if (weightedColumns > 0 && stretchedColumns > 0) {
            result.push({
                error: Enums.ValidationError.Hint,
                message: "It is not recommended to use weighted and stretched columns in the same ColumnSet, because in such a situation stretched columns will always get the minimum amount of space."
            });
        }
        return result;
    };
    ColumnSet.prototype.updateLayout = function (processChildren) {
        if (processChildren === void 0) { processChildren = true; }
        if (processChildren) {
            for (var i = 0; i < this._columns.length; i++) {
                this._columns[i].updateLayout();
            }
        }
    };
    ColumnSet.prototype.addColumn = function (column) {
        if (!column.parent) {
            this._columns.push(column);
            invokeSetParent(column, this);
        }
        else {
            throw new Error("This column already belongs to another ColumnSet.");
        }
    };
    ColumnSet.prototype.isLeftMostElement = function (element) {
        return this._columns.indexOf(element) == 0;
    };
    ColumnSet.prototype.isRightMostElement = function (element) {
        return this._columns.indexOf(element) == this._columns.length - 1;
    };
    ColumnSet.prototype.getAllInputs = function () {
        var result = [];
        for (var i = 0; i < this._columns.length; i++) {
            result = result.concat(this._columns[i].getAllInputs());
        }
        return result;
    };
    ColumnSet.prototype.getElementById = function (id) {
        var result = _super.prototype.getElementById.call(this, id);
        if (!result) {
            for (var i = 0; i < this._columns.length; i++) {
                result = this._columns[i].getElementById(id);
                if (result) {
                    break;
                }
            }
        }
        return result;
    };
    ColumnSet.prototype.getActionById = function (id) {
        var result = null;
        for (var i = 0; i < this._columns.length; i++) {
            result = this._columns[i].getActionById(id);
            if (result) {
                break;
            }
        }
        return result;
    };
    ColumnSet.prototype.renderSpeech = function () {
        if (this.speak != null) {
            return this.speak;
        }
        // render each item
        var speak = '';
        if (this._columns.length > 0) {
            for (var i = 0; i < this._columns.length; i++) {
                speak += this._columns[i].renderSpeech();
            }
        }
        return speak;
    };
    Object.defineProperty(ColumnSet.prototype, "selectAction", {
        get: function () {
            return this._selectAction;
        },
        set: function (value) {
            this._selectAction = value;
            if (this._selectAction) {
                invokeSetParent(this._selectAction, this);
            }
        },
        enumerable: true,
        configurable: true
    });
    return ColumnSet;
}(CardElement));
exports.ColumnSet = ColumnSet;
function raiseAnchorClickedEvent(anchor) {
    return AdaptiveCard.onAnchorClicked != null ? AdaptiveCard.onAnchorClicked(anchor) : false;
}
function raiseExecuteActionEvent(action) {
    if (AdaptiveCard.onExecuteAction != null) {
        action.prepare(action.parent.getRootElement().getAllInputs());
        AdaptiveCard.onExecuteAction(action);
    }
}
function raiseInlineCardExpandedEvent(action, isExpanded) {
    if (AdaptiveCard.onInlineCardExpanded != null) {
        AdaptiveCard.onInlineCardExpanded(action, isExpanded);
    }
}
function raiseElementVisibilityChangedEvent(element) {
    element.getRootElement().updateLayout();
    if (AdaptiveCard.onElementVisibilityChanged != null) {
        AdaptiveCard.onElementVisibilityChanged(element);
    }
}
function raiseParseElementEvent(element, json) {
    if (AdaptiveCard.onParseElement != null) {
        AdaptiveCard.onParseElement(element, json);
    }
}
function raiseParseError(error) {
    if (AdaptiveCard.onParseError != null) {
        AdaptiveCard.onParseError(error);
    }
}
var TypeRegistry = /** @class */ (function () {
    function TypeRegistry() {
        this._items = [];
    }
    TypeRegistry.prototype.findTypeRegistration = function (typeName) {
        for (var i = 0; i < this._items.length; i++) {
            if (this._items[i].typeName === typeName) {
                return this._items[i];
            }
        }
        return null;
    };
    TypeRegistry.prototype.clear = function () {
        this._items = [];
    };
    TypeRegistry.prototype.registerType = function (typeName, createInstance) {
        var registrationInfo = this.findTypeRegistration(typeName);
        if (registrationInfo != null) {
            registrationInfo.createInstance = createInstance;
        }
        else {
            registrationInfo = {
                typeName: typeName,
                createInstance: createInstance
            };
            this._items.push(registrationInfo);
        }
    };
    TypeRegistry.prototype.unregisterType = function (typeName) {
        for (var i = 0; i < this._items.length; i++) {
            if (this._items[i].typeName === typeName) {
                this._items.splice(i, 1);
                return;
            }
        }
    };
    TypeRegistry.prototype.createInstance = function (typeName) {
        var registrationInfo = this.findTypeRegistration(typeName);
        return registrationInfo ? registrationInfo.createInstance() : null;
    };
    return TypeRegistry;
}());
exports.TypeRegistry = TypeRegistry;
var ContainerWithActions = /** @class */ (function (_super) {
    __extends(ContainerWithActions, _super);
    function ContainerWithActions() {
        var _this = _super.call(this) || this;
        _this._actionCollection = new ActionCollection(_this);
        _this._actionCollection.onHideActionCardPane = function () { _this.showBottomSpacer(null); };
        _this._actionCollection.onShowActionCardPane = function (action) { _this.hideBottomSpacer(null); };
        return _this;
    }
    ContainerWithActions.prototype.internalRender = function () {
        var element = _super.prototype.internalRender.call(this);
        var renderedActions = this._actionCollection.render();
        if (renderedActions) {
            Utils.appendChild(element, Utils.renderSeparation({
                spacing: this.hostConfig.getEffectiveSpacing(this.hostConfig.actions.spacing),
                lineThickness: null,
                lineColor: null
            }, Enums.Orientation.Horizontal));
            Utils.appendChild(element, renderedActions);
        }
        return element.children.length > 0 ? element : null;
    };
    ContainerWithActions.prototype.getActionById = function (id) {
        var result = this._actionCollection.getActionById(id);
        return result ? result : _super.prototype.getActionById.call(this, id);
    };
    ContainerWithActions.prototype.parse = function (json, itemsCollectionPropertyName) {
        if (itemsCollectionPropertyName === void 0) { itemsCollectionPropertyName = "items"; }
        _super.prototype.parse.call(this, json, itemsCollectionPropertyName);
        if (json["actions"] != undefined) {
            var jsonActions = json["actions"];
            for (var i = 0; i < jsonActions.length; i++) {
                var action = createActionInstance(jsonActions[i]);
                if (action != null) {
                    this.addAction(action);
                }
            }
        }
    };
    ContainerWithActions.prototype.isLastElement = function (element) {
        return _super.prototype.isLastElement.call(this, element) && this._actionCollection.items.length == 0;
    };
    ContainerWithActions.prototype.addAction = function (action) {
        this._actionCollection.addAction(action);
    };
    ContainerWithActions.prototype.clear = function () {
        _super.prototype.clear.call(this);
        this._actionCollection.clear();
    };
    ContainerWithActions.prototype.getAllInputs = function () {
        return _super.prototype.getAllInputs.call(this).concat(this._actionCollection.getAllInputs());
    };
    Object.defineProperty(ContainerWithActions.prototype, "isStandalone", {
        get: function () {
            return false;
        },
        enumerable: true,
        configurable: true
    });
    return ContainerWithActions;
}(Container));
exports.ContainerWithActions = ContainerWithActions;
var AdaptiveCard = /** @class */ (function (_super) {
    __extends(AdaptiveCard, _super);
    function AdaptiveCard() {
        var _this = _super !== null && _super.apply(this, arguments) || this;
        _this.minVersion = { major: 1, minor: 0 };
        return _this;
    }
    AdaptiveCard.initialize = function () {
        AdaptiveCard.elementTypeRegistry.clear();
        AdaptiveCard.elementTypeRegistry.registerType("Container", function () { return new Container(); });
        AdaptiveCard.elementTypeRegistry.registerType("TextBlock", function () { return new TextBlock(); });
        AdaptiveCard.elementTypeRegistry.registerType("Image", function () { return new Image(); });
        AdaptiveCard.elementTypeRegistry.registerType("ImageSet", function () { return new ImageSet(); });
        AdaptiveCard.elementTypeRegistry.registerType("FactSet", function () { return new FactSet(); });
        AdaptiveCard.elementTypeRegistry.registerType("ColumnSet", function () { return new ColumnSet(); });
        AdaptiveCard.elementTypeRegistry.registerType("ActionSet", function () { return new ActionSet(); });
        AdaptiveCard.elementTypeRegistry.registerType("Input.Text", function () { return new TextInput(); });
        AdaptiveCard.elementTypeRegistry.registerType("Input.Date", function () { return new DateInput(); });
        AdaptiveCard.elementTypeRegistry.registerType("Input.Time", function () { return new TimeInput(); });
        AdaptiveCard.elementTypeRegistry.registerType("Input.Number", function () { return new NumberInput(); });
        AdaptiveCard.elementTypeRegistry.registerType("Input.ChoiceSet", function () { return new ChoiceSetInput(); });
        AdaptiveCard.elementTypeRegistry.registerType("Input.Toggle", function () { return new ToggleInput(); });
        AdaptiveCard.actionTypeRegistry.clear();
        AdaptiveCard.actionTypeRegistry.registerType("Action.Http", function () { return new HttpAction(); });
        AdaptiveCard.actionTypeRegistry.registerType("Action.OpenUrl", function () { return new OpenUrlAction(); });
        AdaptiveCard.actionTypeRegistry.registerType("Action.Submit", function () { return new SubmitAction(); });
        AdaptiveCard.actionTypeRegistry.registerType("Action.ShowCard", function () { return new ShowCardAction(); });
    };
    AdaptiveCard.prototype.isVersionSupported = function () {
        var unsupportedVersion = (AdaptiveCard.currentVersion.major < this.minVersion.major) ||
            (AdaptiveCard.currentVersion.major == this.minVersion.major && AdaptiveCard.currentVersion.minor < this.minVersion.minor);
        return !unsupportedVersion;
    };
    AdaptiveCard.prototype.applyPadding = function () {
        var effectivePadding = this.hostConfig.paddingToSpacingDefinition(this.internalPadding);
        this.renderedElement.style.paddingTop = effectivePadding.top + "px";
        this.renderedElement.style.paddingRight = effectivePadding.right + "px";
        this.renderedElement.style.paddingBottom = effectivePadding.bottom + "px";
        this.renderedElement.style.paddingLeft = effectivePadding.left + "px";
    };
    Object.defineProperty(AdaptiveCard.prototype, "defaultPadding", {
        get: function () {
            return new HostConfig.PaddingDefinition({
                top: Enums.Padding.Default,
                right: Enums.Padding.Default,
                bottom: Enums.Padding.Default,
                left: Enums.Padding.Default
            });
        },
        enumerable: true,
        configurable: true
    });
    Object.defineProperty(AdaptiveCard.prototype, "allowCustomPadding", {
        get: function () {
            return false;
        },
        enumerable: true,
        configurable: true
    });
    Object.defineProperty(AdaptiveCard.prototype, "allowCustomStyle", {
        get: function () {
            return this.hostConfig.adaptiveCard.allowCustomStyle;
        },
        enumerable: true,
        configurable: true
    });
    Object.defineProperty(AdaptiveCard.prototype, "hasBackground", {
        get: function () {
            return true;
        },
        enumerable: true,
        configurable: true
    });
    AdaptiveCard.prototype.getJsonTypeName = function () {
        return "AdaptiveCard";
    };
    AdaptiveCard.prototype.validate = function () {
        var result = [];
        if (this._cardTypeName != "AdaptiveCard") {
            result.push({
                error: Enums.ValidationError.MissingCardType,
                message: "Invalid or missing card type. Make sure the card's type property is set to \"AdaptiveCard\"."
            });
        }
        if (!this.isVersionSupported()) {
            result.push({
                error: Enums.ValidationError.UnsupportedCardVersion,
                message: "The specified card version is not supported."
            });
        }
        return result.concat(_super.prototype.validate.call(this));
    };
    AdaptiveCard.prototype.parse = function (json) {
        this._cardTypeName = json["type"];
        var minVersion = json["minVersion"];
        var regEx = /(\d+).(\d+)/gi;
        var matches = regEx.exec(minVersion);
        if (matches != null && matches.length == 3) {
            this.minVersion.major = parseInt(matches[1]);
            this.minVersion.minor = parseInt(matches[2]);
        }
        this.fallbackText = json["fallbackText"];
        _super.prototype.parse.call(this, json, "body");
    };
    AdaptiveCard.prototype.render = function () {
        var renderedCard;
        if (!this.isVersionSupported()) {
            renderedCard = document.createElement("div");
            renderedCard.innerHTML = this.fallbackText ? this.fallbackText : "The specified card version is not supported.";
        }
        else {
            renderedCard = _super.prototype.render.call(this);
            if (renderedCard) {
                renderedCard.tabIndex = 0;
                if (!Utils.isNullOrEmpty(this.speak)) {
                    renderedCard.setAttribute("aria-label", this.speak);
                }
            }
        }
        return renderedCard;
    };
    AdaptiveCard.prototype.canContentBleed = function () {
        return true;
    };
    AdaptiveCard.currentVersion = { major: 1, minor: 0 };
    AdaptiveCard.useAutoPadding = false;
    AdaptiveCard.preExpandSingleShowCardAction = false;
    AdaptiveCard.elementTypeRegistry = new TypeRegistry();
    AdaptiveCard.actionTypeRegistry = new TypeRegistry();
    AdaptiveCard.onAnchorClicked = null;
    AdaptiveCard.onExecuteAction = null;
    AdaptiveCard.onElementVisibilityChanged = null;
    AdaptiveCard.onInlineCardExpanded = null;
    AdaptiveCard.onParseElement = null;
    AdaptiveCard.onParseError = null;
    return AdaptiveCard;
}(ContainerWithActions));
exports.AdaptiveCard = AdaptiveCard;
// This calls acts as a static constructor (see https://github.com/Microsoft/TypeScript/issues/265)
AdaptiveCard.initialize();
var InlineAdaptiveCard = /** @class */ (function (_super) {
    __extends(InlineAdaptiveCard, _super);
    function InlineAdaptiveCard() {
        return _super !== null && _super.apply(this, arguments) || this;
    }
    Object.defineProperty(InlineAdaptiveCard.prototype, "defaultPadding", {
        get: function () {
            return new HostConfig.PaddingDefinition({
                top: Enums.Padding.Default,
                right: Enums.Padding.Default,
                bottom: Enums.Padding.Default,
                left: Enums.Padding.Default
            });
        },
        enumerable: true,
        configurable: true
    });
    Object.defineProperty(InlineAdaptiveCard.prototype, "defaultStyle", {
        get: function () {
            return this.hostConfig.actions.showCard.style ? this.hostConfig.actions.showCard.style : Enums.ContainerStyle.Emphasis;
        },
        enumerable: true,
        configurable: true
    });
    InlineAdaptiveCard.prototype.render = function () {
        var renderedCard = _super.prototype.render.call(this);
        renderedCard.setAttribute("aria-live", "polite");
        renderedCard.removeAttribute("tabindex");
        return renderedCard;
    };
    InlineAdaptiveCard.prototype.getForbiddenActionTypes = function () {
        return [ShowCardAction];
    };
    return InlineAdaptiveCard;
}(AdaptiveCard));
var defaultHostConfig = new HostConfig.HostConfig();
//# sourceMappingURL=card-elements.js.map
var __extends = (this && this.__extends) || function (d, b) {
    for (var p in b) if (b.hasOwnProperty(p)) d[p] = b[p];
    function __() { this.constructor = d; }
    d.prototype = b === null ? Object.create(b) : (__.prototype = b.prototype, new __());
};
var Activity = (function (_super) {
    __extends(Activity, _super);
    function Activity() {
        _super.apply(this, arguments);
        this.imageSize = Size.Medium;
        this.imageStyle = PictureStyle.Person;
    }
    Activity.prototype.render = function () {
        var html = '';
        var element = document.createElement("div");
        element.style.display = "flex";
        if (!isNullOrEmpty(this.imageUrl)) {
            var size = Picture.getPhysicalSize(this.imageSize);
            var imageSection = document.createElement("div");
            imageSection.style.flex = "0 0 auto";
            imageSection.style.marginRight = "10px";
            imageSection.style.height = size.toString() + "px";
            var image = document.createElement("img");
            image.style.width = size.toString() + "px";
            image.style.height = size.toString() + "px";
            if (this.imageStyle == PictureStyle.Person) {
                image.className = "inCircle";
                image.style.borderRadius = (size / 2).toString() + "px";
                image.style.backgroundPosition = "50% 50%";
                image.style.backgroundRepeat = "no-repeat";
            }
            image.src = this.imageUrl;
            appendChild(imageSection, image);
            appendChild(element, imageSection);
        }
        if (!isNullOrEmpty(this.title) || !isNullOrEmpty(this.subtitle) || !isNullOrEmpty(this.text)) {
            var contentSection = document.createElement("div");
            contentSection.style.flex = "1 1 auto";
            contentSection.style.marginTop = "-5px";
            var textBlock = new TextBlock(this.container);
            textBlock.text = this.title;
            appendChild(contentSection, textBlock.render());
            textBlock = new TextBlock(this.container);
            textBlock.text = this.subtitle;
            textBlock.textWeight = TextWeight.Lighter;
            // textBlock.textColor = TextColor.Brighter;
            appendChild(contentSection, textBlock.render());
            textBlock = new TextBlock(this.container);
            textBlock.text = this.text;
            appendChild(contentSection, textBlock.render());
            appendChild(element, contentSection);
        }
        return element;
    };
    Activity.prototype.getSpacingAfterThis = function () {
        return 16;
    };
    return Activity;
}(CardElement));
function parsePicture(container, json, defaultSize, defaultStyle) {
    if (defaultSize === void 0) { defaultSize = Size.Medium; }
    if (defaultStyle === void 0) { defaultStyle = PictureStyle.Normal; }
    var picture = new Picture(container);
    picture.url = json["image"];
    picture.size = stringToSize(json["size"], defaultSize);
    return picture;
}
function parsePictureGallery(container, json) {
    var pictureGallery = new PictureGallery(container);
    var pictureArray = json;
    for (var i = 0; i < pictureArray.length; i++) {
        var picture = parsePicture(container, pictureArray[i], Size.Large);
        pictureGallery.items.push(picture);
    }
    return pictureGallery;
}
function parseFactGroup(container, json) {
    var factGroup = new FactGroup(container);
    var factArray = json;
    for (var i = 0; i < factArray.length; i++) {
        var fact = new Fact();
        fact.parse(factArray[i]);
        factGroup.items.push(fact);
    }
    return factGroup;
}
function parseActionGroup(container, json) {
    var actionGroup = new ActionGroup(container);
    var actionArray = json;
    for (var i = 0; i < actionArray.length; i++) {
        var action = Action.create(actionGroup, actionArray[i]["@type"]);
        action.parse(actionArray[i]);
        actionGroup.actions.push(action);
    }
    return actionGroup;
}
function parseSection(container, json) {
    var section = new Container(container, ["Section"]);
    section.textContrast = TextContrast.DarkOnLight;
    if (json["startGroup"] === true) {
        section.addElement(new Separator(section));
    }
    var textBlock = new TextBlock(section);
    textBlock.text = json["title"];
    textBlock.textSize = TextSize.Large;
    section.addElement(textBlock);
    if (json["style"] == "emphasis") {
        section.backgroundColor = "#F8F8F8";
        section.padding = Spacing.Normal;
    }
    if (json["activityTitle"] != undefined || json["activitySubtitle"] != undefined ||
        json["activityText"] != undefined || json["activityImage"] != undefined) {
        var activity = new Activity(container);
        activity.topSpacing = Spacing.Normal;
        activity.title = json["activityTitle"];
        activity.subtitle = json["activitySubtitle"];
        activity.text = json["activityText"];
        activity.imageUrl = json["activityImage"];
        activity.imageSize = stringToSize(json["activityImageSize"], Size.Small);
        activity.imageStyle = stringToPictureStyle(json["activityImageStyle"], PictureStyle.Person);
        section.addElement(activity);
    }
    if (json["heroImage"] != undefined) {
        var picture = new Picture(section);
        picture.topSpacing = Spacing.Normal;
        picture.size = Size.Auto;
        picture.url = json["heroImage"];
        section.addElement(picture);
    }
    var text = new TextBlock(section);
    text.text = json["text"];
    text.topSpacing = Spacing.Normal;
    section.addElement(text);
    if (json["facts"] != undefined) {
        var factGroup = parseFactGroup(section, json["facts"]);
        factGroup.topSpacing = Spacing.Normal;
        section.addElement(factGroup);
    }
    if (json["images"] != undefined) {
        var pictureGallery = parsePictureGallery(section, json["images"]);
        pictureGallery.topSpacing = Spacing.Normal;
        section.addElement(pictureGallery);
    }
    if (json["potentialAction"] != undefined) {
        var actionGroup = parseActionGroup(section, json["potentialAction"]);
        actionGroup.topSpacing = Spacing.Normal;
        section.addElement(actionGroup);
    }
    return section;
}
var MessageCard = (function () {
    function MessageCard() {
    }
    MessageCard.prototype.parse = function (json) {
        this.summary = json["summary"];
        this.themeColor = json["themeColor"];
        this._rootContainer = new Container(null);
        this._rootContainer.padding = Spacing.Normal;
        this._rootContainer.textContrast = TextContrast.DarkOnLight;
        var textBlock = new TextBlock(this._rootContainer);
        textBlock.text = json["title"];
        textBlock.textSize = TextSize.ExtraLarge;
        this._rootContainer.addElement(textBlock);
        textBlock = new TextBlock(this._rootContainer);
        textBlock.text = json["text"],
            textBlock.topSpacing = Spacing.Normal;
        this._rootContainer.addElement(textBlock);
        if (json["sections"] != undefined) {
            var sectionArray = json["sections"];
            for (var i = 0; i < sectionArray.length; i++) {
                var section = parseSection(this._rootContainer, sectionArray[i]);
                section.topSpacing = Spacing.Normal;
                this._rootContainer.addElement(section);
            }
        }
        if (json["potentialAction"] != undefined) {
            var actionGroup = parseActionGroup(this._rootContainer, json["potentialAction"]);
            this._rootContainer.addElement(actionGroup);
        }
    };
    MessageCard.prototype.render = function () {
        var element = document.createElement("div");
        if (isNullOrEmpty(this.themeColor)) {
            element.style.border = "1px solid #F1F1F1";
        }
        else {
            element.style.borderTop = "1px solid #F1F1F1";
            element.style.borderRight = "1px solid #F1F1F1";
            element.style.borderBottom = "1px solid #F1F1F1";
            element.style.borderLeft = "1px solid #" + this.themeColor;
        }
        appendChild(element, this._rootContainer.render());
        return element;
    };
    return MessageCard;
}());
//# sourceMappingURL=messageCard.js.map
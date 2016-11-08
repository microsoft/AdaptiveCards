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
        element.className = "activitySection";
        if (!isNullOrEmpty(this.imageUrl)) {
            var size = Picture.getPhysicalSize(this.imageSize);
            var imageSection = document.createElement("div");
            imageSection.className = "activityImage";
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
            contentSection.className = "activityContent";
            appendChild(contentSection, TextBlock.render(this.title, TextStyle.ActivityTitle));
            appendChild(contentSection, TextBlock.render(this.subtitle, TextStyle.ActivitySubtitle));
            appendChild(contentSection, TextBlock.render(this.text, TextStyle.ActivityText));
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
        var action = Action.create(actionGroup, actionArray[i]["type"]);
        action.parse(actionArray[i]);
        actionGroup.actions.push(action);
    }
    return actionGroup;
}
function parseSection(container, json) {
    var section = new Section(container, ["Section"]);
    if (json["startGroup"] === true) {
        section.addElement(new Separator(section));
    }
    section.addElement(TextBlock.create(section, json["title"], TextStyle.SectionTitle));
    this.style = stringToSectionStyle(json["style"], SectionStyle.Normal);
    if (json["activityTitle"] != undefined || json["activitySubtitle"] != undefined ||
        json["activityText"] != undefined || json["activityImage"] != undefined) {
        var activity = new Activity(this);
        activity.title = json["activityTitle"];
        activity.subtitle = json["activitySubtitle"];
        activity.text = json["activityText"];
        activity.imageUrl = json["activityImage"];
        activity.imageSize = stringToSize(json["activityImageSize"], Size.Small);
        activity.imageStyle = stringToPictureStyle(json["activityImageStyle"], PictureStyle.Person);
        section.addElement(activity);
    }
    if (json["heroImage"] != undefined) {
        var picture = parsePicture(section, json["heroImage"]);
        picture.size = Size.Auto;
        section.addElement(picture);
    }
    section.addElement(TextBlock.create(section, json["text"], TextStyle.SectionText));
    if (json["facts"] != undefined) {
        var factGroup = parseFactGroup(section, json["facts"]);
        section.addElement(factGroup);
    }
    if (json["images"] != undefined) {
        var pictureGallery = parsePictureGallery(section, json["images"]);
        section.addElement(pictureGallery);
    }
    if (json["potentialAction"] != undefined) {
        var actionGroup = parseActionGroup(section, json["potentialAction"]);
        section.addElement(actionGroup);
    }
    return section;
}
var SwiftCard = (function () {
    function SwiftCard() {
    }
    SwiftCard.prototype.parse = function (json) {
        this.summary = json["summary"];
        this.rootSection = new Section(null);
        this.rootSection.style = SectionStyle.Card;
        this.rootSection.themeColor = json["themeColor"];
        this.rootSection.addElement(TextBlock.create(this.rootSection, json["title"], TextStyle.CardTitle));
        if (json["sections"] != undefined) {
            var sectionArray = json["sections"];
            for (var i = 0; i < sectionArray.length; i++) {
                var section = parseSection(this.rootSection, sectionArray[i]);
                this.rootSection.addElement(section);
            }
        }
        this.rootSection.addElement(TextBlock.create(this.rootSection, json["text"], TextStyle.CardText));
        if (json["potentialAction"] != undefined) {
            var actionGroup = parseActionGroup(this.rootSection, json["potentialAction"]);
            this.rootSection.addElement(actionGroup);
        }
    };
    SwiftCard.prototype.render = function () {
        return this.rootSection.render();
    };
    return SwiftCard;
}());
//# sourceMappingURL=swiftcard.js.map
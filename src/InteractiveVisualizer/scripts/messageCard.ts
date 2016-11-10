class Activity extends CardElement {
    title: string;
    subtitle: string;
    text: string;
    imageUrl: string;
    imageSize: Size = Size.Medium;
    imageStyle: PictureStyle = PictureStyle.Person;

    render(): HTMLElement {
        let html: string = '';

        let element = document.createElement("div");
        element.style.display = "flex";

        if (!isNullOrEmpty(this.imageUrl)) {
            let size = Picture.getPhysicalSize(this.imageSize);

            let imageSection = document.createElement("div");
            imageSection.style.flex = "0 1 auto";
            imageSection.style.marginRight = "10px";
            imageSection.style.height = size.toString() + "px";

            let image = document.createElement("img");

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
            let contentSection = document.createElement("div");
            contentSection.style.flex = "1 1 auto";
            contentSection.style.marginTop = "-5px";
            appendChild(contentSection, TextBlock.render(this.title, TextSize.Normal, TextWeight.Normal, TextColor.Normal, TextContrast.DarkOnLight)); 
            appendChild(contentSection, TextBlock.render(this.subtitle, TextSize.Normal, TextWeight.Lighter, TextColor.Brighter, TextContrast.DarkOnLight));
            appendChild(contentSection, TextBlock.render(this.text, TextSize.Normal, TextWeight.Normal, TextColor.Normal, TextContrast.DarkOnLight));

            appendChild(element, contentSection)
        }

        return element;
    }

    getSpacingAfterThis(): number {
        return 16;
    }
}

function parsePicture(container: Container, json: any, defaultSize: Size = Size.Medium, defaultStyle: PictureStyle = PictureStyle.Normal): Picture {
    let picture = new Picture(container);

    picture.url = json["image"];
    picture.size = stringToSize(json["size"], defaultSize);

    return picture;
}

function parsePictureGallery(container: Container, json: any): PictureGallery {
    let pictureGallery = new PictureGallery(container);
    let pictureArray = json as Array<any>;

    for (var i = 0; i < pictureArray.length; i++) {
        let picture = parsePicture(container, pictureArray[i], Size.Large);

        pictureGallery.items.push(picture);
    }

    return pictureGallery;
}

function parseFactGroup(container: Container, json: any): FactGroup {
    let factGroup = new FactGroup(container);
    let factArray = json as Array<any>;

    for (var i = 0; i < factArray.length; i++) {
        let fact = new Fact();

        fact.parse(factArray[i]);

        factGroup.items.push(fact);
    }

    return factGroup;
}

function parseActionGroup(container: Container, json: any): ActionGroup {
    let actionGroup = new ActionGroup(container);
    let actionArray = json as Array<any>;

    for (var i = 0; i < actionArray.length; i++) {
        let action = Action.create(actionGroup, actionArray[i]["@type"]);

        action.parse(actionArray[i]);

        actionGroup.actions.push(action);
    }

    return actionGroup;
}

function parseSection(container: Container, json: any): Container {
    let section = new Container(container, [ "Section" ]);
    section.textContrast = TextContrast.DarkOnLight;

    if (json["startGroup"] === true) {
        section.addElement(new Separator(section));
    }

    section.addElement(
        TextBlock.create(
            section,
            json["title"],
            TextSize.Large,
            TextWeight.Normal,
            TextColor.Normal));

    if (json["style"] == "emphasis") {
        section.backgroundColor = "#F8F8F8";
        section.padding = Spacing.Normal;
    }

    if (json["activityTitle"] != undefined || json["activitySubtitle"] != undefined ||
        json["activityText"] != undefined || json["activityImage"] != undefined) {
        let activity: Activity = new Activity(this);

        activity.title = json["activityTitle"];
        activity.subtitle = json["activitySubtitle"];
        activity.text = json["activityText"];
        activity.imageUrl = json["activityImage"];
        activity.imageSize = stringToSize(json["activityImageSize"], Size.Small);
        activity.imageStyle = stringToPictureStyle(json["activityImageStyle"], PictureStyle.Person);

        section.addElement(activity);
    }

    if (json["heroImage"] != undefined) {
        let picture = new Picture(section);
        picture.size = Size.Auto;
        picture.url = json["heroImage"];

        section.addElement(picture);
    }

    section.addElement(
        TextBlock.create(
            section,
            json["text"],
            TextSize.Normal,
            TextWeight.Normal,
            TextColor.Normal));

    if (json["facts"] != undefined) {
        let factGroup = parseFactGroup(section, json["facts"]);

        section.addElement(factGroup);
    }

    if (json["images"] != undefined) {
        let pictureGallery = parsePictureGallery(section, json["images"]);

        section.addElement(pictureGallery);
    }

    if (json["potentialAction"] != undefined) {
        let actionGroup = parseActionGroup(section, json["potentialAction"]);

        section.addElement(actionGroup);
    }

    return section;
}

class MessageCard {
    private _rootSection: Container;

    summary: string;
    themeColor: string;

    parse(json: any) {
        this.summary = json["summary"];
        this.themeColor = json["themeColor"];

        this._rootSection = new Container(null);
        this._rootSection.padding = Spacing.Normal;
        this._rootSection.textContrast = TextContrast.DarkOnLight;

        this._rootSection.addElement(
            TextBlock.create(
                this._rootSection,
                json["title"],
                TextSize.ExtraLarge,
                TextWeight.Normal,
                TextColor.Normal));
        this._rootSection.addElement(
            TextBlock.create(
                this._rootSection,
                json["text"],
                TextSize.Normal,
                TextWeight.Normal,
                TextColor.Normal));

        if (json["sections"] != undefined) {
            let sectionArray = json["sections"] as Array<any>;

            for (var i = 0; i < sectionArray.length; i++) {
                let section = parseSection(this._rootSection, sectionArray[i]);

                this._rootSection.addElement(section);
            }
        }

        if (json["potentialAction"] != undefined) {
            let actionGroup = parseActionGroup(this._rootSection, json["potentialAction"]);

            this._rootSection.addElement(actionGroup);
        }
    }

    render(): HTMLElement {
        let element = document.createElement("div");

        if (isNullOrEmpty(this.themeColor)) {
            element.style.border = "1px solid #F1F1F1"
        }
        else {
            element.style.borderTop = "1px solid #F1F1F1";
            element.style.borderRight = "1px solid #F1F1F1";
            element.style.borderBottom = "1px solid #F1F1F1";
            element.style.borderLeft = "1px solid #" + this.themeColor;
        }

        appendChild(element, this._rootSection.render());

        return element;
    }
}
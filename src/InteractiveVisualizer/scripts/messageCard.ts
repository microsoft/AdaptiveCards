function parsePicture(container: Container, json: any, defaultSize: Size = Size.Medium, defaultStyle: PictureStyle = PictureStyle.Normal): Picture {
    let picture = new Picture(container);

    picture.url = json["image"];
    picture.size = Size.parse(json["size"], defaultSize);

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

    if (json["startGroup"] === true) {
        section.addElement(new Separator(section));
    }

    let textBlock = new TextBlock(section);
    textBlock.text = json["title"];
    textBlock.textSize = TextSize.Large;

    section.addElement(textBlock);

    if (json["style"] == "emphasis") {
        section.backgroundColor = "#F8F8F8";
    }

    if (json["activityTitle"] != undefined || json["activitySubtitle"] != undefined ||
        json["activityText"] != undefined || json["activityImage"] != undefined) {

        let columnGroup = new ColumnGroup(container);

        // Image column
        if (json["activityImage"] != null) {
            let column = columnGroup.addColumn();
            column.size = Size.Auto;

            let picture = new Picture(column);
            picture.size = Size.Small;
            picture.style = PictureStyle.Person;
            picture.url = json["activityImage"];

            column.addElement(picture);
        }

        // Text column
        let column = columnGroup.addColumn();
        column.size = Size.Stretch;

        if (json["activityTitle"] != null) {
            let textBlock = new TextBlock(column);
            textBlock.text = json["activityTitle"];

            column.addElement(textBlock);
        }

        if (json["activitySubtitle"] != null) {
            let textBlock = new TextBlock(column);
            textBlock.text = json["activitySubtitle"];
            textBlock.textWeight = TextWeight.Lighter;
            textBlock.isSubtle = true;
            textBlock.topSpacing = Spacing.None;

            column.addElement(textBlock);
        }

        if (json["activityText"] != null) {
            let textBlock = new TextBlock(column);
            textBlock.text = json["activityText"];
            textBlock.topSpacing = Spacing.None;

            column.addElement(textBlock);
        }

        section.addElement(columnGroup);
    }

    if (json["heroImage"] != undefined) {
        let picture = new Picture(section);
        picture.size = Size.Auto;
        picture.url = json["heroImage"];

        section.addElement(picture);
    }

    let text = new TextBlock(section);
    text.text = json["text"];

    section.addElement(text);

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
    private _rootContainer: Container;

    summary: string;
    themeColor: string;

    parse(json: any) {
        this.summary = json["summary"];
        this.themeColor = json["themeColor"];

        this._rootContainer = new Container(null);
        this._rootContainer.topSpacing = Spacing.None;

        if (json["title"] != null) {
            let textBlock = new TextBlock(this._rootContainer);
            textBlock.text = json["title"];
            textBlock.textSize = TextSize.ExtraLarge;

            this._rootContainer.addElement(textBlock);
        }

        if (json["text"] != null) {
            let textBlock = new TextBlock(this._rootContainer);
            textBlock.text = json["text"],

            this._rootContainer.addElement(textBlock);
        }

        if (json["sections"] != undefined) {
            let sectionArray = json["sections"] as Array<any>;

            for (var i = 0; i < sectionArray.length; i++) {
                let section = parseSection(this._rootContainer, sectionArray[i]);

                if (i == 0 && this._rootContainer.elementCount == 0) {
                    section.topSpacing = Spacing.None;
                }

                this._rootContainer.addElement(section);
            }
        }

        if (json["potentialAction"] != undefined) {
            let actionGroup = parseActionGroup(this._rootContainer, json["potentialAction"]);

            this._rootContainer.addElement(actionGroup);
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
            element.style.borderLeft = "3px solid #" + this.themeColor;
        }

        let renderedContainer = this._rootContainer.internalRender();
        renderedContainer.className = "rootContainer";

        appendChild(element, renderedContainer);

        return element;
    }
}
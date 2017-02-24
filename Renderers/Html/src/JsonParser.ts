import * as Adaptive from "./CardElements";
import * as Enums from "./Enumerations";

export class JsonParser {
    static parseBaseAction(json: any, action: Adaptive.Action) {
        action.name = json["title"];        
    }

    static parseExternalAction(json: any, action: Adaptive.ExternalAction) {
        JsonParser.parseBaseAction(json, action);
    }

    static parseActionOpenUrl(json: any, action: Adaptive.ActionOpenUrl) {
        JsonParser.parseExternalAction(json, action);

        action.url = json["url"];
    }

    static parseActionHttp(json: any, action: Adaptive.ActionHttp) {
        JsonParser.parseExternalAction(json, action);
        
        action.url = json["url"];
        action.method = json["method"];
        action.body = json["body"];

        if (json["headers"] != null) {
            var jsonHeaders = json["headers"] as Array<any>;

            for (var i = 0; i < jsonHeaders.length; i++) {
                let httpHeader = new Adaptive.HttpHeader();

                httpHeader.name = jsonHeaders[i]["name"];
                httpHeader.value = jsonHeaders[i]["value"];

                action.headers.push(httpHeader);
            }
        }
    }

    static parseActionSubmit(json: any, action: Adaptive.ActionSubmit) {
        JsonParser.parseExternalAction(json, action);
    }

    static parseActionShowCard(
        json: any,
        action: Adaptive.ActionShowCard,
        parentContainer: Adaptive.Container) {
        JsonParser.parseBaseAction(json, action);
        
        action.card = new Adaptive.Container(parentContainer, "body");
        action.card.actionButtonStyle = Enums.ActionButtonStyle.Push;
        
        JsonParser.parseContainer(json["card"], action.card, "body");
    }

    static createAction(json: any, container: Adaptive.Container): Adaptive.Action {
        var result: Adaptive.Action;

        var actionType = json["type"];

        switch (actionType) {
            case Adaptive.ActionOpenUrl.TypeName:
                result = new Adaptive.ActionOpenUrl();
                JsonParser.parseActionOpenUrl(json, <Adaptive.ActionOpenUrl>result);

                break;
            case Adaptive.ActionHttp.TypeName:
                result = new Adaptive.ActionHttp();
                JsonParser.parseActionHttp(json, <Adaptive.ActionHttp>result);

                break;
            case Adaptive.ActionSubmit.TypeName:
                result = new Adaptive.ActionSubmit();
                JsonParser.parseActionSubmit(json, <Adaptive.ActionSubmit>result);

                break;
            case Adaptive.ActionShowCard.TypeName:
                result = new Adaptive.ActionShowCard();
                JsonParser.parseActionShowCard(json, <Adaptive.ActionShowCard>result, container);

                break;
            default:
                throw new Error("Unknown action type: " + actionType);
        }

        return result;
    }

    private static parseCardElement(json: any, cardElement: Adaptive.CardElement) {
        cardElement.speak = json["speak"];
        cardElement.horizontalAlignment = Enums.stringToHorizontalAlignment(json["horizontalAlignment"], Enums.HorizontalAlignment.Left);
    }

    private static parseTextBlock(json: any, textBlock: Adaptive.TextBlock) {
        JsonParser.parseCardElement(json, textBlock);

        textBlock.text = json["text"];
        textBlock.textSize = Enums.stringToTextSize(json["size"], Enums.TextSize.Normal);
        textBlock.textWeight = Enums.stringToTextWeight(json["weight"], Enums.TextWeight.Normal);
        textBlock.textColor = Enums.stringToTextColor(json["color"], Enums.TextColor.Default);
        textBlock.isSubtle = json["isSubtle"];
        textBlock.wrap = json["wrap"];

        var startParagraphJson = json["startParagraph"];
        
        if (startParagraphJson != undefined) {
            textBlock.startParagraph = startParagraphJson;
        }        
    }

    private static parseImage(json: any, image: Adaptive.Image) {
        JsonParser.parseCardElement(json, image);
        
        image.url = json["url"];
        image.style = Enums.stringToImageStyle(json["style"], Enums.ImageStyle.Normal);
        image.size = Enums.stringToSize(json["size"], Enums.Size.Medium);

        var selectActionJson = json["selectAction"];

        if (selectActionJson != undefined) {
            image.selectAction = JsonParser.createAction(json, image.container);
        }
    }

    private static parseImageSet(json: any, imageSet: Adaptive.ImageSet) {
        JsonParser.parseCardElement(json, imageSet);
        
        imageSet.imageSize = Enums.stringToSize(json["imageSize"], Enums.Size.Medium);

        if (json["images"] != null) {
            let jsonImages = json["images"] as Array<any>;

            for (let i = 0; i < jsonImages.length; i++) {
                var image = new Adaptive.Image(imageSet.container);

                image.size = imageSet.imageSize;
                image.url = jsonImages[i]["url"];

                imageSet.images.push(image);
            }
        }
    }

    private static parseFactSet(json: any, factSet: Adaptive.FactSet) {
        JsonParser.parseCardElement(json, factSet);
        
        if (json["facts"] != null) {
            var jsonFacts = json["facts"] as Array<any>;

            for (var i = 0; i < jsonFacts.length; i++) {
                let fact = new Adaptive.Fact();

                fact.name = jsonFacts[i]["title"];
                fact.value = jsonFacts[i]["value"];
                fact.speak = jsonFacts[i]["speak"];

                factSet.facts.push(fact);
            }
        }
    }

    private static parseActionCollection(json: any, actions: Adaptive.ActionCollection) {
        var jsonActions = json as Array<any>;

        for (var i = 0; i < jsonActions.length; i++) {
            var action = JsonParser.createAction(jsonActions[i], actions.container);

            actions.items.push(action);
        }
    }

    private static parseContainer(
        json: any,
        container: Adaptive.Container,
        itemsCollectionPropertyName: string = "items",
        forbiddenItemTypes: string[] = null) {
        JsonParser.parseCardElement(json, container);

        container.backgroundImageUrl = json["backgroundImage"];
        container.backgroundColor = json["backgroundColor"];
        container.isGroupStart = json["isGroupStart"];

        container.textColor = Enums.stringToTextColor(json["textColor"], Enums.TextColor.Default);

        if (json[itemsCollectionPropertyName] != null) {
            let items = json[itemsCollectionPropertyName] as Array<any>;

            for (let i = 0; i < items.length; i++) {
                let elementType = items[i]["type"];

                if (forbiddenItemTypes == null || forbiddenItemTypes.indexOf(elementType) == 0) {
                    let element = JsonParser.createElement(items[i], container);

                    container.addElement(element);
                }
                else {
                    throw new Error("Elements of type " + elementType + " are not allowed in this container.");
                }
            }
        }

        if (json["actions"] != undefined) {
            container.actions = new Adaptive.ActionCollection(container);

            JsonParser.parseActionCollection(json["actions"], container.actions);
        }

        var selectActionJson = json["selectAction"];

        if (selectActionJson != undefined) {
            container.selectAction = JsonParser.createAction(selectActionJson["type"], container);
        }
    }

    private static parseColumn(json: any, column: Adaptive.Column) {
        JsonParser.parseContainer(json, column);

        if (json["size"] === "auto") {
            column.weight = 0;
        }
        else if (json["size"] === "stretch") {
            column.weight = -1;
        }
        else {
            column.weight = Number(json["size"]);
        }
    }

    private static parseColumnSet(json: any, columnSet: Adaptive.ColumnSet) {
        JsonParser.parseCardElement(json, columnSet);
        
        if (json["columns"] != null) {
            let jsonColumns = json["columns"] as Array<any>;

            for (let i = 0; i < jsonColumns.length; i++) {
                var column = new Adaptive.Column(columnSet.container);

                JsonParser.parseColumn(jsonColumns[i], column);

                columnSet.columns.push(column);
            }
        }
    }

    private static parseInput(json: any, input: Adaptive.Input) {
        JsonParser.parseCardElement(json, input);

        input.id = json["id"];
        input.defaultValue = json["value"];
    }

    private static parseInputText(json: any, input: Adaptive.InputText) {
        JsonParser.parseCardElement(json, input);

        input.maxLength = json["maxLength"];
        input.isMultiline = json["isMultiline"];
        input.placeholder = json["placeholder"];
    }

    private static parseInputNumber(json: any, input: Adaptive.InputNumber) {
        JsonParser.parseCardElement(json, input);

        input.min = json["min"];
        input.max = json["max"];
    }

    private static parseInputDate(json: any, input: Adaptive.InputDate) {
        JsonParser.parseCardElement(json, input);
    }

    private static parseInputTime(json: any, input: Adaptive.InputTime) {
        JsonParser.parseCardElement(json, input);
    }

    private static parseInputToggle(json: any, input: Adaptive.InputToggle) {
        JsonParser.parseCardElement(json, input);

        input.title = json["title"];
        input.valueOn = json["valueOn"];
        input.valueOff = json["valueOff"];
    }

    private static parseInputChoiceSet(json: any, input: Adaptive.InputChoiceSet) {
        JsonParser.parseCardElement(json, input);

        input.isCompact = !(json["style"] === "expanded");
        input.isMultiSelect = json["isMultiSelect"];
        input.placeholder = json["placeholder"];

        if (json["choices"] != undefined) {
            var choiceArray = json["choices"] as Array<any>;

            for (var i = 0; i < choiceArray.length; i++) {
                var choice = new Adaptive.Choice();

                choice.display = choiceArray[i]["display"];
                choice.value = choiceArray[i]["value"];

                input.choices.push(choice);
            }
        }
    }

    private static createElement(json: any, container: Adaptive.Container): Adaptive.CardElement {
        var result: Adaptive.CardElement;

        var elementType = json["type"];

        switch (elementType) {
            case Adaptive.Container.TypeName:
                result = new Adaptive.Container(container);
                JsonParser.parseContainer(json, <Adaptive.Container>result);

                break;
            case Adaptive.TextBlock.TypeName:
                result = new Adaptive.TextBlock(container);
                JsonParser.parseTextBlock(json, <Adaptive.TextBlock>result);

                break;
            case Adaptive.Image.TypeName:
                result = new Adaptive.Image(container);
                JsonParser.parseImage(json, <Adaptive.Image>result);

                break;
            case Adaptive.ImageSet.TypeName:
                result = new Adaptive.ImageSet(container);
                JsonParser.parseImageSet(json, <Adaptive.ImageSet>result);

                break;
            case Adaptive.FactSet.TypeName:
                result = new Adaptive.FactSet(container);
                JsonParser.parseFactSet(json, <Adaptive.FactSet>result);

                break;
            case Adaptive.ColumnSet.TypeName:
                result = new Adaptive.ColumnSet(container);
                JsonParser.parseColumnSet(json, <Adaptive.ColumnSet>result);

                break;
            case Adaptive.InputText.TypeName:
                result = new Adaptive.InputText(container);
                JsonParser.parseInputText(json, <Adaptive.InputText>result);

                break;
            case Adaptive.InputNumber.TypeName:
                result = new Adaptive.InputNumber(container);
                JsonParser.parseInputNumber(json, <Adaptive.InputNumber>result);

                break;
            case Adaptive.InputDate.TypeName:
                result = new Adaptive.InputDate(container);
                JsonParser.parseInputDate(json, <Adaptive.InputDate>result);

                break;
            case Adaptive.InputTime.TypeName:
                result = new Adaptive.InputTime(container);
                JsonParser.parseInputTime(json, <Adaptive.InputTime>result);

                break;
            case Adaptive.InputToggle.TypeName:
                result = new Adaptive.InputToggle(container);
                JsonParser.parseInputToggle(json, <Adaptive.InputToggle>result);

                break;
            case Adaptive.InputChoiceSet.TypeName:
                result = new Adaptive.InputChoiceSet(container);
                JsonParser.parseInputChoiceSet(json, <Adaptive.InputChoiceSet>result);

                break;
            default:
                throw new Error("Unknown element type: " + elementType);
        }

        return result;
    }

    static parse(json: any): Adaptive.AdaptiveCard {
        var card = new Adaptive.AdaptiveCard();

        JsonParser.parseContainer(json, card.root, "body");

        return card;
    }
}
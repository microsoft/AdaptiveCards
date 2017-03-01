import * as Adaptive from "./CardElements";
import * as Enums from "./Enumerations";
import * as Utils from "./Utils";

export class JsonParser {
    private _card: Adaptive.AdaptiveCard;

    private parseBaseAction(json: any, action: Adaptive.Action) {
        action.name = json["title"];        
    }

    private parseExternalAction(json: any, action: Adaptive.ActionExternal) {
        this.parseBaseAction(json, action);

        action.onExecute.subscribe(
            (a, args) => {
                this._card.executeAction(a);
            });
    }

    private parseActionOpenUrl(json: any, action: Adaptive.ActionOpenUrl) {
        this.parseExternalAction(json, action);

        action.url = json["url"];
    }

    private parseActionHttp(json: any, action: Adaptive.ActionHttp) {
        this.parseExternalAction(json, action);
        
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

    private parseActionSubmit(json: any, action: Adaptive.ActionSubmit) {
        this.parseExternalAction(json, action);
    }

    private parseActionShowCard(
        json: any,
        action: Adaptive.ActionShowCard,
        parentContainer: Adaptive.Container) {
        this.parseBaseAction(json, action);
        
        action.card = new Adaptive.Container(parentContainer, "body");
        action.card.actionButtonStyle = Enums.ActionButtonStyle.Push;
        
        this.parseContainer(json["card"], action.card, "body");
    }

    private createAction(json: any, container: Adaptive.Container): Adaptive.Action {
        var result: Adaptive.Action;

        var actionType = json["type"];

        switch (actionType) {
            case Adaptive.ActionOpenUrl.TypeName:
                result = new Adaptive.ActionOpenUrl();
                this.parseActionOpenUrl(json, <Adaptive.ActionOpenUrl>result);

                break;
            case Adaptive.ActionHttp.TypeName:
                result = new Adaptive.ActionHttp();
                this.parseActionHttp(json, <Adaptive.ActionHttp>result);

                break;
            case Adaptive.ActionSubmit.TypeName:
                result = new Adaptive.ActionSubmit();
                this.parseActionSubmit(json, <Adaptive.ActionSubmit>result);

                break;
            case Adaptive.ActionShowCard.TypeName:
                result = new Adaptive.ActionShowCard();
                this.parseActionShowCard(json, <Adaptive.ActionShowCard>result, container);

                break;
            default:
                throw new Error("Unknown action type: " + actionType);
        }

        return result;
    }

    private parseCardElement(json: any, cardElement: Adaptive.CardElement) {
        cardElement.speak = json["speak"];
        cardElement.horizontalAlignment = Enums.stringToHorizontalAlignment(json["horizontalAlignment"], Enums.HorizontalAlignment.Left);
    }

    private parseTextBlock(json: any, textBlock: Adaptive.TextBlock) {
        this.parseCardElement(json, textBlock);

        textBlock.text = json["text"];
        textBlock.textSize = Enums.stringToTextSize(json["size"], Enums.TextSize.Normal);
        textBlock.textWeight = Enums.stringToTextWeight(json["weight"], Enums.TextWeight.Normal);
        textBlock.textColor = Enums.stringToTextColor(json["color"], Enums.TextColor.Default);
        textBlock.isSubtle = json["isSubtle"];
        textBlock.wrap = json["wrap"];

        var isParagraphStartJson = json["isParagraphStart"];
        
        if (isParagraphStartJson != undefined) {
            textBlock.isParagraphStart = isParagraphStartJson;
        }
    }

    private parseImage(json: any, image: Adaptive.Image) {
        this.parseCardElement(json, image);
        
        image.url = json["url"];
        image.style = Enums.stringToImageStyle(json["style"], Enums.ImageStyle.Normal);
        image.size = Enums.stringToSize(json["size"], Enums.Size.Medium);

        var selectActionJson = json["selectAction"];

        if (selectActionJson != undefined) {
            image.selectAction = <Adaptive.ActionExternal>this.createAction(selectActionJson, image.container);
        }
    }

    private parseImageSet(json: any, imageSet: Adaptive.ImageSet) {
        this.parseCardElement(json, imageSet);
        
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

    private parseFactSet(json: any, factSet: Adaptive.FactSet) {
        this.parseCardElement(json, factSet);
        
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

    private parseActionCollection(json: any, actions: Adaptive.ActionCollection) {
        var jsonActions = json as Array<any>;

        for (var i = 0; i < jsonActions.length; i++) {
            var action = this.createAction(jsonActions[i], actions.container);

            actions.items.push(action);
        }
    }

    private parseContainer(
        json: any,
        container: Adaptive.Container,
        itemsCollectionPropertyName: string = "items",
        forbiddenItemTypes: string[] = null) {
        this.parseCardElement(json, container);

        container.backgroundImageUrl = json["backgroundImage"];
        container.backgroundColor = json["backgroundColor"];
        container.isGroupStart = json["isGroupStart"];

        container.textColor = Enums.stringToTextColor(json["textColor"], Enums.TextColor.Default);

        if (json[itemsCollectionPropertyName] != null) {
            let items = json[itemsCollectionPropertyName] as Array<any>;

            for (let i = 0; i < items.length; i++) {
                let elementType = items[i]["type"];

                if (forbiddenItemTypes == null || forbiddenItemTypes.indexOf(elementType) == 0) {
                    let element = this.createElement(items[i], container);

                    container.addElement(element);
                }
                else {
                    throw new Error("Elements of type " + elementType + " are not allowed in this container.");
                }
            }
        }

        if (json["actions"] != undefined) {
            container.actions = new Adaptive.ActionCollection(container);

            this.parseActionCollection(json["actions"], container.actions);
        }

        var selectActionJson = json["selectAction"];

        if (selectActionJson != undefined) {
            container.selectAction = <Adaptive.ActionExternal>this.createAction(selectActionJson, container);
        }
    }

    private parseColumn(json: any, column: Adaptive.Column) {
        this.parseContainer(json, column);

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

    private parseColumnSet(json: any, columnSet: Adaptive.ColumnSet) {
        this.parseCardElement(json, columnSet);
        
        if (json["columns"] != null) {
            let jsonColumns = json["columns"] as Array<any>;

            for (let i = 0; i < jsonColumns.length; i++) {
                var column = new Adaptive.Column(columnSet.container);

                this.parseColumn(jsonColumns[i], column);

                columnSet.columns.push(column);
            }
        }
    }

    private parseInput(json: any, input: Adaptive.Input) {
        this.parseCardElement(json, input);

        if (!Utils.isNullOrEmpty(input.id)) {
            this._card.allInputs.push(input);
        }

        input.id = json["id"];
        input.defaultValue = json["value"];
    }

    private parseInputText(json: any, input: Adaptive.InputText) {
        this.parseCardElement(json, input);

        input.maxLength = json["maxLength"];
        input.isMultiline = json["isMultiline"];
        input.placeholder = json["placeholder"];
    }

    private parseInputNumber(json: any, input: Adaptive.InputNumber) {
        this.parseCardElement(json, input);

        input.min = json["min"];
        input.max = json["max"];
    }

    private parseInputDate(json: any, input: Adaptive.InputDate) {
        this.parseCardElement(json, input);
    }

    private parseInputTime(json: any, input: Adaptive.InputTime) {
        this.parseCardElement(json, input);
    }

    private parseInputToggle(json: any, input: Adaptive.InputToggle) {
        this.parseCardElement(json, input);

        input.title = json["title"];
        input.valueOn = json["valueOn"];
        input.valueOff = json["valueOff"];
    }

    private parseInputChoiceSet(json: any, input: Adaptive.InputChoiceSet) {
        this.parseCardElement(json, input);

        input.isCompact = !(json["style"] === "expanded");
        input.isMultiSelect = json["isMultiSelect"];
        input.placeholder = json["placeholder"];

        if (json["choices"] != undefined) {
            var choiceArray = json["choices"] as Array<any>;

            for (var i = 0; i < choiceArray.length; i++) {
                var choice = new Adaptive.Choice();

                choice.title = choiceArray[i]["title"];
                choice.value = choiceArray[i]["value"];

                input.choices.push(choice);
            }
        }
    }

    private createElement(json: any, container: Adaptive.Container): Adaptive.CardElement {
        var result: Adaptive.CardElement;

        var elementType = json["type"];

        switch (elementType) {
            case Adaptive.Container.TypeName:
                result = new Adaptive.Container(container);
                this.parseContainer(json, <Adaptive.Container>result);

                break;
            case Adaptive.TextBlock.TypeName:
                result = new Adaptive.TextBlock(container);
                this.parseTextBlock(json, <Adaptive.TextBlock>result);

                break;
            case Adaptive.Image.TypeName:
                result = new Adaptive.Image(container);
                this.parseImage(json, <Adaptive.Image>result);

                break;
            case Adaptive.ImageSet.TypeName:
                result = new Adaptive.ImageSet(container);
                this.parseImageSet(json, <Adaptive.ImageSet>result);

                break;
            case Adaptive.FactSet.TypeName:
                result = new Adaptive.FactSet(container);
                this.parseFactSet(json, <Adaptive.FactSet>result);

                break;
            case Adaptive.ColumnSet.TypeName:
                result = new Adaptive.ColumnSet(container);
                this.parseColumnSet(json, <Adaptive.ColumnSet>result);

                break;
            case Adaptive.InputText.TypeName:
                result = new Adaptive.InputText(container);
                this.parseInputText(json, <Adaptive.InputText>result);

                break;
            case Adaptive.InputNumber.TypeName:
                result = new Adaptive.InputNumber(container);
                this.parseInputNumber(json, <Adaptive.InputNumber>result);

                break;
            case Adaptive.InputDate.TypeName:
                result = new Adaptive.InputDate(container);
                this.parseInputDate(json, <Adaptive.InputDate>result);

                break;
            case Adaptive.InputTime.TypeName:
                result = new Adaptive.InputTime(container);
                this.parseInputTime(json, <Adaptive.InputTime>result);

                break;
            case Adaptive.InputToggle.TypeName:
                result = new Adaptive.InputToggle(container);
                this.parseInputToggle(json, <Adaptive.InputToggle>result);

                break;
            case Adaptive.InputChoiceSet.TypeName:
                result = new Adaptive.InputChoiceSet(container);
                this.parseInputChoiceSet(json, <Adaptive.InputChoiceSet>result);

                break;
            default:
                throw new Error("Unknown element type: " + elementType);
        }

        return result;
    }

    parse(json: any): Adaptive.AdaptiveCard {
        this._card = new Adaptive.AdaptiveCard();

        this.parseContainer(json, this._card.root, "body");

        return this._card;
    }
}
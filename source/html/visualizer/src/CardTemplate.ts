import * as Adaptive from "microsoft-adaptivecards";

export type ImagePlacement = "top" | "right";

export class TemplateDemo {
    category: string;
    title: string;
    attribution: string;
    imageUrl: string;
    imagePlacement: ImagePlacement;
    body: Adaptive.Container;

    parse(json: any) {
        this.category = json["category"];
        this.title = json["title"];
        this.attribution = json["attribution"];
        this.imageUrl = json["imageUrl"];
        this.imagePlacement = json["imagePlacement"];

        if (!this.imagePlacement) {
            this.imagePlacement = "top";
        }
        
        this.body = new Adaptive.Container();
        this.body.parse(json, "body");
    }

    convertToAdaptive(): Adaptive.AdaptiveCard {
        var card = new Adaptive.AdaptiveCard();
        var contentContainer: Adaptive.Container;

        if (this.imageUrl) {
            if (this.imagePlacement === "top") {
                var topContainer = new Adaptive.Container();
                topContainer.pixelHeight = 200;
                topContainer.backgroundImage = new Adaptive.BackgroundImage();
                topContainer.backgroundImage.url = this.imageUrl;

                card.addItem(topContainer);

                contentContainer = new Adaptive.Container();
                contentContainer.spacing = "padding";

                card.addItem(contentContainer);
            }
            else {
                var columnSet = new Adaptive.ColumnSet();

                var column = new Adaptive.Column();
                column.width = "stretch";
                columnSet.addColumn(column);

                contentContainer = column;

                column = new Adaptive.Column();
                column.spacing = "padding";
                column.pixelWidth = 200;
                column.backgroundImage = new Adaptive.BackgroundImage();
                column.backgroundImage.url = this.imageUrl;

                columnSet.addColumn(column);

                card.addItem(columnSet);
            }
        }

        if (this.category) {
            var textBlock = new Adaptive.TextBlock();
            textBlock.size = "small";
            textBlock.text = this.category.toUpperCase();
            textBlock.wrap = true;

            contentContainer.addItem(textBlock);
        }

        if (this.title) {
            var textBlock = new Adaptive.TextBlock();
            textBlock.size = "medium";
            textBlock.text = this.title;
            textBlock.weight = "bolder";
            textBlock.spacing = "small";
            textBlock.wrap = true;
            
            contentContainer.addItem(textBlock);
        }

        contentContainer.addItem(this.body);

        if (this.attribution) {
            var textBlock = new Adaptive.TextBlock();
            textBlock.text = this.attribution;
            textBlock.isSubtle = true;
            textBlock.wrap = true;
            
            contentContainer.addItem(textBlock);
        }

        return card;
    }
}
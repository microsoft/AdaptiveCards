
import * as Constants from './constants';

/**
 * @description - This builder creates adaptive card from `HeroCard` / `ThumbnailCard` .
 * @param  cardContent  - Content of the card to be converted
 * @param  type  - Type of the card.
 */
export const buildAdaptiveCard = (cardContent, type) => {

    const AdaptiveCard = {
        "type": Constants.TypeAdaptiveCard,
        "version": Constants.AdaptiveCardVersion,
        "body": [],
        "actions": []
    }

    const ColumnSet = {
        "type": Constants.TypeColumnSet,
        "columns": [
            {
                "type": Constants.TypeColumn,
                "width": Constants.ThumbNailWidth,
                "items": []
            },
            {
                "type": Constants.TypeColumn,
                "width": Constants.WidthStretch,
                "items": []
            }
        ]
    }

    if (cardContent && type) {
        switch (type) {
            case Constants.TypeHeroCard:
                pushTextBlocks(cardContent, AdaptiveCard.body);
                pushImages(cardContent, AdaptiveCard.body);
                pushActions(cardContent, AdaptiveCard.actions);
                break;
            case Constants.TypeThumbnailCard:
                pushImages(cardContent, ColumnSet.columns[0].items);
                pushTextBlocks(cardContent, ColumnSet.columns[1].items);
                pushActions(cardContent, ColumnSet.columns[1].items, true);
                AdaptiveCard.body.push(ColumnSet);
                delete AdaptiveCard.actions;
                break;
            default:
                elementsContainer = [];
                break;
        }

        /**
         * `tap` to container `selectAction`
         */
        if (cardContent.tap && cardContent.tap.type && cardContent.tap.value) {
            const body = AdaptiveCard.body;
            AdaptiveCard.body = [];
            const containerBody = {};
            containerBody.type = Constants.TypeContainer;
            containerBody.items = body;
            containerBody.selectAction = cardAction(cardContent.tap);
            AdaptiveCard.body[0] = containerBody;
        }

    }
    return AdaptiveCard;
}

/**
 * @description - This method pushes text blocks to the adaptive card container.
 * @param  cardContent  - Content of the card to be converted.
 * @param  textBlockContainer  - Container where the tex blocks to be inserted
 */
pushTextBlocks = (cardContent, textBlockContainer) => {
    if (isNotEmpty(cardContent.title))
        textBlockContainer.push(textBlock(cardContent.title, Constants.TypeTitle));
    if (isNotEmpty(cardContent.subtitle))
        textBlockContainer.push(textBlock(cardContent.subtitle, Constants.TypeSubTitle));
    if (isNotEmpty(cardContent.text))
        textBlockContainer.push(textBlock(cardContent.text));
    return textBlockContainer;
}

/**
 * @description - This method pushes images to the adaptive card container.
 * @param  cardContent  - Content of the card to be converted.
 * @param  imageContainer  - Container where the images to be inserted
 */
pushImages = (cardContent, imageContainer) => {
    if (cardContent.images && cardContent.images.length > 0) {
        cardContent.images.forEach(image => {
            imageContainer.push(cardImage(image));
        })
    }
}

/**
 * @description - This method pushes actions to the adaptive card container.
 * @param  cardContent  - Content of the card to be converted.
 * @param  actionContainer  - Container where the actions to be inserted
 * @param  isNested  - A boolean decides where the actions need to be added in the container
 */
 pushActions = (cardContent, actionContainer, isNested) => {
    if (cardContent.buttons && cardContent.buttons.length > 0) {
        if (!isNested) {
            cardContent.buttons.forEach(button => {
                actionContainer.push(cardAction(button));
            })
        } else {
            const nestedContainer = {
                "type": Constants.TypeColumnSet
            }
            const columns = [];
            cardContent.buttons.forEach(button => {
                const column = {
                    "type": Constants.TypeColumn,
                    "items": []
                };
                column.items.push(cardAction(button));
                columns.push(column);
            })
            nestedContainer.columns = columns;
            actionContainer.push(nestedContainer);;
        }
    }
}

/**
 * @description - Convert card types `title, subtitle and text` to Adaptive card type format.
 * @param  content  - The content to be displayed
 * @param  type  - Element type to be converted.
 */
textBlock = (content, type) => {
    const textBlock = {};
    textBlock.type = Constants.TypeTextBlock;
    textBlock.text = content;
    switch (type) {
        case Constants.TypeTitle:
            textBlock.size = Constants.SizeMedium;
            textBlock.weight = Constants.WeightBold;
            break;
        case Constants.TypeSubTitle:
            textBlock.isSubtle = true;
            textBlock.wrap = true;
            break;
        default:
            textBlock.wrap = true;
            break;
    }
    return textBlock;

}

/**
 * @description - Convert `button` to `actions`
 * @param  button  - button content.
 */
cardAction = (button) => {
    const action = Object.assign({}, button);
    if (button.type === Constants.TypeOpenUrl) {
        action.type = Constants.ActionOpenUrl;
        action.url = button.value;
    } else {
        action.data = {
            "type": button.type,
            "data": button.value
        };
        action.type = Constants.ActionSubmit;
    }
    delete action.value;
    return action;
}

/**
 * @description - Format `image` properties to adaptive card format
 * @param  image  - image content.
 */
cardImage = (image) => {
    const cardImage = Object.assign({}, image);
    cardImage.type = Constants.ImageType;
    cardImage.size = Constants.ImageSize;
    if (image.tap) {
        cardImage.selectAction = cardAction(image.tap);
        delete cardImage.tap;
    }
    return cardImage;
}

/**
 * @description - Checks whether a given value is empty or not.
 * @param  param  - param need to be checked.
 */
isNotEmpty = (param) => {
    return param && param !== Constants.EmptyString && param.length > 0;
}
import * as Models from './index'
import { ElementType } from '../utils/enums'
import * as Utils from '../utils/util'

export class ModelFactory {
    static createElement(parent, payload) {
        if (!payload) {
            return undefined;
        }
        switch (payload.type) {
            case ElementType.Image:
                return new Models.ImageModel(parent, payload);
            case ElementType.TextBlock:
                return new Models.TextBlockModel(parent, payload);
            case ElementType.RichTextBlock:
                return new Models.RichTextBlockModel(parent, payload);
            case ElementType.Column:
                return new Models.ColumnModel(parent, payload);
            case ElementType.ColumnSet:
                return new Models.ColumnSetModel(parent, payload);
            case ElementType.Container:
                return new Models.ContainerModel(parent, payload);
            case ElementType.FactSet:
                return new Models.FactSetModel(parent, payload);
            case ElementType.ImageSet:
                return new Models.ImageSetModel(parent, payload);
            case ElementType.TextInput:
                return new Models.TextInputModel(parent, payload);
            case ElementType.DateInput:
                return new Models.DateInputModel(parent, payload);
            case ElementType.TimeInput:
                return new Models.TimeInputModel(parent, payload);
            case ElementType.NumberInput:
                return new Models.NumberInputModel(parent, payload);
            case ElementType.ChoiceSetInput:
                return new Models.ChoiceSetModel(parent, payload);
            case ElementType.ToggleInput:
                return new Models.ToggleInputModel(parent, payload);
            case ElementType.AdaptiveCard:
                return new Models.AdaptiveCardModel(parent, payload);
            case ElementType.ActionOpenUrl:
                return new Models.OpenUrlActionModel(parent, payload);
            case ElementType.ActionSubmit:
                return new Models.SubmitActionModel(parent, payload);
            case ElementType.ActionShowCard:
                return new Models.ShowCardActionModel(parent, payload);
            case ElementType.ActionToggleVisibility:
                return new Models.ToggleVisibilityActionModel(parent, payload);
            case ElementType.ActionSet:
                return new Models.ActionSetModel(parent, payload);
            default:
                return ModelFactory.checkForFallBack(parent,payload);
        }
    }
    static createGroup(parent, payload) {
        let modelGroup = [];
        if (payload && payload.length > 0) {
            payload.forEach((item) => {
                let model = ModelFactory.createElement(parent, item);
                if (model) {
                    modelGroup.push(model);
                }
            });
        }
        return modelGroup;
    }

    static checkForFallBack (parent, payload) {
        if (!Utils.isNullOrEmpty(payload.fallback)){
            if (payload.fallback !== "drop"){
                return ModelFactory.createElement(parent, payload.fallback);
            }
            else{
                return undefined;
            }  
        }
        else{
                parent.isFallbackActivated = true;
                return undefined;
            }  
    }
}
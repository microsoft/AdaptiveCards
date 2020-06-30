import * as Models from './index'
import { ElementType } from '../utils/enums'
import * as Utils from '../utils/util'
import { HostConfigManager, HostCapabilities } from '../utils/host-config';

export class ModelFactory {
    static createElement(payload, parent) {
        if (!payload) {
            return undefined;
        }
        if(payload.requires) {
            let requirements = new HostCapabilities(payload.requires)
            let hostCapabilities = HostConfigManager.getHostConfig().getHostCapabilities()
            if(requirements.satisfied(hostCapabilities)) {
                return this.getElement(payload, parent)
            } else {
                return ModelFactory.checkForFallBack(payload, parent);
            }
        } else {
            return this.getElement(payload, parent)
        }
        
    }

    static getElement(payload, parent) {
        if (!payload) {
            return undefined;
        }
        switch (payload.type) {
            case ElementType.Image:
                return new Models.ImageModel(payload, parent);
            case ElementType.Media:
                return new Models.MediaModel(payload, parent);
            case ElementType.TextBlock:
                return new Models.TextBlockModel(payload, parent);
            case ElementType.RichTextBlock:
                return new Models.RichTextBlockModel(payload, parent);
            case ElementType.Column:
                return new Models.ColumnModel(payload, parent);
            case ElementType.ColumnSet:
                return new Models.ColumnSetModel(payload, parent);
            case ElementType.Container:
                return new Models.ContainerModel(payload, parent);
            case ElementType.FactSet:
                return new Models.FactSetModel(payload, parent);
            case ElementType.ImageSet:
                return new Models.ImageSetModel(payload, parent);
            case ElementType.TextInput:
                return new Models.TextInputModel(payload, parent);
            case ElementType.DateInput:
                return new Models.DateInputModel(payload, parent);
            case ElementType.TimeInput:
                return new Models.TimeInputModel(payload, parent);
            case ElementType.NumberInput:
                return new Models.NumberInputModel(payload, parent);
            case ElementType.ChoiceSetInput:
                return new Models.ChoiceSetModel(payload, parent);
            case ElementType.ToggleInput:
                return new Models.ToggleInputModel(payload, parent);
            case ElementType.AdaptiveCard:
                return new Models.AdaptiveCardModel(payload, parent);
            case ElementType.ActionOpenUrl:
                return new Models.OpenUrlActionModel(payload, parent);
            case ElementType.ActionSubmit:
                return new Models.SubmitActionModel(payload, parent);
            case ElementType.ActionShowCard:
                return new Models.ShowCardActionModel(payload, parent);
            case ElementType.ActionToggleVisibility:
                return new Models.ToggleVisibilityActionModel(payload, parent);
            case ElementType.ActionSet:
                return new Models.ActionSetModel(payload, parent);
            default:
                return ModelFactory.checkForFallBack(payload, parent);
        }
    }
    static createGroup(payload, parent) {
        let modelGroup = [];
        if (payload && payload.length > 0) {
            payload.forEach((item) => {
                let model = ModelFactory.createElement(item, parent);
                if (model) {
                    modelGroup.push(model);
                }
            });
        }
        return modelGroup;
    }

    static checkForFallBack (payload, parent) {
        if (!Utils.isNullOrEmpty(payload.fallback)){
            if (payload.fallback !== "drop"){
                return ModelFactory.createElement(payload.fallback, parent);
            }
            else{
                return undefined;
            }  
        } else {
            return undefined;
        }  
    }
}
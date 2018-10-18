export declare const adaptiveCardSchema: {
    "$schema": string;
    "id": string;
    "type": string;
    "title": string;
    "additionalProperties": boolean;
    "allOf": {
        "$ref": string;
    }[];
    "properties": {
        "version": {
            "type": string;
            "description": string;
        };
        "minVersion": {
            "type": string;
            "description": string;
        };
        "fallbackText": {
            "type": string;
            "description": string;
        };
        "speak": {
            "type": string;
            "description": string;
        };
    };
    "required": string[];
    "definitions": {
        "Action": {
            "anyOf": {
                "$ref": string;
            }[];
        };
        "Action.OpenUrl": {
            "additionalProperties": boolean;
            "description": string;
            "properties": {
                "title": {
                    "type": string;
                    "description": string;
                };
                "type": {
                    "type": string;
                    "description": string;
                    "enum": string[];
                };
                "url": {
                    "type": string;
                    "description": string;
                };
            };
            "required": string[];
            "type": string;
        };
        "Action.ShowCard": {
            "type": string;
            "additionalProperties": boolean;
            "description": string;
            "properties": {
                "type": {
                    "type": string;
                    "description": string;
                    "enum": string[];
                };
                "title": {
                    "type": string;
                    "description": string;
                };
                "card": {
                    "$ref": string;
                };
            };
            "required": string[];
        };
        "Action.Submit": {
            "type": string;
            "additionalProperties": boolean;
            "description": string;
            "properties": {
                "type": {
                    "type": string;
                    "description": string;
                    "enum": string[];
                };
                "title": {
                    "type": string;
                    "description": string;
                };
                "data": {
                    "type": string[];
                    "description": string;
                };
            };
            "required": string[];
        };
        "Actions": {
            "additionalItems": boolean;
            "items": {
                "$ref": string;
            };
            "type": string;
        };
        "AdaptiveCard": {
            "additionalProperties": boolean;
            "type": string;
            "description": string;
            "properties": {
                "type": {
                    "type": string;
                    "description": string;
                    "enum": string[];
                };
                "actions": {
                    "description": string;
                    "$ref": string;
                };
                "body": {
                    "description": string;
                    "$ref": string;
                };
            };
            "required": string[];
        };
        "CardElement": {
            "additionalProperties": boolean;
            "properties": {
                "type": {
                    "type": string;
                };
                "id": {
                    "type": string;
                    "description": string;
                };
                "spacing": {
                    "$ref": string;
                };
                "separator": {
                    "type": string;
                    "description": string;
                    "default": boolean;
                };
            };
            "required": string[];
        };
        "CardElements": {
            "type": string;
            "additionalItems": boolean;
            "items": {
                "anyOf": {
                    "$ref": string;
                }[];
            }[];
        };
        "Input.Choice": {
            "type": string;
            "description": string;
            "additionalProperties": boolean;
            "properties": {
                "type": {
                    "type": string;
                    "enum": string[];
                };
                "title": {
                    "type": string;
                    "description": string;
                };
                "value": {
                    "type": string;
                    "description": string;
                };
            };
            "required": string[];
        };
        "ChoiceInputStyle": {
            "type": string;
            "description": string;
            "enum": string[];
        };
        "Column": {
            "additionalProperties": boolean;
            "type": string;
            "description": string;
            "allOf": {
                "$ref": string;
            }[];
            "properties": {
                "items": {
                    "description": string;
                    "$ref": string;
                };
                "selectAction": {
                    "description": string;
                    "$ref": string;
                };
                "width": {
                    "type": string[];
                    "description": string;
                };
                "type": {
                    "type": string;
                    "description": string;
                    "enum": string[];
                };
            };
            "required": string[];
        };
        "ColumnSet": {
            "additionalProperties": boolean;
            "type": string;
            "description": string;
            "allOf": {
                "$ref": string;
            }[];
            "properties": {
                "columns": {
                    "type": string;
                    "description": string;
                    "items": {
                        "$ref": string;
                    };
                };
                "selectAction": {
                    "$ref": string;
                    "description": string;
                };
                "type": {
                    "type": string;
                    "description": string;
                    "enum": string[];
                };
            };
        };
        "Container": {
            "additionalProperties": boolean;
            "type": string;
            "description": string;
            "allOf": {
                "$ref": string;
            }[];
            "properties": {
                "items": {
                    "description": string;
                    "$ref": string;
                };
                "selectAction": {
                    "description": string;
                    "$ref": string;
                };
                "style": {
                    "type": string;
                    "description": string;
                    "enum": string[];
                };
                "type": {
                    "type": string;
                    "description": string;
                    "enum": string[];
                };
            };
            "required": string[];
        };
        "Fact": {
            "additionalProperties": boolean;
            "type": string;
            "description": string;
            "properties": {
                "type": {
                    "type": string;
                    "enum": string[];
                };
                "title": {
                    "type": string;
                    "description": string;
                };
                "value": {
                    "type": string;
                    "description": string;
                };
            };
            "required": string[];
        };
        "FactSet": {
            "additionalProperties": boolean;
            "type": string;
            "description": string;
            "allOf": {
                "$ref": string;
            }[];
            "properties": {
                "facts": {
                    "type": string;
                    "description": string;
                    "items": {
                        "$ref": string;
                    };
                };
                "type": {
                    "type": string;
                    "description": string;
                    "enum": string[];
                };
            };
            "required": string[];
        };
        "HorizontalAlignment": {
            "type": string;
            "description": string;
            "enum": string[];
        };
        "Image": {
            "additionalProperties": boolean;
            "type": string;
            "description": string;
            "allOf": {
                "$ref": string;
            }[];
            "properties": {
                "altText": {
                    "type": string;
                    "description": string;
                };
                "horizontalAlignment": {
                    "$ref": string;
                };
                "selectAction": {
                    "description": string;
                    "$ref": string;
                };
                "size": {
                    "type": string;
                    "$ref": string;
                };
                "style": {
                    "$ref": string;
                };
                "type": {
                    "type": string;
                    "description": string;
                    "enum": string[];
                };
                "url": {
                    "type": string;
                    "description": string;
                };
            };
            "required": string[];
        };
        "ImageSet": {
            "additionalProperties": boolean;
            "type": string;
            "description": string;
            "allOf": {
                "$ref": string;
            }[];
            "properties": {
                "images": {
                    "type": string;
                    "description": string;
                    "items": {
                        "$ref": string;
                    };
                };
                "imageSize": {
                    "$ref": string;
                };
                "type": {
                    "type": string;
                    "description": string;
                    "enum": string[];
                };
            };
            "required": string[];
        };
        "ImageSize": {
            "type": string;
            "description": string;
            "default": string;
            "enum": string[];
        };
        "ImageStyle": {
            "type": string;
            "description": string;
            "enum": string[];
        };
        "Input.ChoiceSet": {
            "additionalProperties": boolean;
            "type": string;
            "description": string;
            "allOf": {
                "$ref": string;
            }[];
            "properties": {
                "choices": {
                    "type": string;
                    "description": string;
                    "items": {
                        "$ref": string;
                    };
                };
                "id": {
                    "type": string;
                    "description": string;
                };
                "isMultiSelect": {
                    "type": string;
                    "description": string;
                    "default": boolean;
                };
                "style": {
                    "$ref": string;
                };
                "type": {
                    "description": string;
                    "enum": string[];
                    "type": string;
                };
                "value": {
                    "type": string;
                    "description": string;
                };
            };
            "required": string[];
        };
        "Input.Date": {
            "additionalProperties": boolean;
            "type": string;
            "description": string;
            "allOf": {
                "$ref": string;
            }[];
            "properties": {
                "id": {
                    "type": string;
                    "description": string;
                };
                "max": {
                    "type": string;
                    "description": string;
                };
                "min": {
                    "type": string;
                    "description": string;
                };
                "placeholder": {
                    "type": string;
                    "description": string;
                };
                "type": {
                    "type": string;
                    "description": string;
                    "enum": string[];
                };
                "value": {
                    "type": string;
                    "description": string;
                };
            };
            "required": string[];
        };
        "Input.Number": {
            "additionalProperties": boolean;
            "type": string;
            "description": string;
            "allOf": {
                "$ref": string;
            }[];
            "properties": {
                "id": {
                    "type": string;
                    "description": string;
                };
                "max": {
                    "type": string;
                    "description": string;
                };
                "min": {
                    "type": string;
                    "description": string;
                };
                "placeholder": {
                    "type": string;
                    "description": string;
                };
                "type": {
                    "type": string;
                    "description": string;
                    "enum": string[];
                };
                "value": {
                    "type": string;
                    "description": string;
                };
            };
            "required": string[];
        };
        "Input.Text": {
            "additionalProperties": boolean;
            "type": string;
            "description": string;
            "allOf": {
                "$ref": string;
            }[];
            "properties": {
                "id": {
                    "type": string;
                    "description": string;
                };
                "isMultiline": {
                    "type": string;
                    "description": string;
                };
                "maxLength": {
                    "type": string;
                    "description": string;
                };
                "placeholder": {
                    "type": string;
                    "description": string;
                };
                "style": {
                    "$ref": string;
                };
                "type": {
                    "type": string;
                    "description": string;
                    "enum": string[];
                };
                "value": {
                    "type": string;
                    "description": string;
                };
            };
            "required": string[];
        };
        "Input.Time": {
            "additionalProperties": boolean;
            "type": string;
            "description": string;
            "allOf": {
                "$ref": string;
            }[];
            "properties": {
                "id": {
                    "type": string;
                    "description": string;
                };
                "max": {
                    "type": string;
                    "description": string;
                };
                "min": {
                    "type": string;
                    "description": string;
                };
                "placeholder": {
                    "type": string;
                    "description": string;
                };
                "type": {
                    "type": string;
                    "description": string;
                    "enum": string[];
                };
                "value": {
                    "type": string;
                    "description": string;
                };
            };
            "required": string[];
        };
        "Input.Toggle": {
            "additionalProperties": boolean;
            "type": string;
            "description": string;
            "allOf": {
                "$ref": string;
            }[];
            "properties": {
                "id": {
                    "type": string;
                    "description": string;
                };
                "title": {
                    "type": string;
                    "description": string;
                };
                "type": {
                    "type": string;
                    "description": string;
                    "enum": string[];
                };
                "value": {
                    "type": string;
                    "description": string;
                };
                "valueOff": {
                    "type": string;
                    "description": string;
                };
                "valueOn": {
                    "type": string;
                    "description": string;
                };
            };
            "required": string[];
        };
        "TextBlock": {
            "additionalProperties": boolean;
            "type": string;
            "description": string;
            "allOf": {
                "$ref": string;
            }[];
            "properties": {
                "color": {
                    "type": string;
                    "description": string;
                    "enum": string[];
                };
                "horizontalAlignment": {
                    "$ref": string;
                };
                "isSubtle": {
                    "type": string;
                    "description": string;
                };
                "maxLines": {
                    "type": string;
                    "description": string;
                };
                "size": {
                    "type": string;
                    "description": string;
                    "enum": string[];
                };
                "text": {
                    "type": string;
                    "description": string;
                };
                "type": {
                    "type": string;
                    "description": string;
                    "enum": string[];
                };
                "weight": {
                    "type": string;
                    "description": string;
                    "enum": string[];
                };
                "wrap": {
                    "type": string;
                    "description": string;
                };
            };
            "required": string[];
        };
        "SeparatorStyle": {
            "type": string;
            "description": string;
            "properties": {
                "thickness": {
                    "type": string;
                    "description": string;
                    "enum": string[];
                };
                "color": {
                    "type": string;
                    "description": string;
                    "enum": string[];
                };
            };
        };
        "SpacingStyle": {
            "type": string;
            "description": string;
            "enum": string[];
        };
        "TextInputStyle": {
            "type": string;
            "description": string;
            "enum": string[];
        };
    };
};

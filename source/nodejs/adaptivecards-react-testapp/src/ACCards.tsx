import { AdaptiveCard } from 'adaptivecards-react'
import HostConfigDark from './host-conf-light.json'

const card = {
    "type": "AdaptiveCard",
    "body": [
        {
            "type": "TextBlock",
            "size": "Medium",
            "weight": "Bolder",
            "text": "${title}",
        },
        {
            "type": "ColumnSet",
            "columns": [
                {
                    "type": "Column",
                    "items": [
                        {
                            "type": "TextBlock",
                            "weight": "Bolder",
                            "text": "${creator.name}",
                            "wrap": true,
                        },
                    ],
                    "width": "stretch"
                }
            ]
        },
    ],
    "$schema": "http://adaptivecards.io/schemas/adaptive-card.json",
    "version": "1.3"
};

const CardWithHostConfigFromProperty = () => (<AdaptiveCard payload={card} hostConfig={HostConfigDark} />);

export const ACCards = () => {
    return (<div>
        <CardWithHostConfigFromProperty />
    </div>);
};

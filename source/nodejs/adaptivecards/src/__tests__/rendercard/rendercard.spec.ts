import { renderCard } from "../../rendercard";
import { IAdaptiveCard } from "../../schema";
import { AdaptiveCard } from "../../adaptivecards";

test('Render card works', () => {

    let card: IAdaptiveCard = {
        "type": "AdaptiveCard",
        "version": "1.0",
        "body": [
            {
                "type": "TextBlock",
                "text": "Hello world"
            }
        ]        
    };

    let hostConfig = {
        "fontFamily": "Segoe UI"
    };


    const html1 = renderCard(card);
    const html2 = renderCard(card, {
        hostConfig: hostConfig,        
        onExecuteAction: function (a) { alert(JSON.stringify(a)); }
    });

    
    expect(html1).toEqual(expect.anything());
})
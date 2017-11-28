import { renderCard } from "../../rendercard";

test('Render card works', () => {

    let card = {
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
        onAction: function (a) { alert(JSON.stringify(a)); }
    });

    
    expect(html1).toEqual(expect.anything());
})
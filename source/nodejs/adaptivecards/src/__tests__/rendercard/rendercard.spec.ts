import { render } from "../../render";

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

    const html1 = render(card);
    const html2 = render(card, {
        hostConfig: hostConfig,
        onAction: function (a) { alert(JSON.stringify(a)); }
    });

    
    expect(html1).toEqual(expect.anything());
})
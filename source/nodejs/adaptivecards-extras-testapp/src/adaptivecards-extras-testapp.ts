import { AdaptiveCard, GlobalRegistry } from "adaptivecards";
import * as ACExtras from "adaptivecards-extras"
import { Table } from "adaptivecards-extras";

let testCard = {
    type: "AdaptiveCard",
    version: "1.0",
    body: [
        {
            type: "TextBlock",
            text: "Adaptive Card Extras test card"
        },
        {
            type: "Table",
            columns: [
                {
                    weight: 1,
                    header: "Column 1"
                },
                {
                    weight: 2,
                    header: "Column 2"
                }
            ],
            rows: [
                {
                    cells: [
                        {
                            items: [
                                {
                                    type: "TextBlock",
                                    text: "Row 1, cell 1"
                                }
                            ]
                        },
                        {
                            items: [
                                {
                                    type: "TextBlock",
                                    text: "Row 1, cell 2"
                                }
                            ]
                        }
                    ]
                },
                {
                    cells: [
                        {
                            items: [
                                {
                                    type: "TextBlock",
                                    text: "Row 2, cell 1"
                                }
                            ]
                        },
                        {
                            items: [
                                {
                                    type: "TextBlock",
                                    text: "Row 2, cell 2"
                                }
                            ]
                        }
                    ]
                }
            ]
        }
    ]
}

window.onload = function() {
    GlobalRegistry.elements.register("Table", Table);

    let card = new AdaptiveCard();
    card.parse(testCard);

    document.getElementById("cardHost").appendChild(card.render());
}
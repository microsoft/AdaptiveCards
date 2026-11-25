// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
import { AdaptiveCard, FactSet } from "../../card-elements";

test("FactSet should be instantiated", () => {
    const factSet = new FactSet();
    expect(factSet).toEqual(expect.anything());
});

test("FactSet applies hostConfig.factSet.spacing as padding-top, not margin-top, on tr", () => {
    const card = new AdaptiveCard();
    card.parse({
        "type": "AdaptiveCard",
        "version": "1.0",
        "body": [
            {
                "type": "FactSet",
                "facts": [
                    { "title": "First", "value": "1" },
                    { "title": "Second", "value": "2" }
                ]
            }
        ]
    });

    const rendered = card.render();
    const rows = rendered?.querySelectorAll("tr");

    expect(rows?.length).toEqual(2);

    // margin-top on <tr> is ignored by browsers, so the fix must not rely on it
    expect(rows?.[1].style.marginTop).toEqual("");

    const secondRowCells = rows?.[1].querySelectorAll("td");
    secondRowCells?.forEach((cell) => {
        expect(cell.style.paddingTop).toEqual("10px");
    });
});

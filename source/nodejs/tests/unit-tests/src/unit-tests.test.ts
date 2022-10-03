import * as AdaptiveCards from "adaptivecards";
import * as ACData from "adaptivecards-templating";
import { readFileSync } from "fs";

describe("test Text property on TextBlock", () => {
    it("UnitTest1", () => {
        const textBlock = new AdaptiveCards.TextBlock();
        textBlock.text = "Some text";
        expect(textBlock.text).toBe("Some text");
    });

    it("UnitTest2", () => {
        const textBlock = new AdaptiveCards.TextBlock();
        textBlock.text = "Some text";
        const textBlockJson = textBlock.toJSON();
        expect('{"type":"TextBlock","text":"Some text"}').toBe(JSON.stringify(textBlockJson));
    });
});

const helloOutput = {
    "type": "AdaptiveCard",
    "version": "1.0",
    "body": [ 
        { 
            "type": "TextBlock", 
            "text": "Hello Adaptive Cards!" 
        } 
    ]
};

const helloThemeOutput = {
    "type": "AdaptiveCard",
    "version": "1.0",
    "body": [ 
        { 
            "type": "TextBlock", 
            "text": "Hello Adaptive Cards! You're using the Light theme!" 
        } 
    ]
};

describe("Test Templating Library", () => {
    it("BasicTemplateOnlyRoot", () => {
        const templatePayload = {
            "type": "AdaptiveCard",
            "version": "1.0",
            "body": [
                {
                    "type": "TextBlock",
                    "text": "Hello ${name}!"
                }
            ]
        };
                
        const root = {
            "name": "Adaptive Cards"
        };		

        runTest(templatePayload, helloOutput, root);
    })

    it("BasicTemplateOnlyHost", () => {
        const templatePayload = {
            "type": "AdaptiveCard",
            "version": "1.0",
            "body": [
                {
                    "type": "TextBlock",
                    "text": "Hello Adaptive Cards! You're using the ${$host.WindowsTheme} theme!"
                }
            ]
        };
                
        const host = {
            "WindowsTheme": "Light"
        }
        
        runTest(templatePayload, helloThemeOutput, undefined, host);
    });

    it("BasicTemplateBoth", () => {
        const templatePayload = {
            "type": "AdaptiveCard",
            "version": "1.0",
            "body": [
                {
                    "type": "TextBlock",
                    "text": "Hello ${name}! You're using the ${$host.WindowsTheme} theme!"
                }
            ]
        };
                
        const root = {
            "name": "Adaptive Cards"
        };
        const host = {
            "WindowsTheme": "Light"
        }

        runTest(templatePayload, helloThemeOutput, root, host);
    });

    it("HostAsString", () => {
        const templatePayload = {
            "type": "AdaptiveCard",
            "version": "1.0",
            "body": [
                {
                    "type": "TextBlock",
                    "text": "Hello ${$host}!"
                }
            ]
        };
                
        const host = "Adaptive Cards";

        runTest(templatePayload, helloOutput, undefined, host);
    });

    it("HostAsArray", () => {
        const templatePayload = {
            "type": "AdaptiveCard",
            "version": "1.0",
            "body": [
                {
                    "type": "TextBlock",
                    "text": "Hello ${$host[0]}! You're using the ${$host[1].WindowsTheme} theme!"
                }
            ]
        };

        const host = [ "Adaptive Cards", {"WindowsTheme": "Light"}]

        runTest(templatePayload, helloThemeOutput, undefined, host);

    });

    it("ComplexTemplate", () => {
        runTest(loadFile("template-test-resources/complex-template.json"),
            loadFile("template-test-resources/complex-template.output.json"),
            loadFile("template-test-resources/complex-template.data.json"));
    });

    it("ComplexTemplateWithHost", () => {
        runTest(loadFile("template-test-resources/complex-template-host.json"),
            loadFile("template-test-resources/complex-template-host.output.json"),
            loadFile("template-test-resources/complex-template-host.data.json"),
            loadFile("template-test-resources/complex-template-host.host.json"));
    });

    it("TemplatingVersionSuccess", () => {
        runTest(loadFile("template-test-resources/version-template-success.json"),
            loadFile("template-test-resources/version-template-success.output.json"));           
    });

    it("TemplatingVersionFail", () => {
        runTest(loadFile("template-test-resources/version-template-fail.json"),
            loadFile("template-test-resources/version-template-fail-invalid.output.json"));
    });

    it("TemplateVersionInvalid", () => {
        runTest(loadFile("template-test-resources/version-template-invalid.json"),
            loadFile("template-test-resources/version-template-fail-invalid.output.json"));
    });

    it("TemplateWhenIsNotExpression", () => {
        const templatePayload = {
            "type": "AdaptiveCard",
            "body": [
                {
                    "type": "TextBlock",
                    "size": "Medium",
                    "weight": "Bolder",
                    "text": "${title}",
                    "$when": "isNotExpression"
                }
            ],
            "$schema": "http://adaptivecards.io/schemas/adaptive-card.json",
            "version": "1.5"
        };

        const expectedOutput = {
            "type": "AdaptiveCard",
            "body": [],
            "$schema": "http://adaptivecards.io/schemas/adaptive-card.json",
            "version": "1.5"
        };

        runTest(templatePayload, expectedOutput, undefined, undefined);
    });

    it("TemplateWhenIsInvalidExpression", () => {
        const templatePayload = {
            "type": "AdaptiveCard",
            "body": [
                {
                    "type": "TextBlock",
                    "size": "Medium",
                    "weight": "Bolder",
                    "text": "${title}",
                    "$when": "${invalidExpression}"
                }
            ],
            "$schema": "http://adaptivecards.io/schemas/adaptive-card.json",
            "version": "1.5"
        };

        const expectedOutput = {
            "type": "AdaptiveCard",
            "body": [],
            "$schema": "http://adaptivecards.io/schemas/adaptive-card.json",
            "version": "1.5"
        };

        runTest(templatePayload, expectedOutput, undefined, undefined);
    });

    it("TemplateWhenIsNotExpressionWithLog", () => {
        const templatePayload = {
            "type": "AdaptiveCard",
            "body": [
                {
                    "type": "TextBlock",
                    "size": "Medium",
                    "weight": "Bolder",
                    "text": "${title}",
                    "$when": "isNotExpression"
                }
            ],
            "$schema": "http://adaptivecards.io/schemas/adaptive-card.json",
            "version": "1.5"
        };

        const expectedOutput = {
            "type": "AdaptiveCard",
            "body": [],
            "$schema": "http://adaptivecards.io/schemas/adaptive-card.json",
            "version": "1.5"
        };

        let template = new ACData.Template(templatePayload);

        let context = {
            $root: undefined
        };

        let card = template.expand(context);

        expect(card).toStrictEqual(expectedOutput);

        let errorLog = template.getLastTemplateExpansionWarnings();
        let expectedWarning = "WARN: isNotExpression is not an Adaptive Expression. The $when condition has been set to false by default.";

        expect(errorLog[0]).toStrictEqual(expectedWarning);
    });

    it("TemplateWhenIsInvalidExpressionWithLog", () => {
        const templatePayload = {
            "type": "AdaptiveCard",
            "body": [
                {
                    "type": "TextBlock",
                    "size": "Medium",
                    "weight": "Bolder",
                    "text": "${title}",
                    "$when": "${invalidExpression}"
                }
            ],
            "$schema": "http://adaptivecards.io/schemas/adaptive-card.json",
            "version": "1.5"
        };

        const expectedOutput = {
            "type": "AdaptiveCard",
            "body": [],
            "$schema": "http://adaptivecards.io/schemas/adaptive-card.json",
            "version": "1.5"
        };

        let template = new ACData.Template(templatePayload);

        let context = {
            $root: undefined
        };

        let card = template.expand(context);

        expect(card).toStrictEqual(expectedOutput);

        let errorLog = template.getLastTemplateExpansionWarnings();
        let expectedWarning = "WARN: Unable to parse the Adaptive Expression invalidExpression. The $when condition has been set to false by default.";
        
        expect(errorLog[0]).toStrictEqual(expectedWarning);
    });
    
    it("TemplateWhenIsFalse", () => {
        const templatePayload = {
            "type": "AdaptiveCard",
            "$schema": "http://adaptivecards.io/schemas/adaptive-card.json",
            "version": "1.5",
            "body": [
                {
                    "type": "TextBlock",
                    "text": "New TextBlock",
                    "wrap": true,
                    "$when": "${equals(someproperty, true)}"
                }
            ]
        };

        const expectedOutput = {
            "type": "AdaptiveCard",
            "$schema": "http://adaptivecards.io/schemas/adaptive-card.json",
            "version": "1.5",
            "body": []
        };

        let template = new ACData.Template(templatePayload);

        let context = {
            $root: {
                "someproperty": false
            }
        };

        let card = template.expand(context);

        expect(card).toStrictEqual(expectedOutput);

        let errorLog = template.getLastTemplateExpansionWarnings();
        expect(errorLog.length).toStrictEqual(0);
    });
});

function runTest(templatePayload: any, expectedOutput: any, data?: any, host?: any) {
    let template = new ACData.Template(templatePayload);

    let context = {
        $root: data,
        $host: host
    };

    let card = template.expand(context);

    expect(card).toStrictEqual(expectedOutput);
}

function loadFile(filePath: string) {
    const dataObject = readFileSync(filePath, "utf8");
    return JSON.parse(dataObject);
}

import * as AdaptiveCards from "adaptivecards";
import * as ACData from "adaptivecards-templating";

var fs = require("fs");

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

describe("Test Templating Library", () => {
	it("BasicTemplate", () => {
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

		const expectedOutput = {
			"type": "AdaptiveCard",
			"version": "1.0",
			"body": [ 
				{ 
					"type": "TextBlock", 
					"text": "Hello Adaptive Cards!" 
				} 
			]
		};

		runTest(templatePayload, root, expectedOutput);
	})

	it("BasicTemplateWithHost", () => {
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
		
		const expectedOutput = {
			"type": "AdaptiveCard",
			"version": "1.0",
			"body": [ 
				{ 
					"type": "TextBlock", 
					"text": "Hello Adaptive Cards! You're using the Light theme!" 
				} 
			]
		};

		runTest(templatePayload, root, expectedOutput, host);
	});

	it("ComplexTemplate", () => {
		runTest(loadFile("template-test-resources/complex-template.json"),
			loadFile("template-test-resources/complex-template.data.json"),
			loadFile("template-test-resources/complex-template.output.json"));
	});

	it("ComplexTemplateWithHost", () => {
		runTest(loadFile("template-test-resources/complex-template-host.json"),
			loadFile("template-test-resources/complex-template-host.data.json"),
			loadFile("template-test-resources/complex-template-host.output.json"),
			loadFile("template-test-resources/complex-template-host.host.json"));
	});
});

function runTest(templatePayload: any, data: any, expectedOutput: any, host?: any) {
	let template = new ACData.Template(templatePayload);

	let context = {
		$root: data,
		$host: host
	};

	let card = template.expand(context);

	expect(card).toStrictEqual(expectedOutput);
}

function loadFile(filePath: string) {
	const dataObject = fs.readFileSync(filePath, "utf8");
	return JSON.parse(dataObject);
}

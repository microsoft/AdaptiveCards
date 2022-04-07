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
		
		let template = new ACData.Template(templatePayload);
		
		let context: ACData.IEvaluationContext = {
			$root: {
				"name": "Adaptive Cards"
			}
		};
		
		let card = template.expand(context);

		const expectedOutput = {
			"type": "AdaptiveCard",
			"version": "1.0",
			"body": [ 
				{ 
					"type": "TextBlock", 
					"text": "Hello Adaptive Cards!" 
				} 
			]
		}

		expect(card).toStrictEqual(expectedOutput);
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
		
		let template = new ACData.Template(templatePayload);
		
		let context: ACData.IEvaluationContext = {
			$root: {
				"name": "Adaptive Cards"
			},
			$host: {
				"WindowsTheme": "Light"
			}
		};
		
		let card = template.expand(context);

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

		expect(card).toStrictEqual(expectedOutput);
	});

	it("ComplexTemplate", () => {
		const templateObject = fs.readFileSync("template-test-resources/complex-template.json", "utf8");
		const dataObject = fs.readFileSync("template-test-resources/complex-template.data.json", "utf8");
		const outputObject = fs.readFileSync("template-test-resources/complex-template.output.json", "utf8");

		const templatePayload = JSON.parse(templateObject);
		const inputData = JSON.parse(dataObject);
		const expectedOutput = JSON.parse(outputObject);

		let template = new ACData.Template(templatePayload);

		let context = {
			$root: inputData
		};

		let card = template.expand(context);

		expect(card).toStrictEqual(expectedOutput);
	});

	it("ComplexTemplateWithHost", () => {
		const templateObject = fs.readFileSync("template-test-resources/complex-template-host.json", "utf8");
		const dataObject = fs.readFileSync("template-test-resources/complex-template-host.data.json", "utf8");
		const hostObject = fs.readFileSync("template-test-resources/complex-template-host.host.json", "utf8");
		const outputObject = fs.readFileSync("template-test-resources/complex-template-host.output.json", "utf8");

		const templatePayload = JSON.parse(templateObject);
		const inputData = JSON.parse(dataObject);
		const inputHostData = JSON.parse(hostObject);
		const expectedOutput = JSON.parse(outputObject);

		let template = new ACData.Template(templatePayload);

		let context = {
			$root: inputData,
			$host: inputHostData
		}

		let card = template.expand(context);

		expect(card).toStrictEqual(expectedOutput);
	});
});

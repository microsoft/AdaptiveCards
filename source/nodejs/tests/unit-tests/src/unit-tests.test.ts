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
		var inputPayload = fs.readFileSync("template-test-resources/basic-template.json", "utf8");
		var inputData = fs.readFileSync("template-test-resources/basic-template.data.json", "utf8");
		var expectedOutput = fs.readFileSync("template-test-resources/basic-template.output.json", "utf8");

		console.log(inputPayload.type);

		let template = new ACData.Template(inputPayload);

		let evaluationContext = {
			$root: inputData
		}

		let outputPayload = template.expand(evaluationContext);

		console.log(outputPayload);

		expect(outputPayload).toBe(expectedOutput);
	})

	it("ComplexTemplate", () => {

		var inputPayload = fs.readFileSync("template-test-resources/complex-template.json", "utf8");
		var inputData = fs.readFileSync("template-test-resources/complex-template.data.json", "utf8");
		var inputHostData = fs.readFileSync("template-test-resources/complex-template.host.json", "utf8");
		var expectedOutput = fs.readFileSync("template-test-resources/complex-template.output.json", "utf8");

		let template = new ACData.Template(inputPayload);

		let evaluationContext = {
			$root: inputData,
			$host: inputHostData
		}

		let outputPayload = template.expand(evaluationContext);

		expect(outputPayload).toBe(expectedOutput);
	});
});

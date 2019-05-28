var assert = require("assert");
var tschema = require("../lib/json-schema-with-types");

describe("Test transform", function () {
    it("Test description", function () {

		assertTransform({
			types: [
				{
					"type": "AdaptiveCard",
					"description": "An Adaptive Card."
				}
			],
			primaryTypeName: "AdaptiveCard",
			expected: {
				"$schema": "http://json-schema.org/draft-06/schema#",
				"id": "http://adaptivecards.io/schemas/adaptive-card.json",
				"type": "object",
				"description": "An Adaptive Card."
			}
		})
	});
	
	it("Test string property", function () {
		assertTransform({
			types: [
				{
					"type": "AdaptiveCard",
					"properties": {
						"version": {
							"type": "string",
							"description": "Minimum version this card requires.",
							"examples": [ "1.0", "1.1", "1.2" ]
						}
					}
				}
			],
			primaryTypeName: "AdaptiveCard",
			expected: {
				"$schema": "http://json-schema.org/draft-06/schema#",
				"id": "http://adaptivecards.io/schemas/adaptive-card.json",
				"type": "object",
				"properties": {
					"version": {
						"type": "string",
						"description": "Minimum version this card requires.",
						"examples": [ "1.0", "1.1", "1.2" ]
					}
				}
			}
		})
	});
	
	it("Test uri property", function () {
		assertTransform({
			types: [
				{
					"type": "AdaptiveCard",
					"properties": {
						"source": {
							"type": "uri",
							"description": "The source of the card."
						}
					}
				}
			],
			primaryTypeName: "AdaptiveCard",
			expected: {
				"$schema": "http://json-schema.org/draft-06/schema#",
				"id": "http://adaptivecards.io/schemas/adaptive-card.json",
				"type": "object",
				"properties": {
					"source": {
						"type": "string",
						"format": "uri",
						"description": "The source of the card."
					}
				}
			}
		})
	});
});


function assertTransform(options) {
	var transformed = tschema.transformTypes(options.types, options.primaryTypeName);

	assert.deepStrictEqual(transformed, options.expected, "Transform wasn't equal to expected");
}
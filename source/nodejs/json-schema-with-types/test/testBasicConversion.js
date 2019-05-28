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
	
	it("Test required property", function () {
		assertTransform({
			types: [
				{
					"type": "AdaptiveCard",
					"properties": {
						"version": {
							"type": "string",
							"description": "Minimum version this card requires.",
							"required": true
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
						"description": "Minimum version this card requires."
					}
				},
				"required": [
					"version"
				]
			}
		})
	});
	
	it("Test object property", function () {
		/*
			Things to call out...
				- Descriptions on types (in definitions) are explicitly dropped, since JSON schema doesn't support the concept of types vs properties
		*/
		assertTransform({
			types: [
				{
					"type": "AdaptiveCard",
					"properties": {
						"moreInfoAction": {
							"type": "Action.OpenUrl",
							"description": "Action to invoke when user wants more info"
						}
					}
				},
				{
					"type": "Action.OpenUrl",
					"description": "An open URL action",
					"properties": {
						"url": {
							"type": "uri",
							"description": "The url to open"
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
					"moreInfoAction": {
						"description": "Action to invoke when user wants more info",
						"$ref": "#/definitions/Action.OpenUrl"
					}
				},
				"definitions": {
					"Action.OpenUrl": {
						"type": "object",
						"properties": {
							"url": {
								"type": "string",
								"format": "uri",
								"description": "The url to open"
							}
						}
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
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
    })
});


function assertTransform(options) {
	var transformed = tschema.transformTypes(options.types, options.primaryTypeName);

	// Serialize into string
	var actual = JSON.stringify(transformed);

	// Serialize expected into string too
	var expected = JSON.stringify(options.expected);

	assert.equal(actual, expected, "Transform wasn't equal to expected");
}
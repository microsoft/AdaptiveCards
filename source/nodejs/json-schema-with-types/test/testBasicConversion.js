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
						"description": "An open URL action",
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

	
	
	it("Test extending classes", function () {
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
					"extends": "Action",
					"description": "An open URL action",
					"properties": {
						"url": {
							"type": "uri",
							"description": "The url to open"
						}
					}
				},
				{
					"type": "Action",
					"isAbstract": true,
					"description": "An action to invoke",
					"properties": {
						"title": {
							"type": "string",
							"description": "The title"
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
						"description": "An open URL action",
						"properties": {
							"url": {
								"type": "string",
								"format": "uri",
								"description": "The url to open"
							}
						},
						"allOf": [
							{
								"$ref": "#/definitions/Action"
							}
						]
					},
					"Action": {
						"type": "object",
						"description": "An action to invoke",
						"properties": {
							"title": {
								"type": "string",
								"description": "The title"
							}
						}
					},
					"ImplementationsOf.Action": {
						"anyOf": [
							{
								"properties": {
									"type": {
										"enum": [ "Action.OpenUrl" ]
									}
								},
								"required": [ "type" ],
								"allOf": [
									{
										"$ref": "#/definitions/Action.OpenUrl"
									}
								]
							}
						]
					}
				}
			}
		})
	});



	it("Test referencing base classes", function () {
		assertTransform({
			types: [
				{
					"type": "AdaptiveCard",
					"properties": {
						"moreInfoAction": {
							"type": "Action",
							"description": "Action to invoke when user wants more info"
						}
					}
				},
				{
					"type": "Action.OpenUrl",
					"extends": "Action",
					"properties": {
						"url": {
							"type": "uri"
						}
					}
				},
				{
					"type": "Action.Submit",
					"extends": "Action",
					"properties": {
						"data": {
							"type": "string"
						}
					}
				},
				{
					"type": "Action",
					"isAbstract": true,
					"properties": {
						"title": {
							"type": "string"
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
						"$ref": "#/definitions/ImplementationsOf.Action"
					}
				},
				"definitions": {
					"Action.OpenUrl": {
						"type": "object",
						"properties": {
							"url": {
								"type": "string",
								"format": "uri"
							}
						},
						"allOf": [
							{
								"$ref": "#/definitions/Action"
							}
						]
					},
					"Action.Submit": {
						"type": "object",
						"properties": {
							"data": {
								"type": "string"
							}
						},
						"allOf": [
							{
								"$ref": "#/definitions/Action"
							}
						]
					},
					"Action": {
						"type": "object",
						"properties": {
							"title": {
								"type": "string"
							}
						}
					},
					"ImplementationsOf.Action": {
						"anyOf": [
							{
								"properties": {
									"type": {
										"enum": [ "Action.OpenUrl" ]
									}
								},
								"required": [ "type" ],
								"allOf": [
									{
										"$ref": "#/definitions/Action.OpenUrl"
									}
								]
							},
							{
								"properties": {
									"type": {
										"enum": [ "Action.Submit" ]
									}
								},
								"required": [ "type" ],
								"allOf": [
									{
										"$ref": "#/definitions/Action.Submit"
									}
								]
							}
						]
					}
				}
			}
		})
	});


	it("Test uri or object property", function () {
		assertTransform({
			types: [
				{
					"type": "AdaptiveCard",
					"properties": {
						"backgroundImage": {
							"type": "uri|BackgroundImage"
						}
					}
				},
				{
					"type": "BackgroundImage",
					"properties": {
						"url": {
							"type": "uri"
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
					"backgroundImage": {
						"anyOf": [
							{
								"type": "string",
								"format": "uri"
							},
							{
								"$ref": "#/definitions/BackgroundImage"
							}
						]
					}
				},
				"definitions": {
					"BackgroundImage": {
						"type": "object",
						"properties": {
							"url": {
								"type": "string",
								"format": "uri"
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
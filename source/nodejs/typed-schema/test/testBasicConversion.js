// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
var assert = require("assert");
var tschema = require("../lib/typed-schema");

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
				"anyOf": [
					{
						"allOf": [
							{
								"$ref": "#/definitions/AdaptiveCard"
							}
						]
					}
				],
				"definitions": {
					"AdaptiveCard": {
						"type": "object",
						"additionalProperties": false,
						"description": "An Adaptive Card.",
						"properties": {
							"type": {
								"enum": [ "AdaptiveCard" ],
								"description": "Must be `AdaptiveCard`"
							}
						}
					}
				}
			}
		})
	});
	
	it("Test allow additional properties", function () {
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
			allowAdditionalProperties: true,
			expected: {
				"$schema": "http://json-schema.org/draft-06/schema#",
				"id": "http://adaptivecards.io/schemas/adaptive-card.json",
				"anyOf": [
					{
						"allOf": [
							{
								"$ref": "#/definitions/AdaptiveCard"
							}
						]
					}
				],
				"definitions": {
					"AdaptiveCard": {
						"type": "object",
						"properties": {
							"type": {
								"enum": [ "AdaptiveCard" ],
								"description": "Must be `AdaptiveCard`"
							},
							"version": {
								"type": "string",
								"description": "Minimum version this card requires.",
								"examples": [ "1.0", "1.1", "1.2" ]
							}
						}
					}
				}
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
				"anyOf": [
					{
						"allOf": [
							{
								"$ref": "#/definitions/AdaptiveCard"
							}
						]
					}
				],
				"definitions": {
					"AdaptiveCard": {
						"type": "object",
						"additionalProperties": false,
						"properties": {
							"type": {
								"enum": [ "AdaptiveCard" ],
								"description": "Must be `AdaptiveCard`"
							},
							"version": {
								"type": "string",
								"description": "Minimum version this card requires.",
								"examples": [ "1.0", "1.1", "1.2" ]
							}
						}
					}
				}
			}
		})
	});
	
	it("Test any property", function () {
		assertTransform({
			types: [
				{
					"type": "AdaptiveCard",
					"properties": {
						"version": {
							"type": "any"
						}
					}
				}
			],
			primaryTypeName: "AdaptiveCard",
			expected: {
				"$schema": "http://json-schema.org/draft-06/schema#",
				"id": "http://adaptivecards.io/schemas/adaptive-card.json",
				"anyOf": [
					{
						"allOf": [
							{
								"$ref": "#/definitions/AdaptiveCard"
							}
						]
					}
				],
				"definitions": {
					"AdaptiveCard": {
						"type": "object",
						"additionalProperties": false,
						"properties": {
							"type": {
								"enum": [ "AdaptiveCard" ],
								"description": "Must be `AdaptiveCard`"
							},
							"version": {
							}
						}
					}
				}
			}
		})
	});
	
	it("Test array of any property", function () {
		assertTransform({
			types: [
				{
					"type": "AdaptiveCard",
					"properties": {
						"version": {
							"type": "any[]"
						}
					}
				}
			],
			primaryTypeName: "AdaptiveCard",
			expected: {
				"$schema": "http://json-schema.org/draft-06/schema#",
				"id": "http://adaptivecards.io/schemas/adaptive-card.json",
				"anyOf": [
					{
						"allOf": [
							{
								"$ref": "#/definitions/AdaptiveCard"
							}
						]
					}
				],
				"definitions": {
					"AdaptiveCard": {
						"type": "object",
						"additionalProperties": false,
						"properties": {
							"type": {
								"enum": [ "AdaptiveCard" ],
								"description": "Must be `AdaptiveCard`"
							},
							"version": {
								"type": "array"
							}
						}
					}
				}
			}
		})
	});
	
	it("Test nullable property", function () {
		assertTransform({
			types: [
				{
					"type": "AdaptiveCard",
					"properties": {
						"version": {
							"type": "number?"
						}
					}
				}
			],
			primaryTypeName: "AdaptiveCard",
			expected: {
				"$schema": "http://json-schema.org/draft-06/schema#",
				"id": "http://adaptivecards.io/schemas/adaptive-card.json",
				"anyOf": [
					{
						"allOf": [
							{
								"$ref": "#/definitions/AdaptiveCard"
							}
						]
					}
				],
				"definitions": {
					"AdaptiveCard": {
						"type": "object",
						"additionalProperties": false,
						"properties": {
							"type": {
								"enum": [ "AdaptiveCard" ],
								"description": "Must be `AdaptiveCard`"
							},
							"version": {
								"anyOf": [
									{
										"type": "number"
									},
									{
										"type": "null"
									}
								]
							}
						}
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
				"anyOf": [
					{
						"allOf": [
							{
								"$ref": "#/definitions/AdaptiveCard"
							}
						]
					}
				],
				"definitions": {
					"AdaptiveCard": {
						"type": "object",
						"additionalProperties": false,
						"properties": {
							"type": {
								"enum": [ "AdaptiveCard" ],
								"description": "Must be `AdaptiveCard`"
							},
							"source": {
								"type": "string",
								"format": "uri",
								"description": "The source of the card."
							}
						}
					}
				}
			}
		})
	});
	
	it("Test uri reference property", function () {
		assertTransform({
			types: [
				{
					"type": "AdaptiveCard",
					"properties": {
						"source": {
							"type": "uri-reference",
							"description": "The source of the card."
						}
					}
				}
			],
			primaryTypeName: "AdaptiveCard",
			expected: {
				"$schema": "http://json-schema.org/draft-06/schema#",
				"id": "http://adaptivecards.io/schemas/adaptive-card.json",
				"anyOf": [
					{
						"allOf": [
							{
								"$ref": "#/definitions/AdaptiveCard"
							}
						]
					}
				],
				"definitions": {
					"AdaptiveCard": {
						"type": "object",
						"additionalProperties": false,
						"properties": {
							"type": {
								"enum": [ "AdaptiveCard" ],
								"description": "Must be `AdaptiveCard`"
							},
							"source": {
								"type": "string",
								"format": "uri-reference",
								"description": "The source of the card."
							}
						}
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
				"anyOf": [
					{
						"allOf": [
							{
								"$ref": "#/definitions/AdaptiveCard"
							}
						]
					}
				],
				"definitions": {
					"AdaptiveCard": {
						"type": "object",
						"additionalProperties": false,
						"properties": {
							"type": {
								"enum": [ "AdaptiveCard" ],
								"description": "Must be `AdaptiveCard`"
							},
							"version": {
								"type": "string",
								"description": "Minimum version this card requires."
							}
						},
						"required": [
							"version"
						]
					}
				}
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
				"anyOf": [
					{
						"allOf": [
							{
								"$ref": "#/definitions/AdaptiveCard"
							}
						]
					}
				],
				"definitions": {
					"AdaptiveCard": {
						"type": "object",
						"additionalProperties": false,
						"properties": {
							"type": {
								"enum": [ "AdaptiveCard" ],
								"description": "Must be `AdaptiveCard`"
							},
							"moreInfoAction": {
								"description": "Action to invoke when user wants more info",
								"$ref": "#/definitions/Action.OpenUrl"
							}
						}
					},
					"Action.OpenUrl": {
						"type": "object",
						"additionalProperties": false,
						"description": "An open URL action",
						"properties": {
							"type": {
								"enum": [ "Action.OpenUrl" ],
								"description": "Must be `Action.OpenUrl`"
							},
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
				"anyOf": [
					{
						"allOf": [
							{
								"$ref": "#/definitions/AdaptiveCard"
							}
						]
					}
				],
				"definitions": {
					"AdaptiveCard": {
						"type": "object",
						"additionalProperties": false,
						"properties": {
							"type": {
								"enum": [ "AdaptiveCard" ],
								"description": "Must be `AdaptiveCard`"
							},
							"moreInfoAction": {
								"description": "Action to invoke when user wants more info",
								"$ref": "#/definitions/Action.OpenUrl"
							}
						}
					},
					"Action.OpenUrl": {
						"type": "object",
						"additionalProperties": false,
						"description": "An open URL action",
						"properties": {
							"type": {
								"enum": [ "Action.OpenUrl" ],
								"description": "Must be `Action.OpenUrl`"
							},
							"url": {
								"type": "string",
								"format": "uri",
								"description": "The url to open"
							},
							"title": {} // We have to specify placeholders since additionalProperties=false doesn't allow extended properties
						},
						"allOf": [
							{
								"$ref": "#/definitions/Extendable.Action"
							}
						]
					},
					"Extendable.Action": {
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

	it("Test extending classes with overriding property", function () {
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
						},
						"title": {
							"type": "string|number",
							"description": "The title or number",
							"override": true
						}
					}
				},
				{
					"type": "Action",
					"isAbstract": true,
					"description": "An action to invoke",
					"properties": {
						"id": {
							"type": "string"
						},
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
				"anyOf": [
					{
						"allOf": [
							{
								"$ref": "#/definitions/AdaptiveCard"
							}
						]
					}
				],
				"definitions": {
					"AdaptiveCard": {
						"type": "object",
						"additionalProperties": false,
						"properties": {
							"type": {
								"enum": [ "AdaptiveCard" ],
								"description": "Must be `AdaptiveCard`"
							},
							"moreInfoAction": {
								"description": "Action to invoke when user wants more info",
								"$ref": "#/definitions/Action.OpenUrl"
							}
						}
					},
					"Action.OpenUrl": {
						"type": "object",
						"additionalProperties": false,
						"description": "An open URL action",
						"properties": {
							"type": {
								"enum": [ "Action.OpenUrl" ],
								"description": "Must be `Action.OpenUrl`"
							},
							"id": {
								"type": "string"
							},
							"url": {
								"type": "string",
								"format": "uri",
								"description": "The url to open"
							},
							"title": {
								"description": "The title or number",
								"anyOf": [
									{
										"type": "string"
									},
									{
										"type": "number"
									}
								]
							}
						} // It can't use #definition since JSON schema doesn't support overriding properties
					},
					"Extendable.Action": {
						"type": "object",
						"description": "An action to invoke",
						"properties": {
							"id": {
								"type": "string"
							},
							"title": {
								"type": "string",
								"description": "The title"
							}
						}
					},
					"ImplementationsOf.Action": {
						"anyOf": [
							{
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


	

	
	
	it("Test multiple depths of extending classes", function () {
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
					"extends": "Element",
					"isAbstract": true,
					"description": "An action to invoke",
					"properties": {
						"title": {
							"type": "string",
							"description": "The title"
						}
					}
				},
				{
					"type": "Element",
					"isAbstract": true,
					"properties": {
						"id": {
							"type": "string"
						}
					}
				}
			],
			primaryTypeName: "AdaptiveCard",
			expected: {
				"$schema": "http://json-schema.org/draft-06/schema#",
				"id": "http://adaptivecards.io/schemas/adaptive-card.json",
				"anyOf": [
					{
						"allOf": [
							{
								"$ref": "#/definitions/AdaptiveCard"
							}
						]
					}
				],
				"definitions": {
					"AdaptiveCard": {
						"type": "object",
						"additionalProperties": false,
						"properties": {
							"type": {
								"enum": [ "AdaptiveCard" ],
								"description": "Must be `AdaptiveCard`"
							},
							"moreInfoAction": {
								"description": "Action to invoke when user wants more info",
								"$ref": "#/definitions/Action.OpenUrl"
							}
						}
					},
					"Action.OpenUrl": {
						"type": "object",
						"additionalProperties": false,
						"description": "An open URL action",
						"properties": {
							"type": {
								"enum": [ "Action.OpenUrl" ],
								"description": "Must be `Action.OpenUrl`"
							},
							"url": {
								"type": "string",
								"format": "uri",
								"description": "The url to open"
							},
							"title": {}, // We have to specify placeholders since additionalProperties=false doesn't allow extended properties
							"id": {}
						},
						"allOf": [
							{
								"$ref": "#/definitions/Extendable.Action"
							}
						]
					},
					"Extendable.Action": {
						"type": "object",
						"description": "An action to invoke",
						"properties": {
							"title": {
								"type": "string",
								"description": "The title"
							},
							"id": {}
						},
						"allOf": [
							{
								"$ref": "#/definitions/Extendable.Element"
							}
						]
					},
					"Extendable.Element": {
						"type": "object",
						"properties": {
							"id": {
								"type": "string"
							}
						}
					},
					"ImplementationsOf.Action": {
						"anyOf": [
							{
								"required": [ "type" ],
								"allOf": [
									{
										"$ref": "#/definitions/Action.OpenUrl"
									}
								]
							}
						]
					},
					"ImplementationsOf.Element": {
						"anyOf": [
							{
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
				"anyOf": [
					{
						"allOf": [
							{
								"$ref": "#/definitions/AdaptiveCard"
							}
						]
					}
				],
				"definitions": {
					"AdaptiveCard": {
						"type": "object",
						"additionalProperties": false,
						"properties": {
							"type": {
								"enum": [ "AdaptiveCard" ],
								"description": "Must be `AdaptiveCard`"
							},
							"moreInfoAction": {
								"description": "Action to invoke when user wants more info",
								"$ref": "#/definitions/ImplementationsOf.Action"
							}
						}
					},
					"Action.OpenUrl": {
						"type": "object",
						"additionalProperties": false,
						"properties": {
							"type": {
								"enum": [ "Action.OpenUrl" ],
								"description": "Must be `Action.OpenUrl`"
							},
							"url": {
								"type": "string",
								"format": "uri"
							},
							"title": {}
						},
						"allOf": [
							{
								"$ref": "#/definitions/Extendable.Action"
							}
						]
					},
					"Action.Submit": {
						"type": "object",
						"additionalProperties": false,
						"properties": {
							"type": {
								"enum": [ "Action.Submit" ],
								"description": "Must be `Action.Submit`"
							},
							"data": {
								"type": "string"
							},
							"title": {}
						},
						"allOf": [
							{
								"$ref": "#/definitions/Extendable.Action"
							}
						]
					},
					"Extendable.Action": {
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
								"required": [ "type" ],
								"allOf": [
									{
										"$ref": "#/definitions/Action.OpenUrl"
									}
								]
							},
							{
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
				"anyOf": [
					{
						"allOf": [
							{
								"$ref": "#/definitions/AdaptiveCard"
							}
						]
					}
				],
				"definitions": {
					"AdaptiveCard": {
						"type": "object",
						"additionalProperties": false,
						"properties": {
							"type": {
								"enum": [ "AdaptiveCard" ],
								"description": "Must be `AdaptiveCard`"
							},
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
						}
					},
					"BackgroundImage": {
						"type": "object",
						"additionalProperties": false,
						"properties": {
							"type": {
								"enum": [ "BackgroundImage" ],
								"description": "Must be `BackgroundImage`"
							},
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

	


	it("Test shorthands", function () {
		assertTransform({
			types: [
				{
					"type": "AdaptiveCard",
					"properties": {
						"backgroundImage": {
							"type": "string",
							"description": "URL to image",
							"version": "1.2",
							"shorthands": [
								{
									"type": "number",
									"description": "ID of image from assets",
									"version": "1.1" // Yes, this shorthand property came BEFORE the other
								}
							]
						}
					}
				}
			],
			primaryTypeName: "AdaptiveCard",
			expected: {
				"$schema": "http://json-schema.org/draft-06/schema#",
				"id": "http://adaptivecards.io/schemas/adaptive-card.json",
				"anyOf": [
					{
						"allOf": [
							{
								"$ref": "#/definitions/AdaptiveCard"
							}
						]
					}
				],
				"definitions": {
					"AdaptiveCard": {
						"type": "object",
						"additionalProperties": false,
						"properties": {
							"type": {
								"enum": [ "AdaptiveCard" ],
								"description": "Must be `AdaptiveCard`"
							},
							"backgroundImage": {
								"description": "URL to image",
								"version": "1.2",
								"anyOf": [
									{
										"type": "string"
									},
									{
										"type": "number",
										"description": "ID of image from assets",
										"version": "1.1"
									}
								]
							}
						}
					}
				}
			}
		})
	});

	it("Test object shorthands", function () {
		assertTransform({
			types: [
				{
					"type": "AdaptiveCard",
					"properties": {
						"backgroundImage": {
							"type": "BackgroundImage",
							"description": "The background image to use"
						}
					}
				},
				{
					"type": "BackgroundImage",
					"properties": {
						"url": {
							"type": "string",
							"description": "The URL",
							"required": true
						},
						"fillMode": {
							"type": "string"
						}
					},
					"shorthand": "url"
				}
			],
			primaryTypeName: "AdaptiveCard",
			expected: {
				"$schema": "http://json-schema.org/draft-06/schema#",
				"id": "http://adaptivecards.io/schemas/adaptive-card.json",
				"anyOf": [
					{
						"allOf": [
							{
								"$ref": "#/definitions/AdaptiveCard"
							}
						]
					}
				],
				"definitions": {
					"AdaptiveCard": {
						"type": "object",
						"additionalProperties": false,
						"properties": {
							"type": {
								"enum": [ "AdaptiveCard" ],
								"description": "Must be `AdaptiveCard`"
							},
							"backgroundImage": {
								"$ref": "#/definitions/BackgroundImage",
								"description": "The background image to use"
							}
						}
					},
					"BackgroundImage": {
						"anyOf": [
							{
								"type": "string",
								"description": "The URL"
							},
							{
								"type": "object",
								"additionalProperties": false,
								"properties": {
									"type": {
										"enum": [ "BackgroundImage" ],
										"description": "Must be `BackgroundImage`"
									},
									"url": {
										"type": "string",
										"description": "The URL"
									}, "fillMode": {
										"type": "string"
									}
								},
								"required": [
									"url"
								]
							}
						]
					}
				}
			}
		})
	});


	it("Test array of objects property", function () {
		assertTransform({
			types: [
				{
					"type": "AdaptiveCard",
					"properties": {
						"actions": {
							"type": "Action.OpenUrl[]"
						}
					}
				},
				{
					"type": "Action.OpenUrl",
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
				"anyOf": [
					{
						"allOf": [
							{
								"$ref": "#/definitions/AdaptiveCard"
							}
						]
					}
				],
				"definitions": {
					"AdaptiveCard": {
						"type": "object",
						"additionalProperties": false,
						"properties": {
							"type": {
								"enum": [ "AdaptiveCard" ],
								"description": "Must be `AdaptiveCard`"
							},
							"actions": {
								"type": "array",
								"items": {
									"$ref": "#/definitions/Action.OpenUrl"
								}
							}
						}
					},
					"Action.OpenUrl": {
						"type": "object",
						"additionalProperties": false,
						"properties": {
							"type": {
								"enum": [ "Action.OpenUrl" ],
								"description": "Must be `Action.OpenUrl`"
							},
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


	it("Test array of string properties", function () {
		assertTransform({
			types: [
				{
					"type": "AdaptiveCard",
					"properties": {
						"titles": {
							"type": "string[]"
						}
					}
				}
			],
			primaryTypeName: "AdaptiveCard",
			expected: {
				"$schema": "http://json-schema.org/draft-06/schema#",
				"id": "http://adaptivecards.io/schemas/adaptive-card.json",
				"anyOf": [
					{
						"allOf": [
							{
								"$ref": "#/definitions/AdaptiveCard"
							}
						]
					}
				],
				"definitions": {
					"AdaptiveCard": {
						"type": "object",
						"additionalProperties": false,
						"properties": {
							"type": {
								"enum": [ "AdaptiveCard" ],
								"description": "Must be `AdaptiveCard`"
							},
							"titles": {
								"type": "array",
								"items": {
									"type": "string"
								}
							}
						}
					}
				}
			}
		})
	});


	it("Test array of base classes property", function () {
		assertTransform({
			types: [
				{
					"type": "AdaptiveCard",
					"properties": {
						"actions": {
							"type": "Action[]"
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
				"anyOf": [
					{
						"allOf": [
							{
								"$ref": "#/definitions/AdaptiveCard"
							}
						]
					}
				],
				"definitions": {
					"AdaptiveCard": {
						"type": "object",
						"additionalProperties": false,
						"properties": {
							"type": {
								"enum": [ "AdaptiveCard" ],
								"description": "Must be `AdaptiveCard`"
							},
							"actions": {
								"type": "array",
								"items": {
									"$ref": "#/definitions/ImplementationsOf.Action"
								}
							}
						}
					},
					"Action.OpenUrl": {
						"type": "object",
						"additionalProperties": false,
						"properties": {
							"type": {
								"enum": [ "Action.OpenUrl" ],
								"description": "Must be `Action.OpenUrl`"
							},
							"url": {
								"type": "string",
								"format": "uri"
							},
							"title": {}
						},
						"allOf": [
							{
								"$ref": "#/definitions/Extendable.Action"
							}
						]
					},
					"Action.Submit": {
						"type": "object",
						"additionalProperties": false,
						"properties": {
							"type": {
								"enum": [ "Action.Submit" ],
								"description": "Must be `Action.Submit`"
							},
							"data": {
								"type": "string"
							},
							"title": {}
						},
						"allOf": [
							{
								"$ref": "#/definitions/Extendable.Action"
							}
						]
					},
					"Extendable.Action": {
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
								"required": [ "type" ],
								"allOf": [
									{
										"$ref": "#/definitions/Action.OpenUrl"
									}
								]
							},
							{
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


	it("Test dictionary of objects property", function () {
		assertTransform({
			types: [
				{
					"type": "AdaptiveCard",
					"properties": {
						"actions": {
							"type": "Dictionary<Action.OpenUrl>"
						}
					}
				},
				{
					"type": "Action.OpenUrl",
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
				"anyOf": [
					{
						"allOf": [
							{
								"$ref": "#/definitions/AdaptiveCard"
							}
						]
					}
				],
				"definitions": {
					"AdaptiveCard": {
						"type": "object",
						"additionalProperties": false,
						"properties": {
							"type": {
								"enum": [ "AdaptiveCard" ],
								"description": "Must be `AdaptiveCard`"
							},
							"actions": {
								"type": "object",
								"additionalProperties": {
									"$ref": "#/definitions/Action.OpenUrl"
								}
							}
						}
					},
					"Action.OpenUrl": {
						"type": "object",
						"additionalProperties": false,
						"properties": {
							"type": {
								"enum": [ "Action.OpenUrl" ],
								"description": "Must be `Action.OpenUrl`"
							},
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


	
    it("Test any object as top level", function () {

		assertTransform({
			types: [
				{
					"type": "AdaptiveCard",
					"properties": {
						"version": {
							"type": "string"
						}
					}
				},
				{
					"type": "BasicCard",
					"properties": {
						"title": {
							"type": "string"
						}
					}
				}
			],
			primaryTypeName: ["AdaptiveCard","BasicCard"],
			expected: {
				"$schema": "http://json-schema.org/draft-06/schema#",
				"id": "http://adaptivecards.io/schemas/adaptive-card.json",
				"anyOf": [
					{
						"required": [ "type" ],
						"allOf": [
							{
								"$ref": "#/definitions/AdaptiveCard"
							}
						]
					},
					{
						"required": [ "type" ],
						"allOf": [
							{
								"$ref": "#/definitions/BasicCard"
							}
						]
					}
				],
				"definitions": {
					"AdaptiveCard": {
						"type": "object",
						"additionalProperties": false,
						"properties": {
							"type": {
								"enum": [ "AdaptiveCard" ],
								"description": "Must be `AdaptiveCard`"
							},
							"version": {
								"type": "string"
							}
						}
					},
					"BasicCard": {
						"type": "object",
						"additionalProperties": false,
						"properties": {
							"type": {
								"enum": [ "BasicCard" ],
								"description": "Must be `BasicCard`"
							},
							"title": {
								"type": "string"
							}
						}
					}
				}
			}
		})
	});

	it("Test custom type property name", function () {

		assertTransform({
			types: [
				{
					"type": "Class"
				},
				{
					"type": "Enum"
				}
			],
			primaryTypeName: [ "Class", "Enum" ],
			expected: {
				"$schema": "http://json-schema.org/draft-06/schema#",
				"id": "http://adaptivecards.io/schemas/adaptive-card.json",
				"anyOf": [
					{
						"required": [ "classType" ],
						"allOf": [
							{
								"$ref": "#/definitions/Class"
							}
						]
					},
					{
						"required": [ "classType" ],
						"allOf": [
							{
								"$ref": "#/definitions/Enum"
							}
						]
					}
				],
				"definitions": {
					"Class": {
						"type": "object",
						"additionalProperties": false,
						"properties": {
							"classType": {
								"enum": [ "Class" ],
								"description": "Must be `Class`"
							}
						}
					},
					"Enum": {
						"type": "object",
						"additionalProperties": false,
						"properties": {
							"classType": {
								"enum": [ "Enum" ],
								"description": "Must be `Enum`"
							}
						}
					}
				}
			},
			typePropertyName: "classType"
		})
	});

	it("Test multiple primary types with default", function () {

		assertTransform({
			types: [
				{
					"type": "Class",
					"properties": {
						"type": {
						  "type": "string",
						  "required": true
						},
					}
				},
				{
					"type": "Property",
					"properties": {
						"propertyType": {
						  "type": "string",
						  "required": true
						}
					}
				}
			],
			primaryTypeName: [ "Class", "Property" ],
			defaultPrimaryTypeName: "Class",
			typePropertyName: "classType",
			expected: {
				"$schema": "http://json-schema.org/draft-06/schema#",
				"id": "http://adaptivecards.io/schemas/adaptive-card.json",
				"anyOf": [
					{
						"allOf": [
							{
								"$ref": "#/definitions/Class"
							}
						]
					},
					{
						"required": [ "classType" ],
						"allOf": [
							{
								"$ref": "#/definitions/Property"
							}
						]
					}
				],
				"definitions": {
					"Class": {
						"type": "object",
						"additionalProperties": false,
						"properties": {
							"classType": {
								"enum": [ "Class" ],
								"description": "Must be `Class`"
							},
							"type": {
								"type": "string"
							}
						},
						"required": [ "type" ]
					},
					"Property": {
						"type": "object",
						"additionalProperties": false,
						"properties": {
							"classType": {
								"enum": [ "Property" ],
								"description": "Must be `Property`"
							},
							"propertyType": {
								"type": "string"
							}
						},
						"required": [ "propertyType" ]
					}
				}
			}
		})
	});

	it("Test marker interfaces", function () {
		assertTransform({
			types: [
				{
					"type": "AdaptiveCard",
					"properties": {
						"moreInfoAction": {
							"type": "IActionWithinElement",
							"description": "Action to invoke when user wants more info"
						}
					}
				},
				{
					"type": "Action.OpenUrl",
					"extends": "Action, IActionWithinElement",
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
				},
				{
					"type": "IActionWithinElement",
					"isAbstract": true,
					"description": "Actions supported within elements"
				}
			],
			primaryTypeName: "AdaptiveCard",
			expected: {
				"$schema": "http://json-schema.org/draft-06/schema#",
				"id": "http://adaptivecards.io/schemas/adaptive-card.json",
				"anyOf": [
					{
						"allOf": [
							{
								"$ref": "#/definitions/AdaptiveCard"
							}
						]
					}
				],
				"definitions": {
					"AdaptiveCard": {
						"type": "object",
						"additionalProperties": false,
						"properties": {
							"type": {
								"enum": [ "AdaptiveCard" ],
								"description": "Must be `AdaptiveCard`"
							},
							"moreInfoAction": {
								"description": "Action to invoke when user wants more info",
								"$ref": "#/definitions/ImplementationsOf.IActionWithinElement"
							}
						}
					},
					"Action.OpenUrl": {
						"type": "object",
						"additionalProperties": false,
						"description": "An open URL action",
						"properties": {
							"type": {
								"enum": [ "Action.OpenUrl" ],
								"description": "Must be `Action.OpenUrl`"
							},
							"url": {
								"type": "string",
								"format": "uri",
								"description": "The url to open"
							},
							"title": {}
						},
						"allOf": [
							{
								"$ref": "#/definitions/Extendable.Action"
							}
						]
					},
					"Extendable.Action": {
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
								"required": [ "type" ],
								"allOf": [
									{
										"$ref": "#/definitions/Action.OpenUrl"
									}
								]
							}
						]
					},
					"ImplementationsOf.IActionWithinElement": {
						"anyOf": [
							{
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

	it("Test enums", function () {

		assertTransform({
			types: [
				{
					"type": "TextBlock",
					"properties": {
						"size": {
							"type": "FontSize"
						}
					}
				},
				{
					"type": "FontSize",
					"classType": "Enum",
					"values": [
						"default",
						"small",
						"large"
					]
				}
			],
			primaryTypeName: "TextBlock",
			expected: {
				"$schema": "http://json-schema.org/draft-06/schema#",
				"id": "http://adaptivecards.io/schemas/adaptive-card.json",
				"anyOf": [
					{
						"allOf": [
							{
								"$ref": "#/definitions/TextBlock"
							}
						]
					}
				],
				"definitions": {
					"TextBlock": {
						"type": "object",
						"additionalProperties": false,
						"properties": {
							"type": {
								"enum": [ "TextBlock" ],
								"description": "Must be `TextBlock`"
							},
							"size": {
								"$ref": "#/definitions/FontSize"
							}
						}
					},
					"FontSize": {
						"anyOf": [
							{
								"enum": [
									"default",
									"small",
									"large"
								]
							},
							{
								"pattern": "^([d|D][e|E][f|F][a|A][u|U][l|L][t|T])|([s|S][m|M][a|A][l|L][l|L])|([l|L][a|A][r|R][g|G][e|E])$"
							}
						]
					}
				}
			}
		})
	});

	

	it("Test extendable enums", function () {

		assertTransform({
			types: [
				{
					"type": "TextBlock",
					"properties": {
						"size": {
							"type": "FontSize"
						}
					}
				},
				{
					"type": "FontSize",
					"classType": "Enum",
					"values": [
						"default",
						"small",
						"large"
					]
				}
			],
			primaryTypeName: "TextBlock",
			allowCustomEnums: true,
			expected: {
				"$schema": "http://json-schema.org/draft-06/schema#",
				"id": "http://adaptivecards.io/schemas/adaptive-card.json",
				"anyOf": [
					{
						"allOf": [
							{
								"$ref": "#/definitions/TextBlock"
							}
						]
					}
				],
				"definitions": {
					"TextBlock": {
						"type": "object",
						"additionalProperties": false,
						"properties": {
							"type": {
								"enum": [ "TextBlock" ],
								"description": "Must be `TextBlock`"
							},
							"size": {
								"$ref": "#/definitions/FontSize"
							}
						}
					},
					"FontSize": {
						"anyOf": [
							{
								"enum": [
									"default",
									"small",
									"large"
								]
							},
							{
								"type": "string"
							}
						]
					}
				}
			}
		})
	});

	it("Test enums with descriptions", function () {

		assertTransform({
			types: [
				{
					"type": "TextBlock",
					"properties": {
						"size": {
							"type": "FontSize"
						}
					}
				},
				{
					"type": "FontSize",
					"classType": "Enum",
					"values": [
						"default",
						{
							"value": "small",
							"description": "Small font size"
						},
						"large"
					]
				}
			],
			primaryTypeName: "TextBlock",
			expected: {
				"$schema": "http://json-schema.org/draft-06/schema#",
				"id": "http://adaptivecards.io/schemas/adaptive-card.json",
				"anyOf": [
					{
						"allOf": [
							{
								"$ref": "#/definitions/TextBlock"
							}
						]
					}
				],
				"definitions": {
					"TextBlock": {
						"type": "object",
						"additionalProperties": false,
						"properties": {
							"type": {
								"enum": [ "TextBlock" ],
								"description": "Must be `TextBlock`"
							},
							"size": {
								"$ref": "#/definitions/FontSize"
							}
						}
					},
					"FontSize": {
						"anyOf": [
							{
								"enum": [
									"default",
									"small",
									"large"
								]
							},
							{
								"pattern": "^([d|D][e|E][f|F][a|A][u|U][l|L][t|T])|([s|S][m|M][a|A][l|L][l|L])|([l|L][a|A][r|R][g|G][e|E])$"
							}
						]
					}
				}
			}
		})
	});
});


function assertTransform(options) {

	if (!Array.isArray(options.primaryTypeName)) {
		options.primaryTypeName = [ options.primaryTypeName ];
	}

	var transformed = tschema.transformTypes(options.types, {
		primaryTypeNames: options.primaryTypeName,
		defaultPrimaryTypeName: options.defaultPrimaryTypeName,
		typePropertyName: options.typePropertyName,
		allowAdditionalProperties: options.allowAdditionalProperties,
		allowCustomEnums: options.allowCustomEnums
	});

	assert.deepStrictEqual(transformed, options.expected, "Transform wasn't equal to expected");
}
module.exports = {
	testEnvironment: 'node',
	preset: "ts-jest/presets/default-esm",
	moduleNameMapper: {
		// Seems like we should be subbing something for the numbers here?
		'^(\\.{1,2}/.*)\\.js$': '$1',
	},
	transform: {
		"^.+\\.tsx?$": [
			'ts-jest',
			{
				useESM: true
				// tsconfig: './tsconfig.json'
			}
		]
	}
};
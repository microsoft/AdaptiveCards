module.exports = {
    preset: 'ts-jest/presets/js-with-ts',
    verbose: true,
    moduleFileExtensions: ["ts", "tsx", "js", "jsx", "json", "node"],
    // testRegex: "(/__tests__/.*|(\\.|/)(test|spec))\\.(jsx?|tsx?)$",
    testPathIgnorePatterns: [
        "/node_modules/"
    ],
    modulePathIgnorePatterns: [
        "TestUtils"
    ]
};

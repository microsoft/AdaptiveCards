module.exports = {
    entry: "./src/Adaptive.ts",
    output: {
        filename: "./adaptive.js",
        library: 'adaptiveCardHtmlRenderer'
    },

    resolve: {
        // Add '.ts' as resolvable extensions.
        extensions: [".webpack.js", ".web.js", ".ts", ".js"]
    },

    module: {
        loaders: [
            // All files with a '.ts' or '.tsx' extension will be handled by 'awesome-typescript-loader'.
            {
                test: /\.ts$/,
                loader: "ts-loader",
            },
            {
                test: /\.json$/,
                loader: "json-loader",
            }

        ]
    },
};
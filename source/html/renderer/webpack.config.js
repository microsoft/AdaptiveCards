module.exports = {
    entry: "./src/adaptive-cards.ts",
    output: {
        filename: "./packed/adaptive-cards.js",
        library: 'AdaptiveCards'
    },

    resolve: {
        extensions: [".webpack.js", ".web.js", ".ts", ".js"]
    },

    module: {
        rules: [
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
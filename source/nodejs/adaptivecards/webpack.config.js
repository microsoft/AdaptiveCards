module.exports = {
    entry: "./src/adaptivecards.ts",
    output: {
        filename: "./dist/adaptivecards.js",
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
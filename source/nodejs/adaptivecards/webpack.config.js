module.exports = {
    context: __dirname,
    devtool: "inline-source-map",
    entry: "./src/adaptivecards.ts",
    output: {
        path: __dirname + "/dist",
        filename: "adaptivecards.js",
        library: 'AdaptiveCards'
    },
    resolve: {
        extensions: [".ts", ".js"]
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
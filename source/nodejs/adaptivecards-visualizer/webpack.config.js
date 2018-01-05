var visualizer = {
    entry: "./src/app.ts",
    output: {
        filename: "./dist/adaptivecards-visualizer.js"
    },

    // Enable sourcemaps for debugging webpack's output.
    devtool: "source-map",

    resolve: {
        // Add '.ts' as resolvable extensions.
        extensions: [".webpack.js", ".web.js", ".ts", ".js"]
    },

    module: {
        rules: [
            {
                test: /\.ts$/,
                loader: "ts-loader"
            },
            {
                test: /\.json$/,
                loader: "json-loader",
            }
        ]
    },
    externals: {
        "adaptivecards": { var: "AdaptiveCards" }
    }
};

module.exports = visualizer;

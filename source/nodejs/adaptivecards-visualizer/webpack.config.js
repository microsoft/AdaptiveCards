var webpack = require("webpack");
var path = require("path");

var visualizer = {
    devtool: "source-map",
    entry: {
        "adaptivecards-visualizer": ["./src/app.ts"],
        "adaptivecards-visualizer.min": ["./src/app.ts"]
    },
    output: {
        path: path.resolve(__dirname, "dist"),
        filename: "[name].js",
    },
    resolve: {
        extensions: [".ts", ".tsx", ".js"]
    },
    plugins: [
        new webpack.optimize.UglifyJsPlugin({
            minimize: true,
            sourceMap: true,
            include: /\.min\.js$/,
        })
    ],
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
        "adaptivecards": { var: "AdaptiveCards" },
        "markdown-it": { var: "markdownit"}
    }
};

module.exports = visualizer;

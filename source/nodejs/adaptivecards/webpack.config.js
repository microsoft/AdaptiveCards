var webpack = require("webpack");
var path = require("path");

module.exports = {
    devtool: "source-map",
    entry: {
        "adaptivecards": ["./src/adaptivecards.ts"],
        "adaptivecards.min": ["./src/adaptivecards.ts"]
    },
    output: {
        path: path.resolve(__dirname, "dist"),
        filename: "[name].js",
        library: "AdaptiveCards"
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
                loader: "awesome-typescript-loader",
                exclude: /(node_modules|__tests__)/,
                query: {
                    declaration: false,
                }
            },
            {
                test: /\.json$/,
                loader: "json-loader",
            }
        ]
    }
};
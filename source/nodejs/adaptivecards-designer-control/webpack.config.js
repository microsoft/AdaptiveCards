var webpack = require("webpack");
var path = require("path");

module.exports = {
    devtool: "source-map",
    entry: {
        "adaptivecards-designer-control": ["./src/adaptivecards-designer-control.ts"],
        "adaptivecards-designer-control.min": ["./src/adaptivecards-designer-control.ts"]
    },
    output: {
        path: path.resolve(__dirname, "dist"),
        filename: "[name].js",
        library: "AdaptiveCardsDesignerControl"
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
    },
    externals: {
        adaptivecards: {
            commonjs: 'adaptivecards',
            commonjs2: 'adaptivecards',
            amd: 'adaptivecards',
            umd: 'adaptivecards',
            root: 'AdaptiveCards'
        },
    }
};
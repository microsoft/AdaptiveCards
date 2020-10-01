const path = require("path");
const BundleAnalyzerPlugin = require('webpack-bundle-analyzer').BundleAnalyzerPlugin;

module.exports = (env, argv) => {
    const mode = argv.mode || 'development';
    const devMode = mode === "development";

    console.info('running webpack with mode:', mode);

    return {
        mode: mode,
        entry: {
            "adaptivecards-templating": "./src/adaptivecards-templating.ts"
        },
        output: {
            path: path.resolve(__dirname, "./dist"),
            filename: devMode ? "[name].js" : "[name].min.js",
            libraryTarget: "umd",
            library: "ACData",
            globalObject: "this"
        },
        devtool: devMode ? "inline-source-map" : "source-map",
        devServer: {
            contentBase: './dist'
        },
        resolve: {
            extensions: [".ts", ".tsx", ".js"]
        },
        module: {
            rules: [{
                    test: /\.ts$/,
                    loader: "ts-loader",
                    exclude: /(node_modules|__tests__)/
                }
            ]
        },
        plugins: [
            new BundleAnalyzerPlugin({
                analyzerMode: "disabled",
                generateStatsFile: true,
                openAnalyzer: false
            })
        ]
    };
}

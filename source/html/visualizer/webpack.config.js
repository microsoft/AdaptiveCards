var visualizer = {
    entry: "./src/App.ts",
    output: {
        filename: "./visualizer.js"
    },

    // Enable sourcemaps for debugging webpack's output.
    //devtool: "source-map",

    resolve: {
        alias: {
            "adaptive-cards": "renderer"
        },

        // Add '.ts' as resolvable extensions.
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

    externals: {
        "adaptive-cards": "AdaptiveCardsLib"
        // "adaptive-cards/Utils": 'adaptiveCardHtmlRenderer.Utils',
        // "adaptive-cards/JsonParser": 'adaptiveCardHtmlRenderer.JsonParser'
    }

};

var visualizerWithRenderer = {
    entry: "./src/App.ts",
    output: {
        filename: "./visualizer-with-renderer.js"
    },

    // Enable sourcemaps for debugging webpack's output.
    //devtool: "source-map",

    resolve: {
        alias: {
            "adaptive-cards": "renderer"
        },

        // Add '.ts' as resolvable extensions.
        extensions: [".webpack.js", ".web.js", ".ts", ".js"],

         modules: ["node_modules", ".."]
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

module.exports = [visualizerWithRenderer];

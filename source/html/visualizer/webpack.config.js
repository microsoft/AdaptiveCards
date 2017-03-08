var bundle = {
    entry: "./src/App.ts",
    output: {
        filename: "./visualizer-bundle.js"
    },

    // Enable sourcemaps for debugging webpack's output.
    //devtool: "source-map",

    resolve: {
        alias: {
            "adaptive-card-html-renderer": "adaptive-card-html-renderer/built"
        },

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

var cdn = {
    entry: "./src/App.ts",
    output: {
        filename: "./visualizer-use-cdn.js"
    },

    // Enable sourcemaps for debugging webpack's output.
    //devtool: "source-map",

    resolve: {
        alias: {
            "adaptive-card-html-renderer": "adaptive-card-html-renderer/built"
        },

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

    externals: {
        "adaptive-card-html-renderer/Adaptive": 'adaptiveCardHtmlRenderer',
        "adaptive-card-html-renderer/Utils": 'adaptiveCardHtmlRenderer.Utils',
        "adaptive-card-html-renderer/JsonParser": 'adaptiveCardHtmlRenderer.JsonParser'
    }

};

module.exports = [bundle, cdn];

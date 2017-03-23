// `CheckerPlugin` is optional. Use it if you want async error reporting.
// We need this plugin to detect a `--watch` mode. It may be removed later
// after https://github.com/webpack/webpack/issues/3460 will be resolved.
const { CheckerPlugin } = require('awesome-typescript-loader')
const { TsConfigPathsPlugin } = require('awesome-typescript-loader');

var visualizer = {
    entry: "./src/App.ts",
    output: {
        filename: "./visualizer.js"
    },

    // Enable sourcemaps for debugging webpack's output.
    //devtool: "source-map",

    resolve: {
        // alias: {
        //     "adaptive-cards": "../renderer/built/adaptive-cards"
        // },

        // Add '.ts' as resolvable extensions.
        extensions: [".webpack.js", ".web.js", ".ts", ".js"]
    },

    module: {
        rules: [
            // All files with a '.ts' or '.tsx' extension will be handled by 'awesome-typescript-loader'.
            {
                test: /\.tsx?$/,
                loader: "awesome-typescript-loader",
            },
            {
                test: /\.json$/,
                loader: "json-loader",
            }

        ]
    },
     plugins: [
      new CheckerPlugin(),
  ],

    externals: {
        //"adaptive-cards": "adaptive-cards"
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

module.exports = [visualizer];

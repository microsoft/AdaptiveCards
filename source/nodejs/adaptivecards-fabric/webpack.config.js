const path = require('path');
const CleanWebpackPlugin = require('clean-webpack-plugin');

module.exports = (env, argv) => {

    const mode = argv.mode || 'development';
    const devMode = mode === "development";

    console.info(`running webpack with mode: ${mode}`);

    return {
        entry: {
            'adaptivecards': './src/adaptivecards.ts'
        },
        output: {
            path: path.resolve(__dirname, "./dist"),
            filename: "[name].js",
            libraryTarget: "umd",
            library: "@ms-conv-ux/adaptive-cards-extended"
        },
        devtool: devMode ? "inline-source-map" : "source-map",
        module: {
            rules: [{
                    test: /\.tsx?$/,
                    loader: "awesome-typescript-loader"
                },
                {
                    test: /\.css$/,
                    use: ['style-loader', 'css-loader']
                },
                {
                    test: /\.scss$/,
                    use: ['style-loader', 'css-loader', 'sass-loader']
                }
            ]
        },
        node: {
            fs: 'empty'
        },
        resolve: {
            extensions: [".ts", ".tsx", ".js", ".jsx"]
        },
        plugins: [
            new CleanWebpackPlugin()
        ],
        externals: ["react", "react-dom", "adaptivecards", "office-ui-fabric-react"],
        mode: mode
    }
};

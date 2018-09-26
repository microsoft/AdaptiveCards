var webpack = require("webpack");
var path = require("path");

var designer = {
    devtool: "source-map",
    entry: {
        "adaptivecards-designer": ["./src/app.ts"],
		"adaptivecards-designer.min": ["./src/app.ts"],
		// "editor.worker": "monaco-editor/esm/vs/editor/editor.worker.js",
		// "editor.worker.min": "monaco-editor/esm/vs/editor/editor.worker.js",
		// "json.worker": "monaco-editor/esm/vs/language/json/json.worker",
		// "json.worker.min": "monaco-editor/esm/vs/language/json/json.worker",
	},	
    output: {
		publicPath: '/dist',
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
			},
			{

				test: /\.css$/,
				use: [ 'style-loader', 'css-loader' ]	
			}
        ]
    },
    externals: {
		"markdown-it": "markdownit"
	}
};

module.exports = designer;

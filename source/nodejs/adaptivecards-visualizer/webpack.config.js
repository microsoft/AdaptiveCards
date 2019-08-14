const path = require("path");
const MiniCssExtractPlugin = require("mini-css-extract-plugin");
const HtmlWebpackPlugin = require('html-webpack-plugin');
const CleanWebpackPlugin = require('clean-webpack-plugin');
const MonacoWebpackPlugin = require('monaco-editor-webpack-plugin');

module.exports = (env, argv) => {
	const mode = argv.mode || 'development';
	const devMode = mode === "development";

	console.info('running webpack with mode:', mode);

	return {
		mode: mode,
		entry: {
			"adaptivecards-visualizer": "./src/app.ts",
		},
		output: {
			path: path.resolve(__dirname, "dist"),
			filename: devMode ? "[name].js" : "[name].min.js",
		},
		resolve: {
			extensions: [".ts", ".tsx", ".js"]
		},
		module: {
			rules: [{
					test: /\.ts$/,
					loader: "ts-loader",
					exclude: /(node_modules|__tests__)/
				},
				{
					test: /\.css$/,
					use: [
						'style-loader',
						'css-loader'
					]
				}
			]
		},
		plugins: [
			//new CleanWebpackPlugin(['dist']),
			new HtmlWebpackPlugin({
				title: "Adaptive Cards Visualizer",
				template: "./index.html"
			}),
			new MiniCssExtractPlugin({
				filename: '[name].css'
			 })
		],
		externals: {
			"markdown-it": "markdownit",
			"adaptivecards": "AdaptiveCards",
			"monaco-editor/esm/vs/editor/editor.api": "monaco"
		}
	}
}
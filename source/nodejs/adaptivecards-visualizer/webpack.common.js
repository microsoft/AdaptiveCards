const path = require("path");
const MiniCssExtractPlugin = require("mini-css-extract-plugin");
const HtmlWebpackPlugin = require('html-webpack-plugin');
const CleanWebpackPlugin = require('clean-webpack-plugin');
const MonacoWebpackPlugin = require('monaco-editor-webpack-plugin');

module.exports = {
	entry: {
		"adaptivecards-visualizer": "./src/app.ts",
	},
	output: {
		path: path.resolve(__dirname, "dist"),
		filename: "[name].js",
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
					//MiniCssExtractPlugin.loader,
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
		}),
		new MonacoWebpackPlugin({
			languages: ['json']
		})
	],
	externals: {
		"markdown-it": "markdownit",
		"adaptivecards": "AdaptiveCards",
		"monaco-editor/esm/vs/editor/editor.api": "monaco"
	}
};

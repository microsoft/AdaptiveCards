const path = require("path");
const MiniCssExtractPlugin = require("mini-css-extract-plugin");
const HtmlWebpackPlugin = require('html-webpack-plugin');
const CleanWebpackPlugin = require('clean-webpack-plugin');
const MonacoWebpackPlugin = require('monaco-editor-webpack-plugin');
const CopyWebpackPlugin = require('copy-webpack-plugin');

module.exports = {
	entry: {
		"adaptivecards-designer-app": "./src/app.ts",
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
		new CopyWebpackPlugin([{
			from: 'node_modules/adaptivecards-designer/dist/containers/*',
			to: 'containers/',
			flatten: true
		}]),
		new HtmlWebpackPlugin({
			title: "Adaptive Cards Designer",
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
		//"markdown-it": "markdownit"
		//"monaco-editor/esm/vs/editor/editor.api": "monaco"
	}
};

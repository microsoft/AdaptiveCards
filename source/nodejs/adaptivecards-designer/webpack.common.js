const path = require("path");
const MiniCssExtractPlugin = require("mini-css-extract-plugin");
const HtmlWebpackPlugin = require('html-webpack-plugin');
const CleanWebpackPlugin = require('clean-webpack-plugin');
const CopyWebpackPlugin = require('copy-webpack-plugin');

module.exports = {
	entry: {
		"adaptivecards-designer": "./src/adaptivecards-designer.ts",
		//"microsoft-hosts": "./src/containers/index.ts"
	},
	output: {
		path: path.resolve(__dirname, "./dist"),
		filename: "[name].js",
		library: "ACDesigner",
		//libraryTarget: "umd",
		//umdNamedDefine: true
	},
	resolve: {
		extensions: [".ts", ".tsx", ".js"]
	},
	module: {
		rules: [{
				test: /\.ts$/,
				loader: "awesome-typescript-loader",
				exclude: /(node_modules|__tests__)/,
				query: {
					declaration: false,
				}
			},
			{
				test: /\.css$/,
				use: [
					'style-loader',
					MiniCssExtractPlugin.loader,
					'css-loader'
				]
			}
		]
	},
	plugins: [
		new MiniCssExtractPlugin({
			filename: '[name].css'
		}),
		new CopyWebpackPlugin([{
				from: 'src/containers/**/*.css',
				to: 'containers/',
				flatten: true
			},
			{
				from: 'src/containers/**/*.png',
				to: 'containers/',
				flatten: true
			},
			{
				from: 'src/containers/**/*.jpg',
				to: 'containers/',
				flatten: true
			}
		])
	],
	externals: {
		//"adaptivecards": "AdaptiveCards",
		//"adaptivecards-controls": "ACControls",
		//"monaco-editor/esm/vs/editor/editor.api": "monaco"
	}
};

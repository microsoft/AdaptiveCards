// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
const path = require("path");
const MiniCssExtractPlugin = require("mini-css-extract-plugin");
const HtmlWebpackPlugin = require('html-webpack-plugin');
const CopyWebpackPlugin = require('copy-webpack-plugin');
const ConcatPlugin = require('webpack-concat-files-plugin');
const Dotenv = require('dotenv-webpack');

module.exports = (env, argv) => {
	const mode = argv.mode || 'development';
	const devMode = mode === "development";

	console.info('running webpack with mode:', mode);

	return {
		mode: mode,
		target: 'web',
		entry: {
			"adaptivecards-ui-testapp": "./src/adaptivecards-ui-testapp.ts"
		},
		output: {
			path: path.resolve(__dirname, "./dist"),
			filename: devMode ? "[name].js" : "[name].min.js",
			library: "ACUITestApp",
			libraryTarget: "umd",
			globalObject: "this",
			// umdNamedDefine: true
		},
		devtool: devMode ? "inline-source-map" : "source-map",
		devServer: {
			static: {
				directory: path.resolve(__dirname, "./dist"),
			},
			liveReload: false,
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
					MiniCssExtractPlugin.loader,
					'css-loader'
				]
			}
			]
		},
		plugins: [
			new Dotenv(),
			new HtmlWebpackPlugin({
				title: "Adaptive Cards UI TestApp",
				template: "./index.html",
				filename: "index.html",
				chunks: ["adaptivecards-ui-testapp"]
			}),
			new MiniCssExtractPlugin({
				filename: '[name].css'
			}),
			new ConcatPlugin({
				bundles: [
					{
						dest: 'adaptivecards-ui-testapp.css',
						src: ['./node_modules/adaptivecards-controls/dist/adaptivecards-controls.css', './src/adaptivecards-ui-testapp.css']
					}
				],
			}),
			new CopyWebpackPlugin({
				patterns: [
				{
					from: 'src/adaptivecards-ui-testapp.css',
					to: '.',
					flatten: true
				},
				{
					from: '../../../samples/',
					to: './samples/',
					context: '.',
					flatten: false
				}],
				options: {
					concurrency: 8
				}
			})
		],
		externals: {
			"adaptive-expressions": {
				commonjs2: "adaptive-expressions",
				commonjs: "adaptive-expressions",
				root: "AEL"
			},
			"adaptivecards-templating": {
				commonjs2: "adaptivecards-templating",
				commonjs: "adaptivecards-templating",
				root: "ACData"
			}
		}
	}
}

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
		entry: {
			"adaptivecards-designer": "./src/adaptivecards-designer.ts",
			"adaptivecards-designer-standalone": "./src/adaptivecards-designer-standalone.ts"
		},
		output: {
			path: path.resolve(__dirname, "./dist"),
			filename: devMode ? "[name].js" : "[name].min.js",
			libraryTarget: "umd",
			library: "ACDesigner",
			globalObject: "this"
		},
		devtool: devMode ? "inline-source-map" : "source-map",
		devServer: {
			static: './dist'
		},
		resolve: {
			extensions: [".ts", ".tsx", ".js"]
		},
		module: {
			rules: [
				{
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
				},
				{
					test: /\.svg$/,
					type: 'asset/inline'
				}
			]
		},
		plugins: [
			new Dotenv(),
			new HtmlWebpackPlugin({
				title: "Adaptive Cards Designer (No Microsoft Hosts)",
				template: "./noHosts.html",
				filename: "noHosts.html",
				chunks: ["adaptivecards-designer-standalone"]
			}),
			new HtmlWebpackPlugin({
				title: "Adaptive Cards Designer",
				template: "./index.html",
				filename: "index.html",
				chunks: ["adaptivecards-designer"]
			}),
			new HtmlWebpackPlugin({
				title: "Adaptive Cards Designer (Preview Features)",
				template: "./previewFeatures.html",
				filename: "previewFeatures.html",
				chunks: ["adaptivecards-designer"]
			}),
			new HtmlWebpackPlugin({
				title: "Adaptive Cards Designer (No Microsoft Hosts)",
				template: "./noHosts.html",
				filename: "noHosts.html",
				chunks: ["adaptivecards-designer-standalone"]
			}),
			new MiniCssExtractPlugin({
				filename: '[name].css'
			}),
			new ConcatPlugin({
				bundles: [
					{
						dest: 'dist/adaptivecards-designer.css',
						src: [
							'./node_modules/adaptivecards-controls/dist/adaptivecards-controls.css',
							'./node_modules/adaptivecards/dist/adaptivecards-carousel.css',
							'./src/adaptivecards-designer.css'
						]
					}
				]
			}),
			new CopyWebpackPlugin({
				patterns: [{
					from: 'src/containers/default/adaptivecards-defaulthost.css',
					to: '.'
				},
				{
					from: 'src/containers/**/*.css',
					to: 'containers/[name][ext]'
				},
				{
					from: 'src/containers/**/*.png',
					to: 'containers/[name][ext]'
				},
				{
					from: 'src/containers/**/*.jpg',
					to: 'containers/[name][ext]'
				},
				{
					from: 'src/assets/*.*',
					to: '../lib/assets/[name][ext]'
				}],
				options: {
					concurrency: 8
				}
			})
		],
		externals: {
			///^monaco-editor/ // <-- NOT WORKING for some reason
			"adaptivecards": {
				commonjs2: "adaptivecards",
				commonjs: "adaptivecards",
				root: "AdaptiveCards"
			},
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

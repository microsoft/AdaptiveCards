const path = require("path");
const MiniCssExtractPlugin = require("mini-css-extract-plugin");
const HtmlWebpackPlugin = require('html-webpack-plugin');
const CopyWebpackPlugin = require('copy-webpack-plugin');
const ConcatPlugin = require('webpack-concat-plugin');

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
			library: "ACDesigner",
			//libraryTarget: "umd",
			//umdNamedDefine: true
		},
		devtool: devMode ? "inline-source-map" : "source-map",
		devServer: {
			contentBase: './dist'
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
			new HtmlWebpackPlugin({
				title: "Adaptive Cards Designer (No Microsoft Hosts)",
				template: "./noHosts.html",
				filename: "noHosts.html",
				chunks: [ "adaptivecards-designer-standalone" ]
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
				uglify: false,
				sourceMap: false,
				fileName: 'adaptivecards-designer.css',
				injectType: 'none',
				filesToConcat: ['./node_modules/adaptivecards-controls/dist/adaptivecards-controls.css', './src/adaptivecards-designer.css']
			}),
			new CopyWebpackPlugin({
				patterns: [{
					from: 'src/containers/default/adaptivecards-defaulthost.css',
					to: '.'
				},
				{
					from: 'src/adaptivecards-designer.css',
					to: '.',
					flatten: true
				},
				{
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
				}],
				options: {
					concurrency: 8
				}
			})
		],
		externals: [
			///^monaco-editor/ // <-- NOT WORKING for some reason
		]
	}
}

const path = require("path");
const MiniCssExtractPlugin = require("mini-css-extract-plugin");
const HtmlWebpackPlugin = require('html-webpack-plugin');
const CleanWebpackPlugin = require('clean-webpack-plugin');
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
			//"microsoft-hosts": "./src/containers/index.ts"
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
				title: "Adaptive Cards Designer",
				template: "./index.html"
			}),
			new MiniCssExtractPlugin({
				filename: '[name].css'
			}),
			new CopyWebpackPlugin([{
				from: 'src/adaptivecards-designer.css',
				to: '.',
				flatten: true
			}]),
			new CopyWebpackPlugin([{
				from: 'node_modules/adaptivecards-controls/dist/adaptivecards-controls.css',
				to: '.',
				flatten: true
			}]),
			new ConcatPlugin({
				uglify: false,
				sourceMap: false,
				fileName: 'adaptivecards-designer.css',
				injectType: 'none',
				filesToConcat: [ './node_modules/adaptivecards-controls/dist/adaptivecards-controls.css', './src/adaptivecards-designer.css']
			}),
			new CopyWebpackPlugin([{
					from: 'src/adaptivecards-designer.css',
					to: '../lib/',
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
				},
				{
					from: 'node_modules/monaco-editor/min/vs',
					to: 'monaco-editor/min/vs'
				}
			])
		],
		externals: {
			//"adaptivecards": "AdaptiveCards",
			//"adaptivecards-controls": "ACControls",
			//"monaco-editor/esm/vs/editor/editor.api": "monaco"
		}
	}
}

const path = require("path");
const MiniCssExtractPlugin = require("mini-css-extract-plugin");
const HtmlWebpackPlugin = require('html-webpack-plugin');
const MonacoWebpackPlugin = require('monaco-editor-webpack-plugin');
const CopyWebpackPlugin = require('copy-webpack-plugin');

module.exports = (env, argv) => {
	const mode = argv.mode || 'development';
	const devMode = mode === "development";

	console.info('running webpack with mode:', mode);

	return {
		mode: mode,
		entry: {
			"adaptivecards-designer-app": "./src/app.ts",
		},
		output: {
			path: path.resolve(__dirname, "dist"),
			filename: devMode ? "[name].js" : "[name].min.js",
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
					test: /\.ttf$/,
					loader: "file-loader"
				},
				{
					test: /\.css$/,
					use: [
						devMode ? 'style-loader' : MiniCssExtractPlugin.loader,
						'css-loader'
					]
				},
				{
					test: /\.svg$/,
					type: 'asset/resource'
				}
			]
		},
		plugins: [
			new CopyWebpackPlugin({
				patterns: [
					{
						from: 'node_modules/adaptivecards-designer/src/containers/**/*',
						to: 'containers/[name][ext]'
					},
					{
						// the designer expects to find its CSS here. an alternative for a consumer would
						// be to make sure they load it themselves.
						from: 'node_modules/adaptivecards-designer/dist/adaptivecards-designer.css',
						to: 'adaptivecards-designer.css'
					}
				]
			}),
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
		]
	}
}

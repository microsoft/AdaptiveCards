const path = require("path");
const MiniCssExtractPlugin = require("mini-css-extract-plugin");
const HtmlWebpackPlugin = require('html-webpack-plugin');
const CleanWebpackPlugin = require('clean-webpack-plugin');
const MonacoWebpackPlugin = require('monaco-editor-webpack-plugin');
const CopyWebpackPlugin = require('copy-webpack-plugin');

module.exports = (env, argv) => {
	const mode = argv.mode || 'development';
	const devMode = mode === "development";

	console.info('running webpack with mode:', mode);

	return {
		mode: mode,
		devServer: {
			port: 8080,
			historyApiFallback: {
			  index: '/index.html'
			}
		  },
		devtool: devMode ? "inline-source-map" : "source-map",
		entry: {
			"adaptivecards-designer-app": "./src/app.ts",
		},
		output: {
			path: path.resolve(__dirname, "dist"),
			filename: devMode ? "[name].js" : "[name].min.js",
			publicPath: '/'
		},
		resolve: {
			extensions: [".ts", ".tsx", ".js"],
			alias: {
				handlebars: 'handlebars/dist/handlebars.min.js'
			}
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
				template: "./index.html",
				inject: true
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
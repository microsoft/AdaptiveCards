const path = require('path');
const HtmlWebpackPlugin = require('html-webpack-plugin');
const CopyWebpackPlugin = require('copy-webpack-plugin');

module.exports = (env, argv) => {
	const mode = argv.mode || 'development';
	const devMode = mode === 'development';

	console.info('running webpack with mode:', mode);

	return {
		mode: mode,
		entry: {
			"adaptivecards": "./src/adaptivecards.ts"
		},
		output: {
			path: path.resolve(__dirname, "./dist"),
			filename: devMode ? "[name].js" : "[name].min.js",
			libraryTarget: "umd",
			library: "AdaptiveCards",
			globalObject: "this"
		},
		devtool: devMode ? "inline-source-map" : "source-map",
		devServer: {
			static: {
				directory: './dist'
			}
		},
		resolve: {
			extensions: [".ts", ".tsx", ".js", ".scss"]
		},
		module: {
			rules: [{
				test: /\.ts$/,
				loader: "ts-loader",
				exclude: /(node_modules|__tests__)/
			}]
		},
		plugins: [
			new CopyWebpackPlugin(
				{
					patterns: [
						{
							from: 'src/scss/adaptivecards*',
							to: '../dist/[name][ext]'
						},
						{
							from: 'src/scss/adaptivecards*',
							to: '../lib/[name][ext]'
						},
						{
							from: 'lib/adaptivecards*.css*',
							to: '../dist/[name][ext]'
						}
					]
				}
			),
			new HtmlWebpackPlugin(
				{
					title: "Adaptive Cards Example",
					template: "./example.html"
				}
			)
		]
	};
}

const path = require("path");
const MiniCssExtractPlugin = require("mini-css-extract-plugin");
const HtmlWebpackPlugin = require('html-webpack-plugin');

module.exports = (env, argv) => {
	const mode = argv.mode || 'development';
	const devMode = mode === "development";

	console.info('running webpack with mode:', mode);

	return {
		mode: mode,
		entry: {
			"adaptivecards-aaf-testapp": "./src/app.ts",
		},
		output: {
			path: path.resolve(__dirname, "dist"),
			filename: devMode ? "[name].js" : "[name].min.js",
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
				title: "AAF JavaScript Runtime test application",
				template: "./index.html"
			}),
            new MiniCssExtractPlugin({
				filename: '[name].css'
			})
		]
	}
}

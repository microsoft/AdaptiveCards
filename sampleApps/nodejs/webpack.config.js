const path = require('path');
const HtmlWebpackPlugin = require('html-webpack-plugin');

module.exports = (env, argv) => {
	const mode = argv.mode || 'development';
	const devMode = mode === "development";

	console.info('running webpack with mode:', mode);

	return {
		mode: mode,
		entry: {
			"ac-sample": "./src/ac-sample.ts"
		},
		output: {
			path: path.resolve(__dirname, "./dist"),
			filename: devMode ? "[name].js" : "[name].min.js",
			library: "ac-sample",
			libraryTarget: "umd",
			globalObject: "this"
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
			}]
		},
		plugins: [
			new HtmlWebpackPlugin({
				title: "AC Sample Site",
				template: "./index.html",
				filename: "index.html",
                showErrors: false,
				chunks: ["ac-sample"]
			})
		]
    }
}

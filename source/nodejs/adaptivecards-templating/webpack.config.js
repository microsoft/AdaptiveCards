const path = require("path");

module.exports = (env, argv) => {
	const mode = argv.mode || 'development';
	const devMode = mode === "development";

	console.info('running webpack with mode:', mode);

	return {
		mode: mode,
		entry: {
			"adaptivecards-templating": "./src/adaptivecards-templating.ts"
		},
		output: {
			path: path.resolve(__dirname, "./dist"),
			filename: devMode ? "[name].js" : "[name].min.js",
			libraryTarget: "umd",
			library: "ACData",
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
				},
				{
					test: /\.jsx?$/,
					use: [
						{
							loader: 'babel-loader',
						}
					],
					include: [
						path.resolve(__dirname, "./node_modules/adaptive-expressions"),
						path.resolve(__dirname, "./node_modules/@microsoft/recognizers-text-data-types-timex-expression"),
						path.resolve(__dirname, "./node_modules/antlr4ts"),
						path.resolve(__dirname, "./node_modules/lru-cache"),
						path.resolve(__dirname, "./node_modules/yallist")
					]
				}
			]
		}
	};
}

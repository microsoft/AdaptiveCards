const path = require("path");

module.exports = (env, argv) => {
	const mode = argv.mode || 'development';
	const devMode = mode === "development";

	console.info('running webpack with mode:', mode);

	return {
		mode: mode,
		entry: {
			"adaptivecards-extras": "./src/adaptivecards-extras.ts"
		},
		output: {
			path: path.resolve(__dirname, "./dist"),
			filename: devMode ? "[name].js" : "[name].min.js",
			library: "ACExtras",
			libraryTarget: "umd",
			globalObject: "this",
			// umdNamedDefine: true
		},
		devtool: devMode ? "inline-source-map" : "source-map",
		devServer: {
			static: {
				directory: './dist'
			}
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
				}
			]
		},
		externals: {
			"adaptivecards": {
				commonjs2: "adaptivecards",
				commonjs: "adaptivecards",
				root: "AdaptiveCards"
			}
		}
	}
}

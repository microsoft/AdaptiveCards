const path = require("path");

module.exports = (env, argv) => {
	const devMode = "production";

	console.info('running webpack with mode:', devMode);

	return {
		mode: devMode,
		entry: {
			"test-component": "./src/index.ts",
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
				}
			]
		},
		externals: {
			adaptivecards: "AdaptiveCards"
		}
	}
}

const path = require("path");

module.exports = (env, argv) => {
	const mode = argv.mode || 'development';
	const devMode = mode === "development";

	console.info('running webpack with mode:', mode);

	return {
		mode: mode,
		target: "node",
		entry: {
			"spec-generator-script.0.5.0.0": "./src/spec-generator-script.ts",
		},
		output: {
			path: path.resolve(__dirname, "dist"),
			filename: devMode ? "[name].js" : "[name].min.js",
		},
		externals: {
			fs: "commonjs fs"
		},
		resolve: {
			extensions: [".ts", ".tsx", ".js"]
		},
		module: {
			rules: [{
					test: /\.ts$/,
					loader: "ts-loader",
					exclude: /(node_modules|__tests__)/
				}
			]
		}
	}
}
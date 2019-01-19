const path = require("path");
const MiniCssExtractPlugin = require("mini-css-extract-plugin");
const CopyWebpackPlugin = require("copy-webpack-plugin");

module.exports = (env, argv) => {
	const mode = argv.mode || 'development';
	const devMode = mode === "development";

	console.info('running webpack with mode:', mode);

	return {
		mode: mode,
		entry: {
			"adaptivecards-controls": "./src/adaptivecards-controls.ts",
		},
		output: {
			path: path.resolve(__dirname, "./dist"),
			filename: devMode ? "[name].js" : "[name].min.js",
			libraryTarget: "umd",
			library: "ACControls",
			umdNamedDefine: true,
			publicPath: "/dist/",
			globalObject: "this"
		},
		devtool: devMode ? "inline-source-map" : "source-map",
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
			new MiniCssExtractPlugin({
				filename: 'adaptivecards-controls.css',
			}),
			new CopyWebpackPlugin([{
				from: 'src/adaptivecards-controls.css',
				to: '../lib/',
				flatten: true
			}]),
			new CopyWebpackPlugin([{
				from: 'src/adaptivecards-controls.css',
				to: '../dist/',
				flatten: true
			}])
		]
	};
};

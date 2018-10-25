const path = require("path");
const MiniCssExtractPlugin = require("mini-css-extract-plugin");

module.exports = {
	entry: {
		"adaptivecards": "./src/adaptivecards.ts"
	},
	output: {
		path: path.resolve(__dirname, "dist"),
		filename: "[name].js",
		library: "AdaptiveCards"
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
					'css-loader',
					//'typings-for-css-modules-loader?modules&namedExport&camelCase'
				]
			}
		]
	},
	plugins: [
		new MiniCssExtractPlugin({
			filename: '[name].css'
		})
	]
};

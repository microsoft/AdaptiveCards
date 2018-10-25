const path = require("path");
const MiniCssExtractPlugin = require("mini-css-extract-plugin");

module.exports = {
	entry: {
		"adaptivecards-controls": "./src/adaptivecards-controls.ts",
	},
	output: {
		path: path.resolve(__dirname, "dist"),
		filename: "[name].js",
		library: "ACControls"
	},
	resolve: {
		extensions: [".ts", ".tsx", ".js"]
	},
	module: {
		rules: [{
				test: /\.ts$/,
				loader: "awesome-typescript-loader",
				exclude: /(node_modules|__tests__)/,
				query: {
					declaration: false,
				}
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
			filename: '[name].css'
		})
	]
};

const path = require('path');
const HtmlWebpackPlugin = require('html-webpack-plugin');
const ConcatPlugin = require('webpack-concat-files-plugin');
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
				test: /\.css$/,
				use: [
					'style-loader',
					'css-loader'
				]
			}
			]
		},
		plugins: [
			new ConcatPlugin({
				bundles: [
					{
						dest: 'lib/adaptivecards.css',
						src: [
							'node_modules/swiper/swiper.min.css',
							'node_modules/swiper/modules/pagination/pagination.min.css',
							'node_modules/swiper/modules/navigation/navigation.min.css',
							'src/adaptivecards.css'
						]
					}
				],
			}),
			new CopyWebpackPlugin(
				{
					patterns: [
						{
							from: 'lib/adaptivecards.css',
							to: '../dist/adaptivecards.css',
							noErrorOnMissing: true // doesn't exist when object constructed. don't error.
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

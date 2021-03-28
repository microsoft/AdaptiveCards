const path = require('path');
const CleanWebpackPlugin = require('clean-webpack-plugin');
const HtmlWebpackPlugin = require('html-webpack-plugin');

module.exports = (env, argv) => {

	const mode = argv.mode || 'development';
	const devMode = mode === "development";
	const isLocalBuild = !!argv.local;

	const externals = [{
		"react": "React",
		"react-dom": "ReactDOM",
		"adaptivecards": "AdaptiveCards",
		...(isLocalBuild ? {} : {
			"@fluentui/react": "fluentui"
		})
	}];

	console.info(`running webpack with mode: ${mode}`);

	return {
		mode: mode,
		entry: {
			'adaptivecards-fluentui': './src/index.ts'
		},
		output: {
			path: path.resolve(__dirname, "./dist"),
			filename: devMode ? "[name].js" : "[name].min.js",
			library: "ACFluentUI"
		},
		devtool: devMode ? "inline-source-map" : "source-map",
		module: {
			rules: [{
				test: /\.tsx?$/,
				loader: "awesome-typescript-loader"
			},
			{
				test: /\.css$/,
				use: ['style-loader', 'css-loader']
			},
			{
				test: /\.scss$/,
				use: ['style-loader', 'css-loader', 'sass-loader']
			}
			]
		},
		node: {
			fs: 'empty'
		},
		resolve: {
			extensions: [".ts", ".tsx", ".js", ".jsx"]
		},
		plugins: [
			new CleanWebpackPlugin(),
			new HtmlWebpackPlugin({
				title: "Adaptive Cards Fluent UI Example",
				template: "./index.html"
			})
		],
		externals: externals
	}
};

const path = require('path');
const CopyWebpackPlugin = require('copy-webpack-plugin');

module.exports = (env, argv) => {
    const mode = argv.mode || 'development';
    const devMode = mode === 'development';

    console.info('running webpack with mode:', mode);

    return {
        mode: mode,
        entry: { 'adaptivecards-react': './src/adaptivecards-react.ts' },
        output: {
            path: path.resolve(__dirname, './dist'),
            filename: devMode ? '[name].js' : '[name].min.js',
            libraryTarget: 'umd',
            library: 'AdaptiveCards',
            globalObject: 'this'
        },
        devtool: devMode ? 'inline-source-map' : 'source-map',
        devServer: {
            static: {
                directory: './dist'
            }
        },
        externals: {
            'react': 'React',
        },
        resolve: { extensions: ['.ts', '.tsx', '.js'] },
        module: {
            rules: [
                {
                    test: /\.tsx?$/,
                    loader: 'ts-loader',
                    exclude: /(node_modules|__tests__)/
                }
            ]
        },
        plugins: [
            new CopyWebpackPlugin({
                patterns: [
                    {
                        from: 'node_modules/adaptivecards/dist/*.css',
                        to: './[name][ext]'
                    }
                ]
            })
        ]
    };
}

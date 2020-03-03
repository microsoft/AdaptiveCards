var path = require('path')
var merge = require('webpack-merge')
var baseConfig = require('./webpack.config.base')

var env = process.env.NODE_ENV || 'development'

module.exports = merge(baseConfig, {
  mode: env,
  entry: './demo/main.js',
  output: {
    path: path.resolve(__dirname, './demo/dist'),
    publicPath: '/demo/dist',
    filename: 'build.js'
  },
  module: {
    rules: [
      {
        test: /\.css$/,
        use: [
          'vue-style-loader',
          'css-loader',
          'postcss-loader'
        ]
      },
      {
        test: /\.scss$/,
        use: [
          'vue-style-loader',
          'css-loader',
          'postcss-loader',
          'sass-loader'
        ]
      }
    ]
  }
})

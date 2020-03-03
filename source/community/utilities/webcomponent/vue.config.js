module.exports = {
  chainWebpack: config => {
    config.module
      .rule('vue')
      .use('vue-loader')
        .loader('vue-loader')
        .tap(options => {
          options.shadowMode = true
          return options
        })
    config.module
      .rule('css')
      .oneOf('vue')
      .use('vue-style-loader')
        .tap(options => {
          options.shadowMode = true
          return options
        })
    config.module
      .rule('scss')
      .oneOf('vue')
      .use('vue-style-loader')
        .tap(options => {
          options.shadowMode = true
          return options
        })
    },
  css: {
    modules: true,
   // I'm using material-components-web, this option is to use it.
    loaderOptions: {
      sass: {
        includePaths: ['node_modules']
      }
    }
  }
}
module.exports = (api) => {
    api.cache(true)
  
    return {
        presets: ['module:metro-react-native-babel-preset'],
        plugins: [
            '@babel/plugin-transform-runtime',
            '@babel/plugin-proposal-class-properties',
        ].map(require.resolve),
    }
}
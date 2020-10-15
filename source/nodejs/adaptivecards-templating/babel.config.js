module.exports = function (api) {
    api.cache(false);
    const presets = [
        [ "@babel/preset-typescript"],
        [
            "@babel/preset-env",
            {
                "corejs": { "version":3 },
                "useBuiltIns": "usage",
                "targets": {
                    "browsers": [
						"last 2 versions",
						"ie >= 11",
						"not ie < 11",
						"not android > 0",
						"not ios > 0",
					]
                }
            }
        ]
    ];
    const plugins = [
        ["@babel/plugin-proposal-decorators",{"decoratorsBeforeExport":true}],
		["@babel/plugin-proposal-class-properties"],
		["@babel/plugin-transform-modules-commonjs"],
		["@babel/plugin-transform-runtime", { useESModules: false }]];
    return {
        presets,
        plugins
    };
};
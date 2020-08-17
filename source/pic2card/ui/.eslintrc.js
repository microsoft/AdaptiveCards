module.exports = {
    root: true,
    env: {
        node: true
    },
    extends: [
        "plugin:vue/essential",
        "plugin:prettier/recommended", // we added this line
        "@vue/prettier"
    ],
    rules: {
        "no-console": "off",
        "no-debugger": "off"
    },
    parserOptions: {
        parser: "babel-eslint"
    }
};

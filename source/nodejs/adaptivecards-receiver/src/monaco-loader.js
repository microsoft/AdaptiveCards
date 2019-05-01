// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
function loadMonacoEditor(jsonSchema, callback) {
    require.config({ paths: { 'vs': '/node_modules/monaco-editor/min/vs' } });
    require(['vs/editor/editor.main'], function () {
        if (jsonSchema) {
            var config = {
                schemas: [
                    {
                        uri: "http://adaptivecards.io/schemas/adaptive-card.json",
                        schema: jsonSchema,
                        fileMatch: ["*"],
                    }
                ],
                validate: false,
                allowComments: true
            }

            monaco.languages.json.jsonDefaults.setDiagnosticsOptions(config);
        }

        monacoEditor = monaco.editor.create(
            document.getElementById('editor'),
            {
                folding: true,
                validate: false,
                fontSize: 13.5,
                language: 'json',
                minimap: {
                    enabled: false
                }
            }
        );

        window.addEventListener('resize', function () {
            monacoEditor.layout();
        });

        //monacoEditor.layout();

        callback();
    });
}

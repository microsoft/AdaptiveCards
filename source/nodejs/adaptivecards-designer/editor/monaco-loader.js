function loadMonacoEditor(jsonSchema, callback) {
    require.config({ paths: { 'vs': './editor/monaco/min/vs' } });
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
            document.getElementById('jsonEditorHost'),
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

        callback();
    });
}

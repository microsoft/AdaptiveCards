// This script will be run within the webview itself
// It cannot access the main VS Code APIs directly.
(function () {
       const vscode = acquireVsCodeApi();
       $(document).ready(function(){
               
            // Create an AdaptiveCard instance
            var adaptiveCard = new AdaptiveCards.AdaptiveCard();

            // Use Fabric controls when rendering Adaptive Cards
            ACFabric.useFabricComponents();

            var cardHostConfig = $('#divConfig').text();
            adaptiveCard.hostConfig = new AdaptiveCards.HostConfig(JSON.parse(cardHostConfig));
        
            // Adaptive Cards - Actions
            adaptiveCard.onExecuteAction = function (action) {
                  vscode.postMessage({
                     command: 'action',
                     text: JSON.stringify(action._processedData)
                 })
            };

            var cardPayload = $('#divData').text();
            // Parse the card payload
            adaptiveCard.parse(JSON.parse(cardPayload));

            // Render the card to an HTML element:
            var renderedCard = adaptiveCard.render();

            $('#cardHost').append(renderedCard).show();
       })

}());
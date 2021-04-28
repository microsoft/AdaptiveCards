import * as AC from 'adaptivecards';
import * as markdownit from 'markdown-it';

/**
 * Our input change handler for 'file-picker'
 * @param {Event} e The change event
 */
function fileChosen(e: Event) : void {
    // get input element
    const fileInputElem = <HTMLInputElement>e.target;

    // get file list
    const fileList = fileInputElem.files;
    if (fileList.length === 1) {
        // only render a card if a file was chosen
        setTimeout(() => renderNewAdaptiveCard(fileList[0]), 0);
    }
}

/**
 * Renders supplied Adaptive Card to the 'card-target' element
 * @param {File} jsonFile File to render as an Adaptive Card
 */
function renderNewAdaptiveCard(jsonFile : File): void {
    // read text out of chosen file
    const textPromise = jsonFile.text();

    // this is the element we want to render the Adaptive Card to
    const renderTarget = document.getElementById('card-target');

    // clear any existing children (in case this isn't the first card we've
    // rendered)
    while (renderTarget.lastElementChild) {
        renderTarget.removeChild(renderTarget.lastElementChild);
    }

    // file content ready
    textPromise.then((fileContent) => {
        const adaptiveCard = new AC.AdaptiveCard();


        adaptiveCard.parse(JSON.parse(fileContent));
        adaptiveCard.render(renderTarget);
        // note that you could also choose to render to a local HTMLElement
        // object like this:
        //   let myRenderedCard = adaptiveCard.render();
    });
}

// wire up file picker change event handler
document.getElementById('file-picker').addEventListener('change', fileChosen);

// enable markdown processing
AC.AdaptiveCard.onProcessMarkdown = function (text, result) {
    result.outputHtml = markdownit().render(text);
    result.didProcess = true;
};

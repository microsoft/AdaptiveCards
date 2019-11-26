// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
"use strict";

var path = require("path");
var fs = require("fs");

hexo.extend.helper.register('code_and_card', function (jsonPath, templatePath = undefined, dataPath = undefined) {
	const url_for = hexo.extend.helper.get('url_for').bind(hexo);

	const payloadUrl = url_for(`/payloads/${path.basename(jsonPath)}`);
	let templateAttribute = null;
	let dataAttribute = null;
	let designerUrl = url_for(`/designer/index.html?card=${encodeURIComponent(payloadUrl)}`);

	const templating = dataPath && fs.existsSync(dataPath);
	
	let div = `
	<div class="w3-cell-row w3-margin-bottom reverse-order-mobile code-and-card">
		<div class="w3-container w3-cell w3-mobile w3-rest code-snippet hide-with-templating" style="display: ${templating ? 'none' : 'display'}">
			<div class="codeHeader">
				<span class="language">JSON</span>
				<button aria-label="Copy code" class="action copy-code">
					<span><i class="far fa-copy"></i> Copy</span>
				</button>
			</div>
			<pre><code class="json w3-mobile">${fs.readFileSync(jsonPath)}</code></pre>
		</div>`;

	if (templating) {
		let dataUrl = url_for(`/payloads/${path.basename(dataPath)}`);
		let templateUrl = url_for(`/payloads/${path.basename(templatePath)}`);
		templateAttribute = `data-template-url=${templateUrl}`;
		dataAttribute = `data-data-url="${dataUrl}"`;
		designerUrl =  url_for(`/designer/index.html?card=${encodeURIComponent(templateUrl)}&data=${encodeURIComponent(dataUrl)}`);
		div += `
		<div class="w3-container w3-cell w3-mobile w3-rest code-snippet show-with-templating">
			<div class="codeHeader">
				<span class="language">Data JSON</span>
				<button aria-label="Copy code" class="action copy-code">
					<span><i class="far fa-copy"></i> Copy</span>
				</button>
			</div>
			<pre><code class="json w3-mobile code-short">${fs.readFileSync(dataPath)}</code></pre>
			<div class="codeHeader">
				<span class="language">Template JSON</span>
				<button aria-label="Copy code" class="action copy-code">
					<span><i class="far fa-copy"></i> Copy</span>
				</button>
			</div>
			<pre><code class="json w3-mobile">${fs.readFileSync(templatePath)}</code></pre>
		</div>`;
	}

	div += `
		<div class="w3-container w3-cell w3-mobile card" >
			<div class="codeHeader">
				<span class="language">Adaptive Card</span>
				<button data-designer-url="${designerUrl}" aria-label="Try it yourself" class="w3-button ac-blue action try-adaptivecard">
					<span>Try it Yourself <i class="fas fa-chevron-right"></i></span>
				</button>
			</div>
			<div class="adaptivecard" data-card-url="${payloadUrl}" ${templateAttribute} ${dataAttribute}></div>
		</div>
	</div>`;

	return div;
});

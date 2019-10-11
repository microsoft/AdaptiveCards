// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
"use strict";

var path = require("path");

hexo.extend.helper.register('code_and_card', function (jsonPath) {
	const get_content = hexo.extend.helper.get('get_content').bind(hexo);
	const url_for = hexo.extend.helper.get('url_for').bind(hexo);
	const payloadUrl = url_for(`/payloads/${path.basename(jsonPath)}`);
	const designerUrl = url_for(`/designer/index.html?card=${encodeURIComponent(payloadUrl)}`);

	return `
	<div class="w3-cell-row w3-margin-bottom reverse-order-mobile code-and-card">

		<div class="w3-container w3-cell w3-mobile w3-rest code-snippet">
			<div class="codeHeader">
				<span class="language">JSON</span>
				<button aria-label="Copy code" class="action copy-code">
					<span><i class="far fa-copy"></i> Copy</span>
				</button>
			</div>
			<pre><code class="json w3-mobile">${get_content(jsonPath)}</code></pre>
		</div>
	
		<div class="w3-container w3-cell w3-mobile card" >
			<div class="codeHeader">
				<span class="language">Adaptive Card</span>
				<button data-designer-url="${designerUrl}" aria-label="Try it yourself" class="w3-button ac-blue action try-adaptivecard">
					<span>Try it Yourself <i class="fas fa-chevron-right"></i></span>
				</button>
			</div>
			<div class="adaptivecard">${get_content(jsonPath)}</div>
		</div>
		
	</div>`;

});

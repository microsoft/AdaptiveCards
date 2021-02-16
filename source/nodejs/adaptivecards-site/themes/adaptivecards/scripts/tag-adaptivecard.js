// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

// This tag makes using an AdaptiveCard in a blog post
// USAGE in .md file:
// 
// {% adaptivecard [URL] %}
//
hexo.extend.tag.register('adaptivecard', function (args) {
	const url_for = hexo.extend.helper.get('url_for').bind(hexo);
	var payloadUrl = args[0];
	var designerUrl = url_for(`/designer/index.html`);

	return `
		<div class="codeHeader">
			<span class="language">Adaptive Card</span>
			<button aria-label="Try it yourself" class="w3-button ac-blue action try-adaptivecard">
				<span>Try it Yourself <i class="fas fa-chevron-right"></i></span>
			</button>
		</div>
		<div class="adaptivecard" data-designer-url="${designerUrl}" data-card-url="${payloadUrl}"></div>`;	
});
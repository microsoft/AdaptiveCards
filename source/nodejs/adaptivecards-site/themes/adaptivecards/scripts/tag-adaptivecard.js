// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
hexo.extend.tag.register('adaptivecard', function (args) {
	var payloadUrl = args[0];
		console.log(args);
	const url_for = hexo.extend.helper.get('url_for').bind(hexo);
	const designerUrl = url_for(`/designer/index.html?card=${payloadUrl}`);

	return `
		<div class="codeHeader">
			<span class="language">Adaptive Card</span>
			<button data-designer-url="${designerUrl}" aria-label="Try it yourself" class="w3-button w3-blue action try-adaptivecard">
				<span>Try it Yourself <i class="fa fa-chevron-right"></i></span>
			</button>
		</div>
		<div class="adaptivecard" data-card-url="${payloadUrl}"></div>`;	
});
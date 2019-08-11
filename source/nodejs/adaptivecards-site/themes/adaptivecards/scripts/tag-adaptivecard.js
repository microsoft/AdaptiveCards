// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
hexo.extend.tag.register('adaptivecard', function (args) {
	var url = args[0];
	
	return `
	<div class="code-snippet">
		<div class="codeHeader">
			<span class="language">Adaptive Card</span>
			<button aria-label="Try it yourself" class="w3-button action try-adaptivecard">
				<span>Try it Yourself <i class="fa fa-chevron-right"></i></span>
			</button>
		</div>
		<div class="adaptivecard" data-card-url="${url}"></div>
	</div>`;
});

// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
hexo.extend.tag.register('adaptivecard', function (args) {
	var url = args[0];
	return `
	<div class="code-snippet">
		<div class="codeHeader">
			<span class="language">Adaptive Card</span>
			<button aria-label="Copy code" class="action copy-code">
				<span><i class="fa fa-copy"></i> Copy</span>
			</button>
		</div>
		<div class="adaptivecard" data-card-url="${url}"></div>
	</div>`;

});

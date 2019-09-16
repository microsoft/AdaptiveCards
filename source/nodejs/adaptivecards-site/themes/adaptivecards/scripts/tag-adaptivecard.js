// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
hexo.extend.tag.register('adaptivecard', function (args) {
	var url = args[0];
	return `<div class="adaptivecard" data-card-url="${url}"></div>`;

});

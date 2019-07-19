// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
hexo.extend.helper.register('followbuttons', function (author) {

	var div = `<div class="a2a_kit a2a_kit_size_32 a2a_default_style a2a_follow" data-a2a-icon-color="transparent,#3c3c3c">
		<a class="a2a_button_github" data-a2a-follow="${author.github_username}"></a>`;

	if (author.twitter) {
		div += `<a class="a2a_button_twitter" data-a2a-follow="${author.twitter}"></a>`
	}

	div += `</div>`
	return div;

});

// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
var yaml = require('yaml-front-matter');

hexo.extend.filter.register('before_post_render', function (data) {
	if (data.layout !== "post")
		return;

	return new Promise(function (resolve, reject) {

		const frontMatter = yaml.loadFront(data.raw);
		const excerpt = frontMatter.excerpt;
		if (excerpt) {
			console.log("Got excerpt " + excerpt);

			resolve();
		} else {
			resolve();
		}

	});

});
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

hexo.extend.filter.register('after_init', function () {
	// Allow the site to deployed to a sub directory
	// E.g., set the env variable to "PR123" on the build server 
	if (process.env.SITE_ROOT) {
		hexo.config.root = `/${process.env.SITE_ROOT}/`;
	}
});
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
"use strict";

var path = require("path");

hexo.extend.helper.register('trysamplelink', function (samplePath) {
	const url_for = hexo.extend.helper.get('url_for').bind(hexo);
	const payloadPath = url_for(`/payloads/${path.basename(samplePath)}`);
	const designerPath = url_for(`/designer/index.html?card=${payloadPath}`);
	
	return `<a class="w3-btn w3-blue" 
				target="_blank" 
				href="${designerPath}">Try it Yourself »</a>`;
});

// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
"use strict";
var path = require("path");

// This helper tries to locate an asset based on it's hashed filename
// The md5 hashes are added in generator-adaptiveassets.js 
// We use hashing to ensure browsers load the latest version of files as they change

hexo.extend.helper.register('hashed_asset', function (asset) {
	let assetPath = asset;
	const url_for = hexo.extend.helper.get('url_for').bind(hexo);

	let hashedAssets = hexo.locals.get("hashedAssets");
	if (hashedAssets) {
		let hashedAsset = hashedAssets.find(a => a.originalPath === asset);
		if (hashedAsset) {
			assetPath = hashedAsset.hashedPath;
		}
	}

	let ext = path.extname(assetPath);

	return ext === '.js' ?
		`<script type="text/javascript" src="${url_for(assetPath)}"></script>`
		: `<link rel="stylesheet" href="${url_for(assetPath)}">`;

});

// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
const yaml = require('yaml-front-matter');
const request = require('request-promise');

hexo.extend.filter.register('before_post_render', function (data) {

	if (data.layout !== "post")
		return;

	const frontMatter = yaml.loadFront(data.raw);
	const github_username = frontMatter.github_username;
	data.image = frontMatter.featured_image;
	data.subtitle = frontMatter.subtitle;
	data.author = {
		github_username: "Microsoft/AdaptiveCards",
		avatar: "https://adaptivecards.io/content/adaptive-cards-100.png",
		name: "Adaptive Cards Team",
		bio: "Break outside the box of templated cards",
		webpage: "https://adaptivecards.io"
	};
	
	if (github_username) {
		// TODO: cache this
		return request({
			uri: `https://api.github.com/users/${github_username}`,
			headers: {
				'User-Agent': 'Request-Promise'
			},
			json: true
		}).then(function (githubData) {
			data.author = {
				github_username: github_username,
				avatar: githubData.avatar_url,
				name: githubData.name,
				bio: githubData.bio,
				webpage: githubData.html_url,
				twitter: frontMatter.twitter
			};
		}).catch(function (err) {
			console.log(`ERROR: Failed getting GitHub data on page ${data.source}. Message: ${err.message}`);
		});
	} else {
		console.log(`WARN: No GitHub username in page: ${data.source}`);
		
	}
});
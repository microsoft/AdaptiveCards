// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
var https = require('https');
var yaml = require('yaml-front-matter');

hexo.extend.filter.register('before_post_render', function (data) {

	return new Promise(function (resolve, reject) {
		const frontMatter = yaml.loadFront(data.raw);
		const github_username = frontMatter.github_username;

		if (github_username) {
			https.get(`https://api.github.com/users/${github_username}`, {
				headers: { "User-Agent": "Adaptive-Cards-Blog-Engine" }
			}, (resp) => {
				let response = '';

				resp.on('data', (chunk) => {
					response += chunk;
				});

				resp.on('end', () => {
					var githubData = JSON.parse(response);
					data.author = {
						github_username: github_username,
						avatar: githubData.avatar_url,
						name: githubData.name,
						bio: githubData.bio,
						webpage: githubData.html_url,
						twitter: frontMatter.twitter
					};
					data.image = frontMatter.featured_image;
					resolve();
				});

			}).on("error", (err) => {
				console.log("Error: " + err.message);
				reject();
			});
		}
		else {
			console.log("Error: No GitHub username in blog post");
			reject();
		}
	});

});
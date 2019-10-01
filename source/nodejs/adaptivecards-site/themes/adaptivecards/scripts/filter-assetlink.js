// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
'use strict';
const url = require('url');
let cheerio;

hexo.extend.filter.register('after_post_render', function(data) {
  if (!hexo.config.post_asset_folder) return;

  if (!cheerio) cheerio = require('cheerio');

  // Get asset folder's path which is root-relative to site host
  const hexoRoot = hexo.config.root.endsWith("/") ? hexo.config.root.slice(0, -1) : hexo.config.root;
  const root = hexoRoot + url.parse(data.permalink).pathname.replace(/\.[^/.]+$/, '/');
  console.info && console.info("Asset folder root-relative path: " + root);

  const keys = ['excerpt', 'more', 'content'];
  for (let i = 0; i < keys.length; i++) {
    const $ = cheerio.load(data[keys[i]], {decodeEntities: false});

    function convertLink(element, attribute) {
      $(element).each(function() {
        const attr = $(this).attr(attribute);
        if (!attr) return;  // no such attribute
        if (url.parse(attr).protocol) return;  // absolute link
        if (attr.startsWith('/')) return;  // root-relative link
        if (attr.startsWith('#')) return;  // in-page fragment link

        // Get file's path which is base-relative to asset folder
        const base = decodeURI(attr.replace(/.*?[^\.]\//, ''));
        $(this).attr(attribute, root + base);
        console.info && console.info("Converted link: " + root + base);
      });
    }

    convertLink('img', 'src');  // images
    convertLink('a', 'href');  // other files

    data[keys[i]] = $.html();
  }
});
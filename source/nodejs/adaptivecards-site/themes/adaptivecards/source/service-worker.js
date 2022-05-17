//var fs = require("fs");
const cacheName = 'designerCache';

// TODO: need to get this stuff sorted out
// Sync with canhua about what files are actually used??
const contentToCache = ['content/cats/1.png',
'content/cats/2.png',
'content/cats/3.png',
'content/connect/blog.png',
'content/connect/friends.png',
'content/connect/github.png',
'content/connect/stackoverflow.png',
'content/connect/twitter.png'];
// const contentToCache = getAllFiles('/content');
// const contentToCache.concat(getAllFiles('../../public/designer'))

self.addEventListener('install', (event) => {
  console.log("Installing service worker");

  self.skipWaiting();

  event.waitUntil(
    caches.open(cacheName).then((cache) => cache.addAll(contentToCache))
  );
});

// This method hasn't been tested yet :)
self.addEventListener('activate', (event) => {
  console.log("Activating service worker");

  // Delete all caches that are not cacheName
  event.waitUntil(caches.keys().then((keys) => {
    return Promise.all(keys.map((key) => {
      if (key !== cacheName) {
       return caches.delete(key);
      }
    }));
  }));
});

self.addEventListener('fetch', (event) => {
  console.log("Service worker is fetching");

  event.respondWith(

    caches.match(event.request).then(response => {
      if (response) {
        return response;
      }

      return fetch(event.request).then(response => {
        if (response.status == 200) {
          return caches.open(cacheName).then(cache => {
            cache.put(event.request, response.clone);
            return response;
          })
        }
      });
    });
  );
});

// function getAllFiles(dir) {
//   var fileArr = [];
// 	var files = fs.readdirSync(dir);

// 	files.forEach(function(file) {
// 		var filePath = dir + '/' + file;
// 		var stat = fs.statSync(filePath);
// 		if (stat && stat.isDirectory()) {

// 			/* Recurse into a subdirectory */
// 			fileArr = results.concat(getAllFiles(filePath));
// 		} else {

// 			/* Is a file */
// 			fileArr.push(filePath);
// 		}
// 	});

// 	return fileArr;
// }

// TODO: if we want to simplify things, we could use workbox?
// importScripts('https://storage.googleapis.com/workbox-cdn/releases/5.1.2/workbox-sw.js');
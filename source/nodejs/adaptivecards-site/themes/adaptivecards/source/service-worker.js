//var fs = require("fs");
const cacheName = 'designerCache-v2';

// TODO: need to get this stuff sorted out
// Sync with canhua about what files are used by the designer
const contentToCache = ['content/adaptive-card-200.png',
'css/extracted.css',
'css/style.css',
'css/w3.css'];
// const contentToCache = getAllFiles('/content');
// const contentToCache.concat(getAllFiles('../../public/designer'))

self.addEventListener('install', (event) => {
  console.log("Installing service worker");

  self.skipWaiting();

  event.waitUntil(
    caches.open(cacheName)
    .then(cache => {
      return cache.addAll(contentToCache);
    })
  );
});

// When we activate a new service worker, we delete the outdated caches
self.addEventListener('activate', (event) => {
  console.log("Activating service worker");

  // Delete all caches that are not cacheName
  // The cache name is updated for new service worker versions
  event.waitUntil(
    caches.keys().then(keys => {
      return Promise.all(
        keys.map(key => {
          if (key !== cacheName) {
            return caches.delete(key);
          }
        })
      );
    })
  );
});

// The fetch listener intercepts requests for files from the network 
// and responds with the files from the cache
self.addEventListener('fetch', (event) => {
  console.log('Service worker is fetching ', event.request.url);

  event.respondWith(
    caches.match(event.request)
    .then(response => {
      if (response) {
        // The request was found in the cache
        console.log(event.request.url, ' was found in the cache.');
        return response;
      }

      // Now we will make a network request and add the files to the cache
      return fetch(event.request)
      .then(response => {
        if (response.status === 200) {
          return caches.open(cacheName).then(cache => {
            cache.put(event.request.url, response.clone());
            return response;
          });
        }
      })
    })
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
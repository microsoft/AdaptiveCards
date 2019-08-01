// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System;
using System.IO;
using System.Threading.Tasks;
using Microsoft.Azure.Storage;
using Microsoft.Azure.Storage.Blob;

namespace AdaptiveCards.Tools.IOSFeed
{
    public static class Constants
    {
        public const string ConnectionStringPath = "source/ios/tools/IOSFeed/ConnectString.txt";
        public const string ContainerId = "adaptivecardsiosblobs";
        public const string FrameworkPath = "source/ios/AdaptiveCards/AdaptiveCards";
        public const string FrameworkName = "AdaptiveCards.framework.zip";
        public const string PodspecPath = "./source/ios/tools/";
        public const string TargetPodspecPath = "./source/ios/";
        public const string PodspecName = "AdaptiveCards.podspec";
    }

    /// <summary>
    /// IOSFeed picks up ios artifact, sends to the Azure storage 
    /// and updates podspec for pod publication
    /// </summary>
    class IOSFeed
    {
        public static void Main()
        {
            // Run the examples asynchronously, wait for the results before proceeding
            ProcessAsync().GetAwaiter().GetResult();
        }

        private static async Task ProcessAsync()
        {
            string storageConnectionString;

            FileInfo fi = new FileInfo(Constants.ConnectionStringPath);
            if (!fi.Exists)
            {
                throw new InvalidOperationException("connection string file does not exist");
            }

            using (StreamReader sr = File.OpenText(Constants.ConnectionStringPath))
            {
                storageConnectionString = sr.ReadToEnd();
            }

            // Check whether the connection string can be parsed.
            CloudStorageAccount storageAccount;
            if (CloudStorageAccount.TryParse(storageConnectionString, out storageAccount))
            {
                // If the connection string is valid, proceed with operations against Blob
                // storage here.
                // Create the CloudBlobClient that represents the 
                // Blob storage endpoint for the storage account.
                CloudBlobClient cloudBlobClient = storageAccount.CreateCloudBlobClient();

                CloudBlobContainer cloudBlobContainer =
                    cloudBlobClient.GetContainerReference(Constants.ContainerId);
                await cloudBlobContainer.CreateIfNotExistsAsync();

                // Set the permissions so the blobs are public.
                BlobContainerPermissions permissions = new BlobContainerPermissions
                {
                    PublicAccess = BlobContainerPublicAccessType.Blob
                };

                await cloudBlobContainer.SetPermissionsAsync(permissions);

                var sourceFile = Path.Combine(Constants.FrameworkPath, Constants.FrameworkName);
                var blobGuid = Guid.NewGuid().ToString();
                var cloudFileName = blobGuid + Constants.FrameworkName;

                CloudBlockBlob cloudBlockBlob = cloudBlobContainer.GetBlockBlobReference(cloudFileName);

                await cloudBlockBlob.UploadFromFileAsync(sourceFile);

                BlobContinuationToken blobContinuationToken = null;
                do
                {
                    var results = await cloudBlobContainer.ListBlobsSegmentedAsync(null, blobContinuationToken);
                    // Get the value of the continuation token returned by the listing call.
                    blobContinuationToken = results.ContinuationToken;
                    foreach (IListBlobItem item in results.Results)
                    {
                        var uriString = item.Uri.ToString();
                        if (uriString.Contains(blobGuid))
                        {
                            UpdatePodSpec(uriString);
                        }
                    }
                } while (blobContinuationToken != null);
            }
            else
            {
                throw new InvalidOperationException("invalid connection string");
            }
        }

        private static void UpdatePodSpec(string uri)
        {
            var sourceFile = Path.Combine(Constants.PodspecPath, Constants.PodspecName);
            var targetFile = Path.Combine(Constants.TargetPodspecPath, Constants.PodspecName);

            FileInfo fi = new FileInfo(sourceFile);
            if (!fi.Exists)
            {
                throw new FileNotFoundException("missing podspec");
            }

            // Open the stream and read it back.
            using (StreamReader sr = File.OpenText(sourceFile))
            {
                string s = "";
                string output = "";
                while ((s = sr.ReadLine()) != null)
                {
                    if (s.Length != 0)
                    {
                        var splits = s.Split('=');
                        if (splits.Length > 0)
                        {
                            if (splits[0].Contains("spec.source"))
                            {
                                s = splits[0] + "= { :http => " + "'" + uri + "' }";
                            }
                            else if (splits[0].Contains("spec.version"))
                            {
                                var adaptiveVersion = Environment.GetEnvironmentVariable("ADCVERSION");
                                s = splits[0] + "= '" + adaptiveVersion + "'" ;
                            }
                        }

                        output += (s + "\n");
                    } else
                    {
                        output += "\n";
                    }
                }

                File.WriteAllText(targetFile, output);
            }
        }
    }
}

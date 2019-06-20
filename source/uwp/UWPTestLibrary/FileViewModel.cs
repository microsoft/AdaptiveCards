// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System;
using System.Threading.Tasks;
using Windows.Security.Cryptography;
using Windows.Security.Cryptography.Core;
using Windows.Storage;
using Windows.Storage.Streams;

namespace UWPTestLibrary
{
    public class FileViewModel
    {
        public string Name { get; set; }

        // <summary>
        // 7 characters of the SHA 1 hash of Contents
        // </summary>
        public string Hash { get; set; }

        public string Contents { get; set; }

        public static async Task<FileViewModel> LoadAsync(StorageFile file)
        {
            var answer = new FileViewModel();

            const string linkedCardsFolder = "LinkedCards\\";
            const string linkedHostConfigsFolder = "LinkedHostConfigs\\";
            const string expected = "Expected\\";
            const string results = "Results\\";
            if (file.Path.Contains(linkedCardsFolder))
            {
                answer.Name = file.Path.Substring(file.Path.IndexOf(linkedCardsFolder) + linkedCardsFolder.Length);
            }
            else if (file.Path.Contains(linkedHostConfigsFolder))
            {
                answer.Name = file.Path.Substring(file.Path.IndexOf(linkedHostConfigsFolder) + linkedHostConfigsFolder.Length);
            }
            else if (file.Path.Contains(expected))
            {
                answer.Name = file.Path.Substring(file.Path.IndexOf(expected) + expected.Length);
            }
            else if (file.Path.Contains(results))
            {
                answer.Name = file.Path.Substring(file.Path.IndexOf(results) + results.Length);
            }
            else
            {
                throw new NotImplementedException("Unknown path: " + file.Path);
            }

            answer.Contents = await FileIO.ReadTextAsync(file);
            answer.Contents = answer.Contents.Replace("\r\n", "\n");
            answer.Hash = ToSha1(answer.Contents).Substring(0, 7);

            return answer;
        }

        private static string ToSha1(string contents)
        {
            IBuffer buffer = CryptographicBuffer.ConvertStringToBinary(contents, BinaryStringEncoding.Utf8);

            // Grab the algoritm
            HashAlgorithmProvider algorithm = HashAlgorithmProvider.OpenAlgorithm("SHA1");

            // Hash the data
            IBuffer buffHash = algorithm.HashData(buffer);

            // Verify that hash succeeded
            if (buffHash.Length != algorithm.HashLength)
                throw new Exception("There was an error creating the hash.");

            // Convert to string
            return CryptographicBuffer.EncodeToHexString(buffHash);
        }
    }
}

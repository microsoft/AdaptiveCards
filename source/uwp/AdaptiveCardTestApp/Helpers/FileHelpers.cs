using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Windows.Storage;

namespace AdaptiveCardTestApp.Helpers
{
    public static class FileHelpers
    {
        private const string LINKED_HOST_CONFIGS_FOLDER_NAME = "LinkedHostConfigs";
        private const string LINKED_SAMPLES_FOLDER_NAME = "LinkedSamples";

        public static async Task<List<StorageFileAndName>> GetAllStorageFiles(StorageFolder fromFolder)
        {
            List<StorageFileAndName> answer = new List<StorageFileAndName>();

            await GetAllStorageFilesHelper(fromFolder.Name, fromFolder, answer);

            return answer;
        }

        private static async Task GetAllStorageFilesHelper(string currentName, StorageFolder currentFolder, List<StorageFileAndName> insertInto)
        {
            foreach (var file in await currentFolder.GetFilesAsync())
            {
                insertInto.Add(new StorageFileAndName()
                {
                    Name = currentName + "/" + file.Name,
                    File = file
                });
            }

            foreach (var folder in await currentFolder.GetFoldersAsync())
            {
                await GetAllStorageFilesHelper(currentName + "/" + folder.Name, folder, insertInto);
            }
        }
    }

    public class StorageFileAndName
    {
        public string Name { get; set; }

        public StorageFile File { get; set; }
    }
}

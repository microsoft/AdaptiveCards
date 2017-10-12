using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Windows.Storage;

namespace AdaptiveCardTestApp.ViewModels
{
    public class FileViewModel
    {
        public string Name { get; set; }

        public string Contents { get; set; }

        public static async Task<FileViewModel> LoadAsync(StorageFile file)
        {
            var answer = new FileViewModel();

            const string linkedCardsFolder = "LinkedCards\\";
            const string linkedHostConfigsFolder = "LinkedHostConfigs\\";
            if (file.Path.Contains(linkedCardsFolder))
            {
                answer.Name = file.Path.Substring(file.Path.IndexOf(linkedCardsFolder) + linkedCardsFolder.Length);
            }
            else if (file.Path.Contains(linkedHostConfigsFolder))
            {
                answer.Name = file.Path.Substring(file.Path.IndexOf(linkedHostConfigsFolder) + linkedHostConfigsFolder.Length);
            }
            else
            {
                throw new NotImplementedException("Unknown path: " + file.Path);
            }

            answer.Contents = await FileIO.ReadTextAsync(file);

            return answer;
        }
    }
}

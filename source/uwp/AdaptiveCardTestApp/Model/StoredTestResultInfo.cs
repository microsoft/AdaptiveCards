using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Serialization;
using System.Text;
using System.Threading.Tasks;
using Windows.Storage;

namespace AdaptiveCardTestApp.Model
{
    [DataContract]
    public class StoredTestResultInfo
    {
        [DataMember]
        public string HostConfigHash { get; set; }

        [DataMember]
        public string CardHash { get; set; }

        [DataMember]
        public string Error { get; set; }

        /// <summary>
        /// Returns null if didn't exist
        /// </summary>
        /// <param name="expectedFolder"></param>
        /// <param name="fileNameWithoutExtension"></param>
        /// <returns></returns>
        public static async Task<StoredTestResultInfo> DeserializeFromFileAsync(StorageFolder expectedFolder, string fileNameWithoutExtension)
        {
            try
            {
                var file = await expectedFolder.GetFileAsync(fileNameWithoutExtension + ".json");

                return JsonConvert.DeserializeObject<StoredTestResultInfo>(await FileIO.ReadTextAsync(file));
            }
            catch { return null; }
        }

        public async Task SaveToFileAsync(StorageFolder expectedFolder, string fileNameWithoutExtension)
        {
            var file = await expectedFolder.CreateFileAsync(fileNameWithoutExtension + ".json", CreationCollisionOption.ReplaceExisting);

            string json = JsonConvert.SerializeObject(this);

            await FileIO.WriteTextAsync(file, json);
        }
    }
}

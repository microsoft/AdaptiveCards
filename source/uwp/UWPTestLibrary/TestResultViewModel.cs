using System;
using System.Threading.Tasks;
using Windows.Graphics.Imaging;
using Windows.Storage;
using Windows.UI.Popups;
using Windows.UI.Xaml;

namespace UWPTestLibrary
{
    public class TestResultViewModel : BindableBase
    {
        public string CardName { get; set; }
        public FileViewModel CardFile { get; set; }

        public string HostConfigName { get; set; }
        public FileViewModel HostConfigFile { get; set; }

        public FileViewModel RoundtrippedJsonModel { get; set; }
        public FileViewModel ExpectedRoundtrippedJsonModel { get; set; }

        private TestStatus _status;
        public TestStatus Status
        {
            get { return _status; }
            set { SetProperty(ref _status, value); }
        }

        public string ExpectedError { get; set; }

        public StorageFile ExpectedImageFile { get; set; }
        public StorageFile ExpectedRoundtrippedJsonFile { get; set; }

        public string ActualError { get; set; }
        public StorageFile ActualImageFile { get; set; }
        public StorageFile ActualRoundTrippedJsonFile { get; set; }
        public RenderedTestResult TestResult { get; set; }
        public UIElement XamlCard { get { return TestResult?.Tree; } }

        public bool DidHostConfigChange => _oldHostConfigHash != null && _oldHostConfigHash != HostConfigFile.Hash;
        public bool DidCardPayloadChange => _oldCardHash != null && _oldCardHash != CardFile.Hash;
        public bool DidRoundtrippedJsonChange => ExpectedRoundtrippedJsonModel != null && ExpectedRoundtrippedJsonModel.Hash != RoundtrippedJsonModel.Hash;

        public StorageFolder _expectedFolder { get; set; }
        private StorageFolder _sourceHostConfigsFolder;
        private StorageFolder _sourceCardsFolder;
        private string _expectedFileNameWithoutExtension;
        private string _oldHostConfigHash;
        private string _oldCardHash;

        public static async Task<TestResultViewModel> CreateAsync(
            FileViewModel cardFile,
            FileViewModel hostConfigFile,
            RenderedTestResult renderedTestResult,
            StorageFile actualImageFile,
            StorageFile actualJsonFile,
            StorageFolder expectedFolder,
            StorageFolder sourceHostConfigsFolder,
            StorageFolder sourceCardsFolder)
        {
            var answer = new TestResultViewModel()
            {
                CardName = cardFile.Name,
                CardFile = cardFile,
                TestResult = renderedTestResult,
                HostConfigName = hostConfigFile.Name,
                HostConfigFile = hostConfigFile,
                ActualImageFile = actualImageFile,
                ActualRoundTrippedJsonFile = actualJsonFile,
                _expectedFolder = expectedFolder,
                _sourceHostConfigsFolder = sourceHostConfigsFolder,
                _sourceCardsFolder = sourceCardsFolder,
                _expectedFileNameWithoutExtension = GetStrippedFileName(hostConfigFile) + "." + GetStrippedFileName(cardFile)
            };

            try
            {
                var storedInfo = await StoredTestResultInfo.DeserializeFromFileAsync(expectedFolder, answer._expectedFileNameWithoutExtension);
                if (storedInfo == null)
                {
                    answer.Status = TestStatus.New;
                }
                else
                {
                    answer._oldHostConfigHash = storedInfo.HostConfigHash;
                    answer._oldCardHash = storedInfo.CardHash;

                    if (storedInfo.Error != null)
                    {
                        answer.ExpectedError = storedInfo.Error;
                    }
                    else
                    {
                        answer.ExpectedImageFile = await expectedFolder.GetFileAsync(answer._expectedFileNameWithoutExtension + ".png");
                        answer.ExpectedRoundtrippedJsonFile = await expectedFolder.GetFileAsync(GetStrippedFileName(answer.CardFile) + "ToJson.json");
                    }
                }

                // If both had error, compare via the error
                if (answer.ExpectedError != null && answer.TestResult.Error != null)
                {
                    if (answer.ExpectedError == answer.TestResult.Error)
                    {
                        answer.Status = TestStatus.Passed;
                    }
                    else
                    {
                        answer.Status = TestStatus.Failed;
                    }
                }

                // If neither had error, compare via the image
                else if (answer.ExpectedImageFile != null && answer.ActualImageFile != null)
                {
                    byte[] oldBytes = await GetPixelDataBytesAsync(answer.ExpectedImageFile);
                    byte[] newBytes = await GetPixelDataBytesAsync(answer.ActualImageFile);

                    if (ImageBytesAreTheSame(oldBytes, newBytes))
                    {
                        answer.Status = TestStatus.Passed;
                    }
                    else
                    {
                        answer.Status = TestStatus.Failed;
                    }

                    // Check if the round tripped json is the same
                    answer.ExpectedRoundtrippedJsonModel = await FileViewModel.LoadAsync(answer.ExpectedRoundtrippedJsonFile);
                    answer.RoundtrippedJsonModel = await FileViewModel.LoadAsync(answer.ActualRoundTrippedJsonFile);
                    if (answer.DidRoundtrippedJsonChange)
                    {
                        answer.Status = (answer.Status == TestStatus.Passed) ? TestStatus.JsonFailed : TestStatus.ImageAndJsonFailed;
                    }
                }

                // Otherwise one had image and one had error, so fail
                else
                {
                    answer.Status = TestStatus.Failed;
                }

                // See if the source chagned by checking
                // if the hashes have changed since the stored info
                if (storedInfo.HostConfigHash != hostConfigFile.Hash
                    || storedInfo.CardHash != cardFile.Hash)
                {
                    answer.Status = (answer.Status == TestStatus.Failed ||
                                     answer.Status == TestStatus.ImageAndJsonFailed ||
                                     answer.Status == TestStatus.JsonFailed) ? 
                        TestStatus.FailedButSourceWasChanged : 
                        TestStatus.PassedButSourceWasChanged;
                }
            }
            catch
            {
                // Any exceptions being thrown get reported as "New", typically this results from file
                // not found of an expected file, which means it genuinely is new
                answer.Status = TestStatus.New;
            }

            return answer;
        }

        private static async Task<byte[]> GetPixelDataBytesAsync(StorageFile file)
        {
            // Code from https://social.msdn.microsoft.com/Forums/en-US/ab86a816-ee11-49f1-bd37-9cee2b8f48f4/uwphow-to-access-the-pixel-data-of-an-image?forum=wpdevelop
            using (var stream = await file.OpenAsync(FileAccessMode.Read))
            {
                var decoder = await BitmapDecoder.CreateAsync(stream);

                var data = await decoder.GetPixelDataAsync();

                return data.DetachPixelData();
            }
        }

        private const byte TOLERANCE = 20;
        private static bool ImageBytesAreTheSame(byte[] oldBytes, byte[] newBytes)
        {
            if (oldBytes.Length != newBytes.Length)
            {
                return false;
            }

            int diffTotal = 0;

            for (int i = 0; i < oldBytes.Length; i++)
            {
                // We compare based on a tolerance, since sometimes images inside the payload are rendered slightly differently
                int diff = Math.Abs(oldBytes[i] - newBytes[i]);
                if (diff > TOLERANCE)
                {
                    // If too drastically different, we fail
                    System.Diagnostics.Debug.WriteLine("Exceeded diff tolerance: " + diff);
                    return false;
                }

                diffTotal += diff;
            }

            double diffPercent = diffTotal / (newBytes.Length * 255f);

            // We've seen this go as high as 1.5E-04, so use 5E-04 for wiggle room
            if (diffPercent > 5 * Math.Pow(10, -4))
            {
                System.Diagnostics.Debug.WriteLine("Diff percent too large: " + diffPercent);
                return false;
            }

            return true;
        }

        public Task<string> GetOldHostConfigContentsAsync()
        {
            return GetOldContentsAsync(_sourceHostConfigsFolder, HostConfigFile.Name, _oldHostConfigHash);
        }

        public Task<string> GetOldCardContentsAsync()
        {
            return GetOldContentsAsync(_sourceCardsFolder, CardFile.Name, _oldCardHash);
        }

        private static async Task<string> GetOldContentsAsync(StorageFolder folder, string name, string hash)
        {
            try
            {
                if (hash != null)
                {
                    var oldFile = await folder.GetFileAsync(GetStoredSourceFileName(name, hash));
                    return await FileIO.ReadTextAsync(oldFile);
                }
            }
            catch { }

            return "";
        }

        private static string GetStrippedFileName(FileViewModel file)
        {
            return GetStrippedFileName(file.Name);
        }

        private static string GetStrippedFileName(string name)
        {
            // Turn folder slashes into periods
            return name.Replace('\\', '.');
        }

        public async Task SaveAsNewExpectedAsync()
        {
            try
            {
                // If actual has error and existing did NOT have error, delete existing image
                if (TestResult.Error != null && ExpectedImageFile != null)
                {
                    try
                    {
                        await ExpectedImageFile.DeleteAsync(StorageDeleteOption.PermanentDelete);
                    }
                    catch { }
                }

                // Save the updated info
                await new StoredTestResultInfo()
                {
                    HostConfigHash = HostConfigFile.Hash,
                    CardHash = CardFile.Hash,
                    Error = TestResult.Error
                }.SaveToFileAsync(_expectedFolder, _expectedFileNameWithoutExtension);

                // Make sure the source files are saved (we use FailIfExists and try/catch since if file already exists no need to update it)
                try
                {
                    var sourceHostConfigFile = await _sourceHostConfigsFolder.CreateFileAsync(GetStoredSourceFileName(HostConfigFile.Name, HostConfigFile.Hash), CreationCollisionOption.FailIfExists);
                    await FileIO.WriteTextAsync(sourceHostConfigFile, HostConfigFile.Contents);

                    var oldSourceHostConfigFile = await _sourceHostConfigsFolder.CreateFileAsync(GetStoredSourceFileName(HostConfigFile.Name, _oldHostConfigHash), CreationCollisionOption.OpenIfExists);
                    await oldSourceHostConfigFile.DeleteAsync(StorageDeleteOption.PermanentDelete);
                }
                catch { }
                try
                {
                    var sourceCardFile = await _sourceCardsFolder.CreateFileAsync(GetStoredSourceFileName(CardFile.Name, CardFile.Hash), CreationCollisionOption.FailIfExists);
                    await FileIO.WriteTextAsync(sourceCardFile, CardFile.Contents);

                    var oldSourceCardFile = await _sourceCardsFolder.CreateFileAsync(GetStoredSourceFileName(CardFile.Name, _oldCardHash), CreationCollisionOption.OpenIfExists);
                    await oldSourceCardFile.DeleteAsync(StorageDeleteOption.PermanentDelete);
                }
                catch { }

                // If no error, update the image file
                if (TestResult.Error == null)
                {
                    var expectedFile = await _expectedFolder.CreateFileAsync(_expectedFileNameWithoutExtension + ".png", CreationCollisionOption.ReplaceExisting);
                    await ActualImageFile.CopyAndReplaceAsync(expectedFile);

                    var expectedJsonFile = await _expectedFolder.CreateFileAsync(GetStrippedFileName(CardFile) + "ToJson.json", CreationCollisionOption.ReplaceExisting);
                    await ActualRoundTrippedJsonFile.CopyAndReplaceAsync(expectedJsonFile);
                }

                // Update the status
                ExpectedError = TestResult.Error;
                ExpectedImageFile = ActualImageFile;
                _oldHostConfigHash = HostConfigFile.Hash;
                _oldCardHash = CardFile.Hash;
                Status = TestStatus.Passed;
            }
            catch (Exception ex)
            {
                var dontWait = new MessageDialog(ex.ToString()).ShowAsync();
            }
        }

        private static string GetStoredSourceFileName(string name, string hash)
        {
            return $"{GetStrippedFileName(name)}.{hash}.json";
        }
    }

    public enum TestStatus
    {
        /// <summary>
        /// Visual identically matched
        /// </summary>
        Passed,

        /// <summary>
        /// Visual did match, but source files (payload and host config) changed, so changes are possibly expected
        /// </summary>
        PassedButSourceWasChanged,

        /// <summary>
        /// Visual did NOT match, and source files (payload and host config) were identical, Json round tripping matches
        /// </summary>
        Failed,

        /// <summary>
        /// Visual did NOT match, and source files (payload and host config) were identical, Json round tripping doesn't match
        /// </summary>
        ImageAndJsonFailed,

        /// <summary>
        /// Visual identically matched, Roundtripped json did not match, and source files (payload and host config) were identical
        /// </summary>
        JsonFailed,

        /// <summary>
        /// Visual did NOT match, but source files (payload and host config) changed, so changes are possibly expected
        /// </summary>
        FailedButSourceWasChanged,

        /// <summary>
        /// New test, no existing Expected
        /// </summary>
        New
    }
}

// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System;
using System.Threading.Tasks;
using Windows.Graphics.Imaging;
using Windows.Storage;
using Windows.UI.Popups;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Media;

namespace UWPTestLibrary
{
    public class TestResultViewModel : BindableBase
    {
        public TestResultViewModel()
        {
            _status = new TestStatus();
        }

        public string CardName { get; set; }
        public FileViewModel CardFile { get; set; }

        public string HostConfigName { get; set; }
        public FileViewModel HostConfigFile { get; set; }

        private Brush GetBrushForResult(bool image)
        {
            if (Status.MatchedViaError)
            {
                return new SolidColorBrush(Windows.UI.Colors.Black);
            }
            else if (Status.NewCard)
            {
                return new SolidColorBrush(Windows.UI.Color.FromArgb(255, 65, 159, 254));
            }
            else if (image && Status.ImageMatched ||
                     !image && Status.JsonRoundTripMatched)
            {
                return new SolidColorBrush(Windows.UI.Colors.LimeGreen);
            }
            else
            {
                return new SolidColorBrush(Windows.UI.Colors.Red);
            }
        }

        private string GetStringForResult(bool image)
        {
            if (Status.MatchedViaError)
            {
                return "N/A";
            }
            else if (Status.NewCard)
            {
                return "New";
            }
            else if (image && Status.ImageMatched ||
                     !image && Status.JsonRoundTripMatched)
            {
                return "Passed";
            }
            else
            {
                return "Failed";
            }
        }

        public string ImageResult
        {
            get { return GetStringForResult(true); }
        }
        public Brush ImageResultBrush
        {
            get { return GetBrushForResult(true); }
        }
        public string JsonResult
        {
            get { return GetStringForResult(false); }
        }
        public Brush JsonResultBrush
        {
            get { return GetBrushForResult(false); }
        }

        public string OriginalResult
        {
            get
            {
                if (Status.NewCard)
                {
                    return "New";
                }
                else if (Status.OriginalMatched)
                {
                    return "Unchanged";
                }
                else
                {
                    return "Changed";
                }
            }
        }

        public Brush OriginalResultBrush
        {
            get
            {
                if (Status.NewCard)
                {
                    return new SolidColorBrush(Windows.UI.Color.FromArgb(255, 65, 159, 254));
                }
                else if (Status.OriginalMatched)
                {
                    return new SolidColorBrush(Windows.UI.Colors.LimeGreen);
                }
                else
                {
                    return new SolidColorBrush(Windows.UI.Colors.Red);
                }
            }
        }

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
                    answer.Status.NewCard = true;
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

                answer.Status.Error = answer.TestResult.Error;

                // If both had error, compare via the error
                if (answer.ExpectedError != null && answer.TestResult.Error != null)
                {
                    if (answer.ExpectedError == answer.TestResult.Error)
                    {
                        answer.Status.MatchedViaError = true;
                    }
                }

                // If neither had error, compare via the image
                else if (answer.ExpectedImageFile != null && answer.ActualImageFile != null)
                {
                    byte[] oldBytes = await GetPixelDataBytesAsync(answer.ExpectedImageFile);
                    byte[] newBytes = await GetPixelDataBytesAsync(answer.ActualImageFile);

                    if (ImageBytesAreTheSame(oldBytes, newBytes))
                    {
                        answer.Status.ImageMatched = true;
                    }

                    // Check if the round tripped json is the same
                    answer.ExpectedRoundtrippedJsonModel = await FileViewModel.LoadAsync(answer.ExpectedRoundtrippedJsonFile);
                    answer.RoundtrippedJsonModel = await FileViewModel.LoadAsync(answer.ActualRoundTrippedJsonFile);
                    if (!answer.DidRoundtrippedJsonChange)
                    {
                        answer.Status.JsonRoundTripMatched = true;
                    }
                }

                // See if the source chagned by checking
                // if the hashes have changed since the stored info
                if (storedInfo.HostConfigHash == hostConfigFile.Hash &&
                    storedInfo.CardHash == cardFile.Hash)
                {
                    answer.Status.OriginalMatched = true;
                }
            }
            catch
            {
                // Any exceptions being thrown get reported as "New", typically this results from file
                // not found of an expected file, which means it genuinely is new
                answer.Status.NewCard = true;
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

        public async Task SaveAsNewExpectedAsync(bool updateOriginals, bool updateJson, bool updateImage)
        {
            try
            {
                if (!updateOriginals && !updateJson && !updateImage)
                {
                    return;
                }

                // If actual has error and existing did NOT have error, delete existing image
                if (TestResult.Error != null && ExpectedImageFile != null && updateImage)
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
                    HostConfigHash = updateOriginals ? HostConfigFile.Hash : _oldHostConfigHash,
                    CardHash = updateOriginals ? CardFile.Hash : _oldCardHash,
                    Error = (updateJson || updateImage) ? TestResult.Error : ExpectedError
                }.SaveToFileAsync(_expectedFolder, _expectedFileNameWithoutExtension);

                // Make sure the source files are saved (we use FailIfExists and try/catch since if file already exists no need to update it)
                if (updateOriginals)
                {
                    try
                    {
                        var sourceHostConfigFile = await _sourceHostConfigsFolder.CreateFileAsync(GetStoredSourceFileName(HostConfigFile.Name, HostConfigFile.Hash), CreationCollisionOption.OpenIfExists);
                        await FileIO.WriteTextAsync(sourceHostConfigFile, HostConfigFile.Contents);

                        var oldSourceHostConfigFile = await _sourceHostConfigsFolder.CreateFileAsync(GetStoredSourceFileName(HostConfigFile.Name, _oldHostConfigHash), CreationCollisionOption.OpenIfExists);
                        await oldSourceHostConfigFile.DeleteAsync(StorageDeleteOption.PermanentDelete);
                    }
                    catch { }
                    try
                    {
                        var sourceCardFile = await _sourceCardsFolder.CreateFileAsync(GetStoredSourceFileName(CardFile.Name, CardFile.Hash), CreationCollisionOption.OpenIfExists);
                        await FileIO.WriteTextAsync(sourceCardFile, CardFile.Contents);

                        var oldSourceCardFile = await _sourceCardsFolder.CreateFileAsync(GetStoredSourceFileName(CardFile.Name, _oldCardHash), CreationCollisionOption.OpenIfExists);
                        await oldSourceCardFile.DeleteAsync(StorageDeleteOption.PermanentDelete);
                    }
                    catch { }
                }

                // If no error, update the image file
                if (TestResult.Error == null)
                {
                    if (updateImage)
                    {
                        var expectedFile = await _expectedFolder.CreateFileAsync(_expectedFileNameWithoutExtension + ".png", CreationCollisionOption.ReplaceExisting);
                        await ActualImageFile.CopyAndReplaceAsync(expectedFile);
                    }
                    if (updateJson)
                    {
                        var expectedJsonFile = await _expectedFolder.CreateFileAsync(GetStrippedFileName(CardFile) + "ToJson.json", CreationCollisionOption.ReplaceExisting);
                        await ActualRoundTrippedJsonFile.CopyAndReplaceAsync(expectedJsonFile);
                    }
                }

                // Create a new status with the values set to the current values
                TestStatus newStatus = new TestStatus();
                newStatus.ImageMatched = Status.ImageMatched;
                newStatus.JsonRoundTripMatched = Status.JsonRoundTripMatched;
                newStatus.MatchedViaError = Status.MatchedViaError;
                newStatus.NewCard = Status.NewCard;
                newStatus.OriginalMatched = Status.OriginalMatched;

                // Update based on the changes
                if ((TestResult.Error != null) && (updateImage || updateJson))
                {
                    newStatus.MatchedViaError = true;
                    ExpectedError = TestResult.Error;
                }
                else
                {

                    if (updateImage)
                    {
                        newStatus.ImageMatched = true;
                        ExpectedImageFile = ActualImageFile;
                    }
                    if (updateJson)
                    {
                        newStatus.JsonRoundTripMatched = true;
                    }
                }

                if (updateOriginals)
                {
                    _oldHostConfigHash = HostConfigFile.Hash;
                    _oldCardHash = CardFile.Hash;
                    newStatus.OriginalMatched = true;
                    newStatus.NewCard = false;
                }

                Status = newStatus;
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

    public class TestStatus
    {
        /// <summary>The error results match (either both pass or both fail with the same result)</summary>
        public bool MatchedViaError { get; set; } = false;

        /// <summary> The original card and host config json matches </summary>
        public bool OriginalMatched { get; set; } = false;

        /// <summary> The rendered image matches</summary>
        public bool ImageMatched { get; set; } = false;

        /// <summary> The round tripped json matches</summary>
        public bool JsonRoundTripMatched { get; set; } = false;

        /// <summary> This is a new card</summary>
        public bool NewCard { get; set; } = false;

        public string Error;

        /// <summary> Set the status to a passing result</summary>
        public void SetToPassingStatus(bool matchedViaError)
        {
            NewCard = false;
            OriginalMatched = true;

            ImageMatched = !matchedViaError;
            JsonRoundTripMatched = !matchedViaError;
            MatchedViaError = matchedViaError;
        }

        // Determine if this status is a passing result
        public bool IsPassingStatus()
        {
            return MatchedViaError || (ImageMatched && JsonRoundTripMatched);
        }

        public override string ToString()
        {
            if (IsPassingStatus())
            {
                return "Passed";
            }
            else if (NewCard == true)
            {
                if (Error == null)
                {
                    return "New Card Added";
                }
                else
                {
                    return "Error in new card";
                }
            }
            else if (!OriginalMatched && ((!ImageMatched || !JsonRoundTripMatched) && !MatchedViaError))
            {
                return "Failure with original changed";
            }
            else if (!ImageMatched && JsonRoundTripMatched)
            {
                return "Image comparison failed";
            }
            else if (ImageMatched && !JsonRoundTripMatched)
            {
                return "Json round trip failed";
            }
            else if (!ImageMatched && !JsonRoundTripMatched)
            {
                return "Json round trip and image comparison failed";
            }
            else
            {
                return base.ToString();
            }
        }
    }
}

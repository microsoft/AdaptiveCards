using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices.WindowsRuntime;
using System.Text;
using System.Threading.Tasks;
using Windows.ApplicationModel;
using Windows.Graphics.Imaging;
using Windows.Storage;
using Windows.UI.Popups;

namespace AdaptiveCardTestApp.ViewModels
{
    public class TestResultViewModel : BaseViewModel
    {
        public string CardName { get; set; }

        public string HostConfigName { get; set; }

        private TestStatus _status;
        public TestStatus Status
        {
            get { return _status; }
            set { SetProperty(ref _status, value); }
        }

        public StorageFile NewFile { get; set; }

        public StorageFile OldFile { get; set; }

        private StorageFolder _expectedFolder;
        private string _expectedFileName;

        public static async Task<TestResultViewModel> CreateAsync(FileViewModel cardFile, FileViewModel hostConfigFile, StorageFile newFile, StorageFolder expectedFolder)
        {
            var answer = new TestResultViewModel()
            {
                CardName = cardFile.Name,
                HostConfigName = hostConfigFile.Name,
                NewFile = newFile,
                _expectedFolder = expectedFolder,
                _expectedFileName = GetStrippedFileName(hostConfigFile) + "." + GetStrippedFileName(cardFile) + ".jxr"
            };

            try
            {
                answer.OldFile = await expectedFolder.GetFileAsync(answer._expectedFileName);

                byte[] oldBytes = await GetPixelDataBytesAsync(answer.OldFile);
                byte[] newBytes = await GetPixelDataBytesAsync(answer.NewFile);

                if (CompareBytes(oldBytes, newBytes))
                {
                    answer.Status = TestStatus.Passed;
                }
                else
                {
                    answer.Status = TestStatus.Failed;
                }
            }
            catch
            {
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

        private const byte TOLERANCE = 12;
        private static bool CompareBytes(byte[] oldBytes, byte[] newBytes)
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

        private static string GetStrippedFileName(FileViewModel file)
        {
            // Turn folder slashes into periods
            return file.Name.Replace('\\', '.');
        }

        public async Task SaveAsNewExpectedAsync()
        {
            try
            {
                var expectedFile = await _expectedFolder.CreateFileAsync(_expectedFileName, CreationCollisionOption.ReplaceExisting);
                await NewFile.CopyAndReplaceAsync(expectedFile);
                Status = TestStatus.Passed;
            }
            catch (Exception ex)
            {
                var dontWait = new MessageDialog(ex.ToString()).ShowAsync();
            }
        }
    }

    public enum TestStatus
    {
        /// <summary>
        /// Visual identically matched
        /// </summary>
        Passed,

        /// <summary>
        /// Visual did NOT match, and source files (payload and host config) were identical
        /// </summary>
        Failed,

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

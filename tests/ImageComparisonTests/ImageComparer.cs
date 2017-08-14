using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using ImageMagick;
using System.Diagnostics;

namespace ImageComparisonTests
{
    class ImageComparer
    {
        public static double CompareImages(string baseImagePath, string testImagePath, string diffImagePath = null)
        {
            using (var baseImage = new MagickImage(baseImagePath))
            using (var testImage = new MagickImage(testImagePath))
            {
                return CompareImages(baseImage, testImage, diffImagePath);
            }
        }

        public static double CompareImages(MagickImage baseImage, MagickImage testImage, string diffImagePath)
        {
            if (baseImage == null)
            {
                throw new ArgumentNullException($"Invalid Arg: {nameof(baseImage)}");
            }
            if (testImage == null)
            {
                throw new ArgumentNullException($"Invalid Arg: {nameof(testImage)}");
            }

            try
            {
                using (MagickImage diffImage = new MagickImage())
                {
                    var distortion = baseImage.Compare(testImage, ErrorMetric.RootMeanSquared, diffImage);
                    baseImage.Composite(diffImage, CompositeOperator.Over);
                    if (!string.IsNullOrEmpty(diffImagePath))
                    {
                        baseImage.Write(diffImagePath);
                    }
                    return distortion;
                }
            }
            catch (MagickException ex)
            {
                Debug.WriteLine($"Exception while comparing images. BaseImage: {baseImage.ToString()}," +
                    $" TestImage: {testImage.ToString()}, Exception:{ex.ToString()}");
                throw;
            }
        }
    }
}

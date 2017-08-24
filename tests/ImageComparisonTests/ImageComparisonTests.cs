using System;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using ImageMagick;

namespace ImageComparisonTests
{
    [TestClass]
    public class ImageComparisonTest
    {
        private const double AllowedDistortion = 0.05;

        [TestMethod]
        public void CompareImageTest()
        {
            string basePath = @"C:\Users\riarenas\Pictures\comparisons\big.png";
            string testPath = @"C:\Users\riarenas\Pictures\comparisons\big_test.png";
            string diffPath = @"C:\Users\riarenas\Pictures\comparisons\big_diff.png";
            double distortion = ImageComparer.CompareImages(basePath, testPath, diffPath);
            Assert.IsTrue(distortion < AllowedDistortion);
        }

    }
}

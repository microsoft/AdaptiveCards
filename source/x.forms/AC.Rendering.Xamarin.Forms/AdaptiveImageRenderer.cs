using System;
using System.Collections.Generic;
using System.Text;
using Xamarin.Forms;
using Xamarin.Forms.Pages;

namespace AdaptiveCards.Rendering.Forms
{
    public class AdaptiveImageRenderer
    {
        public static View Render(AdaptiveImage image, AdaptiveRenderContext context)
        {
            if (image.Style == AdaptiveImageStyle.Person)
            {
                Image uiImage = new Image()
                {
                    Source = image.Url
                };

                switch (image.Size)
                {
                    case AdaptiveImageSize.Small:
                        uiImage.WidthRequest = context.Config.ImageSizes.Small;
                        uiImage.HeightRequest = context.Config.ImageSizes.Small;
                        break;
                    case AdaptiveImageSize.Medium:
                        uiImage.WidthRequest = context.Config.ImageSizes.Medium;
                        uiImage.HeightRequest = context.Config.ImageSizes.Medium;
                        break;
                    case AdaptiveImageSize.Large:
                        uiImage.WidthRequest = context.Config.ImageSizes.Large;
                        uiImage.HeightRequest = context.Config.ImageSizes.Large;
                        break;
                }

                return uiImage;
            }
            else
            {
                Image uiImage = new Image()
                {
                    Source = image.Url
                };

                switch (image.Size)
                {
                    case AdaptiveImageSize.Small:
                        uiImage.WidthRequest = context.Config.ImageSizes.Small;
                        uiImage.HeightRequest = context.Config.ImageSizes.Small;
                        break;
                    case AdaptiveImageSize.Medium:
                        uiImage.WidthRequest = context.Config.ImageSizes.Medium;
                        uiImage.HeightRequest = context.Config.ImageSizes.Medium;
                        break;
                    case AdaptiveImageSize.Large:
                        uiImage.WidthRequest = context.Config.ImageSizes.Large;
                        uiImage.HeightRequest = context.Config.ImageSizes.Large;
                        break;
                }

                return uiImage;
            }
            
        }

    }
}

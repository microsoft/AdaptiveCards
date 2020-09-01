using System;
namespace AdaptiveCards.XamarinForms.Platforms.Android
{
    public class Cards
    {
        public static bool IsInitialised = false;

        public static void Init()
        {
            if(!IsInitialised)
            {
                //Do nothing, required to ensure library is loaded
                IsInitialised = true;

            }
        }
    }
}

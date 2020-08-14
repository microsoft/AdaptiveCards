// Copyright (c) Microsoft Corporation. All rights reserved. 
// Licensed under the MIT License. 
using AdaptiveCards.Rendering.Uwp;
using AdaptiveCards.Templating;
using Newtonsoft.Json.Linq;
using System;
using System.Collections.Generic;
using System.IO;
using System.Net;
using System.Runtime.InteropServices.WindowsRuntime;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Timers;
using Windows.ApplicationModel.Core;
using Windows.Graphics.Display;
using Windows.Graphics.Imaging;
using Windows.Storage.Streams;
using Windows.UI.Core;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Media.Imaging;

namespace UWPDriver
{
    // This class encompasses our UWP application that embeds a REST server on which it listens for HTTP POST requests.
    // It recieves a card payload, renders the card, creates a bitmap and returns the results.
    public sealed partial class MainPage : Page
    {
        public MainPage()
        {
            this.InitializeComponent();
            Task.Run(() => this.StartHTTPServer());
        }

        private async Task StartHTTPServer()
        {
            using (HttpListener listener = new HttpListener())
            {
                listener.Prefixes.Add("http://10.64.36.176:8800/");
                listener.Start();

                while (listener.IsListening)
                {
                    JObject resultJson = new JObject();
                    List<string> errorList = new List<string>();
                    List<string> warningList = new List<string>();
                    resultJson.Add("imageData", "");
                    resultJson.Add("warnings", "");
                    resultJson.Add("errors", "");
                    HttpListenerContext context = await listener.GetContextAsync();
                    Semaphore signal = new Semaphore(0, 1);
                    try
                    {
                        
                        // This function reads the request body and creates an adaptive card payload. It then renders
                        //the card on the UI and calls another function to create a bitmap from that card
                        await CoreApplication.MainView.CoreWindow.Dispatcher.RunAsync(CoreDispatcherPriority.Normal,
                            () =>
                            {
                                HttpListenerRequest request = context.Request;
                                Stream requestBody = request.InputStream;
                                Encoding requestEncoding = request.ContentEncoding;
                                StreamReader reader = new StreamReader(requestBody, requestEncoding);
                                string inputString = reader.ReadToEnd();
                                try
                                {
                                    JObject inputJson = JObject.Parse(inputString);
                                    string cardData = inputJson["data"].ToString();
                                    string cardTemplate = inputJson["template"].ToString();

                                    AdaptiveCardTemplate adaptiveCardTemplate = new AdaptiveCardTemplate(cardTemplate);
                                    string cardPayload = adaptiveCardTemplate.Expand(cardData);

                                    AdaptiveCardParseResult card = AdaptiveCard.FromJsonString(cardPayload);
                                    AdaptiveCardRenderer renderer = new AdaptiveCardRenderer();
                                    RenderedAdaptiveCard renderedAdaptiveCard = renderer.RenderAdaptiveCard(card.AdaptiveCard);

                                    foreach (AdaptiveWarning warning in renderedAdaptiveCard.Warnings)
                                    {
                                        warningList.Add(warning.Message);
                                    }

                                    if (renderedAdaptiveCard.FrameworkElement != null)
                                    {
                                        FrameworkElement adaptiveCardElement = renderedAdaptiveCard.FrameworkElement;
                                        adaptiveCardElement.Name = "AdaptiveCard";
                                        myGrid.Children.Add(adaptiveCardElement);

                                        // This timer is used to queue the bitmap creation of our adaptive card
                                        BitmapTimer timer = null;
                                        BoolWrapper bitmapCreated = new BoolWrapper(false);
                                        
                                        // This function checks if the layout of our grid is changed. This is because
                                        // images are loaded asynchronously and we want to create a bitmap once all 
                                        // the images have loaded.
                                        myGrid.LayoutUpdated += (sender, e) =>
                                        {
                                            if (timer != null)
                                            {
                                                timer.Stop();
                                                timer.Dispose();
                                            }

                                            timer = new BitmapTimer(2000);
                                            timer.resultJson = resultJson;
                                            timer.signal = signal;
                                            timer.errorList = errorList;
                                            timer.warningList = warningList;
                                            timer.adaptiveCardElement = adaptiveCardElement;
                                            timer.context = context;
                                            timer.bitmapCreated = bitmapCreated;
                                            timer.Elapsed += createBitmapAsync;
                                            timer.Enabled = true;
                                        };
                                    }

                                    else
                                    {
                                        errorList.Add("Unable to render the card payload");
                                        signal.Release();
                                    }

                                }
                                catch (Exception e)
                                {
                                    errorList.Add(e.Message);
                                    signal.Release();
                                }

                            });

                    }
                    catch (Exception e)
                    {
                        errorList.Add(e.Message);
                    }
                    finally
                    {
                        signal.WaitOne();
                        SendResponse(context, resultJson, errorList, warningList);

                    }

                }
            }
        }


        // This function uses the bitmap timer to create a bitmap of the adaptive card and removes it from the UI. 
        // It adds the resulting img string to our json object
        private async void createBitmapAsync(object sender, ElapsedEventArgs e)
        {
            BitmapTimer timer = (BitmapTimer)sender;
            BoolWrapper bitmapCreated = timer.bitmapCreated;
            if (!bitmapCreated.boolVal)
            {
                Semaphore signal = timer.signal;
                FrameworkElement adaptiveCardElement = timer.adaptiveCardElement;
                HttpListenerContext context = timer.context;
                List<string> errorList = timer.errorList;
                List<string> warningList = timer.warningList;
                JObject resultJson = timer.resultJson;

                await CoreApplication.MainView.CoreWindow.Dispatcher.RunAsync(CoreDispatcherPriority.Normal,
                    async () =>
                    {
                        try
                        {
                            RenderTargetBitmap adaptiveCardBitmap = new RenderTargetBitmap();

                            await adaptiveCardBitmap.RenderAsync(adaptiveCardElement, 
                                                                (int)adaptiveCardElement.ActualWidth,
                                                                (int)adaptiveCardElement.ActualHeight);

                            IBuffer pixels = await adaptiveCardBitmap.GetPixelsAsync();

                            InMemoryRandomAccessStream stream = new InMemoryRandomAccessStream();
                            BitmapEncoder encoder = await BitmapEncoder.CreateAsync(BitmapEncoder.PngEncoderId, stream);
                            encoder.SetPixelData(
                                    BitmapPixelFormat.Bgra8,
                                    BitmapAlphaMode.Straight,
                                    (uint)adaptiveCardBitmap.PixelWidth,
                                    (uint)adaptiveCardBitmap.PixelHeight,
                                    DisplayInformation.GetForCurrentView().LogicalDpi,
                                    DisplayInformation.GetForCurrentView().LogicalDpi,
                                    pixels.ToArray());

                            await encoder.FlushAsync();
                            DataReader dataReader = new DataReader(stream.GetInputStreamAt(0));
                            byte[] byteBuffer = new byte[stream.Size];
                            await dataReader.LoadAsync((uint)stream.Size);
                            dataReader.ReadBytes(byteBuffer);

                            string imgString = Convert.ToBase64String(byteBuffer);
                            resultJson["imageData"] = imgString;
                            myGrid.Children.Remove(adaptiveCardElement);
                            bitmapCreated.boolVal = true;
                            
                        }
                        catch (Exception exp)
                        {
                            errorList.Add(exp.Message);
                        }
                        finally
                        {
                            signal.Release();
                        }

                    });
            }
        }


        // This function takes the context, result json, error list and warning list and creates the result response
        // string. It then sends this string as a response to the HTTP request received earlier
        private void SendResponse(HttpListenerContext context, 
                                 JObject resultJson, 
                                 List<string> errorList, 
                                 List<string> warningList)
        {
            resultJson["warnings"] = new JArray(warningList);
            resultJson["errors"] = new JArray(errorList);
            string responseString = resultJson.ToString();
            using (HttpListenerResponse response = context.Response)
            {
                byte[] buffer = Encoding.UTF8.GetBytes(responseString);
                using (Stream output = response.OutputStream)
                {
                    output.Write(buffer, 0, buffer.Length);
                }
            }
        }
    }
}

using EventSource4Net;
using Newtonsoft.Json.Linq;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Http;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace WpfVisualizer
{
    public class HostConnection
    {
        private const string _baseUrl = "https://cardhub.azurewebsites.net/api/";
        private static HttpClient _client = new HttpClient();
        private string _hostId;
        private EventSource _eventSource;

        public event EventHandler OnClosed;
        public event EventHandler<string> OnError;
        public event EventHandler OnConnected;
        public event EventHandler<string> OnCardJsonReceived;

        public HostConnection(string hostId)
        {
            _hostId = hostId;
        }

        public void StartConnect()
        {
            _eventSource = new EventSource(new Uri(_baseUrl + "card/" + _hostId + "/subscribe"), 10000);
            _eventSource.EventReceived += _eventSource_EventReceived;
            _eventSource.StateChanged += _eventSource_StateChanged;
            _eventSource.Start(CancellationToken.None);

            StartUpdateCardJson();
        }

        private void _eventSource_StateChanged(object sender, StateChangedEventArgs e)
        {
            switch (e.State)
            {
                case EventSourceState.CLOSED:
                    OnClosed?.Invoke(this, new EventArgs());
                    break;
            }
        }

        private void _eventSource_EventReceived(object sender, ServerSentEventReceivedEventArgs e)
        {
            StartUpdateCardJson();
        }

        private bool _isGettingCard;
        private bool _needsAnotherCard;

        private async void StartUpdateCardJson()
        {
            if (_isGettingCard)
            {
                _needsAnotherCard = true;
                return;
            }

            _isGettingCard = true;

            try
            {
                string cardData = await _client.GetStringAsync(_baseUrl + "card/" + _hostId);
                TriggerNewCardReceived(cardData);
            }
            catch (Exception ex)
            {
                ShowError("Failed getting latest card");
            }

            _isGettingCard = false;
            if (_needsAnotherCard)
            {
                _needsAnotherCard = false;
                StartUpdateCardJson();
            }
        }

        private void ShowError(string message)
        {
            OnError?.Invoke(this, message);
        }

        private bool _hasReceivedFirstCard = false;
        private void TriggerNewCardReceived(string cardDataJson)
        {
            if (!_hasReceivedFirstCard)
            {
                _hasReceivedFirstCard = true;
                OnConnected?.Invoke(this, new EventArgs());
            }

            try
            {
                JObject cardData = JObject.Parse(cardDataJson);
                string cardJson = cardData.Value<string>("CardJson");
                OnCardJsonReceived?.Invoke(this, cardJson);
            }
            catch
            {
                ShowError("Invalid JSON received");
            }
        }
    }
}

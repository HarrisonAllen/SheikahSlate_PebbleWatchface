var myAPIKey = 'REDACTED'; // key for open weather
var metric = false; // celsius or fahrenheit
var use_current_location = false; // use GPS
var lat = '42.36'; // latitude for weather w/o GPS
var lon = '-71.1'; // longitude for weather w/o GPS

// Import the Clay package
var Clay = require('pebble-clay');
// Load our Clay configuration file
var clayConfig = require('./config');
// Initialize Clay
var clay = new Clay(clayConfig);

// request data from url
var xhrRequest = function (url, type, callback) {
	var xhr = new XMLHttpRequest();
	xhr.onload = function () {
		callback(this.responseText);
	};
	xhr.open(type, url);
	xhr.send();
};

function locationSuccess(pos) {
	// Construct URL
	var url = 'http://api.openweathermap.org/data/2.5/weather?' + 
		'lat=' + (use_current_location ? pos.coords.latitude : lat) + 
		'&lon=' + (use_current_location ? pos.coords.longitude : lon) + 
		'&appid=' + myAPIKey +
		'&units=' + (metric ? 'metric' : 'imperial');

	xhrRequest(url, 'GET',
		function(responseText) {
			// responseText contains a JSON object with weather info
			var json = JSON.parse(responseText);

			var temperature = json.main.temp;

			var conditions = 0; // sunny
			var id = json.weather[0].id;
			if (id > 802) {
				conditions = 2; // cloudy
			} else if (id > 800) {
				conditions = 1; // partly cloudy
			} else if (id == 800) {
				conditions = 0; // sunny
			} else if (id > 700) {
				conditions = 2; // cloudy
			} else if (id > 600 || id == 511) { //snow/freezing rain
				conditions = 4; // snowy
			} else if (id > 300) {
				conditions = 3; // rainy
			} else if (id > 200) {
				conditions = 5; // stormy
			}

			var dictionary = {
				'TEMPERATURE': temperature,
				'CONDITIONS': conditions
			};
			Pebble.sendAppMessage(dictionary,
				function(e) {
					console.log('Weather info sent to Pebble successfully!');
				},
				function(e) {
					console.log('Error sending weather info to Pebble!');
				}
			);
		}
	);
}

function locationError(err) {
	console.log('Error requesting location!');
}

function getWeather() {
	if (use_current_location == true) { // if using current location
		navigator.geolocation.getCurrentPosition(
			locationSuccess,
			locationError,
			{timeout: 15000, maximumAge: 60000}
		);
	} else {
		locationSuccess(null); // otherwise, just grab using lat and lon
	}
}

// send nothing to pebble, which will prompt weather request
function pokePebble() {
	var dictionary = {};
	Pebble.sendAppMessage(dictionary,
		function(e) {
			console.log('Pebble poked successfully!');
		},
		function(e) {
			console.log('Error poking Pebble!');
		}
	);
}

// Listen for when the watchface is opened
Pebble.addEventListener('ready',
	function(e) {
		console.log('PebbleKit JS ready!');

		// Get the initial weather
		pokePebble();
	}
);

// Listen for when an AppMessage is received
Pebble.addEventListener('appmessage',
	function(e) {
		console.log('AppMessage received!');
		var dict = e.payload;

		if ('TemperatureMetric' in dict) // use celsius/fahrenheit
			metric = dict['TemperatureMetric'] == 1;
		if ('UseCurrentLocation' in dict) // use current location
			use_current_location = dict['UseCurrentLocation'] == 1;
		if ('Latitude' in dict) // latitude if not using current location
			lat = dict['Latitude'];
		if ('Longitude' in dict) // longitude if not using current location
			lon = dict['Longitude'];

		getWeather();
	}
);

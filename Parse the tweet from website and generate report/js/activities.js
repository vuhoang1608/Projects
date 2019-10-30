function parseTweets(runkeeper_tweets) {
	//Do not proceed if no tweets loaded
	if(runkeeper_tweets === undefined) {
		window.alert('No tweets returned');
		return;
	}
	
	tweet_array = runkeeper_tweets.map(function(tweet) {
		return new Tweet(tweet.text, tweet.created_at);
	});	

	//--------------------------------Part 2-1-------------------------------- :
	//Generate a Map named activityMap {activityType : count}
	var activityMap = new Map();
	tweet_array.forEach(function(element) {
		if(activityMap.get(element.activityType) == undefined){
			activityMap.set(element.activityType,1);
		}
		activityMap.set(element.activityType,activityMap.get(element.activityType) + 1);
	});
	//Return number of activity types
	$('#numberActivities').text(activityMap.size);

	//Return the most 3 activities
	//Sort the activityMap
	activityMap[Symbol.iterator] = function* () {
		yield* [...this.entries()].sort((a, b) => b[1] - a[1]);
	}	
	
	//Modify html file to return the most 3 activities			
	var i = 1;
	var firstMostActivity = "";
	var secondMostActivity = "";
	var thirdMostActivity = "";

	//define 3 variables to use to calculate longest and shortest distance in the most 3 activities
	for (let [key, value] of activityMap) {     // get data sorted
		if(i == 1) 
		{
			$('#firstMost').text(key);
			firstMostActivity = key;		
		}
		else if(i == 2)
		{
			$('#secondMost').text(key);			
			secondMostActivity = key;
		} 
		else if(i == 3)
		{ 
			$('#thirdMost').text(key);
			thirdMostActivity = key;
			break;
		}
		i++;
	}	

	//--------------------------------End Part 2-1--------------------------------

	//--------------------------------Part 2-2--------------------------------
	//Graphing activities by distance	
	//Generate an activityDict array in this format below
	//var activityDict = [{"Type_Of_Activity": "run","Activity_Distancec": 3.0}]
	var activityDict = [];
	var tempObject1 = {};
	for (let [key, value] of activityMap)
	{
		tempObject1 = {};
		tempObject1.Type_Of_Activity = key;
		tempObject1.Activity_Distance = value;
		activityDict.push(tempObject1);
	}	
	//Define the activity plot
	activity_vis_spec = {
	  "$schema": "https://vega.github.io/schema/vega-lite/v4.0.0-beta.8.json",
	  "description": "A graph of the number of Tweets containing each type of activity.",
	  "data": 
		{	
		"values": activityDict
	  },	  
	  //TODO: Add mark and encoding
	  "mark" : "bar",
	  "encoding": {
		  "x" : {"field": "Type_Of_Activity", "type" : "ordinal", "sort": "-Activity_Distance"},
		  "y" : {"field": "Activity_Distance" , "type" : "quantitative"}
	  }
	};	
	vegaEmbed('#activityVis', activity_vis_spec, {actions:false});

	//Graph the plot of distance by day from the most 3 activities
	//Generate the distanceDict array that have the most 3 activities
	var distanceDict = [];
	var tempObject2 = {};	
	var options = {weekday: 'short'};
	tweet_array.forEach(function(element) {
		tempObject2 = {};
		if(element.activityType == firstMostActivity || element.activityType == secondMostActivity || element.activityType == thirdMostActivity)
		{
			tempObject2.Day = element.time.toLocaleDateString('en-US', options);
			tempObject2.Distance = element.distance;
			tempObject2.Type_Of_Activity = element.activityType;
			distanceDict.push(tempObject2);
		}
	});
	//Graph the plot
	distance_vis_spec = {
		"$schema": "https://vega.github.io/schema/vega-lite/v4.0.0-beta.8.json",
		"description": "A graph of the distance of top three activities for each day.",
		"data": 
		{	
		"values": distanceDict
		},
		"mark" : "point",
		"encoding": {
			"x" : {	"field": "Day", 
					"type" : "ordinal", 
					"sort": ["Sun","Mon", "Tue", "Wed", "Thu", "Fri", "Sat"]
			},
			"y" : {	"field": "Distance",
					"type" : "quantitative"
			},
			
			"color":{"field": "Type_Of_Activity", "type": "nominal"},
			"tooltip" : [{"field" : "Distance", "type":"quantitative"},
					{"field" : "Type_Of_Activity", "type":"nominal"}]
	  }
	};
	vegaEmbed('#distanceVis', distance_vis_spec, {actions:false});
	//Set the mean of distance plot as NO DISPLAY
	$('#distanceVis').css("display", "none"); 

	//Graph the plot mean of distance by date from the most 3 activities
	distance_vis_aggregated_spec = {
		"$schema": "https://vega.github.io/schema/vega-lite/v4.0.0-beta.8.json",
		"description": "A graph of the mean of distance of top three activities for each day.",
		"data": 
		{	
		"values": distanceDict
		},
		"mark" : "point",
		"encoding": {
			"x" : {	"field": "Day", 
					"type" : "ordinal", 
					"sort": ["Sun","Mon", "Tue", "Wed", "Thu", "Fri", "Sat"]					
			},
			"y" : {	"field": "Distance",
					"type" : "quantitative",
					"aggregate": "mean",
					"format":".2f"
			},			
			"color":{"field": "Type_Of_Activity", "type": "nominal"},
			"tooltip" : [{"field" : "Distance", "type":"quantitative", "aggregate": "mean", "format":".2f"},
					{"field" : "Type_Of_Activity", "type":"nominal"}]
	  }
	};

	vegaEmbed('#distanceVisAggregated', distance_vis_aggregated_spec, {actions:false});
	//Set this plot as NO DISPLAY
	$('#distanceVisAggregated').css("display", "none");
	
	//Add 1 line above the graph (for better format)
	$('</br>').insertAfter("button");
	//Edit button to switch between graphs using toggle()
	$('#aggregate').click((event) => {
		if($('#aggregate').text() == "Show means")
		{
			$('#distanceVis').css("display", "none");
			$('#distanceVisAggregated').toggle();
			$('#aggregate').text('Show all activities');
		}
		else
		{	
			$('#distanceVisAggregated').css("display", "none");
			$('#distanceVis').toggle();
			$('#aggregate').text('Show means');
		}
	});

	//Use those visualizations to answer the questions about which activities tended to be longest and when.
	$('#longestActivityType').text('run');
	$('#shortestActivityType').text('run, walk, and bike');
	$('#weekdayOrWeekendLonger').text('weekend');
}

//Wait for the DOM to load
$(document).ready(function() {
	loadSavedRunkeeperTweets().then(parseTweets);
});
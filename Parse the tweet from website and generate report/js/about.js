function parseTweets(runkeeper_tweets) {
	//Do not proceed if no tweets loaded
	if(runkeeper_tweets === undefined) {
		window.alert('No tweets returned');
		return;
	}

	tweet_array = runkeeper_tweets.map(function(tweet) {
		return new Tweet(tweet.text, tweet.created_at);
	});
	
	//This line modifies the DOM, searching for the tag with the numberTweets ID and updating the text.
	//It works correctly, your task is to update the text of the other tags in the HTML file!
	//Get the total number of tweet
	var totalTweet = 0;
	tweet_array.forEach(function(element)
	{
		if(element.text.search("#Runkeeper") != -1 || element.text.search("#runkeeper") != -1) totalTweet++;
	});
	//Update the HTML
	$('#numberTweets').text(totalTweet);

	//Part 1-1: Get the first and last Date of Tweet
	var firstDate = tweet_array[0].time;
	var lastDate = tweet_array[0].time;
	
	tweet_array.forEach(function(element) {
		if(firstDate > element.time) firstDate = element.time;
		if(lastDate < element.time) lastDate = element.time;
	});

	var options = {year: 'numeric', month: 'long', day: 'numeric'};
	//Update the HTML
	$('#lastDate').text(lastDate.toLocaleDateString('en-US', options));
	$('#firstDate').text(firstDate.toLocaleDateString('en-US', options));	
	
	//Part 1-2 && 1-3: Tweet categories
	var completed = 0;
	var liveEvent = 0;
	var achieve = 0;
	var other = 0;
	var written = 0;	
	tweet_array.forEach(function(element) {
		if(element.source == "completed_event")	completed++;
		if(element.source == "achievement") achieve++;
		if(element.source == "live_event") liveEvent++;
		if(element.source == "miscellaneous") other++;
		if(element.written) written++;
	});
	
	//Update the HTML
	$('.completedEvents').text(completed);
	$('.completedEventsPct').text(math.format((completed/totalTweet*100),{notation: 'fixed',precision: 2}) + '%');
	$('.liveEvents').text(liveEvent);
	$('.liveEventsPct').text(math.format((liveEvent/totalTweet*100),{notation: 'fixed',precision: 2}) + '%');
	$('.achievements').text(achieve);
	$('.achievementsPct').text(math.format((achieve/totalTweet*100),{notation: 'fixed',precision: 2}) + '%');
	$('.miscellaneous').text(other);
	$('.miscellaneousPct').text(math.format((other/totalTweet*100),{notation: 'fixed',precision: 2}) + '%');
	$('.written').text(written);
	$('.writtenPct').text(math.format((written/completed*100),{notation: 'fixed',precision: 2}) + '%');
}

//Wait for the DOM to load
$(document).ready(function() {
	loadSavedRunkeeperTweets().then(parseTweets);
});
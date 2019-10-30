function parseTweets(runkeeper_tweets) {
	//Do not proceed if no tweets loaded
	if(runkeeper_tweets === undefined) {
		window.alert('No tweets returned');
		return;
	}
	
	tweet_array = runkeeper_tweets.map(function(tweet) {
		return new Tweet(tweet.text, tweet.created_at);
	});		
	
	//TODO: Filter to just the written tweets
	var i = 0;	
	while(i < tweet_array.length)
	{
		if(!tweet_array[i].written)
			delete tweet_array.splice(i,1);		
		else
			i++;
	}
	
	//Create an event listener when keyword is inputted
	var input = document.getElementById('textFilter');
	input.onkeyup = function(event) 
	{
		var counter = 1;
		var inputKey = ($(this).val()).toLowerCase();	
		//empty the table everytime an input is detected		
		$('#tweetTable').empty();

		//Add a new line to the table that contains the search keyword
		tweet_array.forEach(function(element)	{						
			if(element.text.toLowerCase().search(inputKey) != -1 && inputKey != "" )	
			{
				$('#tweetTable').append(element.getHTMLTableRow(counter));				
				counter++;
			}
		});
		//Update search count and search content HTML field
		$('#searchCount').text(counter-1);
		$('#searchText').text(inputKey);
	};	
}

function addEventHandlerForSearch() {
	//TODO: Search the written tweets as text is entered into the search box, and add them to the table
	//I did not implement this function, I implement EventListener in the above function.
}

//Wait for the DOM to load
$(document).ready(function() {
	addEventHandlerForSearch();
	loadSavedRunkeeperTweets().then(parseTweets);	
});
class Tweet {
	private text:string;
	time:Date;

	constructor(tweet_text:string, tweet_time:string) {
        this.text = tweet_text;
		this.time = new Date(tweet_time);//, "ddd MMM D HH:mm:ss Z YYYY"
	}

	//returns either 'live_event', 'achievement', 'completed_event', or 'miscellaneous'
    get source():string {
        if(this.text.search("#Runkeeper") != -1 || this.text.search("#runkeeper") != -1){
            if(this.text.includes("posted") || this.text.includes("completed") || this.text.includes("Completed"))
            {
                return "completed_event";
            }
            else if(this.text.startsWith("Achieved"))
            {
                return "achievement";
            }
            else if(this.text.startsWith("Watch") && this.text.includes("Live"))
            {
                return "live_event";
            }
            else{
                return "miscellaneous";
            }
        }
        return "miscellaneous";         
    }

    //returns a boolean, whether the text includes any content written by the person tweeting.
    get written():boolean {
        //Remove tag #Runkeeper
        var edittedText = this.text.replace("#Runkeeper"," ");
        edittedText = this.text.replace("#runkeeper"," ");

        //Remove URL
        var indexOfHttp = edittedText.search("http");        
        var temp = edittedText.substring(indexOfHttp);
        edittedText = edittedText.replace(temp," ");

        //Get and compare the pattern with the text
        var pattern = /^Just (completed|posted) .+ (with @Runkeeper. Check it out!|TomTom)/;      
        if(pattern.test(edittedText)) return false;
        return true;
        
    }

    get writtenText():string {
        if(!this.written) {
            return "";
        }
        //TODO: parse the written text from the tweet
        //get the index of "http" and return a substring of tweet starting from 0 to index of http
        var indexOfLink = this.text.search("http");
        var resultText = this.text.substring(0,indexOfLink); 
        return resultText;
    }

    get activityType():string {
        if (this.source != 'completed_event') {
            return "unknown";
        }
        //Get the substring from "km" or "mi" to "-" or "with" to get the activity type
        var activity = "";
        var start = 0;
        var end = 0;
        var indexOfDash = this.text.indexOf("-");
        var indexOfWith = this.text.search("with");
        var indexOfDistanceKm = this.text.search("km");
        var indexOfDistanceMi = this.text.search("mi");        

        if(indexOfDistanceKm != -1) start = indexOfDistanceKm;
        else if(indexOfDistanceMi != -1) start = indexOfDistanceMi;

        if(indexOfDash != -1) end = indexOfDash;
        else if(indexOfWith != -1) end = indexOfWith;

        //Remove tweet with no activity
        if(indexOfDash <= 0 && indexOfWith <= 0 && indexOfDistanceKm <= 0 && indexOfDistanceMi <= 0)
            return "unknown";

        //get the activity type
        activity = this.text.substring(start+3,end-1);

        //Remove substring that contains "posted"
        if(activity.search("posted") != -1)
        {
            var indexOfA = activity.indexOf(" a ");
            var indexOfAn = activity.indexOf(" an ");
            var indexOfIn = activity.indexOf(" in ");

            if(indexOfA != -1) activity = activity.substring(indexOfA+3,indexOfIn);
            if(indexOfAn != -1) activity = activity.substring(indexOfAn+4,indexOfIn);
        }       

        //remove invalid activity
        if(activity.search("http") != -1 || activity.search(" - ") != -1) activity = "unknown";
        return activity;
    }

    get distance():number { //distance is in mile
        if(this.source != 'completed_event') {
            return 0;
        }
        //TODO: prase the distance from the text of the tweet        
        var indexOfDistanceKm = this.text.search("km");
        var indexOfDistanceMi = this.text.search("mi");
        var indexOfA = this.text.search("a");
        var distance = 0;

        //convert to mile if distance is in km
        if(indexOfDistanceKm != -1) { 
            distance = parseFloat(this.text.substring(indexOfA+2,indexOfDistanceKm-1));
            distance = parseFloat((distance / 1.609).toFixed(2));
        }

        if(indexOfDistanceMi != -1) distance = parseFloat(this.text.substring(indexOfA+2,indexOfDistanceMi-1));
        return distance;
    }

    getHTMLTableRow(rowNumber:number):string {
        //TODO: return a table row which summarizes the tweet with a clickable link to the RunKeeper activity
        var edittedText = this.text;
        //Get the index of "http" and "#Runkeeper"
        var indexOfHttp = edittedText.search("http");        
        var runkeeperIndex = edittedText.search("#Runkeeper") || edittedText.search("#runkeeper");
        
        //get the written text, the URL, and "#runkeeper"
        var text = edittedText.substring(0,indexOfHttp);
        var url = edittedText.substring(indexOfHttp,runkeeperIndex);
        var runkeeperHashtag = edittedText.substring(runkeeperIndex);
        //Get the activity type
        var typeOfActivity = this.activityType;
        
        var newRow = '<tr><td>' + rowNumber + '</td><td>' + typeOfActivity + '</td><td>' + text + '<a href=' + url + 'target = "_blank">' + url + '</a>' + runkeeperHashtag + '</td></tr>';
        return newRow ;
    }
}
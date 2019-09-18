*** Search Engine Optimization ***
1. Use web crawler to fetch data from ICS department of UC Irvine.
2. Save data as html format in local folder. Folder is orranized in folder number (0 to 75), each folder contains 500 webpages' content.
   Ex: The path 2 / 15 means 2nd folder and file number 15.
3. Use Beautiful Soup to read the html page. Only read content inside these following tags: header, h1 to h7, p, article
4. Generate a Inverted Index dictionary with key (keyword) and value (TF-IDF score,extra score for keyword appears on header tag)
5. Apply lemmatization, stemming technique in generating Inverted Index dictionary.
6. Rank each pair (query, document) using Vector Space Similarity technique.
7. Return the top 10 results to the user.
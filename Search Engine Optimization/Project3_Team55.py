#!/usr/bin/python3
# @Vu Tran
""" Team 55
    Vu Tran - 48894667
    MHD Anas Alaya - 41551580
    Hoang Tran - 20843397
    CS 121 - Project 3  """

""" Objective: 
    Build INDEX table from 37,497 files
    Parsing for keywords
    """

""" Data structure:
    INDEX is a dict= {keyword:(set of (docID,tf-idf,term frequency****)), ...}, works as main database
        **** term frequency of the keyword appear in title, hearder, bold text (We call SPECIAL TERM)
    docID = foldNum * 1000 + location file number of that folder, ex: 34/156 => docID = 34156
    """

""" Algorithm:
    For each docID do
        IF a "keyword" found not existing in the INDEX
            adding it to INDEX[keys]
            adding docID to the set of that "keywords" in INDEX
        ELSE
            adding docID to the set of that "keywords" in INDEX
    Store INDEX database on a file
    """



""" Reference: https://nlp.stanford.edu/IR-book/html/htmledition/contents-1.html
             : https://arxiv.org/pdf/1208.6109.pdf => wordlength < 20 ?
    """

import os, sys, math, json, io
import re
from collections import Counter
import nltk
from nltk.corpus import stopwords  # Get the common english stopwords
from bs4 import BeautifulSoup, SoupStrainer  # Get content from html files
from pathlib import Path
from operator import itemgetter
from nltk.stem  import PorterStemmer  # https://www.datacamp.com/community/tutorials/stemming-lemmatization-python

INDEX = dict()  # INDEX = {keyword: {set of (docID, tf-idf score)}}
posting_list = dict()  # = { 'keyword' : (doc1,doc2, ....) }
docLocation = dict()  # = { "docID" : path}
NUM_OF_FOLDERS = 1 # 0-74, 0-499
NUM_OF_FILES_PER_FOLDER = 500  # 500        #0-74, 0-499
MAXWORDLENGTH = 20
MINWORDLENGTH = 2
TOTAL_NUM_OF_DOC = 37497 #37497 #total documents


def buildINDEX(rootFolder):
    # 0-74, 0-499
    # Build docID - filename mapping
    for i in range(0, NUM_OF_FOLDERS):
        for j in range(0, NUM_OF_FILES_PER_FOLDER):
            filePath = rootFolder + "/" + str(i) + "/" + str(j)  # WEBPAGES_RAW/0/12
            docID = i * 1000 + j
            docLocation[str(docID)] = filePath

    # Traverse each file docID and processing
    for docID in docLocation:
        try:
            buildPostingList(docID)
            print("processing docID: " + docID)
        except:
            continue

#Build the posting list {keyword : (list of docID)}
def buildPostingList(docID):
    tokenList, temp_set = getTokensList(docLocation[docID])
    for keyword in tokenList:
        # todo here
        if keyword not in posting_list:
            tmpSet = set()
            tmpSet.add(docID)
            posting_list[keyword] = tmpSet  # posting_list = {keyword : (doc1, doc2, ...)}
        else:
            posting_list[keyword].add(docID)

#Build list with IDF score only - used to calculate tf-idf in the INDEX
def build_list_with_IDF_score(tokenList):
    for keyword in tokenList:
        tokenList[keyword] = math.log(TOTAL_NUM_OF_DOC/len(tokenList[keyword]),10)
    return tokenList

#Build the complete INDEX file with {keyword : (docID, tf-idf, term frequency)}
def updating_INDEX():
    idf_score_list = build_list_with_IDF_score(posting_list)

    # Traverse each file docID and processing
    for docID in docLocation:
        try:
            processOneDoc(docID, idf_score_list)
            print("Populating complete INDEX file: " + docID)
        except:
            continue

#Adding the keyword into INDEX and calculating tf-idf
def processOneDoc(docID, idf_score_list):
    dictList, title_list = buildDict(docLocation[docID])  #dictList is a dict of (keyword : frequency)
    for keyword in dictList:
        # todo here
        tmpTuple = (docID, int((1 + math.log(dictList[keyword],10)) * idf_score_list[keyword] *100),
                    title_list[keyword])  # Calculate tf-idf score and add term frequency for SPECIAL TERM

        if keyword not in INDEX:
            tmpSet = list()
            tmpSet.append(tmpTuple)
            INDEX[keyword] = tmpSet  # INDEX = {keyword: {set of (docID, if-tdf score, term frequency)}}
        else:
            INDEX[keyword].append(tmpTuple)
            INDEX[keyword].sort(key=itemgetter(1, 2), reverse=True)

def locateTSV(docID, fileName):
    docDirNum, docFileNum = divmod(docID, 1000)
    docTag = str(docDirNum) + "/" + str(docFileNum)
    # print(docTag)
    foundURL = "URL Not Found"
    try:
        with open(fileName, "r") as f:  # todo: multi-threading
            for line in f:
                pattern = line.split('\t', maxsplit=2)
                for pat in pattern:
                    # print(pat)
                    if pat == docTag and len(pattern) > 1:
                        foundURL = pattern[1]
    except:
        foundURL = "Error-Finding-URL"
    return foundURL

def writeINDEXToFile():
    try:
        with open("./output/INDEX.txt", "w", encoding='utf8') as f:
            for keyword in INDEX:
                    f.write(keyword)
                    f.write('\t')
                    f.write(str(INDEX[keyword]))
                    f.write('\n')
    except ValueError as e:
        print(e,'<-----------------WriteINDEXFile')

def writeJSONFile():
    try:
        with open("./output/INDEX.json",'w', encoding='utf8') as file:
            json.dump(INDEX, file, separators=(',', ':'), ensure_ascii=False)
    except ValueError as e:
        print(e,"<--------------- writeJSONfile")

def reportMilestone1():
    # Build & store INDEX database
    # Need to change / to \ if using WINDOW
    if sys.platform.startswith('win32'):
        slash = "\\"
    else:
        slash = "/"

    rootFolderPath = os.getcwd() + slash + "WEBPAGES_RAW"
    #TSVFile = rootFolderPath + slash + "bookkeeping.tsv"
    #indexFilePath = rootFolderPath + slash + "INDEX"
    buildINDEX(rootFolderPath)
    updating_INDEX() #Hoang added code
    writeJSONFile()  # Hoang added code
    writeINDEXToFile()

##################### Text Processing #################################################################
def getTokensList(fileName):
    """ Convert file name text contents into sorted list of tokens in alphabetically
        Reading lines in file: O(n)
        Sorting token list: O(nlgn)
        Thus, complexity: O(nlgn)    """
    tokensList = []
    pattern = re.compile('[a-z0-9]+', re.IGNORECASE)
    stopWords = set(stopwords.words('english'))  # Init here for the performance

    # https://beautiful-soup-4.readthedocs.io/en/latest/index.html?highlight=SoupStrainer
    # https://www.w3schools.com/html/html_intro.asp
    parsingTags = ['p', 'a', 'div', 'li']
    parsingOnly = SoupStrainer(parsingTags)
    try:
        with open(fileName, "r", encoding='utf8') as f:  # todo: multi-threading
            soupObj = BeautifulSoup(f, features="html.parser", parse_only=parsingOnly) #parse every tag in a html

            vipList = [i.get_text(" ") for i in soupObj.find_all(['h1', 'h2', 'h3', 'b'])]
            if (soupObj.title != None):
                vipList.append(soupObj.title.text)
            vipString = "".join(vipList)

            content = soupObj.get_text(" ")
            tokenLine = pattern.findall(content.lower()) # Tokenize
            tokensList = filterPattern(tokenLine, stopWords) # stopWord + stemming

            tokenLine2 = pattern.findall(vipString.lower())  # Tokenize
            tokensList2 = filterPattern(tokenLine2, stopWords)  # stopWord + stemming
    except Exception as e:
        print(e, "<----getTokenList")

    return sorted(tokensList), sorted(tokensList2)  # to ensure later sorted(dictList) return descending by value and ascending by key

def buildDict(fileName):
    """ Returns a list of pairs (key,value)
        [("keys" -> "number of appearance of the key")] and sorted by the highest appearance
        Complexity: O(nlgn)    """

    tokenList, headersList = getTokensList(fileName)
    dictList = Counter()
    headerDict = Counter()

    for token in tokenList:
        dictList[token] += 1

    for token in headersList:
        headerDict[token] += 1

    return dictList, headerDict

def filterPattern(tokenList, stopWords):  # Applying all possible rules to filtering out non-sense keywords
    filteredList = []
    Porter = PorterStemmer()
    for pattern in tokenList:
        selectPattern = True
        if (re.compile('^[0-9].*', re.IGNORECASE)).match(str(pattern)) \
                or (re.compile('^[0-9]+', re.IGNORECASE)).match(str(pattern)) \
                or (pattern in stopWords) \
                or (len(str(pattern)) > MAXWORDLENGTH) \
                or (len(str(pattern)) <= MINWORDLENGTH):
            selectPattern = False

        if selectPattern:
            stemPattern = Porter.stem(pattern)  # stemming it before adding
            filteredList.append(stemPattern)
            # filteredList.append(pattern)

    return filteredList

def stemList(listOfTokens):  # Applying stemming rules for each keywords
    Porter = PorterStemmer()
    for i in range(len(listOfTokens)):
        # applying the stemmer of each item in the list
        listOfTokens[i] = Porter.stem(listOfTokens[i])
    return None

def main():
    reportMilestone1()
main()
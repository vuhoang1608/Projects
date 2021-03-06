import sys, os, re, urllib, nltk, operator, math
from urllib.request import urlopen
from urllib.parse import urlparse, parse_qs, urljoin
from nltk.corpus import stopwords, wordnet
from bs4 import BeautifulSoup as bs
from nltk.stem import WordNetLemmatizer

valid_link_testing = {'http://www.ics.uci.edu/~magda' : '46/309',
'http://www.ironwood.ics.uci.edu/wiki:navigation?rev=1376434009&vecdo=print' :'4/215',
'http://www.cml.ics.uci.edu/aiml/page/12' : '4/214',
'http://www.ics.uci.edu/~irus//css/98/mini-tutorial/tsld018.htm' : '4/217',
'http://www.sli.ics.uci.edu/Site/UserCreation' : '4/211',
'http: // www.ics.uci.edu / ~pattis / ICS - 21 / lectures / inheritancei / index.html' : '74/184',
'http://www.ics.uci.edu/~dock/manuals/oechem/api/node939.html' : '20/407'}
#----------------------------------------------------
stop_words = set(stopwords.words('english'))
valid_link_index = dict() #contains valid links and its index
bad_links = set()
crawler_traps = set()
lemma = WordNetLemmatizer()
#------------------Check valid links and save to dictionary-------

#use is_valid function from project 2
def is_valid(url):
    '''
    Function returns True or False based on whether the url has to be
    downloaded or not.
    Robot rules and duplication rules are checked separately.
    This is a great place to filter out crawler traps.
    '''
    global bad_links  # sets
    global crawler_traps  # sets

    if len(url) > 100:
        crawler_traps.add(url)
        return False

    # parse url string to url object
    parsed = urlparse(url)
    # print url

    if parsed.scheme not in set(["http", "https"]):
        bad_links.add(url)
        return False

    # look for calendar in path (trap)
    elif re.search(r'^.*calendar.*$', parsed.path):
        crawler_traps.add(url)
        return False

    # another trap
    elif re.search(r'^.*ganglia.*$', parsed.path):
        crawler_traps.add(url)
        return False

    # regx for Repeating Directories:
    elif re.search(r'^.*?(/.+?/).*?\1.*$|^.*?/(.+?/)\2.*$', parsed.path):
        crawler_traps.add(url)
        return False

    try:
        if ".ics.uci.edu" in parsed.hostname and not re.match(
                ".*\.(css|js|bmp|gif|jpe?g|ico" + "|png|tiff?|mid|mp2|mp3|mp4" \
                + "|wav|avi|mov|mpeg|ram|m4v|mkv|ogg|ogv|pdf" \
                + "|ps|eps|tex|ppt|pptx|doc|docx|xls|xlsx|names|data|dat|exe|bz2|tar|msi|bin|7z|psd|dmg|iso|epub|dll|cnf|tgz|sha1" \
                + "|thmx|mso|arff|rtf|jar|csv" \
                + "|rm|smil|wmv|swf|wma|zip|rar|gz|pdf)$", parsed.path.lower()):
            return True
        else:
            crawler_traps.add(url)
            return False

    except TypeError:
        print("TypeError for ", parsed)
        return False

    finally:
        bad_links.add(url)

#This function check the link in bookkeeping and save the valid links (with index) into a dictionary
def check_link(file):
    if not os.path.isfile(file):
        print("File path {} does not exist. Exiting...".format(file))
        sys.exit()
    index = set()
    with open(file) as fp:
        for line in fp:
            index = re.findall(r'\S+', line)

            if index[1].startswith('www'):
                index[1] = 'http://' + index[1]
            else:
                index[1] = 'http://www.' + index[1]

            if is_valid(index[1]):
                valid_link_index[index[1]] = index[0]
    return valid_link_index

#------------------From HTMl to Word Frequency--------
# Given a text string, remove all non-alphanumeric
# characters (using Unicode definition of alphanumeric).

#use the treebank_tag and return the correct word form
#Refer: https://stackoverflow.com/questions/15586721/wordnet-lemmatization-and-pos-tagging-in-python
def get_wordnet_pos(treebank_tag):
    if treebank_tag.startswith('J'):
        return wordnet.ADJ
    elif treebank_tag.startswith('V'):
        return wordnet.VERB
    elif treebank_tag.startswith('N'):
        return wordnet.NOUN
    elif treebank_tag.startswith('R'):
        return wordnet.ADV
    else:
        return wordnet.NOUN

def stripNonAlphaNum(text):
    import re
    s = text.lower()
    result = re.findall(r'[a-z0-9]+',s)
    result = nltk.pos_tag(result)
    lemma_list = set()
    for w in result:
        lemma_list.add(lemma.lemmatize(w[0],get_wordnet_pos(w[1])))
    return result

def removeStopwords(wordlist, stopwords):
    return [w for w in wordlist if w not in stopwords]

def html_to_word_frequency(url):

    response = urlopen(url)
    html = response.read()
    soup = bs(html, 'html.parser')
    text = soup.text
    fullwordlist = stripNonAlphaNum(text)
    wordlist = removeStopwords(fullwordlist, stop_words)

    return wordlist

def create_freqDict_id_list():
    freqDict_id_list = []
    count = 0
    for link, docid in valid_link_index.items():
        try:
            frequency_dict = html_to_word_frequency(link)
            temp = {'docId' : docid, 'Frequency_Dict': frequency_dict}
            freqDict_id_list.append(temp)

        except urllib.error.URLError:
            continue
        #these statements just keeps track of how many links has been processed
        count += 1
        remain = len(valid_link_index) - count
        print("Remaining links: " + str(remain))
        if(remain < 12000):
            break

    return freqDict_id_list

def create_postinglist(wordDict):
    posting_list = {}
    for tempDict in wordDict:
        id = tempDict['docId']
        for n in range(0, len(tempDict['Frequency_Dict'])):
            if tempDict['Frequency_Dict'][n] not in posting_list:
                posting_list[tempDict['Frequency_Dict'][n]] = list()
            posting_list[tempDict['Frequency_Dict'][n]].append(id)

    result = sorted(posting_list.items(), key=operator.itemgetter(0))
    return result

def main():
    global valid_link_index
    file = 'bookkeeping.tsv'
    print(len(check_link(file)))
    #------------------------------------------------
    freqDict_id_list = create_freqDict_id_list()
    #print(tf(freqDict_id_list))
    #print(freqDict_id_list[0]['Frequency_Dict'][0][1] / 3)

    #------------------

    # output_file1 = open("tf_score.txt", "w")
    # for s in tf(freqDict_id_list):
    #     output_file1.write(str(s) + "\n")
    # output_file1.close()

    output_file2 = open("posting_list.txt", "w")
    for s in create_postinglist(freqDict_id_list):
        output_file2.write(str(s) + "\n")
    output_file2.close()

main()

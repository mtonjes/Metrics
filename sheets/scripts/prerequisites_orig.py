'''
Created on Oct 10, 2013

@author: mantas.stankevicius@cern.ch
@author: ali.mehmet.altundag@cern.ch

Last modification May 14, 2015
(see git repo for history of modification and blaming)
'''

from BeautifulSoup import BeautifulSoup
import cookielib, urllib, urllib2, getpass, os, re

import time

# Source: http://stackoverflow.com/questions/13925983/login-to-website-using-urllib2-python-2-7

class Login:
    def __init__(self):
        # The action/ target from the form
        authentication_url = """https://cms.cern.ch/iCMS/analysisadmin/loginnice?url='/jsp/page.jsp?mode=news'"""

        # Store the cookies and create an opener that will hold them
        self.cj = cookielib.CookieJar()
        self.opener = urllib2.build_opener(urllib2.HTTPCookieProcessor(self.cj))

        # Add our headers
        self.opener.addheaders = [('User-agent', 'RedditTesting')]

        # Install our opener (note that this changes the global opener to the one
        # we just made, but you can also just call opener.open() if you want)
        urllib2.install_opener(self.opener)

        # Input parameters we are going to send
        payload = {
            'username':None,
            'password':None,
            'login':'login'
            }

        print "Please enter your login and password"

        if not payload['username']:
            payload['username'] = raw_input("Username:")

        if not payload["password"]:
            payload["password"] = getpass.getpass()

        print "Thank you!"

        # Use urllib to encode the payload
        data = urllib.urlencode(payload)

        print "Thank you x2!"

        # Build our Request object (supplying 'data' makes it a POST)
        req = urllib2.Request(authentication_url, data)

        print "Thank you x3!"

        # Make the request and read the response
        resp = urllib2.urlopen(req)

        print "Thank you x4!"

        self.contents = resp.read()

        print "Thank you x5!"
        print self.contents
    def getPage(self, url):
        return urllib2.urlopen(url).read()

    def getLoginResponse(self):
        return self.contents

print "Out of login class"

def fetchAnalyses():
    print "Getting the list of analyses takes just a few seconds..."

#    This is the global page, by default it will show the first 1,000 records. In our case, with more than
#    1,000 records, we need to access in a different way. Next lines will show how that is done.
#    data = handle.getPage('http://cms.cern.ch/iCMS/analysisadmin/cadilines?awg=any')

#    This is the way I think we can approach it, p=1, p=2, ..., p=n; will have set's of up to one thousand
#    records. As of May '15 we have ~1,400, so we would need just p=1 and p=2. It will be maybe a long time
#    before we actually need to go above p=2.
    print "Getting page 1!"
    data1 = handle.getPage('http://cms.cern.ch/iCMS/jsp/analysis/admin/cadilines.jsp?d-446288-p=1&awg=any')
    print "Getting page 2!"
    data2 = handle.getPage('http://cms.cern.ch/iCMS/jsp/analysis/admin/cadilines.jsp?d-446288-p=2&awg=any')
    print "Getting page 3!"
    data3 = handle.getPage('http://cms.cern.ch/iCMS/jsp/analysis/admin/cadilines.jsp?d-446288-p=3&awg=any')
# May '17 have 1,866, so may need to go above p=2 soonish
# May '18 have 2,017, so have to do 3 pages
# June 2020 have 2,310, still 3 pages

    data = data1 + data2 + data3
    
    f = open("data/analyses.html", "w")
    f.write(data)
    f.close()

    print "Got list of analyses.\n"

    # creating analyses folder where all fetched analyses will be stored
    if not os.path.exists("data/analyses"):
        os.makedirs("data/analyses")

    print "Retrieving the page for each analysis.\n"

    soup = BeautifulSoup(data)
    trs = soup.findAll("tr",{ "class" : re.compile(r"^(odd|even)$") })
    print "Retrieving an individual HTML file takes 0.5 sec,"
    print "but there are {0} of them, so a rough estimation".format( len(trs) )
    print "of {0:.2f} min (give or take) for this step (with".format( len(trs)*0.5/60.)
    print "progress report every 200 analyses).\n"

    index=1
    for tr in trs:
        if len(tr.findAll("td")) > 2:
            tds = tr.findAll("td")
            analysis_url = tds[0].find("a")["href"]

            parts = analysis_url.split("&")
            firstPart = parts[0].split("?")
            id = firstPart[1].replace("line=","")
            #download analysis details page
            analysisHTML = handle.getPage("http://cms.cern.ch/iCMS/analysisadmin/getan?code="+id)
            o = open("data/analyses/id_"+id+".html", "w")
            o.write(analysisHTML)
            o.close()
            if index%200 == 0:
                print "{0} pages retrieved. The last page was for the {1} analysis.".format( index, id )
            index += 1

    print "Done"

def fetchANotes():
    data = handle.getPage('http://cms.cern.ch/iCMS/user/annotes')
    f = open("data/annotes.html", "w")
    f.write(data)
    f.close()

# ---------------------------------- #
# countries = ["Armenia", "Austria", "Belarus", "Belgium",
#              "Brazil", "Bulgaria", "China", "Colombia",
#              "Croatia", "Cyprus", "Czech Republic", "Egypt",
#              "Estonia", "Finland", "France", "Georgia",
#              "Germany", "Greece", "Hungary", "India",
#              "Iran", "Ireland", "Italy", "Korea", "Lithuania",
#              "Malaysia", "Mexico", "Netherlands", "New Zealand",
#              "Pakistan", "Poland", "Portugal", "Russia",
#              "Serbia", "Spain", "Switzerland", "Taiwan", "Thailand",
#              "Turkey", "Ukraine", "United Kingdom", "USA", "USA2", "Uzbekistan"]
# ---------------------------------- #
# new countries, Sep 2018
countries = ["Armenia", "Austria", "Belarus", "Belgium",
             "Brazil", "Bulgaria", "China", "Colombia",
             "Croatia", "Cyprus", "Czech Republic", "Egypt",
             "Estonia", "Finland", "France", "Georgia",
             "Germany", "Greece", "Hungary", "India",
             "Iran", "Ireland", "Italy", "Korea", "Latvia",
             "Lebanon", "Lithuania", "Malaysia", "Mexico",
             "Montenegro", "Netherlands", "New Zealand", "Oman",
             "Pakistan", "Poland", "Portugal", "Russia", "Saudi Arabia",
             "Serbia", "Spain", "Sri Lanka", "Switzerland", 
             "Taiwan", "Thailand", "Turkey", "Ukraine", "United Kingdom", 
             "USA", "USA2", "Uzbekistan"]
def fetchAuthors():
    global handle
    url = 'http://cms.cern.ch/iCMS/jsp/secr/sqlCountryMembers.jsp?country='
    for i in countries:
        if os.path.isfile("data/authors/%s.html" % i):
            continue
        else:
            if not handle:
                handle = Login()
        if i == "USA2":
            data = handle.getPage('http://cms.cern.ch/iCMS/jsp/secr/stats/cmsUS.jsp')
        else:
            data = handle.getPage(url + i.replace(' ', '%20'))
        f = open("data/authors/%s.html" % i, "w")
        f.write(data)
        f.close()

def fetchDetailPage(anotes_id):
    global handle
    if handle == None:
        handle = Login()

    url = 'http://cms.cern.ch/iCMS/jsp/db_notes/showNoteDetails.jsp?noteID='
    data = handle.getPage(url + anotes_id.replace(' ', '%20'))
    f = open("data/detail_pages/%s.html" % anotes_id.replace('/', '_'), "w")
    f.write(data)
    f.close()

def authorsCheck():
    for i in countries:
        if not os.path.isfile("data/authors/%s.html" % i):
            return True
    return False
# ---------------------------------- #

handle = None

print "Checking for prerequisites"

if not os.path.exists("data"):
    os.makedirs("data")

if not os.path.exists("sheets"):
    os.makedirs("sheets")

if not os.path.isfile("data/analyses.html"):
    print "Fetching analyses"
    handle = Login()
    print "Logged in!"
    fetchAnalyses()

#print "waiting 100s"
#time.sleep(100)

if not os.path.isfile("data/annotes.html"):
    if handle == None:
        handle = Login()
    fetchANotes()

if not os.path.exists("data/authors"):
    os.makedirs("data/authors")

# ---------------------------------- #
if not os.path.exists("data/detail_pages"):
    os.makedirs("data/detail_pages")

fetchAuthors()

def parseANotes():
    f = open("data/annotes.html")
    source = f.read()
    f.close()
    bs     = BeautifulSoup(source)
    tr     = bs.findAll("tr", {})

    CMSNoteIDIndex  = 0
    TitleIndex      = 1
    submitDateIndex = 2
    CountryIndex    = 3
    InstCodeIndex   = 4
    SubmitterIndex  = 5
    NauthIndex      = 6

    # Data format:
    # [[CMSNoteID, Title, submitDate, Country, InstCode, Submitter, Nauth], ... ]
    CMSANNotes = []

    for i in tr[1:len(tr)]:
        cells = i.findChildren('td')
        CMSANNotes.append([cells[CMSNoteIDIndex].text.encode('utf-8'),
                    cells[TitleIndex].text.replace('\n', ' ').replace('\r', ' ').encode('utf-8'),
                    cells[submitDateIndex].text.encode('utf-8'),
                    cells[CountryIndex].text.encode('utf-8'),
                    cells[InstCodeIndex].text.encode('utf-8'),
                    cells[SubmitterIndex].text.encode('utf-8'),
                    cells[NauthIndex].text.encode('utf-8')])
    return CMSANNotes

parsedANotes = parseANotes()

for i in parsedANotes:
    if not os.path.exists("data/detail_pages/%s.html" % i[0].replace('/', '_')):
        fetchDetailPage(i[0])
# ---------------------------------- #

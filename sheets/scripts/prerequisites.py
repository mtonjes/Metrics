'''
Created on Oct 10, 2013

@author: mantas.stankevicius@cern.ch
@author: ali.mehmet.altundag@cern.ch

Last modification May 14, 2015
(see git repo for history of modification and blaming)
'''
#
from bs4 import BeautifulSoup
import sys
import subprocess
import pathlib
from pathlib import Path
import http.cookiejar, urllib.request, urllib.parse, urllib.error, urllib.request, urllib.error, urllib.parse, getpass, os, re
#
import time
#
# Source: http://stackoverflow.com/questions/13925983/login-to-website-using-urllib2-python-2-7
# Modified for python3 https://docs.python.org/3/howto/urllib2.html
# authentication (Andreas Pfeiffer)
# authentication switched to auth-get-sso-cookie https://gitlab.cern.ch/-/snippets/1457
# debugging assistance from Nick Manganelli - thanks!!!
class Login:
    def __init__(self):
        url = "https://icms.cern.ch/tools/"
#        cmd = 'ls -alh ~/private/sso-auth-cookie'
        cmd = 'auth-get-sso-cookie --outfile ~/private/sso-auth-cookie -u %s ;' % (url,)
#        print("got sso-cookie to file ~/private/sso-auth-cookie")
        self.contents = cmd
#        print(cmd)
        loginres=''
#        print("in SSOgetPage.\n")
        cmd += 'curl --silent --cookie-jar ~/private/sso-auth-cookie --cookie ~/private/sso-auth-cookie -k -L %s ' % (url,)
        res=''
        try:
            res = subprocess.check_output(cmd, shell=True, stderr=subprocess.STDOUT)
#            print( res.decode('utf-8') )
        except Exception as e:
            print ( "ERROR: got: %s" % (str(e),) )
            print ( "    output: %s " % (str(res)) )

    def getPage(self, url):
        return urllib.request.urlopen(url).read()
#
    def getLoginResponse(self):
        return self.contents
#
print("Out of SSO class")
#
def fetchAnalyses():
    print("Getting the list of analyses takes just a few seconds...")
#
#    This is the global page, by default it will show the first 1,000 records. In our case, with more than
#    1,000 records, we need to access in a different way. Next lines will show how that is done.
#    data = handle.getPage('http://cms.cern.ch/iCMS/analysisadmin/cadilines?awg=any')
#
#    This is the way I think we can approach it, p=1, p=2, ..., p=n; will have set's of up to one thousand
#    records. As of May '15 we have ~1,400, so we would need just p=1 and p=2. It will be maybe a long time
#    before we actually need to go above p=2.
#    handle = Login()
    print("Getting page 1!")
    data1 = handle.getPage('https://icms.cern.ch/tools/idProvider/demand/https://cms.cern.ch/iCMS/jsp/analysis/admin/cadilines.jsp?d-446288-p=1&awg=any')
#    print(data1)
    print("Getting page 2!")
    data2 = handle.getPage('https://icms.cern.ch/tools/idProvider/demand/https://cms.cern.ch/iCMS/jsp/analysis/admin/cadilines.jsp?d-446288-p=2&awg=any')
    print("Getting page 3!")
    data3 = handle.getPage('https://icms.cern.ch/tools/idProvider/demand/https://cms.cern.ch/iCMS/jsp/analysis/admin/cadilines.jsp?d-446288-p=3&awg=any')
# May '17 have 1,866, so may need to go above p=2 soonish
# May '18 have 2,017, so have to do 3 pages
# June 2020 have 2,310, still 3 pages
#
    data_CADI = data1 + data2 + data3
#    print("going to print data")
#    print(data_CADI)
 #   
    f = open("data/analyses.html", "wb")
    f.write(data_CADI)
    f.close()
#
    print("Got list of analyses.\n")
#
    # creating analyses folder where all fetched analyses will be stored
    if not os.path.exists("data/analyses"):
        os.makedirs("data/analyses")
#
    print("Retrieving the page for each analysis.\n")
#
    soup = BeautifulSoup(data_CADI, "html.parser")
    trs = soup.findAll("tr",{ "class" : re.compile(r"^(odd|even)$") })
    print("Retrieving an individual HTML file takes 0.5 sec,")
    print("but there are {0} of them, so a rough estimation".format( len(trs) ))
    print("of {0:.2f} min (give or take) for this step (with".format( len(trs)*0.5/60.))
    print("progress report every 200 analyses).\n")
#
    index=1
    for tr in trs:
        if len(tr.findAll("td")) > 2:
            tds = tr.findAll("td")
            analysis_url = tds[0].find("a")["href"]
#
            parts = analysis_url.split("&")
            firstPart = parts[0].split("?")
            id = firstPart[1].replace("line=","")
            #download analysis details page
            analysisHTML = handle.getPage("https://cms.cern.ch/iCMS/analysisadmin/getan?code="+id)
            o = open("data/analyses/id_"+id+".html", "wb")
            o.write(analysisHTML)
            o.close()
            if index%200 == 0:
                print("{0} pages retrieved. The last page was for the {1} analysis.".format( index, id ))
            index += 1
#
    print("Done")
#
def fetchANotes():
    data = handle.getPage('https://icms.cern.ch/tools/idProvider/demand/https://cms.cern.ch/iCMS/user/annotes')
    f = open("data/annotes.html", "wb")
    f.write(data)
    f.close()
#
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
    url = 'https://cms.cern.ch/iCMS/jsp/secr/sqlCountryMembers.jsp?country='
    for i in countries:
        if os.path.isfile("data/authors/%s.html" % i):
            continue
        else:
#            if not handle:
                handle = Login()
        if i == "USA2":
            data_Auth = handle.getPage('https://cms.cern.ch/iCMS/jsp/secr/stats/cmsUS.jsp')
        else:
            data_Auth = handle.getPage(url + i.replace(' ', '%20'))
        f = open("data/authors/%s.html" % i, "wb")
        f.write(data_Auth)
        f.close()
#
def fetchDetailPage(anotes_id):
    global handle
    if handle == None:
        handle = Login()
#
    url = 'https://cms.cern.ch/iCMS/jsp/db_notes/showNoteDetails.jsp?noteID='
    data_Detail = handle.getPage(url + anotes_id.replace(' ', '%20'))
#    print "detail note data: " + data
    f = open("data/detail_pages/%s.html" % anotes_id.replace('/', '_'), "wb")
    f.write(data_Detail)
    f.close()
#
def authorsCheck():
    for i in countries:
        if not os.path.isfile("data/authors/%s.html" % i):
            return True
    return False
# ---------------------------------- #
#
handle = None
#
print("Checking for prerequisites")
#
if not os.path.exists("data"):
    os.makedirs("data")
#
if not os.path.exists("sheets"):
    os.makedirs("sheets")
#
if not os.path.isfile("data/analyses.html"):
    print("Fetching analyses")
    if handle == None:
        handle = Login()
    fetchAnalyses()
#
#print "waiting 100s"
#time.sleep(100)
#
if not os.path.isfile("data/annotes.html"):
    if handle == None:
        handle = Login()
    fetchANotes()
#
if not os.path.exists("data/authors"):
    os.makedirs("data/authors")
#
# ---------------------------------- #
if not os.path.exists("data/detail_pages"):
    os.makedirs("data/detail_pages")
#
fetchAuthors()
#
def parseANotes():
    f = open("data/annotes.html")
    source = f.read()
    f.close()
    bs     = BeautifulSoup(source, "html.parser")
    tr     = bs.findAll("tr", {})
#
    CMSNoteIDIndex  = 0
    TitleIndex      = 1
    submitDateIndex = 2
    CountryIndex    = 3
    InstCodeIndex   = 4
    SubmitterIndex  = 5
    NauthIndex      = 6
#
    # Data format:
    # [[CMSNoteID, Title, submitDate, Country, InstCode, Submitter, Nauth], ... ]
    CMSANNotes = []
#
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
#
parsedANotes = parseANotes()
print(parsedANotes)
#
for i in parsedANotes:
#    so much debugging printing
#     print("going to check string contents of i[0]") 
#     print(str(i[0])) 
#     print("\n") 
#     print("going to check type of i[0]") 
#     print(type(i[0])) 
    myAN = i[0].decode(encoding='utf-8').replace('/', '_')
    myFile = Path(f"data/detail_pages/{myAN}.html")
    if not myFile.exists():
# previous prequisites code
#    if not os.path.exists("data/detail_pages/%s.html" % i[0].replace('/', '_')):
        fetchDetailPage(myAN)
# ---------------------------------- #
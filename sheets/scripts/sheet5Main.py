from ROOT import TString

'''
Created on Sep 24, 2013

@author: MantYdze
@email: mantas.stankevicius@cern.ch
'''

import json

''' 2017 '''
Scholars=["Claudio Campagnari"]
Scholars+=["Ketino Kaadze"]
Scholars+=["Bjoern Penning"]
Scholars+=["Alexander Schmidt"]
Scholars+=["Jamie Antonelli"]
Scholars+=["Jordan Damgov"]
Scholars+=["Ben Kreis"]
Scholars+=["Andrew Melo"]
Scholars+=["Sezen Sekmen"]
Scholars+=["Caterina Vernieri"]
Scholars+=["Giovanni Zevi Della Porta"]
Scholars+=["Ulrich Heintz"]
Scholars+=["Norbert Neumeister"]
Scholars+=["Roberto Rossin"]
Scholars+=["Seema Sharma"]
Scholars+=["Josh Bendavid"]
Scholars+=["Julie managan Hogan"]
Scholars+=["Matteo Cremonesi"]
Scholars+=["Abdollah Mohammadi"]
Scholars+=["Marco Trovato"]
Scholars+=["Marc Weinberg"]
''' 2017 graduate scholar '''
Scholars+=["Ryan Mueller"]

''' 2016 '''
''' duplicates from above are removed '''
'''Scholars=["Claudio Campagnari"]'''
Scholars+=["Robin Erbacher"]
Scholars+=["Kenichi Hatakeyama"]
Scholars+=["Christopher Hill"]
'''Scholars+=["Ketino Kaadze"]'''
Scholars+=["Luca Malgeri"]
''' didn't add CERN to LPC_AboveWithScholars '''
'''Scholars+=["Alexander Schmidt"]'''
'''Scholars+=["Jamie Antonelli"]'''
Scholars+=["Marco De Mattia"]
'''Scholars+=["Ben Kreis"]'''
Scholars+=["Edward Laird"]
Scholars+=["Jacob Linacre"]
Scholars+=["Ivan Marchesini"]
Scholars+=["Dominick Olivito"]
Scholars+=["Justin Pilot"]
Scholars+=["Lovedeep Saini"]
Scholars+=["Lesya Shchutska"]
Scholars+=["Markus Stoye"]
''' didn't add CERN to LPC_AboveWithScholars '''
Scholars+=["John Stupak"]
Scholars+=["Matthew Walker"]
Scholars+=["Andrew Whitbeck"]
Scholars+=["Si Xie"]

''' 2016 graduate scholars '''
Scholars+=["David Sheffield"]
Scholars+=["Ali Celik"]
Scholars+=["Sean-Jiun Wang"]
Scholars+=["Rizki Syarif"]

# Modified 28 April 2017 with Cecilia and Boaz, intended to represent
# institutions where people have a recent physical presence at LPC (keeping in 
# mind people come and go)
LPC = ["BAYLOR-UNIV", "BOSTON-UNIV", "BROWN-UNIV", "CALTECH", "CARNEGIE-MELLON", "CHICAGO", "COLORADO", "CORNELL", "FERMILAB", "FLORIDA-STATE", "FLORIDA-TECH",  "FLORIDA-UNIV", "IOWA", "JOHNS-HOPKINS", "KANSAS-STATE", "KANSAS-UNIV", "MINNESOTA", "NEBRASKA", "NORTHWESTERN", "OHIO-STATE", "PRINCETON", "PUERTO_RICO", "PURDUE", "PURDUE-CALUMET", "ROCHESTER", "ROCKEFELLER", "RUTGERS", "SUNY-BUFFALO", "TEXAS-TAMU", "TEXAS-TECH", "UCDAVIS", "UCSB", "UCSD", "VANDERBILT", "VIRGINIA-UNIV", "WAYNE", "WISCONSIN"]

#Came with Metric code when I started April 2017
LPC_ORIG = ["BAYLOR-UNIV", "BOSTON-UNIV", "BROWN-UNIV", "CARNEGIE-MELLON", "CHICAGO", "COLORADO", "CORNELL", "FERMILAB", "FLORIDA-FIU", "FLORIDA-STATE", "FLORIDA-TECH", "IOWA", "KANSAS-STATE", "KANSAS-UNIV", "LIVERMORE", "MINNESOTA", "MISSISSIPPI", "NEBRASKA", "NOTRE_DAME", "PUERTO_RICO", "PURDUE", "PURDUE-CALUMET", "ROCKEFELLER", "RUTGERS", "SUNY-BUFFALO", "TENNESSEE", "TEXAS-TAMU", "TEXAS-TECH", "VIRGINIA-UNIV"]

#LPC = []
#LPC_AboveWithScholars = ["BAYLOR-UNIV", "BOSTON-UNIV", "BRISTOL", "BROWN-UNIV", "CALTECH", "CARNEGIE-MELLON", "CHICAGO", "COLORADO", "CORNELL", "FERMILAB", "FLORIDA-FIU", "FLORIDA-STATE", "FLORIDA-TECH", "HAMBURG-UNIV", "IOWA", "KANSAS-STATE", "KANSAS-UNIV", "KYUNGPOOK", "LIVERMORE", "MINNESOTA", "MISSISSIPPI", "NEBRASKA", "NORTHWESTERN", "NOTRE_DAME", "OHIO-STATE", "PADOVA", "PUERTO_RICO", "PUNE-IISER", "PURDUE", "PURDUE-CALUMET", "RAL", "ROCKEFELLER", "RUTGERS", "SUNY-BUFFALO", "TENNESSEE", "TEXAS-TAMU", "TEXAS-TECH", "UCDAVIS", "UCSB", "UCSD", "VANDERBILT", "VIRGINIA-UNIV", "ZURICH-ETH"]

analysies_json = ""
annotes_json = ""
usa_lpc_authors = {}
output = ""
total = ""


def isInLPC(institute):
    for s in LPC:
        if institute == s:
            return True
    return False

def load_usa_lpc_authors_csv():
    f = open('data/LPCauthors-08November2017_fromLPCsurvey_GV_DR.csv', 'r')
    lines = f.read().split("\n")
    for line in lines[1:]:
        columns = line.split("|")
        if len(columns) > 6:
            fname = columns[4].replace("\"", "").replace("'", "")
            name = columns[3].replace("\"", "").replace("'", "")

            isLPC = False
            for i in range(5,7):  #lpc-fellows = 5, lpc-all = 6
                if columns[i].replace("\"", "") == '1':
                    isLPC = True
                    break

            usa_lpc_authors[fname + " " + name] = isLPC
            usa_lpc_authors[name + " " + fname] = isLPC

json_file = open('data/sheet1.json', 'r')
analysies_json = json.load(json_file)

json_file = open('data/sheet2.json', 'r')
annotes_json = json.load(json_file)

load_usa_lpc_authors_csv()

analysis_codes = analysies_json.keys()
analysis_codes.sort()

# TOTALS
arc_chair_from_USA_total = 0
arc_chair_from_LPC_total = 0
arc_chair_from_LPC_total_N = 0 ###
cadi_contact_from_USA_total = 0
cadi_contact_from_LPC_total = 0
cadi_contact_from_LPC_total_N = 0###
arc_members_num_total = 0
arc_members_num_from_USA_total = 0
arc_members_num_from_LPC_total = 0
arc_members_num_from_LPC_total_N = 0###
submitters_num_total = 0
submitters_num_from_USA_total = 0
submitters_num_from_LPC_total = 0
submitters_num_from_LPC_N_total = 0
authors_num_total = 0
authors_num_from_USA_total = 0
authors_num_from_LPC_total = 0
authors_num_from_LPC_N_total = 0
authors_num_lpc_fellows_total=0
authors_num_chair_lpc_fellows_total=0
authors_num_arc_lpc_fellows_total=0
institutes_num_total = 0
institutes_USA_num_total = 0
institutes_LPC_num_total = 0
institutes_LPC_num_total_N = 0###

# going through all cadi analysies
for analysis_code in analysis_codes:

    status = ""
    samples = ""
    arc_chair_from_USA = "-"
    arc_chair_from_LPC = "-"
    arc_chair_from_LPC_N = "-"###
    cadi_contact_from_USA = "-"
    cadi_contact_from_LPC = "-"
    cadi_contact_from_LPC_N = "-"###
    arc_members_num = 0
    arc_members_num_from_USA = 0
    arc_members_num_from_LPC = 0
    arc_members_num_from_LPC_N = 0###
    submitters_num = 0
    submitters_num_from_USA = 0
    submitters_num_from_LPC = 0
    submitters_num_from_LPC_N = 0
    authors_num = 0
    authors_num_fix = 0
    authors_num_from_USA = 0
    authors_num_from_LPC = 0
    authors_num_from_LPC_N = 0
    authors_num_lpc_fellows=0
    authors_num_chair_lpc_fellows=0
    authors_num_arc_lpc_fellows=0

    analysis = analysies_json[analysis_code]

    # Status
    status = analysis["status"]
    samples = analysis["samples"]

    ### ARC chairperson
    chairperson = analysis["chairperson"]
    if len(chairperson.keys()) > 0:
        # arc_chair_from_USA
        if chairperson["country"] == "USA":
            arc_chair_from_USA = 1
        else:
            arc_chair_from_USA = 0

        # arc_chair_from_LPC
        if isInLPC(chairperson["institute"]):
            arc_chair_from_LPC = 1
        else:
            arc_chair_from_LPC = 0

        # arc_chair_from_LPC_N###
        if usa_lpc_authors.has_key(chairperson['fullname']) and usa_lpc_authors[chairperson['fullname']]:
            arc_chair_from_LPC_N = 1
            try :
                chairPersonName=chairperson['fullname']
                print chairPersonName
                authString=chairPersonName.__str__()
                authString=authString.split(" ")
                for sch in Scholars :
                    schString=sch.split(" ")
                    authInSch= authString==schString
                    authInSch= authInSch or (authString[0] == schString[-1] and authString[-1]==schString[0])
                    if authInSch :
                        authors_num_chair_lpc_fellows+=1
            except UnicodeEncodeError:
                print "Hit a weird symbol! Moving on..."

        else:
            arc_chair_from_LPC_N = 0


    ### CADI contact
    cadi_contact = analysis["cadi_contact"]
    if len(cadi_contact.keys()) > 0:
        # cadi_contact_from_USA
        if cadi_contact["country"] == "USA":
            cadi_contact_from_USA = 1
        else:
            cadi_contact_from_USA = 0

        # cadi_contact_from_LPC
        if isInLPC(cadi_contact["institute"]):
            cadi_contact_from_LPC = 1
        else:
            cadi_contact_from_LPC = 0

        # cadi_contact_from_LPC_N###
        if usa_lpc_authors.has_key(cadi_contact['fullname']) and usa_lpc_authors[cadi_contact['fullname']]:
            cadi_contact_from_LPC_N = 1
        else:
            cadi_contact_from_LPC_N = 0

    ### ARC Members

    #    arc_members_num
    arc_members_num = analysis["arc_members_num"]

    arc_members = analysis["arc_members"]

    for member_key in arc_members :
        member = arc_members[member_key]

        #    arc_members_num_from_USA = 0
        if member["country"] == "USA":
            arc_members_num_from_USA += 1
        #    arc_members_num_from_LPC
        if isInLPC(member["institute"]):
            arc_members_num_from_LPC += 1
        # of ARC members from LPC NEW###
        if usa_lpc_authors.has_key(member_key) and usa_lpc_authors[member_key]:
            arc_members_num_from_LPC_N += 1
            try :
                arcMemName=member_key
                authString=arcMemName.__str__()
                authString=authString.split(" ")
                for sch in Scholars :
                    schString=sch.split(" ")
                    authInSch= authString==schString
                    authInSch= authInSch or (authString[0] == schString[-1] and authString[-1]==schString[0])
                    if authInSch :
                        #print "Hello!"
                        authors_num_arc_lpc_fellows+=1
            except UnicodeEncodeError:
                print "Hit a weird symbol! Moving on..."

    ### AN Notes submitters

    institutes = {}
    institutes_USA = {}
    institutes_LPC = {}
    institutes_LPC_N = {}###

    # submitters_num = 0
    submitters_num = analysis["notes_num"]

    for note_key in analysis["notes"].keys():
        if annotes_json.has_key(note_key):
            note = annotes_json[note_key]
            #    submitters_num_from_USA
            if note["country"] == "USA":
                submitters_num_from_USA += 1

            #    submitters_num_from_LPC
            if isInLPC(note["institute"]):
                submitters_num_from_LPC += 1

            # checking if submitter belongs to LPC (in new list provided by Sudhir)
            fname_name = " ".join(note["fullname"].split(" ")[:-1])
            if usa_lpc_authors.has_key(fname_name) and usa_lpc_authors[fname_name]:
                submitters_num_from_LPC_N += 1

            # authors_num
            authors_num += int(note["nauth"])

            authors = note["authors"]

            for author_key in authors :       # author_key = FirstName LastName
                author = authors[author_key]
                authors_num_fix += 1
            #    print "sheet5 test, got an author, authors_num_fix: %d" %authors_num_fix

                #    institutes_num
                if not institutes.has_key(author["institute"]):
                    institutes[author["institute"]] = author["country"]

                try :
                    authString=author_key.__str__()
                    authString=authString.split(" ")
                    for sch in Scholars :
                        schString=sch.split(" ")
                        authInSch= authString==schString
                        authInSch= authInSch or (authString[0] == schString[-1] and authString[-1]==schString[0])
                        if authInSch :
                            #print "Hello!"
                            print "Author in DRs, author: %s" %authString
                            authors_num_lpc_fellows+=1
                except UnicodeEncodeError:
                    print "Hit a weird symbol! Moving on..."


                #    authors_num_from_USA
                if author["country"] == "USA":
                    authors_num_from_USA += 1
                    #    institutes_num_from_USA
                    if not institutes_USA.has_key(author["institute"]):
                        institutes_USA[author["institute"]] = author["country"]

                #    authors_num_from_LPC
                if isInLPC(author["institute"]):
                    authors_num_from_LPC += 1
                    #    institutes_num_from_LPC
                    if not institutes_LPC.has_key(author["institute"]):
                        institutes_LPC[author["institute"]] = author["country"]

                if usa_lpc_authors.has_key(author_key) and usa_lpc_authors[author_key]:####
                    #    institutes_num_from_LPC_N###
                    if not institutes_LPC_N.has_key(author["institute"]):###
                        institutes_LPC_N[author["institute"]] = author["country"]###

                # checking if authors belongs to LPC (in new list provided by Sudhir)
                if usa_lpc_authors.has_key(author_key) and usa_lpc_authors[author_key]:
                    authors_num_from_LPC_N += 1
 # check my author count repair:
    if authors_num_fix > authors_num:
    	print "sheet5 fix mismatch, Analysis Code: %s, Original authors_num: %d, authors_num_fix: %d" %(analysis_code,authors_num,authors_num_fix)
    
    output_line = []
    output_line.append(analysis_code)
    output_line.append(status)
    output_line.append(samples)
    output_line.append(arc_chair_from_USA.__str__())
    output_line.append(arc_chair_from_LPC.__str__())
    output_line.append(arc_chair_from_LPC_N.__str__())###
    output_line.append(cadi_contact_from_USA.__str__())
    output_line.append(cadi_contact_from_LPC.__str__())
    output_line.append(cadi_contact_from_LPC_N.__str__())###
    output_line.append(arc_members_num.__str__())
    output_line.append(arc_members_num_from_USA.__str__())
    output_line.append(arc_members_num_from_LPC.__str__())
    output_line.append(arc_members_num_from_LPC_N.__str__())###
    output_line.append(submitters_num.__str__())
    output_line.append(submitters_num_from_USA.__str__())
    output_line.append(submitters_num_from_LPC.__str__())
    output_line.append(submitters_num_from_LPC_N.__str__())
    output_line.append(authors_num_fix.__str__())
    output_line.append(authors_num_from_USA.__str__())
    output_line.append(authors_num_from_LPC.__str__())
    output_line.append(authors_num_from_LPC_N.__str__())
    output_line.append(authors_num_lpc_fellows.__str__())
    output_line.append(authors_num_chair_lpc_fellows.__str__())
    output_line.append(authors_num_arc_lpc_fellows.__str__())
    output_line.append(len(institutes).__str__())
    output_line.append(len(institutes_USA).__str__())
    output_line.append(len(institutes_LPC).__str__())
    output_line.append(len(institutes_LPC_N).__str__())

    output += " | ".join(output_line) + "\n"

    if (arc_chair_from_USA != "-"):
        arc_chair_from_USA_total += arc_chair_from_USA

    if (arc_chair_from_LPC != "-"):
        arc_chair_from_LPC_total += arc_chair_from_LPC

    if (arc_chair_from_LPC_N != "-"):###
        arc_chair_from_LPC_total_N += arc_chair_from_LPC_N###

    if (cadi_contact_from_USA != "-"):
        cadi_contact_from_USA_total += cadi_contact_from_USA

    if (cadi_contact_from_LPC != "-"):
        cadi_contact_from_LPC_total += cadi_contact_from_LPC

    if (cadi_contact_from_LPC_N != "-"):
        cadi_contact_from_LPC_total_N += cadi_contact_from_LPC_N

    arc_members_num_total += arc_members_num
    arc_members_num_from_USA_total += arc_members_num_from_USA
    arc_members_num_from_LPC_total += arc_members_num_from_LPC
    arc_members_num_from_LPC_total_N += arc_members_num_from_LPC_N
    submitters_num_total += submitters_num
    submitters_num_from_USA_total += submitters_num_from_USA
    submitters_num_from_LPC_total += submitters_num_from_LPC
    submitters_num_from_LPC_N_total += submitters_num_from_LPC_N
    authors_num_total += int(authors_num)
    authors_num_from_USA_total += authors_num_from_USA
    authors_num_from_LPC_total += authors_num_from_LPC
    authors_num_from_LPC_N_total += authors_num_from_LPC_N
    authors_num_lpc_fellows_total += authors_num_lpc_fellows
    authors_num_chair_lpc_fellows_total += authors_num_chair_lpc_fellows
    authors_num_arc_lpc_fellows_total += authors_num_arc_lpc_fellows
    institutes_num_total += len(institutes)
    institutes_USA_num_total += len(institutes_USA)
    institutes_LPC_num_total += len(institutes_LPC)
    institutes_LPC_num_total_N += len(institutes_LPC_N)###


output_line = []
output_line.append("TOTAL")
output_line.append("")
output_line.append(arc_chair_from_USA_total.__str__())
output_line.append(arc_chair_from_LPC_total.__str__())
output_line.append(arc_chair_from_LPC_total_N.__str__())###
output_line.append(cadi_contact_from_USA_total.__str__())
output_line.append(cadi_contact_from_LPC_total.__str__())
output_line.append(cadi_contact_from_LPC_total_N.__str__())###
output_line.append(arc_members_num_total.__str__())
output_line.append(arc_members_num_from_USA_total.__str__())
output_line.append(arc_members_num_from_LPC_total.__str__())
output_line.append(arc_members_num_from_LPC_total_N.__str__())###
output_line.append(submitters_num_total.__str__())
output_line.append(submitters_num_from_USA_total.__str__())
output_line.append(submitters_num_from_LPC_total.__str__())
output_line.append(submitters_num_from_LPC_N_total.__str__())
output_line.append(authors_num_total.__str__())
output_line.append(authors_num_from_USA_total.__str__())
output_line.append(authors_num_from_LPC_total.__str__())
output_line.append(authors_num_from_LPC_N_total.__str__())
output_line.append(authors_num_lpc_fellows_total.__str__())
output_line.append(authors_num_chair_lpc_fellows_total.__str__())
output_line.append(authors_num_arc_lpc_fellows_total.__str__())
output_line.append(institutes_num_total.__str__())
output_line.append(institutes_USA_num_total.__str__())
output_line.append(institutes_LPC_num_total.__str__())
output_line.append(institutes_LPC_num_total_N.__str__())###

total = " | ".join(output_line) + "\n"

header = "Analysis code | Status | Samples | ARC chair from USA | ARC chair from LPC | ARC chair from LPC NEW | Cadi contact from US | Cadi contact LPC | Cadi contact LPC NEW | # of ARC members | # of ARC members form USA | # of ARC members from LPC | # of ARC members from LPC NEW | # of an submitters | # of submitters from USA | # of AN submitters from LPC | # of AN submitters from LPC NEW | # AN authors | # of AN authors from USA | # of  AN authors from LPC | # of  AN authors from LPC NEW | # AN authors LPC fellows | ARC chairs LPC fellow | # ARC members LPC fellows  | # of institutes | # in institutes from USA | # of institutes from LPC | # of institutes from LPC NEW\n"

f = open("sheets/sheet5.csv","w")
f.write(header+output+header+total)
f.close()
#print header+output+header+total

print "Done"

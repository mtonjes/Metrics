'''
Created on Sep 24, 2013

@author: MantYdze
@email: mantas.stankevicius@cern.ch
'''

import json

LPC = ["BAYLOR-UNIV", "BOSTON-UNIV", "BROWN-UNIV", "CALTECH", "CARNEGIE-MELLON", "CHICAGO", "COLORADO", "CORNELL", "FERMILAB", "FLORIDA-STATE", "FLORIDA-TECH",  "FLORIDA-UNIV", "IOWA", "JOHNS-HOPKINS", "KANSAS-STATE", "KANSAS-UNIV", "MINNESOTA", "NEBRASKA", "NORTHWESTERN", "OHIO-STATE", "PRINCETON", "PUERTO_RICO", "PURDUE", "PURDUE-CALUMET", "ROCHESTER", "ROCKEFELLER", "RUTGERS", "SUNY-BUFFALO", "TEXAS-TAMU", "TEXAS-TECH", "UCDAVIS", "UCSB", "UCSD", "VANDERBILT", "VIRGINIA-UNIV", "WAYNE", "WISCONSIN"]

analysies_json = ""
annotes_json = ""
output = ""
total = ""


def isInLPC(institute):
    for s in LPC:
        if institute == s:
            return True
    return False


json_file = open('data/sheet1.json', 'r')
analysies_json = json.load(json_file)
    
json_file = open('data/sheet2.json', 'r')
annotes_json = json.load(json_file)
    

analysis_codes = analysies_json.keys()
analysis_codes.sort()


# TOTALS
arc_chair_from_USA_total = 0
arc_chair_from_LPC_total = 0
cadi_contact_from_USA_total = 0
cadi_contact_from_LPC_total = 0
arc_members_num_total = 0
arc_members_num_from_USA_total = 0
arc_members_num_from_LPC_total = 0
submitters_num_total = 0
submitters_num_from_USA_total = 0
submitters_num_from_LPC_total = 0
authors_num_total = 0
authors_num_from_USA_total = 0
authors_num_from_LPC_total = 0
institutes_num_total = 0
institutes_USA_num_total = 0
institutes_LPC_num_total = 0

# going through all cadi analysies
for analysis_code in analysis_codes:
    
    status = ""
    arc_chair_from_USA = "-"
    arc_chair_from_LPC = "-"
    cadi_contact_from_USA = "-"
    cadi_contact_from_LPC = "-"
    arc_members_num = 0
    arc_members_num_from_USA = 0
    arc_members_num_from_LPC = 0
    submitters_num = 0
    submitters_num_from_USA = 0
    submitters_num_from_LPC = 0
    authors_num = 0
    authors_num_from_USA = 0
    authors_num_from_LPC = 0
    
    analysis = analysies_json[analysis_code]
    
    # Status
    status = analysis["status"]
    
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
    
    ### ARC Members
    
    #    arc_members_num
    arc_members_num = analysis["arc_members_num"]
    
    arc_members = analysis["arc_members"]
        
    for member_key in arc_members.keys():
        member = arc_members[member_key]
        
        #    arc_members_num_from_USA = 0
        if member["country"] == "USA":
            arc_members_num_from_USA += 1
        #    arc_members_num_from_LPC
        if isInLPC(member["institute"]):
            arc_members_num_from_LPC += 1
            
    ### AN Notes submitters

    institutes = {}
    institutes_USA = {}
    institutes_LPC = {}
    
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
                
            # authors_num
            authors_num += int(note["nauth"])
            
            authors = note["authors"]
            
            for author_key in authors.keys():
                author = authors[author_key]
                
                #    institutes_num
                if not institutes.has_key(author["institute"]):
                    institutes[author["institute"]] = author["country"]
                
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
        
    output_line = []
    output_line.append(analysis_code)
    output_line.append(status)
    output_line.append(arc_chair_from_USA.__str__())
    output_line.append(arc_chair_from_LPC.__str__())
    output_line.append(cadi_contact_from_USA.__str__())
    output_line.append(cadi_contact_from_LPC.__str__())
    output_line.append(arc_members_num.__str__())
    output_line.append(arc_members_num_from_USA.__str__())
    output_line.append(arc_members_num_from_LPC.__str__())
    output_line.append(submitters_num.__str__())
    output_line.append(submitters_num_from_USA.__str__())
    output_line.append(submitters_num_from_LPC.__str__())
    output_line.append(authors_num.__str__())
    output_line.append(authors_num_from_USA.__str__())
    output_line.append(authors_num_from_LPC.__str__())
    output_line.append(len(institutes).__str__())
    output_line.append(len(institutes_USA).__str__())
    output_line.append(len(institutes_LPC).__str__())
    
    output += " | ".join(output_line) + "\n"
    
    if (arc_chair_from_USA != "-"):
        arc_chair_from_USA_total += arc_chair_from_USA
        
    if (arc_chair_from_LPC != "-"):
        arc_chair_from_LPC_total += arc_chair_from_LPC
        
    if (cadi_contact_from_USA != "-"):
        cadi_contact_from_USA_total += cadi_contact_from_USA
    
    if (cadi_contact_from_LPC != "-"):
        cadi_contact_from_LPC_total += cadi_contact_from_LPC
        
    arc_members_num_total += arc_members_num
    arc_members_num_from_USA_total += arc_members_num_from_USA
    arc_members_num_from_LPC_total += arc_members_num_from_LPC
    submitters_num_total += submitters_num
    submitters_num_from_USA_total += submitters_num_from_USA
    submitters_num_from_LPC_total += submitters_num_from_LPC
    authors_num_total += int(authors_num)
    authors_num_from_USA_total += authors_num_from_USA
    authors_num_from_LPC_total += authors_num_from_LPC
    institutes_num_total += len(institutes)
    institutes_USA_num_total += len(institutes_USA)
    institutes_LPC_num_total += len(institutes_LPC)


output_line = []
output_line.append("TOTAL")
output_line.append("")
output_line.append(arc_chair_from_USA_total.__str__())
output_line.append(arc_chair_from_LPC_total.__str__())
output_line.append(cadi_contact_from_USA_total.__str__())
output_line.append(cadi_contact_from_LPC_total.__str__())
output_line.append(arc_members_num_total.__str__())
output_line.append(arc_members_num_from_USA_total.__str__())
output_line.append(arc_members_num_from_LPC_total.__str__())
output_line.append(submitters_num_total.__str__())
output_line.append(submitters_num_from_USA_total.__str__())
output_line.append(submitters_num_from_LPC_total.__str__())
output_line.append(authors_num_total.__str__())
output_line.append(authors_num_from_USA_total.__str__())
output_line.append(authors_num_from_LPC_total.__str__())
output_line.append(institutes_num_total.__str__())
output_line.append(institutes_USA_num_total.__str__())
output_line.append(institutes_LPC_num_total.__str__())

total = " | ".join(output_line) + "\n" 
    
header = "Analysis code | Status | ARC chair from USA | ARC chair from LPC | Cadi contact from US | Cadi contact LPC | # of ARC members | # of ARC members form USA | # of ARC members from LPC | # of an submitters | # of submitters from USA | # of AN submitters from LPC | # AN authors | # of AN authors from USA | # of  AN authors from LPC | # of institutes | # in institutes from USA | # of institutes from LPC\n"
    
f = open("sheets/sheet4.csv","w")
f.write(header+output+header+total)
f.close()    
    

print "Done"

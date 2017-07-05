from ROOT import TString

'''
Created on Sep 24, 2013

@author: MantYdze
@email: mantas.stankevicius@cern.ch

Heavyily modified July 5, 2017 from sheey5.py
Marguerite Tonjes
'''

import json


analysies_json = ""
output = ""
total = ""

json_file = open('data/sheet1.json', 'r')
analysies_json = json.load(json_file)

#json_file = open('data/sheet2.json', 'r')
#annotes_json = json.load(json_file)

analysis_codes = analysies_json.keys()
analysis_codes.sort()

# TOTALS
inactive_total = 0
published_total = 0
FR_total = 0
CWR_total = 0
arc_chair = ""
cadi_contact_name = ""

# going through all cadi analysies
for analysis_code in analysis_codes:

    status = ""
    samples = ""
    arc_chair = "-"
    cadi_contact_name = "-"

#     arc_chair_from_LPC = "-"
#     arc_chair_from_LPC_N = "-"###
#     cadi_contact_from_USA = "-"
#     cadi_contact_from_LPC = "-"
#     cadi_contact_from_LPC_N = "-"###
#     arc_members_num = 0
#     arc_members_num_from_USA = 0
#     arc_members_num_from_LPC = 0
#     arc_members_num_from_LPC_N = 0###
#     submitters_num = 0
#     submitters_num_from_USA = 0
#     submitters_num_from_LPC = 0
#     submitters_num_from_LPC_N = 0
#     authors_num = 0
#     authors_num_fix = 0
#     authors_num_from_USA = 0
#     authors_num_from_LPC = 0
#     authors_num_from_LPC_N = 0
#     authors_num_lpc_fellows=0
#     authors_num_chair_lpc_fellows=0
#     authors_num_arc_lpc_fellows=0

    analysis = analysies_json[analysis_code]

    # Status
    status = analysis["status"]
    samples = analysis["samples"]
    date = analysis["date"]
    ### ARC chairperson
    chairperson = analysis["chairperson"]
    if len(chairperson.keys()) > 0:
        arc_chair = chairperson["fullname"]
        # arc_chair_from_USA
#         if chairperson["country"] == "USA":
#             arc_chair_from_USA = 1
#         else:
#             arc_chair_from_USA = 0
# 
#         # arc_chair_from_LPC
#         if isInLPC(chairperson["institute"]):
#             arc_chair_from_LPC = 1
#         else:
#             arc_chair_from_LPC = 0
# 
#         # arc_chair_from_LPC_N###
#         if usa_lpc_authors.has_key(chairperson['fullname']) and usa_lpc_authors[chairperson['fullname']]:
#             arc_chair_from_LPC_N = 1
#             try :
#                 chairPersonName=chairperson['fullname']
#                 print chairPersonName
#                 authString=chairPersonName.__str__()
#                 authString=authString.split(" ")
#                 for sch in Scholars :
#                     schString=sch.split(" ")
#                     authInSch= authString==schString
#                     authInSch= authInSch or (authString[0] == schString[-1] and authString[-1]==schString[0])
#                     if authInSch :
#                         authors_num_chair_lpc_fellows+=1
#             except UnicodeEncodeError:
#                 print "Hit a weird symbol! Moving on..."
# 
#         else:
#             arc_chair_from_LPC_N = 0


    ### CADI contact
    cadi_contact = analysis["cadi_contact"]
    cadi_contact_name = cadi_contact["fullname"]
#     if len(cadi_contact.keys()) > 0:
#         # cadi_contact_from_USA
#         if cadi_contact["country"] == "USA":
#             cadi_contact_from_USA = 1
#         else:
#             cadi_contact_from_USA = 0
# 
#         # cadi_contact_from_LPC
#         if isInLPC(cadi_contact["institute"]):
#             cadi_contact_from_LPC = 1
#         else:
#             cadi_contact_from_LPC = 0
# 
#         # cadi_contact_from_LPC_N###
#         if usa_lpc_authors.has_key(cadi_contact['fullname']) and usa_lpc_authors[cadi_contact['fullname']]:
#             cadi_contact_from_LPC_N = 1
#         else:
#             cadi_contact_from_LPC_N = 0
# 
#     ### ARC Members
# 
#     #    arc_members_num
#     arc_members_num = analysis["arc_members_num"]
# 
#     arc_members = analysis["arc_members"]
# 
#     for member_key in arc_members :
#         member = arc_members[member_key]
# 
#         #    arc_members_num_from_USA = 0
#         if member["country"] == "USA":
#             arc_members_num_from_USA += 1
#         #    arc_members_num_from_LPC
#         if isInLPC(member["institute"]):
#             arc_members_num_from_LPC += 1
#         # of ARC members from LPC NEW###
#         if usa_lpc_authors.has_key(member_key) and usa_lpc_authors[member_key]:
#             arc_members_num_from_LPC_N += 1
#             try :
#                 arcMemName=member_key
#                 authString=arcMemName.__str__()
#                 authString=authString.split(" ")
#                 for sch in Scholars :
#                     schString=sch.split(" ")
#                     authInSch= authString==schString
#                     authInSch= authInSch or (authString[0] == schString[-1] and authString[-1]==schString[0])
#                     if authInSch :
#                         #print "Hello!"
#                         authors_num_arc_lpc_fellows+=1
#             except UnicodeEncodeError:
#                 print "Hit a weird symbol! Moving on..."
# 
#     ### AN Notes submitters
# 
#     institutes = {}
#     institutes_USA = {}
#     institutes_LPC = {}
#     institutes_LPC_N = {}###
# 
#     # submitters_num = 0
#     submitters_num = analysis["notes_num"]
# 
#     for note_key in analysis["notes"].keys():
#         if annotes_json.has_key(note_key):
#             note = annotes_json[note_key]
#             #    submitters_num_from_USA
#             if note["country"] == "USA":
#                 submitters_num_from_USA += 1
# 
#             #    submitters_num_from_LPC
#             if isInLPC(note["institute"]):
#                 submitters_num_from_LPC += 1
# 
#             # checking if submitter belongs to LPC (in new list provided by Sudhir)
#             fname_name = " ".join(note["fullname"].split(" ")[:-1])
#             if usa_lpc_authors.has_key(fname_name) and usa_lpc_authors[fname_name]:
#                 submitters_num_from_LPC_N += 1
# 
#             # authors_num
#             authors_num += int(note["nauth"])
# 
#             authors = note["authors"]
# 
#             for author_key in authors :       # author_key = FirstName LastName
#                 author = authors[author_key]
#                 authors_num_fix += 1
#             #    print "sheet5 test, got an author, authors_num_fix: %d" %authors_num_fix
# 
#                 #    institutes_num
#                 if not institutes.has_key(author["institute"]):
#                     institutes[author["institute"]] = author["country"]
# 
#                 try :
#                     authString=author_key.__str__()
#                     authString=authString.split(" ")
#                     for sch in Scholars :
#                         schString=sch.split(" ")
#                         authInSch= authString==schString
#                         authInSch= authInSch or (authString[0] == schString[-1] and authString[-1]==schString[0])
#                         if authInSch :
#                             #print "Hello!"
#                             print "Author in DRs, author: %s" %authString
#                             authors_num_lpc_fellows+=1
#                 except UnicodeEncodeError:
#                     print "Hit a weird symbol! Moving on..."
# 
# 
#                 #    authors_num_from_USA
#                 if author["country"] == "USA":
#                     authors_num_from_USA += 1
#                     #    institutes_num_from_USA
#                     if not institutes_USA.has_key(author["institute"]):
#                         institutes_USA[author["institute"]] = author["country"]
# 
#                 #    authors_num_from_LPC
#                 if isInLPC(author["institute"]):
#                     authors_num_from_LPC += 1
#                     #    institutes_num_from_LPC
#                     if not institutes_LPC.has_key(author["institute"]):
#                         institutes_LPC[author["institute"]] = author["country"]
# 
#                 if usa_lpc_authors.has_key(author_key) and usa_lpc_authors[author_key]:####
#                     #    institutes_num_from_LPC_N###
#                     if not institutes_LPC_N.has_key(author["institute"]):###
#                         institutes_LPC_N[author["institute"]] = author["country"]###
# 
#                 # checking if authors belongs to LPC (in new list provided by Sudhir)
#                 if usa_lpc_authors.has_key(author_key) and usa_lpc_authors[author_key]:
#                     authors_num_from_LPC_N += 1
#  # check my author count repair:
#     if authors_num_fix > authors_num:
#     	print "sheet5 fix mismatch, Analysis Code: %s, Original authors_num: %d, authors_num_fix: %d" %(analysis_code,authors_num,authors_num_fix)
    
    output_line = []
    output_line.append(analysis_code)
    output_line.append(status)
    output_line.append(samples)
    output_line.append(arc_chair.__str__())
    output_line.append(cadi_contact_name.__str__())
    output_line.append(date)
#     output_line.append(arc_chair_from_USA.__str__())
#     output_line.append(arc_chair_from_LPC.__str__())
#     output_line.append(arc_chair_from_LPC_N.__str__())###
#     output_line.append(cadi_contact_from_USA.__str__())
#     output_line.append(cadi_contact_from_LPC.__str__())
#     output_line.append(cadi_contact_from_LPC_N.__str__())###
#     output_line.append(arc_members_num.__str__())
#     output_line.append(arc_members_num_from_USA.__str__())
#     output_line.append(arc_members_num_from_LPC.__str__())
#     output_line.append(arc_members_num_from_LPC_N.__str__())###
#     output_line.append(submitters_num.__str__())
#     output_line.append(submitters_num_from_USA.__str__())
#     output_line.append(submitters_num_from_LPC.__str__())
#     output_line.append(submitters_num_from_LPC_N.__str__())
#     output_line.append(authors_num_fix.__str__())
#     output_line.append(authors_num_from_USA.__str__())
#     output_line.append(authors_num_from_LPC.__str__())
#     output_line.append(authors_num_from_LPC_N.__str__())
#     output_line.append(authors_num_lpc_fellows.__str__())
#     output_line.append(authors_num_chair_lpc_fellows.__str__())
#     output_line.append(authors_num_arc_lpc_fellows.__str__())
#     output_line.append(len(institutes).__str__())
#     output_line.append(len(institutes_USA).__str__())
#     output_line.append(len(institutes_LPC).__str__())
#     output_line.append(len(institutes_LPC_N).__str__())

    output += " | ".join(output_line) + "\n"

#     if (arc_chair_from_USA != "-"):
#         arc_chair_from_USA_total += arc_chair_from_USA
# 
#     if (arc_chair_from_LPC != "-"):
#         arc_chair_from_LPC_total += arc_chair_from_LPC
# 
#     if (arc_chair_from_LPC_N != "-"):###
#         arc_chair_from_LPC_total_N += arc_chair_from_LPC_N###
# 
#     if (cadi_contact_from_USA != "-"):
#         cadi_contact_from_USA_total += cadi_contact_from_USA
# 
#     if (cadi_contact_from_LPC != "-"):
#         cadi_contact_from_LPC_total += cadi_contact_from_LPC
# 
#     if (cadi_contact_from_LPC_N != "-"):
#         cadi_contact_from_LPC_total_N += cadi_contact_from_LPC_N
# 
#     arc_members_num_total += arc_members_num
#     arc_members_num_from_USA_total += arc_members_num_from_USA
#     arc_members_num_from_LPC_total += arc_members_num_from_LPC
#     arc_members_num_from_LPC_total_N += arc_members_num_from_LPC_N
#     submitters_num_total += submitters_num
#     submitters_num_from_USA_total += submitters_num_from_USA
#     submitters_num_from_LPC_total += submitters_num_from_LPC
#     submitters_num_from_LPC_N_total += submitters_num_from_LPC_N
#     authors_num_total += int(authors_num)
#     authors_num_from_USA_total += authors_num_from_USA
#     authors_num_from_LPC_total += authors_num_from_LPC
#     authors_num_from_LPC_N_total += authors_num_from_LPC_N
#     authors_num_lpc_fellows_total += authors_num_lpc_fellows
#     authors_num_chair_lpc_fellows_total += authors_num_chair_lpc_fellows
#     authors_num_arc_lpc_fellows_total += authors_num_arc_lpc_fellows
#     institutes_num_total += len(institutes)
#     institutes_USA_num_total += len(institutes_USA)
#     institutes_LPC_num_total += len(institutes_LPC)
#     institutes_LPC_num_total_N += len(institutes_LPC_N)###


output_line = []
output_line.append("TOTAL not yet filled in")
output_line.append("")
# output_line.append(arc_chair_from_USA_total.__str__())
# output_line.append(arc_chair_from_LPC_total.__str__())
# output_line.append(arc_chair_from_LPC_total_N.__str__())###
# output_line.append(cadi_contact_from_USA_total.__str__())
# output_line.append(cadi_contact_from_LPC_total.__str__())
# output_line.append(cadi_contact_from_LPC_total_N.__str__())###
# output_line.append(arc_members_num_total.__str__())
# output_line.append(arc_members_num_from_USA_total.__str__())
# output_line.append(arc_members_num_from_LPC_total.__str__())
# output_line.append(arc_members_num_from_LPC_total_N.__str__())###
# output_line.append(submitters_num_total.__str__())
# output_line.append(submitters_num_from_USA_total.__str__())
# output_line.append(submitters_num_from_LPC_total.__str__())
# output_line.append(submitters_num_from_LPC_N_total.__str__())
# output_line.append(authors_num_total.__str__())
# output_line.append(authors_num_from_USA_total.__str__())
# output_line.append(authors_num_from_LPC_total.__str__())
# output_line.append(authors_num_from_LPC_N_total.__str__())
# output_line.append(authors_num_lpc_fellows_total.__str__())
# output_line.append(authors_num_chair_lpc_fellows_total.__str__())
# output_line.append(authors_num_arc_lpc_fellows_total.__str__())
# output_line.append(institutes_num_total.__str__())
# output_line.append(institutes_USA_num_total.__str__())
# output_line.append(institutes_LPC_num_total.__str__())
# output_line.append(institutes_LPC_num_total_N.__str__())###

total = " | ".join(output_line) + "\n"

header = "Analysis code | Status | Samples | ARC chair | CADI contact | date |\n"



f = open("sheets/sheet8.csv","w")
#f.write(header+output+header+total)
f.write(header+output)
f.close()
#print header+output+header+total

print "Done"

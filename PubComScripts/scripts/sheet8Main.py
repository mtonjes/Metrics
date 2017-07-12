from ROOT import TString

'''
Created on Sep 24, 2013

@author: MantYdze
@email: mantas.stankevicius@cern.ch

Heavyily modified July 5, 2017 from sheey5.py
Marguerite Tonjes
'''

import json
import time

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
num_analyses_accept = 0
num_analyses_cwr = 0
num_analyses_sub = 0

cwr_out = ""
submitted_out = ""
accepted_out = ""
    
# https://www.cyberciti.biz/faq/howto-get-current-date-time-in-python/
now = time.strftime("date_%m_%d_%Y_time_%H_%M_%S")
print ("Current time %s"  % now )

# going through all cadi analysies
for analysis_code in analysis_codes:

    status = ""
    samples = ""
    arc_chair = "-"
    cadi_contact_name = "-"
    analysis_title = "-"
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
    ### date is not being filled in properly, use current time/date instead
    date = analysis["date"]
    ### ARC chairperson
    chairperson = analysis["chairperson"]
    if len(chairperson.keys()) > 0:
        arc_chair = chairperson["fullname"]
#        print "arc chair of ",analysis_code
#        print "is ",arc_chair.encode('utf-8')
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
    
    # analysis title
    analysis_title = analysis["analysis_name"]
 
    # count status
    if status=="CWR":
        cwr = []
        num_analyses_cwr+=1
        print status," ",analysis_code," ",analysis_title.encode('utf-8')
        cwr.append(now)
        cwr.append(analysis_code.__str__())
        cwr.append(status.__str__())
        cwr.append(analysis_title.encode('utf-8').__str__())   
        cwr_coded = []
        for i in cwr:
            try: cwr_coded.append(i.encode('utf-8'))
            except: cwr_coded.append(i)
        cwr_out += (",".join(cwr_coded) + "\n")
#        cwr.append(status.__str__()+" "+analysis_code.__str__()+"\n")
        
    if status=="ACCEPT":
        accepted = []
        num_analyses_accept+=1
        print status," ",analysis_code," ",analysis_title.encode('utf-8')
        accepted.append(now)
        accepted.append(analysis_code.__str__())
        accepted.append(status.__str__())
        accepted.append(analysis_title.encode('utf-8').__str__())
        accepted_coded = []
        for i in accepted:
            try: accepted_coded.append(i.encode('utf-8'))
            except: accepted_coded.append(i)
        accepted_out += (",".join(accepted_coded) + "\n")
#        accepted.append(status.__str__()+" "+analysis_code.__str__()+"\n")
              
    if status=="SUB":
        submitted = []
        num_analyses_sub+=1
        print status," ",analysis_code," ",analysis_title.encode('utf-8')
        submitted.append(now)
        submitted.append(analysis_code.__str__())
        submitted.append(status.__str__())
        submitted.append(analysis_title.encode('utf-8').__str__())
        submitted_coded = []
        for i in submitted:
            try: submitted_coded.append(i.encode('utf-8'))
            except: submitted_coded.append(i)
        submitted_out += (",".join(submitted_coded) + "\n")    
#        submitted.append(status.__str__()+" "+analysis_code.__str__()+" "+"\n")


#    print "cadi contact of ",analysis_code
#    print "is ",cadi_contact_name.encode('utf-8')
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
    output_line.append(now)    
    output_line.append(analysis_code)
    output_line.append(status)
    output_line.append(samples)
    output_line.append(analysis_title)
#
# Traceback (most recent call last):
#  File "scripts/sheet8Main.py", line 250, in <module>
#    output_line.append(arc_chair.__str__())
# UnicodeEncodeError: 'utf-8' codec can't encode character u'\xfc' in position 1: ordinal not in range(128)
# https://stackoverflow.com/questions/5760936/handle-wrongly-encoded-character-in-python-unicode-string
### want to be able to do those, which is why I'm debugging above
    output_line.append(arc_chair.encode("utf-8").__str__())
    output_line.append(cadi_contact_name.encode("utf-8").__str__())
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

    coded_output_line = []
    for i in output_line:
        try: coded_output_line.append(i.encode('utf-8'))
        except: coded_output_line.append(i)
    output += (" | ".join(coded_output_line) + "\n")


                        
#    output += " | ".join(output_line) + "\n"

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
#output_line.append("TOTALS for "+now+"\n")
#output_line.append("Accepted: ",num_analyses_accept)
#output_line.append("Submitted: ",num_analyses_sub)
#output_line.append("CWR: ",num_analyses_cwr)
print "Accepted: ",num_analyses_accept
print "Submitted: ",num_analyses_sub
print "CWR: ",num_analyses_cwr
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

header = "Today's date | Analysis code | Status | Samples | Title | ARC chair | CADI contact\n"

status_header = "Today's date,Analysis code,Status,Title \n"


                        
#    output += " | ".join(output_line) + "\n"


# 

f = open("sheets/sheet8.csv","w")
#f.write(header+output+header+total)
f.write(header+output)
f.close()

f2 = open("data/Accepted_{}.csv".format(now),"w")
f2.write(status_header+accepted_out)
f2.close()

f3 = open("data/CWR_{}.csv".format(now),"w")
f3.write(status_header+cwr_out)
f3.close()

f4 = open("data/Submitted_{}.csv".format(now),"w")
f4.write(status_header+submitted_out)
f4.close()
#print header+output+header+total

print "Done"

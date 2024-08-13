**Query CADI; Make sheets**
Instructions how to generate CADI sheets (presumably you have already setup an appropriate CMSSW working area on lxplus7.cern.ch (this does not work remote from CERN currently)):

```
> git clone https://github.com/mtonjes/Metrics.git

> cd Metrics/sheets

> voms-proxy-init --valid 168:00 -voms cms

> cd CMSSW_10_6_1/src

> cmsenv

> cd -

```
Code check: Login to iCMS (http://cms.cern.ch/iCMS)
Make sure http://cms.cern.ch/iCMS/analysisadmin/cadilines?awg=any has 3 pages.
If more, change scripts/prerequisites.py
Also consider which year DRs in both sheet5main.py and analyse.C code - try not to have repeat DRs, they will be counted twice!
Follow [1] instruction below if you have updated list of USA LPC authors 
CAVEAT: year is the two digit year of the paper code, NOT necessarily when the paper entered that stage (published/etc.)
```
> chmod +x generate_sheets.sh
> ./generate_sheets.sh
```


You will be asked to enter your CERN login and password, because CADI requires authentication in order to access data (note: this will be saved after the initial run in the file).

...wait... take a break :)

Generated sheets will be stored in the **sheets** directory as csv files. Separator is pipe `|`

For the first time script will take about 30mins because it downloads a lot of data from CADI.

In case of unrecoverable error:

1. launch `chmod +x cleanup.sh && ./cleanup.sh`

2. try again `./generate_sheets.sh`

3. if problem persist contact https://lpc.fnal.gov/computing/gethelp.shtml
```
**Make plots**
1) backup your current results
```
cd Metrics
cp -pr sheets sheets_TodayDate
```
2) Make plots directory and copy sheets5.csv
```
cd sheets
mkdir plots
mkdir plots/zcode
cp -pr sheets/sheet5.csv plots/.
cd plots
root -l -b -q ../scripts/analyse.C 
```
3) Look for errors - there is a lot of text and debugging statements, sorry :)
The debugging statements and spreadsheets help you validate with small subsets of data
---

**[1] Instuction**

1.Convert updated_list_of_authors.xls(x) to **usa_lpc_authors.csv**
Most recent used in multiple sheet*.py scripts is LPCSurvey_1May2019_RSRFCOCQ3-9.csv
**IMPORTANT!**

Do not mistype filename, or replace it appropriately in code **usa_lpc_authors.csv**

Field delimiter - **|**

Text delimiter - None (leave empty field)

2.Replace existing **usa_lpc_authors.csv** with new one in **data** directory.

---
**[2] Accuracy Note**
There is roughly a 20% uncertainty in the results. This is due to the name parsing of AN author lists. Additionally, some groups prefer not to list names in AN (Higgs, for instance).


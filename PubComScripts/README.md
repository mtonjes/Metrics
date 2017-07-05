**Query CADI; Make sheets**

Instructions how to generate CADI sheets:

**Setup working area once on cmslpc**
```
cd ~/nobackup
cmsrel CMSSW_8_0_25
git clone https://github.com/mtonjes/Metrics.git
cd Metrics/PubComScripts
chmod +x generate_sheets8.sh
chmod +x cleanup8.sh
```
Ensure your grid certificate is obtained and installed on the cmslpc cluster: https://twiki.cern.ch/twiki/bin/view/CMSPublic/WorkBookStartingGrid#BasicGrid

**Daily or weekly run of code**
For each time you run the code do the following after you login to cmslpc:.
*Note* we are cleaning up previous results, so you may wish to back them up in advance if you wish to retain previous results:

```
voms-proxy-init --valid 168:00 -voms cms

cd CMSSW_8_0_25/src

cmsenv

cd -

cd ~/nobackup/Metrics/PubComScripts

./cleanup8.sh

./generate_sheets8.sh
```


You will be asked to enter your CERN login and password, because CADI requires authentication in order to access data (note: this will be saved after the initial run in the file for each day's login).

...wait... take a break :)

Generated sheets will be stored in the **sheets** directory as csv files. Separator is pipe `|`

For the first time script will take about 30mins because it downloads a lot of data from CADI.

In case of unrecoverable error:

1. run cleanup `chmod +x cleanup8.sh && ./cleanup8.sh`

2. try again `./generate_sheets8.sh`

3. if problem persist contact http://lpc.fnal.gov/computing/gethelp.shtml

**Make plots**

1) backup your current results
```
cd ~/nobackup/Metrics
cp -pr PubComScripts PubComScripts_TodayDate
```
2) Make plots directory and copy sheet8.csv (not yet implemented July 5, 2017)
```
cd ~/nobackup/Metrics/PubComScripts
mkdir plots
mkdir plots/zcode
cp -pr sheets/sheet8.csv plots/.
cd plots
root -l -b -q ../scripts/analyse_PubCom.C 
```
3) Look for errors
---

**Debugging and future development/usage notes**

A) Note that prerequisites.py queries this web page: http://cms.cern.ch/iCMS/analysisadmin/cadilines?awg=any, if there are 2,000 or more items found you will need to edit prerequisites.py to allow for it to obtain 3 pages of data instead of 2.

B) This is a cleaned up version with much functionality removed and a different use case path of https://github.com/mtonjes/Metrics/tree/master/sheets

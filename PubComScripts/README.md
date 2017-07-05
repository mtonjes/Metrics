**A cleaned up version of https://github.com/mtonjes/Metrics/tree/master/sheets for a different purpose**
---
**Query CADI; Make sheets**
Instructions how to generate CADI sheets (presumably you have already setup an appropriate CMSSW working area):

```
> git clone https://github.com/mtonjes/Metrics.git

> cd Metrics/PubComScripts

> voms-proxy-init --valid 168:00 -voms cms

> cd CMSSW_8_0_25/src

> cmsenv

> cd -

```
Follow [1] instruction below if you have updated list of USA LPC authors 
```
> chmod +x generate_sheets8.sh
> ./generate_sheets8.sh
```


You will be asked to enter your CERN login and password, because CADI requires authentication in order to access data (note: this will be saved after the initial run in the file).

...wait... take a break :)

Generated sheets will be stored in the **sheets** directory as csv files. Separator is pipe `|`

For the first time script will take about 30mins because it downloads a lot of data from CADI.

In case of unrecoverable error:

1. run cleanup `chmod +x cleanup8.sh && ./cleanup8.sh`

2. try again `./generate_sheets8.sh`

3. if problem persist contact http://lpc.fnal.gov/computing/gethelp.shtml
```
**Make plots**
1) backup your current results
```
cd Metrics
cp -pr PubComScripts PubComScripts_TodayDate
```
2) Make plots directory and copy sheet8.csv (not yet implemented July 5, 2017)
```
cd PubComScripts
mkdir plots
mkdir plots/zcode
cp -pr sheets/sheet8.csv plots/.
cd plots
root -l -b -q ../scripts/analyse_PubCom.C 
```
3) Look for errors
---


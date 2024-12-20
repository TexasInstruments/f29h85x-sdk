import sys
import os

# Open the syscfg file in read mode and read the lines
sysCfgFile = open(sys.argv[1], "r")
lines = sysCfgFile.readlines()
sysCfgFile.close()

# Get CPU id
cpuId = int(sys.argv[3])

# Open the syscfg file in write mode and write back the read lines
# while skipping the cpu2/cpu3 appsize module instances
sysCfgFile = open(sys.argv[1], "w")
for row in lines:
    if(cpuId == 2):
        if((row.find("const cpu2") == -1) and (row.find("cpu2.appsize") == -1)):
            sysCfgFile.write(row)
    if(cpuId == 3):
        if((row.find("const cpu3") == -1) and (row.find("cpu3.appsize") == -1)):
            sysCfgFile.write(row)
sysCfgFile.close()

# Open syscfg file in append mode
sysCfgFile = open(sys.argv[1], "a")

# Get the size of appImgFile
appImgSize = os.path.getsize(sys.argv[2])

# Append syscfg file with the appImage file size based on the CPU id
if (cpuId == 2):
    sysCfgFile.write("const cpu2  = scripting.addModule(\"/driverlib/cpu2.js\");\n")
    sysCfgFile.write("cpu2.appsize = "+str(appImgSize)+";\n")
else:
    sysCfgFile.write("const cpu3  = scripting.addModule(\"/driverlib/cpu3.js\");\n")
    sysCfgFile.write("cpu3.appsize = "+str(appImgSize)+";\n")

# Close syscfg file
sysCfgFile.close()
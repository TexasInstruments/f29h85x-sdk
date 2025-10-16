import sys
import os

# Get the size of the CPU application
appImgSize = os.path.getsize(sys.argv[2])

# Get CPU id
cpuId = int(sys.argv[3])

# Open CPU app section file in write mode
cpuAppSecFile = open(sys.argv[1], "w")

# Add the CPU application section to the file
cpuAppSecFile.write("#include <stdint.h>\n")
cpuAppSecFile.write("\n")

if(cpuId == 2):
    cpuAppSecFile.write("__attribute__((retain, section(\"cpu2app\"))) const uint8_t cpu2App["+str(appImgSize)+"] = {0U};\n")
else:
    cpuAppSecFile.write("__attribute__((retain, section(\"cpu3app\"))) const uint8_t cpu3App["+str(appImgSize)+"] = {0U};\n")

cpuAppSecFile.close()

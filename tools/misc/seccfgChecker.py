###############################################################################
# SECCFG checker script
###############################################################################
import sys
import os
import subprocess

# Seccfg offsets
CRC_REGION_START_1  = 0x000
CRC_REGION_END_1    = 0x6C0
CRC_REGION_START_2  = 0x7A0
CRC_REGION_END_2    = 0x7F4
CRC_REGION_START_3  = 0x7F8
CRC_REGION_END_3    = 0x800
SECCFG_CRC          = 0x7F4
SECCFG_STATUS_1     = 0x7B8
SECCFG_STATUS_2     = 0x7BC
SSU_MODE            = 0x7F8
RAMOPEN_LOCK        = 0x7B2
ZONE_CFG            = 0x6B8
DEBUG_CFG           = 0x7A0
STACK_CFG           = 0x7D3
LINK_CFG            = 0x7DB
SECCFG_UPDATE_CFG   = 0x6BE

# Defines
NUM_APR             = 64
APR_OFFSET          = 16
APR_CONFIG_OFFSET   = 14
NUM_ZONE            = 3
NUM_STACK           = 5
NUM_LINK            = 13
SECCFG_SIZE         = 2048
SECCFG_STATUS       = 0x55555555
SSUMODE_1           = 0x30
SSUMODE_2           = 0x0C
SSUMODE_3           = 0x03
APR_START_MASK      = 0xFFFFF000
APR_END_MASK        = 0x00000FFF
APR_END_OFFSET      = 4
APR_ACCESS_OFFSET   = 8
L1_RD               = 0x04
L1_RW               = 0x0C

# Necessary APRs
necessaryAprAddr    = [0x10000000, 0x30208000, 0x30226000, 0x30227000, 0x302C0000, 0x60080000, 0x6008C000, 0x60090000]
necessaryAprSize    = [0x00001000, 0x00001000, 0x00001000, 0x00001000, 0x00002000, 0x00001000, 0x00001000, 0x00001000]
necessaryAprAccess  = [L1_RD, L1_RW, L1_RW, L1_RW, L1_RW, L1_RW, L1_RW, L1_RW]
necessaryAprCheck   = [0, 0, 0, 0, 0, 0, 0, 0]

# CRC look up table
crc32Table = [
0x00000000, 0x77073096, 0xEE0E612C, 0x990951BA, 0x076DC419, 0x706AF48F, 0xE963A535, 0x9E6495A3,
0x0EDB8832, 0x79DCB8A4, 0xE0D5E91E, 0x97D2D988, 0x09B64C2B, 0x7EB17CBD, 0xE7B82D07, 0x90BF1D91,
0x1DB71064, 0x6AB020F2, 0xF3B97148, 0x84BE41DE, 0x1ADAD47D, 0x6DDDE4EB, 0xF4D4B551, 0x83D385C7,
0x136C9856, 0x646BA8C0, 0xFD62F97A, 0x8A65C9EC, 0x14015C4F, 0x63066CD9, 0xFA0F3D63, 0x8D080DF5,
0x3B6E20C8, 0x4C69105E, 0xD56041E4, 0xA2677172, 0x3C03E4D1, 0x4B04D447, 0xD20D85FD, 0xA50AB56B,
0x35B5A8FA, 0x42B2986C, 0xDBBBC9D6, 0xACBCF940, 0x32D86CE3, 0x45DF5C75, 0xDCD60DCF, 0xABD13D59,
0x26D930AC, 0x51DE003A, 0xC8D75180, 0xBFD06116, 0x21B4F4B5, 0x56B3C423, 0xCFBA9599, 0xB8BDA50F,
0x2802B89E, 0x5F058808, 0xC60CD9B2, 0xB10BE924, 0x2F6F7C87, 0x58684C11, 0xC1611DAB, 0xB6662D3D,
0x76DC4190, 0x01DB7106, 0x98D220BC, 0xEFD5102A, 0x71B18589, 0x06B6B51F, 0x9FBFE4A5, 0xE8B8D433,
0x7807C9A2, 0x0F00F934, 0x9609A88E, 0xE10E9818, 0x7F6A0DBB, 0x086D3D2D, 0x91646C97, 0xE6635C01,
0x6B6B51F4, 0x1C6C6162, 0x856530D8, 0xF262004E, 0x6C0695ED, 0x1B01A57B, 0x8208F4C1, 0xF50FC457,
0x65B0D9C6, 0x12B7E950, 0x8BBEB8EA, 0xFCB9887C, 0x62DD1DDF, 0x15DA2D49, 0x8CD37CF3, 0xFBD44C65,
0x4DB26158, 0x3AB551CE, 0xA3BC0074, 0xD4BB30E2, 0x4ADFA541, 0x3DD895D7, 0xA4D1C46D, 0xD3D6F4FB,
0x4369E96A, 0x346ED9FC, 0xAD678846, 0xDA60B8D0, 0x44042D73, 0x33031DE5, 0xAA0A4C5F, 0xDD0D7CC9,
0x5005713C, 0x270241AA, 0xBE0B1010, 0xC90C2086, 0x5768B525, 0x206F85B3, 0xB966D409, 0xCE61E49F,
0x5EDEF90E, 0x29D9C998, 0xB0D09822, 0xC7D7A8B4, 0x59B33D17, 0x2EB40D81, 0xB7BD5C3B, 0xC0BA6CAD,
0xEDB88320, 0x9ABFB3B6, 0x03B6E20C, 0x74B1D29A, 0xEAD54739, 0x9DD277AF, 0x04DB2615, 0x73DC1683,
0xE3630B12, 0x94643B84, 0x0D6D6A3E, 0x7A6A5AA8, 0xE40ECF0B, 0x9309FF9D, 0x0A00AE27, 0x7D079EB1,
0xF00F9344, 0x8708A3D2, 0x1E01F268, 0x6906C2FE, 0xF762575D, 0x806567CB, 0x196C3671, 0x6E6B06E7,
0xFED41B76, 0x89D32BE0, 0x10DA7A5A, 0x67DD4ACC, 0xF9B9DF6F, 0x8EBEEFF9, 0x17B7BE43, 0x60B08ED5,
0xD6D6A3E8, 0xA1D1937E, 0x38D8C2C4, 0x4FDFF252, 0xD1BB67F1, 0xA6BC5767, 0x3FB506DD, 0x48B2364B,
0xD80D2BDA, 0xAF0A1B4C, 0x36034AF6, 0x41047A60, 0xDF60EFC3, 0xA867DF55, 0x316E8EEF, 0x4669BE79,
0xCB61B38C, 0xBC66831A, 0x256FD2A0, 0x5268E236, 0xCC0C7795, 0xBB0B4703, 0x220216B9, 0x5505262F,
0xC5BA3BBE, 0xB2BD0B28, 0x2BB45A92, 0x5CB36A04, 0xC2D7FFA7, 0xB5D0CF31, 0x2CD99E8B, 0x5BDEAE1D,
0x9B64C2B0, 0xEC63F226, 0x756AA39C, 0x026D930A, 0x9C0906A9, 0xEB0E363F, 0x72076785, 0x05005713,
0x95BF4A82, 0xE2B87A14, 0x7BB12BAE, 0x0CB61B38, 0x92D28E9B, 0xE5D5BE0D, 0x7CDCEFB7, 0x0BDBDF21,
0x86D3D2D4, 0xF1D4E242, 0x68DDB3F8, 0x1FDA836E, 0x81BE16CD, 0xF6B9265B, 0x6FB077E1, 0x18B74777,
0x88085AE6, 0xFF0F6A70, 0x66063BCA, 0x11010B5C, 0x8F659EFF, 0xF862AE69, 0x616BFFD3, 0x166CCF45,
0xA00AE278, 0xD70DD2EE, 0x4E048354, 0x3903B3C2, 0xA7672661, 0xD06016F7, 0x4969474D, 0x3E6E77DB,
0xAED16A4A, 0xD9D65ADC, 0x40DF0B66, 0x37D83BF0, 0xA9BCAE53, 0xDEBB9EC5, 0x47B2CF7F, 0x30B5FFE9,
0xBDBDF21C, 0xCABAC28A, 0x53B39330, 0x24B4A3A6, 0xBAD03605, 0xCDD70693, 0x54DE5729, 0x23D967BF,
0xB3667A2E, 0xC4614AB8, 0x5D681B02, 0x2A6F2B94, 0xB40BBE37, 0xC30C8EA1, 0x5A05DF1B, 0x2D02EF8D,
]

# Dump CPU1 CPU2 and CPU3 seccfg
subprocess.check_output('{} -O binary --only-section=.TI.bound:CPU1_Cfg {} seccfgCpu1.bin'.format(sys.argv[1], sys.argv[2]), shell=True)
subprocess.check_output('{} -O binary --only-section=.TI.bound:CPU2_Cfg {} seccfgCpu2.bin'.format(sys.argv[1], sys.argv[2]), shell=True)
subprocess.check_output('{} -O binary --only-section=.TI.bound:CPU3_Cfg {} seccfgCpu3.bin'.format(sys.argv[1], sys.argv[2]), shell=True)
subprocess.check_output('{} -O binary --only-section=.TI.bound:CPU4_Cfg {} seccfgCpu4.bin'.format(sys.argv[1], sys.argv[2]), shell=True)

###############################################################################
# Function definitions
###############################################################################
# Function to read 32 bit value
def read32(address, index):
    return address[index] | (address[index + 1] << 8) | (address[index + 2] << 16) | (address[index + 3] << 24)

# Function to check APR settings
def aprCheck(secCfgAddr):
    # LINKID cannot be 0, will reset to HW reset value
    retVal = 0
    for i in range(0, NUM_APR):
        aprCfg      = secCfgAddr[(APR_OFFSET * i) + APR_CONFIG_OFFSET] | (secCfgAddr[(APR_OFFSET * i) + APR_CONFIG_OFFSET + 1] << 8)
        aprCfgMask  = aprCfg & 0xF
        if(aprCfgMask == 0):
            print("APR",i,"config = ",aprCfg)
            retVal = -1

    return retVal

# Zone config check
def zoneCfgCheck(secCfgAddr):
    # UPDATE_EN should be either 0x3 or 0xC
    retVal = 0
    for i in range(0, NUM_ZONE):
        zoneCfg     = secCfgAddr[ZONE_CFG + (i * 2)] | (secCfgAddr[ZONE_CFG + (i * 2) + 1] << 8)
        zoneCfgMask = zoneCfg & 0xF000
        if((zoneCfgMask != 0x3000) and (zoneCfgMask != 0xC000)):
            print("Zone",(i + 1),"config = ",zoneCfg)
            retVal = -1

    return retVal

# Debug config check
def debugCfgCheck(secCfgAddr):
    retVal      = 0
    debugCfg    = secCfgAddr[DEBUG_CFG] | (secCfgAddr[DEBUG_CFG + 1] << 8)
    # C29DBGGEN_CFG
    debugCfgMask    = debugCfg & 0x7
    if((debugCfgMask != 0x1) and (debugCfgMask != 0x2) and (debugCfgMask != 0x4)):
        print("Debug config = ", debugCfg)
        retVal = -1
    # ZONE 1
    debugCfgMask    = debugCfg & 0x70
    if((debugCfgMask != 0x10) and (debugCfgMask != 0x20) and (debugCfgMask != 0x40)):
        print("Debug config = ", debugCfg)
        retVal = -1
    # ZONE 2
    debugCfgMask    = debugCfg & 0x700
    if((debugCfgMask != 0x100) and (debugCfgMask != 0x200) and (debugCfgMask != 0x400)):
        print("Debug config = ", debugCfg)
        retVal = -1
    # ZONE 3
    debugCfgMask    = debugCfg & 0x7000
    if((debugCfgMask != 0x1000) and (debugCfgMask != 0x2000) and (debugCfgMask != 0x4000)):
        print("Debug config = ", debugCfg)
        retVal = -1

    return retVal

# Stack config check
def stackCheck(secCfgAddr):
    # ZONE cannot be 0, results in HW reset value
    retVal = 0
    for i in range(0, NUM_STACK):
        stackCfg        = secCfgAddr[STACK_CFG + i]
        stackCfgMask    = stackCfg & 0x3
        if(stackCfgMask == 0):
            print("Stack",(i + 3),"config = ", stackCfg)
            retVal = -1

    return retVal

# Link config check
def linkCheck(secCfgAddr):
    # STACK cannot be 0, results in HW reset value
    retVal = 0
    for i in range(0, NUM_LINK):
        linkCfg     = secCfgAddr[LINK_CFG + i]
        linkCfgMask = linkCfg & 0x7
        if(linkCfgMask == 0):
            print("Link",(i + 3),"config = ", linkCfg)
            retVal = -1

    return retVal

# Init error count to 0
errorCount = 0

# Check if seccfg files are present
if((os.path.getsize("seccfgCpu1.bin") != SECCFG_SIZE) or (os.path.getsize("seccfgCpu2.bin") != SECCFG_SIZE) or (os.path.getsize("seccfgCpu3.bin") != SECCFG_SIZE) or (os.path.getsize("seccfgCpu4.bin") != SECCFG_SIZE)):
    print("No seccfg sections in the", sys.argv[2])
    os.remove("seccfgCpu1.bin")
    os.remove("seccfgCpu2.bin")
    os.remove("seccfgCpu3.bin")
    os.remove("seccfgCpu4.bin")
    exit(0)

# Read the seccfg data
secCfgCpu1File = open("seccfgCpu1.bin", "rb")
secCfgCpu2File = open("seccfgCpu2.bin", "rb")
secCfgCpu3File = open("seccfgCpu3.bin", "rb")
secCfgCpu1Data = secCfgCpu1File.read()
secCfgCpu2Data = secCfgCpu2File.read()
secCfgCpu3Data = secCfgCpu3File.read()
secCfgCpu1File.close()
secCfgCpu2File.close()
secCfgCpu3File.close()

###############################################################################
# Check CRC computation
###############################################################################
# CRC region 1
computedCrc = 0xFFFFFFFF
for i in range(CRC_REGION_START_1, CRC_REGION_END_1):
    computedCrc = crc32Table[(computedCrc ^ secCfgCpu1Data[i]) & 0xFF] ^ (computedCrc >> 8)
# CRC region 2
for i in range(CRC_REGION_START_2, CRC_REGION_END_2):
    computedCrc = crc32Table[(computedCrc ^ secCfgCpu1Data[i]) & 0xFF] ^ (computedCrc >> 8)
# CRC region 2
for i in range(CRC_REGION_START_3, CRC_REGION_END_3):
    computedCrc = crc32Table[(computedCrc ^ secCfgCpu1Data[i]) & 0xFF] ^ (computedCrc >> 8)
# Final CRC
computedCrc = computedCrc ^ 0xFFFFFFFF
# Read golden CRC
goldenCrc = read32(secCfgCpu1Data, SECCFG_CRC)
# Compare golden CRC vs computed CRC
if(computedCrc != goldenCrc):
    errorCount += 1
    print("SECCFG-ERROR:Seccfg CRC mismatch computed = ", computedCrc, "golden = ",goldenCrc)

###############################################################################
# Check seccfg STATUS
###############################################################################
# Check CPU1 seccfg status
secCfgStatus1 = read32(secCfgCpu1Data, SECCFG_STATUS_1)
secCfgStatus2 = read32(secCfgCpu1Data, SECCFG_STATUS_2)
if((secCfgStatus1 != SECCFG_STATUS) or (secCfgStatus2 != SECCFG_STATUS)):
    errorCount += 1
    print("SECCFG-ERROR:CPU1 seccfg status is invalid = ", secCfgStatus1, secCfgStatus2)

# Check CPU3 seccfg status
secCfgStatus1 = read32(secCfgCpu3Data, SECCFG_STATUS_1)
secCfgStatus2 = read32(secCfgCpu3Data, SECCFG_STATUS_2)
if((secCfgStatus1 != SECCFG_STATUS) or (secCfgStatus2 != SECCFG_STATUS)):
    errorCount += 1
    print("SECCFG-ERROR:CPU3 seccfg status is invalid = ", secCfgStatus1, secCfgStatus2)

###############################################################################
# Check SSUMODE
###############################################################################
ssuMode = read32(secCfgCpu1Data, SSU_MODE)
# SSUMODE should be either 0x30 or 0x0C or 0x03, any other write causes fault
if((ssuMode != SSUMODE_1) and (ssuMode != SSUMODE_2) and (ssuMode != SSUMODE_3)):
    errorCount += 1
    print("SECCFG-ERROR:SSUMODE is invalid = ", ssuMode)

###############################################################################
# Check APR list
###############################################################################
# CPU1 apr
aprCheckResult = aprCheck(secCfgCpu1Data)
if(aprCheckResult == -1):
    errorCount += 1
    print("SECCFG-ERROR:CPU1 APR settings are invalid")
# CPU2 apr
aprCheckResult = aprCheck(secCfgCpu2Data)
if(aprCheckResult == -1):
    errorCount += 1
    print("SECCFG-ERROR:CPU2 APR settings are invalid")
# CPU3 apr
aprCheckResult = aprCheck(secCfgCpu3Data)
if(aprCheckResult == -1):
    errorCount += 1
    print("SECCFG-ERROR:CPU3 APR settings are invalid")
# Check necessary APRs
if(ssuMode != SSUMODE_1):
    for i in range(0, NUM_APR):
        aprStartAddr    = read32(secCfgCpu1Data, (i * APR_OFFSET)) & APR_START_MASK
        aprEndAddr      = read32(secCfgCpu1Data, ((i * APR_OFFSET) + APR_END_OFFSET)) | APR_END_MASK
        aprAccess       = read32(secCfgCpu1Data, ((i * APR_OFFSET) + APR_ACCESS_OFFSET))
        for j in range(0, len(necessaryAprAddr)):
            if((necessaryAprAddr[j] >= aprStartAddr) and ((necessaryAprAddr[j] + (necessaryAprSize[j] - 1)) <= aprEndAddr)):
                if((necessaryAprAccess[j] == (aprAccess & L1_RD)) or (necessaryAprAccess[j] == (aprAccess & L1_RW))):
                    necessaryAprCheck[j] = 1
    for k in range(0, len(necessaryAprCheck)):
        if(necessaryAprCheck[k] == 0):
            errorCount += 1
            print("SECCFG-ERROR:Necessary APR for ",necessaryAprAddr[k],"not defined")

###############################################################################
# ZONE config
###############################################################################
zoneCfgCheckResult = zoneCfgCheck(secCfgCpu1Data)
if(zoneCfgCheckResult == -1):
    errorCount += 1
    print("SECCFG-ERROR:Zone config are invalid")

###############################################################################
# Seccfg update config
###############################################################################
secCfgUpdateCfg = secCfgCpu1Data[SECCFG_UPDATE_CFG] | (secCfgCpu1Data[SECCFG_UPDATE_CFG + 1] << 8)
# LINK_OWNER cannot be 0
if((secCfgUpdateCfg & 0xF) == 0):
    errorCount += 1
    print("SECCFG-ERROR:Seccfg update config is invalid = ", secCfgUpdateCfg)
# UPDATE_EN should be either 0x3 or 0xC
if(((secCfgUpdateCfg & 0xF000) != 0x3000) and ((secCfgUpdateCfg & 0xF000) != 0xC000)):
    errorCount += 1
    print("SECCFG-ERROR:Seccfg update config is invalid = ", secCfgUpdateCfg)

###############################################################################
# DEBUG config
###############################################################################
debugCfgCheckResult = debugCfgCheck(secCfgCpu1Data)
if(debugCfgCheckResult == -1):
    errorCount += 1
    print("SECCFG-ERROR:Debug config are invalid")

###############################################################################
# RAMOPEN lock
###############################################################################
ramopenLock = secCfgCpu1Data[RAMOPEN_LOCK]
# RAMOPEN_LOCK should be either 0xA5 or 0x5A
if(((ramopenLock & 0xFF) != 0xA5) and ((ramopenLock & 0xFF) != 0x5A)):
    errorCount += 1
    print("SECCFG-ERROR:Ramopen lock is invalid = ", ramopenLock)

###############################################################################
# Check STACK config
###############################################################################
# CPU1 stack
stackCheckResult = stackCheck(secCfgCpu1Data)
if(stackCheckResult == -1):
    errorCount += 1
    print("SECCFG-ERROR:CPU1 Stack settings are invalid")
# CPU2 stack
stackCheckResult = stackCheck(secCfgCpu2Data)
if(stackCheckResult == -1):
    errorCount += 1
    print("SECCFG-ERROR:CPU2 Stack settings are invalid")
# CPU3 stack
stackCheckResult = stackCheck(secCfgCpu3Data)
if(stackCheckResult == -1):
    errorCount += 1
    print("SECCFG-ERROR:CPU3 Stack settings are invalid")

###############################################################################
# Check LINK config
###############################################################################
# CPU1 link
linkCheckResult = linkCheck(secCfgCpu1Data)
if(linkCheckResult == -1):
    errorCount += 1
    print("SECCFG-ERROR:CPU1 Link settings are invalid")
# CPU2 link
linkCheckResult = linkCheck(secCfgCpu2Data)
if(linkCheckResult == -1):
    errorCount += 1
    print("SECCFG-ERROR:CPU2 Link settings are invalid")
# CPU3 link
linkCheckResult = linkCheck(secCfgCpu3Data)
if(linkCheckResult == -1):
    errorCount += 1
    print("SECCFG-ERROR:CPU3 Link settings are invalid")

###############################################################################
# Check for error count
###############################################################################
print("SECCFG-CHECK:Error count = ", errorCount)

# Delete files
os.remove("seccfgCpu1.bin")
os.remove("seccfgCpu2.bin")
os.remove("seccfgCpu3.bin")
os.remove("seccfgCpu4.bin")

if(errorCount == 0):
    exit(0)
else:
    exit(1)
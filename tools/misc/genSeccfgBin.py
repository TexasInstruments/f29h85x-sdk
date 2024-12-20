###############################################################################
# SECCFG binary generation script
###############################################################################
import sys
import os
import subprocess

# Dump CPU1 CPU2 and CPU3 seccfg
subprocess.check_output('{} -O binary --only-section=.TI.bound:CPU1_Cfg {} seccfgCpu1.bin'.format(sys.argv[1], sys.argv[2]), shell=True)
subprocess.check_output('{} -O binary --only-section=.TI.bound:CPU2_Cfg {} seccfgCpu2.bin'.format(sys.argv[1], sys.argv[2]), shell=True)
subprocess.check_output('{} -O binary --only-section=.TI.bound:CPU3_Cfg {} seccfgCpu3.bin'.format(sys.argv[1], sys.argv[2]), shell=True)

# Sign the CPU1 seccfg binary
subprocess.check_output('{} {} --image-bin seccfgCpu1.bin --core C29 --swrv 1 --loadaddr 0x10001000 --sign-key {} --out-image seccfg_cert.bin --device f29h85x --boot FLASH --fw_type SEC_CFG'.format(sys.argv[5], sys.argv[3], sys.argv[4]), shell=True)

# Combine certificate + CPU1 seccfg + CPU2 seccfg + CPU3 seccfg
secCfgCert     = open("seccfg_cert.bin",    "rb")
secCfgCpu2File = open("seccfgCpu2.bin",     "rb")
secCfgCpu3File = open("seccfgCpu3.bin",     "rb")
secCfgFile     = open("seccfg.bin",         "wb")

secCfgFile.write(secCfgCert.read() + secCfgCpu2File.read() + secCfgCpu3File.read())

secCfgCert.close()
secCfgCpu2File.close()
secCfgCpu3File.close()
secCfgFile.close()

os.remove("C29-cert-pad.bin")
os.remove("seccfg_cert.bin")
os.remove("seccfgCpu1.bin")
os.remove("seccfgCpu2.bin")
os.remove("seccfgCpu3.bin")
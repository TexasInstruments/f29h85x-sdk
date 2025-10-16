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

# Remove last 16 bytes from seccfgCpu2.bin
secCfgCpu2 = open("seccfgCpu2.bin", "rb+")
secCfgCpu2.truncate(2032)
secCfgCpu2.close()

# Sign the CPU1, CPU2 and CPU3 seccfg binaries
subprocess.check_output('{} {} --image-bin seccfgCpu1.bin --core C29 --swrv 1 --loadaddr 0x10001000 --sign-key {} --out-image seccfg_cert_1.bin --device f29h85x --boot FLASH --fw_type SEC_CFG_CPU1'.format(sys.argv[5], sys.argv[3], sys.argv[4]), shell=True)
subprocess.check_output('{} {} --image-bin seccfgCpu2.bin --core C29 --swrv 1 --loadaddr 0x10001000 --sign-key {} --out-image seccfg_cert_2.bin --device f29h85x --boot FLASH --fw_type SEC_CFG_CPU2'.format(sys.argv[5], sys.argv[3], sys.argv[4]), shell=True)
subprocess.check_output('{} {} --image-bin seccfgCpu3.bin --core C29 --swrv 1 --loadaddr 0x10001000 --sign-key {} --out-image seccfg_cert_3.bin --device f29h85x --boot FLASH --fw_type SEC_CFG_CPU3'.format(sys.argv[5], sys.argv[3], sys.argv[4]), shell=True)

# Pad 16 bytes to the seccfg_cert_2.bin
secCfgCert2 = open("seccfg_cert_2.bin", "ab")
zeroBytes = b'\x00' * 16
secCfgCert2.write(zeroBytes)
secCfgCert2.close()

# Combine cert + seccfg for all 3 CPUs
secCfgCert1 = open("seccfg_cert_1.bin", "rb")
secCfgCert2 = open("seccfg_cert_2.bin", "rb")
secCfgCert3 = open("seccfg_cert_3.bin", "rb")
secCfgFile  = open("seccfg.bin",        "wb")

secCfgFile.write(secCfgCert1.read() + secCfgCert2.read() + secCfgCert3.read())

secCfgCert1.close()
secCfgCert2.close()
secCfgCert3.close()
secCfgFile.close()

os.remove("C29-cert-pad.bin")
os.remove("seccfg_cert_1.bin")
os.remove("seccfg_cert_2.bin")
os.remove("seccfg_cert_3.bin")
os.remove("seccfgCpu1.bin")
os.remove("seccfgCpu2.bin")
os.remove("seccfgCpu3.bin")
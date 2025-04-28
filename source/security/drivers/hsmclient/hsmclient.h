/*
 *  Copyright (C) 2022-24 Texas Instruments Incorporated
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef HSM_CLIENT_H_
#define HSM_CLIENT_H_

#ifdef __cplusplus
extern "C"
{
#endif

/* Header file for HSM client driver */
#include <stdint.h>
#include <security/drivers/secure_ipc_notify/sipc_notify.h>
#include <security/drivers/hsmclient/hsmclient_msg.h>
#include <security/drivers/hsmclient/utils/hsmclient_utils.h>
#include <kernel/dpl/SemaphoreP.h>

/**
 * \defgroup DRV_HSMCLIENT_MODULE APIs for HSMCLIENT
 * \ingroup DRV_MODULE
 *
 * See \ref DRIVERS_HSMCLIENT_PAGE for more details.
 *
 * @{
 */
#define LABEL_AND_CONTEXT_LEN_MAX 48U

/**
 * @brief
 *        HSMRT load has not been requested
 */
#define HSMRT_LOAD_NOT_REQUESTED (0U)
/**
 * @brief
 *        HSMRT load has been requested
 */
#define HSMRT_LOAD_REQUESTED (1U)
/**
 * @brief
 *        HSMRT load has failed
 */
#define HSMRT_LOAD_FAILED (2U)
/**
 * @brief
 *        HSMRT load has succeeded
 */
#define HSMRT_LOAD_SUCCEEDED (3U)

    /**
     * @brief
     * type for reading HSMRt version.
     *
     */
    typedef union HsmVer_t_
    {
        uint64_t HsmrtVer /**< A 64 bit unique Version number */;
        struct
        {
            uint8_t PatchVer; /** patch Version number refer HSMRT_PATCH_VER in TIFS Docs  */
            uint8_t MinorVer; /** HSMRt minor version number refer HSMRT_MINOR_VER in TIFS Docs*/
            uint8_t MajorVer; /** HSMRt major version number refer HSMRT_MAJOR_VER in TIFS Docs*/
            uint8_t ApiVer;   /** HSMRt API version number refer HSMRT_APIS_VER in TIFS Docs*/
            uint8_t SocType;  /** HSMRt Soc type ID refer HSMRT_SOC_TYPE in TIFS Docs*/
            uint8_t BinType;  /** HSMRt Binary type ID refer HSMRT_BIN_TYPE in TIFS Docs*/
            uint8_t HsmType;  /** HSM Architecture version */
            uint8_t DevType;  /** HSMRt Device type ID  refer HSMRT_DEVICE_TYPE in TIFS Docs*/

        } VerStruct;
#if defined(_TMS320C6X)
    } __attribute__((packed)) HsmVer_t_;
#else
} __attribute__((packed)) HsmVer_t;
#endif

    /**
     * @brief
     * This is a HSMClient type which holds the information
     * needed by hsm client to communicate with HSM .
     */
    typedef struct HsmClient_t_
    {
        SemaphoreP_Object Semaphore; /**  Registered client will pend of this semaphore
                                       till it receives a response from HSM server. */
        HsmMsg_t ReqMsg;             /** message frame that is to be passed to HSM server.*/
        HsmMsg_t RespMsg;            /** Stores a message frame received from HSM server.*/
        uint8_t RespFlag;            /** Indicates weather a request has been Acked or Nacked by HSM server.*/
        uint8_t ClientId;            /** object's ClientId.*/

    } HsmClient_t;

    /**
     * @brief
     * This is an NvmOtpRead type which holds the information
     * of NvmOtp row index and row data corresponding to it .
     * For F29H85x, the rowdIdx corresponds to the Flash Offsets.
     * For AM26x, the rowIdx corresponds to efuse row offsets.
     */
    typedef struct NvmOtpRead_t_
    {
        uint32_t rowData; /** Points to data retrieved from gp otp registers or fw otp region.*/
        uint16_t rowIdx;  /** Points index of an NvmOtp row to be read.*/
        uint8_t rsvd[2];  /** Reserved **/
    } NvmOtpRead_t;

    /**
     * @brief
     * This is an NvmOtpRowWrite type which holds the information
     * regarding programming NvmOtp row.
     * For F29H85x, the rowdIdx corresponds to the Flash Offsets.
     * For AM26x, the rowIdx corresponds to efuse row offsets.
     */
    typedef struct NvmOtpRowWrite_t_
    {
        uint32_t rowData;    /** Data to be written in an NvmOtp row **/
        uint32_t rowBitMask; /** Bit mask to apply to an NvmOtp row data bits **/
        uint16_t rowIdx;     /** Index of an NvmOtp row. **/
        uint8_t rsvd[2];     /** Reserved **/
    } NvmOtpRowWrite_t;

    /**
     * @brief
     * This is an NvmOtpRowCount type which holds the information
     * regarding NvmOtp row count and size of each row in bits.
     */
    typedef struct NvmOtpRowCount_t_
    {
        uint32_t rowCount; /** NvmOtp row count **/
        uint8_t rowSize;   /** Size of an NvmOtp row in bits. **/
        uint8_t rsvd[3];   /** Reserved **/
    } NvmOtpRowCount_t;

    /**
     * @brief
     * This is a NvmOtpRowProt type which holds the information
     * of NvmOtp row index and protection status corresponding
     * to the row index.
     * This structure is not valid for f29h85x
     */
    typedef struct NvmOtpRowProt_t_
    {
        uint16_t rowidx;   /** Index of an NvmOtp row. **/
        uint8_t readProt;  /** Read row protection information used in getting or setting an NvmOtp row protection. **/
        uint8_t writeProt; /** Write row protection information used in getting or setting an NvmOtp row protection. **/
    } NvmOtpRowProt_t;

    /**
     * @brief
     * This is a keywriter_cert_header type which holds the information
     * of customer key certificate and debug responce.
     */
    typedef struct keywriter_cert_header_t_
    {
        uint8_t *certAddress;   /*For holding cerificate address*/
        uint32_t certSize;      /*Cerificate size*/
        uint32_t debugResponse; /*Debug response*/
        uint32_t reserved;      /*reserved for future use*/
    } KeyWriterCertHeader_t;

    /**
     * @brief
     * This is a FirewallRegionReq type which holds the information
     * of Firewall region configuration.
     */
    typedef struct FirewallRegionReq_t_
    {
        uint16_t firewallId;           /**< Index of the firewall. **/
        uint16_t region;               /**< Region number **/
        uint32_t permissionAttributes; /**< Memory Protection Permission Attributes corresponding to the firewall **/
        uint32_t startAddress;         /**< Start Address of the region **/
        uint32_t endAddress;           /**< End Address of the region **/
    } FirewallRegionReq_t;

    /**
     * @brief
     * This is a FirewallReq_t type which holds the information
     * of Firewall configuration.
     */
    typedef struct FirewallReq_t_
    {
        uint16_t regionCount;                   /**< Region count **/
        uint16_t crcArr;                        /**< crc of FirewallRegionArr **/
        FirewallRegionReq_t *FirewallRegionArr; /**< Array containing set firewall region request **/
        uint16_t statusFirewallRegionArr;       /**< Status of all region requests **/
    } FirewallReq_t;

    /**
     * @brief
     * This is a FirewallIntrReq type which holds the information
     * of MPU Firewall request for interrupt enable, interrupt enable clear,
     * interrupt enable status clear and fault clear.
     */
    typedef struct FirewallIntrReq_t_
    {
        uint16_t firewallId;                /**< Index of the firewall. **/
        uint8_t interruptEnable;            /**< MPU Interrupt Enable **/
        uint8_t interruptEnableClear;       /**< Clear MPU Interrupt **/
        uint8_t interruptEnableStatusClear; /**< Clear raw status **/
        uint8_t faultClear;                 /**< Clear voilation status MMRs **/
    } FirewallIntrReq_t;

    /**
     * @brief
     * This is SWRev type which holds the information
     * regarding Revision identifier and value corresponding to it .
     *
     * @param revValue  stores software revision value retreived from sec manager.
     * @param revId    revision identifier
     * @param rsvd     reserved for future use.
     */
    typedef struct SWRev_t_
    {
        uint32_t revValue; /**< Value for sw rev retreived from sec manager.*/
        uint8_t revId;     /**< revision identifier*/
        uint8_t rsvd[3];   /**< Reserved */
    } SWRev_t;

    /**
     * @brief
     * This is DKEK type which holds the label and context for derivation.
     * This also holds the 256 derived KEK value which is returned by TIFS.
     *
     * @param label_length		length of label.
     * @param context_length	length of context
     * @param label_and_context holds the label and context as an array
     * @param dkek				holds the derived key as returned by TIFS.
     */
    typedef struct DKEK_t_
    {
        uint8_t label_length;                                 /**< label length.*/
        uint8_t context_length;                               /**< context length.*/
        uint8_t label_and_context[LABEL_AND_CONTEXT_LEN_MAX]; /**< label_and_context array */
        uint32_t dkek[8];                                     /**< derived KEK. */
    } DKEK_t;

    /**
     * @brief
     * This is RNG type which holds the resultPtr for derivation which is returned by TIFS.
     * This also holds the resultLengthPtr and DRBG Mode along with seedValue and seedSize.
     *
     * @param resultPtr		    Pointer to the random number generated
     * @param resultLengthPtr	Pointer to store the desired length in bytes
     * @param DRBGMode          Flag that determines whether DRBG mode is required or not
     * @param seedValue			Stores the seed values
     * @param seedSizeInDWords   Stores the seed size in double words
     */
    typedef struct RNGReq_t_
    {
        uint8_t *resultPtr;        /**< Pointer to the random number.*/
        uint32_t *resultLengthPtr; /**< Pointer to determine result length.*/
        uint8_t DRBGMode;          /**< Flag to enable DRBG Mode.*/
        uint32_t *seedValue;       /**< Seed Value.*/
        uint8_t seedSizeInDWords;  /**< Seed Size in double words.*/
        uint8_t reserved;          /**< Reserved Variable.*/
    } RNGReq_t;

    /**
     * @brief
     * This is the SecureBoot Stream type which holds the data for a specific bootloader
     * to HSM call. This packet is needed by HSM the to do the required operation.
     */
    typedef struct SecureBoot_Stream_t_
    {
        uint8_t *dataIn;        /**< Pointer to the data in shared memory.*/
        uint32_t dataLen;       /**< Size of the data.*/
        uint8_t canBeEncrypted; /**< Whether this data could be encrypted or not.*/
    } __attribute__((packed)) SecureBoot_Stream_t;

    /**
     * @brief
     * This is Firmware Update request structure passed to HSM core via SIPC as
     * argument, these parameters are required by the service handler
     *
     * @param pStartAddress               Pointer to the start address of data to be programmed in flash
     * @param dataLength                  Length of data to be programmed in flash
     */
    typedef struct FirmwareUpdateReq_t_
    {
        uint8_t *pStartAddress; /** Start address of data to be programmed in flash memory */
        uint32_t dataLength;    /** Length of data to be programmed in flash memory */
        uint32_t bankMode;      /** Current device bank mode */
    } FirmwareUpdateReq_t;


/**
 * @brief
 * This is the OTFA Region structure which holds individual region specific information to be written to corresponding OTFA registers.
 * In AM263Px and AM261x, there are 4 OTFA regions
 */
typedef struct OTFA_Region_t
{
    uint8_t   authMode ;         /* mode of authentication - disable-0/GMAC-1/CMAC-2 ; */
    uint8_t   encMode ;          /* mode of decryption - disable-0 or AES_CTR-1 */
    uint16_t  reservedArea ;     /* reserved to align with 4kB structure */
    uint32_t  regionStAddr ;     /* start address of the flash region for which the configuration should apply */
    uint32_t  regionSize ;       /* size of the flash region in kB for which the configuration should apply */
    uint8_t   authKeyID ;        /* Keyring ID of key to be used for authentication */    
    uint8_t   encrKeyID ;        /* Keyring ID of key to be used for encryption */
    uint8_t   encrKeyFetchMode ; /* specify which 16 bytes of DSMEK are to be used - 1 for fist 16/2 for last 16/ 3 for XOR of both */
    uint8_t   authAesKey [16] ;  /* actual key value to be written to the register for authentication ; fetched from keyring */
    uint8_t   encrAesKey [16] ;  /* actual key value to be written to the register for decryption ; fetched from keyring */
    uint8_t   regionIV[16] ;     /* IV to be used for encryption */
}OTFA_Region_t ;

/**
 * @brief
 * This is the OTFA Region structure which holds individual region specific information to be read from OTFA registers.
 */
typedef struct OTFA_readRegion_t
{
    uint8_t   regionNumber ;    /* Index of the region - 0/1/2/3 */
    uint8_t   authMode ;        /* mode of authentication - disable-0/GMAC-1/CMAC-2 ; */
    uint8_t   encMode ;         /* mode of decryption - disable-0 or AES_CTR-1 */
    uint8_t   authKeyHash[64] ; /* hash of the authentication key stored in OTFA register */
    uint8_t   encKeyHash[64] ;  /* hash of the encryption key stored in OTFA register */
    uint32_t  regionStAddr ;    /* start address of the flash region for which the configuration should apply */
    uint32_t  regionSize ;      /* size of the flash region in kB for which the configuration should apply */
    uint16_t  regionIV[16] ;    /* IV to be used for encryption */
}OTFA_readRegion_t ;

/**
 * @brief
 * This is the entire OTFA structure which holds all regions' information 
 * 4 regions in AM263Px and AM261x
 */
typedef struct OTFA_Config_t
{
    OTFA_Region_t  OTFA_Reg[4] ;    /* array of all registers' information of 4 OTFA Regions */
    uint8_t        numRegions ;     /* number of OTFA regions to be configured */
    uint8_t        keySize   ;      /* options - 128/256 */
    uint8_t        macSize   ;      /* options - 4/8/12/16 */
    uint8_t        masterEnable ;   /* specifies whether OTFA IP has to be enabled/disabled ; 0 or 1 */
}OTFA_Config_t ;

    /**
     * @brief
     * This API waits for HSMRT load if requested
     * and then waits for boot notification. In case of
     * failure in HSMRT load it returns SystemP_FAILURE.
     *
     * @return
     * 1. SystemP_SUCCESS if HSMRT load is successful.
     * 2. SystemP_FAILURE if HSMRT load fails.
     */
    int32_t HsmClient_checkAndWaitForBootNotification(void);

    /**
     * @brief
     * Initialize the HSM client for current core.
     *
     * @param params [IN] SIPC_notify params.
     *
     * @return
     * 1. SystemP_SUCCESS if init sequence successful.
     * 2. SystemP_FAILURE if init sequence fails.
     */
    int32_t HsmClient_init(SIPC_Params *params);

    /**
     * @brief
     * De initialize the HSM client for current core.
     *
     */
    void HsmClient_deInit(void);

/**
 * @brief
 * Customize the size of the HSM client message queue
 *
 * @param configured_hsm_client_msg_queue_size  Desired size of the HSM client message queue passed by the user.
 */
void HsmClient_SecureBootQueueInit(uint32_t configured_hsm_client_msg_queue_size);
/**
 * @brief
 *  populates the current HSMRT version Id
 *  by default the hsm flag is set to HSM_FLAG_AOP for this service
 *
 * @param timeToWaitInTick  [IN] amount of time to block waiting for
 * semaphore to be available, in units of system ticks (see KERNEL_DPL_CLOCK_PAGE)
 * @param HsmClient         [IN] Client object which is using this getversion API.
 * @param verId             [OUT] populates HsmVer_t struct which describes current version. This object's memory address needs to be cache aligned.
 *
 * @return
 * 1. SystemP_SUCCESS if returns successfully
 * 2. SystemP_FAILURE if NACK message is received or client id not registered.
 * 3. SystemP_TIMEOUT if timeout exception occours.
 */
int32_t HsmClient_getVersion(HsmClient_t *HsmClient ,
                                        HsmVer_t* verId,uint32_t timeToWaitInTick);

    /**
     * @brief
     *  The service issued to HSM Server populates the Device UID
     *  by default the hsm flag is set to HSM_FLAG_AOP for this service
     *
     * @param timeout           [IN] amount of time to block waiting for
     * semaphore to be available, in units of system ticks (see KERNEL_DPL_CLOCK_PAGE)
     * @param HsmClient         [IN] Client object which is using this getUID API.
     * @param uid               [OUT] populates UID value.
     *
     * @return
     * 1. SystemP_SUCCESS if returns successfully
     * 2. SystemP_FAILURE if NACK message is received or client id not registered.
     * 3. SystemP_TIMEOUT if timeout exception occours.
     */
    int32_t HsmClient_getUID(HsmClient_t *HsmClient,
                             uint8_t *uid, uint32_t timeout);

    /**
     * @brief
     *  The service issued to HSM Server verifies the certificate and
     *  by default the hsm flag is set to HSM_FLAG_AOP for this service
     *
     * @param timeout           [IN] amount of time to block waiting for
     * semaphore to be available, in units of system ticks (see KERNEL_DPL_CLOCK_PAGE)
     * @param HsmClient         [IN] Client object which is using this openDbgFirewalls API.
     * @param cert              [IN] point to the location of certificate in the device memory.
     * @param cert_size         [IN] size of certificate.
     *
     * @return
     * 1. SystemP_SUCCESS if returns successfully
     * 2. SystemP_FAILURE if NACK message is received or client id not registered.
     * 3. SystemP_TIMEOUT if timeout exception occours.
     */
    int32_t HsmClient_openDbgFirewall(HsmClient_t *HsmClient,
                                      uint8_t *cert,
                                      uint32_t cert_size,
                                      uint32_t timeout);

    /**
     * @brief
     *  The service issued to HSM Server verifies the certificate and
     *  imports the keys from the certificate
     *
     * @param timeout           [IN] amount of time to block waiting for
     * semaphore to be available, in units of system ticks (see KERNEL_DPL_CLOCK_PAGE)
     * @param HsmClient         [IN] Client object which is using this importKeyring API.
     * @param cert              [IN] point to the location of certificate in the device memory.
     * @param cert_size         [IN] size of certificate.
     *
     * @return
     * 1. SystemP_SUCCESS if returns successfully
     * 2. SystemP_FAILURE if NACK message is received or client id not registered.
     * 3. SystemP_TIMEOUT if timeout exception occours.
     */
    int32_t HsmClient_importKeyring(HsmClient_t *HsmClient,
                                    uint8_t *cert,
                                    uint32_t cert_size,
                                    uint32_t timeout);

    /**
     * @brief
     *  The service issued to HSM Server retrieves the data of GP OTP row
     *  based on row index provided as param.
     *
     * @param HsmClient [IN] HsmClient object.
     * @param readRow   [IN] populates NvmOtpRead_t struct with rowData
     *                       corresponding to rowIdx.
     * @return
     * 1. SystemP_SUCCESS if returns successfully
     * 2. SystemP_FAILURE if NACK message is received or client id not registered.
     */
    int32_t HsmClient_readOTPRow(HsmClient_t *HsmClient,
                                 NvmOtpRead_t *readRow);

    /**
     * @brief
     *  The service issued to HSM Server writes the data to extended
     *  OTP efuse row based on row index provided as param.
     *
     * @param HsmClient  [IN] HsmClient object.
     * @param writeRow   [IN] populates NvmOtpRowWrite_t struct with rowData
     *                       corresponding to rowIdx.
     * @return
     * 1. SystemP_SUCCESS if returns successfully
     * 2. SystemP_FAILURE if NACK message is received or client id not registered.
     */
    int32_t HsmClient_writeOTPRow(HsmClient_t *HsmClient,
                                  NvmOtpRowWrite_t *writeRow);

    /**
     * @brief
     *  The service issued to HSM Server sets the protection status bit of
     *  the specified row to 1. This API is not valid for F29H85x.
     *
     * @param HsmClient [IN] HsmClient object.
     * @param rowProt   [IN] Pointer to NvmOtpRowProt_t struct which contains
     *                       the row index and row protection status
     * @return
     * 1. SystemP_SUCCESS if returns successfully
     * 2. SystemP_FAILURE if NACK message is received or client id not registered.
     */
    int32_t HsmClient_lockOTPRow(HsmClient_t *HsmClient,
                                 NvmOtpRowProt_t *rowProt);

    /**
     * @brief
     *  The service issued to HSM Server retrieves the count of extended OTP
     *  rows.
     *
     * @param HsmClient [IN] HsmClient object.
     * @param rowCount  [IN] Pointer to NvmOtpRowCount_t struct which is
     *                       populated by HSM server with row count and row size
     * @return
     * 1. SystemP_SUCCESS if returns successfully
     * 2. SystemP_FAILURE if NACK message is received or client id not registered.
     */
    int32_t HsmClient_getOTPRowCount(HsmClient_t *HsmClient,
                                     NvmOtpRowCount_t *rowCount);

    /**
     * @brief
     *  The service issued to HSM Server retrieves the extended otp efuse row
     *  protection status. This API is not valid for F29H85x.
     *
     * @param HsmClient [IN] HsmClient object.
     * @param rowProt  [IN]  Pointer to NvmOtpRowProt_t struct which is
     *                       populated by HSM server with row protection status
     * @return
     * 1. SystemP_SUCCESS if returns successfully
     * 2. SystemP_FAILURE if NACK message is received or client id not registered.
     */
    int32_t HsmClient_getOTPRowProtection(HsmClient_t *HsmClient,
                                          NvmOtpRowProt_t *rowProt);

    /**
     * @brief
     *  The service issued to HSM Server helps with extended secure boot for
     *  applications.
     *
     * @param timeout           [IN] amount of time to block waiting for
     * semaphore to be available, in units of system ticks (see KERNEL_DPL_CLOCK_PAGE)
     * @param HsmClient         [IN] Client object which is using this openDbgFirewalls API.
     * @param cert              [IN] point to the location of certificate in the device memory.
     * @param cert_size         [IN] size of certificate.
     *
     * @return
     * 1. SystemP_SUCCESS if returns successfully
     * 2. SystemP_FAILURE if NACK message is received or client id not registered.
     * 3. SystemP_TIMEOUT if timeout exception occours.
     */
    int32_t HsmClient_procAuthBoot(HsmClient_t *HsmClient,
                                   uint8_t *cert,
                                   uint32_t cert_size,
                                   uint32_t timeout);

    /**
     * @brief
     *  The service issued to HSM Server helps with extended secure boot for
     *  applications.
     *
     * @param HsmClient         [IN] Client object which is using this openDbgFirewalls API.
     * @param secureBootInfo    [IN] pointer to the secure boot information object in
     *                               shared memory.
     *
     * @return
     * 1. SystemP_SUCCESS if returns successfully
     * 2. SystemP_FAILURE if NACK message is received or client id not registered.
     * 3. SystemP_TIMEOUT if timeout exception occours.
     */
    int32_t HsmClient_procAuthBootStart(HsmClient_t *HsmClient,
                                        SecureBoot_Stream_t *secureBootInfo);

    /**
     * @brief
     *  The service issued to HSM Server helps with extended secure boot for
     *  applications.
     *
     * @param HsmClient         [IN] Client object which is using this openDbgFirewalls API.
     * @param secureBootInfo    [IN] pointer to the secure boot information object in
     *                               shared memory.
     *
     * @return
     * 1. SystemP_SUCCESS if returns successfully
     * 2. SystemP_FAILURE if NACK message is received or client id not registered.
     * 3. SystemP_TIMEOUT if timeout exception occours.
     */
    int32_t HsmClient_procAuthBootUpdate(HsmClient_t *HsmClient,
                                         SecureBoot_Stream_t *secureBootInfo);

    /**
     * @brief
     *  The service issued to HSM Server helps with extended secure boot for
     *  applications.
     *
     * @param HsmClient         [IN] Client object which is using this openDbgFirewalls API.
     * @param secureBootInfo    [IN] pointer to the secure boot information object in
     *                               shared memory
     *
     * @return
     * 1. SystemP_SUCCESS if returns successfully
     * 2. SystemP_FAILURE if NACK message is received or client id not registered.
     * 3. SystemP_TIMEOUT if timeout exception occours.
     */
    int32_t HsmClient_procAuthBootFinish(HsmClient_t *HsmClient,
                                         SecureBoot_Stream_t *secureBootInfo);

    /**
     * @brief
     *  The service issued to HSM Server sets the firewall for the given firewall id and
     *  region.
     *
     * @param timeout           [IN] amount of time to block waiting for
     * semaphore to be available, in units of system ticks (see KERNEL_DPL_CLOCK_PAGE)
     * @param HsmClient              [IN] HsmClient object.
     * @param FirewallReqObj         [IN] Pointer to FirewallReq_t struct which contains
     *                                    information required for HSM to process set firewall request.
     * @return
     * 1. SystemP_SUCCESS if returns successfully
     * 2. SystemP_FAILURE if NACK message is received or client id not registered.
     * 3. SystemP_TIMEOUT if timeout exception occours.
     */
    int32_t HsmClient_setFirewall(HsmClient_t *HsmClient,
                                  FirewallReq_t *FirewallReqObj,
                                  uint32_t timeout);
    /**
     * @brief
     *  The service issued to HSM Server sets the firewall interrupt request for the given firewall id.
     *
     * @param timeout           [IN] amount of time to block waiting for
     * semaphore to be available, in units of system ticks (see KERNEL_DPL_CLOCK_PAGE)
     * @param HsmClient                  [IN] HsmClient object.
     * @param FirewallIntrReqObj         [IN] Pointer to FirewallIntrReq_t struct which contains
     *                                    information required for HSM to process firewall interrupt
     *                                    request.
     * @return
     * 1. SystemP_SUCCESS if returns successfully
     * 2. SystemP_FAILURE if NACK message is received or client id not registered.
     * 3. SystemP_TIMEOUT if timeout exception occours.
     */
    int32_t HsmClient_FirewallIntr(HsmClient_t *HsmClient,
                                   FirewallIntrReq_t *FirewallIntrReqObj,
                                   uint32_t timeout);

    /**
     * @brief
     * The service issued to HSM Server verifies the certificate and process the keywriter operations,
     * @param HsmClient         [IN] Client object which is using this API.
     * @param certHeader        [IN] point to the location of certificate in the device memory.  This object's memory address needs to be cache aligned.
     * @param timeout           [IN] amount of time to block waiting for
     * semaphore to be available, in units of system ticks (see KERNEL_DPL_CLOCK_PAGE)
     * @return
     * 1. SystemP_SUCCESS if returns successfully
     * 2. SystemP_FAILURE if NACK message is received or client id not registered.
     * 3. SystemP_TIMEOUT if timeout exception occours.
     */
    int32_t HsmClient_keyWriter(HsmClient_t *HsmClient,
                                KeyWriterCertHeader_t *certHeader,
                                uint32_t timeout);

    /**
     * @brief
     *  The service issued to HSM Server retrieves the SWRevision value
     *  based on identifier as param.
     *
     * @param HsmClient [IN] HsmClient object.
     * @param readSWRev [IN] populates SWRev_t struct with SWRev value
     *                       corresponding to identifier.
     * @return
     * 1. SystemP_SUCCESS if returns successfully
     * 2. SystemP_FAILURE if NACK message is received or client id not registered.
     */
    int32_t HsmClient_readSWRev(HsmClient_t *HsmClient,
                                SWRev_t *readSWRev);

    /**
     * @brief
     *  The service issued to HSM Server writes the SWRevision value
     *  based on identifier as param.
     *
     * @param HsmClient [IN] HsmClient object.
     * @param writeSWRev [IN] updates the SWRev efuses with SWRev value
     *                       corresponding to identifier.
     * @return
     * 1. SystemP_SUCCESS if returns successfully
     * 2. SystemP_FAILURE if NACK message is received or client id not registered.
     */
    int32_t HsmClient_writeSWRev(HsmClient_t *HsmClient,
                                 SWRev_t *writeSWRev);

    /**
     * @brief
     *  The service issued to HSM Server retrieves the derived KEK
     *  based on identifier as param.
     *
     *  The service issued to HSM Server retrieves the derived KEK.
     *
     * @param timeout           [IN] amount of time to block waiting for
     * semaphore to be available, in units of system ticks (see KERNEL_DPL_CLOCK_PAGE)
     * @param HsmClient         [IN] HsmClient object.
     * @param getDKEK           [IN] Pointer to DKEK_t which contains the request
     *								 structure for Derived KEK.
     * @return
     * 1. SystemP_SUCCESS if returns successfully
     * 2. SystemP_FAILURE if NACK message is received or client id not registered.
     */
    int32_t HsmClient_getDKEK(HsmClient_t *HsmClient,
                              DKEK_t *getDKEK,
                              uint32_t timeout);
    /**
     * @brief
     * register a client to a particular ClientId
     *
     * @param HsmClient [IN] HsmClient object.
     * @param clientId [IN] enable HSM <--> R5 communication for given clientID
     *
     * @return
     * 1. SystemP_SUCCESS if clientId is available
     * 2. SystemP_FAILURE if clientId is not available or already in use.
     */
    int32_t HsmClient_register(HsmClient_t *HsmClient, uint8_t clientId);

    /**
     * @brief
     * unregister a client to a particular ClientId
     *
     * @param HsmClient [IN] HsmClient object
     * @param clientId [IN] disable HSM <--> R5 communication for given clientId
     *
     */
    void HsmClient_unregister(HsmClient_t *HsmClient, uint8_t clientId);

    /**
     * @brief
     * Current core will wait for bootnotify message from HSM core.
     *
     * @param HsmClient [IN] HsmClient object
     *
     * @param timeToWaitInTicks  [IN] amount of time to block waiting for
     * semaphore to be available, in units of SystemP_timeout if timeout exception occours.system ticks (see KERNEL_DPL_CLOCK_PAGE)
     *
     * @return
     * 1. SystemP_SUCCESS -: when BootNotify received
     * 2. SystemP_FAILURE -: if faulty msg received
     */
    int32_t HsmClient_waitForBootNotify(HsmClient_t *HsmClient, uint32_t timeToWaitInTicks);

    /**
     *  @brief  Loads the HSMRt firmware. This is typically called by SBL.
     *
     *  @param gHSMClient         [IN]  Pointer to registered HSM Client
     *
     * @param pHSMRt_firmware     [IN]  Pointer to signed HSMRt binary
     *
     *  @return SystemP_SUCCESS on success, else SystemP_FAILURE
     *
     */
    int32_t Hsmclient_loadHSMRtFirmware(HsmClient_t *gHSMClient, const uint8_t *pHSMRt_firmware);

    /**
     *  @brief  Loads the HSMRt firmware but does wait for ROM response and boot notification.
     *          This is typically called by SBL.
     *
     * @param pHSMRt_firmware     [IN]  Pointer to signed HSMRt binary
     *
     *  @return SystemP_SUCCESS on success, else SystemP_FAILURE
     *
     */
    int32_t Hsmclient_loadHSMRtFirmwareNonBlocking(const uint8_t *pHSMRt_firmware);

    /**
     *  @brief  Returns the Random Number Generated.
     *
     *  @param  HsmClient            [IN] HsmClient object
     *  @param getRandomNum          [IN] Pointer to RNGReq_t which contains the request
     *								 structure for Random Number Generated.
     *
     * @return
     * 1. SystemP_SUCCESS if returns successfully
     * 2. SystemP_FAILURE if NACK message is received or client id not registered.
     */
    int32_t HsmClient_getRandomNum(HsmClient_t *HsmClient,
                                   RNGReq_t *getRandomNum);

    /**
     * @brief
     *  service request issued to HSM server to parse the certificate to validate authenticity
     *  and identify the firmware component undergoing update
     *  This service is valid only for F29H85x SOC
     *
     * @param HsmClient                [IN] Client object which is using this API.
     * @param pFirmwareUpdateObject     [IN] Pointer to arguments to be passed to HSM core via SIPC.
     *
     * @return
     * 1. SystemP_SUCCESS if returns successfully
     * 2. SystemP_FAILURE if NACK message is received or client id not registered.
     * 3. SystemP_TIMEOUT if timeout exception occours.
     */
    int32_t HsmClient_firmwareUpdate_CertProcess(HsmClient_t *HsmClient,
                                                 FirmwareUpdateReq_t *pFirmwareUpdateObject);

    /**
     * @brief
     *  service request issued to HSM server to program the incoming firmware to device dormant banks
     *  This service is valid only for F29H85x SOC
     *
     * @param HsmClient                [IN] Client object which is using this API.
     * @param pFirmwareUpdateObject     [IN] Pointer to arguments to be passed to HSM core via SIPC.
     *
     * @return
     * 1. SystemP_SUCCESS if returns successfully
     * 2. SystemP_FAILURE if NACK message is received or client id not registered.
     * 3. SystemP_TIMEOUT if timeout exception occours.
     */
    int32_t HsmClient_firmwareUpdate_CodeProgram(HsmClient_t *HsmClient,
                                                 FirmwareUpdateReq_t *pFirmwareUpdateObject);

    /**
     * @brief
     *  service request issued to HSM server to decrypt the firmware programmed in dormant flash bank in place,
     *  perform integrity checks on the decrypted firmware and program the certificate in flash memory
     *  This service is valid only for F29H85x SOC
     *
     * @param HsmClient                [IN] Client object which is using this API.
     * @param pFirmwareUpdateObject     [IN] Pointer to arguments to be passed to HSM core via SIPC.
     *
     * @return
     * 1. SystemP_SUCCESS if returns successfully
     * 2. SystemP_FAILURE if NACK message is received or client id not registered.
     * 3. SystemP_TIMEOUT if timeout exception occours.
     */
    int32_t HsmClient_firmwareUpdate_CodeVerify(HsmClient_t *HsmClient,
                                                FirmwareUpdateReq_t *pFirmwareUpdateObject);

    /**
     * @brief
     *  service request issued to HSM server to validate RoT Switching Certificate
     *
     * @param timeout           [IN] amount of time to block waiting for
     * semaphore to be available, in units of system ticks (see KERNEL_DPL_CLOCK_PAGE)
     * @param HsmClient         [IN] Client object which is using this RoT Switching API.
     * @param cert              [IN] point to the location of certificate in the device memory.
     * @param cert_size         [IN] size of certificate.
     *
     * @return
     * 1. SystemP_SUCCESS if returns successfully
     * 2. SystemP_FAILURE if NACK message is received or client id not registered.
     * 3. SystemP_TIMEOUT if timeout exception occours.
     */
    int32_t HsmClient_VerifyROTSwitchingCertificate(HsmClient_t *HsmClient,
                                  uint8_t *cert,
                                  uint32_t cert_size,
                                  uint32_t timeout);

    /**
     * @brief
     *  service request issued to HSM server to update key revision to 0x2 which changes the root of trust key from
     *  secondary keys to back up keys.
     *
     * @param timeout           [IN] amount of time to block waiting for
     * semaphore to be available, in units of system ticks (see KERNEL_DPL_CLOCK_PAGE)
     * @param HsmClient         [IN] Client object which is using this RoT Switching API.
     *
     * @return
     * 1. SystemP_SUCCESS if returns successfully
     * 2. SystemP_FAILURE if NACK message is received or client id not registered.
     * 3. SystemP_TIMEOUT if timeout exception occours.
     */
    int32_t HsmClient_UpdateKeyRevsion(HsmClient_t *HsmClient,
                                       uint32_t timeout);

/**
 *  @brief  Client request to configure the OTFA regions
 *
 *  @param  HsmClient        [IN] HsmClient object
 *  @param  OTFA_ConfigInfo  [IN] OTFA Config Info
 *  @param  timeout          [IN] timeout
 * 
 * @return
 * 1. SystemP_SUCCESS if returns successfully
 * 2. SystemP_FAILURE if NACK message is received or client id not registered.
 */
int32_t HsmClient_configOTFARegions(HsmClient_t* HsmClient,
                                        OTFA_Config_t* OTFA_ConfigInfo,
                                        uint32_t timeout);

/**
 *  @brief  Client request to read the OTFA regions
 *
 *  @param  HsmClient        [IN] HsmClient object
 *  @param  OTFA_readRegion  [IN] OTFA Read Region
 *  @param  timeout          [IN] timeout
 * 
 * @return
 * 1. SystemP_SUCCESS if reading done successfully
 * 2. SystemP_FAILURE if NACK message is received or client id not registered.
 */
int32_t HsmClient_readOTFARegions(HsmClient_t* HsmClient,
                                        OTFA_readRegion_t* OTFA_readRegion,
                                        uint32_t timeout);

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* HSM_CLIENT_H_ */

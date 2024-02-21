
# coding: utf-8
# wolfcrypt_defs.py
#===============================================================================
from wolfcrypt_globals import *

localwolfCryptComponent   = None
cryptoHwAdditionalDefines = set([])

cryptoWolfSSLIncluded = None
#cryptoSupportCompression = None
cryptoHaveZlib = None

#asn1Support = None

# SYMBOLS used by FTL are put in the cryptoHwAdditionalDefines
cryptoHwAdditionalDefines = set([])

#Any HW that is enabled 
cryptoHwSupported         = False


#Global variables.  Do not modify the defaults
cryptoCurrentHwRngSupport    = ["SW", "SW", "3.2", []]
cryptoCurrentHwMd5Support    = ["SW", "SW", "3.2", []]
cryptoCurrentHwSha1Support   = ["SW", "SW", "3.2", []]
cryptoCurrentHwSha224Support = ["SW", "SW", "3.2", []]
cryptoCurrentHwSha256Support = ["SW", "SW", "3.2", []]
cryptoCurrentHwSha384Support = ["SW", "SW", "3.2", []]
cryptoCurrentHwSha512Support = ["SW", "SW", "3.2", []]
cryptoCurrentHwAesSupport    = ["SW", "SW", "3.2", []]
cryptoCurrentHwDesSupport    = ["SW", "SW", "3.2", []]
cryptoCurrentHwRsaSupport    = ["SW", "SW", "3.2", ["rsa.c"]]
cryptoCurrentHwEccSupport    = ["SW", "SW", "3.2", ["ecc.c", "ecc_fp.c"]]

cryptoCurrentSwRngSupport    = ["SW", "SW", "3.2", []]
cryptoCurrentSwMd5Support    = ["SW", "SW", "3.2", []]
cryptoCurrentSwSha1Support   = ["SW", "SW", "3.2", []]
cryptoCurrentSwSha224Support = ["SW", "SW", "3.2", []]
cryptoCurrentSwSha256Support = ["SW", "SW", "3.2", []]
cryptoCurrentSwSha384Support = ["SW", "SW", "3.2", []]
cryptoCurrentSwSha512Support = ["SW", "SW", "3.2", []]
cryptoCurrentSwAesSupport    = ["SW", "SW", "3.2", []]
cryptoCurrentSwDesSupport    = ["SW", "SW", "3.2", []]
cryptoCurrentSwRsaSupport    = ["SW", "SW", "3.2", ["rsa.c"]]
cryptoCurrentSwEccSupport    = ["SW", "SW", "3.2", ["ecc.c", "ecc_fp.c"]]

cryptoHwFilesDict        = {}
cryptoSwFilesDict        = {}
cryptoWolfCryptFilesDict = {}

cryptoHwFileComponentsDict                = {}
cryptoSwFileComponentsDict                = {}
cryptoWolfCryptFileComponentsDict         = {}
cryptoHwMenuComponentsList                = []
cryptoWolfCryptEnabledMenuComponentsList  = []
cryptoWolfCryptDisabledMenuComponentsList = []

cryptoHwSupportFound = False

def instantiateComponent(cryptoComponent):

	cryptoHW = cryptoComponent.createBooleanSymbol("hw", None)
	cryptoHW.setLabel("Use Hardware Acceleration?")
	cryptoHW.setDescription("Enables harware acceleration of cryptograhic library")

	if (Peripheral.moduleExists("ICM")):
		cryptoHW.setVisible(True)
		cryptoHW.setDefaultValue(True)
	else:
		cryptoHW.setVisible(False)

def onDependentComponentAdded(cryptoComponent, id, trngComponent):
	
	if id == "LIB_CRYPTO_Dependency":
		trngComponent.setSymbolValue("TRNG_Reserved", "TRNGReservedSymbol", True, 1)


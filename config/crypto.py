def instantiateComponent(cryptoComponent):

	cryptoHW = cryptoComponent.createBooleanSymbol("hw", None)
	cryptoHW.setLabel("Use Hardware Acceleration?")
	cryptoHW.setDescription("Enables harware acceleration of cryptograhic library")

	if (Peripheral.moduleExists("ICM")):
		cryptoHW.setVisible(True)
	else:
		cryptoHW.setVisible(False)

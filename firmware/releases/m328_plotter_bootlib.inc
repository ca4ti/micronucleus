# Makefile include for use micronucleus bootloader as usb library 

micronusblib.ld:
	$(file >$@,/* auto generated by micronusblib.inc dont modify */)
	$(file >>$@,PROVIDE(usbCrc16 = 0x00007a50);)
	$(file >>$@,PROVIDE(usbCrc16Append = 0x00007a7a);)
	$(file >>$@,PROVIDE(micronucleusInt = 0x00007a82);)
	$(file >>$@,)
	$(file >>$@,PROVIDE(usbBootVarEnd = 0x00800146);)
	$(file >>$@,PROVIDE(usbBootReserved = 0x00800100);)
	$(file >>$@,PROVIDE(usbConfiguration = 0x00800123);)
	$(file >>$@,PROVIDE(usbCurrentTok = 0x00800122);)
	$(file >>$@,PROVIDE(usbDeviceAddr = 0x00800118);)
	$(file >>$@,PROVIDE(usbInputBufOffset = 0x0080011a);)
	$(file >>$@,PROVIDE(usbMsgPtr = 0x0080011e);)
	$(file >>$@,PROVIDE(usbNewDeviceAddr = 0x00800121);)
	$(file >>$@,PROVIDE(usbRxBuf = 0x00800124);)
	$(file >>$@,PROVIDE(usbRxLen = 0x00800120);)
	$(file >>$@,PROVIDE(usbRxToken = 0x00800119);)
	$(file >>$@,PROVIDE(usbSofCount = 0x0080011d);)
	$(file >>$@,PROVIDE(usbTxBuf = 0x00800101);)
	$(file >>$@,PROVIDE(usbTxLen = 0x0080011c);)
	$(file >>$@,PROVIDE(usbTxStatus1 = 0x0080010c);)
	$(file >>$@,PROVIDE(usbTxStatus3 = 0x0080013a);)
	$(file >>$@,)
	$(file >>$@,SECTIONS)
	$(file >>$@,{)
	$(file >>$@,  usbbv.data : AT (0x00800100))
	$(file >>$@,  {)
	$(file >>$@,    KEEP (*(usbbv.data)))
	$(file >>$@,  })
	$(file >>$@,})

CFLAGS += -DUSBRESERVERDDATA=0x00800146-0x00800100 -DHAVEUSBLIB=1
MCUARCH = avr5
LDFLAGS += -T micronusblib.ld -T ldscripts/$(MCUARCH).x
LDDEPENDS += micronusblib.ld


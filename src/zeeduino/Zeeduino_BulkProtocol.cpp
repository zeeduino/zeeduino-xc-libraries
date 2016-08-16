/*
 * Zeeduino_BulkProtocol.cpp
 *
 *  Created on: Aug 15, 2016
 *      Author: iceman
 */

#include "Arduino.h"

#include "lib/USBDeviceCustom.h"
#include "Zeeduino_BulkProtocol.h"

/**************************************************************************/
/* Zeeduino USB bulk protocol object */

UsbBulkProtocol simpleUsbBulkProtocol;

/**************************************************************************/
/* Class implementation */

static ProtocolPacket commandBuffer;
static ProtocolPacket responseBuffer;

UsbBulkProtocol::UsbBulkProtocol()
{
	memset((void*)&commandBuffer, 0, sizeof(ProtocolPacket));
	memset((void*)&responseBuffer, 0, sizeof(ProtocolPacket));
}

void UsbBulkProtocol::process()
{
    if(UsbBulk.dataAvailable())
    {
    	UsbBulk.read((uint8_t*)&commandBuffer, sizeof(ProtocolPacket));
    	memset((void*)&responseBuffer, 0, sizeof(ProtocolPacket));

    	if(commandBuffer.packetType == PROTOCOL_PACKET_COMMAND)
    	{
    		uint8_t commandId = commandBuffer.commandId;
    		uint8_t payloadLength = commandBuffer.payloadLength < PROTOCOL_PAYLOAD_SIZE ? commandBuffer.payloadLength : PROTOCOL_PAYLOAD_SIZE;

    		// trivial lookup algorithm
    		ProtocolCommandTableEntry* tableEntry = protocolCommandTable;
    		while(tableEntry->commandId != 0)
    		{
    			if(tableEntry->commandId == commandId)
    			{
    				responseBuffer.payloadLength = tableEntry->command(commandBuffer.payload, payloadLength, responseBuffer.payload, PROTOCOL_PAYLOAD_SIZE);
    				responseBuffer.commandId = commandId;
    				responseBuffer.packetType = PROTOCOL_PACKET_RESPONSE;
    				break;
    			}
    			tableEntry++;
    		}
    	}
    	else
    	{
    		responseBuffer.packetType = PROTOCOL_PACKET_ERROR;
    	}

    	UsbBulk.write((uint8_t*)&responseBuffer, sizeof(ProtocolPacket));
    }
}


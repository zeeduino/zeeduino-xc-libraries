/*
 * Zeeduino_BulkProtocol.h
 *
 *  Created on: Aug 15, 2016
 *      Author: iceman
 */

#ifndef ZEEDUINO_BULKPROTOCOL_H_
#define ZEEDUINO_BULKPROTOCOL_H_

#include <inttypes.h>

#if defined(__GNUC__)
#define PRE_PACK
#define POST_PACK	__attribute__((__packed__))
#define ALIGNED(n)      __attribute__((aligned (n)))

#elif defined(__arm)
#define PRE_PACK	__packed
#define POST_PACK
#define ALIGNED(n)      __align(n)

#elif defined(__ICCARM__)
#define PRE_PACK                __packed
#define POST_PACK

#endif

typedef enum
{
  PROTOCOL_PACKET_COMMAND   = 0x10,
  PROTOCOL_PACKET_RESPONSE  = 0x20,
  PROTOCOL_PACKET_ERROR     = 0xF0
} ProtocolPacketType;


// This should be the same as or less than USB_FS_MAX_BULK_PACKET value
#define PROTOCOL_PACKET_SIZE 64
#define PROTOCOL_PAYLOAD_SIZE PROTOCOL_PACKET_SIZE-3

typedef PRE_PACK struct POST_PACK {
  uint8_t packetType;
  uint8_t commandId;
  uint8_t payloadLength;
  uint8_t payload[PROTOCOL_PAYLOAD_SIZE];
} ProtocolPacket;

typedef uint8_t (*ProtocolCallback)(uint8_t* payload, uint8_t length, uint8_t* buffer, uint8_t size);
typedef struct
{
	uint8_t commandId;
	ProtocolCallback command;
} ProtocolCommandTableEntry;

#define PROTOCOL_COMMAND_TABLE_END {0,0}

extern ProtocolCommandTableEntry protocolCommandTable[];

class UsbBulkProtocol
{
public:
	UsbBulkProtocol();

	void process();
private:
};

extern UsbBulkProtocol simpleUsbBulkProtocol;


#endif /* ZEEDUINO_BULKPROTOCOL_H_ */

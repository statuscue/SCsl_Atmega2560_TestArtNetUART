/*
 Name:		SCpj_TestArtNetUART.ino
 Created:	09-Mar-19 13:43:44
 Author:	statuscue
 Editor:	http://hes.od.ua
*/

/*
	Copyright 2019-2019 by Yevhen Mykhailov
	Art-Net(TM) Designed by and Copyright Artistic Licence Holdings Ltd.
*/

#include <SClb_Arduino_DMXEthernet.h>
#include <SClb_ArtNetNode1.h>
#include <SClb_ArtNetNode2.h>
#include <SClb_ArtNetNode3.h>
#include <SClb_ArtNetNode4.h>
#include <SClb_Atmega2560_DMXUART_C0.h>
#include <SClb_Atmega2560_DMXUART_C1.h>
#include <SClb_Atmega2560_DMXUART_C2.h>
#include <SClb_Atmega2560_DMXUART_C3.h>

#include <SPI.h>
#include <Ethernet.h>
#include <EthernetUdp.h>

#define USE_DHCP 1

#define MAC_ADDRESS 0x90, 0xA2, 0xDA, 0x10, 0x6C, 0xA8
#define IP_ADDRESS 192,168,0,77
#define GATEWAY_IP 192,168,0,1
#define SUBNET_MASK 255,255,255,0
#define BROADCAST_IP 192,168,0,255

#define ARTNET_NODE_NAME "STATUCUE ArtNET"

#define SDSELECT_PIN 4

//*********************** globals ***********************

//network addresses
byte mac[] = { MAC_ADDRESS };
IPAddress ip(IP_ADDRESS);
IPAddress gateway(GATEWAY_IP);
IPAddress subnet_mask(SUBNET_MASK);

#if defined( BROADCAST_IP )
IPAddress broadcast_ip(BROADCAST_IP);
#else
IPAddress broadcast_ip = INADDR_NONE;
#endif

// An EthernetUDP instance to let us send and receive packets over UDP
EthernetUDP eUDP;

uint8_t artnetBuffer[ARTNET_BUFFER_MAX];
SCArtNet1* artNetInterface_0_0;
SCArtNet1* artNetInterface_0_1;
SCArtNet1* artNetInterface_0_2;
SCArtNet1* artNetInterface_0_3;
SCArtNet2* artNetInterface_0_4;
SCArtNet2* artNetInterface_0_5;
SCArtNet2* artNetInterface_0_6;
SCArtNet2* artNetInterface_0_7;
SCArtNet3* artNetInterface_0_8;
SCArtNet3* artNetInterface_0_9;
SCArtNet3* artNetInterface_0_10;
SCArtNet3* artNetInterface_0_11;
SCArtNet4* artNetInterface_0_12;
SCArtNet4* artNetInterface_0_13;
SCArtNet4* artNetInterface_0_14;
SCArtNet4* artNetInterface_0_15;


uint8_t level = 0;


// the setup function runs once when you press reset or power the board
void setup() {
#if defined(SDSELECT_PIN)
	pinMode(SDSELECT_PIN, OUTPUT);
#endif
	// Initialize Ethernet
	if (USE_DHCP) {
		Ethernet.begin(mac);										// DHCP
	}
	else {
		Ethernet.begin(mac, ip, gateway, gateway, subnet_mask);		// Static
	}
	//************************
	artNetInterface_0_0 = new SCArtNet1(Ethernet.localIP(), Ethernet.subnetMask(), artnetBuffer);
	artNetInterface_0_0->setSubnetUniverse(0, 0);
	artNetInterface_0_1 = new SCArtNet1(Ethernet.localIP(), Ethernet.subnetMask(), artnetBuffer);
	artNetInterface_0_1->setSubnetUniverse(0, 1);
	artNetInterface_0_2 = new SCArtNet1(Ethernet.localIP(), Ethernet.subnetMask(), artnetBuffer);
	artNetInterface_0_2->setSubnetUniverse(0, 2);
	artNetInterface_0_3 = new SCArtNet1(Ethernet.localIP(), Ethernet.subnetMask(), artnetBuffer);
	artNetInterface_0_3->setSubnetUniverse(0, 3);
	//************************
	artNetInterface_0_4 = new SCArtNet2(Ethernet.localIP(), Ethernet.subnetMask(), artnetBuffer);
	artNetInterface_0_4->setSubnetUniverse(0, 4);
	artNetInterface_0_5 = new SCArtNet2(Ethernet.localIP(), Ethernet.subnetMask(), artnetBuffer);
	artNetInterface_0_5->setSubnetUniverse(0, 5);
	artNetInterface_0_6 = new SCArtNet2(Ethernet.localIP(), Ethernet.subnetMask(), artnetBuffer);
	artNetInterface_0_6->setSubnetUniverse(0, 6);
	artNetInterface_0_7 = new SCArtNet2(Ethernet.localIP(), Ethernet.subnetMask(), artnetBuffer);
	artNetInterface_0_7->setSubnetUniverse(0, 7);
	//************************
	artNetInterface_0_8 = new SCArtNet3(Ethernet.localIP(), Ethernet.subnetMask(), artnetBuffer);
	artNetInterface_0_8->setSubnetUniverse(0, 8);
	artNetInterface_0_9 = new SCArtNet3(Ethernet.localIP(), Ethernet.subnetMask(), artnetBuffer);
	artNetInterface_0_9->setSubnetUniverse(0, 9);
	artNetInterface_0_10 = new SCArtNet3(Ethernet.localIP(), Ethernet.subnetMask(), artnetBuffer);
	artNetInterface_0_10->setSubnetUniverse(0, 10);
	artNetInterface_0_11 = new SCArtNet3(Ethernet.localIP(), Ethernet.subnetMask(), artnetBuffer);
	artNetInterface_0_11->setSubnetUniverse(0, 11);
	//************************
	artNetInterface_0_12 = new SCArtNet4(Ethernet.localIP(), Ethernet.subnetMask(), artnetBuffer);
	artNetInterface_0_12->setSubnetUniverse(0, 12);
	artNetInterface_0_13 = new SCArtNet4(Ethernet.localIP(), Ethernet.subnetMask(), artnetBuffer);
	artNetInterface_0_13->setSubnetUniverse(0, 13);
	artNetInterface_0_14 = new SCArtNet4(Ethernet.localIP(), Ethernet.subnetMask(), artnetBuffer);
	artNetInterface_0_14->setSubnetUniverse(0, 14);
	artNetInterface_0_15 = new SCArtNet4(Ethernet.localIP(), Ethernet.subnetMask(), artnetBuffer);
	artNetInterface_0_15->setSubnetUniverse(0, 15);

	//************************
	eUDP.begin(artNetInterface_0_0->dmxPort());
	((SCArtNet1*)artNetInterface_0_0)->setNodeName(ARTNET_NODE_NAME);
	((SCArtNet1*)artNetInterface_0_0)->send_art_poll_reply(&eUDP);
	eUDP.begin(artNetInterface_0_1->dmxPort());
	((SCArtNet1*)artNetInterface_0_1)->setNodeName(ARTNET_NODE_NAME);
	((SCArtNet1*)artNetInterface_0_1)->send_art_poll_reply(&eUDP);
	eUDP.begin(artNetInterface_0_2->dmxPort());
	((SCArtNet1*)artNetInterface_0_2)->setNodeName(ARTNET_NODE_NAME);
	((SCArtNet1*)artNetInterface_0_2)->send_art_poll_reply(&eUDP);
	eUDP.begin(artNetInterface_0_3->dmxPort());
	((SCArtNet1*)artNetInterface_0_3)->setNodeName(ARTNET_NODE_NAME);
	((SCArtNet1*)artNetInterface_0_3)->send_art_poll_reply(&eUDP);
	//************************
	eUDP.begin(artNetInterface_0_4->dmxPort());
	((SCArtNet2*)artNetInterface_0_4)->setNodeName(ARTNET_NODE_NAME);
	((SCArtNet2*)artNetInterface_0_4)->send_art_poll_reply(&eUDP);
	eUDP.begin(artNetInterface_0_5->dmxPort());
	((SCArtNet2*)artNetInterface_0_5)->setNodeName(ARTNET_NODE_NAME);
	((SCArtNet2*)artNetInterface_0_5)->send_art_poll_reply(&eUDP);
	eUDP.begin(artNetInterface_0_6->dmxPort());
	((SCArtNet2*)artNetInterface_0_6)->setNodeName(ARTNET_NODE_NAME);
	((SCArtNet2*)artNetInterface_0_6)->send_art_poll_reply(&eUDP);
	eUDP.begin(artNetInterface_0_7->dmxPort());
	((SCArtNet2*)artNetInterface_0_7)->setNodeName(ARTNET_NODE_NAME);
	((SCArtNet2*)artNetInterface_0_7)->send_art_poll_reply(&eUDP);
	//************************
	eUDP.begin(artNetInterface_0_8->dmxPort());
	((SCArtNet3*)artNetInterface_0_8)->setNodeName(ARTNET_NODE_NAME);
	((SCArtNet3*)artNetInterface_0_8)->send_art_poll_reply(&eUDP);
	eUDP.begin(artNetInterface_0_9->dmxPort());
	((SCArtNet3*)artNetInterface_0_9)->setNodeName(ARTNET_NODE_NAME);
	((SCArtNet3*)artNetInterface_0_9)->send_art_poll_reply(&eUDP);
	eUDP.begin(artNetInterface_0_10->dmxPort());
	((SCArtNet3*)artNetInterface_0_10)->setNodeName(ARTNET_NODE_NAME);
	((SCArtNet3*)artNetInterface_0_10)->send_art_poll_reply(&eUDP);
	eUDP.begin(artNetInterface_0_11->dmxPort());
	((SCArtNet3*)artNetInterface_0_11)->setNodeName(ARTNET_NODE_NAME);
	((SCArtNet3*)artNetInterface_0_11)->send_art_poll_reply(&eUDP);
	//************************
	eUDP.begin(artNetInterface_0_12->dmxPort());
	((SCArtNet4*)artNetInterface_0_12)->setNodeName(ARTNET_NODE_NAME);
	((SCArtNet4*)artNetInterface_0_12)->send_art_poll_reply(&eUDP);
	eUDP.begin(artNetInterface_0_13->dmxPort());
	((SCArtNet4*)artNetInterface_0_13)->setNodeName(ARTNET_NODE_NAME);
	((SCArtNet4*)artNetInterface_0_13)->send_art_poll_reply(&eUDP);
	eUDP.begin(artNetInterface_0_14->dmxPort());
	((SCArtNet4*)artNetInterface_0_14)->setNodeName(ARTNET_NODE_NAME);
	((SCArtNet4*)artNetInterface_0_14)->send_art_poll_reply(&eUDP);
	eUDP.begin(artNetInterface_0_15->dmxPort());
	((SCArtNet4*)artNetInterface_0_15)->setNodeName(ARTNET_NODE_NAME);
	((SCArtNet4*)artNetInterface_0_15)->send_art_poll_reply(&eUDP);

	SCDMXUSART0.startOutput();
	//SCDMXUSART0.setMaxSlots(512);
	SCDMXUSART1.startOutput();
	//SCDMXUSART1.setMaxSlots(512);
	SCDMXUSART2.startOutput();
	//SCDMXUSART2.setMaxSlots(512);
	SCDMXUSART3.startOutput();
	//SCDMXUSART3.setMaxSlots(512);

}

// the loop function runs over and over again until power down or reset
void loop() {
	// Send DMX
	uint16_t packetSize = eUDP.parsePacket();

	if (packetSize) {
		packetSize = eUDP.read(artnetBuffer, ARTNET_BUFFER_MAX);
		//************************
		uint8_t read_result_artnet_0_0 = artNetInterface_0_0->readDMXPacketContents(&eUDP, packetSize);
		uint8_t read_result_artnet_0_1 = artNetInterface_0_1->readDMXPacketContents(&eUDP, packetSize);
		uint8_t read_result_artnet_0_2 = artNetInterface_0_2->readDMXPacketContents(&eUDP, packetSize);
		uint8_t read_result_artnet_0_3 = artNetInterface_0_3->readDMXPacketContents(&eUDP, packetSize);
		//************************
		uint8_t read_result_artnet_0_4 = artNetInterface_0_4->readDMXPacketContents(&eUDP, packetSize);
		uint8_t read_result_artnet_0_5 = artNetInterface_0_5->readDMXPacketContents(&eUDP, packetSize);
		uint8_t read_result_artnet_0_6 = artNetInterface_0_6->readDMXPacketContents(&eUDP, packetSize);
		uint8_t read_result_artnet_0_7 = artNetInterface_0_7->readDMXPacketContents(&eUDP, packetSize);
		//************************
		uint8_t read_result_artnet_0_8 = artNetInterface_0_8->readDMXPacketContents(&eUDP, packetSize);
		uint8_t read_result_artnet_0_9 = artNetInterface_0_9->readDMXPacketContents(&eUDP, packetSize);
		uint8_t read_result_artnet_0_10 = artNetInterface_0_10->readDMXPacketContents(&eUDP, packetSize);
		uint8_t read_result_artnet_0_11 = artNetInterface_0_11->readDMXPacketContents(&eUDP, packetSize);
		//************************
		uint8_t read_result_artnet_0_12 = artNetInterface_0_12->readDMXPacketContents(&eUDP, packetSize);
		uint8_t read_result_artnet_0_13 = artNetInterface_0_13->readDMXPacketContents(&eUDP, packetSize);
		uint8_t read_result_artnet_0_14 = artNetInterface_0_14->readDMXPacketContents(&eUDP, packetSize);
		uint8_t read_result_artnet_0_15 = artNetInterface_0_15->readDMXPacketContents(&eUDP, packetSize);

		//************************
		if (read_result_artnet_0_0 == RESULT_DMX_RECEIVED) {
			for (int i = 1; i <= artNetInterface_0_0->numberOfSlots(); i++) {
				SCDMXUSART0.setSlot(i, artNetInterface_0_0->getSlot(i));
			}
		}
		if (read_result_artnet_0_1 == RESULT_DMX_RECEIVED) {
			for (int i = 1; i <= artNetInterface_0_1->numberOfSlots(); i++) {
				SCDMXUSART1.setSlot(i, artNetInterface_0_1->getSlot(i));
			}
		}
		if (read_result_artnet_0_2 == RESULT_DMX_RECEIVED) {
			for (int i = 1; i <= artNetInterface_0_2->numberOfSlots(); i++) {
				SCDMXUSART2.setSlot(i, artNetInterface_0_2->getSlot(i));
			}
		}
		if (read_result_artnet_0_3 == RESULT_DMX_RECEIVED) {
			for (int i = 1; i <= artNetInterface_0_3->numberOfSlots(); i++) {
				SCDMXUSART3.setSlot(i, artNetInterface_0_3->getSlot(i));
			}
		}
		//************************
		if (read_result_artnet_0_4 == RESULT_DMX_RECEIVED) {
			for (int i = 1; i <= artNetInterface_0_4->numberOfSlots(); i++) {
				SCDMXUSART0.setSlot(i, artNetInterface_0_4->getSlot(i));
			}
		}
		if (read_result_artnet_0_5 == RESULT_DMX_RECEIVED) {
			for (int i = 1; i <= artNetInterface_0_5->numberOfSlots(); i++) {
				SCDMXUSART1.setSlot(i, artNetInterface_0_5->getSlot(i));
			}
		}
		if (read_result_artnet_0_6 == RESULT_DMX_RECEIVED) {
			for (int i = 1; i <= artNetInterface_0_6->numberOfSlots(); i++) {
				SCDMXUSART2.setSlot(i, artNetInterface_0_6->getSlot(i));
			}
		}
		if (read_result_artnet_0_7 == RESULT_DMX_RECEIVED) {
			for (int i = 1; i <= artNetInterface_0_7->numberOfSlots(); i++) {
				SCDMXUSART3.setSlot(i, artNetInterface_0_7->getSlot(i));
			}
		}
		//************************
		if (read_result_artnet_0_8 == RESULT_DMX_RECEIVED) {
			for (int i = 1; i <= artNetInterface_0_8->numberOfSlots(); i++) {
				SCDMXUSART0.setSlot(i, artNetInterface_0_8->getSlot(i));
			}
		}
		if (read_result_artnet_0_9 == RESULT_DMX_RECEIVED) {
			for (int i = 1; i <= artNetInterface_0_9->numberOfSlots(); i++) {
				SCDMXUSART1.setSlot(i, artNetInterface_0_9->getSlot(i));
			}
		}
		if (read_result_artnet_0_10 == RESULT_DMX_RECEIVED) {
			for (int i = 1; i <= artNetInterface_0_10->numberOfSlots(); i++) {
				SCDMXUSART2.setSlot(i, artNetInterface_0_10->getSlot(i));
			}
		}
		if (read_result_artnet_0_11 == RESULT_DMX_RECEIVED) {
			for (int i = 1; i <= artNetInterface_0_11->numberOfSlots(); i++) {
				SCDMXUSART3.setSlot(i, artNetInterface_0_11->getSlot(i));
			}
		}
		//************************
		if (read_result_artnet_0_12 == RESULT_DMX_RECEIVED) {
			for (int i = 1; i <= artNetInterface_0_12->numberOfSlots(); i++) {
				SCDMXUSART0.setSlot(i, artNetInterface_0_12->getSlot(i));
			}
		}
		if (read_result_artnet_0_13 == RESULT_DMX_RECEIVED) {
			for (int i = 1; i <= artNetInterface_0_13->numberOfSlots(); i++) {
				SCDMXUSART1.setSlot(i, artNetInterface_0_13->getSlot(i));
			}
		}
		if (read_result_artnet_0_14 == RESULT_DMX_RECEIVED) {
			for (int i = 1; i <= artNetInterface_0_14->numberOfSlots(); i++) {
				SCDMXUSART2.setSlot(i, artNetInterface_0_14->getSlot(i));
			}
		}
		if (read_result_artnet_0_15 == RESULT_DMX_RECEIVED) {
			for (int i = 1; i <= artNetInterface_0_15->numberOfSlots(); i++) {
				SCDMXUSART3.setSlot(i, artNetInterface_0_15->getSlot(i));
			}
		}
	}
}

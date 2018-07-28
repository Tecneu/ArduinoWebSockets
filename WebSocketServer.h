#ifndef __WEBSOCKETSERVER_DOT_H_INCLUDED_
#define __WEBSOCKETSERVER_DOT_H_INCLUDED_

#include "WebSocket.h"

class WebSocketServer {
public:
	WebSocketServer(uint16_t port);
	~WebSocketServer();
	
	void begin();
	void shutdown();
	
	void listen();
	
	uint8_t countClients();
	
	// ---
	
	void setOnOpenCallback(onOpenCallback *callback);
	void setOnCloseCallback(onCloseCallback *callback);
	void setOnMessageCallback(onMessageCallback *callback);
	void setOnErrorCallback(onErrorCallback *callback);
	
private:
	void _heartbeat();

#if defined(_USE_WIFI) && defined(ESP8266)
	WebSocket *_getWebSocket(WiFiClient client);
	bool _handleRequest(WiFiClient &client);
	void _rejectRequest(WiFiClient &client, const eWebSocketError code);
#else
	WebSocket *_getWebSocket(EthernetClient client);
	bool _handleRequest(EthernetClient &client);
	void _rejectRequest(EthernetClient &client, const eWebSocketError code);
#endif
	
	void _triggerError(const eWebSocketError code);
	
private:
#if defined(_USE_WIFI) && defined(ESP8266)
	WiFiServer m_Server;
#else
	EthernetServer m_Server;
#endif

	WebSocket *m_pSockets[MAX_CONNECTIONS];
	
	onOpenCallback *_onOpen;
	onCloseCallback *_onClose;
	onMessageCallback *_onMessage;
	onErrorCallback *_onError;
};

#endif
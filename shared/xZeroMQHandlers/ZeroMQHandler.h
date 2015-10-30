//------------------------------------------------------------------------------
// Class: ZeroMQHandler
//------------------------------------------------------------------------------
#ifndef __Eaagles_xZeroMQ_ZeroMQHandler_H__
#define __Eaagles_xZeroMQ_ZeroMQHandler_H__

#include "openeaagles/basic/NetHandler.h"

#include <map>
#include <string>

namespace Eaagles {
   namespace Basic { class Boolean; class Integer; class List; class PairStream; class String; };

namespace xZeroMQHandlers {
   class ZeroMQContext;

//------------------------------------------------------------------------------
// Class: ZeroMQHandler
//
// Description: Manages a ZeroMQ (0MQ) socket
//
// ZeroMQHandler defines the basic 0MQ socket interface.  It is derived from
// the Basic::NetHandler.  It is noted that 0MQ sockets can only talk to other
// 0MQ sockets.  Ensure any communications strategy uses 0MQ at endpoints.
//
// The derivation from NetHandler is to allow this handler to be used in place
// of other NetHandler objects but 0MQ is so dissimilar that only the
// signature type is used - little sharing of methods.
//
// The following slots are provided for socket definition:
//
//    context     - The context used to create the socket
//    socketType  - Socket type (REQ, REP, DEALER, ROUTER, PUB, SUB, XPUB,
//                  XSUB, PUSH, PULL, PAIR, or STREAM)
//    connect     - Connect a full endpoint definition string (tcp://*:12345)
//    accept      - Accept a full endpoint definition string (tcp://*:12345)
//    noWait      - Set the no-wait flag
//    <options>   - The set options will each have a slot for them
//
//------------------------------------------------------------------------------
class ZeroMQHandler : public Basic::NetHandler
{
   DECLARE_SUBCLASS(ZeroMQHandler, Basic::NetHandler)

public:
   ZeroMQHandler();

   // Subscribe to a message (SUB type only)
   virtual bool setSubscribe(const Basic::String& msg);

   // Unsubscribe a message (SUB type only)
   virtual bool setUnsubscribe(const Basic::String& msg);

   // Casting for the dereference operator much like Basic::String.  This is
   // useful when using a 0MQ function directly like zmq_poll.
   operator void* ()               { return socket; }
   operator const void* () const   { return socket; }

   // NetHandler functions
   bool initNetwork(const bool noWaitFlag) override;
   bool isConnected() const override;
   bool closeConnection() override;
   bool sendData(const char* const packet, const int size) override;
   unsigned int recvData(char* const packet, const int maxSize) override;
   bool setBlocked() override;
   bool setNoWait() override;

protected:
   virtual bool setContext(ZeroMQContext* const context);
   virtual bool setSocketType(const char* const type);
   virtual bool setConnect(const char* const type);
   virtual bool setAccept(const char* const type);
   virtual bool setNoWait(const bool noWait);
   virtual bool setLinger(const int period);
   virtual bool setBackLog(const int count);
   virtual bool setIdentity(const char* const ident);
   virtual bool setSendBufSize(const int count);
   virtual bool setRecvBufSize(const int count);
   virtual bool setSendHWM(const int mark);
   virtual bool setRecvHWM(const int mark);

   // Slots
   virtual bool setSlotContext(ZeroMQContext* const msg);
   virtual bool setSlotSocketType(const Basic::String* const msg);
   virtual bool setSlotConnect(const Basic::String* const msg);
   virtual bool setSlotAccept(const Basic::String* const msg);
   virtual bool setSlotNoWait(const Basic::Boolean* const msg);
   virtual bool setSlotLinger(const Basic::Integer* const msg);
   virtual bool setSlotSubscribe(const Basic::String* const msg);
   virtual bool setSlotSubscribe(const Basic::PairStream* const msg);
   virtual bool setSlotBackLog(const Basic::Integer* const msg);
   virtual bool setSlotIdentity(const Basic::String* const msg);
   virtual bool setSlotSendBufSize(const Basic::Integer* const msg);
   virtual bool setSlotRecvBufSize(const Basic::Integer* const msg);
   virtual bool setSlotSendHWM(const Basic::Integer* const msg);
   virtual bool setSlotRecvHWM(const Basic::Integer* const msg);

private:
   void initData();

private:
   // The master context is the main process context.  It will be used by
   // all subsequent handlers unless otherwise specified with the context
   // slot.
   static ZeroMQContext* masterContext;

   // Mapping types used to convert the enums and 0MQ constants to strings
   // and back again!
   typedef std::map <std::string, int> s2i_t;
   typedef std::map <int, std::string> i2s_t;

   static s2i_t sts2i;           // ZeroMQHandler type maps
   static i2s_t sti2s;

protected:
   ZeroMQContext* context;       // Parent context (Eaagles not ZeroMQ)
   int            socketType;    // Socket type
   std::string    endpoint;      // Endpoint for binding
   int            linger;        // Socket linger period (ms)
   Basic::safe_ptr<const Basic::List> subscriptions;     // SUB type Message filters
   int            backLog;       // Connection queue size
   std::string    identity;      // Socket identity
   int            sendBufSize;   // Kernel buffer size for sending
   int            recvBufSize;   // Kernel buffer size for receiving
   int            sendHWM;       // High-water-mark for outbound messages
   int            recvHWM;       // High-water-mark for inbound messages
   bool           noWait;        // No wait flag from the slot
   void*          socket;        // 0MQ socket
   bool           doBind;        // Accept or connect!
   bool           dontWait;      // 0MQ no wait flag
   bool           ready;         // Initialization was successful
};

}  // End xZeroMQHandlers namespace
}  // End Eaagles namespace

#endif


//------------------------------------------------------------------------------
// Class: Factory
//
// Description: Class factory
//------------------------------------------------------------------------------
#ifndef __oe_xZeroMQHandlers_Factory_H__
#define __oe_xZeroMQHandlers_Factory_H__

namespace oe {

namespace Basic { class Object; }

namespace xZeroMQHandlers {

class Factory
{
public:
   static Basic::Object* createObj(const char* name);

protected:
   Factory();   // prevent object creation
};

}  // end namespace xZeroMQHandlers
}  // end namespace oe

#endif

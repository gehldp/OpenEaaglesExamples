
#ifndef __oe_xzmq_factory_H__
#define __oe_xzmq_factory_H__

namespace oe {

namespace basic { class Object; }

namespace xZeroMQHandlers {

basic::Object* factory(const char* name);

}
}

#endif
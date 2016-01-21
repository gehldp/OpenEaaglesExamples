//------------------------------------------------------------------------------
// Class: TestComputer
//
// Description:
//    Onboard computer for IrMissile, provides basic functionality
//    Controls a TrackManager, IrSensor, & IrSeeker.
//    Updates gimbal to point at predicted az/el of strongest signal in IFOV
//    Provides these methods in public i/f mainly for IrMissile
//       haveTgt()   true if computer/seeker currently tracking a target
//
//------------------------------------------------------------------------------
#ifndef __oe_Example_TestComputer_H__
#define __oe_Example_TestComputer_H__

#include "openeaagles/simulation/OnboardComputer.h"

namespace oe {
namespace Example {

class TestComputer : public Simulation::OnboardComputer
{
    DECLARE_SUBCLASS(TestComputer, Simulation::OnboardComputer)

public:
   TestComputer();
   bool haveTgt() const { return haveTarget; }

   void updateShootList(const bool step = false) override;      // Updates the shoot list

   void updateTC(const LCreal dt = 0.0) override;

   void reset() override;

protected:
   // process() subfunction, tells computer if we are tracking a target or not
   virtual bool processIr();

   void process(const LCreal dt) override;

private:
   bool uncaged;      // flag that indicates whether gimbal is free to track target
   bool haveTarget;   // flag indicating if we have a target track
};

} // End Example namespace
} // End oe namespace

#endif



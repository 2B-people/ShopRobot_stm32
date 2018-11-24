#ifndef control_h
#define control_h

#include "Kinematics.h"
#include "motor.h"
#include "config.h"

#ifdef __cplusplus
extern "C"
{
    void move_base();
    void stop_base();
		void 	yt_move_base();
#endif //__cplusplus

#ifdef __cplusplus
}
#endif //__cplusplus

#endif




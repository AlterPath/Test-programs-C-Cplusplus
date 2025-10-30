
#include <bur/plctypes.h>

#ifdef _DEFAULT_INCLUDES
	#include <AsDefault.h>
#endif

void _INIT ProgramInit(void)
{
	fb_motor1.dt = 0.01;
	fb_motor1.ke = 0.24;
	fb_motor1.Tm = 0.1;
	fb_motor1.u = 0;
	fb_motor1.integrator.dt=0.01;
	
	fb_motor2.dt = 0.01;
	fb_motor2.ke = 0.24;
	fb_motor2.Tm = 0.1;
	fb_motor2.u = 0;
	fb_motor2.integrator.dt=0.01;
	
	fb_controller.dt = 0.01;
	fb_controller.integrator.dt = 0.01;
	fb_controller.k_i = 2.7;
	fb_controller.k_p = 0.3;
	fb_controller.max_abs_value = 24.0;
	
	Speed = 0;
	counter = 0;
	Enable = 1;
}

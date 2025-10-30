
#include <bur/plctypes.h>
#ifdef __cplusplus
	extern "C"
	{
#endif
	#include "Library.h"
#ifdef __cplusplus
	};
#endif
/* TODO: Add your comment here */
void FB_Motor(struct FB_Motor* inst)
{
	/*TODO: Add your code here*/
	REAL A = (inst->u / inst->ke - inst->w) / inst->Tm;
	inst->integrator.in = A;
	FB_Integrator(&inst->integrator);
	
	inst->w = inst->integrator.out;
}

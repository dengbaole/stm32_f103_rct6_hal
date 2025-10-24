#include "platform.h"

int main(void) {
	platform_init();
	uevt_bc_e(UEVT_APP_BOOT);
	while(1) {
		app_sched_execute();
	}
}



#include <motor_position.h>

void motor_position(int encoder_step, int32_t *Steps, int8_t *Direction){
	
	
	// State machine variables
	static State current_state = STATE_IDLE;
	static int32_t current_steps = 0;
	static int8_t current_direction = 0;


	// Update the state machine based on the encoder step
	switch (current_state) {
		case STATE_IDLE:
		if (encoder_step == 1) {
			current_state = STATE_FORWARD;
			current_direction = 1;
			current_steps = 1;
		} else if (encoder_step == -1) {
			current_state = STATE_BACKWARD;
			current_direction = -1;
			current_steps = -1;
		}
		break;
		
		case STATE_FORWARD:
		if (encoder_step == 0) {
			current_state = STATE_IDLE;
			//current_direction = 0;
			current_steps = 0;
		} else if (encoder_step == -1) {
			current_state = STATE_BACKWARD;
			current_direction = -1;
			current_steps = -1;
		} else {
			current_steps++;
			current_direction = 1;
			if (current_steps >= MAX_STEPS) {
				current_steps = MAX_STEPS;
			}
		}
		break;
	
		case STATE_BACKWARD:
		if (encoder_step == 0) {
			current_state = STATE_IDLE;
			//current_direction = 0;
			current_steps = 0;
		} else if (encoder_step == 1) {
			current_state = STATE_FORWARD;
			current_direction = 1;
			current_steps = 1;
		} else {
			current_steps--;
			current_direction = -1;
			if (current_steps <= MIN_STEPS) {
				current_steps = MIN_STEPS;
			}
		}
		break;
		}
		
	*Steps = current_steps;
	*Direction = current_direction;
}
/*
 * pid.h
 *
 *  Created on: Sep 17, 2024
 *      Author: AI FARM
 */

#ifndef INC_CONTROLLERS_PID_H_
#define INC_CONTROLLERS_PID_H_

void controllerPidInit(void);
bool controllerPidTest(void);
void controllerPid(control_t *control, const setpoint_t *setpoint,
                                         const sensorData_t *sensors,
                                         const state_t *state,
                                         const stabilizerStep_t stabilizerStep);

#endif /* INC_CONTROLLERS_PID_H_ */

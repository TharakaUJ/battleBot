#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/pwm.h>
#include <zephyr/logging/log.h>

LOG_MODULE_REGISTER(diff_drive, LOG_LEVEL_INF);

/* Devicetree node identifiers */
#define PWM_LEFT_NODE  DT_ALIAS(pwm_left)
#define PWM_RIGHT_NODE DT_ALIAS(pwm_right)

#if !DT_NODE_HAS_STATUS(PWM_LEFT_NODE, okay) || !DT_NODE_HAS_STATUS(PWM_RIGHT_NODE, okay)
#error "Unsupported board: PWM devicetree aliases not defined"
#endif

static const struct pwm_dt_spec pwm_left = PWM_DT_SPEC_GET(PWM_LEFT_NODE);
static const struct pwm_dt_spec pwm_right = PWM_DT_SPEC_GET(PWM_RIGHT_NODE);

/* PWM period in nanoseconds (e.g., 20kHz = 50000ns) */
#define PWM_PERIOD_NS  50000

/* Differential Control Function */
void set_motors(int32_t left_speed, int32_t right_speed)
{
    // Clamp speeds between 0 and 100
    left_speed = CLAMP(left_speed, 0, 100);
    right_speed = CLAMP(right_speed, 0, 100);

    // Convert % to duty cycle (assuming duty_cycle = period * % / 100)
    uint32_t left_dc = (PWM_PERIOD_NS * left_speed) / 100;
    uint32_t right_dc = (PWM_PERIOD_NS * right_speed) / 100;

    pwm_set_dt(&pwm_left, PWM_PERIOD_NS, left_dc);
    pwm_set_dt(&pwm_right, PWM_PERIOD_NS, right_dc);
}

int main(void)
{
    int ret;

    LOG_INF("Differential Drive Controller Starting");

    if (!pwm_is_ready_dt(&pwm_left) || !pwm_is_ready_dt(&pwm_right)) {
        LOG_ERR("PWM devices not ready");
        return -1;
    }

    // Example driving loop: Move forward then turn
    while (1) {
        LOG_INF("Forward");
        set_motors(70, 70); // 70% speed
        k_sleep(K_SECONDS(2));

        LOG_INF("Turn Right");
        set_motors(60, 20); // Differential speed
        k_sleep(K_SECONDS(2));

        LOG_INF("Stop");
        set_motors(0, 0);
        k_sleep(K_SECONDS(1));
    }
    return 0;
}

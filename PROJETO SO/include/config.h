#ifndef config_h
#define config_h

#define MAX_SENSORS 20
#define MAX_KEYS 50
#define MAX_ACTUATORS 10
#define MAX_RULES 30
#define MAX_ALERTS 100

typedef struct {
    int time_unit_ms, max_keys, max_sensors, max_actuators, max_energy_budget;
    int max_rules, max_alerts, cooldown_min, cooldown_max;
    int history_flush_interval, snapshot_interval, sensor_timeout, reading_buffer_size;
    int num_actuators;
    struct { char name[20]; int is_high_power; } actuators[MAX_ACTUATORS];
} config_t;

#endif /* config_h */

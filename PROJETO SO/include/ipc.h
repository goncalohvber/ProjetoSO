//
//  ipc.h
//  
//
//  Created by Gonçalo Henrique Viegas Bernardino on 18/11/2026.
//

#ifndef ipc_h
#define ipc_h

// SHM1: Estatísticas Globais
typedef struct {
pthread_mutex_t mutex;
int total_readings;
int total_commands;
int total_alerts;
int total_actuator_starts;
struct timespec start_time; // CLOCK_MONOTONIC (ver 2.4)
int simulation_time_units;
} global_stats_shm_t;

// SHM2: Estado dos Atuadores
typedef struct {
char id[20];
int is_high_power; // 1 consome sem_energy; 0 independente
int status; // 0=OFF, 1=ON, 2=COOLDOWN
int on_until_ut;
int cooldown_until_ut;
pthread_mutex_t mutex;
} actuator_shm_entry_t;

typedef struct {
actuator_shm_entry_t actuators[MAX_ACTUATORS];
int total_actuators;
int active_high_power_count;
pthread_mutex_t global_mutex;
} actuator_shm_t;

// SHM3: Telemetria e Sensores
typedef struct {
char key[32];
int last_value;
int min_value;
int max_value;
double avg_value;
int sample_count;
} key_telemetry_t;

typedef struct {
char sensor_id[32];
int online; // 1=ONLINE, 0=OFFLINE
int last_seen_ut;
int total_readings;
} sensor_entry_t;

typedef struct {
key_telemetry_t keys[MAX_KEYS];
int total_keys;
sensor_entry_t sensors[MAX_SENSORS];
int total_sensors;
pthread_mutex_t mutex;
pthread_cond_t cond_update; // sinaliza o Monitor (PTHREAD_PROCESS_SHARED)
unsigned long update_seq; // incrementado a cada atualização
} telemetry_shm_t;

// SHM4: Regras e Alertas Ativos
typedef struct {
char rule_id[16];
char key[32];
int min_limit;
int max_limit;
int severity; // 1=Crítico, 2=Aviso, 3=Info
char auto_actuator[20];
int auto_action_on; // 1=ON, 0=OFF
int auto_action_duration;
int is_active_alert; // 1 enquanto a regra estiver violada
} alert_rule_entry_t;

typedef struct {
char alert_id[16]; // AL_001, AL_002, ...
char rule_id[16];
int value; // valor que violou a regra
int timestamp_ut;
int state; // 0=ACTIVE, 1=ACKED, 2=RESOLVED
} alert_entry_t;

typedef struct {
alert_rule_entry_t rules[MAX_RULES];
int total_rules;
alert_entry_t alerts[MAX_ALERTS];
int total_alerts;
int next_alert_seq;
pthread_mutex_t mutex;
} alerts_shm_t;

#endif /* ipc_h */

#pragma once
#include <Arduino.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

typedef enum
{
    TASK_PRIORITY_IDLE = 1,
    TASK_PRIORITY_LOW = 2,
    TASK_PRIORITY_MEDIUM = 3,
    TASK_PRIORITY_HIGH = 4
} task_priority_t;

typedef struct
{
    TaskHandle_t handle;
    const char *name;
    UBaseType_t stack_depth;
    task_priority_t priority;
    BaseType_t core_id;
} task_config_t;

void createSystemTasks();
void monitorTaskStacks();
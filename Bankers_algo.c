#include <stdio.h>

#define MAX_PROCESSES 10
#define MAX_RESOURCES 10

int allocation[MAX_PROCESSES][MAX_RESOURCES];
int max_demand[MAX_PROCESSES][MAX_RESOURCES];
int available[MAX_RESOURCES];
int work[MAX_RESOURCES];
int finish[MAX_PROCESSES];

int num_processes, num_resources;
void input_data() {
    int i, j;
    printf("Enter the number of processes: ");
    scanf("%d", &num_processes);

    printf("Enter the number of resources: ");
    scanf("%d", &num_resources);

    printf("Enter the allocation matrix:\n");
    for (i = 0; i < num_processes; i++) {
        for (j = 0; j < num_resources; j++) {
            scanf("%d", &allocation[i][j]);
        }
    }
    printf("Enter the maximum demand matrix:\n");
    for (i = 0; i < num_processes; i++) {
        for (j = 0; j < num_resources; j++) {
            scanf("%d", &max_demand[i][j]);
        }
    }
    printf("Enter the available resources:\n");
    for (i = 0; i < num_resources; i++) {
        scanf("%d", &available[i]);
    }
}
int is_safe_state() {
    int i, j, k;

    // Initialize work and finish arrays
    for (i = 0; i < num_resources; i++) {
        work[i] = available[i];
    }

    for (i = 0; i < num_processes; i++) {
        finish[i] = 0;
    }

    int num_finished = 0;
    int is_safe = 0;

    while (num_finished < num_processes) {
        int can_execute = 0;

        for (i = 0; i < num_processes; i++) {
            if (!finish[i]) {
                int resource_available = 1;
                for (j = 0; j < num_resources; j++) {
                    if (max_demand[i][j] - allocation[i][j] > work[j]) {
                        resource_available = 0;
                        break;
                    }
                }

                if (resource_available) {
                    can_execute = 1;
                    finish[i] = 1;
                    num_finished++;

                    for (k = 0; k < num_resources; k++) {
                        work[k] += allocation[i][k];
                    }
                }
            }
        }

        if (!can_execute) {
            is_safe = 0;
            break;
        }

        if (num_finished == num_processes) {
            is_safe = 1;
            break;
        }
    }

    return is_safe;
}
int can_grant_request(int process_id, int request[]) {
    int i, j;
    int temp_available[MAX_RESOURCES];
    int temp_allocation[MAX_PROCESSES][MAX_RESOURCES];
    int temp_max_demand[MAX_PROCESSES][MAX_RESOURCES];

    for (i = 0; i < num_resources; i++) {
        if (request[i] > max_demand[process_id][i]) {
            return 0;  // Request exceeds maximum demand
        }
        if (request[i] > available[i]) {
            return 0;  // Request exceeds available resources
        }
    }

    for (i = 0; i < num_resources; i++) {
        temp_available[i] = available[i] - request[i];
        temp_allocation[process_id][i] = allocation[process_id][i] + request[i];
        temp_max_demand[process_id][i] = max_demand[process_id][i] - request[i];
    }

    int finish[MAX_PROCESSES] = { 0 };
    int work[MAX_RESOURCES];

    for (i = 0; i < num_resources; i++) {
        work[i] = temp_available[i];
    }

    int num_finished = 0;
    int is_safe = 0;

    while (num_finished < num_processes) {
        int can_execute = 0;

        for (i = 0; i < num_processes; i++) {
            if (!finish[i]) {
                int resource_available = 1;
                for (j = 0; j < num_resources; j++) {
                    if (temp_max_demand[i][j] > work[j]) {
                        resource_available = 0;
                        break;
                    }
                }

                if (resource_available) {
                    can_execute = 1;
                    finish[i] = 1;
                    num_finished++;

                    for (j = 0; j < num_resources; j++) {
                        work[j] += temp_allocation[i][j];
                    }
                }
            }
        }

        if (!can_execute) {
            is_safe = 0;
            break;
        }

        if (num_finished == num_processes) {
            is_safe = 1;
            break;
        }
    }

    return is_safe;
}

int main() {
    int process_id, request[MAX_RESOURCES];

    input_data();

    if (is_safe_state()) {
        printf("The system is in a safe state.\n");
    } else {
        printf("The system is not in a safe state.\n");
    }

    printf("Enter the process ID for the resource request: ");
    scanf("%d", &process_id);

    printf("Enter the resource request:\n");
    for (int i = 0; i < num_resources; i++) {
        scanf("%d", &request[i]);
    }

    if (can_grant_request(process_id, request)) {
        printf("The resource request can be granted.\n");
    } else {
        printf("The resource request cannot be granted.\n");
    }

    return 0;
}

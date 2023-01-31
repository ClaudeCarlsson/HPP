#include <stdio.h>
#include <stdlib.h>

typedef struct day {
    int index;
    double min;
    double max;
    struct day *next_day;
} day_t;

void insert_day(day_t **head, int index, double min, double max) {
    
    // Initiate and allocate a new day
    day_t *new_day = malloc(sizeof(day_t));
    new_day->index = index;
    new_day->min = min;
    new_day->max = max;
    new_day->next_day = NULL;

    // First insert for the program, set the new day as head
    if (*head == NULL) {
        *head = new_day;
        return;
    }

    // Find the position for the new day
    day_t *current = *head;
    day_t *previous = NULL;
    while (current != NULL && current->index < index) {
        previous = current;
        current = current->next_day;
    }

    // If index exists, update the day
    if (current != NULL && current->index == index) {
        current->min = min;
        current->max = max;
        return;
    }

    // Insert first day in the series
    if (previous == NULL) {
        new_day->next_day = *head;
        *head = new_day;
    // Insert middle or the last day in the series
    } else { 
        new_day->next_day = current;
        previous->next_day = new_day;
    }
}

void delete_day(day_t **head, int index) {
    day_t *current = *head;
    day_t *previous = NULL;

    // Find the day to delete
    while (current != NULL && current->index != index) {
        previous = current;
        current = current->next_day;
    }

    // Day was not found
    if (current == NULL) {
        return;
    }

    // First day in the series
    if (previous == NULL) {
        *head = current->next_day;
    // Middle or the last day in the series
    } else {
        previous->next_day = current->next_day;
    }

    // Free the memory of the current day
    free(current);
}

void print_database(day_t *head) {
    printf("Day Min Max\n");
    day_t *current = head;
    while (current != NULL) {
        printf("%d %lf %lf\n", current->index, current->min, current->max);

        current = current->next_day;
    }
}

int main(int argc, char *argv[]) {
    day_t *head = NULL;

    char command;
    int index;
    double min;
    double max;

    while (1) {
        printf("Enter command: ");
        scanf(" %c", &command);

        switch (command) {
            // Add
            case 'A': 
                scanf("%d %lf %lf", &index, &min, &max);
                insert_day(&head, index, min, max);
                break;
            // Delete
            case 'D':
                scanf("%d", &index);
                delete_day(&head, index);
                break;
            // Print
            case 'P':
                print_database(head);
                break;
            // Quit
            case 'Q': 
                // Free memory
                day_t *current = head;
                while (current != NULL) {
                    day_t *previous = current;
                    current = current->next_day;
                    free(previous);
                }
                return 0;

            // Error
            default:
                printf("Invalid command!\n");
                break;
        }
    }
}

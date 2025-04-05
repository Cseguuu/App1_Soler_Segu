#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/order.h"
#include "csv_parser.h"

// Función para encontrar la ultima ocurrencia de un caracter
char* strrchr(const char* s, int c);

// Función para dividir una línea de CSV en campos
char* split_csv_line(char* line, int* field_count) {
    *field_count = 0;
    char* token = strtok(line, ",");
    
    while (token != NULL) {
        (*field_count)++;
        token = strtok(NULL, ",");
    }
    
    strtok(line, ",");
    return line;
}

// Función para parsear un archivo CSV y cargar las órdenes
Order* parse_csv_file(const char* filename, int* total_orders) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Error abriendo el archivo");
        return NULL;
    }

    int capacity = 100;
    Order* orders = malloc(capacity * sizeof(Order));
    *total_orders = 0;

    char line[1000];
    // Saltar encabezado
    fgets(line, sizeof(line), file);

    while (fgets(line, sizeof(line), file)) {
        if (*total_orders >= capacity) {
            capacity *= 2;
            orders = realloc(orders, capacity * sizeof(Order));
        }

        line[strcspn(line, "\n")] = 0;

        Order* current_order = &orders[*total_orders];
        
        // Encontrar el incio del nombre de la pizza
        char* pizza_name_start = strrchr(line, '\"');
        if (pizza_name_start) {
            pizza_name_start += 2; // moverse despues de la cuota y coma            
            // Extraer el nombre de la pizza
            strcpy(current_order->pizza_name, pizza_name_start);
            
        
            *(pizza_name_start - 2) = '\0';
        }

        // Parseo del resto de los campos
        sscanf(line, "%lf,%lf,%[^,],%lf,%[^,],%[^,],%lf,%lf,%[^,],%[^,]",
               &current_order->pizza_id, 
               &current_order->order_id, 
               current_order->pizza_name_id,
               &current_order->quantity,
               current_order->order_date,
               current_order->order_time,
               &current_order->unit_price,
               &current_order->total_price,
               current_order->pizza_size,
               current_order->pizza_category);
        
        
        char* ingredients_start = strchr(line, '\"');
        if (ingredients_start) {
            ingredients_start++;
            char* ingredients_end = strrchr(line, '\"');
            if (ingredients_end) {
                *ingredients_end = '\0'; // terminar al cierre de la cuota
                
                // Parseo de ingredientes
                current_order->num_ingredients = 0;
                char* ingredient_token = strtok(ingredients_start, ",");
                while (ingredient_token != NULL && 
                       current_order->num_ingredients < MAX_INGREDIENTS) {
                    while (*ingredient_token == ' ') ingredient_token++;
                    strcpy(current_order->pizza_ingredients[current_order->num_ingredients], 
                          ingredient_token);
                    current_order->num_ingredients++;
                    ingredient_token = strtok(NULL, ",");
                }
            }
        }

        (*total_orders)++;
    }

    fclose(file);
    return orders;
}
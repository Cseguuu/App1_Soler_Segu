// src/csv_parser.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/order.h"
#include "csv_parser.h"

// Función para dividir una línea de CSV en campos
char* split_csv_line(char* line, int* field_count) {
    *field_count = 0;
    char* token = strtok(line, ",");
    
    // Contar número de campos
    while (token != NULL) {
        (*field_count)++;
        token = strtok(NULL, ",");
    }
    
    // Reiniciar el tokenizador
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

    // Tamaño inicial del arreglo de órdenes
    int capacity = 100;
    Order* orders = malloc(capacity * sizeof(Order));
    *total_orders = 0;

    char line[1000];
    // Saltar encabezado
    fgets(line, sizeof(line), file);

    while (fgets(line, sizeof(line), file)) {
        // Reallocate memory if needed
        if (*total_orders >= capacity) {
            capacity *= 2;
            orders = realloc(orders, capacity * sizeof(Order));
        }

        // Eliminar salto de línea
        line[strcspn(line, "\n")] = 0;

        Order* current_order = &orders[*total_orders];
        
        // Parsear campos individuales
        sscanf(line, "%lf,%lf,%[^,],%lf,%[^,],%[^,],%lf,%lf,%[^,],%[^,],%[^,],%[^\n]",
               &current_order->pizza_id, 
               &current_order->order_id, 
               current_order->pizza_name_id,
               &current_order->quantity,
               current_order->order_date,
               current_order->order_time,
               &current_order->unit_price,
               &current_order->total_price,
               current_order->pizza_size,
               current_order->pizza_category,
               current_order->pizza_ingredients[0],
               current_order->pizza_name);

        // Parsear ingredientes
        current_order->num_ingredients = 1;
        char* ingredient_token = strtok(current_order->pizza_ingredients[0], ", ");
        while (ingredient_token != NULL && 
               current_order->num_ingredients < MAX_INGREDIENTS) {
            strcpy(current_order->pizza_ingredients[current_order->num_ingredients], ingredient_token);
            current_order->num_ingredients++;
            ingredient_token = strtok(NULL, ", ");
        }

        (*total_orders)++;
    }

    fclose(file);
    return orders;
}


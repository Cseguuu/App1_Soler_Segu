// src/csv_parser.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/order.h"
#include "csv_parser.h"
#include "../debuger.h"

// Helper function to find the last occurrence of a character
char* strrchr(const char* s, int c);

// Función para dividir una línea de CSV en campos
char* split_csv_line(char* line, int* field_count) {
    LOG_DEBUG("Dividiendo línea CSV: %s", line);
    *field_count = 0;
    char* token = strtok(line, ",");
    
    while (token != NULL) {
        (*field_count)++;
        LOG_DEBUG("Campo %d: %s", *field_count, token);
        token = strtok(NULL, ",");
    }
    
    strtok(line, ",");
    return line;
}

// Función para parsear un archivo CSV y cargar las órdenes
Order* parse_csv_file(const char* filename, int* total_orders) {
    LOG_INFO("Iniciando parseo del archivo CSV: %s", filename);
    
    FILE* file = fopen(filename, "r");
    CHECK(file != NULL, "No se pudo abrir el archivo CSV");
    
    int capacity = 100;
    Order* orders = malloc(capacity * sizeof(Order));
    CHECK(orders != NULL, "Fallo al asignar memoria para órdenes");
    *total_orders = 0;

    LOG_DEBUG("Capacidad inicial: %d órdenes", capacity);

    char line[1000];
    // Saltar encabezado
    if(!fgets(line, sizeof(line), file)) {
        LOG_WARN("Archivo CSV vacío o sin encabezado");
    } else {
        LOG_DEBUG("Encabezado omitido: %s", line);
    }

    while (fgets(line, sizeof(line), file)) {
        if (*total_orders >= capacity) {
            capacity *= 2;
            LOG_DEBUG("Redimensionando capacidad a %d órdenes", capacity);
            orders = realloc(orders, capacity * sizeof(Order));
            CHECK(orders != NULL, "Fallo al realocar memoria");
        }

        line[strcspn(line, "\n")] = 0;
        LOG_DEBUG("Procesando línea %d: %s", *total_orders + 1, line);

        Order* current_order = &orders[*total_orders];
        
        // Find the start of the pizza name
        char* pizza_name_start = strrchr(line, '\"');
        if (pizza_name_start) {
            pizza_name_start += 2;
            strcpy(current_order->pizza_name, pizza_name_start);
            *(pizza_name_start - 2) = '\0';
            LOG_DEBUG("Nombre de pizza extraído: %s", current_order->pizza_name);
        }

        // Parsear campos restantes
        int parsed = sscanf(line, "%lf,%lf,%[^,],%lf,%[^,],%[^,],%lf,%lf,%[^,],%[^,]",
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
        
        if(parsed != 10) {
            LOG_WARN("Línea %d: Solo se parsearon %d/10 campos correctamente", 
                   *total_orders + 1, parsed);
        }

        // Procesar ingredientes
        char* ingredients_start = strchr(line, '\"');
        if (ingredients_start) {
            ingredients_start++;
            char* ingredients_end = strrchr(line, '\"');
            if (ingredients_end) {
                *ingredients_end = '\0';
                
                current_order->num_ingredients = 0;
                char* ingredient_token = strtok(ingredients_start, ",");
                while (ingredient_token != NULL && 
                       current_order->num_ingredients < MAX_INGREDIENTS) {
                    while (*ingredient_token == ' ') ingredient_token++;
                    strcpy(current_order->pizza_ingredients[current_order->num_ingredients], 
                          ingredient_token);
                    LOG_DEBUG("Ingrediente %d: %s", 
                            current_order->num_ingredients + 1,
                            current_order->pizza_ingredients[current_order->num_ingredients]);
                    current_order->num_ingredients++;
                    ingredient_token = strtok(NULL, ",");
                }
            }
        }

        (*total_orders)++;
        LOG_DEBUG("Orden %d parseada exitosamente", *total_orders);
    }

    LOG_INFO("Archivo CSV parseado exitosamente. Total de órdenes: %d", *total_orders);
    fclose(file);
    return orders;

error:
    if(file) fclose(file);
    return NULL;
}
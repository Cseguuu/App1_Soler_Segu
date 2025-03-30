// src/main.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/order.h"
#include "../include/csv_parser.h"
#include "../include/metrics.h"

// Mapeo de métricas a sus funciones correspondientes
struct MetricMapping {
    const char* name;
    MetricFunction function;
    const char* description; // Añadido: descripción completa de la métrica
};

int main(int argc, char* argv[]) {
    // Verificar argumentos de entrada
    if (argc < 3) {
        fprintf(stderr, "Uso: %s <archivo_csv> <metrica1> [<metrica2> ...]\n", argv[0]);
        return 1;
    }
    
    // Definir mapeo de métricas con sus descripciones
    struct MetricMapping metrics[] = {
        {"pms", pizza_mas_vendida, "Pizza más vendida"},
        {"pls", pizza_menos_vendida, "Pizza menos vendida"},
        {"dms", fecha_mas_ventas_dinero, "Fecha con más ventas en dinero"},
        {"dls", fecha_menos_ventas_dinero, "Fecha con menos ventas en dinero"},
        {"dmsp", fecha_mas_ventas_pizzas, "Fecha con más ventas en cantidad de pizzas"},
        {"dlsp", fecha_menos_ventas_pizzas, "Fecha con menos ventas en cantidad de pizzas"},
        {"apo", promedio_pizzas_orden, "Promedio de pizzas por orden"},
        {"apd", promedio_pizzas_dia, "Promedio de pizzas por día"},
        {"ims", ingrediente_mas_vendido, "Ingrediente más vendido"},
        {"hp", pizzas_por_categoria, "Cantidad de pizzas por categoría"}
    };
    int num_metrics = sizeof(metrics) / sizeof(metrics[0]);
    
    // Parsear archivo CSV
    int total_orders;
    Order* orders = parse_csv_file(argv[1], &total_orders);
        
    if (!orders) {
        fprintf(stderr, "Error al parsear el archivo CSV\n");
        return 1;
    }
    
    // Procesar métricas solicitadas
    for (int i = 2; i < argc; i++) {
        int metric_found = 0;
        for (int j = 0; j < num_metrics; j++) {
            if (strcmp(argv[i], metrics[j].name) == 0) {
                char* resultado = metrics[j].function(&total_orders, orders);
                // Usar la descripción en lugar de la abreviatura
                printf("%s: %s\n", metrics[j].description, resultado);
                free(resultado);
                metric_found = 1;
                break;
            }
        }
                
        if (!metric_found) {
            fprintf(stderr, "Métrica desconocida: %s\n", argv[i]);
        }
    }
    
    // Liberar memoria
    free(orders);
    
    return 0;
}
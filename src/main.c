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
};

int main(int argc, char* argv[]) {
    // Verificar argumentos de entrada
    if (argc < 3) {
        fprintf(stderr, "Uso: %s <archivo_csv> <metrica1> [<metrica2> ...]\n", argv[0]);
        return 1;
    }

    // Definir mapeo de métricas
    struct MetricMapping metrics[] = {
        {"pms", pizza_mas_vendida},
        {"pls", pizza_menos_vendida}
        // Agregar más métricas aquí
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
                printf("%s: %s\n", argv[i], resultado);
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
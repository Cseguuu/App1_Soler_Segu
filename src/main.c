// src/main.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/order.h"
#include "../include/csv_parser.h"
#include "../include/metrics.h"
#include "../debuger.h"

// Mapeo de métricas a sus funciones correspondientes
struct MetricMapping {
    const char* name;
    MetricFunction function;
    const char* description;
};

int main(int argc, char* argv[]) {
    LOG_INFO("Iniciando programa de análisis de pizzas");
    LOG_DEBUG("Argumentos recibidos: %d", argc);
    
    // Verificar argumentos de entrada
    if (argc < 3) {
        LOG_ERROR("Argumentos insuficientes. Uso: %s <archivo_csv> <metrica1> [<metrica2> ...]", argv[0]);
        return 1;
    }
    
    LOG_DEBUG("Archivo CSV a procesar: %s", argv[1]);
    LOG_DEBUG("Métricas solicitadas:");
    for(int i = 2; i < argc; i++) {
        LOG_DEBUG(" - %s", argv[i]);
    }
    
    // Definir mapeo de métricas
    struct MetricMapping metrics[] = {
        {"pms", pizza_mas_vendida, "Pizza más vendida"},
        {"pls", pizza_menos_vendida, "Pizza menos vendida"},
        // ... (resto de las métricas)
    };
    int num_metrics = sizeof(metrics) / sizeof(metrics[0]);
    
    // Parsear archivo CSV
    LOG_INFO("Iniciando parseo del archivo CSV");
    int total_orders;
    Order* orders = parse_csv_file(argv[1], &total_orders);
        
    if (!orders) {
        LOG_ERROR("Fallo al parsear el archivo CSV. Verifique la ruta y formato del archivo");
        return 1;
    }
    LOG_INFO("Archivo CSV parseado exitosamente. Órdenes procesadas: %d", total_orders);
    
    // Procesar métricas solicitadas
    LOG_INFO("Calculando métricas solicitadas");
    for (int i = 2; i < argc; i++) {
        int metric_found = 0;
        for (int j = 0; j < num_metrics; j++) {
            if (strcmp(argv[i], metrics[j].name) == 0) {
                LOG_DEBUG("Calculando métrica: %s (%s)", metrics[j].name, metrics[j].description);
                char* resultado = metrics[j].function(&total_orders, orders);
                
                if(!resultado) {
                    LOG_WARN("La métrica %s no devolvió resultado", metrics[j].name);
                    continue;
                }
                
                printf("%s: %s\n", metrics[j].description, resultado);
                free(resultado);
                metric_found = 1;
                break;
            }
        }
                
        if (!metric_found) {
            LOG_WARN("Métrica desconocida ignorada: %s", argv[i]);
        }
    }
    
    // Liberar memoria
    LOG_DEBUG("Liberando recursos");
    free(orders);
    LOG_INFO("Programa finalizado exitosamente");
    
    return 0;
}
// Otras métricas similares pueden ser implementadas siguiendo este patrón
// src/metrics.h
#ifndef METRICS_H
#define METRICS_H

#include "../include/order.h"

// Definición de tipo para punteros a funciones de métricas
typedef char* (*MetricFunction)(int*, Order*);

// Declaraciones de funciones de métricas
char* pizza_mas_vendida(int* size, Order* orders);
char* pizza_menos_vendida(int* size, Order* orders);

#endif // METRICS_H
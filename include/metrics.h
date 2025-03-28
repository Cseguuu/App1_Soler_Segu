// Actualizar header con nuevas declaraciones
// src/metrics.h
#ifndef METRICS_H
#define METRICS_H

#include "../include/order.h"

// Definición de tipo para punteros a funciones de métricas
typedef char* (*MetricFunction)(int*, Order*);

// Declaraciones de funciones de métricas
char* pizza_mas_vendida(int* size, Order* orders);
char* pizza_menos_vendida(int* size, Order* orders);
char* fecha_mas_ventas_dinero(int* size, Order* orders);
char* fecha_menos_ventas_dinero(int* size, Order* orders);
char* fecha_mas_ventas_pizzas(int* size, Order* orders);
char* fecha_menos_ventas_pizzas(int* size, Order* orders);
char* promedio_pizzas_orden(int* size, Order* orders);
char* promedio_pizzas_dia(int* size, Order* orders);
char* ingrediente_mas_vendido(int* size, Order* orders);
char* pizzas_por_categoria(int* size, Order* orders);

#endif // METRICS_H
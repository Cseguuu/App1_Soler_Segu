// src/metrics.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/order.h"
#include "../include/metrics.h"

// Métrica: Pizza más vendida (pms)
char* pizza_mas_vendida(int* size, Order* orders) {
    // Inicializar estructura para contar ventas de pizzas
    struct PizzaVenta {
        char pizza_name[MAX_PIZZA_NAME];
        double total_quantity;
    } *pizza_ventas = calloc(*size, sizeof(struct PizzaVenta));
    int unique_pizzas = 0;

    // Contar ventas por pizza
    for (int i = 0; i < *size; i++) {
        int found = 0;
        for (int j = 0; j < unique_pizzas; j++) {
            if (strcmp(orders[i].pizza_name, pizza_ventas[j].pizza_name) == 0) {
                pizza_ventas[j].total_quantity += orders[i].quantity;
                found = 1;
                break;
            }
        }
        
        if (!found) {
            strcpy(pizza_ventas[unique_pizzas].pizza_name, orders[i].pizza_name);
            pizza_ventas[unique_pizzas].total_quantity = orders[i].quantity;
            unique_pizzas++;
        }
    }

    // Encontrar pizza más vendida
    int max_index = 0;
    for (int i = 1; i < unique_pizzas; i++) {
        if (pizza_ventas[i].total_quantity > pizza_ventas[max_index].total_quantity) {
            max_index = i;
        }
    }

    char* resultado = malloc(MAX_PIZZA_NAME * sizeof(char));
    strcpy(resultado, pizza_ventas[max_index].pizza_name);

    free(pizza_ventas);
    return resultado;
}

// Métrica: Pizza menos vendida (pls)
char* pizza_menos_vendida(int* size, Order* orders) {
    // Similar a pizza_mas_vendida, pero buscando el mínimo
    struct PizzaVenta {
        char pizza_name[MAX_PIZZA_NAME];
        double total_quantity;
    } *pizza_ventas = calloc(*size, sizeof(struct PizzaVenta));
    int unique_pizzas = 0;

    // Proceso idéntico a pizza_mas_vendida
    for (int i = 0; i < *size; i++) {
        int found = 0;
        for (int j = 0; j < unique_pizzas; j++) {
            if (strcmp(orders[i].pizza_name, pizza_ventas[j].pizza_name) == 0) {
                pizza_ventas[j].total_quantity += orders[i].quantity;
                found = 1;
                break;
            }
        }
        
        if (!found) {
            strcpy(pizza_ventas[unique_pizzas].pizza_name, orders[i].pizza_name);
            pizza_ventas[unique_pizzas].total_quantity = orders[i].quantity;
            unique_pizzas++;
        }
    }

    // Encontrar pizza menos vendida
    int min_index = 0;
    for (int i = 1; i < unique_pizzas; i++) {
        if (pizza_ventas[i].total_quantity < pizza_ventas[min_index].total_quantity) {
            min_index = i;
        }
    }

    char* resultado = malloc(MAX_PIZZA_NAME * sizeof(char));
    strcpy(resultado, pizza_ventas[min_index].pizza_name);

    free(pizza_ventas);
    return resultado;
}


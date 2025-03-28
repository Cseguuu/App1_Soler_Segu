// src/metrics.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "../include/order.h"
#include "../include/metrics.h"

// Función auxiliar para encontrar el máximo de un arreglo de doubles
double find_max_double(double* arr, int size) {
    double max = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    return max;
}

// Función auxiliar para encontrar el mínimo de un arreglo de doubles
double find_min_double(double* arr, int size) {
    double min = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] < min) {
            min = arr[i];
        }
    }
    return min;
}

// 1. Pizza más vendida (pms)
char* pizza_mas_vendida(int* size, Order* orders) {
    struct PizzaVenta {
        char pizza_name[MAX_PIZZA_NAME];
        double total_quantity;
    } *pizza_ventas = calloc(*size, sizeof(struct PizzaVenta));
    int unique_pizzas = 0;

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

// 2. Pizza menos vendida (pls)
char* pizza_menos_vendida(int* size, Order* orders) {
    struct PizzaVenta {
        char pizza_name[MAX_PIZZA_NAME];
        double total_quantity;
    } *pizza_ventas = calloc(*size, sizeof(struct PizzaVenta));
    int unique_pizzas = 0;

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

// 3. Fecha con más ventas en dinero (dms)
char* fecha_mas_ventas_dinero(int* size, Order* orders) {
    struct FechaVenta {
        char fecha[MAX_DATE_LENGTH];
        double total_ventas;
    } *fechas_ventas = calloc(*size, sizeof(struct FechaVenta));
    int unique_fechas = 0;

    for (int i = 0; i < *size; i++) {
        int found = 0;
        for (int j = 0; j < unique_fechas; j++) {
            if (strcmp(orders[i].order_date, fechas_ventas[j].fecha) == 0) {
                fechas_ventas[j].total_ventas += orders[i].total_price;
                found = 1;
                break;
            }
        }
        
        if (!found) {
            strcpy(fechas_ventas[unique_fechas].fecha, orders[i].order_date);
            fechas_ventas[unique_fechas].total_ventas = orders[i].total_price;
            unique_fechas++;
        }
    }

    int max_index = 0;
    for (int i = 1; i < unique_fechas; i++) {
        if (fechas_ventas[i].total_ventas > fechas_ventas[max_index].total_ventas) {
            max_index = i;
        }
    }

    char* resultado = malloc((MAX_DATE_LENGTH + 50) * sizeof(char));
    sprintf(resultado, "%s (Ventas: $%.2f)", 
            fechas_ventas[max_index].fecha, 
            fechas_ventas[max_index].total_ventas);

    free(fechas_ventas);
    return resultado;
}

// 4. Fecha con menos ventas en dinero (dls)
char* fecha_menos_ventas_dinero(int* size, Order* orders) {
    struct FechaVenta {
        char fecha[MAX_DATE_LENGTH];
        double total_ventas;
    } *fechas_ventas = calloc(*size, sizeof(struct FechaVenta));
    int unique_fechas = 0;

    for (int i = 0; i < *size; i++) {
        int found = 0;
        for (int j = 0; j < unique_fechas; j++) {
            if (strcmp(orders[i].order_date, fechas_ventas[j].fecha) == 0) {
                fechas_ventas[j].total_ventas += orders[i].total_price;
                found = 1;
                break;
            }
        }
        
        if (!found) {
            strcpy(fechas_ventas[unique_fechas].fecha, orders[i].order_date);
            fechas_ventas[unique_fechas].total_ventas = orders[i].total_price;
            unique_fechas++;
        }
    }

    int min_index = 0;
    for (int i = 1; i < unique_fechas; i++) {
        if (fechas_ventas[i].total_ventas < fechas_ventas[min_index].total_ventas) {
            min_index = i;
        }
    }

    char* resultado = malloc((MAX_DATE_LENGTH + 50) * sizeof(char));
    sprintf(resultado, "%s (Ventas: $%.2f)", 
            fechas_ventas[min_index].fecha, 
            fechas_ventas[min_index].total_ventas);

    free(fechas_ventas);
    return resultado;
}

// 5. Fecha con más ventas en cantidad de pizzas (dmsp)
char* fecha_mas_ventas_pizzas(int* size, Order* orders) {
    struct FechaVenta {
        char fecha[MAX_DATE_LENGTH];
        double total_pizzas;
    } *fechas_ventas = calloc(*size, sizeof(struct FechaVenta));
    int unique_fechas = 0;

    for (int i = 0; i < *size; i++) {
        int found = 0;
        for (int j = 0; j < unique_fechas; j++) {
            if (strcmp(orders[i].order_date, fechas_ventas[j].fecha) == 0) {
                fechas_ventas[j].total_pizzas += orders[i].quantity;
                found = 1;
                break;
            }
        }
        
        if (!found) {
            strcpy(fechas_ventas[unique_fechas].fecha, orders[i].order_date);
            fechas_ventas[unique_fechas].total_pizzas = orders[i].quantity;
            unique_fechas++;
        }
    }

    int max_index = 0;
    for (int i = 1; i < unique_fechas; i++) {
        if (fechas_ventas[i].total_pizzas > fechas_ventas[max_index].total_pizzas) {
            max_index = i;
        }
    }

    char* resultado = malloc((MAX_DATE_LENGTH + 50) * sizeof(char));
    sprintf(resultado, "%s (Pizzas: %.0f)", 
            fechas_ventas[max_index].fecha, 
            fechas_ventas[max_index].total_pizzas);

    free(fechas_ventas);
    return resultado;
}

// 6. Fecha con menos ventas en cantidad de pizzas (dlsp)
char* fecha_menos_ventas_pizzas(int* size, Order* orders) {
    struct FechaVenta {
        char fecha[MAX_DATE_LENGTH];
        double total_pizzas;
    } *fechas_ventas = calloc(*size, sizeof(struct FechaVenta));
    int unique_fechas = 0;

    for (int i = 0; i < *size; i++) {
        int found = 0;
        for (int j = 0; j < unique_fechas; j++) {
            if (strcmp(orders[i].order_date, fechas_ventas[j].fecha) == 0) {
                fechas_ventas[j].total_pizzas += orders[i].quantity;
                found = 1;
                break;
            }
        }
        
        if (!found) {
            strcpy(fechas_ventas[unique_fechas].fecha, orders[i].order_date);
            fechas_ventas[unique_fechas].total_pizzas = orders[i].quantity;
            unique_fechas++;
        }
    }

    int min_index = 0;
    for (int i = 1; i < unique_fechas; i++) {
        if (fechas_ventas[i].total_pizzas < fechas_ventas[min_index].total_pizzas) {
            min_index = i;
        }
    }

    char* resultado = malloc((MAX_DATE_LENGTH + 50) * sizeof(char));
    sprintf(resultado, "%s (Pizzas: %.0f)", 
            fechas_ventas[min_index].fecha, 
            fechas_ventas[min_index].total_pizzas);

    free(fechas_ventas);
    return resultado;
}

// 7. Promedio de pizzas por orden (apo)
char* promedio_pizzas_orden(int* size, Order* orders) {
    struct OrderCount {
        double order_id;
        double total_pizzas;
    } *order_pizzas = calloc(*size, sizeof(struct OrderCount));
    int unique_orders = 0;

    for (int i = 0; i < *size; i++) {
        int found = 0;
        for (int j = 0; j < unique_orders; j++) {
            if (orders[i].order_id == order_pizzas[j].order_id) {
                order_pizzas[j].total_pizzas += orders[i].quantity;
                found = 1;
                break;
            }
        }
        
        if (!found) {
            order_pizzas[unique_orders].order_id = orders[i].order_id;
            order_pizzas[unique_orders].total_pizzas = orders[i].quantity;
            unique_orders++;
        }
    }

    double total_pizzas = 0;
    for (int i = 0; i < unique_orders; i++) {
        total_pizzas += order_pizzas[i].total_pizzas;
    }

    char* resultado = malloc(50 * sizeof(char));
    sprintf(resultado, "%.2f", total_pizzas / unique_orders);

    free(order_pizzas);
    return resultado;
}

// 8. Promedio de pizzas por día (apd)
char* promedio_pizzas_dia(int* size, Order* orders) {
    struct FechaVenta {
        char fecha[MAX_DATE_LENGTH];
        double total_pizzas;
    } *fechas_ventas = calloc(*size, sizeof(struct FechaVenta));
    int unique_fechas = 0;

    for (int i = 0; i < *size; i++) {
        int found = 0;
        for (int j = 0; j < unique_fechas; j++) {
            if (strcmp(orders[i].order_date, fechas_ventas[j].fecha) == 0) {
                fechas_ventas[j].total_pizzas += orders[i].quantity;
                found = 1;
                break;
            }
        }
        
        if (!found) {
            strcpy(fechas_ventas[unique_fechas].fecha, orders[i].order_date);
            fechas_ventas[unique_fechas].total_pizzas = orders[i].quantity;
            unique_fechas++;
        }
    }

    double total_pizzas = 0;
    for (int i = 0; i < unique_fechas; i++) {
        total_pizzas += fechas_ventas[i].total_pizzas;
    }

    char* resultado = malloc(50 * sizeof(char));
    sprintf(resultado, "%.2f", total_pizzas / unique_fechas);

    free(fechas_ventas);
    return resultado;
}

// 9. Ingrediente más vendido (ims)
char* ingrediente_mas_vendido(int* size, Order* orders) {
    struct IngredienteVenta {
        char ingrediente[50];
        double total_ventas;
    } *ingredientes_ventas = calloc(*size * MAX_INGREDIENTS, sizeof(struct IngredienteVenta));
    int unique_ingredientes = 0;

    for (int i = 0; i < *size; i++) {
        for (int j = 0; j < orders[i].num_ingredients; j++) {
            int found = 0;
            for (int k = 0; k < unique_ingredientes; k++) {
                if (strcmp(orders[i].pizza_ingredients[j], ingredientes_ventas[k].ingrediente) == 0) {
                    ingredientes_ventas[k].total_ventas += orders[i].quantity;
                    found = 1;
                    break;
                }
            }
            
            if (!found) {
                strcpy(ingredientes_ventas[unique_ingredientes].ingrediente, orders[i].pizza_ingredients[j]);
                ingredientes_ventas[unique_ingredientes].total_ventas = orders[i].quantity;
                unique_ingredientes++;
            }
        }
    }

    int max_index = 0;
    for (int i = 1; i < unique_ingredientes; i++) {
        if (ingredientes_ventas[i].total_ventas > ingredientes_ventas[max_index].total_ventas) {
            max_index = i;
        }
    }

    char* resultado = malloc(50 * sizeof(char));
    strcpy(resultado, ingredientes_ventas[max_index].ingrediente);

    free(ingredientes_ventas);
    return resultado;
}

// 10. Cantidad de pizzas por categoría (hp)
char* pizzas_por_categoria(int* size, Order* orders) {
    struct CategoriaVenta {
        char categoria[50];
        double total_pizzas;
    } *categorias_ventas = calloc(*size, sizeof(struct CategoriaVenta));
    int unique_categorias = 0;

    for (int i = 0; i < *size; i++) {
        int found = 0;
        for (int j = 0; j < unique_categorias; j++) {
            if (strcmp(orders[i].pizza_category, categorias_ventas[j].categoria) == 0) {
                categorias_ventas[j].total_pizzas += orders[i].quantity;
                found = 1;
                break;
            }
        }
        
        if (!found) {
            strcpy(categorias_ventas[unique_categorias].categoria, orders[i].pizza_category);
            categorias_ventas[unique_categorias].total_pizzas = orders[i].quantity;
            unique_categorias++;
        }
    }

    // Generar string de resultado
    char* resultado = malloc(500 * sizeof(char));
    resultado[0] = '\0';
    
    for (int i = 0; i < unique_categorias; i++) {
        char categoria_info[100];
        sprintf(categoria_info, "%s: %.0f pizzas; ", 
                categorias_ventas[i].categoria, 
                categorias_ventas[i].total_pizzas);
        strcat(resultado, categoria_info);
    }

    free(categorias_ventas);
    return resultado;
}


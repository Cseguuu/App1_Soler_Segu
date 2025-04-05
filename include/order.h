#ifndef ORDER_STRUCTURE_H
#define ORDER_STRUCTURE_H

#define MAX_PIZZA_NAME 100
#define MAX_INGREDIENTS 20
#define MAX_DATE_LENGTH 20

// Estructura para representar un pedido individual
typedef struct {
    double pizza_id;          // Identificador único de pizza
    double order_id;          // Identificador de orden
    char pizza_name_id[50];   // Identificador del nombre de pizza
    double quantity;          // Cantidad de pizzas
    char order_date[MAX_DATE_LENGTH];  // Fecha de la orden
    char order_time[20];      // Hora de la orden
    double unit_price;        // Precio unitario
    double total_price;       // Precio total
    char pizza_size[10];      // Tamaño de pizza
    char pizza_category[20];  // Categoría de pizza
    char pizza_ingredients[MAX_INGREDIENTS][50];  // Lista de ingredientes
    char pizza_name[MAX_PIZZA_NAME];  // Nombre completo de la pizza
    int num_ingredients;      // Número de ingredientes
} Order;

#endif 
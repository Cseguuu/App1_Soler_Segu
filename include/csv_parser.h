#ifndef CSV_PARSER_H
#define CSV_PARSER_H

#include "./order.h"

// Función para parsear archivo CSV
Order* parse_csv_file(const char* filename, int* total_orders);

#endif // CSV_PARSER_H
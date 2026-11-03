#include "sync_car.h"

void station_init(struct station *station){ // inicializa estação
    pthread_mutex_init(&station->mutex, NULL);
    pthread_cond_init(&station->car_arrived, NULL);
    pthread_cond_init(&station->all_boarded, NULL);
    station->waiting = 0;
    station->free_seats = 0;
    station->boarding = 0;
    station->car_present = 0;
}
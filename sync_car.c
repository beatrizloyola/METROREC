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

void station_on_board(struct station *station){ // passageiro senta
    pthread_mutex_lock(&station->mutex);
    station->boarding--;
    if (station->boarding == 0){
        pthread_cond_signal(&station->all_boarded);
    }
    pthread_mutex_unlock(&station->mutex);
}

void station_wait_for_car(struct station *station){
    pthread_mutex_lock(&station->mutex);
    station->waiting++;
    while (!station->car_present || station->free_seats == 0){
        pthread_cond_wait(&station->car_arrived, &station->mutex); // a mimir, solta lock
    }
    // acordou (tem carro e tem assento disponível)
    station->waiting--;
    station->free_seats--;
    station->boarding++;
    pthread_mutex_unlock(&station->mutex);
}

void station_load_car(struct station *station, int count){
    pthread_mutex_lock(&station->mutex);
    if (count <= 0 || station->waiting == 0){
        // nada a fazer
        pthread_mutex_unlock(&station->mutex);
        return;
    }
    station->car_present = 1;
    station->free_seats = count;
    pthread_cond_broadcast(&station->car_arrived); // CHEGOU GALERA! ACORDA
    while ((station->free_seats > 0 && station->waiting > 0) || station->boarding > 0){
        // ainda tem gente querendo entrar e assento livre pra essa galera
        // OU ainda tem gente entrando com assento já reservado
        pthread_cond_wait(&station->all_boarded, &station->mutex);
    }
    station->car_present = 0;
    station->free_seats = 0;
    pthread_mutex_unlock(&station->mutex);
}
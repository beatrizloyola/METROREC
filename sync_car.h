#ifndef SYNC_CAR_H
#define SYNC_CAR_H

#include <pthread.h>

struct station {
    pthread_mutex_t mutex;

    int waiting; // qtd de passageiros esperando
    int free_seats; // qtd de assentos livres
    int boarding; // qtd de assentos reservados ainda não embarcados
    int car_present; // a porta tá aberta? (1 ou 0)

    pthread_cond_t car_arrived; // carro chegou, acorda passageiros
    pthread_cond_t all_boarded; // passageiros embarcados, acorda carro
};

void station_init(struct station *station); // inicializa estação
void station_wait_for_car(struct station *station); // passageiro chega e espera o carro
void station_load_car(struct station *station, int count); // carro chegou
void station_on_board(struct station *station); // passageiro sentou

#endif
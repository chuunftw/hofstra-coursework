#include <stdio.h>
#include <stdlib.h>
#include <pthread.h> 

struct station {
    int available_seats;
    int waiting_students;
    int next_ticket;
    int next_student;
    pthread_mutex_t lock;
    pthread_cond_t bus_arrive_cond;
    pthread_cond_t bus_loaded_cond;
};

void station_init(struct station *station)
{
    station->waiting_students = 0;
    station->available_seats = 0;
    station->next_ticket = 1;
    station->next_student = 1;
    pthread_mutex_init(&station->lock, NULL);
    pthread_cond_init(&station->bus_arrive_cond, NULL);
    pthread_cond_init(&station->bus_loaded_cond, NULL);
}

void station_load_bus(struct station *station, int count)
{
    pthread_mutex_lock(&station->lock);
	if(station->waiting_students == 0 || count == 0){
		pthread_mutex_unlock(&station->lock);
		return; 
	}
	station->available_seats = count; 
	pthread_cond_broadcast(&station->bus_arrive_cond);
    
	while(station->available_seats>0 && station->waiting_students>0)
	{
        pthread_cond_wait(&station->bus_loaded_cond, &station->lock);
	}
	
	station->available_seats = 0; //even if leftover, all students have boarded 
	pthread_mutex_unlock(&station->lock);
}

int station_wait_for_bus(struct station *station, int myticket, int myid)
{
	pthread_mutex_lock(&station->lock);
	station->waiting_students++;

	while( station->available_seats == 0 || myticket != station->next_ticket){
		pthread_cond_wait(&station->bus_arrive_cond, &station->lock);
	}
    int myTurn = station->next_student;
	station->next_student++;
	station->available_seats--;
	station->waiting_students--;
	station->next_ticket++;      

	if(station->available_seats ==0 || station->waiting_students ==0){
		pthread_cond_signal(&station->bus_loaded_cond);
	}
	pthread_cond_broadcast(&station->bus_arrive_cond);

	pthread_mutex_unlock(&station->lock);
	return myTurn;

}
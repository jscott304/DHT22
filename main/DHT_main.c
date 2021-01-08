/*

	DHT22 sensor reading test

	Jun 2007: Ricardo Timmermann, implemetation


*/

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "DHT22.h"

void DHT_task(void *pvParameter)
{
    /* Inspect our own high water mark on entering the task. */
	//UBaseType_t uxHighWaterMark;
    //uxHighWaterMark = uxTaskGetStackHighWaterMark( NULL );

	printf( "Starting DHT Task\n\n");
	setDHTgpio( 4 );

	while(1) {
		printf("=== Reading DHT ===\n" );
		int ret = readDHT();
		errorHandler(ret);

		printf( "Hum %.1f\n", getHumidity() );
		printf( "Tmp %.1f\n", getTemperature() );
		
		/*Inspect highwater mark and print it*/
		//uxHighWaterMark = uxTaskGetStackHighWaterMark( NULL );
		//printf( "Remaining Stack %i Words\n\n", uxHighWaterMark );

		// -- wait at least 2 sec before reading again ------------
		// The interval of whole process must be beyond 2 seconds !! 
		vTaskDelay( 3000 / portTICK_RATE_MS );
	}
}

void app_main()
{
	//1550 words provided a buffer of 8 words starting disconnected this was the worst configuration
	//Removing the uxHighWaterMark logic should provide even more headroom
	xTaskCreate( &DHT_task, "DHT_task", 1550, NULL, 5, NULL );
}
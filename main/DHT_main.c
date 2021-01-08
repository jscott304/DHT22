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
	printf( "Starting DHT Task\n\n");
	setDHTgpio( 4 );

	while(1) {
		printf("=== Reading DHT ===\n" );
		int ret = readDHT();
		errorHandler(ret);

		printf( "Hum %.1f\n", getHumidity() );
		printf( "Tmp %.1f\n", getTemperature() );
		
		// -- wait at least 2 sec before reading again ------------
		// The interval of whole process must be beyond 2 seconds !! 
		vTaskDelay( 3000 / portTICK_RATE_MS );
	}
}

void app_main()
{
	xTaskCreate( &DHT_task, "DHT_task", 2048, NULL, 5, NULL );	
}


     //Used for UART
#include "bme280.h"
#include "bme280_defs.h"

#include "bcm2835.h"
#include "reading_temp_umi.h"

float valores[2];

/*!
 * @brief This API reads the sensor temperature, pressure and humidity data in forced mode.
 */
int8_t stream_sensor_data_forced_mode(struct bme280_dev *dev)
{
    /* Variable to define the result */
    int8_t rslt = BME280_OK;

    /* Variable to define the selecting sensors */
    uint8_t settings_sel = 0;

    /* Variable to store minimum wait time between consecutive measurement in force mode */
    uint32_t req_delay;

    /* Structure to get the pressure, temperature and humidity values */
    struct bme280_data comp_data, *ptr_comp_data;

    ptr_comp_data = &comp_data;

    /* Recommended mode of operation: Indoor navigation */
    dev->settings.osr_h = BME280_OVERSAMPLING_1X;
    dev->settings.osr_p = BME280_OVERSAMPLING_16X;
    dev->settings.osr_t = BME280_OVERSAMPLING_2X;
    dev->settings.filter = BME280_FILTER_COEFF_16;

    settings_sel = BME280_OSR_PRESS_SEL | BME280_OSR_TEMP_SEL | BME280_OSR_HUM_SEL | BME280_FILTER_SEL;

    /* Set the sensor settings */
    rslt = bme280_set_sensor_settings(settings_sel, dev);
    if (rslt != BME280_OK)
    {
        fprintf(stderr, "Failed to set sensor settings (code %+d).", rslt);

        return rslt;
    }

    /*Calculate the minimum delay required between consecutive measurement based upon the sensor enabled
     *  and the oversampling configuration. */
    req_delay = bme280_cal_meas_delay(&dev->settings);
   
    time_t rawtime;
    struct tm * timeinfo;
    int i = 0;

    FILE *file;
    file = fopen("arquivo.csv","w");
    fclose(file);
    

    /* Continuously stream sensor data */
    while (1)
    {
        FILE *file;
        file = fopen("arquivo.csv","a+");

	    time (&rawtime);
        timeinfo = localtime (&rawtime);
	
        /* Set the sensor to forced mode */
        rslt = bme280_set_sensor_mode(BME280_FORCED_MODE, dev);
        if (rslt != BME280_OK)
        {
            fprintf(stderr, "Failed to set sensor mode (code %+d).", rslt);
            break;
        }

        /* Wait for the measurement to complete and print data */
        dev->delay_us(req_delay, dev->intf_ptr);
        rslt = bme280_get_sensor_data(BME280_ALL, &comp_data, dev);
        if (rslt != BME280_OK)
        {
            fprintf(stderr, "Failed to get sensor data (code %+d).", rslt);
            break;
        }
            float temp = comp_data.temperature;
            float umi = comp_data.humidity;
            
            valores[0] = comp_data.humidity;
            valores[1] = comp_data.temperature;

       	    print_sensor_data(&comp_data);
	        printf("%s",asctime(timeinfo));
            fprintf(file, "Medicao %d - Hora: %s - Temperatura: %f - Umidade %f\n", i+1, asctime(timeinfo), temp, umi);
            i++;
	        sleep(1);
            fclose(file);

            if (!bcm2835_init())
                return 1;
 
            config_gpio_proj(1,1);

            pthread_t thread_id;
            pthread_create (&thread_id, NULL, &Servidor, ptr_comp_data);

            bcm2835_close();
    }

    return rslt;
}
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef enum {
    TEMPERATURE,
    PRESSURE,
    HUMIDITY
}SensorType;
typedef enum {
    ACTIVE,
    INACTIVE,
    ERROR
}SensorState;

typedef union {
    struct {
        short int min;
        short int max;
        float reading;
    }TempData;
    struct {
        float calibration;
        float reading;
    }HumidityData;
    struct {
        short int altitude;
        float reading;
    }PressureData;
}Data;

typedef struct {
    unsigned char id;
    char name[20];
    SensorType type;
    Data data;
    SensorState status;    
}__attribute__((packed)) SensorData ;

void init_sensor(SensorData* sensorlist,unsigned char count,int max){
    if(count > max){
        printf("\n Max sensors already connected\n");
        return ;
    }
    for(unsigned char i =0;i<count;i++){
        char type;

        printf("\n ID: ");
        scanf("%hhu",&sensorlist[i].id);

        printf("\n name: ");
        scanf("%19s",sensorlist[i].name);
        scanf("%*c");
        printf("\n T-temperature \n H-humidity \n P-pressure\n");
        printf("type: ");
        scanf("%c",&type);
        switch(type){
            case 'T':
                sensorlist[i].type = TEMPERATURE;
                break;
            case 'H':
                sensorlist[i].type = HUMIDITY;
                break;
            case 'P':
                sensorlist[i].type = PRESSURE;
                break;
            default:
                printf("enter valid datatype");
                return;
        }

        printf("\n data: \n");
        switch(type){
            case 'T':
                printf("min range :");
                scanf("%hd",&sensorlist[i].data.TempData.min);
                scanf("%*c");
                printf("max range :");
                scanf("%hd",&sensorlist[i].data.TempData.max);
                scanf("%*c");
                break;
            case 'H':
                printf("calibration :");
                scanf("%f",&sensorlist[i].data.HumidityData.calibration);
                scanf("%*c");
                break;
            case 'P':
                printf("altitude :");
                scanf("%hd",&sensorlist[i].data.PressureData.altitude);
                scanf("%*c");
                break;
            default :
                printf("invalid entry \n");
        }

        char status;
        printf("\n A-active\n I-inactive\n E-error \n");
        printf("status: ");
        scanf("%c",&status);
        switch(status){
            case 'A':
                sensorlist[i].status = ACTIVE;
                break;
            case 'I':
                sensorlist[i].status = INACTIVE;
                break;
            case 'E':
                sensorlist[i].status = ERROR;
                break;
            default:
                sensorlist[i].status = INACTIVE;
        }
        printf("Sensor Status : %u\n",sensorlist[i].status);
    }
}

void read_sensor_data(SensorData* sensorreading){
    unsigned char type = sensorreading->type;
    switch(type){
            case 0:
                (*sensorreading).data.TempData.reading = (float)rand() / (50.0);
                break;
            case 1:
                (*sensorreading).data.HumidityData.reading = (float)rand() / (50.0);
                break;
            case 2:
                (*sensorreading).data.PressureData.reading = (float)rand() / (50.0);
                break;
        }
}

void process_sensor_data(SensorData* sensorreading){
    unsigned char type = sensorreading->type;
    switch(type){
        float reading;
            case 0:
                reading = (*sensorreading).data.TempData.reading;
                short int min = (*sensorreading).data.TempData.min;
                short int max = (*sensorreading).data.TempData.max;
                if(reading<min || reading>max){
                    printf("\nerror detected\n");
                    sensorreading->status = ERROR;
                }
                break;
            case 1:
                reading = (*sensorreading).data.HumidityData.reading;
                float calibration = (*sensorreading).data.HumidityData.calibration;
                sensorreading->data.HumidityData.reading = reading * calibration;
                break;
            case 2:
                reading = (*sensorreading).data.PressureData.reading;
                float altitude = (*sensorreading).data.PressureData.altitude;
                sensorreading->data.PressureData.reading = reading + altitude;
                break;
        }
}

void display_sensors(SensorData* sensor_list,unsigned char count){
    //printf("%hhu")
    unsigned char type = sensor_list[count].type;
    switch(type){
            case 0:
                printf("Sensor Id : %u\n",sensor_list[count].id);
                printf("Sensor Name : %s\n",sensor_list[count].name);
                printf("Sensor Type : %s\n","TEMPERATURE");
                printf("Sensor Data : %f\n",sensor_list[count].data.TempData.reading);
                printf("Sensor Status : %u\n",sensor_list[count].status);
                break;
            case 1:
                printf("Sensor Id : %u\n",sensor_list[count].id);
                printf("Sensor Name : %s\n",sensor_list[count].name);
                printf("Sensor Type : %s\n","PRESSURE");
                printf("Sensor Data : %f\n",sensor_list[count].data.PressureData.reading);
                printf("Sensor Status : %u\n",sensor_list[count].status);
                break;
            case 2:
                printf("Sensor Id : %u\n",sensor_list[count].id);
                printf("Sensor Name : %s\n",sensor_list[count].name);
                printf("Sensor Type : %s\n","HUMIDITY");
                printf("Sensor Data : %f\n",sensor_list[count].data.HumidityData.reading);
                printf("Sensor Status : %u\n",sensor_list[count].status);
                break;
        }
}

int main(){
    srand(time(NULL));

    SensorData sensor_list[10] = {0};
    SensorData temp = {0};
    unsigned char count = 0;

    while(1){
        unsigned char choice;
        printf("\n1. Initialize Sensor \n2. Read Sensor Data \n3. Display Sensors \n4. Exit\n");
        printf("Enter choice: ");
        scanf("%hhu",&choice);
        printf("\n");

        switch(choice){
            case 1:
                printf("Enter count: ");
                scanf("%hhu",&count);
                init_sensor(sensor_list,count,10);
                break;
            case 2:
                for(unsigned char i = 0;i<count;i++){
                    read_sensor_data(&sensor_list[i]);
                    process_sensor_data(&sensor_list[i]);
                }
                break;
            case 3:
            printf("Sensor Status : %u\n",sensor_list[1].status);
                printf("Enter count: ");
                scanf("%hhu",&count);
                display_sensors(sensor_list,count);
                break;
            case 4:
                return 0;
            default:
                printf("Invalid choice \n");
        }
        
    }
    return 0;
}
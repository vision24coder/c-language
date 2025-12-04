#include <stdio.h>
#include <math.h>
#define PI 3.14
int main(){
    float samples_per_second = 44100;
    int duration = 2;
    int max_value_encoding = 32767;
    
    FILE *f;
    f = fopen("sine.raw","wb");
    if(f == NULL){
        printf("file not created");
        return -1;
    }

    int i = 0;
    int total_samples = duration*samples_per_second;
    int tone_freq = 440;
    float time = 0;
    float angle = 0;

    while(i<total_samples){
        time = i * (1/samples_per_second);
        angle = 2 * PI * tone_freq * time;
        int sample = max_value_encoding * sin(angle);
        printf("%d ",sample);

        fwrite(&sample,2,1,f);

        i++;
    }
}
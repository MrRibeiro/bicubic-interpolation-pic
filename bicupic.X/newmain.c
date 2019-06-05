
//Copyright: FELIXKLEMM - https://stackoverflow.com/questions/34622717/bicubic-interpolation-in-c
#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "uart.h"

const unsigned char sourcef[] = {80, 54, 10, 50, 49, 32, 50, 48, 10, 50, 53, 53, 
10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 248, 160, 104, 248, 160, 104, 248, 160,
104, 248, 160, 104, 248, 160, 104, 248, 160, 104, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 248, 248, 248, 248, 160, 104, 248, 248, 248, 248, 160, 104, 248, 
160, 104, 248, 248, 248, 248, 160, 104, 248, 248, 248, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 248, 160, 104, 248, 160, 104, 0, 0, 0, 248, 160, 104, 248, 160, 104, 0, 
0, 0, 248, 160, 104, 248, 160, 104, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 248, 160, 
104, 248, 160, 104, 0, 0, 0, 248, 160, 104, 248, 160, 104, 0, 0, 0, 248, 160, 104, 
248, 160, 104, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 248, 64, 40, 248, 248, 248, 248, 
160, 104, 248, 160, 104, 248, 160, 104, 248, 160, 104, 248, 248, 248, 248, 64, 40, 
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 0, 248, 64, 40, 248, 248, 248, 248, 248, 248, 248, 248, 
248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 
248, 64, 40, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 248, 64, 40, 248, 64, 40, 248, 248, 248, 248, 248, 248, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 248, 248, 248, 248, 248, 248, 248, 64, 40, 248, 64, 
40, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 248, 
64, 40, 248, 64, 40, 248, 248, 248, 248, 248, 248, 248, 64, 40, 248, 248, 248, 
248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 64, 40, 248, 248, 248, 248, 248, 
248, 248, 64, 40, 248, 64, 40, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
0, 248, 160, 104, 248, 64, 40, 248, 64, 40, 248, 248, 248, 248, 64, 40, 248, 64, 
40, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 64, 40, 248, 
64, 40, 248, 248, 248, 248, 64, 40, 248, 64, 40, 248, 160, 104, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 248, 160, 104, 248, 64, 40, 248, 64, 40, 248, 64, 40, 
248, 64, 40, 248, 64, 40, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 
248, 248, 64, 40, 248, 64, 40, 248, 64, 40, 248, 64, 40, 248, 64, 40, 248, 160, 
104, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 248, 160, 104, 248, 64, 40, 248, 
64, 40, 248, 64, 40, 0, 0, 0, 248, 64, 40, 248, 64, 40, 248, 248, 248, 248, 248, 
248, 248, 64, 40, 248, 64, 40, 0, 0, 0, 248, 64, 40, 248, 64, 40, 248, 64, 40, 248, 
160, 104, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 248, 64, 40, 248, 
64, 40, 248, 64, 40, 0, 0, 0, 248, 64, 40, 248, 64, 40, 248, 64, 40, 248, 64, 40, 
248, 64, 40, 248, 64, 40, 0, 0, 0, 248, 64, 40, 248, 64, 40, 248, 64, 40, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 248, 64, 40, 248, 64, 40, 
248, 64, 40, 0, 0, 0, 248, 64, 40, 248, 64, 40, 248, 64, 40, 248, 64, 40, 248, 64, 
40, 248, 64, 40, 0, 0, 0, 248, 64, 40, 248, 64, 40, 248, 64, 40, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 248, 64, 40, 0, 0, 0, 248, 
64, 40, 248, 64, 40, 248, 64, 40, 248, 64, 40, 248, 64, 40, 248, 64, 40, 248, 64, 
40, 248, 64, 40, 0, 0, 0, 248, 64, 40, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 248, 64, 40, 248, 64, 40, 
248, 64, 40, 248, 64, 40, 248, 64, 40, 248, 64, 40, 248, 64, 40, 248, 64, 40, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 248, 64, 40, 248, 64, 40, 248, 160, 104, 248, 160, 104, 248, 64, 40, 
248, 64, 40, 248, 160, 104, 248, 160, 104, 248, 64, 40, 248, 64, 40, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, -1};


typedef unsigned char uint8_t;
typedef signed char int8_t;
typedef unsigned short uint16_t;
typedef signed short int16_t;
typedef int sfloat;


#define CREATOR "FELIXKLEMM"
#define RGB_COMPONENT_COLOR 255

#define INP_PATH "imgs/lozman.ppm"
#define OUT_PATH "imgs/lozman_out.ppm"

#define W 21
#define H 20


#define CLAMP(v, min, max) if(v < min) { v = min; } else if(v > max) { v = max; }



//Estrutura usada para representar um pixel
typedef struct {

     unsigned char red,green,blue;
} PPMPixel;

//Estrutura usada para representar uma imagem. Possui vários pixels
typedef struct {
     int x, y; //Tamanho da imagem
     PPMPixel *data; //pixels
} PPMImage;


void mem_copy(char *buff, const char *source, int size){
    int i;
    
    for(i = 0; i < size; i++){
        buff[i] = source[i];
    }
}

// - Função que aloca na memoria o arquivo recebido por parametro
static void readPPM(PPMImage *img, const char *filename) {

    char buff[16];
    //FILE *fp;
    int c, rgb_comp_color;
    int chread = 0;

    //Abre arquivo PPM para leitura binária
    // fp = fopen(filename, "rb");
    // if(!fp) {

    //     fprintf(stderr, "Unable to open file '%s'\n", filename);
    //     exit(1);
    // }

    mem_copy(buff, sourcef, sizeof(buff));

    chread = 2;

    //checa formato da imagem
    if(buff[0] != 'P' || buff[1] != '6') {

        printf("Invalid image format (must be 'P6')\n");
        exit(1);
    }

    //ignora comentários
    // c = getc(fp);
    // while (c == '#') {

    //     while (getc(fp) != '\n');
    //     c = getc(fp);
    // }

    // ungetc(c, fp);

    while(sourcef[chread] == '\n') chread++;
    
    //lê tamanho da imagem
    img->x = atoi(sourcef + chread);
    
    while((sourcef + chread)[0] != ' ') chread++;
    
    chread++;
    
    img->y = atoi(sourcef + chread);
    
    //sscanf(sourcef + chread, "%d %d", &img->x, &img->y);

    chread += 3; //MAGICK

    // if(fscanf(fp, "%d %d", &img->x, &img->y) != 2) {

    //     fprintf(stderr, "Invalid image size (error loading '%s')\n", filename);
    //     exit(1);
    // }


    //while(sourcef[chread] == '\r') chread++;
    //while(sourcef[chread] == '\n') chread++;

    printf("chread 2: %s\n", sourcef+chread);

    //lê componentes RGB
    //sscanf((sourcef + chread), "%d", &rgb_comp_color);
    rgb_comp_color = atoi((sourcef+chread));

    chread += 3; //MORE MAGICK

    while(sourcef[chread] == '\n') chread++;

    printf("rgb_comp_color: %d\n", rgb_comp_color);

    printf("chread 3: %d", chread);

    // //Checa profundidade
    if(rgb_comp_color!= RGB_COMPONENT_COLOR) {
        printf("'%s' does not have 8-bits components\n", filename);
        exit(1);
    }

    //while (fgetc(fp) != '\n');
    //Alocação de memória para os pixels
    
    img->data = (sourcef + chread);

    //memcpy(img->data, (sourcef + chread), (3 * img->x * img->y));

    //Lê pixels do arquivo
    // if(fread(img->data, 3 * img->x, img->y, fp) != img->y) {
    //     fprintf(stderr, "Error loading image '%s'\n", filename);
    //     exit(1);
    // }

    //fclose(fp);
}

void writeSerial(uint8_t *sample){
    UART_Escrever_Buffer(sample, 3);
}

//void writePPM(const char *filename, PPMImage *img)
//{
//    FILE *fp;
//    //Abre arquivo para escrita binária
//    fp = fopen(filename, "wb");
//    if (!fp) {
//         fprintf(stderr, "Unable to open file '%s'\n", filename);
//         exit(1);
//    }
//
//    //Informa o formato da imagem
//    fprintf(fp, "P6\n");
//
//    //Comentários
//    fprintf(fp, "# Created by %s\n",CREATOR);
//
//    //Informa o tamanho da imagem
//    fprintf(fp, "%d %d\n",img->x,img->y);
//
//    // Informa RGB_COMPONENT_COLOR
//    fprintf(fp, "%d\n",RGB_COMPONENT_COLOR);
//
//    // Escreve pixels no arquivo destino
//    fwrite(img->data, 3 * img->x, img->y, fp);
//    fclose(fp);
//}

//Interpola valores passados por parametro para estimar o valor de um pixel novo, que deve ser gerado na imagem
sfloat cubic_hermite(sfloat A, sfloat B, sfloat C, sfloat D, sfloat t) {
	

    sfloat a = -A / 2.0f + (3.0f*B) / 2.0f - (3.0f*C) / 2.0f + D / 2.0f;
    sfloat b = A - (5.0f*B) / 2.0f + 2.0f*C - D / 2.0f;
    sfloat c = -A / 2.0f + C / 2.0f;
    sfloat d = B;
 
    return a*t*t*t + b*t*t + c*t + d;
}

void get_pixel_clamped(PPMImage *source_image, int x, int y, uint8_t temp[])  {
    CLAMP(x, 0, source_image->x - 1);
    CLAMP(y, 0, source_image->y - 1);
    
    temp[0] = source_image->data[x+(W*y)].red;
    temp[1] = source_image->data[x+(W*y)].green;
    temp[2] = source_image->data[x+(W*y)].blue;
}

void sample_bicubic(PPMImage *source_image, sfloat u, sfloat v, uint8_t sample[]) {
    sfloat x = (u * source_image->x)-0.5;
    int xint = (int)x;
    sfloat xfract = x-floor(x);
 
    sfloat y = (v * source_image->y) - 0.5;
    int yint = (int)y;
    sfloat yfract = y - floor(y);

    int i;

    uint8_t p00[3];
    uint8_t p10[3];
    uint8_t p20[3];
    uint8_t p30[3];
    
    uint8_t p01[3];
    uint8_t p11[3];
    uint8_t p21[3];
    uint8_t p31[3];

    uint8_t p02[3];
    uint8_t p12[3];
    uint8_t p22[3];
    uint8_t p32[3];

    uint8_t p03[3];
    uint8_t p13[3];
    uint8_t p23[3];
    uint8_t p33[3];
    

    // Obtem os 4 pixels da primeira linha
    get_pixel_clamped(source_image, xint - 1, yint - 1, p00);
    get_pixel_clamped(source_image, xint + 0, yint - 1, p10);
    get_pixel_clamped(source_image, xint + 1, yint - 1, p20);
    get_pixel_clamped(source_image, xint + 2, yint - 1, p30);
    
    // Obtem os 4 pixels da segunda linha
    get_pixel_clamped(source_image, xint - 1, yint + 0, p01);
    get_pixel_clamped(source_image, xint + 0, yint + 0, p11);
    get_pixel_clamped(source_image, xint + 1, yint + 0, p21);
    get_pixel_clamped(source_image, xint + 2, yint + 0, p31);
 
    // Obtem os 4 pixels da terceira linha
    get_pixel_clamped(source_image, xint - 1, yint + 1, p02);
    get_pixel_clamped(source_image, xint + 0, yint + 1, p12);
    get_pixel_clamped(source_image, xint + 1, yint + 1, p22);
    get_pixel_clamped(source_image, xint + 2, yint + 1, p32);
 
    // Obtem os 4 pixels da quarta linha
    get_pixel_clamped(source_image, xint - 1, yint + 2, p03);
    get_pixel_clamped(source_image, xint + 0, yint + 2, p13);
    get_pixel_clamped(source_image, xint + 1, yint + 2, p23);
    get_pixel_clamped(source_image, xint + 2, yint + 2, p33);
    
    // Interpolação bicubica, que usa os 16 bits mais próximos de um pixel para estimar seu valor
    for (i = 0; i < 3; i++) {
        sfloat col0 = cubic_hermite(p00[i], p10[i], p20[i], p30[i], xfract);
        sfloat col1 = cubic_hermite(p01[i], p11[i], p21[i], p31[i], xfract);
        sfloat col2 = cubic_hermite(p02[i], p12[i], p22[i], p32[i], xfract);
        sfloat col3 = cubic_hermite(p03[i], p13[i], p23[i], p33[i], xfract);

        sfloat value = cubic_hermite(col0, col1, col2, col3, yfract);

        CLAMP(value, 0.0f, 255.0f);

        sample[i] = (uint8_t)value;
        
        //printf("sample[%d]=%d\n",i,sample[i]);      
        
    }
    
}

//Função que redimensiona imagem origem, dado uma escala
void resize_image(PPMImage *source_image, PPMImage *destination_image, sfloat scale) {
	uint8_t sample[3];
	int y, x;
	
    destination_image->x = (long)((sfloat)(source_image->x)*scale);
    destination_image->y = (long)((sfloat)(source_image->y)*scale);
    
    for (y = 0; y < destination_image->y; y++) {

        sfloat v = (sfloat)y / (sfloat)(destination_image->y - 1);
        
        for (x = 0; x < destination_image->x; ++x) {

            sfloat u = (sfloat)x / (sfloat)(destination_image->x - 1);
    
            sample_bicubic(source_image, u, v, sample);

            writeSerial(sample);
            
            //destination_image->data[x+((destination_image->x)*y)].red   = sample[0];
            //destination_image->data[x+((destination_image->x)*y)].green	= sample[1];  
            //destination_image->data[x+((destination_image->x)*y)].blue 	= sample[2];  
        }
    }
}

sfloat get_scale(){
    sfloat scale;
    printf("Digite uma escala(sfloat): ");
    //scanf("%f", &scale);
    return scale;
}


int main() {
   
    UART_iniciar();
    UART_Escrever('a');
    
    int i;
    for(i =0; i < 100000; i++); //delay
    
    // - Inicia o contador pra saber o tempo de execução
    //clock_t tempo;
    // - Recebe um valor sfloat com a escala de resize
    //sfloat scale = get_scale();
    const sfloat scale = 2;

    //tempo = clock();

    //Cria vetores estáticos com os tamanhos adequados
    //PPMPixel dest_data[1680];

    // - Cria ponteiro pras imgs setando um tipo de estrutura especifica
    PPMImage source_image;
    PPMImage destination_image;

    //inicializa os ponteiros do PPMImage para apontar para os vetores estáticos
    //destination_image.data = dest_data;

    // - Deleta a img antiga caso exista
// 	if(remove(OUT_PATH) == 0)
// 		printf("Deleting old image...\n\n");

    // - Aloca a img a ser interpolada
    readPPM(&source_image, INP_PATH);

    
    while(1) {
        // - Chama a funcao que contem o metodo de interpolação bicubica
        resize_image(&source_image, &destination_image, scale);
    
        for(i =0; i < 100000; i++); //delay
    }
    // - Escreve na img resultante
    //writePPM(OUT_PATH, &destination_image);

    //printf("Tempo de interpolacao(ms): %f\n",(clock() - tempo) / (double)CLOCKS_PER_SEC);
}


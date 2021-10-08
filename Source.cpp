#define _USE_MATH_DEFINES
#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<cstring>
#include<cmath>
#include<string.h>
#include<stdlib.h>

#define eps 0.00001
#define MAX_STR_SIZE 80

int main() {
    char ch, bufstr[MAX_STR_SIZE];
    int nl, no, iter;
    FILE* input_file = fopen("input1.txt", "rt");
    char str[50];
    printf("Enter name of output file:\n");
    fgets(bufstr, MAX_STR_SIZE, input_file);
    sscanf(bufstr, "%s\n", str);

    fgets(bufstr, MAX_STR_SIZE, input_file);
    sscanf(bufstr, "%d", &iter);

    printf("Enter nl and no:\n");
    fgets(bufstr, MAX_STR_SIZE, input_file);
    sscanf(bufstr, "%d %d", &nl, &no);

    double x0, y0, x1, y1, ymin, ymax, xmin, xmax, R, b;
    double r[181];
    for(int cur_iter = 1; cur_iter <= iter; cur_iter++) {
        for (int i = 0; i < 181; i++) {
            r[i] = 0;
        }
        for (int n = 1; n <= nl; n++) {
            ch = '1';
            printf("\nEnter coords 0 and 1:\n");
            fgets(bufstr, MAX_STR_SIZE, input_file);
            sscanf(bufstr, "%lf %lf %lf %lf", &x0, &y0, &x1, &y1);
            if (x0 == x1) {                                    //vertikal
                while ((ch != '0') && (ch != 'y')) {
                    printf("\nExpected '0' or 'y'\n");
                    //while (getchar() != '\n') {}
                    fgets(bufstr, MAX_STR_SIZE, input_file);
                    sscanf(bufstr, "%c", &ch);
                }
                if (ch == 'y') {
                    printf("Enter ymin and ymax^\n");
                    fgets(bufstr, MAX_STR_SIZE, input_file); 
                    sscanf(bufstr, "%lf %lf", &ymin, &ymax);
                }
                for (int i = 0; i <= 180; i++) {
                    if (i != 90) {
                        b = x0 / cos(M_PI * i / 180);
                        if (((r[i] == 0) || (b < r[i])) && (b > 0)) {
                            if (ch == 'y') {
                                if ((b * sin(M_PI * i / 180) > ymin) && (b * sin(M_PI * i / 180) < ymax)) {
                                    r[i] = b;
                                }
                            }
                            else {
                                r[i] = b;
                            }
                        }
                    }
                }
            }
            else {                                        //ne Vertikal
                while ((ch != '0') && (ch != 'y') && (ch != 'x')) {
                    printf("\nExpected '0' or 'y' or 'x'\n");
                    //while (getchar() != '\n') {}
                    fgets(bufstr, MAX_STR_SIZE, input_file);
                    sscanf(bufstr, "%c", &ch);
                }
                if (ch == 'y') {
                    printf("Enter ymin and ymax^\n");
                    fgets(bufstr, MAX_STR_SIZE, input_file);
                    sscanf(bufstr, "%lf %lf", &ymin, &ymax);
                }
                if (ch == 'x') {
                    printf("Enter xmin and xmax^\n");
                    fgets(bufstr, MAX_STR_SIZE, input_file);
                    sscanf(bufstr, "%lf %lf", &xmin, &xmax);
                }
                for (int i = 0; i < 181; i++) {
                    if (abs(sin(M_PI * i / 180) - cos(M_PI * i / 180) * (y1 - y0) / (x1 - x0)) > eps) {// ... != 0
                        b = (y0 - x0 * (y1 - y0) / (x1 - x0)) / (sin(M_PI * i / 180) - cos(M_PI * i / 180) * (y1 - y0) / (x1 - x0));
                        if (((r[i] == 0) || (b < r[i])) && (b > 0)) {
                            if (ch == 'x') {
                                if ((b * cos(M_PI * i / 180) > xmin) && (b * cos(M_PI * i / 180) < xmax)) {
                                    r[i] = b;
                                }
                            }
                            else if (ch == 'y') {
                                if ((b * sin(M_PI * i / 180) > ymin) && (b * sin(M_PI * i / 180) < ymax)) {
                                    r[i] = b;
                                }
                            }
                            else {
                                r[i] = b;
                            }
                        }
                    }
                }
            }
        }
        for (int n = 1; n <= no; n++) {                // Kruglyi
            ch = '1';
            printf("\nEnter x0, y0, R\n");
            fgets(bufstr, MAX_STR_SIZE, input_file);
            sscanf(bufstr, "%lf %lf %lf", &x0, &y0, &R);
            while ((ch != '0') && (ch != 'y') && (ch != 'x')) {
                printf("\nExpected '0' or 'y' or 'x'\n");
                //while (getchar() != '\n') {}
                fgets(bufstr, MAX_STR_SIZE, input_file);
                sscanf(bufstr, "%c", &ch);
            }
            if (ch == 'y') {
                printf("Enter ymin and ymax^\n");
                fgets(bufstr, MAX_STR_SIZE, input_file);
                sscanf(bufstr, "%lf %lf", &ymin, &ymax);
            }
            if (ch == 'x') {
                printf("Enter xmin and xmax^\n");
                fgets(bufstr, MAX_STR_SIZE, input_file);
                sscanf(bufstr, "%lf %lf", &xmin, &xmax);
            }
            for (int i = 0; i < 181; i++) {
                if (pow(-2 * x0 * cos(M_PI * i / 180) - 2 * y0 * sin(M_PI * i / 180), 2) - 4 * (pow(x0, 2) + pow(y0, 2) - pow(R, 2)) >= 0) {
                    b = ((2 * x0 * cos(M_PI * i / 180) + 2 * y0 * sin(M_PI * i / 180) + sqrt(pow(-2 * x0 * cos(M_PI * i / 180) - 2 * y0 * sin(M_PI * i / 180), 2) - 4 * (pow(x0, 2) + pow(y0, 2) - pow(R, 2)))) / 2);
                    if (((r[i] == 0) || (b < r[i])) && (b > 0)) {
                        if (ch == 'x') {
                            if ((b * cos(M_PI * i / 180) > xmin) && (b * cos(M_PI * i / 180) < xmax)) {
                                r[i] = b;
                            }
                        }
                        else if (ch == 'y') {
                            if ((b * sin(M_PI * i / 180) > ymin) && (b * sin(M_PI * i / 180) < ymax)) {
                                r[i] = b;
                            }
                        }
                        else {
                            r[i] = b;
                        }
                    }
                }
            }
            for (int i = 0; i < 181; i++) {
                if (pow(-2 * x0 * cos(M_PI * i / 180) - 2 * y0 * sin(M_PI * i / 180), 2) - 4 * (pow(x0, 2) + pow(y0, 2) - pow(R, 2)) >= 0) {
                    b = ((2 * x0 * cos(M_PI * i / 180) + 2 * y0 * sin(M_PI * i / 180) - sqrt(pow(-2 * x0 * cos(M_PI * i / 180) - 2 * y0 * sin(M_PI * i / 180), 2) - 4 * (pow(x0, 2) + pow(y0, 2) - pow(R, 2)))) / 2);
                    if (((r[i] == 0) || (b < r[i])) && (b > 0)) {
                        if (ch == 'x') {
                            if ((b * cos(M_PI * i / 180) > xmin) && (b * cos(M_PI * i / 180) < xmax)) {
                                r[i] = b;
                            }
                        }
                        else if (ch == 'y') {
                            if ((b * sin(M_PI * i / 180) > ymin) && (b * sin(M_PI * i / 180) < ymax)) {
                                r[i] = b;
                            }
                        }
                        else {
                            r[i] = b;
                        }
                    }
                }
            }
        }
        
        char out_number[9], name[MAX_STR_SIZE];
        _itoa(cur_iter, out_number, 10);
        FILE* fp = fopen(strcat(strcat(strcpy(name, str), out_number),".txt"), "w+");               //TODO mnogofailov
        if (fp == NULL) {
            fprintf(stderr, "ERROR! File not opened!");
            return 1;
        }

        char buf[80];
        for (int i = 0; i < 181; i++) {
            sprintf(buf, "%d %lf\n", i, r[i]);
            fwrite(buf, strlen(buf), 1, fp);
        }
        fclose(fp);
    }
    fclose(input_file);
    return 0;
}
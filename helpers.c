#include "helpers.h"
#include <math.h>
#include <stdio.h>
// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    float value;
    int avg;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            value = (float)(image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3;
            avg = round(value);
            image[i][j].rgbtBlue = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtRed = avg;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    int sepiaRed, sepiaGreen, sepiaBlue;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //Calculate new RBG value
            sepiaRed = round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue);
            sepiaGreen = round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue);
            sepiaBlue = round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue);
            //Cap new RGB value
            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }
            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }
            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < (width / 2); j++) //image[0][first] = image[0][last], set middle point, flip both sides
        {
            RGBTRIPLE tmp; //swap first and last item
            tmp = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = tmp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copyimage[height][width];  //create a image[] copy, prevent change original value of image[];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float newred = 0.0, newgreen = 0.0, newblue = 0.0;
            int cnt = 0;
            for (int dr = -1; dr <= 1; dr++)  //dr=[-1,0,1], dc=[-1,0,1]
            {

                for (int dc = -1; dc <= 1; dc++)
                {
                    int nr, nc;
                    nr = i + dr; //adding dr and dc --> new i and new j
                    nc = j + dc;
                    if (nr >= 0 && nr < height && nc >= 0 && nc < width) //check if new i and new j are valid -->within 0~height and 0~width
                    {
                        newred += image[nr][nc].rgbtRed; //red  value from all neighbors
                        newgreen += image[nr][nc].rgbtGreen;
                        newblue += image[nr][nc].rgbtBlue;
                        cnt ++; //how many neighbors have been added
                    }
                }

            }
            copyimage[i][j].rgbtRed = round((float)newred / cnt); //set current cell's red to avg of all neighbors
            copyimage[i][j].rgbtGreen = round((float)newgreen / cnt);
            copyimage[i][j].rgbtBlue = round((float)newblue / cnt);
        }
    }

    for (int r = 0; r < height; r++)
    {
        for (int c = 0; c < width; c++)
        {
            image[r][c] = copyimage[r][c]; //set copyimage[] value back to original image[];
        }
    }
    return;
}


// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copyimage[height][width];  //create a image[] copy, prevent change original value of image[];
    int gx[] = {-1, 0, 1, -2, 0, 2, -1, 0, 1};
    int gy[] = {-1, -2, -1, 0, 0, 0, 1, 2, 1};
    int gsize = sizeof(gx) / sizeof(gx[0]);
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float gxRed = 0.0, gxGreen = 0.0, gxBlue = 0.0;
            float gyRed = 0.0, gyGreen = 0.0, gyBlue = 0.0;
            float red, green, blue;
            int m = 0;
            for (int dr = -1; dr <= 1; dr++)  //dr=[-1,0,1], dc=[-1,0,1]
            {
                for (int dc = -1; dc <= 1; dc++)
                {
                    int nr, nc;
                    nr = i + dr; //adding dr and dc --> new i and new j
                    nc = j + dc;
                    //for (int m = 0; m < gsize; m++)
                    //{
                    if (nr >= 0 && nr < height && nc >= 0 && nc < width) //check if new i and new j are valid -->within 0~height and 0~width
                    {
                        gxRed += gx[m] * image[nr][nc].rgbtRed;
                        gxGreen += gx[m] * image[nr][nc].rgbtGreen;
                        gxBlue += gx[m] * image[nr][nc].rgbtBlue;
                        gyRed += gy[m] * image[nr][nc].rgbtRed;
                        gyGreen += gy[m] * image[nr][nc].rgbtGreen;
                        gyBlue += gy[m] * image[nr][nc].rgbtBlue;
                    }
                    //}
                    m++;
                }
            }
            red = (float)sqrt(pow(gxRed, 2) + pow(gyRed, 2));
            green = (float)sqrt(pow(gxGreen, 2) + pow(gyGreen, 2));
            blue = (float)sqrt(pow(gxBlue, 2) + pow(gyBlue, 2));
            //printf("Red: %i\n", red);
            if (red > 255)
            {
                red = 255;
            }
            if (green > 255)
            {
                green = 255;
            }
            if (blue > 255)
            {
                blue = 255;
            }
            copyimage[i][j].rgbtRed = round(red);
            copyimage[i][j].rgbtGreen = round(green);
            copyimage[i][j].rgbtBlue = round(blue);

        }
    }

    for (int r = 0; r < height; r++)
    {
        for (int c = 0; c < width; c++)
        {
            image[r][c] = copyimage[r][c]; //set copyimage[] value back to original image[];
        }
    }
    return;
}

/*
Copyright 2013 Elbert van de Put
*/
#include "placer.h"

//an iterative quadratic placer
void quadraticPlace(Module *modules, Cell ***grid)
{
	int i, j, k;
	int mSize = modules->gateSize;
	//put the connected gates in an |gates|*|gates| matrix
	//create the matrix (free has to be done)
	float **a;
	a = (float**) malloc(mSize * sizeof(float*));
	for(i = 0; i < mSize; i++)
        a[i] = (float*) malloc(mSize * sizeof(float));

    //allocate memory for the global inverse matrix
    inverse = (float**) malloc(mSize * sizeof(float*));
	for(i = 0; i < mSize; i++)
        inverse[i] = (float*) malloc(mSize * sizeof(float));

    //zero out the matrices
    for(i = 0; i < mSize; i++)
        for(j = 0; j < mSize; j++)
        {
            a[i][j] = 0.0f;
            inverse[i][j] = 0.0f;
        }

	//if a connection between gate x and y exists fill a[y][x] and a[x][y] with the weight of the connection
	for(i = 0; i < mSize; i++)
	{
        //if a connection between gate x and y exists fill a[y][x] and a[x][y] with the weight of the connection (1)
        for(j = 0; j < modules->gates[i].outputSize; j++)
        {
            if(modules->gates[i].output[j] < modules->gateSize)
            {
                a[i][ modules->gates[i].output[j] ] = 1.0f;
                a[ modules->gates[i].output[j] ][i] = 1.0f;
            }
        }
	}

    //fill the diagonal with the sum of the row plus the weight of any connected pads
    float rowSum, conPads;
    for(i = 0; i < mSize; i++)
    {
        rowSum = 0.0f;
        for(j = 0; j < mSize; j++)
        {
            rowSum += a[i][j];
        }

        conPads = 0.0f;
        //find connected input
        for(j = 0; j < modules->inputSize; j++)
        {
            for(k = 0; k < modules->inputGateSize[j]; k++)
            {
                if(modules->inputGate[j][k] == i)
                    conPads += 1.0f;
            }
        }
        //find connected output
        for(j = 0; j < modules->gates[i].outputSize; j++)
        {
            if(modules->gates[i].output[j] > modules->gateSize)
                conPads += 1.0f;
        }

        //invert the items not on the diagonal
        for(j = 0; j < mSize; j++)
        {
            if(a[i][j] != 0.0f)
                a[i][j] = -a[i][j];
        }

        a[i][i] = rowSum + conPads;
    }

	//we need to create a vector for the x- and y-coordinates of the pads
    float *xV = (float*) calloc(mSize, sizeof(float));
    float *yV = (float*) calloc(mSize, sizeof(float));

    //search input gates
    float inputDistance = 100.0f / (modules->inputSize + 1.0f);
    for(i = 0; i < modules->inputSize; i++)
    {
        for(j = 0; j < modules->inputGateSize[i]; j++)
        {
            //input at left
            xV[ modules->inputGate[i][j] ] =  xV[ modules->inputGate[i][j] ] / 2;
            yV[ modules->inputGate[i][j] ] = (yV[ modules->inputGate[i][j] ] + (i + 1.0f) * inputDistance) / 2;

        }
    }

    //search output gates
    int outputCnt;
    float outputDistance = 100.0f / (modules->outputSize + 1.0f);
    for(i = 0; i < mSize; i++)
    {
        for(j = 0; j < modules->gates[i].outputSize; j++)
        {
            outputCnt = modules->gates[i].output[j] - modules->gateSize;
            if(outputCnt >= 0)
            {
                //output at right
                xV[i] += 100.0f;
                yV[i] = (yV[i] * 2 + (outputCnt + 1.0f) * outputDistance) / 3;
            }
        }
    }

    g_printf("Vector X:\n");
    for(i = 0; i < mSize; i++)
        g_printf(" %f,", xV[i]);

    g_printf("\nVector Y:\n");
    for(i = 0; i < mSize; i++)
        g_printf(" %f,", yV[i]);
    g_printf("\n");

	//now we need to invert the matrix
    float d;

    //first calculate the determinant to detect if the matrix is invertible
	d = determinant(a, mSize);

    d == 0 ? g_printf("ERROR: Inverse matrix not possible.\n") : cofactor(a, mSize);

	//and multiply the matrix by the x- and y-vector to get a vector that contains the x- and y-coordinates of all the gates
    float *x = (float*) malloc(mSize * sizeof(float));
    float *y = (float*) malloc(mSize * sizeof(float));

    for(i = 0; i < mSize; i++)
    {
        for(j = 0; j < mSize; j++)
        {
            //the bug is here :) we multiply by original matrix not by the inversed one
            x[i] += inverse[i][j] * xV[j];
            y[i] += inverse[i][j] * yV[j];
        }
    }


    for(i = 0; i < mSize; i++)
    {
        grid[ (int)(x[i]) ][ (int)(y[i]) ]->occupied = TRUE;
        grid[ (int)(x[i]) ][ (int)(y[i]) ]->type = GATE;
        grid[ (int)(x[i]) ][ (int)(y[i]) ]->ID = i;
    }

	return;
}

/*For calculating Determinant of the Matrix */
float determinant(float **a,float k)
{
	float s=1,det=0;
	int i,j,m,n,c;

	//create a new k*k matrix
	float **b;
	b = (float**) malloc(k * sizeof(float*));
	for(i = 0; i < k; i++)
        b[i] = (float*) malloc(k * sizeof(float));

    //if the matrix has size 1
	if (k==1)
	{
	 	return (a[0][0]);
	}
	else
	{
	 	det=0;
	 	for(c=0;c<k;c++)
	    {
			m=0;
			n=0;
			for(i=0;i<k;i++)
		  	{
		    	for (j=0;j<k;j++)
		      	{
		        	b[i][j]=0;
		        	if (i != 0 && j != c)
		         	{
		           		b[m][n]=a[i][j];
		           		if (n<(k-2))
		            		n++;
		           		else
		            	{
		            		n=0;
		            	 	m++;
		            	}
		            }
				}
		  	}
		 	det=det + s * (a[0][c] * determinant(b,k-1));
			s=-1 * s;
		}
	}
	return (det);
}

void cofactor(float **num,float f)
{
    int p,q,m,n,i,j;

	//create a new k*k matrix
	float **b;
	b = (float**) malloc(f * sizeof(float*));
	for(i = 0; i < f; i++)
        b[i] = (float*) malloc(f * sizeof(float));

    //create a new k*k matrix
	float **fac;
	fac = (float**) malloc(f * sizeof(float*));
	for(i = 0; i < f; i++)
        fac[i] = (float*) malloc(f * sizeof(float));

	for (q=0;q<f;q++)
	{
		for (p=0;p<f;p++)
   		{
			m=0;
			n=0;
     		for (i=0;i<f;i++)
     		{
       			for (j=0;j<f;j++)
        		{
          			if (i != q && j != p)
          			{
            			b[m][n]=num[i][j];
            			if (n<(f-2))
            			{
             				n++;
             			}
            			else
             			{
               				n=0;
               				m++;
               			}
					}
        		}
      		}
			fac[q][p]=pow(-1,q + p) * determinant(b,f-1);
		}
	}
	transpose(num,fac,f);
}

/*Finding transpose of matrix*/
void transpose(float **num,float **fac,float r)
{
//stopped here
	int i,j;
	float d;

	float **b;
	b = (float**) malloc(r * sizeof(float*));
	for(i = 0; i < r; i++)
        b[i] = (float*) malloc(r * sizeof(float));

	for (i=0;i<r;i++)
	{
		for (j=0;j<r;j++)
		{
			b[i][j]=fac[j][i];
        }
    }
	d=determinant(num,r);
	for (i=0;i<r;i++)
    {
		for (j=0;j<r;j++)
		{
        	inverse[i][j]=b[i][j] / d;
        }
    }

   	return(inverse);
}

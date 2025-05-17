#include <iostream>
#include <string>
#include <memory.h>
#include <cmath>

using namespace std;

struct cmplx
{
    double real;
    double imag;
};

void conject (cmplx &elementVal)
{
    elementVal.imag = -1 * elementVal.imag;
}

cmplx addCmplx(cmplx addC1 , cmplx addC2)
{
    cmplx cmplxOut;
    cmplxOut.real = addC1.real + addC2.real;
    cmplxOut.imag = addC1.imag + addC2.imag;
    return cmplxOut;
}

cmplx subtractCmplx(cmplx subC1 , cmplx subC2)
{
    cmplx cmplxOut;
    cmplxOut.real = subC1.real - subC2.real;
    cmplxOut.imag = subC1.imag - subC2.imag;
    return cmplxOut;
}
cmplx multiCmplx(cmplx multiC1 , cmplx multiC2)
{
    cmplx cmplxOut;
    cmplxOut.real = (multiC1.real * multiC2.real) - (multiC1.imag * multiC2.imag) ;
    cmplxOut.imag = (multiC1.real * multiC2.imag) + (multiC1.imag * multiC2.real) ;
    return cmplxOut;
}

cmplx divisionCmplx(cmplx divC1 , cmplx divC2)
{
    cmplx cmplxOut;
    conject(divC2);
    cmplxOut = multiCmplx( divC1 , divC2 );
    double denominator = ( pow(divC2.real , 2) + pow(divC2.imag , 2) );
    cmplxOut.real = cmplxOut.real / denominator;
    cmplxOut.imag = cmplxOut.imag / denominator;
    return cmplxOut ;
}

double Magnitude(cmplx magC1)
{
    double magnitude = sqrt(pow( magC1.real , 2 ) + pow( magC1.imag , 2 ));
    return magnitude;
}


//Solves system of linear equations
cmplx* SolveSystem(cmplx** matrix, unsigned int size);

int main() {
    const cmplx POS_REAL_ONE = { 1.0, 0.0 };
    const cmplx NEG_REAL_ONE = { -1.0, 0.0 };

    unsigned int nodes, elements, vs = 0, ind_VS, dep_VS, tot_VS;
    unsigned int elementPosNode, elementNegNode, depPosNode, depNegNode;
    string elementType;
    cmplx elementVal;

    cout << "Enter the number of nodes: ";
    cin >> nodes;

    cout << "Enter the number of elements: ";
    cin >> elements;

    cout << "Enter the number of independent voltage sources: ";
    cin >> ind_VS;

    cout << "Enter the number of dependent sources: ";
    cin >> dep_VS;

    tot_VS = ind_VS + dep_VS;

    cmplx** matrix = new cmplx*[nodes + tot_VS];
    for (unsigned int i = 0; i < (nodes + tot_VS); i++) {
        matrix[i] = new cmplx[nodes + tot_VS + 1];
        memset(matrix[i], 0, (nodes + tot_VS + 1) * sizeof(cmplx));
    }

    cout << "Enter the elements data (one by one):\n";
    for (unsigned int i = 0; i < elements; i++) {
        cout << "Element " << i + 1 << ":\n";
        cout << "Enter type (R, L, C, V, I, dV, dI): ";
        cin >> elementType;

        cout << "Enter the positive node (0-" << nodes - 1 << "): ";
        cin >> elementPosNode;

        cout << "Enter the negative node (0-" << nodes - 1 << "): ";
        cin >> elementNegNode;

        cout << "Enter the value (real and imaginary parts): ";
        cin >> elementVal.real >> elementVal.imag;


        if (elementType[0] == 'd' || elementType[0] == 'D') {
            cout << "Enter the dependent source's positive node (0-" << nodes - 1 << "): ";
            cin >> depPosNode;

            cout << "Enter the dependent source's negative node (0-" << nodes - 1 << "): ";
            cin >> depNegNode;

            depPosNode--;  // Convert to zero-indexed
            depNegNode--;
        }

        // Process element
        switch (elementType[0]) {
            case 'R':
            case 'r':
            case 'C':
            case 'c':
            case 'L':
            case 'l':
                elementVal = divisionCmplx(POS_REAL_ONE, elementVal);
                matrix[elementPosNode][elementPosNode] = addCmplx(matrix[elementPosNode][elementPosNode], elementVal);
                matrix[elementPosNode][elementNegNode] = subtractCmplx(matrix[elementPosNode][elementNegNode], elementVal);
                matrix[elementNegNode][elementPosNode] = subtractCmplx(matrix[elementNegNode][elementPosNode], elementVal);
                matrix[elementNegNode][elementNegNode] = addCmplx(matrix[elementNegNode][elementNegNode], elementVal);
                break;

            case 'I':
            case 'i':
                matrix[elementPosNode][nodes + tot_VS] = addCmplx(matrix[elementPosNode][nodes + tot_VS], elementVal);
                matrix[elementNegNode][nodes + tot_VS] = subtractCmplx(matrix[elementNegNode][nodes + tot_VS], elementVal);
                break;

            case 'V':
            case 'v':
                matrix[nodes + vs][elementPosNode] = POS_REAL_ONE;
                matrix[nodes + vs][elementNegNode] = NEG_REAL_ONE;
                matrix[nodes + vs][nodes + tot_VS] = elementVal;
                matrix[elementPosNode][nodes + vs] = NEG_REAL_ONE;
                matrix[elementNegNode][nodes + vs] = POS_REAL_ONE;
                vs++;
                break;

            case 'd':
            case 'D':
                if (elementType[1] == 'v' || elementType[1] == 'V') {
                    matrix[nodes + vs][elementPosNode] = POS_REAL_ONE;
                    matrix[nodes + vs][elementNegNode] = NEG_REAL_ONE;
                    matrix[nodes + vs][depPosNode] = multiCmplx(NEG_REAL_ONE, elementVal);
                    matrix[nodes + vs][depNegNode] = elementVal;
                    matrix[elementPosNode][nodes + vs] = NEG_REAL_ONE;
                    matrix[elementNegNode][nodes + vs] = POS_REAL_ONE;
                    vs++;
                } else if (elementType[1] == 'i' || elementType[1] == 'I') {
                    matrix[elementPosNode][depPosNode] = subtractCmplx(matrix[elementPosNode][depPosNode], elementVal);
                    matrix[elementPosNode][depNegNode] = addCmplx(matrix[elementPosNode][depNegNode], elementVal);
                    matrix[elementNegNode][depPosNode] = addCmplx(matrix[elementNegNode][depPosNode], elementVal);
                    matrix[elementNegNode][depNegNode] = subtractCmplx(matrix[elementNegNode][depNegNode], elementVal);
                }
                break;
        }
    }

    // Solve system and print solutions (same as before)
    cmplx* solutions = SolveSystem(matrix, nodes + tot_VS);
    for (unsigned int i = 0; i < nodes; i++)
        cout << "V(" << i + 1 << ") = " << solutions[i].real << " " << solutions[i].imag << "j\n";
    for (unsigned int i = nodes, c = 0; i < nodes + tot_VS; i++, c++)
        cout << "Iv(" << c + 1 << ") = " << solutions[i].real << " " << solutions[i].imag << "j\n";

    delete[] solutions;
    for (unsigned int i = 0; i < nodes + tot_VS; i++) delete[] matrix[i];
    delete[] matrix;

    return 0;
}

cmplx* SolveSystem(cmplx** matrix, unsigned int size)
{
	cmplx tempFactor;
	unsigned int i, j, k;

	for (i = 0; i < size; i++)
	{
		for (j = i + 1; j < size; j++)
		{
			if (Magnitude(matrix[i][i]) < Magnitude(matrix[j][i]))   // here
			{
				for (k = 0; k <= size; k++)
				{
					tempFactor = matrix[i][k];
					matrix[i][k] = matrix[j][k];
					matrix[j][k] = tempFactor;
				}
			}
		}
	}

	for (i = 0; i < size; i++)
	{
		for (j = 0; j < size; j++)
		{
			if (j != i)
			{
				tempFactor = divisionCmplx( matrix[j][i] , matrix[i][i] );
				for (k = i; k < size + 1; k++)
					matrix[j][k] = subtractCmplx( matrix[j][k] , multiCmplx( tempFactor , matrix[i][k] ) );
			}
		}
	}

	cmplx* solutions = new cmplx[size];
	for (i = 0; i < size; i++)
		solutions[i] = divisionCmplx( matrix[i][size] , matrix[i][i] );
	return solutions;
}


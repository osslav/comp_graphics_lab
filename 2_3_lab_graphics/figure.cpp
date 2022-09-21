#include "figure.h"

void sorting(int& biggerNum, int& lessNum)
{
    if (biggerNum < lessNum)
    {
        int temp = biggerNum;
        biggerNum = lessNum;
        lessNum = temp;
    }
}

Figure::Figure(int countPoints_)
{
    countPoints = countPoints_;

    arrPoints = new Point3D[countPoints];

    matrixLines = new bool*[countPoints];
    matrixViewedLines = new bool*[countPoints];
    for (int i = 0; i < countPoints; i++)           //используем элементы над главной диагональю
    {
        matrixLines[i] = new bool[i+1];
        matrixViewedLines[i] = new bool[i+1];
    }

    for(int i = 0; i < countPoints; i++)
        for(int j = 0; j < (i+1); j++)
        {
            matrixLines[i][j] = false;
            matrixViewedLines[i][j] = false;
        }
}

Figure::~Figure()
{
    if(countPoints != 0)
    {
        delete[] arrPoints;

        for (int i = 0; i < countPoints; i++)
        {
            delete [] matrixLines[i];
            delete [] matrixViewedLines[i];
        }

        delete[] matrixLines;
        delete[] matrixViewedLines;
    }
}

void Figure::setPoint(int index, Point3D newPoint)
{
    arrPoints[index] = newPoint;
}

Point3D Figure::getPoint(int index)
{
    return arrPoints[index];
}

void Figure::connectPoint(int indexFirstPoint, int indexSecondPoint)
{
    if (indexFirstPoint < countPoints && indexFirstPoint >= 0 && indexSecondPoint < countPoints && indexSecondPoint >= 0)
    {
        sorting(indexFirstPoint, indexSecondPoint);
        matrixLines[indexFirstPoint][indexSecondPoint] = true;
    }
}

void Figure::disconnectPoint(int indexFirstPoint, int indexSecondPoint)
{
    if (indexFirstPoint < countPoints && indexFirstPoint >= 0 && indexSecondPoint < countPoints && indexSecondPoint >= 0)
    {
        sorting(indexFirstPoint, indexSecondPoint);
        matrixLines[indexFirstPoint][indexSecondPoint] = false;
    }
}

bool Figure::checkLine(int indexFirstPoint, int indexSecondPoint)
{
    if (!matrixLines)
        return false;

    sorting(indexFirstPoint, indexSecondPoint);
    return matrixLines[indexFirstPoint][indexSecondPoint];
}

bool Figure::checkViewedLine(int indexFirstPoint, int indexSecondPoint)
{
    if (!matrixViewedLines)
        return false;

    sorting(indexFirstPoint, indexSecondPoint);
    return matrixViewedLines[indexFirstPoint][indexSecondPoint];
}

void Figure::calculateViewedLine(Point3D point_of_view)
{
    Point3D centerFigure;
    for (int i = 0; i < countPoints; i++)
    {
        centerFigure.shiftByX(arrPoints[i].getX()/countPoints);
        centerFigure.shiftByY(arrPoints[i].getY()/countPoints);
        centerFigure.shiftByZ(arrPoints[i].getZ()/countPoints);
    }

    int** planePoints = new int*[13];
    for(int i = 0; i < 13; i++)
        planePoints[i] = new int[3];
    //задняя грань карандаша
    planePoints[0][0] = 0;
    planePoints[0][1] = 1;
    planePoints[0][2] = 2;

    //грани основной части карандаша
    for (int i = 1; i < 7; i++)
    {
        planePoints[i][0] = i-1;
        planePoints[i][1] = i;
        planePoints[i][2] = i-1+6;
    }
    planePoints[6][1] = 0;

    //грани кончика карандаша
    for (int i = 7; i < 13; i++)
    {
        planePoints[i][0] = i-1;
        planePoints[i][1] = i;
        planePoints[i][2] = 12;
    }
    planePoints[12][1] = 6;

    double** W = new double*[13];
    for (int i = 0; i < 13; i++)
    {
        W[i] = new double[4];
        W[i][0] = (arrPoints[planePoints[i][2]].getY() - arrPoints[planePoints[i][0]].getY()) *
                (arrPoints[planePoints[i][1]].getZ() - arrPoints[planePoints[i][0]].getZ()) -
                (arrPoints[planePoints[i][1]].getY() - arrPoints[planePoints[i][0]].getY()) *
                (arrPoints[planePoints[i][2]].getZ() - arrPoints[planePoints[i][0]].getZ());

        W[i][1] = (arrPoints[planePoints[i][1]].getX() - arrPoints[planePoints[i][0]].getX()) *
                (arrPoints[planePoints[i][2]].getZ() - arrPoints[planePoints[i][0]].getZ()) -
                (arrPoints[planePoints[i][2]].getX() - arrPoints[planePoints[i][0]].getX()) *
                (arrPoints[planePoints[i][1]].getZ() - arrPoints[planePoints[i][0]].getZ());

        W[i][2] = (arrPoints[planePoints[i][2]].getX() - arrPoints[planePoints[i][0]].getX()) *
                (arrPoints[planePoints[i][1]].getY() - arrPoints[planePoints[i][0]].getY()) -
                (arrPoints[planePoints[i][1]].getX() - arrPoints[planePoints[i][0]].getX()) *
                (arrPoints[planePoints[i][2]].getY() - arrPoints[planePoints[i][0]].getY());

        W[i][3] = -(W[i][0]*arrPoints[planePoints[i][0]].getX() + W[i][1]*arrPoints[planePoints[i][0]].getY() + W[i][2]*arrPoints[planePoints[i][0]].getZ());
    }

    //задний 6-угольник
    if(W[0][0]*point_of_view.getX() + W[0][1]*point_of_view.getY() + W[0][2]*point_of_view.getZ() < 0)
    {
        for(int i = 1; i < 6; i++)
            matrixViewedLines[i][i-1] = true;
        matrixViewedLines[5][0] = true;
    }

    //боковые грани карандаша
    for(int i = 1; i < 6; i++)
        if (W[i][0]*point_of_view.getX() + W[i][1]*point_of_view.getY() + W[i][2]*point_of_view.getZ() >= 0)
        {
            matrixViewedLines[i][i-1] = true;
            matrixViewedLines[i-1 + 6][i-1] = true;
            matrixViewedLines[i + 6][i] = true;
            matrixViewedLines[i + 6][i-1 + 6] = true;
        }
    if (W[6][0]*point_of_view.getX() + W[6][1]*point_of_view.getY() + W[6][2]*point_of_view.getZ() >= 0)
    {
        matrixViewedLines[5][0] = true;
        matrixViewedLines[11][5] = true;
        matrixViewedLines[6][0] = true;
        matrixViewedLines[11][6] = true;
    }

    //грани кончика карандаша
    for(int i = 7; i < 12; i++)
        if (W[i][0]*point_of_view.getX() + W[i][1]*point_of_view.getY() + W[i][2]*point_of_view.getZ() >= 0)
        {
            matrixViewedLines[i][i-1] = true;
            matrixViewedLines[12][i-1] = true;
            matrixViewedLines[12][i] = true;
        }
    if (W[12][0]*point_of_view.getX() + W[12][1]*point_of_view.getY() + W[12][2]*point_of_view.getZ() >= 0)
    {
        matrixViewedLines[11][6] = true;
        matrixViewedLines[12][6] = true;
        matrixViewedLines[12][11] = true;
    }

}


void Figure::changeFigure(Matrix matrix)
{
    for (int i = 0; i < countPoints; i++)
        arrPoints[i] = matrix.changePoint(arrPoints[i]);
}

void Figure::operator =(const Figure& temp)
{
    if (&temp != this)
    {
        delete[] arrPoints;

        for (int i = 0; i < countPoints; i++)
            delete[] matrixLines[i];
        delete[] matrixLines;

        for (int i = 0; i < countPoints; i++)
            delete[] matrixViewedLines[i];
        delete[] matrixViewedLines;

        countPoints = temp.countPoints;

        arrPoints = new Point3D[countPoints];
        for (int i = 0; i < countPoints; i++)
            arrPoints[i] = temp.arrPoints[i];

        matrixLines = new bool*[countPoints];
        for (int i = 0; i < countPoints; i++)
        {
            matrixLines[i] = new bool[i+1];
            for (int j = 0; j < i+1; j++)
                matrixLines[i][j] = temp.matrixLines[i][j];
        }

        matrixViewedLines = new bool*[countPoints];
        for (int i = 0; i < countPoints; i++)
        {
            matrixViewedLines[i] = new bool[i+1];
            for (int j = 0; j < i+1; j++)
                matrixViewedLines[i][j] = temp.matrixViewedLines[i][j];
        }
    }
}
